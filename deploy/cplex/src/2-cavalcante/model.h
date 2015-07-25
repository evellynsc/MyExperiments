#ifndef MSC_MODEL_H
#define MSC_MODEL_H

#include <ilcplex/ilocplex.h>
#include <vector>
#include "io.h"

using namespace std;

class Model
{
public:
    // constructor builds model
    Model(InputData *);
    virtual ~Model();
    
    // model solution
    void solve_relaxed();
    void solve();
    
    // information
    vector<int> solution;      // std vector with index of chosen Ys
    void print_status();
    double objective_value();
    void export_model(const char *);
    void minimal_output(bool);
    
    // cplex objects
    IloEnv env;              // environment: manage memory and object identifiers
    IloModel model;          // model - represents the formulation to solve
    IloCplex cplex;          // cplex algorithm engine
    
    IloBoolVarArray y;       // decision variables (choice of points)
    IloBoolVarArray v;       // decision variables (covered vehicles)
    
    IloExpr obj;             // objective function
    
    IloRangeArray constr1;   // cover constraints
    IloRangeArray constr2;   // generalized upper bound on y constraint
    
    // other cplex info
    IloNum ub;
    IloNum lb;
    IloNum total_time;
    
private:
    // model building routines
    void create_variables();
    void create_objective_function();
    bool create_constraints();
    
    // setup cplex parameters
    void set_cplex_params(IloCplex *);
    
    // problem instance to solve (graph and conflict set)
    InputData *instance;
    
    bool min_out;            // minimal output by default
};

#endif // MSC_MODEL_H
