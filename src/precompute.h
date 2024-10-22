//
// Created by ShadowCat650 on 3/4/23.
//

#ifndef VELOCITYCHESS_PRECOMPUTE_H
#define VELOCITYCHESS_PRECOMPUTE_H

#include <cmath>
#include "map"
#include "vector"
#include "misc.h"
#include "definitions.h"
#include <cstdint>
#include <bitset>

const U64 RookMagics[64] = {
        0x2000a04084a10402ULL,
        0x800415008020184ULL,
        0x101001208040089ULL,
        0x200080c306002ULL,
        0x101100e01000c409ULL,
        0x8021002811402001ULL,
        0x8208220041150082ULL,
        0x9000608000401109ULL,
        0x8006208141040a00ULL,
        0x8052010208108400ULL,
        0x50200102c084600ULL,
        0x106000410200a00ULL,
        0x204010002a210100ULL,
        0x10200b00401100ULL,
        0x8110804205002200ULL,
        0x808000390080c100ULL,
        0x810206400820001ULL,
        0x2080022830040081ULL,
        0x2300180c010002ULL,
        0x7020021100e0008ULL,
        0x1209062010010008ULL,
        0x1206000c1010030ULL,
        0xe07000412000c000ULL,
        0x4022204002808000ULL,
        0x140800040802500ULL,
        0x88b1000421002200ULL,
        0x60a01101e000804ULL,
        0xc42004c0a002010ULL,
        0xa50217001000900ULL,
        0x881a00011004100ULL,
        0x88848a000401000ULL,
        0x2902400980800121ULL,
        0x9052082000c0441ULL,
        0x902040001c810ULL,
        0x4082010200081004ULL,
        0x4a0c580100041100ULL,
        0x400900100606900ULL,
        0x80c0a200148201ULL,
        0x3a00810700204008ULL,
        0xa00208480004010ULL,
        0x100002000c228241ULL,
        0x182040032085001ULL,
        0x504008002008024ULL,
        0x540a020011200804ULL,
        0x502420011220018ULL,
        0x400910041006000ULL,
        0xd110004008402000ULL,
        0x80c0808000400464ULL,
        0x4002800040802300ULL,
        0x5001000c8a000300ULL,
        0x608e001200084410ULL,
        0x49228048000c0080ULL,
        0x200600201200d840ULL,
        0x8402004021920282ULL,
        0x2087006082400100ULL,
        0x1a01800084644008ULL,
        0x44800220c5800100ULL,
        0xc880800100008200ULL,
        0x10018a201000400ULL,
        0x80080004002681ULL,
        0xa8030000800804cULL,
        0x85000c402000d100ULL,
        0x2c4008c220009002ULL,
        0x280008040022830ULL,
};

const int RookMagicShifts[64] = {
        52, 53, 53, 53, 53, 53, 53, 52,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        52, 53, 53, 53, 53, 53, 53, 52
};


const U64 BishopMagics[64] = {
        0x240c9024410300ULL,
        0x1000c02348160080ULL,
        0x840800411002b080ULL,
        0x8200801840028201ULL,
        0x2003900980421200ULL,
        0x40a1040d4411ULL,
        0x3a2c02021008ULL,
        0x348150802022000ULL,
        0x22105502008205ULL,
        0x200408a848008100ULL,
        0x2240300c212104ULL,
        0x1502041012020240ULL,
        0x901080042120100ULL,
        0x1131084404040c00ULL,
        0x8001004304204240ULL,
        0x304024202200300ULL,
        0x6082081441000881ULL,
        0x4481020200a406ULL,
        0x40c2039001000380ULL,
        0x9064040094000200ULL,
        0x880020c200880804ULL,
        0x6008ac0044001808ULL,
        0x4040218480201ULL,
        0x5081118200808c0ULL,
        0x8003111220020204ULL,
        0x2323040100040120ULL,
        0x20200085000080d0ULL,
        0x10400c0c40c0100ULL,
        0x40e8080a80200ULL,
        0x8082080200210203ULL,
        0x2202820800109000ULL,
        0x2004101808c00210ULL,
        0x1c150000406200ULL,
        0xa1a018800441000ULL,
        0x1401020005080108ULL,
        0x15003021004002ULL,
        0x522020808008028ULL,
        0x8008404008048504ULL,
        0x8021040110100204ULL,
        0x2400c22245400ULL,
        0x15480c80441080ULL,
        0x200240882085eULL,
        0x1002004848060812ULL,
        0x54120202022440ULL,
        0x2002401405020084ULL,
        0x4810084204004808ULL,
        0x2a1000080a080448ULL,
        0x8040020690160600ULL,
        0x2400204248180842ULL,
        0x40120802084480ULL,
        0xc048208804c00808ULL,
        0x1804011040ac0440ULL,
        0x2c082e00401001ULL,
        0x8091281200420004ULL,
        0x1100901040480ULL,
        0x80112022040458ULL,
        0x2101806402024022ULL,
        0x84040446880002ULL,
        0x11050842080488ULL,
        0x184042022a80080ULL,
        0x2042c1280200014ULL,
        0x8020405206080ULL,
        0x8002083501060020ULL,
        0x420031050808080ULL,
};

