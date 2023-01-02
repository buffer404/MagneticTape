#pragma once
#include <string>
#include <vector>

using namespace std;

class Tape
{
public:
	Tape(int size, string input_data_path, int del_rd, int del_wr, int del_idx, int del_inc);
	void debug();
	void writeNum(int num);
	void setCurIndex(int idx);
	int getCurIndex();
	void incCurIndex();
	void decCurIndex();
	int getCurNum();
	void clearFile();
	void printDelay();
	int getTotalDelay();

private:
	int size = 0, cur_index = 0, del_inc = 0, del_rd = 0, del_wr = 0, del_idx = 0, del_total = 0;
	string storage_path;
	void writeToFile(int num);

};

Tape::Tape(int size, string input_data_path, int del_rd, int del_wr, int del_idx, int del_inc)
{
	this->size = size;
	this->storage_path = input_data_path;
	this->del_rd = del_rd;
	this->del_wr = del_wr;
	this->del_idx = del_idx;
	this->del_inc = del_inc;
}

void Tape::debug() {
	cout << "Storage path: " << storage_path << endl;
	cout << "Cur index" << getCurIndex() << endl;
}

void Tape::writeNum(int num) {
	writeToFile(num);
}

void Tape::writeToFile(int num) {
	del_total += del_wr;
	ofstream fout(storage_path, ios_base::app);
	fout << num << endl;
}

int Tape::getCurIndex() {
	return cur_index;
}

void Tape::incCurIndex() {
	del_total += del_inc;
	if (cur_index + 1 != size)
		cur_index++;
}

void Tape::decCurIndex() {
	del_total += del_inc;
	cur_index--;
}

int Tape::getCurNum() {
	del_total += del_rd;
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
	del_total += del_idx;
	this->cur_index = idx;
}

void Tape::clearFile() {
	remove(storage_path.c_str());
}

int Tape::getTotalDelay() {
	return del_total;
}

void Tape::printDelay() {
	cout << "Tape: " << storage_path;
	cout << " Total delay for tape: " << del_total << endl;
}
