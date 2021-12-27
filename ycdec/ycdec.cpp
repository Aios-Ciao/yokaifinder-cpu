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
		std::cerr << "usage: ycdec.exe  with dict.txt on same folder." << endl;
		return 0;
	}

	string fnDict = "dict.txt";

	ifstream ifs(fnDict);
	if (ifs.fail()) {
		cerr << "Fail open file " << fnDict << "." << endl;
		return 0;
	}
	string dict;
	getline(ifs, dict);


	PassSearcher ps(dict.c_str());

#if defined(PRUNING)
	std::cerr << "Pruning by $31F4, $31F5, $31F9" << std::endl;
#else
	std::cerr << "Full search" << std::endl;
#endif

	ps.SearchScheduler();

	std::cout << "Finished." << std::endl;
	(void)getchar();

	return 0;
}
