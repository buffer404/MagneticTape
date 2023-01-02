#pragma once
#include <string>
#include <vector>

using namespace std;

class Tape
{
public:
	Tape(int size, string input_data_path, int del_rd_wr, int del_rewind, int del_inc_dec);

	void writeNum(int num);

	int getCurNum();

	void setCurIndex(int idx);

	void incCurIndex();
	void decCurIndex();

	int getCurIndex();

	int getTotalDelay();
	void printDelay();

	void clearFile();

private:
	int size = 0, cur_index = 0, del_inc_dec = 0, del_rd_wr = 0, del_rewind = 0, del_total = 0;
	string storage_path;
};

Tape::Tape(int size, string input_data_path, int del_rd_wr, int del_rewind, int del_inc_dec)
{
	this->size = size;
	this->storage_path = input_data_path;
	this->del_rd_wr = del_rd_wr;
	this->del_rewind = del_rewind;
	this->del_inc_dec = del_inc_dec;
}

void Tape::writeNum(int num) {
	del_total += del_rd_wr;
	ofstream fout(storage_path, ios_base::app);
	fout << num << endl;
}

int Tape::getCurNum() {
	del_total += del_rd_wr;
	int cur_num = 0;
	ifstream fin(storage_path);
	for (size_t i = 0; i < size; i++){
		fin >> cur_num;
		if (i == cur_index)
			break;
	}
	return cur_num;
}

void Tape::setCurIndex(int idx) {
	del_total += del_rewind;
	this->cur_index = idx;
}

void Tape::incCurIndex() {
	del_total += del_inc_dec;
	if (cur_index + 1 != size)
		cur_index++;
}

void Tape::decCurIndex() {
	del_total += del_inc_dec;
	cur_index--;
}

int Tape::getCurIndex() {
	return cur_index;
}

int Tape::getTotalDelay() {
	return del_total;
}

void Tape::printDelay() {
	cout << "Tape: " << storage_path;
	cout << " Total delay for tape: " << del_total << endl;
}


void Tape::clearFile() {
	remove(storage_path.c_str());
}
