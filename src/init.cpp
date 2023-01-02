#include "../include/init.h"

void init(int* n, int* m, int* delay_read, int* delay_write, int* delay_index, int* delay_inc) {
  
    ifstream fin(CONFIG_PATH);
    
    fin >> *n;
    fin >> *m;
    fin >> *delay_read;
    fin >> *delay_write;
    fin >> *delay_index;
    fin >> *delay_inc;

}