#pragma once
#include <iostream>
#include "chess.hpp"
#include "Node.h"
#include "UCT.h"

using namespace chess;

class MonteCarlo {

public:
    chess::Move Run(Movelist possibleMoves, int simulationsInput, Board board);

private:
    int totalSimulations = 0;
    int currentSimulationCount = 0;
    Node* root = nullptr;

    Node* Selection(Node* root);
    Node* Expansion(Node* parentNode);
    GameResult Simulation(Board board);
    void Propagation(Node* newNode);
};