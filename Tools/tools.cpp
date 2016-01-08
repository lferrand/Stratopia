#include "tools.h"
#include <iostream>
#include <stdlib.h>

Tools::Tools()
{
    //ctor
}

bool Tools::Astar(Node start, Node destination, bool **pathingMap, std::vector<Node>& path)
{
    bool solution = false;
    std::vector<Node> openNodes;
    std::vector<Node> closedNodes;
    start.SetG(0);
    start.SetH(0);
    openNodes.push_back(start);
    Node current;
    std::cout << "start x : " << start.GetX()<<"start y : " << start.GetY();
    while (solution == false){

        if(openNodes.empty()){
            return false;
        }
        int index = 0;
        current = BestNodeInVector(openNodes, index);
        closedNodes.push_back(current);
        openNodes.erase(openNodes.begin()+index);

        if (current.GetX() == destination.GetX() && current.GetY() == destination.GetY()){
            solution = true;
            break;
        }

        //bas gauche
        if( !Passable(current.GetBottomLeftNode(),pathingMap) && !VectorContainsNode(current.GetBottomLeftNode(),closedNodes))
        {
            if(!VectorContainsNode(current.GetBottomLeftNode(),openNodes)){
                Node nodeToAdd = current.GetBottomLeftNode();
                nodeToAdd.SetG(current.GetG()+14);
                nodeToAdd.SetH(DistanceManhattan(nodeToAdd,destination)*10);
                nodeToAdd.SetParent(&current);
                openNodes.push_back(nodeToAdd);
            }
            else
            {
                UpdateNodeScoreInVector(&current,current.GetBottomLeftNode(),openNodes, 14);
            }
        }
        //bas
        if( !Passable(current.GetBottomNode(),pathingMap) && !VectorContainsNode(current.GetBottomNode(),closedNodes))
        {
            if(!VectorContainsNode(current.GetBottomNode(),openNodes)){
                Node nodeToAdd = current.GetBottomNode();
                nodeToAdd.SetG(current.GetG()+10);
                nodeToAdd.SetH(DistanceManhattan(nodeToAdd,destination)*10);
                nodeToAdd.SetParent(&current);
                openNodes.push_back(nodeToAdd);
            }
            else
            {
                UpdateNodeScoreInVector(&current,current.GetBottomNode(),openNodes, 10);
            }
        }
        //gauche
        if( !Passable(current.GetLeftNode(),pathingMap) && !VectorContainsNode(current.GetLeftNode(),closedNodes))
        {
            if(!VectorContainsNode(current.GetLeftNode(),openNodes)){
                Node nodeToAdd = current.GetLeftNode();
                nodeToAdd.SetG(current.GetG()+10);
                nodeToAdd.SetH(DistanceManhattan(nodeToAdd,destination)*10);
                nodeToAdd.SetParent(&current);
                openNodes.push_back(nodeToAdd);
            }
            else
            {
                UpdateNodeScoreInVector(&current,current.GetLeftNode(),openNodes, 10);
            }
        }
        // haut gauche
        if( !Passable(current.GetTopLeftNode(),pathingMap) && !VectorContainsNode(current.GetTopLeftNode(),closedNodes))
        {
            if(!VectorContainsNode(current.GetTopLeftNode(),openNodes)){
                Node nodeToAdd = current.GetTopLeftNode();
                nodeToAdd.SetG(current.GetG()+14);
                nodeToAdd.SetH(DistanceManhattan(nodeToAdd,destination)*10);
                nodeToAdd.SetParent(&current);
                openNodes.push_back(nodeToAdd);
            }
            else
            {
                UpdateNodeScoreInVector(&current,current.GetTopLeftNode(),openNodes, 14);
            }
        }
        //haut
        if( !Passable(current.GetTopNode(),pathingMap) && !VectorContainsNode(current.GetTopNode(),closedNodes))
        {
            if(!VectorContainsNode(current.GetTopNode(),openNodes)){
                Node nodeToAdd = current.GetTopNode();
                nodeToAdd.SetG(current.GetG()+10);
                nodeToAdd.SetH(DistanceManhattan(nodeToAdd,destination)*10);
                nodeToAdd.SetParent(&current);
                openNodes.push_back(nodeToAdd);
            }
            else
            {
                UpdateNodeScoreInVector(&current,current.GetTopNode(),openNodes, 10);
            }
        }
        // haut droit
        if( !Passable(current.GetTopRightNode(),pathingMap) && !VectorContainsNode(current.GetTopRightNode(),closedNodes))
        {
            if(!VectorContainsNode(current.GetTopRightNode(),openNodes)){
                Node nodeToAdd = current.GetTopRightNode();
                nodeToAdd.SetG(current.GetG()+14);
                nodeToAdd.SetH(DistanceManhattan(nodeToAdd,destination)*10);
                nodeToAdd.SetParent(&current);
                openNodes.push_back(nodeToAdd);
            }
            else
            {
                UpdateNodeScoreInVector(&current,current.GetTopRightNode(),openNodes, 14);
            }
        }
        //droite
        if( !Passable(current.GetRightNode(),pathingMap) && !VectorContainsNode(current.GetRightNode(),closedNodes))
        {
            if(!VectorContainsNode(current.GetRightNode(),openNodes)){
                Node nodeToAdd = current.GetRightNode();
                nodeToAdd.SetG(current.GetG()+10);
                nodeToAdd.SetH(DistanceManhattan(nodeToAdd,destination)*10);
                nodeToAdd.SetParent(&current);
                openNodes.push_back(nodeToAdd);
            }
            else
            {
                UpdateNodeScoreInVector(&current,current.GetRightNode(),openNodes, 10);
            }
        }
        // bas droit
        if( !Passable(current.GetBottomRightNode(),pathingMap) && !VectorContainsNode(current.GetBottomRightNode(),closedNodes))
        {
            if(!VectorContainsNode(current.GetBottomRightNode(),openNodes)){
                Node nodeToAdd = current.GetBottomRightNode();
                nodeToAdd.SetG(current.GetG()+14);
                nodeToAdd.SetH(DistanceManhattan(nodeToAdd,destination)*10);
                nodeToAdd.SetParent(&current);
                openNodes.push_back(nodeToAdd);
            }
            else
            {
                UpdateNodeScoreInVector(&current,current.GetBottomRightNode(),openNodes, 14);
            }
        }

        Node lastNode = *closedNodes.end();
//        std::cout << "nb open nodes : " << openNodes.size() << "\n";
//        std::cout << "current x : " << current.GetX()<<" current y : " << current.GetY() << "\n";
//        std::cout << "score : " << current.GetScore() << "\n";
    }
    if(solution == true){
        Node *currentBactrack = &current;
        while (currentBactrack->HasParent()){
            std::cout << "solution x : " << currentBactrack->GetX()<<" solution y : " << currentBactrack->GetY() << "\n";
            //std::cout << "trackback : "<< path.size() << "\n";
            path.push_back(*currentBactrack);
            currentBactrack = currentBactrack->GetParent();
        }
    }
}

