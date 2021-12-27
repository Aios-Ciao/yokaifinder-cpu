#include <thread>
#include <list>
#include <vector>
#include "PassSearcher.h"
#include "SearchPass.h"
#include "CheckPassRange.h"

using namespace std;

PassSearcher::PassSearcher(
	const char *chartable,
	unsigned char atk31F4,	/*�`�F�b�N�f�B�W�b�gA */
	unsigned char atk31F5,	/*�`�F�b�N�f�B�W�b�gA */
	unsigned char atk31F6,	/* ���� */
	unsigned char atk31F7,	/*�`�F�b�N�f�B�W�b�gB */
	unsigned char atk31F8,	/*�`�F�b�N�f�B�W�b�gB */
	unsigned char atk31F9,	/*�`�F�b�N�f�B�W�b�gB */
	unsigned char atk31FA,	/*�`�F�b�N�f�B�W�b�gB */
	unsigned char atk31FB	/*�`�F�b�N�f�B�W�b�gB */
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
	// �g�p���Ă���PC���Ή�����X���b�h���@12�Ƃ�
	nthread = thread::hardware_concurrency();

	chrdic = std::string(chartable);	// �g�p�\�ȕ��������X�g�ɕϊ�


}

#define THREADS_NUM	(chrdic.size())
//#define THREADS_NUM	(1)
void PassSearcher::SearchScheduler()
{
	vector<CheckPassRange>	cpr;
	vector<thread>	threads;

	cout << "Dict:" << chrdic << endl;
	cerr << "Dict:" << chrdic << endl;

	for (unsigned int thid = 0; thid < THREADS_NUM; ++thid) {
		cpr.push_back(CheckPassRange());
		cpr[thid].setDict(chrdic);
		// �����ł̐������Ɋe��������Ԃ�^����
//		cpr[thid].counters[0] = 'I' - 'A';
//		cpr[thid].counters[1] = 'S' - 'A';
//		cpr[thid].counters[2] = 'S' - 'A';
//		cpr[thid].counters[3] = 'Y' - 'A';
//		cpr[thid].counters[4] = 'Z' - 'A';
//		cpr[thid].counters[5] = 'N' - 'A';
//		cpr[thid].counters[6] = 'M' - 'A';
//		cpr[thid].counters[7] = 35;// '9'
//		cpr[thid].counters[8] = 'N' - 'A';
//		cpr[thid].counters[9] = 'R' - 'A';
//		cpr[thid].counters[10] = 'Z' - 'A';
//		cpr[thid].counters[11] = 'Z' - 'A';
//		cpr[thid].counters[12] = 'D' - 'A';

		cpr[thid].counters[13] = thid;
		cpr[thid].chkcol = 13;

		threads.push_back(thread(cpr[thid]));
	}

	for (thread& th : threads) {
		th.join();
	}
}


