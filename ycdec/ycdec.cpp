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


#define MAX_WORD 65535

using namespace std;
#if 0
// 文字コード変換テーブル
static char ytoa[256];
void make_ytoa() {
	memset(ytoa, NULL, sizeof(ytoa));
	ytoa['A'] = 0x00; ytoa['B'] = 0x08; ytoa['C'] = 0x10; ytoa['D'] = 0x18; ytoa['E'] = 0x20; ytoa['F'] = 0x28;
	ytoa['G'] = 0x30; ytoa['H'] = 0x01; ytoa['I'] = 0x09; ytoa['J'] = 0x11; ytoa['K'] = 0x19; ytoa['L'] = 0x21;
	ytoa['M'] = 0x29; ytoa['N'] = 0x31; ytoa['O'] = 0x02; ytoa['P'] = 0x0A; ytoa['Q'] = 0x12; ytoa['R'] = 0x1A;
	ytoa['S'] = 0x22; ytoa['T'] = 0x2A; ytoa['U'] = 0x32; ytoa['V'] = 0x03; ytoa['W'] = 0x0B; ytoa['X'] = 0x13;
	ytoa['Y'] = 0x1B; ytoa['Z'] = 0x23; ytoa['-'] = 0x2B; ytoa['.'] = 0x33; ytoa['1'] = 0x04; ytoa['2'] = 0x0C;
	ytoa['3'] = 0x14; ytoa['4'] = 0x1C; ytoa['5'] = 0x24; ytoa['6'] = 0x05; ytoa['7'] = 0x0D; ytoa['8'] = 0x15;
	ytoa['9'] = 0x1D; ytoa['0'] = 0x25; ytoa['!'] = 0x2D; ytoa['n'] = 0x2C; ytoa['m'] = 0x34; ytoa['c'] = 0x35;
	ytoa['ﾅ'] = 0x2C; ytoa['ﾑ'] = 0x34; ytoa['ｺ'] = 0x35; // 念のためﾅﾑｺも処理
}
#endif
//static map<unsigned char, unsigned char> chrcode;
#if 0
void make_chrmap()
{
	chrcode.clear();
	chrcode['A'] = 0x00; chrcode['B'] = 0x08; chrcode['C'] = 0x10; chrcode['D'] = 0x18; chrcode['E'] = 0x20; chrcode['F'] = 0x28;
	chrcode['G'] = 0x30; chrcode['H'] = 0x01; chrcode['I'] = 0x09; chrcode['J'] = 0x11; chrcode['K'] = 0x19; chrcode['L'] = 0x21;
	chrcode['M'] = 0x29; chrcode['N'] = 0x31; chrcode['O'] = 0x02; chrcode['P'] = 0x0A; chrcode['Q'] = 0x12; chrcode['R'] = 0x1A;
	chrcode['S'] = 0x22; chrcode['T'] = 0x2A; chrcode['U'] = 0x32; chrcode['V'] = 0x03; chrcode['W'] = 0x0B; chrcode['X'] = 0x13;
	chrcode['Y'] = 0x1B; chrcode['Z'] = 0x23; chrcode['-'] = 0x2B; chrcode['.'] = 0x33; chrcode['1'] = 0x04; chrcode['2'] = 0x0C;
	chrcode['3'] = 0x14; chrcode['4'] = 0x1C; chrcode['5'] = 0x24; chrcode['6'] = 0x05; chrcode['7'] = 0x0D; chrcode['8'] = 0x15;
	chrcode['9'] = 0x1D; chrcode['0'] = 0x25; chrcode['!'] = 0x2D; chrcode['n'] = 0x2C; chrcode['m'] = 0x34; chrcode['c'] = 0x35;
	chrcode['ﾅ'] = 0x2C; chrcode['ﾑ'] = 0x34; chrcode['ｺ'] = 0x35; // 念のためﾅﾑｺも処理
}
#endif
// 単語用メモリ
static char wordptr[MAX_WORD + 2][16]; // 65536単語×16バイト = 1MBほど確保
static char wordlen[MAX_WORD + 2]; // 文字列の長さ(最大14文字を想定)を確保。
static int DEBUG = 0; // デバッグモードフラグ。辞書の1行目にDEBUGMODE=1で有効