const int BishopMagicShifts[64] = {
        58, 59, 59, 59, 59, 59, 59, 58,
        59, 59, 59, 59, 59, 59, 59, 59,
        59, 59, 57, 57, 57, 57, 59, 59,
        59, 59, 57, 55, 55, 57, 59, 59,
        59, 59, 57, 55, 55, 57, 59, 59,
        59, 59, 57, 57, 57, 57, 59, 59,
        59, 59, 59, 59, 59, 59, 59, 59,
        58, 59, 59, 59, 59, 59, 59, 58
};


const string int_to_location_string[64] = {
        "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
        "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
        "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
        "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
        "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
        "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
        "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
        "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
};


class precompute {
public:

    U64 KnightAttackTable[64];
    U64 KingAttackTable[64];

    U64 RookAttackTable[64][4096];
    U64 BishopAttackTable[64][4096];

    map<U8, map<U64, U64>> MuggleRookAttackTable;
    map<U8, map<U64, U64>> MuggleBishopAttackTable;

    map<U8, vector<U64>> RookBlockers;
    map<U8, vector<U64>> BishopBlockers;

    U64 RookMasks[64];
    U64 BishopMasks[64];

    map<char, map<U8, U64>> CoordinatesToBitmap;


    void initTables();

    U64 _generateRookMoveSlow(U64 blockers, U8 square);

    U64 _generateBishopMoveSlow(U64 blockers, U8 square);

    map<string, U8> locationStringToInt = {
            {"a1", 0}, {"b1", 1}, {"c1", 2}, {"d1", 3}, {"e1", 4}, {"f1", 5}, {"g1", 6}, {"h1", 7},
            {"a2", 8}, {"b2", 9}, {"c2", 10}, {"d2", 11}, {"e2", 12}, {"f2", 13}, {"g2", 14}, {"h2", 15},
            {"a3", 16}, {"b3", 17}, {"c3", 18}, {"d3", 19}, {"e3", 20}, {"f3", 21}, {"g3", 22}, {"h3", 23},
            {"a4", 24}, {"b4", 25}, {"c4", 26}, {"d4", 27}, {"e4", 28}, {"f4", 29}, {"g4", 30}, {"h4", 31},
            {"a5", 32}, {"b5", 33}, {"c5", 34}, {"d5", 35}, {"e5", 36}, {"f5", 37}, {"g5", 38}, {"h5", 39},
            {"a6", 40}, {"b6", 41}, {"c6", 42}, {"d6", 43}, {"e6", 44}, {"f6", 45}, {"g6", 46}, {"h6", 47},
            {"a7", 48}, {"b7", 49}, {"c7", 50}, {"d7", 51}, {"e7", 52}, {"f7", 53}, {"g7", 54}, {"h7", 55},
            {"a8", 56}, {"b8", 57}, {"c8", 58}, {"d8", 59}, {"e8", 60}, {"f8", 61}, {"g8", 62}, {"h8", 63},
    };

private:

    void _initKnightAttackTable();
    void _initKingAttackTable();
    void _initRookAttackTable();
    void _initBishopAttackTable();

    void _initRookBlockerTable();
    void _initBishopBlockerTable();


    void _initRookMasks();
    void _initBishopMasks();


    void _initCoordinatesToBitmap();


    vector<U64> _getBlockersFor(U8 square, PIECE piece);

    void _initMuggleAttackTables();


};

void initPrecompute();


extern precompute Precomputed;

#endif //VELOCITYCHESS_PRECOMPUTE_H
