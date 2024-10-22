//
// Created by ShadowCat650 on 4/7/23.
//

#include "opening.h"

opening::opening(string openingName) {
    if (openingName == "vienna") {
        vienna();
    } else if (openingName == "london") {
        london();
    } else if (openingName == "caro") {
        caro();
    } else if (openingName == "sicilian") {
        sicilian();
    } else if (openingName == "queensGambit") {
        queensGambit();
    } else if (openingName == "italian") {
        italian();
    } else if (openingName == "french") {
        french();
    } else if (openingName == "scandinavian") {
        scandinavian();
    }
}

void opening::vienna() {
    openingPositions.push_back({"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq ", {0x8000800000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq ", {0x4000200000000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"rnbqkb1r/pppp1ppp/5n2/4p3/4P3/2N5/PPPP1PPP/R1BQKBNR w KQkq ", {0x4000400000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkb1r/pppp1ppp/5n2/8/4Pp2/2N5/PPPP2PP/R1BQKBNR w KQkq ", {0x808000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkbnr/pppp1ppp/8/4P3/5p2/2N5/PPPP2PP/R1BQKBNR w KQkq ", {0x200040000000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"rnbqkbnr/ppp2ppp/3p4/4P3/5p2/2N2N2/PPPP2PP/R1BQKB1R w KQkq ", {0x10001000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkbnr/ppp2ppp/8/4p3/3P1p2/2N2N2/PPP3PP/R1BQKB1R w KQkq ", {0x1008000000000000ULL, QUEEN, WHITE}});
    openingPositions.push_back({"rn1qkbnr/ppp2ppp/8/4p3/3P1pb1/2N2N2/PPP1Q1PP/R1B1KB1R w KQkq ", {0x2000000400000000ULL, BISHOP, WHITE}});
    openingPositions.push_back({"r1bqkbnr/pppp1ppp/2n5/4P3/5p2/2N2N2/PPPP2PP/R1BQKB1R w KQkq ", {0x10001000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkb1r/ppppnppp/8/4P3/5p2/2N2N2/PPPP2PP/R1BQKB1R w KQkq ", {0x10001000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkb1r/ppp2ppp/5n2/3pp3/4PP2/2N5/PPPP2PP/R1BQKBNR w KQkq ", {0x408000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkb1r/ppp2ppp/8/3pP3/4n3/2N5/PPPP2PP/R1BQKBNR w KQkq ", {0x1000040000000000ULL, QUEEN, WHITE}});
    openingPositions.push_back({"rnbqkb1r/ppp2ppp/8/3pP3/8/2n2Q2/PPPP2PP/R1B1KBNR w KQkq ", {0x40200000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkb1r/ppp2ppp/5n2/4P3/4p3/2N5/PPPP2PP/R1BQKBNR w KQkq ", {0x8040000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkb1r/ppp2ppp/3p1n2/4p3/4PP2/2N5/PPPP2PP/R1BQKBNR w KQkq ", {0x200040000000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"r1bqkb1r/ppp2ppp/2np1n2/4p3/4PP2/2N2N2/PPPP2PP/R1BQKB1R w KQkq ", {0x400000040000000ULL, BISHOP, WHITE}});
    openingPositions.push_back({"rnbqk2r/pppp1ppp/3b1n2/4p3/4PP2/2N5/PPPP2PP/R1BQKBNR w KQkq ", {0x408000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqk2r/pppp1ppp/5n2/4b3/4P3/2N5/PPPP2PP/R1BQKBNR w KQkq ", {0x10001000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"r1bqkbnr/pppp1ppp/2n5/4p3/4P3/2N5/PPPP1PPP/R1BQKBNR w KQkq ", {0x400002000000000ULL, BISHOP, WHITE}});
    openingPositions.push_back({"r1bqk1nr/pppp1ppp/2n5/2b1p3/2B1P3/2N5/PPPP1PPP/R1BQK1NR w KQkq ", {0x1000000200000000ULL, QUEEN, WHITE}});
    openingPositions.push_back({"r1bqk1nr/pppp1p1p/2n3p1/2b1p3/2B1P1Q1/2N5/PPPP1PPP/R1B1K1NR w KQkq ", {0x40200000000ULL, QUEEN, WHITE}});
    openingPositions.push_back({"r1bqk2r/pppp1p1p/2n2np1/2b1p3/2B1P3/2N2Q2/PPPP1PPP/R1B1K1NR w KQkq ", {0x208000000000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"r1b1k1nr/pppp1p1p/2n2qp1/2b1p3/2B1P3/2N2Q2/PPPP1PPP/R1B1K1NR w KQkq ", {0x200010000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"r1bqk2r/pppp1ppp/2n2n2/2b1p3/2B1P1Q1/2N5/PPPP1PPP/R1B1K1NR w KQkq ", {0x200000200ULL, QUEEN, WHITE}});
    openingPositions.push_back({"r1b1k1nr/pppp1ppp/2n2q2/2b1p3/2B1P1Q1/2N5/PPPP1PPP/R1B1K1NR w KQkq ", {0x200010000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"r1bqkb1r/pppp1ppp/2n2n2/4p3/2B1P3/2N5/PPPP1PPP/R1BQK1NR w KQkq ", {0x10100000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"r1bqk2r/pppp1ppp/2n2n2/2b1p3/2B1P3/2NP4/PPP2PPP/R1BQK1NR w KQkq ", {0x4000400000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"r1bqk2r/pppp1ppp/2n2n2/2b5/2B1Pp2/2NP4/PPP3PP/R1BQK1NR w KQkq ", {0x2000000400000000ULL, BISHOP, WHITE}});
    openingPositions.push_back({"r1bqk2r/ppp2ppp/2np1n2/2b1p3/2B1PP2/2NP4/PPP3PP/R1BQK1NR w KQkq ", {0x200040000000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"r1bqkb1r/ppp2ppp/2np1n2/4p3/2B1P3/2NP4/PPP2PPP/R1BQK1NR w KQkq ", {0x4000400000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"r2qkb1r/ppp2ppp/2npbn2/4p3/2B1PP2/2NP4/PPP3PP/R1BQK1NR w KQkq ", {0x2000080000ULL, BISHOP, WHITE}});
    openingPositions.push_back({"r2qkb1r/ppp3pp/2nppn2/4p3/4PP2/2NP4/PPP3PP/R1BQK1NR w KQkq ", {0x200040000000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"r1bqk2r/ppp1bppp/2np1n2/4p3/2B1PP2/2NP4/PPP3PP/R1BQK1NR w KQkq ", {0x200040000000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"r1bqkb1r/ppp2ppp/2n2n2/3pp3/2B1P3/2NP4/PPP2PPP/R1BQK1NR w KQkq ", {0x200010000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"r1bqkb1r/ppp2ppp/2n5/3np3/2B1P3/3P4/PPP2PPP/R1BQK1NR w KQkq ", {0x2010000000ULL, BISHOP, WHITE}});
    openingPositions.push_back({"r1bqk2r/pppp1ppp/2n2n2/4p3/1bB1P3/2NP4/PPP2PPP/R1BQK1NR w KQkq ", {0x208000000000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"rnbqk1nr/pppp1ppp/8/2b1p3/4P3/2N5/PPPP1PPP/R1BQKBNR w KQkq ", {0x1000000001000000ULL, QUEEN, WHITE}});
    openingPositions.push_back({"rnbqk1nr/pppp1ppp/8/4p3/1b2P3/2N5/PPPP1PPP/R1BQKBNR w KQkq ", {0x10001000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqk1nr/ppp2ppp/8/3pp3/1b1PP3/2N5/PPP2PPP/R1BQKBNR w KQkq ", {0x810000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkbnr/ppp2ppp/8/3pp3/4P3/2N5/PPPP1PPP/R1BQKBNR w KQkq ", {0x200010000000ULL, KNIGHT, WHITE}});
}

void opening::caro() {
// black
    openingPositions.push_back({"rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq ", {0x202000ULL, PAWN, BLACK}});
    openingPositions.push_back({"rnbqkbnr/pp1ppppp/2p5/8/3PP3/8/PPP2PPP/RNBQKBNR b KQkq ", {0x10001000ULL, PAWN, BLACK}});
    openingPositions.push_back({"rnbqkbnr/pp2pppp/2p5/3pP3/3P4/8/PPP2PPP/RNBQKBNR b KQkq ", {0x20200000ULL, PAWN, BLACK}});
    openingPositions.push_back({"rnbqkbnr/pp2pppp/8/2PpP3/8/8/PPP2PPP/RNBQKBNR b KQkq ", {0x200040ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp2pppp/2n5/2PpP3/8/5N2/PPP2PPP/RNBQKB1R b KQkq ", {0x200000020ULL, BISHOP, BLACK}});
    openingPositions.push_back({"rnbqkbnr/pp2pppp/8/2ppP3/3P4/5N2/PPP2PPP/RNBQKB1R b KQkq ", {0x200000020ULL, BISHOP, BLACK}});
    openingPositions.push_back({"rn1qkbnr/pp2pppp/8/2PpP3/6b1/5N2/PPP2PPP/RNBQKB1R b KQkq ", {0x200040ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"r2qkbnr/pp2pppp/2n5/1BPpP3/6b1/5N2/PPP2PPP/RNBQK2R b KQkq ", {0x80800ULL, PAWN, BLACK}});
    openingPositions.push_back({"r2qkbnr/pp3ppp/2n1p3/1BPpP3/6b1/4BN2/PPP2PPP/RN1QK2R b KQkq ", {0x802ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"r2qkb1r/pp2nppp/2n1p3/1BPpP3/6b1/4BN1P/PPP2PP1/RN1QK2R b KQkq ", {0x40200000000ULL, BISHOP, BLACK}});
    openingPositions.push_back({"r2qkbnr/pp2pppp/2n5/2PpP3/6b1/5N1P/PPP2PP1/RNBQKB1R b KQkq ", {0x40200000000ULL, BISHOP, BLACK}});
    openingPositions.push_back({"rn1qkbnr/pp2pppp/8/2ppP3/3P2b1/5N1P/PPP2PP1/RNBQKB1R b KQkq ", {0x40200000000ULL, BISHOP, BLACK}});
    openingPositions.push_back({"rn1qkbnr/pp2pppp/8/2ppP3/3P4/5Q1P/PPP2PP1/RNB1KB1R b KQkq ", {0x200040ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"rn1qkbnr/pp2pppp/8/2ppP3/3P4/5P1P/PPP2P2/RNBQKB1R b KQkq ", {0x200040ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"rnbqkbnr/pp2pppp/2p5/3P4/3P4/8/PPP2PPP/RNBQKBNR b KQkq ", {0x10200000ULL, PAWN, BLACK}});
    openingPositions.push_back({"rnbqkbnr/pp2pppp/8/3p4/3P4/5N2/PPP2PPP/RNBQKB1R b KQkq ", {0x40002ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"rnbqkbnr/pp2pppp/8/3p4/3P4/2N5/PPP2PPP/R1BQKBNR b KQkq ", {0x40002ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"rnbqkbnr/pp1ppppp/2p5/8/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq ", {0x10001000ULL, PAWN, BLACK}});
    openingPositions.push_back({"rnbqkbnr/pp2pppp/2p5/3P4/8/5N2/PPPP1PPP/RNBQKB1R b KQkq ", {0x10200000ULL, PAWN, BLACK}});
    openingPositions.push_back({"rnbqkbnr/pp2pppp/8/3p4/8/2N2N2/PPPP1PPP/R1BQKB1R b KQkq ", {0x40002ULL, KNIGHT, BLACK}});
    // white
    openingPositions.push_back({"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq ", {0x8000800000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkbnr/pp1ppppp/2p5/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq ", {0x10001000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkbnr/pp2pppp/2p5/3p4/3PP3/8/PPP2PPP/RNBQKBNR w KQkq ", {0x4040000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkbnr/pp2pppp/2p5/8/3Pp3/5P2/PPP3PP/RNBQKBNR w KQkq ", {0x40800000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkb1r/pp2pppp/2p2n2/3p4/3PP3/5P2/PPP3PP/RNBQKBNR w KQkq ", {0x808000000ULL, PAWN, WHITE}});

}


void opening::london() {
    // white
    openingPositions.push_back({"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq ", {0x10001000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkbnr/ppp1pppp/8/3p4/3P4/8/PPP1PPPP/RNBQKBNR w KQkq ", {0x2000000400000000ULL, BISHOP, WHITE}});
    openingPositions.push_back({"rnbqkb1r/ppp1pppp/5n2/3p4/3P1B2/8/PPP1PPPP/RN1QKBNR w KQkq ", {0x8080000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"r1bqkb1r/pp2pppp/2n2n2/2pp4/3P1B2/4PN2/PPP2PPP/RN1QKB1R w KQkq ", {0x20200000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"r1bqkb1r/pp3ppp/2n1pn2/2pp4/3P1B2/2P1PN2/PP3PPP/RN1QKB1R w KQkq ", {0x400100000000000ULL, BISHOP, WHITE}});
    openingPositions.push_back({"r1bqk2r/pp2bppp/2n1pn2/2pp4/3P1B2/2PBPN2/PP3PPP/RN1QK2R w KQkq ", {0x4010000000000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"r1bqk2r/pp2bppp/2n1pn2/3p4/2pP1B2/2PBPN2/PP1N1PPP/R2QK2R w KQkq ", {0x20100000000000ULL, BISHOP, WHITE}});
    openingPositions.push_back({"r1bq1rk1/pp2bppp/2n1pn2/2pp4/3P1B2/2PBPN2/PP1N1PPP/R2QK2R w KQ ", {0x40008000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"r1bq1rk1/pp2bppp/4pn2/2ppn3/3P1B2/2PBP3/PP1N1PPP/R2QK2R w KQ ", {0x1008000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"r1bqkb1r/ppp1pppp/2n2n2/3p4/3P1B2/4P3/PPP2PPP/RN1QKBNR w KQkq ", {0x20200000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"r2qkb1r/ppp1pppp/2n2n2/3p1b2/3P1B2/2P1P3/PP3PPP/RN1QKBNR w KQkq ", {0x400100000000000ULL, BISHOP, WHITE}});
    openingPositions.push_back({"rnbqkb1r/ppp1pppp/5n2/3p4/3P1B2/8/PPP1PPPP/RN1QKBNR w KQkq ", {0x8080000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkb1r/pp2pppp/5n2/2pp4/3P1B2/4P3/PPP2PPP/RN1QKBNR w KQkq ", {0x20200000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"r1bqkb1r/pp2pppp/2n2n2/2pp4/3P1B2/2P1P3/PP3PPP/RN1QKBNR w KQkq ", {0x4010000000000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"r1b1kb1r/pp2pppp/1qn2n2/2pp4/3P1B2/2P1P3/PP1N1PPP/R2QKBNR w KQkq ", {0x1000400000000000ULL, QUEEN, WHITE}});
    openingPositions.push_back({"r1b1kb1r/pp2pppp/2n2n2/2pp4/3P1B2/1qP1P3/PP1N1PPP/R3KBNR w KQkq ", {0x80400000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"r1b1kb1r/pp2pppp/1qn2n2/3p4/2pP1B2/1QP1P3/PP1N1PPP/R3KBNR w KQkq ", {0x20400000000000ULL, QUEEN, WHITE}});
    openingPositions.push_back({"rn1qkb1r/ppp1pppp/5n2/3p1b2/3P1B2/4P3/PPP2PPP/RN1QKBNR w KQkq ", {0x20002000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rn1qkb1r/ppp2ppp/4pn2/3p1b2/2PP1B2/4P3/PP3PPP/RN1QKBNR w KQkq ", {0x1000400000000000ULL, QUEEN, WHITE}});
    openingPositions.push_back({"rnbqkb1r/ppp2ppp/4pn2/3p4/3P1B2/4P3/PPP2PPP/RN1QKBNR w KQkq ", {0x20200000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"r1bqkb1r/ppp2ppp/2n1pn2/3p4/3P1B2/2P1P3/PP3PPP/RN1QKBNR w KQkq ", {0x4010000000000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"rnbqk2r/ppp2ppp/3bpn2/3p4/3P1B2/2P1P3/PP3PPP/RN1QKBNR w KQkq ", {0x20400000000ULL, BISHOP, WHITE}});
    openingPositions.push_back({"rnbqk2r/ppp2ppp/4pn2/3p4/3P4/2P1P1b1/PP3PPP/RN1QKBNR w KQkq ", {0x1020000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkb1r/pppppppp/5n2/8/3P4/8/PPP1PPPP/RNBQKBNR w KQkq ", {0x2000000400000000ULL, BISHOP, WHITE}});
    openingPositions.push_back({"rnbqkb1r/pppppp1p/5np1/8/3P1B2/8/PPP1PPPP/RN1QKBNR w KQkq ", {0x4000200000000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"rnbqk2r/ppppppbp/5np1/8/3P1B2/2N5/PPP1PPPP/R2QKBNR w KQkq ", {0x1010000000000000ULL, QUEEN, WHITE}});
    openingPositions.push_back({"rnbq1rk1/ppppppbp/5np1/8/3P1B2/2N5/PPPQPPPP/R3KBNR w KQ ", {0x2800000000000000ULL, KING, WHITE, QUEENSIDE}});
    openingPositions.push_back({"rnbqkb1r/pp1ppppp/5n2/2p5/3P1B2/8/PPP1PPPP/RN1QKBNR w KQkq ", {0x8080000000000ULL, PAWN, WHITE}});
    // black
    openingPositions.push_back({"rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq ", {0x10001000ULL, PAWN, BLACK}});
    openingPositions.push_back({"rnbqkbnr/ppp1pppp/8/3p4/3P1B2/8/PPP1PPPP/RN1QKBNR b KQkq ", {0x20002000ULL, PAWN, BLACK}});
    openingPositions.push_back({"rnbqkbnr/pp2pppp/8/2Pp4/5B2/8/PPP1PPPP/RN1QKBNR b KQkq ", {0x200040ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp2pppp/2n5/2Pp4/5B2/5N2/PPP1PPPP/RN1QKB1R b KQkq ", {0x80800ULL, PAWN, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp3ppp/2n1p3/2Pp4/8/4BN2/PPP1PPPP/RN1QKB1R b KQkq ", {0x8080000ULL, PAWN, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp2pppp/2n5/2Pp4/5B2/2N5/PPP1PPPP/R2QKBNR b KQkq ", {0x8000800ULL, PAWN, BLACK}});
    openingPositions.push_back({"rnbqkbnr/pp2pppp/8/2pp4/3P1B2/4P3/PPP2PPP/RN1QKBNR b KQkq ", {0x1020000000ULL, PAWN, BLACK}});
    openingPositions.push_back({"rnbqkbnr/pp2pppp/8/3p4/3Q1B2/4P3/PPP2PPP/RN2KBNR b KQkq ", {0x200040ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"rnbqkbnr/pp2pppp/8/3p4/3P1B2/8/PPP2PPP/RN1QKBNR b KQkq ", {0x200040ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp2pppp/2n5/3p4/3P1B2/2P5/PP3PPP/RN1QKBNR b KQkq ", {0x40400ULL, PAWN, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp2p1pp/2n2p2/3p4/3P1B2/2P5/PP1N1PPP/R2QKBNR b KQkq ", {0x8000800ULL, PAWN, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp4pp/2n2p2/3pP3/5B2/2P5/PP1N1PPP/R2QKBNR b KQkq ", {0x8040000ULL, PAWN, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp4pp/2n5/3pp3/5B2/2P2N2/PP1N1PPP/R2QKB1R b KQkq ", {0x40002ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp4pp/2n5/1B1pp3/5B2/2P5/PP1N1PPP/R2QK1NR b KQkq ", {0x40002ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp2p1pp/2n2p2/3p4/3P1B2/2P2N2/PP3PPP/RN1QKB1R b KQkq ", {0x2000200ULL, PAWN, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp2p2p/2n2p2/3p2p1/3P4/2P2NB1/PP3PPP/RN1QKB1R b KQkq ", {0x10002ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp2p1pp/2n2p2/3p4/3P1B2/2PB4/PP3PPP/RN1QK1NR b KQkq ", {0x8000800ULL, PAWN, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp4pp/2n2p2/3pP3/5B2/2PB4/PP3PPP/RN1QK1NR b KQkq ", {0x8040000ULL, PAWN, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp4pp/2n5/3pp3/5B2/2PB1N2/PP3PPP/RN1QK2R b KQkq ", {0x40002ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp2p1pp/2n2p2/3p3Q/3P1B2/2P5/PP3PPP/RN2KBNR b KQkq ", {0x20200ULL, PAWN, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp4pp/2n2p2/3pp2Q/3P1B2/2PB4/PP3PPP/RN2K1NR b KQkq ", {0x20200ULL, PAWN, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp5p/2n2pB1/3pp2Q/3P1B2/2P5/PP3PPP/RN2K1NR b KQkq ", {0x20100ULL, PAWN, BLACK}});
    openingPositions.push_back({"r1bqkbnQ/pp6/2n2pp1/3pp3/3P1B2/2P5/PP3PPP/RN2K1NR b KQkq ", {0x408000000ULL, PAWN, BLACK}});
    openingPositions.push_back({"r1bqkbQ1/pp6/2n2pp1/3p4/3P1p2/2P5/PP3PPP/RN2K1NR b KQkq ", {0x810ULL, QUEEN, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pp2pppp/2n5/3p4/3P1B2/5N2/PPP2PPP/RN1QKB1R b KQkq ", {0x200000020ULL, BISHOP, BLACK}});
    openingPositions.push_back({"rnbqkbnr/ppp1pppp/8/3p4/3P4/5N2/PPP1PPPP/RNBQKB1R b KQkq ", {0x200040ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"r1bqkbnr/ppp1pppp/2n5/3p4/3P1B2/5N2/PPP1PPPP/RN1QKB1R b KQkq ", {0x200000020ULL, BISHOP, BLACK}});
    openingPositions.push_back({"r2qkbnr/ppp1pppp/2n5/3p4/3P1Bb1/4PN2/PPP2PPP/RN1QKB1R b KQkq ", {0x40400ULL, PAWN, BLACK}});
}

void opening::sicilian() {
    // for black


    // for white
}
void opening::queensGambit() {
// white
    openingPositions.push_back({"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq ", {0x10001000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkbnr/ppp1pppp/8/3p4/3P4/8/PPP1PPPP/RNBQKBNR w KQkq ", {0x20002000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkbnr/ppp1pppp/8/8/2pP4/8/PP2PPPP/RNBQKBNR w KQkq ", {0x8000800000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkbnr/p1p1pppp/8/1p6/2pPP3/8/PP3PPP/RNBQKBNR w KQkq ", {0x80008000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkbnr/2p1pppp/p7/1p6/P1pPP3/8/1P3PPP/RNBQKBNR w KQkq ", {0x8040000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkbnr/p3pppp/2p5/1p6/P1pPP3/8/1P3PPP/RNBQKBNR w KQkq ", {0x8040000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkbnr/p3pppp/8/1p6/2pPP3/8/1P3PPP/RNBQKBNR w KQkq ", {0x4000200000000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"rnbqkbnr/4pppp/p7/1p6/2pPP3/2N5/1P3PPP/R1BQKBNR w KQkq ", {0x200040000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"rnbqkbnr/ppp2ppp/4p3/3p4/2PP4/8/PP2PPPP/RNBQKBNR w KQkq ", {0x4000200000000000ULL, KNIGHT, WHITE}});
// black
    openingPositions.push_back({"rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq ", {0x10001000ULL, PAWN, BLACK}});
    openingPositions.push_back({"rnbqkbnr/ppp1pppp/8/3p4/2PP4/8/PP2PPPP/RNBQKBNR b KQkq ", {0x80800ULL, PAWN, BLACK}});
    openingPositions.push_back({"rnbqkbnr/ppp2ppp/4p3/3p4/2PP4/2N5/PP2PPPP/R1BQKBNR b KQkq ", {0x40002ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"rnbqkbnr/ppp2ppp/4p3/3p4/2PP4/5N2/PP2PPPP/RNBQKB1R b KQkq ", {0x40002ULL, KNIGHT, BLACK}});
}

void opening::italian() {
    // for white
    openingPositions.push_back({"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq ", {0x8000800000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq ", {0x200040000000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"r1bqkbnr/pppp1ppp/2n5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq ", {0x400002000000000ULL, BISHOP, WHITE}});
    openingPositions.push_back({"r1bqk1nr/pppp1ppp/2n5/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq ", {0x20200000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"r1bqk1nr/pppp1pp1/2n4p/2b1p3/2B1P3/2P2N2/PP1P1PPP/RNBQK2R w KQkq ", {0x10001000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"r1bqk1nr/pppp1pp1/2n4p/2b5/2BpP3/2P2N2/PP3PPP/RNBQK2R w KQkq ", {0x201000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"r1bqk1nr/pppp1pp1/2n4p/8/1bBPP3/5N2/PP3PPP/RNBQK2R w KQkq ", {0x4000200000000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"r1bqk2r/pppp1ppp/2n2n2/2b1p3/2B1P3/2P2N2/PP1P1PPP/RNBQK2R w KQkq ", {0x10001000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"r1bqk2r/pppp1ppp/2n2n2/2b5/2BpP3/2P2N2/PP3PPP/RNBQK2R w KQkq ", {0x201000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"r1bqk2r/pppp1ppp/1bn2n2/8/2BPP3/5N2/PP3PPP/RNBQK2R w KQkq ", {0x1010000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"r1bqk2r/pppp1ppp/2n2n2/8/1bBPP3/5N2/PP3PPP/RNBQK2R w KQkq ", {0x4000200000000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"r1bqk2r/pppp1ppp/2n5/8/1bBPn3/2N2N2/PP3PPP/R1BQK2R w KQkq ", {0xa00000000000000ULL, KING, WHITE, KINGSIDE}});
    openingPositions.push_back({"r1bqk2r/pppp1ppp/2n5/8/2BPn3/2b2N2/PP3PPP/R1BQ1RK1 w kq ", {0x1010000000ULL, PAWN, WHITE}});
    // for black
    openingPositions.push_back({"rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq ", {0x8000800ULL, PAWN, BLACK}});
    openingPositions.push_back({"rnbqkbnr/pppp1ppp/8/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq ", {0x200040ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"r1bqkbnr/pppp1ppp/2n5/4p3/2B1P3/5N2/PPPP1PPP/RNBQK2R b KQkq ", {0x20000004ULL, BISHOP, BLACK}});
    openingPositions.push_back({"r1bqk1nr/pppp1ppp/2n5/2b1p3/2B1P3/2P2N2/PP1P1PPP/RNBQK2R b KQkq ", {0x40002ULL, KNIGHT, BLACK}});
}

void opening::french() {
    // for white

    // for black
}

void opening::scandinavian() {
// black
    openingPositions.push_back({"rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq ", {0x10001000ULL, PAWN, BLACK}});
    openingPositions.push_back({"rnbqkbnr/ppp1pppp/8/3P4/8/8/PPPP1PPP/RNBQKBNR b KQkq ", {0x10000010ULL, QUEEN, BLACK}});
    openingPositions.push_back({"rnb1kbnr/ppp1pppp/8/3q4/8/2N5/PPPP1PPP/R1BQKBNR b KQkq ", {0x90000000ULL, QUEEN, BLACK}});
    openingPositions.push_back({"rnb1kbnr/ppp1pppp/8/q7/3P4/2N5/PPP2PPP/R1BQKBNR b KQkq ", {0x40002ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"rnb1kbnr/ppp1pppp/8/q7/8/2N2N2/PPPP1PPP/R1BQKB1R b KQkq ", {0x40002ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"rnb1kb1r/ppp1pppp/5n2/q7/2B5/2N2N2/PPPP1PPP/R1BQK2R b KQkq ", {0x200040ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"r1b1kb1r/ppp1pppp/2n2n2/q7/2B5/2NP1N2/PPP2PPP/R1BQK2R b KQkq ", {0x200000020ULL, BISHOP, BLACK}});
    openingPositions.push_back({"r3kb1r/ppp1pppp/2n2n2/q7/2B3b1/2NP1N2/PPP2PPP/R1BQ1RK1 b kq ", {0x28ULL, KING, BLACK, QUEENSIDE}});
    openingPositions.push_back({"rnb1kb1r/ppp1pppp/5n2/q7/3P4/2N2N2/PPP2PPP/R1BQKB1R b KQkq ", {0x200000020ULL, BISHOP, BLACK}});
    openingPositions.push_back({"rn2kb1r/ppp1pppp/5n2/q7/3P2b1/2N2N1P/PPP2PP1/R1BQKB1R b KQkq ", {0x201000000ULL, BISHOP, BLACK}});
    openingPositions.push_back({"rn2kb1r/ppp1pppp/5n2/q7/3P2b1/2N2N2/PPP1BPPP/R1BQK2R b KQkq ", {0x200040ULL, KNIGHT, BLACK}});
    openingPositions.push_back({"r3kb1r/ppp1pppp/2n2n2/q2P4/6b1/2N2N2/PPP1BPPP/R1BQK2R b KQkq ", {0x28ULL, KING, BLACK, QUEENSIDE}});
    openingPositions.push_back({"rn2kb1r/ppp1pppp/5n2/q6b/3P4/2N2N1P/PPP1BPP1/R1BQK2R b KQkq ", {0x80800ULL, PAWN, BLACK}});
    openingPositions.push_back({"rn2kb1r/ppp1pppp/5n2/q6b/2BP4/2N2N1P/PPP2PP1/R1BQK2R b KQkq ", {0x80800ULL, PAWN, BLACK}});
// white
    openingPositions.push_back({"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq ", {0x8000800000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq ", {0x810000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnb1kbnr/ppp1pppp/8/3q4/8/8/PPPP1PPP/RNBQKBNR w KQkq ", {0x4000200000000000ULL, KNIGHT, WHITE}});
    openingPositions.push_back({"rnb1kbnr/ppp1pppp/8/q7/8/2N5/PPPP1PPP/R1BQKBNR w KQkq ", {0x10001000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnbqkbnr/ppp1pppp/8/8/8/2N5/PPPP1PPP/R1BQKBNR w KQkq ", {0x10001000000000ULL, PAWN, WHITE}});
    openingPositions.push_back({"rnb1kbnr/ppp1pppp/3q4/8/8/2N5/PPPP1PPP/R1BQKBNR w KQkq ", {0x10001000000000ULL, PAWN, WHITE}});
}
