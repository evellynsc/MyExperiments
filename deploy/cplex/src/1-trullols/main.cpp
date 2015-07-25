#include "io.h"
#include "model.h"
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 6)
    {
        cout << "usage: \t" << argv[0] << " [k] [tau] [n] [m] [input-file]" << endl << endl;
        return 0;
    }
    
    InputData* instance = new InputData();
    instance->k = atoi(argv[1]);
    instance->tau = atof(argv[2]);
    instance->n = atoi(argv[3]);
    instance->m = atoi(argv[4]);
    
    // parse given input file
    if (instance->parse_input(argv[5]) == false)
    {
        cout << "unable to parse input file" << endl;
        delete instance;
        return 0;
    }
    
    // TODO: remove me
//     cout << "T matrix is:" << endl;
//     for (int i=0; i<instance->n; i++)
//     {
//         cout << "[ ";
//         for (int j=0; j<instance->m; j++)
//             cout << instance->t_matrix[i][j] << " ";
//         
//         cout << "]" << endl;
//     }
    
    // the instance is now completely loaded - ok to solve it!
    Model *ip = new Model(instance);
    ip->minimal_output(false);
    ip->solve();
    ip->print_status();
    //ip->export_model("./formulation.lp");
    
    // clean-up
    delete instance;
    delete ip;
    
    return 0;
}
