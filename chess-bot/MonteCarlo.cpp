#include "MonteCarlo.h"

chess::Move MonteCarlo::Run(Movelist possibleMoves, int simulationsInput, Board board){
    simulations = simulationsInput;
    root = new Node(possibleMoves, board);

    for(auto move : possibleMoves){
        chess::Board tempBoard = board;

        tempBoard.makeMove(move);

        chess::Square currentMove = move.to();

        //this is how I see the square
        if(currentMove == Square::underlying::SQ_A1){

        }

        //this is for ranks
        if(currentMove.rank() == Rank::RANK_1){

        }

        tempBoard.isGameOver();

        auto piece = board.at(currentMove);

        if(piece == chess::PieceType::PAWN){

        }

    }

    //select

    //expand
    
    //simulate

    //propagate

    return possibleMoves[0];
    //return chess::Move();
}

/*
    in:     root node
    out:    best node
    brief:  select a node using UCT
            if children maxed, then select children
            if children missing, select this node
*/
Node* MonteCarlo::Selection(Node* rootInput) {

    Node* current = rootInput;

    //compare root first
    if(current == rootInput){
        //if we have the same number of moves to children (we maxed children out)
        if(rootInput->children.size() != rootInput->maxChildren){
            cout << "returning root! root size: " << rootInput->children.size() <<
            "||| root max children possible: " << rootInput->maxChildren << std::endl;
            return rootInput;
        }
    }

    current = UCT::FindBestUCT(rootInput->children);

    //this is now not a root node
    while(true){

        //node does not have max children
        if(current->children.size() != current->maxChildren){
            return current;
        }

        //node has max children...

        //scan all ucts for best node
        current = UCT::FindBestUCT(current->children);
    }
}

/*
    in:     selected node
    out:    new created node
    brief:  expands upon selected node
*/
Node* MonteCarlo::Expansion(Node* parentNode) {

    // this don't work, how do I get all new possible moves???????
    Node* newNode = new Node(parentNode->board, parentNode);

    //set parent
    newNode->parent = parentNode;

    //set children
    parentNode->children.push_back(newNode);
}

/*
    in:     board
    out:    result
    brief:  simulates a full game to gather a result (?200 moves?)
*/
GameResult MonteCarlo::Simulation(Board board) {

    //get board
    //simulate random move
    //make move
    //repeat until move limit or result
    //return result

    //board.isGameOver()

    return GameResult();
}

/*
    in:     new created node
    out:
    brief:  update all information of all parents from new node
*/
void MonteCarlo::Propagation(Node* newNode) {
    Node* current = newNode;

    while(current->parent != nullptr){
        current->visits += 1;
        current->UCT = UCT::Calculate(current->wins, current->parent->visits, current->visits);
        current = current->parent;
    }

}