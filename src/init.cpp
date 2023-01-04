#include "../include/init.h"

void readConfig(int* n, int* m, int* delay_rd_wr,  int* del_rewind, int* delay_inc_dec) {

    ifstream fin(CONFIG_PATH);

    if (!fin) {
        cout << "The file did't open";
        exit(EXIT_FAILURE);
    }

    fin >> *n;
    fin >> *m;
    fin >> *delay_rd_wr;
    fin >> *del_rewind;
    fin >> *delay_inc_dec;

}

void readArgv(string* input, string* output, int argc, char** argv) {
    if (argc != 3) {
        cout << "Incorrect number of input arguments\n";
        exit(EXIT_FAILURE);
    }
    *input = argv[1];
    *output = argv[2];
}