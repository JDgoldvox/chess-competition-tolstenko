//
// Created by voxca on 01/04/2024.
//

#include "BoardScore.h"

float BoardScore::Evaluate(const chess::Board& board){
    float totalScore = 0;

    // set our color
    if(board.sideToMove() == Color::BLACK){
        ourColor = Color::WHITE;
    }
    else{
        ourColor = Color::BLACK;
    }

    totalScore += EvaluateBoardScore(board); // -1 to 1
    totalScore += EvaluateKingSafety(board); // outta 1
    totalScore += EvaluateAttackOpportunity(board); // outta 1
    totalScore += EvaluateCenterActivity(board); // outta 1
    totalScore += EvaluatePawnStructure(board); // outta 1

    return totalScore;
}

float BoardScore::EvaluateBoardScore(const chess::Board& board){
    float score;

    for(size_t row = 0; row < 8; row++){
        for(size_t col = 0; col < 8; col++){
            auto piece = board.at(chess::Square(chess::File(row), chess::Rank(col)));

            if(ourColor == Color::WHITE){
                switch(piece.internal()) //we are white
                {
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
            else{ //we are black
                switch(piece.internal())
                {
                    //accumulate scores
                    case chess::Piece::BLACKPAWN:
                        score += 1;
                        break;
                    case chess::Piece::BLACKKNIGHT:
                    case chess::Piece::BLACKBISHOP:
                        score += 3;
                        break;
                    case chess::Piece::BLACKROOK:
                        score += 5;
                        break;
                    case chess::Piece::BLACKQUEEN:
                        score += 9;
                        break;
                    case chess::Piece::BLACKKING:
                        score += 1000;
                        break;

                    case chess::Piece::WHITEPAWN:
                        score -= 1;
                        break;
                    case chess::Piece::WHITEKNIGHT:
                    case chess::Piece::WHITEBISHOP:
                        score -= 3;
                        break;
                    case chess::Piece::WHITEROOK:
                        score -= 5;
                        break;
                    case chess::Piece::WHITEQUEEN:
                        score -= 9;
                        break;
                    case chess::Piece::WHITEKING:
                        score -= 1000;
                        break;
                }
            }
        }
    }

    //1039 is max, return from -1 to 1
    return score / 1039;
}

float BoardScore::EvaluateKingSafety(const chess::Board& board){
    if(ourColor == Color::BLACK){

        //find king square
        Square square = board.kingSq(ourColor);

        //check surrounding squares
        //square.

        //if surrounding king is all pieces,
    }
    //board.at(chess::Piece::BLACKKING);
    //board.isCapture();

    return 0;
}

float BoardScore::EvaluateAttackOpportunity(const chess::Board& board){
    if(ourColor == Color::BLACK){

        //find king square
        Square square = board.kingSq(ourColor);

        //find how many pieces are attacked
       // Board::isAttacked()
       // board.

        for(size_t row = 0; row < 8; row++) {
            for (size_t col = 0; col < 8; col++) {
                Square square = chess::Square(chess::File(row), chess::Rank(col));
                //square.

                //board.isCapture();
                //square.a
            }
        }

    }

    return 0;
}

float BoardScore::EvaluateCenterActivity(const chess::Board& board){
    return 0;
}

float BoardScore::EvaluatePawnStructure(const chess::Board& board){
    return 0;
}