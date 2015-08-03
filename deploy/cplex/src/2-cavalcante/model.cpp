#include <cstdio>
#include <cmath>
#include <cfloat>     // for DBL_MAX
#include <algorithm>  // for min
#include "model.h"

// maximum tolerance, used to prevent numerical erros when comparing values
#define MAX_TOLERANCE 1e-5

// constructor builds model
Model::Model(InputData *inst)
: env(), model(env)
{
    // instance object
    this->instance = inst;
    
    // by default, output cplex and solution info verbosely
    this->min_out = false;
    
    // initialize cplex objects
    try
    {
        create_variables();
        create_objective_function();
        if (create_constraints() == false)
            throw new exception();
        
        cplex = IloCplex(model);
    }
    catch (IloException& e)
    {
        cerr << "Concert exception caught in Model constructor: " << e.getMessage() << endl;
    }
    catch (...)
    {
        cerr << "Error while executing Model constructor" << endl;
    }
}

Model::~Model()
{
    // handles possible exceptions during cleanup
    try
    {
        // model objects
        y.end();
        v.end();
        obj.end();
        //constr1.end();
        //constr2.end();
        
        model.end();   // model
        cplex.end();   // algorithm
        env.end();     // clear everything
    }
    catch (IloException& e)
    {
        cerr << "Concert exception caught in Model destructor: " << e.getMessage() << endl;
    }
    catch (...)
    {
        cerr << "Error while executing Model destructor" << endl;
    }
}

// model solution methods

void Model::solve_relaxed()
{
    // convert y and v into continuous vars in [0,1]
    IloConversion conv_y(env, y, ILOFLOAT);
    IloConversion conv_v(env, v, ILOFLOAT);
    model.add(conv_y);
    model.add(conv_v);
    
    // evaluates linear relaxation
    try
    {
        // setup search. NOTE: using all cplex preprocessing, heuristics and cuts
        set_cplex_params(&cplex);
        
        cplex.setOut(env.getNullStream());   // supress cplex output
        cplex.solve();
        
        // store upper bound
        ub = (double) cplex.getObjValue();
    }
    catch (IloException& e)
    {
        if (cplex.getStatus() == CPX_STAT_INFEASIBLE)
            return;
        else
        {
            cerr << "Concert exception while solving LP relaxation model: "
            << e.getMessage() << endl;
            return;
        }
    }
    catch (...)
    {
        cerr << "Error while solving LP relaxation model" << endl;
        return;
    }
    
    // make variables integer again
    model.remove(conv_y);
    model.remove(conv_v);
    conv_y.end();
    conv_v.end();
}

void Model::solve()
{
    // handles possible exceptions during execution
    try
    {
        // evaluate linear relaxation?
        solve_relaxed();
        
        // setup search and turn off cplex preprocessing, heuristics and cuts
        set_cplex_params(&cplex);
        
        // solve cplex model
        cplex.setOut(cout);
        IloTimer timer(env);
        timer.start();
        cplex.solve();
        timer.stop();
        total_time = timer.getTime();
        
        // store lower bound reached solving MIP
        lb = (double) cplex.getObjValue();
        
        // build std vector with index of chosen Ys
        solution = vector<int>();
        solution.clear();
        for (int i=0; i<instance->n; ++i)
            if (cplex.getValue(y[i]) > 1 - MAX_TOLERANCE)
                solution.push_back(i);
    }
    catch (IloException& e)
    {
        if (cplex.getStatus() == CPX_STAT_INFEASIBLE)
            return;
        else
            cerr << "Concert exception caught while solving Model: " << e.getMessage() << endl;
    }
    catch (...)
    {
        cerr << "Error while solving Model" << endl;
    }
}

// model building routines

