
#include <iostream>
#include <conio.h>
#include <vector>
#include <bit>
#include "SearchPass.h"

const unsigned char SearchPass::chrcode[] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0x2D,0,0,0,0,0,0,0,0,0,0,0,0x2B,0,0,
0x25,0x04,0x0C,0x14,0x1C,0x24,0x05,0x0D,0x15,0x1D,0,0,0,0,0,0,
0,0x00,0x08,0x10,0x18,0x20,0x28,0x30,0x01,0x09,0x11,0x19,0x21,0x29,0x31,0x02,
0x0A,0x12,0x1A,0x22,0x2A,0x32,0x03,0x0B,0x13,0x1B,0x23,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0x33,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0x35,0,0,0,0,0,
0,0,0,0,0,0x2C,0,0,0,0,0,0,0,0,0,0,
0,0x34,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
int SearchPass::kat31F7;
int SearchPass::kat31F8;
int SearchPass::kat31F9;
int SearchPass::kat31FA;
int SearchPass::kat31FB;

// コンストラクタ
SearchPass::SearchPass(int kF7, int kF8, int kF9, int kFA, int kFB)
{

	kat31F7 = kF7;
	kat31F8 = kF8;
	kat31F9 = kF9;
	kat31FA = kFA;
	kat31FB = kFB;

}

bool SearchPass::calcCheckDigit(
	unsigned char* str, unsigned char len,
	unsigned char cd14, unsigned char cd15
)
{
	bool result;
	std::vector<unsigned char> buffer;

	// 文字コード変換
	for (unsigned char idx = 0; idx < len; ++idx) {
		buffer.push_back(chrcode[str[idx]]);
	}

	result = false;
#if 0
	int A(1), X(0), /* Y(0), */ Z(0), C(0);
	int ror(0);
	int a31F4(0), a31F5(0), a31F6(len), a31F7(0), a31F8(0), a31F9(0), a31FA(0), a31FB(0);
	int stack0, stack1;

	A = 1;
	a31FA = A;

	for (unsigned char ch : buffer) {
//	for (int ch = 0; ch < buffer.size(); ++ch) {
//	do {//	D86B:
//		if (stackApos != 0) {
//			printf("stack error!\n");
//		}
		A = ch;

		//D8BD:
		//stackA[stackApos++] = A;
//		stack0 = A;		// 14,15を出すだけなら不使用
		for (int Y = 0; Y < 8; ++Y) {
			//		Y = 8;
			//		do {//	D8C0:

			//			if (A > 0xFF) {
			//				C = 1;
			//				A = A & 0xFF;
			//			}
			//			else {
			//				C = 0;
			//			}
			C = (A & 0x80) != 0;
//			A = (A << 1) & 0xFF;
//			stack1 = A; //	stackA[stackApos++] = A;
 			stack1 = (A << 1) & 0xFF;
			// 31F4と31F5を右1ビットローテート
			ror = a31F4 & 0x01;
			a31F4 = (a31F4 >> 1) | (C * 0x80);
			//			a31F4 = a31F4 >> 1;
			//			a31F4 = a31F4 | (C << 7); // C0000000
			C = ror;

			ror = a31F5 & 0x01;
//			a31F5 = a31F5 >> 1;
//			a31F5 = a31F5 | (C << 7); // C0000000
			a31F5 = (a31F5 >> 1) | (C << 7); // C0000000
			C = ror;
			//
						//			printf("ror %02X %02X\n", a31F4, a31F5);
			//
			//			A = 0;
			//			A = 0xFF + C;
			//			if (A > 0xFF) { A = 0; C = 1; }
			//			else C = 0;

				//		A = 0xFF + C;
				//		C = (A & 0x100) != 0;
				//		A &= 0xFF;
				//		A = A ^ 0xFF;

			A = ((0xFF + C) ^ 0xFF) & 0xFF;

//			stack2 = A; //	stackA[stackApos++] = A;
//			A = A & 0x84;
//			A = A ^ a31F4;
//			a31F4 = A;
//			a31F4 = (stack2 & 0x84) ^ a31F4;
			a31F4 = (A & 0x84) ^ a31F4;

			//		A = stack2; // A = stackA[--stackApos];
			//		A = A & 0x08;
			//		A = A ^ a31F5;
			//		a31F5 = A;
//			a31F5 = (stack2 & 0x08) ^ a31F5;
			a31F5 = (A & 0x08) ^ a31F5;

			A = stack1;	// A = stackA[--stackApos];
//			Y--;
#if 1	// 枝刈りするなら 1
//			stackApos = 0;
		}
//		} while (Y > 0);
//		if (Y > 0) goto D8C0;
#else
		} while (Y > 0);
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
		do {//		D880: // 31FBを生成
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
		} while (!Z);
//		if (!Z) goto D880; // ローテ終わるまでループ
//		printf("a31FB=%x ",a31FB);

		A = stackA[--stackApos];
#endif
		// 文字数分だけ演算をカウント
//		X++;
//	} while (a31F6 != X);
	}
	//	if (a31F6 != X) goto D86B;

	result = ((a31F4 == cd14) && (a31F5 == cd15));
