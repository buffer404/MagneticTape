#pragma once
#include <iostream>
#include <fstream>

#define CONFIG_PATH "config.txt"
#define TMP_DIR_PATH "tmp/"
using namespace std;

void init(int* n, int* m, int* delay_rd_wr, int* del_rewind, int* delay_inc_dec);