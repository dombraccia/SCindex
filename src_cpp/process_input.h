/* process_input.cpp */
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "map"
#include <string>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <cfloat>

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
    int num_cells;
    int num_genes;
    // constructor
    Skiplist(string filepath, int skipval)
    {
        skip_value = skipval;
        cout << "fetching data from files" << endl;
        ifstream data;
        data.open(filepath);

        if (!data.is_open())
        {
            cout << "ERROR: It seems that the filepath you gave does not exist." << endl;
            exit(EXIT_FAILURE);
        }

        // Declare variables:
        int M, N, L;

        // Ignore headers and comments:
        while (data.peek() == '%')
            data.ignore(2048, '\n');

        // Read defining parameters:
        data >> M >> N >> L;
        num_cells = N;
        num_genes = M;
        cout << "number of genes = " << M << endl;
        cout << "number of cells = " << N << endl;
        cout << "number of non-zero expressed genes = " << L << endl;

        // initializing struct data_map
        // struct cell tmp_cell;
        map<int, cell*> gene_map_last;
        map<int, cell*> gene_map_skip;
        map<int, cell*> gene_map_prev;
        map<int, int> gene_map_skip_head;
        cell* prev;
        
        for (int l = 0; l < L; l++) // only needs to go up to Lth non-zero element
        {
            // initialize row and column variables
            int m, n, exp;
            cell* tmp_cell = new cell;

            data >> m >> n >> exp;
            
            // description
            tmp_cell->cellid = n;
            tmp_cell->next = NULL;
            tmp_cell->skip = NULL;
            // assign m & n in data_map //
            // NOTE: n (cell numbers) should already be sorted low -> high
            if (gene_map_last.find(m) == gene_map_last.end())
            {
                // initializing key m with empty vector & adding first cell value
                gene_map.insert(pair<int, cell*>(m, tmp_cell));
                gene_map_last.insert(pair<int, cell*>(m, tmp_cell));
                gene_map_skip.insert(pair<int, cell*>(m, tmp_cell));
                gene_map_prev.insert(pair<int, cell*>(m, tmp_cell));
                gene_map_skip_head.insert(pair<int, int>(m, 0));
            }
            else
            {
                cell* last_cell = gene_map_last[m]; 
                cell* skip_cell = gene_map_skip[m];
                last_cell->next = tmp_cell;
                gene_map_last[m] = tmp_cell;
                

                int head_val = gene_map_skip_head[m]*skip_value;

                if (n - head_val > skip_value) 
                {
                    skip_cell->skip = gene_map_prev[m];
                    gene_map_skip[m] = gene_map_prev[m]; 
                    gene_map_skip_head[m] = gene_map_skip_head[m] + 1;
                }
                gene_map_prev[m] = tmp_cell;
                
            }
        }
        data.close();
    }
};