void Tools::UpdateNodeScoreInVector(Node *currentNode,Node updatedNode,std::vector<Node>& nodeVector, int gAdd)
{
    for(std::vector<Node>::iterator it = nodeVector.begin(); it != nodeVector.end(); ++it) {
        Node itNode = *it;
        if ( updatedNode.GetX() == itNode.GetX() && updatedNode.GetY() == itNode.GetY()){
            int tempScore = currentNode->GetG() + gAdd + itNode.GetH();
            if(tempScore < itNode.GetScore()){
                itNode.SetG(currentNode->GetG() + gAdd);
                itNode.SetParent(currentNode);
            }
        }
    }
}

bool Tools::VectorContainsNode(Node addedNode, std::vector<Node> nodeVector)
{
    for(std::vector<Node>::iterator it = nodeVector.begin(); it != nodeVector.end(); ++it) {
        Node currentNode = *it;
        if ( addedNode.GetX() == currentNode.GetX() && addedNode.GetY() == currentNode.GetY()){
            return true;
        }
        }
    return false;

}

int Tools::DistanceManhattan(Node start, Node origin)
{
    int distance = 0;
    distance = abs(start.GetX() - origin.GetX())+ abs(start.GetY() - origin.GetY());
    //std::cout << "distance mana" << distance << "\n";
    return distance;
}

bool Tools::Passable(Node testedNode, bool **pathingMap)
{
    if(!pathingMap[testedNode.GetX()][testedNode.GetY()]){
        std::cout << testedNode.GetX() << "oba" << testedNode.GetY() << "\n";
    }
    return pathingMap[testedNode.GetX()][testedNode.GetY()];
}

Node Tools::BestNodeInVector(std::vector<Node> nodeVector, int& index)
{
    Node bestNode = *nodeVector.begin();
    int i = 0;
    std::cout << "new test" << "\n";
    for(std::vector<Node>::iterator it = nodeVector.begin(); it != nodeVector.end(); ++it) {
            Node currentNode = *it;
            if (currentNode.GetScore() < bestNode.GetScore()){
                bestNode = currentNode;
                index = i;
            }
            i++;
        }
    std::cout << "best score is : " << bestNode.GetScore() << "\n";
    return bestNode;
}
