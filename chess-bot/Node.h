#pragma once
#include <iostream>
#include <limits>
#include <vector>
#include <chess.hpp>

using namespace std;
using namespace chess;

class Node {
	
public:
    Node(Movelist possibleMovesInput){
        maxChildren = possibleMoves.size();
        possibleMoves = possibleMovesInput; //not 100% sure if this makes a copy.
    }

    //parent relation
	Node* parent = nullptr;

    //children relation
	vector<Node*> children;

    //possible moves to play
    chess::Movelist possibleMoves;

	float UCT = numeric_limits<float>::max();
    float wins = 0; // -1 = loss, +1 win, +0 draw

    int maxChildren = 0;
    int visits = 1;

    chess::Color color;
};