/* process_input.cpp */
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <cmath>
#include <cfloat>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
using namespace std;

/* A program for taking in the sparse matrix representation and converting it
*  to a Inverted Index, as described in:
*  https://nlp.stanford.edu/IR-book/html/htmledition/an-example-information-retrieval-problem-1.html
*  (see figure 1.2 at the bottom of the page)
*
*  NOTE: there are many output testing statements that are commented out that
*        should help with debugging
*/

// this is a data structure for each cell which contains the cell_id
// as an int and pointers to: the next cell and the next skip
struct cell
{
    uint64_t cellid;
    cell* next;
    cell* skip;
};

// DESCRIPTION
class Skiplist
{
    public:
    map<int, cell*> gene_map;
    int skip_value;
    // constructor
    Skiplist(string filepath)
    {
        cout << "fetching data from files" << endl;
        ifstream data;
        data.open(filepath);

        if (!data.is_open())
        {
            cout << "ERROR: It seems that the filepath you gave does not exist." << endl;
            exit(EXIT_FAILURE);
        }

        //cout << "break 1" << endl;

        // Declare variables:
        int M, N, L;

        // Ignore headers and comments:
        while (data.peek() == '%')
            data.ignore(2048, '\n');

        // Read defining parameters:
        data >> M >> N >> L;
        cout << "M = " << M << endl;
        cout << "N = " << N << endl;
        cout << "L = " << L << endl;

        //cout << "break 2" << endl;

        // initializing struct data_map
        // struct cell tmp_cell;
        map<int, cell*> gene_map_last;
        //struct data_map my_datamap;
        //my_datamap.my_index.insert(pair<int, vector<int>>(0, vector<int>()));

        for (int l = 0; l < L; l++) // only needs to go up to Lth non-zero element
        {
            // cout << "from for loop: l = " << l << endl;
            // initialize row and column variables
            int m, n, exp;
            cell* tmp_cell = new cell;

            // m: gene (row number); n = cell (col number); data = value of expression
            data >> m >> n >> exp;
            // cout << "m = " << m << endl;
            // cout << "n = " << n << endl;
            // cout << "exp = " << exp << endl;
            
            //description
            tmp_cell->cellid = n;

            // assign m & n in data_map //
            // NOTE: n (cell numbers) should already be sorted low -> high
            if (gene_map_last.find(m) == gene_map_last.end())
            {
                // initializing key m with empty vector & adding first cell value
                // cout << "gene doesnt exist" << endl;
                gene_map.insert(pair<int, cell*>(m, tmp_cell));
                gene_map_last.insert(pair<int, cell*>(m, tmp_cell));
            }
            else
            {
                // cout << "gene exists" << endl;
                cell* last_cell = gene_map_last[m];
                // cout << last_cell->cellid << endl;
                // cout << last_cell << endl;
                last_cell->next = tmp_cell;
                // cout << last_cell->next << endl;
                gene_map_last[m] = tmp_cell;
            }
            // cout << gene_map_last[m] << endl;
            // this out tests the addition of the cell # to the vector
            // cout << "testing struct: " << gene_map[m]->cellid << endl;
        }
        //cout << "break 3" << endl;
        data.close();
    }
};


int main()
{
    cout << "from `process_input.cpp`" << endl;
    Skiplist input_data ("../data/filtered_matrices_mex/hg19/matrix.mtx");
    cout << "end building skiplist" << endl;

    // Below are print statements to test that the Skiplist built properly
    // cell* last_cell = input_data.gene_map.at(32709);
    // cout << input_data.gene_map.size() << endl;
    // cout << last_cell->cellid << endl;
    // cout << last_cell->next->cellid << endl;
    // cout << last_cell->next->next->cellid << endl;
    // cout << last_cell->next->next->next->cellid << endl;
    // cout << last_cell->next->next->next->next->cellid << endl;
    // cout << &(input_data.gene_map[32709].next).cellid << endl;
};