#endif

//	printf("$31F4 = %02X, $31F5 = %02X\n", a31F4, a31F5);

	unsigned char	a(0), c(0);
	unsigned char	mem2[2] = { 0, 0 };
	unsigned char	mem5[5] = { 0,0,0,1,0 };

	auto ror = [&c](unsigned char v)
	{
		unsigned char wc = c;

		c = v & 0x01;
		return (unsigned char)((v >> 1) | (wc << 7));
	};

	auto adc = [&c](unsigned char lhs, unsigned char rhs)
	{
		unsigned short v;

		v = (unsigned short)lhs + (unsigned short)rhs + (unsigned short)c;
		c = (v > 0xFF) ? 1 : 0;

		return (v & 0xFF);
	};


	for (unsigned char chr : buffer) {
		a = chr;
		// calc checkdigit1
		for (int bit = 7; bit >= 0; --bit) {
			c = (a >> bit) & 1;
			mem2[0] = ror(mem2[0]);
			mem2[1] = ror(mem2[1]);

			if (c) {
				mem2[0] ^= 0x84;
				mem2[1] ^= 0x08;
			}
		}
		// calc checkdigit2
		c = (mem2[0] >= 0xE5) ? 1 : 0;
		mem5[0] = adc(a, mem5[0]);
		mem5[1] = adc(mem5[1], mem2[1]);
		// calc checkdigit3
		mem5[2] ^= a;
		// calc checkdigit4
		{
			unsigned char v = ror(mem5[3]);
			mem5[3] = adc(v, a);
		}
		// calc checkdigit5
		mem5[4] += (unsigned char )(c + std::popcount(a));
	}

	result = ((mem2[0] == cd14) && (mem2[1] == cd15));
	if (result ) {
//		fprintf(stderr, "chk %14s %02x %02x 0E %02x %02x %02x %02x %02x\n",
//			str, mem2[0], mem2[1], mem5[0], mem5[1], mem5[2], mem5[3], mem5[4]);
		return (true);
	}

	return (false);
}


