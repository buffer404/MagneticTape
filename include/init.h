#pragma once
#include <iostream>
#include <fstream>

#define CONFIG_PATH "config.txt"
#define TMP_DIR_PATH "tmp/"
using namespace std;

void init(int* n, int* m, int* delay_read, int* delay_write, int* delay_index, int* delay_inc);