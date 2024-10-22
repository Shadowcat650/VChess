//
// Created by ShadowCat650 on 3/11/23.
//

#include "magic_search.h"


void find_magics() {
    cout << "Bishop magics: \n";
    for (int square = 0; square < 64; square++) {
        U64 number = generateMagic(square, false);
        if (number != 0) {
            cout << "0x" << hex << number << "ULL" << "," << "\n";
        }
    }
    cout << "Rook magics: \n";
    for (int square = 0; square < 64; square++) {
        U64 number = generateMagic(square, true);
        if (number != 0) {
            cout << "0x" << hex << number << "ULL" << "," << "\n";
        }
    }
}


std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution<> dist_small(8,12);
std::uniform_int_distribution<int> dist_big(0, 63);


U64 get_random() {
    int ones = dist_small(rng);
    U64 random = 0;
    for (int i = 0; i < ones; i++) {
        int pos = dist_big(rng);
        while ((random >> pos) & 1) {
            pos = dist_big(rng);
        }
        random |= 1ULL << pos;
    }
    return random;
}


U64 generateMagic(int square, bool isRook) {
    vector<U64> blockers = (isRook) ? Precomputed.RookBlockers[square] : Precomputed.BishopBlockers[square];

    int shift = (isRook) ? RookMagicShifts[square] : BishopMagicShifts[square];

    // init attack-index table
    U64 index_attack[4096];

    // blocker combinations with different attack sets have different indexes

    while (true) {
        bool valid_magic = true;

        memset(index_attack, 0, sizeof(index_attack));

        // generate magic number to try
        U64 magic = get_random();


        // loop through all possible combinations of blockers
        for (U64 combination : blockers) {

            // generate the index
            U16 index = (combination * magic) >> shift;

            // get attack set
            U64 attacks = (isRook) ? Precomputed.MuggleRookAttackTable[square][combination] : Precomputed.MuggleBishopAttackTable[square][combination];

            if (index_attack[index] == 0) { // check if the index has been used before
                index_attack[index] = attacks;
            } else {
                valid_magic = false;
                break;
            }
        }
        if (valid_magic) {
            return magic;  // magic had no bad collisions, so it returns
        }
    }
}
