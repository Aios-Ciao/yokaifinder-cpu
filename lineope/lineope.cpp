#include <fstream>
#include <iostream>
#include <forward_list>
#include <numeric>
#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    forward_list<string>    dic1;
    forward_list<string>    dic2;

    ifstream ifs;
    ofstream ofs;

    string infname1;
    string infname2;
    string password;
    string outfname;

    if (argc != 4) {
        cout << "usage: lineope infile1.txt infile2.txt outfile.txt" << endl;
        return (-1);
    }

    infname1 = argv[1];
    infname2 = argv[2];
    outfname = argv[3];

    // 開けるか確認
    ofs.open(outfname, ios::out);
    if (ofs.fail()) {
        cerr << "can't open file1 " << argv[3] << endl;
        return (-1);
    }
    ofs.close();
    ifs.open(infname2, ios::in);
    if (ifs.fail()) {
        cerr << "can't open file1 " << argv[2] << endl;
        return (-1);
    }
    ifs.close();
    ifs.open(infname1, ios::in);
    if (ifs.fail()) {
        cerr << "can't open file1 " << argv[1] << endl;
        return (-1);
    }

    // ファイル１読み込み
    while (getline(ifs, password)) {
        dic1.push_front(password);
    }
    ifs.close();

    ifs.open(infname2, ios::in);
    if (ifs.fail()) {
        cerr << "can't open file1 " << argv[1] << endl;
        return (-1);
    }

    // ファイル２読み込み
    while (getline(ifs, password)) {
        dic2.push_front(password);
    }
    ifs.close();

    dic1.sort();
    dic2.sort();

    ofs.open(outfname, ios::out);
    if (ofs.fail()) {
        cerr << "can't open file1 " << outfname << endl;
        return (-1);
    }
    for (auto it : dic1) {
        for (auto trg = dic2.before_begin(); ;) {
            auto nx = next(trg);
            if (nx == dic2.end()) {
                break;
            }
            if (std::equal(begin(it), end(it), nx->begin(), nx->end())) {
                ofs << it << endl;
                trg = dic2.erase_after(trg);
            }
            else {
                ++trg;
            }
        }
    }
    ofs.close();

    return (0);
}
