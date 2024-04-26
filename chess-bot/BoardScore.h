//
// Created by voxca on 01/04/2024.
//

#ifndef CHESS_BOARDSCORE_H
#define CHESS_BOARDSCORE_H
#include "chess.hpp"

using namespace chess;

class BoardScore {
public:
    static float Evaluate(const chess::Board& board);

private:
    static float EvaluateBoardScore(const chess::Board& board);
    static float EvaluateKingSafety(const chess::Board& board);
    static float EvaluateAttackOpportunity(const chess::Board& board);
    static float EvaluateCenterActivity(const chess::Board& board);
    static float EvaluatePawnStructure(const chess::Board& board);

//    static Color ourColor;
//    static Color enemyColor;
};

#endif //CHESS_BOARDSCORE_H
