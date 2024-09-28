
// C++ code to demonstrate the working of
// iterator, begin() and end()
#include <iostream>
#include <iterator> // for iterators
#include <vector>   // for vectors
#include <string>

using namespace std;
int main()
{
   for (int i = 1; i < 100; i++)
    {
        string file = "uf20-0" + to_string(i) + ".cnf";
        cout << file << endl;
    }
}
