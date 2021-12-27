#pragma once
#include "SearchPass.h"
#include <thread>
#include <iostream>
#include <chrono>
#include <string>

class CheckPassRange
{
#define COLUMNS	(14)
	//	int colmuns;
	SearchPass sp;
	unsigned char candidate[COLUMNS + 1];
	static std::string dict;
	static size_t dictsize;
public:
	unsigned char counters[COLUMNS + 1];
	int		countstart_col;

	unsigned char chkcol;	// �I�����茅

	CheckPassRange()
	:	sp(SearchPass(0xAC, 0xE9, 0x07, 0x33, 0x25)), countstart_col(0)
	{
		memset(counters, 0x00, COLUMNS);
		memset(candidate, 0x00, COLUMNS + 1);
		chkcol = 0;
	};
	~CheckPassRange() {
	}
	void setDict(std::string dictbase = "") {
		dict = dictbase;
	};
	void setStartCol(int c) { countstart_col = c; };

	void operator() ()
	{
		{
			const size_t	dictlen = dict.size();

			const int refresh_col_n = 4;
			unsigned char	chkkey;
			unsigned char	refresh_col;		// �i���\���p�̔��茅

			// �I������p���l��ޔ�
			chkkey = counters[chkcol];
			refresh_col = counters[refresh_col_n];

			while (counters[chkcol] == chkkey) {

				if (refresh_col != counters[refresh_col_n]) {
					std::cout << "chk " << candidate << std::endl;
					std::cerr << "chk " << candidate << std::endl;
					refresh_col = counters[refresh_col_n];
				}
				for (int idx = 0; idx < COLUMNS; ++idx) {
					candidate[idx] = dict[counters[idx]];
				}

				// �ŏ��̐����̓X���b�h���N���������[�v�ň�C�Ƀ`�F�b�N
				for (size_t col2 = 0; col2 < dictlen; ++col2) {
					counters[countstart_col + 2] = col2;
					candidate[countstart_col + 2] = dict[counters[countstart_col + 2]];

					for (size_t col1 = 0; col1 < dictlen; ++col1) {
						counters[countstart_col + 1] = col1;
						candidate[countstart_col + 1] = dict[counters[countstart_col + 1]];

						for (size_t col0 = 0; col0 < dictlen; ++col0) {
							counters[countstart_col + 0] = col0;
							candidate[countstart_col + 0] = dict[counters[countstart_col + 0]];

							SearchPass::Word cd(candidate, COLUMNS);
							if (SearchPass::checkPass(cd)) {
								std::cout << "#hit! " << cd.str << std::endl;
								std::cerr << "#hit! " << cd.str << std::endl;
								std::this_thread::sleep_for(std::chrono::milliseconds(1));
							}
						}
					}
				}

				// �I�������ɍ��v�����Ԃ𔻒肵����T���I��
				bool carry = true;
				for (int col = (countstart_col + 3); col < (COLUMNS - 1); ++col) {
					counters[col] += carry ? 1 : 0;
					carry = (counters[col] == dictlen);
					counters[col] = carry ? 0 : counters[col];
				}
			}
		}
	};
};

