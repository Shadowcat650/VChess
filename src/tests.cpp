//
// Created by ShadowCat650 on 3/20/23.
//

#include "tests.h"

void perft_test(int depth, int perft) {
    switch (perft) {
        case 2:
            test_position(depth, "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
            break;
        case 3:
            test_position(depth, "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
            break;
        case 4:
            test_position(depth,"r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
            test_position(depth,"r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1");
            break;
        case 5:
            test_position(depth,"rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
            break;
        case 6:
            test_position(depth,"r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
            break;
        default:
            int t1 = test_position(depth,"r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -", "Perft 2:");
            int t2 = test_position(depth,"8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -", "Perft 3:");
            int t3 = test_position(depth,"r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1", "Perft 4(white variation):");
            int t4 = test_position(depth,"r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1", "Perft 4(black variation):");
            int t5 = test_position(depth,"rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8", "Perft 5:");
            int t6 = test_position(depth,"r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10", "Perft 6:");
            float average = average_numbers({t1, t2, t3, t4, t5, t6});
            cout << "Average time per test: " << average << " microseconds" << endl;
            break;
    }
}

int test_position(int depth, string position, string message) {
    board TestBoard;
    TestBoard.loadPosition(position);
    cout << message << endl;

    auto start = std::chrono::high_resolution_clock::now();

    find_best_move(TestBoard, depth, {});

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Time taken: " << duration << " microseconds." << endl;
    return duration;
}

void basic_speed_test(int depth) {
    test_position(depth,"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 0");
}

float average_numbers(vector<int> numbers) {
    float total = 0;
    for (float n : numbers) {
        total += n;
    }
    float average = total / numbers.size();

    return average;
}