void Model::create_variables()
{
    // label variables to print a more readable formulation in .lp file
    char buffer[50];
    
    // a binary decision variable for (choosing or not) an access point
    y = IloBoolVarArray(env, instance->n);
    
    for (int i=0; i<instance->n; ++i)
    {
        sprintf(buffer, "y_%d", i);
        y[i].setName(buffer);
    }
    
    // a binary decision variable indicating a vehicle is covered or not
    v = IloBoolVarArray(env, instance->m);
    
    for (int j=0; j<instance->m; ++j)
    {
        sprintf(buffer, "v_%d", j);
        v[j].setName(buffer);
    }
}

void Model::create_objective_function()
{
    // objective function: maximize covered vehicles
    obj = IloExpr(env);
    for (int j=0; j<instance->m; ++j)
        obj += v[j];
    
    // add objective function to model, indicating that we seek to maximize it
    model.add(IloMaximize(env, obj));
}

bool Model::create_constraints()
{
    char buffer[200];
    
    // 1. cover constraints: \sum_i {T_{ij} * y_i} => tau*v_j  \forall j
    constr1 = IloRangeArray(env, instance->m);
    
    for (int j=0; j<instance->m; ++j)
    {
        IloExpr constraint(env);
        
        // build inequality and store in the array
        for (int i=0; i<instance->n; ++i)
            constraint += (instance->t_matrix[i][j])*y[i];
        
        constraint -= (instance->tau)*v[j];
        constr1[j] = constraint >= 0;
        
        // label current constraint and add it to the model
        sprintf(buffer, "cover_constr_%d", j);
        constr1[j].setName(buffer);
        model.add(constr1[j]);
        constraint.end();
    }
    
    constr1.end();
    
    // 2. generalized upper bound constraint: \sum_i y_i <= k
    constr2 = IloRangeArray(env, 1);
    
    IloExpr constr2exp(env);
    for (int i=0; i<instance->n; ++i)
        constr2exp += y[i];
    
    // build inequality (constraint, sign, rhs)
    constr2[0] = constr2exp <= (instance->k);
    
    // label constraint and add it to the model
    sprintf(buffer, "gub_constr");
    constr2[0].setName(buffer);
    model.add(constr2[0]);
    
    constr2exp.end();
    constr2.end();
    
    return true;
}

// information methods

void Model::minimal_output(bool choice)
{
    this->min_out = choice;
}

double Model::objective_value()
{
    return cplex.getValue(obj);  // getObjValue()
}

void Model::export_model(const char *file_path)
{
    // export model as text file
    cplex.exportModel(file_path);
}

