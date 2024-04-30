#pragma once
#include <iostream>
#include "chess.hpp"
#include "Node.h"
#include "UCT.h"
#include "BoardScore.h"

using namespace chess;

class MonteCarlo {

public:
    Move Run(Movelist possibleMoves, int simulationsInput, Board board);
    Move ReturnBestMove();

    ~MonteCarlo(){
        DestroyAllNodes();
    }
private:
    void DestroyAllNodes();

    int totalSimulations = 0;
    int currentSimulationCount = 0;
    Node* root = nullptr;

    Node* Selection(Node* root);
    Node* Expansion(Node* parentNode);
    GameResult Simulation(Node* simulationNode);
    void Propagation(Node* newNode);

    int maxSimulationMoves = 90; //max moves
    GameResult lastResult = GameResult::NONE;
    Color ourColor;

    //clean up
    vector<Node*> allNodes;
};