#ifndef CHESS_UCT_H
#define CHESS_UCT_H

#include <cmath>
#include <bits/stdc++.h>
#include <Node.h>

using namespace std;
static float UCT_CONST = 1.41f;

 class UCT {

 public:
    static float Calculate(int wins, int parentVisits, int thisNodeVisits)
    {
        float winRatio = (float)wins / (float)thisNodeVisits;
        return winRatio + UCT_CONST * sqrt(log(thisNodeVisits) / parentVisits);
    }

    static Node* FindBestUCT(vector<Node*>& nodesVec){

        Node* bestNode = nullptr;
        float bestScore = numeric_limits<float>::min();

        for(Node* node : nodesVec){

            if(node->UCT > bestScore){
                bestScore = node->UCT;
                bestNode = node;
            }
        }

        return bestNode;
    }

 private:

};

#endif //CHESS_UCT_H