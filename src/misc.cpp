//
// Created by ShadowCat650 on 3/5/23.
//

#include "misc.h"


void printBinaryInGrid(U64 n) {
    std::bitset<64> bits(n); // convert decimal number to binary using std::bitset
    std::string str = bits.to_string(); // convert binary representation to string

    // keep these variables so the inline functions are recognized my compiler
    U64 test = getLowestBit64(1);
    U8 test2 = countOnes(1);


    // print out the binary digits in a grid format
    for (int row = 7; row >= 0; --row) {
        for (int col = 0; col < 8; ++col) {
            int index = row * 8 + col; // calculate index of the bit to print
            std::cout << str[index] << " ";
        }
        std::cout << std::endl;
    }
}

vector<U64> breakBitboard(U64 board) {
    vector<U64> newBitboards;
    while (board != 0) {
        U64 lowest = getLowestBit64(board);
        newBitboards.push_back(lowest);
        board ^= lowest;
    }
    return newBitboards;
}