bool SearchPass::checkPass(Word wd)
{
	bool result;
	std::vector<unsigned char> buffer;


	// 文字コード変換
	for (unsigned char idx = 0; idx < wd.length; ++idx) {
		buffer.push_back(chrcode[wd.str[idx]]);
	}

	result = false;
#if 0
	//	int a31DC[256];
	int A(1), X(0), Y(0), Z(0), C(0);
	int ror(0);
	int a31F4(0), a31F5(0), a31F6(wd.length), a31F7(0), a31F8(0), a31F9(0), a31FA(0), a31FB(0);

	int stack0, stack1;

	A = 1;
	a31FA = A;

	do {//	D86B:
		A = buffer[X];
//		printf("pop %02X\n", A);

	//D8BD:
		stack0 = A; //	stackA[stackApos++] = A;
		for (int Y = 0; Y < 8; ++Y) {
//		Y = 8;
//		do {//	D8C0:
//			A = A << 1;

//			if (A > 0xFF) {
//				C = 1;
//				A = A & 0xFF;
//			}
//			else {
//				C = 0;
//			}
			C = (A & 0x80) != 0;
//			A = (A << 1) & 0xFF;
//			stack1 = A; //	stackA[stackApos++] = A;
			stack1 = (A << 1) & 0xFF;
			// 31F4と31F5を右1ビットローテート
			ror = a31F4 & 0x01;
			a31F4 = (a31F4 >> 1) | (C * 0x80);
//			a31F4 = a31F4 >> 1;
//			a31F4 = a31F4 | (C << 7); // C0000000
			C = ror;

			ror = a31F5 & 0x01;
//			a31F5 = a31F5 >> 1;
//			a31F5 = a31F5 | (C << 7); // C0000000
			a31F5 = (a31F5 >> 1) | (C << 7); // C0000000
			C = ror;
//
			//			printf("ror %02X %02X\n", a31F4, a31F5);
//
//			A = 0;
//			A = 0xFF + C;
//			if (A > 0xFF) { A = 0; C = 1; }
//			else C = 0;

	//		A = 0xFF + C;
	//		C = (A & 0x100) != 0;
	//		A &= 0xFF;
	//		A = A ^ 0xFF;

			A = ((0xFF + C) ^ 0xFF) & 0xFF;

//			stack2 = A; //	stackA[stackApos++] = A;
//			A = A & 0x84;
//			A = A ^ a31F4;
//			a31F4 = A;
//			a31F4 = (stack2 & 0x84) ^ a31F4;
			a31F4 = (A & 0x84) ^ a31F4;

	//		A = stack2; // A = stackA[--stackApos];
	//		A = A & 0x08;
	//		A = A ^ a31F5;
	//		a31F5 = A;
//			a31F5 = (stack2 & 0x08) ^ a31F5;
			a31F5 = (A & 0x08) ^ a31F5;

			A = stack1;	// A = stackA[--stackApos];
//			Y--;
#if 0	// 枝刈りするなら 1
			stackApos = 0;
		} while (Y > 0);
		//		if (Y > 0) goto D8C0;
#else
//		} while (Y > 0);
 		}
//		A = stack0; // 	A = stackA[--stackApos]; // ここまでで31F4と31F5算出完了

		//D8A4: // 31F7と31F8を生成(Complete)
//		stack0 = A; //		stackA[stackApos++] = A;
//		stack1 = A; //stackA[stackApos++] = A;
		A = a31F4;
		if (A >= 0xE5) { C = 1; }
		else C = 0; //C5の値でキャリーを生成
//		A = stack0; //	A = stackA[--stackApos];
//		A = A + a31F7 + C;
		A = stack0 + a31F7 + C;

		C = (A > 0xFF);
//		A &= 0xFF;
	//	if (A > 0xFF) { // ADCのキャリー処理
	//		A = A & 0xFF;
	//		C = 1;
	//	}
	//	else C = 0;
//		a31F7 = A;
		a31F7 = A & 0xFF;
//		A = a31F8;
//		A = A + a31F5 + C;
		A = a31F8 + a31F5 + C;

		C = (A > 0xFF);
//		A &= 0xFF;

	//	if (A > 0xFF) { // ADCのキャリー処理
	//		A = A & 0xFF;
	//		C = 1;
	//	}
	//	else C = 0;
//		a31F8 = A;
		a31F8 = A & 0xFF;
	//	A = stack0; //	A = stackA[--stackApos];

		//D89B: // 31F9を生成(Complete)
//		stack0 = A; //	stackA[stackApos++] = A;
//		A = A ^ a31F9;
//		a31F9 = A ^ a31F9;
		a31F9 = stack0 ^ a31F9;
//		A = stack0; //A = stackA[--stackApos];

		//D88F: // 31FAを生成
	//	stack0 = A; //	stackA[stackApos++] = A;
		// 31FAをローテート
		ror = a31FA & 0x01;
//		a31FA = a31FA >> 1;
//		a31FA = a31FA | (C << 7); // $31F8のCがここで入る
		a31FA = (a31FA >> 1) | (C << 7); // $31F8のCがここで入る
		C = ror;
//		A = A + a31FA + C;
		A = stack0 + a31FA + C;

		C = (A > 0xFF);
//		A &= 0xFF;

	//	if (A > 0xFF) { // ADCのキャリー処理
	//		A = A & 0xFF;
	//		C = 1;
	//	}
	//	else C = 0;
//		a31FA = A;
		a31FA = A & 0xFF;
		if ((a31F7 != kat31F7)
			|| (a31F8 != kat31F8)
			|| (a31F9 != kat31F9)
			|| (a31FA != kat31FA)
			) {
//			delete[] buffer;
			return (false);
		}

		A = stack0; //A = stackA[--stackApos];

		//D87F:
//		stack0 = A; // 	stackA[stackApos++] = A;
		do {//		D880: // 31FBを生成
			// Aを左ローテート
	//		A = A << 1;
	//		if (A > 0xFF) { // ADCのキャリー処理
	//			A = A & 0xFF;
	//			C = 1;
	//		}
			C = ((A & 0x80) != 0x00);
//			A <<= 1;
//			A &= 0xFF;
			A = (A << 1) & 0xFF;

	//		if (A == 0) Z = 1; else Z = 0; // 演算結果がゼロの時Z=1;
			Z = (A == 0);

//			stack1 = A; //	stackA[stackApos++] = A; // スタックに値を保存
//			A = a31FB;
//			A = A + C;
//			A = a31FB + C;

//			C = (A > 0xFF);
//			A &= 0xFF;
	//		if (A > 0xFF) { // ADCのキャリー処理
	//			A = A & 0xFF;
	//			C = 1;
	//		}
	//		else C = 0;
//			a31FB = A;
			a31FB = (a31FB + C) & 0xFF;

//			A = stack1; //	A = stackA[--stackApos];
		} while (!Z);
		//		if (!Z) goto D880; // ローテ終わるまでループ
		//		printf("a31FB=%x ",a31FB);

//		A = stack0; // A = stackA[--stackApos];
	#endif
		// 文字数分だけ演算をカウント
		X++;
	} while (a31F6 != X);
	//	if (a31F6 != X) goto D86B;

