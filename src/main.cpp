#include "../include/main.h"

int main(int argc, char** argv)
{
    int n, m, del_rd_wr, del_rewind, del_inc_dec;

    init(&n, &m, &del_rd_wr, &del_rewind, &del_inc_dec);

    string input_data_path = argv[1];
    string output_data_path = argv[2];

    Tape inputTape(n, input_data_path, del_rd_wr, del_rewind, del_inc_dec);
    Tape outputTape(n, output_data_path, del_rd_wr, del_rewind, del_inc_dec);


    SortTape sortTape(n, m, &inputTape, &outputTape, del_rd_wr, del_rewind, del_inc_dec);

    sortTape.startSort();

    sortTape.printAllDelay();

}