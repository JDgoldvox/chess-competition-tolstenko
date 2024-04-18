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
    Node(Board parentBoard, Node* parentNode){

        //choose random move from board legal moves
        chess::Movelist currentLegalMoves;
        currentLegalMoves = parentNode->possibleMoves;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0,  currentLegalMoves.size() - 1);
        auto selectedMove = currentLegalMoves[dist(gen)];

        //this returns index if found
        int index = parentNode->possibleMoves.find(selectedMove);
        currentLegalMoves[index].; // <--------- this does not have remove function implemented??
        //Either we have to create a generic list and loop through all values or find way to remove using Chess::movelist
        //Either we have to create a generic list and loop through all values or find way to remove using Chess::movelist
        //Either we have to create a generic list and loop through all values or find way to remove using Chess::movelist
        //Either we have to create a generic list and loop through all values or find way to remove using Chess::movelist
        //Either we have to create a generic list and loop through all values or find way to remove using Chess::movelist
        //Either we have to create a generic list and loop through all values or find way to remove using Chess::movelist

        //set move & make move
        move = selectedMove;
        board = parentBoard;
        board.makeMove(selectedMove);

        //recalculate legal moves after making that move
        currentLegalMoves.clear();
        chess::movegen::legalmoves(currentLegalMoves, board);

        //set initial max children
        maxChildren = currentLegalMoves.size();

        //set all possible moves to make
        possibleMoves = currentLegalMoves;
    }

    /*
    * root node
    */
    Node(Board thisBoard, bool isRootNode){
        maxChildren = possibleMoves.size();
        possibleMoves = possibleMovesInput; //not 100% sure if this makes a copy.
        board = thisBoard;
    }

    //parent relation
	Node* parent = nullptr;

    //children relation
	vector<Node*> children;

    //possible moves to play
    chess::Movelist possibleMoves;

    //uct
	float UCT = numeric_limits<float>::max();
    float wins = 0; // -1 = loss, +1 win, +0 draw

    int maxChildren = 0;
    int visits = 1;

    Board board;
    Move move;
};