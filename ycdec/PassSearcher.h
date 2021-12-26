#pragma once
#include <thread>
#include <string>
class PassSearcher
{
	int at31F4, at31F5, at31F6, at31F7, at31F8, at31F9, at31FA, at31FB;
	int nthread;
public:

	std::string chrdic;
public:
	// 65 94 0E AC E9 07 33 25
	// chartable	ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!.-ﾅﾑｺ
	PassSearcher(
//		const char* chartable = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!.-nmcﾅﾑｺ",
//		const char* chartable = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.-",
		const char* chartable = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
		//		const char* chartable = "0123456789!.-",
		//		const char* chartable = "ABCDEFGHIJKMNOPRSTUWXYZ",
		unsigned char atk31F4 = 0x65,		// チェックディジット
		unsigned char atk31F5 = 0x94,
		unsigned char atk31F6 = 0x0E,		// 桁数
		unsigned char atk31F7 = 0xAC,
		unsigned char atk31F8 = 0xE9,
		unsigned char atk31F9 = 0x07,
		unsigned char atk31FA = 0x33,
		unsigned char atk31FB = 0x25
	);


	void SearchScheduler();	// スレッド生成
	void ThRangeSearch();		// 検索スレッド

};



