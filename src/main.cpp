#include "process_input.h"
#include "Query_Operations.h"

int main()
{
    cout << "from `process_input.cpp`" << endl;

    // the Skiplist constuctor takes two parameters from the user:
    //      1. "path/to/file.mtx" (a string)
    //      2. skip_value (an int)
    //"../data/filtered_matrices_mex/hg19/matrix.mtx"
    //"../data/test.mtx"
    Skiplist input_data ("../data/filtered_matrices_mex/hg19/matrix.mtx", 1000);
    cout << "end building skiplist" << endl;

    // Below are print statements to test that the Skiplist built properly
    int c1_ctr=0, c2_ctr=0, int_ctr=0, union_ctr=0;
    cell* c1 = input_data.gene_map.at(29910);
    cell* temp = c1;
    
    while(temp != NULL)
    {
        c1_ctr += 1;
        temp = temp->next;
    }
    cout<<"C1 ----->"<<c1_ctr<<"\n";

    cell* c2 = input_data.gene_map.at(30972);
    temp = c2;
    while(temp != NULL)
    {
        c2_ctr += 1;
        temp = temp->next;
    }
    cout<<"C2 ----->"<<c2_ctr<<"\n";
    
    cell* union_list = NULL;
    union_list = UNION(c1, c2, NULL);
    temp = union_list;
    while(temp != NULL)
    {
        union_ctr += 1;
        temp = temp->next;
    }
    cout<<"Union ----->"<<union_ctr<<"\n";

    cell* intersection = NULL;
    intersection = INTERSECTION(c1, c2, 1000, NULL);
    temp = intersection;
    while(temp != NULL)
    {
        int_ctr += 1;
        temp = temp->next;
    }
    cout<<"Intersection ----->"<<int_ctr<<"\n";
};