#ifndef TOOLS_H
#define TOOLS_H
#include "node.h"
#include <vector>
#include <map>

class Tools
{
    public:
        Tools();
        static bool Astar(Node current, Node destination, bool **pathingMap, std::vector<Node>& path);
        static bool VectorContainsNode(Node addedNode, std::vector<Node> nodeList);
        static Node BestNodeInVector(std::vector<Node> nodeVector, int& index);
        static bool Passable(Node testedNode, bool **pathingMap);
        static int DistanceManhattan(Node start, Node origin);
        static void UpdateNodeScoreInVector(Node *currentNode,Node updatedNode,std::vector<Node>& nodeVector, int gAdd, std::map<Node,Node>& parents);
        static int DistanceEuclidienne(int x1, int x2, int y1, int y2);
        static float DistanceEuclidienneF(int x1, int x2, int y1, int y2);
        static Node GetNodeFromAxis(int x, int y);
    protected:
    private:
};

#endif // TOOLS_H
