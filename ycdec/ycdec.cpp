// yokai05.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
// Visual Studio 2022でビルドしました。

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <thread>
#include <map>
#include <chrono>

#include "PassSearcher.h"
#include "SearchPass.h"


using namespace std;

int main(int argc, char* argv[])
{
	PassSearcher ps;

	ps.SearchScheduler();

	std::cout << "Finished." << std::endl;
	std::cerr << "Finished." << std::endl;
	(void)getchar();

	return 0;
}
