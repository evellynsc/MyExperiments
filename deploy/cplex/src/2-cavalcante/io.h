#ifndef MSC_IO_H
#define MSC_IO_H

#include <iostream>
#include <fstream>

using namespace std;

class InputData
{
public:
    InputData();
    ~InputData();
    
    bool parse_input(const char *);   // parse instance from input file
    
    // instance data
    // TODO: os tipos estao certos? tau e T podem ser inteiros?
    int k;
    double tau;
    int n;
    int m;
    double **t_matrix;
    
private:
    bool instance_loaded;
};

#endif // MSC_IO_H
