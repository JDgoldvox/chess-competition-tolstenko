//
// Created by voxca on 01/04/2024.
//

#ifndef CHESS_BOARDSCORE_H
#define CHESS_BOARDSCORE_H
#include "chess.hpp"

class BoardScore {
    static int Evaluate(chess::Board& board){

        int score = 0;

        for(size_t row = 0; row < 8; row++){
            for(size_t col = 0; col < 8; col++){
                auto piece = board.at(chess::Square(chess::File(row), chess::Rank(col)));
                switch(piece.internal()){
                    //accumulate scores
                    case chess::Piece::BLACKPAWN:
                        score -= 1;
                        break;
                    case chess::Piece::BLACKKNIGHT:
                    case chess::Piece::BLACKBISHOP:
                        score -= 3;
                        break;
                    case chess::Piece::BLACKROOK:
                        score -= 5;
                        break;
                    case chess::Piece::BLACKQUEEN:
                        score -= 9;
                        break;
                    case chess::Piece::BLACKKING:
                        score -= 1000;
                        break;

                    case chess::Piece::WHITEPAWN:
                        score += 1;
                        break;
                    case chess::Piece::WHITEKNIGHT:
                    case chess::Piece::WHITEBISHOP:
                        score += 3;
                        break;
                    case chess::Piece::WHITEROOK:
                        score += 5;
                        break;
                    case chess::Piece::WHITEQUEEN:
                        score += 9;
                        break;
                    case chess::Piece::WHITEKING:
                        score += 1000;
                        break;

                }
            }
        }
    }
};


#endif //CHESS_BOARDSCORE_H
