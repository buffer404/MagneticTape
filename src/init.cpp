#include "../include/init.h"

void init(int* n, int* m, int* delay_rd_wr,  int* del_rewind, int* delay_inc_dec) {
  
    ifstream fin(CONFIG_PATH);
    
    fin >> *n;
    fin >> *m;
    fin >> *delay_rd_wr;
    fin >> *del_rewind;
    fin >> *delay_inc_dec;

}