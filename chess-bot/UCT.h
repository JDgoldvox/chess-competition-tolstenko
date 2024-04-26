#ifndef CHESS_UCT_H
#define CHESS_UCT_H

#include <cmath>
#include <bits/stdc++.h>
#include <Node.h>
#include <limits>

using namespace std;
static float UCT_CONST = 1.41f;

 class UCT {

 public:
    static float Calculate(int score, int parentVisits, int thisNodeVisits)
    {
        //encourage more exploration
        if(score == 0){
            return std::numeric_limits<float>().max();
        }

        //calculate ratio
        float winRatio = (float)score / (float)thisNodeVisits;

        //calculate exploration term
        float exTop = log(parentVisits);
        float explorationTerm = sqrt( exTop / thisNodeVisits);

        //return UCT with constant
        return winRatio + UCT_CONST * explorationTerm;
    }

    static Node* FindBestUCT(vector<Node*>& nodesVec){

        Node* bestNode = nullptr;
        float bestUCT = -numeric_limits<float>::max();

        for(Node* node : nodesVec){
            if(node->UCT > bestUCT){
                bestUCT = node->UCT;
                bestNode = node;
            }
        }

        //if this is somehow still null
        if(bestNode == nullptr){
            if(nodesVec.size() > 0){
                bestNode = nodesVec[0];
            }
        }

        return bestNode;
    }

 private:

};

#endif //CHESS_UCT_H