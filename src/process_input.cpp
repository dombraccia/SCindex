/* process_input.cpp */
#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm> 
#include<math.h>
#include<cmath>
#include<cfloat>
using namespace std;

/* A program for taking in the sparse matrix representation and converting it
*  to a Inverted Index, as described in:
*  https://nlp.stanford.edu/IR-book/html/htmledition/an-example-information-retrieval-problem-1.html
*  (see figure 1.2 at the bottom of the page)
*
*  NOTE: there are many output testing statements that are commented out that
*        should help with debugging
*/

// ATTEMPT AT MAKING INVERTEDINDEX CLASS
class InvertedIndex 
{
    public:
        struct data_map ;
    private:
        map<int, vector<int> > ii;
};

// this map structure contains the gene as the key which maps to a vector 
// that contains the numbers of the cells that express that gene
struct data_map 
{
    map<int, vector<int> > my_index;
};

// for testing new implementations
void test(); 

// for converting the sparse matrix representation to an inverted index
void mtx2ii(); 

int main() {
    cout << "from `process_input.cpp`" << endl;
    //test();
    mtx2ii();

};

void test()
{   
    // testing new data_map struct
    struct data_map my_datamap;

    // initializing with empty vector and 0 key
    my_datamap.my_index.insert(pair<int,vector<int> >(0, vector<int>()));
    
    // adding a value to the vector at the "0" key value
    my_datamap.my_index[0].push_back(1);

    // testing the addition
    cout << "testing struct: " << my_datamap.my_index.at(0)[0] << endl;
    bool val = std::isnan(my_datamap.my_index.at(0)[1]);
    cout << "testing existence: " << val << endl;

    //gene.gene_num = 11;
    //gene.cells.push_back(10);
        //my_datamap.my_index.at(0)
        //cout << "testing struct: " << my_datamap.my_index.at(0)[2] << endl;
}

void mtx2ii() // help from: http://www.cplusplus.com/forum/general/65804/
{
    cout << "fetching data from files" << endl; 
    ifstream data;
    data.open("../data/filtered_matrices_mex/hg19/matrix.mtx");

    //cout << "break 1" << endl; 
    
    // Declare variables:
    int M, N, L;

    // Ignore headers and comments:
    while (data.peek() == '%') data.ignore(2048, '\n');

    // Read defining parameters:
    data >> M >> N >> L;
    cout << "M = " << M << endl;
    cout << "N = " << N << endl;
    cout << "L = " << L << endl;

    //cout << "break 2" << endl; 

    // initializing struct data_map 
    struct data_map my_datamap;
    my_datamap.my_index.insert(pair<int,vector<int> >(0, vector<int>()));

    for (int l = 0; l < L; l++) // only needs to go up to Lth non-zero element
    {                              
        //cout << "from for loop: l = " << l << endl;
        // initialize row and column variables
    	int m, n, exp;

        // m: gene (row number); n = cell (col number); data = value of expression
    	data >> m >> n >> exp; 
        //cout << "m = " << m << endl;
        //cout << "n = " << n << endl;
        //cout << "exp = " << exp << endl;

        // assign m & n in data_map //
        // NOTE: n (cell numbers) should already be sorted low -> high
        if (my_datamap.my_index.find(m) == my_datamap.my_index.end()) 
        {
            // initializing key m with empty vector & adding first cell value
            my_datamap.my_index.insert(pair<int,vector<int> >(m, vector<int>()));
            my_datamap.my_index[m].push_back(n);
        } else 
        {
            my_datamap.my_index[m].push_back(n);
        }

        // this out tests the addition of the cell # to the vector
        //cout << "testing struct: " << my_datamap.my_index.at(m)[my_datamap.my_index.at(m).size() - 1] << endl;
    }
    //cout << "break 3" << endl; 
    data.close();
} 

/* read in data: 
// from .mtx sparse matrix representation, barcodes and genes
void readData()
{
    cout << "fetching data from files" << endl; 
    ifstream data;
    data.open("../data/filtered_matrices_mex/hg19/matrix.mtx");

    // from http://www.cplusplus.com/forum/general/65804/
    // Open the file:
    std::ifstream fin("../data/filtered_matrices_mex/hg19/matrix.mtx");
    cout << "break 1" << endl; 

    // Declare variables:
    int M, N, L;

    // Ignore headers and comments:
    while (fin.peek() == '%') fin.ignore(2048, '\n');

    // Read defining parameters:
    fin >> M >> N >> L;
    cout << "M = " << M << endl;
    cout << "N = " << N << endl;
    cout << "L = " << L << endl;

    // Create your matrix:
    cout << "break 2a" << endl; 
    double* matrix;			     // Creates a pointer to the array
    cout << "break 2b" << endl; 
    matrix = new double[L];	 // Creates the array of M*N size
    cout << "break 2c" << endl; 
    std::fill(matrix, matrix + M*N, 0.); // From <algorithm>, zeros all entries.

    // Read the data
    cout << "break 3" << endl; 
    int MN = M * N; // had to set the upper limit to be M * N, not L
    for (int l = 0; l < MN; l++)
    {
    	int m, n;
    	double data;
    	fin >> m >> n >> data;
        //cout << "data: " << data << endl;
        //cout << "m = " << m << endl;
        //cout << "n = " << n << endl;
        //cout << "data = " << data << endl;
        int index = (m-1) + (n-1)*M;
        //cout << "current index: " << index << endl;
    	matrix[index] = data;
    }
    cout << "break 4" << endl; 
    fin.close();
}; */
