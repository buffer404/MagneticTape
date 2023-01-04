#pragma once
#include "../include/main.h"
#include "cassert"

using namespace std;

void testInit() {
    int n, m, del_rd_wr, del_rewind, del_inc_dec;

    readConfig(&n, &m, &del_rd_wr, &del_rewind, &del_inc_dec);

    assert(n == 17);
    assert(m == 3);
    assert(del_rd_wr == 1);
    assert(del_rewind == 10);
    assert(del_inc_dec == 1);

    cout << "Test Init OK!" << endl;
}

void testTape() {
    int n = 18, del_rd_wr = 1, del_rewind = 2, del_inc_dec = 3;

    Tape inputTape(n, "testData/input1.txt", del_rd_wr, del_rewind, del_inc_dec);
    Tape outputTape(n, "testData/output1.txt", del_rd_wr, del_rewind, del_inc_dec);

    // test getCurIndex
    assert(inputTape.getCurIndex() == 0);

    // test getCurNum
    assert(inputTape.getCurNum() == 6);

    // test inc/dec index
    inputTape.incCurIndex();
    assert(inputTape.getCurIndex() == 1);
    inputTape.decCurIndex();
    assert(inputTape.getCurIndex() == 0);

    // test setCurIndex
    inputTape.setCurIndex(5);
    assert(inputTape.getCurIndex() == 5);

    // test writeNum
    outputTape.writeNum(-32);
    assert(outputTape.getCurNum() == -32);
	
    // test Delay
    assert(inputTape.getTotalDelay() == 9);
	assert(outputTape.getTotalDelay() == 2);

    ofstream ofs;
    ofs.open("testData/output1.txt", ofstream::out | ofstream::trunc);
    ofs.close();
    cout << "Test Tape OK!" << endl;

}

void testSort(int n, int m, int del_rd_wr, int del_rewind, int del_inc_dec, string input_path, string output_path, int* result) {
    Tape inputTape(n, input_path, del_rd_wr, del_rewind, del_inc_dec);
    Tape outputTape(n, output_path, del_rd_wr, del_rewind, del_inc_dec);

    SortTape sortTape1(n, m, &inputTape, &outputTape, del_rd_wr, del_rewind, del_inc_dec);
    sortTape1.startSort();

    int cur_num = 0;
    ifstream fin("testData/output1.txt");
    for (size_t i = 0; i < n - 1; i++)
    {
        fin >> cur_num;
        assert(cur_num == result[i]);
    }
    ofstream ofs;
    ofs.open(output_path, ofstream::out | ofstream::trunc);
    ofs.close();
}

void testSortTape() {

    // Standart test
    int result1[18] = { -4345, -543, -1, -1, 0, 0, 0, 0, 1, 3, 6, 7, 7, 67, 234, 345, 456, 3245 };
    testSort(18, 4, 1, 2, 3, "testData/input1.txt", "testData/output1.txt", result1);

    // Standart test where ram size = 1
    testSort(18, 1, 1, 2, 3, "testData/input1.txt", "testData/output1.txt", result1);

    // Standart test where ram size = count of num
    testSort(18, 18, 1, 2, 3, "testData/input1.txt", "testData/output1.txt", result1);

    // Standart test where ram size > count of num
    testSort(18, 19, 1, 2, 3, "testData/input1.txt", "testData/output1.txt", result1);


    // One number
    int result2[1] = {777};
    testSort(1, 1, 1, 2, 3, "testData/input2.txt", "testData/output2.txt", result2);
	
	cout << "Test Sort OK!" << endl;
}

int main()
{
    testInit();
    testTape();
    testSortTape();
    return 0;
}