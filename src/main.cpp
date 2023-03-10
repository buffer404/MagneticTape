#include "../include/main.h"

int main(int argc, char** argv)
{
    int n, m, del_rd_wr, del_rewind, del_inc_dec;

    readConfig(&n, &m, &del_rd_wr, &del_rewind, &del_inc_dec);

    string input_data_path, output_data_path;
    readArgv(&input_data_path, &output_data_path, argc, argv);

    Tape inputTape(n, input_data_path, del_rd_wr, del_rewind, del_inc_dec);
    Tape outputTape(n, output_data_path, del_rd_wr, del_rewind, del_inc_dec);


    SortTape sortTape(n, m, &inputTape, &outputTape, del_rd_wr, del_rewind, del_inc_dec);

    sortTape.startSort();

    sortTape.printAllDelay();

}