#endif
	//	printf("$31F4 = %02X, $31F5 = %02X\n", a31F4, a31F5);

	unsigned char	a(0), c(0);
	unsigned char	mem2[2] = { 0, 0 };
	unsigned char	mem5[5] = { 0,0,0,1,0 };

	auto ror = [&c](unsigned char v)
	{
		unsigned char wc = c;

		c = v & 0x01;
		return (unsigned char)((v >> 1) | (wc << 7));
	};

	auto adc = [&c](unsigned char lhs, unsigned char rhs)
	{
		unsigned short v;

		v = (unsigned short)lhs + (unsigned short)rhs + (unsigned short)c;
		c = (v > 0xFF) ? 1 : 0;

		return (v & 0xFF);
	};

	for (unsigned char chr : buffer) {
		a = chr;
		// calc checkdigit1
		for (int bit = 7; bit >= 0; --bit) {
			c = (a >> bit) & 1;
			mem2[0] = ror(mem2[0]);
			mem2[1] = ror(mem2[1]);

			if (c) {
				mem2[0] ^= 0x84;
				mem2[1] ^= 0x08;
			}
		}
		// calc checkdigit2
		c = (mem2[0] >= 0xE5) ? 1 : 0;
		mem5[0] = adc(a, mem5[0]);
		mem5[1] = adc(mem5[1], mem2[1]);
		// calc checkdigit3
		mem5[2] ^= a;
		// calc checkdigit4
		{
			unsigned char v = ror(mem5[3]);
			mem5[3] = adc(v, a);
		}
		// calc checkdigit5
		mem5[4] += (unsigned char)(c + std::popcount(a));
	}

	// 合うことは判っているのでmem2の方は照合省略
	//result = ((a31F4 == cd14) && (a31F5 == cd15));
	result = (
			(mem5[0] == kat31F7)
		&&	(mem5[1] == kat31F8)
		&&	(mem5[2] == kat31F9)
		&&	(mem5[3] == kat31FA)
		&&	(mem5[4] == kat31FB)
		);
	if ((mem2[0] == 0x65) && (mem2[1] == 0x94)) {
		for (int idx = 0; idx < 14; ++idx) {
			fprintf(stderr, "0x%02X ", chrcode[wd.str[idx]]);
		}
		fprintf(stderr, "\n");

		fprintf(stderr, "chk %14s %02x %02x 0E %02x %02x %02x %02x %02x\n",
			wd.str, mem2[0], mem2[1], mem5[0], mem5[1], mem5[2], mem5[3], mem5[4]);
	}
	if (result) {
		return (true);
	}
	return (false);
}
