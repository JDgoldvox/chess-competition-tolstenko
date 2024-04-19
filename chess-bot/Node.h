#pragma once
#include <iostream>
#include <limits>
#include <vector>
#include <chess.hpp>
#include <random>

using namespace std;
using namespace chess;

class Node {
	
public:

    /*
     * parent board
     */
    Node(Node* parentNode){

        //choose random move from board legal moves
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0,  parentNode->possibleMoves.size() - 1);
        int rng = dist(gen);
        Move selectedMove = parentNode->possibleMoves[rng]; //not sure whats up with this, but im getting an error here.

        //set move & make move
        move = selectedMove;
        board = parentNode->board;
        board.makeMove(selectedMove);

        //delete the move we just made --------------------------------------------
        //this returns itt for the selected move
        auto itt = std::find(parentNode->possibleMoves.begin(), parentNode->possibleMoves.end(), selectedMove);
        //remove it from list
        parentNode->possibleMoves.erase(itt);

        //now capture all legal moves after this current move ------------------------------------------------

        //recalculate legal moves after making that move
        Movelist legalMoves;
        chess::movegen::legalmoves(legalMoves, board);

        //set all possible moves to make
        for(Move legalMove : legalMoves){
            possibleMoves.emplace_back(legalMove);
        }

        //set initial max children
        maxChildren = possibleMoves.size();
    }

    /*
    * root node
    */
    Node(Board& thisBoard, Movelist legalMoves){

        //set all possible moves to make
        for(Move legalMove : legalMoves){
            possibleMoves.emplace_back(legalMove);
        }

        maxChildren = possibleMoves.size();
        board = thisBoard;
    }

    //parent relation
	Node* parent = nullptr;

    //children relation
	vector<Node*> children;

    //possible moves to play
    vector<Move> possibleMoves;

    //uct
	float UCT = numeric_limits<float>::max();
    float score = 0; // -1 = loss, +1 win, +0.1 draw

    unsigned int maxChildren = 0;
    unsigned int visits = 1;

    Board board;
    Move move;
};