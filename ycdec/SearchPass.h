#pragma once

#undef XOR_VAR_TABLE		// defineすると変数でテーブルをもつ
#undef XORMAP_DUMP
#include <map>
class SearchPass {
public:

	struct Word {
		unsigned char str[15];
		unsigned char length;
	public:
		Word(unsigned char* ary, unsigned char len) :
			length(len)
		{
			memcpy_s(str, 14, ary, 14);
			str[14] = '\0';
		}
	};

private:
	static int kat31F7, kat31F8, kat31F9, kat31FA, kat31FB;
#if defined(XOR_VAR_TABLE)
	static unsigned char lut_xor31F4[256];
	static unsigned char lut_xor31F5[256];
#endif  // XOR_VAR_TABLE


	static const unsigned char chrcode[];
public:
	SearchPass(int, int, int, int, int);		// コンストラクタ

	static void create_lut();
	static bool checkPass(Word);

};



