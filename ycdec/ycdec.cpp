// yokai05.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
// Visual Studio 2022でビルドしました。

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <string>

#include "PassSearcher.h"
#include "SearchPass.h"


using namespace std;

//-Csearchsettings.txt -Sprogress.txt 
int main(int argc, char* argv[])
{
	if (argc != 1) {
		cerr << "usage: ycdec.exe  with dict.txt on same folder." << endl;
		return 0;
	}

	string fnDict = "dict.txt";

	ifstream ifs(fnDict);
	if (ifs.fail()) {
		cout << "Fail open file " << fnDict << "." << endl;
		return 0;
	}
	string dict;
	getline(ifs, dict);


	PassSearcher ps(dict.c_str());

#if defined(PRUNING)
	cout << "Pruning by $31F4, $31F5, $31F9" << endl;
#else
	cout << "Full search" << endl;
#endif

	ps.SearchScheduler();

	cout << "Finished." << endl;
	(void)getchar();

	return 0;
}
