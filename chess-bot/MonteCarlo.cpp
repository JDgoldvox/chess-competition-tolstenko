#include "MonteCarlo.h"

Move MonteCarlo::Run(Movelist moveList, int simulationsInput, Board board){
    totalSimulations = simulationsInput;
    currentSimulationCount = 0;

    //set our color
    if(board.sideToMove() == Color::BLACK){
        ourColor = Color::WHITE;
    }

    //create root
    root = new Node(board, moveList);
    allNodes.emplace_back(root);

//    for(auto move : possibleMoves){
//        chess::Board tempBoard = board;
//
//        tempBoard.makeMove(move);
//
//        chess::Square currentMove = move.to();
//
//        //this is how I see the square
//        if(currentMove == Square::underlying::SQ_A1){
//
//        }
//
//        //this is for ranks
//        if(currentMove.rank() == Rank::RANK_1){
//
//        }
//
//        tempBoard.isGameOver();
//
//        auto piece = board.at(currentMove);
//
//        if(piece == chess::PieceType::PAWN){
//
//        }
//
//    }

    while(currentSimulationCount <= totalSimulations){
        currentSimulationCount++;

        //debug
        //print out children for each root node
        int i = 0;
        for(Node* node : root->children){
            //std::cout << "child[ " << i << " ] has: " << node->children.size() << " children with UCT: " << node->UCT << "\n";
            i++;
        }



        //select
        //std::cout << "-------------------------------------------------------------\n";
        //std::cout << "selection stage\n";
        Node* selectedNode = Selection(root);

        //expand
       // std::cout << "-------------------------------------------------------------\n";
        //std::cout << "expansion stage\n";
        Node* newNode = Expansion(selectedNode);

        //simulate
       // std::cout << "-------------------------------------------------------------\n";
       // std::cout << "simulation stage\n";
        lastResult = Simulation(newNode);

        //propagate
        //std::cout << "-------------------------------------------------------------\n";
       // std::cout << "propagation stage\n";
        Propagation(newNode);
    }

    return ReturnBestMove();
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

    //if we have the same number of moves to children (we maxed children out)
    if(rootInput->children.size() != rootInput->maxChildren){
        //cout << "returning root! root size: " << rootInput->children.size() <<
             //"||| root max children possible: " << rootInput->maxChildren << std::endl;
        return rootInput;
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

    Node* newNode = new Node(parentNode);
    allNodes.emplace_back(newNode);

    //set parent
    newNode->parent = parentNode;

    //set children
    parentNode->children.push_back(newNode);

    return newNode;
}

/*
    in:     board
    out:    result
    brief:  simulates a full game to gather a result (?200 moves?)
*/
GameResult MonteCarlo::Simulation(Node* simulationNode) {

    Board board = simulationNode->board;
    Movelist legalMoves;
    int currentMoveCount = 0;
    GameResult result = GameResult::NONE;

    while(true){
        //recalculate legal moves after making that move
        legalMoves.clear();
        chess::movegen::legalmoves(legalMoves, board);

        //simulate random move
        std::random_device rd;
        std::mt19937 gen(rd()); //assuming this generates the seed
        std::uniform_int_distribution<> dist(0,  legalMoves.size() - 1);

        if(legalMoves.size() - 1 == -1){
            //std::cout << "legal moves is 0" << endl;
            return GameResult::DRAW;
        }

        int rngIndex = dist(gen);
        Move selectedMove = legalMoves[rngIndex];

        //make move
        board.makeMove(selectedMove); //assuming this chances the board

        //check if win, lose or draw
        auto resultPair = board.isGameOver();

       if(resultPair.second == GameResult::WIN){
           //cout << "WIN\n";
            result = resultPair.second;
            break;
        }

        if(resultPair.second == GameResult::LOSE){
            //cout << "LOSS\n";
            result = resultPair.second;
            break;
        }

        //repeat until move limit or result
        currentMoveCount++;

        //limit amount of moves allowed on this simulation
        if(currentMoveCount >= maxSimulationMoves){
            result = resultPair.second;
            //cout << "DRAW\n";
            return GameResult::DRAW;
        }
    }

    return result;
}

/*
    in:     new created node
    out:
    brief:  update all information of all parents from new node
*/
void MonteCarlo::Propagation(Node* newNode) {
    //find out how many points we subtract or add depending on last simulation result
    float pointsToAdd = 0;

    switch(lastResult){
        case GameResult::WIN:
            //opposite color is this node //if next was black turn, this means white won
            if(newNode->board.sideToMove() == Color::BLACK && ourColor == Color::WHITE) {
                pointsToAdd = 1;
            }
            else{
                pointsToAdd = -1;
            }
            break;
        case GameResult::DRAW:
            pointsToAdd = 0.2;
            break;
        case GameResult::LOSE:
            if(newNode->board.sideToMove() == Color::BLACK && ourColor == Color::WHITE) {
                pointsToAdd = -1;
            }
            else{
                pointsToAdd = 1;
            }
            break;
        case GameResult::NONE:
            pointsToAdd -= 100000;
            std::cout << "some shit went down, and now we are messing up in propagation, this shouldn't be happening\n";
            break;
    }

    Node* current = newNode;

    while(current->parent != nullptr){
        current->visits += 1;
        current->score += pointsToAdd;

        if(current == newNode){
            //do not change UCT if its a NEW NODE
        }
        else{
            current->UCT = UCT::Calculate(current->score, current->parent->visits, current->visits);
        }

        current = current->parent;
    }
}

Move MonteCarlo::ReturnBestMove(){

    Node* bestMoveNode = UCT::FindBestUCT(root->children);
    return bestMoveNode->move;
}