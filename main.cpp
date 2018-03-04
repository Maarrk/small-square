#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string filenameIn = "input.txt";

    ifstream fin;
    fin.open(filenameIn, ifstream::in);

    int num;
    fin >> num;
    cout << num << endl;

    return 0;
}
