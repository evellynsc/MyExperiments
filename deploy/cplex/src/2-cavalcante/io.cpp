#include "io.h"

InputData::InputData()
{
    instance_loaded = false;
}

InputData::~InputData()
{
    // avoid delete if input file was parsed successfully
    if (instance_loaded)
    {
        for (int i=0; i<n; ++i)
            delete[] t_matrix[i];
        
        delete[] t_matrix;
    }
}

// parse instance file into InputData object
bool InputData::parse_input(const char *filename)
{
    ifstream input_fh(filename);
    
    if (input_fh.is_open())
    {
        // initialize T matrix: n more lines, each with m entries
        t_matrix = new double*[n];
        for (int i=0; i<n; i++)
        {
            t_matrix[i] = new double[m];
            for (int j=0; j<m; j++)
                input_fh >> t_matrix[i][j];
        }
        
        instance_loaded = true;  // flag matrix was initialized
        input_fh.close();
    }
    else
    {
        cerr << "ERROR: could not open file (might not exist)." << endl;
        return false;
    }
    
    return true;
}
