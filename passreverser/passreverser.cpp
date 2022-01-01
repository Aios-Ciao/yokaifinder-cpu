#include <fstream>
#include <iostream>
#include <forward_list>
#include <numeric>
#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    ifstream ifs;
    ofstream ofs;

    string infname;
    string outfname;
    string password;

    if (argc != 3) {
        cout << "usage: passreverser infilename.txt outfilename.txt" << endl;
        return (-1);
    }

    infname = argv[1];
    outfname = argv[2];

    ifs.open(infname, ios::in);
    ofs.open(outfname, ios::out);

    while (getline(ifs, password)) {
        ofs << string(password.rbegin(), password.rend()) << endl;
    }

    ifs.close();
    ofs.close();

    return (0);
}