void Model::print_status()
{
    if (this->min_out)
    {
        printf("%10.4f \t", lb);
        printf("%10.4f \t", ub);
        printf("%10.4f \t", (double) 100. * ( ((double)ub-lb) / lb)  );
        cout << setw(12) <<  cplex.getStatus() << " \t";
        
        if (cplex.getStatus() == CPX_STAT_INFEASIBLE)
        {
            printf("%10s \t", "");
            printf("%10.2f \t", total_time);
            cout << setw(12) <<  cplex.getNiterations() << " \t";
            printf("%12d \t", (int) cplex.getNnodes());
            printf("%12d \t \t \t\n", (int) cplex.getNnodesLeft());
            return;
        }
        
        printf("%10.4f \t", (double) 100 * cplex.getMIPRelativeGap());
        printf("%10.2f \t", total_time);
        cout << setw(12) <<  cplex.getNiterations() << " \t";
        printf("%12d \t", (int) cplex.getNnodes());
        printf("%12d \t", (int) cplex.getNnodesLeft());
    }
    else
    {
        env.out() << endl << " ===================================================== " << endl;
        
        env.out() << " Model has " << cplex.getNrows() << " rows and " << cplex.getNcols() <<" columns" << endl;
        
        env.out() << fixed << setprecision(4) << showpoint;
        
        env.out() << " Objective   : " << setw(18) << lb << endl;
        env.out() << " UB          : " << setw(18) << ub << endl;
        env.out() << " LP gap      : " << setw(18) << (double) 100. * ( ((double)ub-lb) / lb) << " (\%)" << endl;
        env.out() << " Status      : " << setw(18) << cplex.getStatus() << endl;
        
        if (cplex.getStatus() == CPX_STAT_INFEASIBLE)
        {
            env.out() << " Time        : " << setw(18) << setprecision(2) << total_time << endl;
            env.out() << " Iterations  : " << setw(18) << cplex.getNiterations() << endl;
            env.out() << " # B&B nodes : " << setw(18) << (int) cplex.getNnodes() << endl;
            env.out() << " # nodes left: " << setw(18) << (int) cplex.getNnodesLeft()<< endl;
            env.out() << endl << " ===================================================== " << endl;
            
            return;   // do not show solution
        }
        
        env.out() << " GAP         : " << setw(18) << (double) 100 * cplex.getMIPRelativeGap() << " (\%)" << endl;
        env.out() << " Time        : " << setw(18) << setprecision(2) << total_time << endl;
        env.out() << " Iterations  : " << setw(18) << cplex.getNiterations() << endl;
        env.out() << " # B&B nodes : " << setw(18) << (int) cplex.getNnodes() << endl;
        env.out() << " # nodes left: " << setw(18) << (int) cplex.getNnodesLeft()<< endl;
    }
    
    // TODO: remove below - only printing solution
    if (!min_out)
    {
        cout << endl << " Solution includes " << solution.size() << " access points ";
        
	    int tmp = 0;   // quantos veiculos cobertos
		for (int j=0; j<instance->m; ++j)
		{
			if (cplex.getValue(v[j]) > 1 - MAX_TOLERANCE)
				++tmp;
		}

        cout << endl << " ===================================================== " << endl;
        cout << "solution:\t";
        for (unsigned i=0; i<solution.size(); ++i)
            cout << solution[i] << ' ';

        cout << endl << " ===================================================== " << endl;      
        cout << "coverage:\t" << tmp << endl;
        
        cout << endl << " ===================================================== " << endl;
    }
    
    // check solution for errors. TODO: check anything else you want here!
    
    if (solution.size() > (unsigned) instance->k)
    {
        cout << endl << " Error! Solution using " << solution.size() << " > "
             << instance->k << "= k access points" << endl;
        
        return;
    }
    
    for (int j=0; j<instance->m; ++j)
    {
        // cover constraint trivially satisfied if v_j = 0 (i.e. < epsilon)
        if (cplex.getValue(v[j]) < MAX_TOLERANCE)
            continue;
        
        // sum over: j-th column of T times y
        double aux = 0;
        for (int i=0; i<instance->n; ++i)
        {
            if (cplex.getValue(y[i]) > 1 - MAX_TOLERANCE)
                aux += instance->t_matrix[i][j];
        }
        
        if (aux < instance->tau)
        {
            cout << " Error! Vehicle " << j << " not covered but counting in objective" << endl;
            return;
        }
    }
    
}

