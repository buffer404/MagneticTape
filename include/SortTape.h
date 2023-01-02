#pragma once
#include <vector>
#include "Tape.h"

#define MAX_INT 2147483647

using namespace std;

class SortTape
{
public:
    SortTape(int number_count, int RAM_size, Tape* inputTape, Tape* outputTape, int del_rd_wr, int del_rewind, int del_inc_dec);
    ~SortTape();
    void startSort();
    void printAllDelay();
private:
    int number_count, RAM_size, additional_tape_count;
    Tape* input_tape;
    Tape* output_tape;
    vector <Tape*> additional_tape;
    vector <int> RAM;
    void writeAdditionalData();
    void descRAMSort();
    void writeOutputTapeData();
    void checkMin(int tape_idx, int RAM_idx, vector<int>* vector_idx);
};

SortTape::SortTape(int number_count, int RAM_size, Tape* inputTape, Tape* outputTape, int del_rd_wr, int del_rewind, int del_inc_dec)
{
    this->number_count = number_count;
    this->RAM_size = RAM_size;
    RAM.reserve(RAM_size);
    this->input_tape = inputTape;
    this->output_tape = outputTape;
    this->additional_tape_count = (number_count - 1) / RAM_size + 1;

    for (int i = 0; i < additional_tape_count; i++){
        Tape* tape = new Tape(RAM_size, TMP_DIR_PATH + to_string(i), del_rd_wr, del_rewind, del_inc_dec);
        additional_tape.push_back(tape);
    }
}

void SortTape::startSort() {

    writeAdditionalData();

    writeOutputTapeData();

}

// «апись в дополнительные ленты отсортированные данные
void SortTape::writeAdditionalData() {
    for (Tape* tape : additional_tape) {
        // —читываем в RAM
        int k = 0;

        for (int i = 0; i < RAM_size; i++){
            if (input_tape->getCurIndex() < number_count - 1) {
                RAM.push_back(input_tape->getCurNum());
                input_tape->incCurIndex();
            }
            else if (input_tape->getCurIndex() == number_count - 1 && k == 0) {
                RAM.push_back(input_tape->getCurNum());
                tape->decCurIndex();
                k = 1;
            }
        }

        //for (int i : RAM) {
        //    cout << i;
        //}

        descRAMSort();

        for (int i = 0; i < RAM.size(); i++){
            tape->writeNum(RAM[i]);
            tape->incCurIndex();
        }

        RAM.clear();

    }

}

// —ортировка данных в RAM по убыванию (—ортировка выбором)
void SortTape::descRAMSort() {
    for (int startIndex = 0; startIndex < RAM.size()-1; startIndex++){
        int smallestIndex{ startIndex };

        for (int currentIndex{ startIndex + 1 }; currentIndex < RAM.size(); ++currentIndex){
            // ≈сли мы нашли элемент, который меньше нашего ранее найденного наименьшего
            if (RAM[currentIndex] > RAM[smallestIndex])
                // тогда отслеживаем его
                smallestIndex = currentIndex;
        }

        swap(RAM[startIndex], RAM[smallestIndex]);

    }
}

void SortTape::writeOutputTapeData() {

    for (int i = 0; i < RAM_size; i++) {
        RAM.push_back(MAX_INT);
    }

    for (int i = 0; i < number_count; i++){

        vector<int> index(RAM.size());

        for (int tape_idx = 0; tape_idx < additional_tape_count; tape_idx++) {
            checkMin(tape_idx, RAM.size()-1, &index);
        }

        for (int i = 0; i < RAM.size(); i++) {
            if (RAM[i] != MAX_INT) {
                output_tape->writeNum(RAM[i]);
                output_tape->incCurIndex();


                RAM[i] = MAX_INT;
                additional_tape[index[i]]->decCurIndex();
            }
        }
    }
}

void SortTape::checkMin(int tape_idx, int RAM_idx, vector<int>* vector_idx) {

    if (additional_tape[tape_idx]->getCurIndex() == -1)
        return;

    if (RAM[RAM_idx] >= additional_tape[tape_idx]->getCurNum()) {
        int cur_min_idx = RAM_idx;
        for (int i = cur_min_idx-1; i >= 0; i--) {
            if (RAM[i] < additional_tape[tape_idx]->getCurNum()){
                break;
            }
            cur_min_idx--;
        }

        RAM.insert(RAM.begin() + cur_min_idx, additional_tape[tape_idx]->getCurNum());
        RAM.pop_back();

        (*vector_idx).insert((*vector_idx).begin() + cur_min_idx, tape_idx);
        (*vector_idx).pop_back();

        additional_tape[tape_idx]->decCurIndex();
        checkMin(tape_idx, RAM_idx, vector_idx);
        additional_tape[tape_idx]->incCurIndex();
    }
}

void SortTape::printAllDelay() {
    int total_delay = 0;

    input_tape->printDelay();
    total_delay += input_tape->getTotalDelay();

    output_tape->printDelay();
    total_delay += output_tape->getTotalDelay();

    for (Tape* tape : additional_tape) {
        tape->printDelay();
        total_delay += tape->getTotalDelay();
    }
    cout << "TOTAL DELAY: " << total_delay << endl;
}

SortTape::~SortTape() {
    for (Tape* tape : additional_tape) {
        tape->clearFile();
    }
}