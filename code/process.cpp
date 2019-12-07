/* process.cpp */
#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm> 
using namespace std;

/* A program for taking in the sparse matrix representation and converting it
*  to a Inverted Index, as described in:
*  https://nlp.stanford.edu/IR-book/html/htmledition/an-example-information-retrieval-problem-1.html
*  (see figure 1.2 at the bottom of the page)
*/

/* ATTEMPT AT MAKING INVERTEDINDEX CLASS
// create inverted index class w some methods
class InvertedIndex 
{
    public:
        InvertedIndex() : genes()
        {};
    private:
        map< int, vector<int> > genes;
};
*/

/* testing adding info to an InvertedIndex */
void test()
{
    // initializing a map & insert empty vector
    map<int, vector<int> > tmp;
    tmp.insert(pair<int,vector<int> >(1, vector<int>()));

        //cout << tmp.at(1) << endl;

    // adding elements to the vector in the map
    tmp[1].push_back(1);
    tmp[1].push_back(2);

        cout << tmp.at(1)[1] << endl;
}

int main() {
    cout << "from `process.cpp`" << endl;
    test();
    //readData();
};

/*
void mtx2ii()
{
    cout << "fetching data from files" << endl; 
    ifstream data;
    data.open("../data/filtered_matrices_mex/hg19/matrix.mtx");

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

    // Read the data
        
        cout << "break 2" << endl; 

    int MN = M * N; // had to set the upper limit to be M * N, not L
    for (int l = 0; l < MN; l++)
    {
        // initialize row and column variables
    	int m, n;

        // m: gene (row number); n = cell (col number); data = value of expression
    	fin >> m >> n >> data; 

        // assign m & n in map
        map< int, vector<int> > II;
        II[m]

    }
    cout << "break 4" << endl; 
    fin.close();
    

    int g = 1;
    vector<int> c(5,1);
    //cout << "testing: " << c << endl;
    map< int, vector<int> > tmp;
    tmp[g] = c;
    int vals = tmp.at(1)[0];
    cout << vals << endl;
} */

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
