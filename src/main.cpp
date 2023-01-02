#include "../include/main.h"

int main(int argc, char** argv)
{
    int n, m, del_rd, del_wr, del_idx, del_inc;

    init(&n, &m, &del_rd, &del_wr, &del_idx, &del_inc);

    string input_data_path = argv[1];
    string output_data_path = argv[2];

    Tape inputTape(n, input_data_path, del_rd, del_wr, del_idx, del_inc);
    Tape outputTape(n, output_data_path, del_rd, del_wr, del_idx, del_inc);


    SortTape sortTape(n, m, &inputTape, &outputTape, del_rd, del_wr, del_idx, del_inc);

    sortTape.startSort();

    sortTape.printAllDelay();

}