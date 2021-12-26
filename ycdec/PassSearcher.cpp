#include <thread>
#include <list>
#include <vector>
#include "PassSearcher.h"
#include "SearchPass.h"
#include "CheckPassRange.h"

using namespace std;

PassSearcher::PassSearcher(
	const char *chartable,
	unsigned char atk31F4,	/*チェックディジットA */
	unsigned char atk31F5,	/*チェックディジットA */
	unsigned char atk31F6,	/* 桁数 */
	unsigned char atk31F7,	/*チェックディジットB */
	unsigned char atk31F8,	/*チェックディジットB */
	unsigned char atk31F9,	/*チェックディジットB */
	unsigned char atk31FA,	/*チェックディジットB */
	unsigned char atk31FB	/*チェックディジットB */
) :
	at31F4(atk31F4),
	at31F5(atk31F5),
	at31F6(atk31F6),
	at31F7(atk31F7),
	at31F8(atk31F8),
	at31F9(atk31F9),
	at31FA(atk31FA),
	at31FB(atk31FB)
{
	// 使用しているPCが対応するスレッド数　12とか
	nthread = thread::hardware_concurrency();

	// 使用可能な文字をリストに変換
	chrdic = std::string(chartable);

}

#define THREADS_NUM	(chrdic.size())
//#define THREADS_NUM	(1)
void PassSearcher::SearchScheduler()
{
	vector<CheckPassRange>	cpr(THREADS_NUM);
	vector<thread>	threads;
	
	for (unsigned int thid = 0; thid < THREADS_NUM; ++thid) {
		cpr[thid].setDict(chrdic);
//		cpr[thid].counters[0] = 'O' - 'A';	// O
//		cpr[thid].counters[1] = 'Y' - 'A';	// Y
//		cpr[thid].counters[2] = 'A' - 'A';	// A
//		cpr[thid].counters[3] = 'S' - 'A';	// S
//		cpr[thid].counters[4] = 'U' - 'A';	// U
//		cpr[thid].counters[5] = 'M' - 'A';	// M
//		cpr[thid].counters[6] = 'I' - 'A';	// I
//
//		cpr[thid].counters[12] = 'E' - 'A';	// E	までみた
//		cpr[thid].counters[13] = thid;
//		cpr[thid].chkcol = 13;

//		cpr[thid].counters[4] = thid;
//		cpr[thid].chkcol = 4;

		cpr[thid].counters[13] = thid;
		cpr[thid].chkcol = 13;
//		cpr[thid].setStartCol(7);
		threads.push_back(thread(cpr[thid]));
	}

	for (thread& th : threads) {
		th.join();
	}
}

void PassSearcher::ThRangeSearch()
{


}


