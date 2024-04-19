#pragma once
#include <iostream>
#include "chess.hpp"
#include "Node.h"
#include "UCT.h"

using namespace chess;

class MonteCarlo {

public:
    Move Run(Movelist possibleMoves, int simulationsInput, Board board);
    Move ReturnBestMove();

    ~MonteCarlo(){
        for(Node* node : allNodes){
            delete(node);
        }

        allNodes.clear();
    }
private:
    int totalSimulations = 0;
    int currentSimulationCount = 0;
    Node* root = nullptr;

    Node* Selection(Node* root);
    Node* Expansion(Node* parentNode);
    GameResult Simulation(Node* simulationNode);
    void Propagation(Node* newNode);

    int maxSimulationMoves = 500; //max moves
    GameResult lastResult = GameResult::NONE;
    Color ourColor;

    //clean up
    vector<Node*> allNodes;
};