void Model::set_cplex_params(IloCplex *cplex)
{
    // time limit
    cplex->setParam(IloCplex::TiLim, 3600);  // time limit for this solve call
    cplex->setParam(IloCplex::ClockType, 2);  // wall clock time (default...)
    
    // objective is integer, absolut gap cannot be less than 1
    //cplex->setParam(IloCplex::EpAGap, 0.9999);   // absolute MIP gap tolerance
    
    // suppress output
    if (this->min_out)
    {
        cplex->setParam(IloCplex::MIPDisplay, 0);
        cplex->setOut(env.getNullStream());
    }
    
    // search strategy
    //cplex->setParam(IloCplex::VarSel, CPX_VARSEL_DEFAULT);  // MIP variable selection strategy
    //cplex->setParam(IloCplex::VarSel, CPX_VARSEL_STRONG);  // MIP variable selection strategy
    //cplex->setParam(IloCplex::VarSel, CPX_VARSEL_MAXINFEAS);  // MIP variable selection strategy
    
    //cplex->setParam(IloCplex::MIPEmphasis, CPX_MIPEMPHASIS_BALANCED);  // MIP emphasis switch (default CPX_MIPEMPHASIS_BALANCED)
    //cplex->setParam(IloCplex::MIPEmphasis, CPX_MIPEMPHASIS_BESTBOUND);  // MIP emphasis switch (default CPX_MIPEMPHASIS_BALANCED)
    
    //cplex->setParam(IloCplex::NodeSel, CPX_NODESEL_BESTBOUND);  // node selection (best-bound search by default)
    //cplex->setParam(IloCplex::NodeSel, CPX_NODESEL_BESTEST);  // node selection (best-bound search by default)
    //cplex->setParam(IloCplex::NodeSel, CPX_NODESEL_DFS);  // node selection (best-bound search by default)
    
    // algorithms
    //cplex->setParam(IloCplex::MIPSearch, CPX_MIPSEARCH_TRADITIONAL);  // disable dynamic search (force branch and cut)
    //cplex->setParam(IloCplex::RootAlg, CPX_ALG_CONCURRENT);  // continuous optimizer for initial relaxation. default: automatic - CPX_ALG_AUTOMATIC
    //cplex->setParam(IloCplex::NodeAlg, CPX_ALG_AUTOMATIC);  // continuous optimizer for subproblems. default: automatic - CPX_ALG_AUTOMATIC
    
    // parallel (left parallelMode auto since using control callbacks)
    cplex->setParam(IloCplex::ParallelMode, CPX_PARALLEL_DETERMINISTIC);  // parallel mode switch
    //cplex->setParam(IloCplex::Threads, 0);  // global default thread count
    
    // turn off heuristics
    //cplex->setParam(IloCplex::HeurFreq, -1);  // heuristic frequency
    //cplex->setParam(IloCplex::RINSHeur, -1);  // do not apply RINS heuristic
    //cplex->setParam(IloCplex::FPHeur, -1);  // do not apply feasibility pump heuristic
    //cplex->setParam(IloCplex::LBHeur, 0);  // do not apply local branching heuristic
    
    // turn off preprocessing
    //cplex->setParam(IloCplex::PreInd, 0);  // do not apply presolve
    //cplex->setParam(IloCplex::RelaxPreInd, CPX_OFF);  // do not apply presolve
    //cplex->setParam(IloCplex::RepeatPresolve, 0);  // reapplication of presolve
    //cplex->setParam(IloCplex::PreslvNd, -1);  // node presolve
    //cplex->setParam(IloCplex::Symmetry, 0);  // symmetry breaking
    //cplex->setParam(IloCplex::AggInd, 0);  // do not use any aggregator
    //cplex->setParam(IloCplex::BndStrenInd, 0);  // no var bound strengthening
    //cplex->setParam(IloCplex::CoeRedInd, 0);  // no coefficient reduction
    //cplex->setParam(IloCplex::DepInd, 0);  // no dependency checker
    //cplex->setParam(IloCplex::Reduce, CPX_PREREDUCE_NOPRIMALORDUAL);  // no reductions
    
    // turn off cuts
    //cplex->setParam(IloCplex::CutPass, -1);  // cutting plane passes at root node
    //cplex->setParam(IloCplex::Cliques, -1);
    //cplex->setParam(IloCplex::Covers, -1);
    //cplex->setParam(IloCplex::DisjCuts, -1);
    //cplex->setParam(IloCplex::FlowCovers, -1);
    //cplex->setParam(IloCplex::FlowPaths, -1);
    //cplex->setParam(IloCplex::FracCuts, -1);
    //cplex->setParam(IloCplex::GUBCovers, -1);
    //cplex->setParam(IloCplex::ImplBd, -1);
    //cplex->setParam(IloCplex::MIRCuts, -1);
    //cplex->setParam(IloCplex::MCFCuts, -1);
    //cplex->setParam(IloCplex::ZeroHalfCuts, -1);
}