int main(int argc, char* argv[])
{
#if 0
	FILE* fp; // 辞書オープン用


	char a31DC[256], chainstr[256];
	char temp = 0;
	unsigned long word_count = 0, cursor = 0, cursor2 = 0;
	unsigned long i = 0, j = 0;
	int stackApos = 0, stackXpos = 0, stackYpos = 0;
	static int stackA[256];
	int atk_count = 1;
	int atk31F4 = 0, atk31F5 = 0, atk31F7 = 0, atk31F8 = 0, atk31F9 = 0, atk31FA = 0, atk31FB = 0;

	int A = 0, X = 0, Y = 0, C = 0, Z = 0;
	int a31F6 = 0; // 文字列長さ
	int a31F4 = 0, a31F5 = 0, a31F7 = 0, a31F8 = 0, a31F9 = 0, a31FA = 0, a31FB = 0;
	int ror = 0;
	int loopmode = 0;

	if (argc < 9) {
		printf("yokai05 - Yokai Randam Attacker\n");
		printf("usage: yokai05.exe $31F4 $31F5 $31F6 $31F7 $31F8 $31F9 $31FA $31FB DictFile\n");
		return 0;
	}
	// 引数を各ターゲットに割り当て	
	atk31F4 = (int)strtoul(argv[1], NULL, 16);
	atk31F5 = (int)strtoul(argv[2], NULL, 16);
	atk_count = (int)strtol(argv[3], NULL, 16);
	a31F6 = atk_count;
	atk31F7 = (int)strtoul(argv[4], NULL, 16);
	atk31F8 = (int)strtoul(argv[5], NULL, 16);
	atk31F9 = (int)strtoul(argv[6], NULL, 16);
	atk31FA = (int)strtoul(argv[7], NULL, 16);
	atk31FB = (int)strtoul(argv[8], NULL, 16);

	if (fopen_s(&fp, argv[9], "rt") != 0) {
		printf("File %s not found.\n", argv[9]);
		_fcloseall();
		return -1;
	}

	// 変換テーブル生成。乱数シード初期化
	make_ytoa();
	srand((unsigned)time(NULL));

	// 辞書ロード
	memset(wordptr, NULL, sizeof(wordptr));
	memset(wordlen, NULL, sizeof(wordlen));

	for (i = 0; i < MAX_WORD; i++) {
		// 1行が16文字を超えることは絶対ありえない(解析パスが14文字以下)という前提
		if (fgets(wordptr[i], 16, fp) == NULL) break;
		wordlen[i] = (int)strlen(wordptr[i]);
		wordptr[i][wordlen[i] - 1] = '\0'; // 終端の改行コードを削る
		wordlen[i]--; // 削った分文字列長を調整
	}
	word_count = i; // 単語数をキープ。この回数だけアタックを試行する。
	wordptr[i][0] = '*'; wordptr[i][1] = '\0'; // 念のため配列終端に番兵セット

	printf("Random DICT Attack Start (ESC=break).\n");

	// 検索ループ位置はここ
LOOP:
	strcpy_s(chainstr, ""); // 文字列クリア
	while (1) {
		if (strlen(chainstr) == (unsigned)atk_count) break; // 生成成功
		// 単語を乱数サーチしてターゲット文字数以下なら連結
		cursor = rand() % word_count;
		if (strlen(chainstr) + strlen(wordptr[cursor]) <= (unsigned)atk_count) {
			strcat_s(chainstr, wordptr[cursor]);
		}
	}

	// 生成した文字列をトリガーにコピー
	a31F6 = (int)strlen(chainstr);

	// ここで文字コードをコンバートしておく
	for (j = 0; j < (unsigned long)a31F6; j++) {
		temp = ytoa[chainstr[j]];
		a31DC[j] = temp;
		if (DEBUG) {
			printf("%02X ", a31DC[j]);
		}
	}

	// スタート
	X = 0;
	a31F4 = 0;
	a31F5 = 0;
	a31F7 = 0;
	a31F8 = 0;
	a31F9 = 0;
	a31FB = 0;
	A = 1;
	a31FA = A;

D86B:
	A = a31DC[X];

	//D8BD:
	stackA[stackApos++] = A;
	Y = 8;
D8C0:
	A = A << 1;

	if (A > 0xFF) {
		C = 1;
		A = A & 0xFF;
	}
	else {
		C = 0;
	}
	stackA[stackApos++] = A;
	// 31F4と31F5を右1ビットローテート
	ror = a31F4 & 0x01;
	a31F4 = a31F4 >> 1;
	a31F4 = a31F4 | (C << 7); // C0000000
	C = ror;

	ror = a31F5 & 0x01;
	a31F5 = a31F5 >> 1;
	a31F5 = a31F5 | (C << 7); // C0000000
	C = ror;

	//printf("ror %02X %02X\n",a31F4,a31F5);

	A = 0;
	A = 0xFF + C;
	if (A > 0xFF) { A = 0; C = 1; }
	else C = 0;
	A = A ^ 0xFF;
	stackA[stackApos++] = A;
	A = A & 0x84;
	A = A ^ a31F4;
	a31F4 = A;
	A = stackA[--stackApos];
	A = A & 0x08;
	A = A ^ a31F5;
	a31F5 = A;
	A = stackA[--stackApos];
	Y--;
	if (Y > 0) goto D8C0;
	A = stackA[--stackApos]; // ここまでで31F4と31F5算出完了

//D8A4: // 31F7と31F8を生成(Complete)
	stackA[stackApos++] = A;
	stackA[stackApos++] = A;
	A = a31F4;
	if (A >= 0xE5) { C = 1; }
	else C = 0; //C5の値でキャリーを生成
	A = stackA[--stackApos];
	A = A + a31F7 + C;
	if (A > 0xFF) { // ADCのキャリー処理
		A = A & 0xFF;
		C = 1;
	}
	else C = 0;
	a31F7 = A;
	A = a31F8;
	A = A + a31F5 + C;
	if (A > 0xFF) { // ADCのキャリー処理
		A = A & 0xFF;
		C = 1;
	}
	else C = 0;
	a31F8 = A;
	A = stackA[--stackApos];

	//D89B: // 31F9を生成(Complete)
	stackA[stackApos++] = A;
	A = A ^ a31F9;
	a31F9 = A;
	A = stackA[--stackApos];

	//D88F: // 31FAを生成
	stackA[stackApos++] = A;
	// 31FAをローテート
	ror = a31FA & 0x01;
	a31FA = a31FA >> 1;
	a31FA = a31FA | (C << 7); // $31F8のCがここで入る
	C = ror;
	A = A + a31FA + C;
	if (A > 0xFF) { // ADCのキャリー処理
		A = A & 0xFF;
		C = 1;
	}
	else C = 0;
	a31FA = A;

	A = stackA[--stackApos];

	//D87F:
	stackA[stackApos++] = A;
D880: // 31FBを生成
	// Aを左ローテート
	A = A << 1;
	if (A > 0xFF) { // ADCのキャリー処理
		A = A & 0xFF;
		C = 1;
	}
	if (A == 0) Z = 1; else Z = 0; // 演算結果がゼロの時Z=1;

	stackA[stackApos++] = A; // スタックに値を保存
	A = a31FB;
	A = A + C;
	if (A > 0xFF) { // ADCのキャリー処理
		A = A & 0xFF;
		C = 1;
	}
	else C = 0;
	a31FB = A;

	A = stackA[--stackApos];
	if (!Z) goto D880; // ローテ終わるまでループ
	//printf("a31FB=%x ",a31FB);

	A = stackA[--stackApos];

	// 文字数分だけ演算をカウント
	X++;
	if (a31F6 != X) goto D86B;

	if (DEBUG) printf("%s %02X %02X %02X ", chainstr, a31F4, a31F5, a31F8);

	// 検算後に比較
	if (a31F4 == atk31F4 && a31F5 == atk31F5) {
		if (a31F7 == atk31F7 && a31F8 == atk31F8 && a31F9 == atk31F9 && a31FA == atk31FA && a31FB == atk31FB) {
			printf("Hit! : %s\n", chainstr);
		}
	}
	else if (DEBUG) printf("\n");

	// ESCキー判定。65535回に1度しかチェックしない
	if (_kbhit() && _getch() == 27) {
		printf("break.\n");
		return 0;
	}


	goto LOOP; // ループ

#endif
//	unsigned char dict[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!.-nmcﾅﾑｺ";
	PassSearcher ps;
//	SearchPass* sp = new SearchPass(0xAC, 0xE9, 0x07, 0x33, 0x25);

//	cout << ps->chrdic.size() << endl;
//	std::chrono::system_clock::time_point  start, end;

//	unsigned char passcandidate[14 + 1] = "AAAAAAAAAAAAAA";
//	unsigned char passcol[14] = { 0 };

//	bool result;
//	cout << "check:" << passcandidate << endl;

//	for (int idx = 0; idx < 14; ++idx) {
//		passcandidate[idx] = 'A' + (idx / 2);
//
//	}

//	start = std::chrono::system_clock::now(); // 計測開始時間
//	for (unsigned long count = 0; count < 100000; ++count) {
//		result = sp->calcCheckDigit(passcandidate, 14, 0x65, 0x94);
//	}
//	end = std::chrono::system_clock::now();  // 計測終了時間
//	double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//	printf("elapsed %fms\n", elapsed);
//	cout << "hit?" <<  result << endl;
#if 0
	while (1) {
		bool carry;

		// インデックスを文字列に変換
		for (int idx = 0; idx < 14; ++idx) {
			passcandidate[idx] = dict[passcol[idx]];
//			printf("%02X ", passcandidate[idx]);
		}
//		printf("\n");
		result = sp->calcCheckDigit(passcandidate, 14, 0x65, 0x94);

		if (result) {
			cout << "chk " << passcandidate << endl;
			cerr << "chk " << passcandidate << endl;
			SearchPass::Word cd(passcandidate, 14);
			thread	th([cd] {
				if (SearchPass::checkPass(cd) == true) {
					cout << "hit! " << cd.str << endl;
					cerr << "hit! " << cd.str << endl;
				}
			});
			th.detach();
		}
		carry = true;
		for (int col = 0; col < 14; ++col) {
			passcol[col] += carry ? 1 : 0;
			if (passcol[col] < ps->chrdic.size()) {
				carry = false;
			}
			else {
				passcol[col] = 0;
				carry = true;
			}
		}
	}


	delete ps;
	delete sp;
#endif

	ps.SearchScheduler();
	
//	delete ps;

	std::cout << "Finished." << std::endl;
	std::cerr << "Finished." << std::endl;
	(void)getchar();

	return 0;
}
