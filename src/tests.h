//
// Created by ShadowCat650 on 3/20/23.
//

#ifndef VELOCITYCHESS_TESTS_H
#define VELOCITYCHESS_TESTS_H

#include "board.h"
#include "search.h"
#include <iomanip>

void perft_test(int depth, int perf=0);

int test_position(int depth, string position, string message="");

void basic_speed_test(int depth);

float average_numbers(vector<int> numbers);


#endif //VELOCITYCHESS_TESTS_H
