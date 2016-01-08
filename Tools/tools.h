#ifndef TOOLS_H
#define TOOLS_H
#include "node.h"
#include <vector>

class Tools
{
    public:
        Tools();
        static bool Astar(Node current, Node destination, bool **pathingMap, std::vector<Node>& path);
        static bool VectorContainsNode(Node addedNode, std::vector<Node> nodeList);
        static Node BestNodeInVector(std::vector<Node> nodeVector, int& index);
        static bool Passable(Node testedNode, bool **pathingMap);
        static int DistanceManhattan(Node start, Node origin);
        static void UpdateNodeScoreInVector(Node *currentNode,Node updatedNode,std::vector<Node>& nodeVector, int gAdd);
    protected:
    private:
};

#endif // TOOLS_H
