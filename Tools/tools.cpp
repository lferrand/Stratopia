#include "tools.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <map>


Tools::Tools()
{
    //ctor
}

   bool operator< (Node lhs, Node rhs)
   {
       return (lhs.GetY()*100000000 + lhs.GetX() < rhs.GetY()*100000000 + rhs.GetX());
   }
bool Tools::Astar(Node start, Node destination, bool **pathingMap, std::vector<Node>& path)
{
    //initialisation des structure necessaire
    bool solution = false;
    std::vector<Node> openNodes;
    std::vector<Node> closedNodes;
    std::map<Node,Node> parents;
    //initialisation du cout du premier node a 0
    start.SetG(0);
    start.SetH(0);
    //ajout au vecteur ouvert
    openNodes.push_back(start);
    Node current;
    int currentIndex;

    while (solution == false){

        //Si le vecteur ouvert est vide il n'y a pas de solution
        if(openNodes.empty()){
            return false;
        }
        //index pour faciliter le retrer de current au vecteur ouvert
        int index = 0;

        //choisi le meilleur noeud dans le vecteur ouvert
        current = BestNodeInVector(openNodes, index);

        //ajout dans le vecteur fermer
        closedNodes.push_back(current);
        currentIndex = closedNodes.size() - 1;
        //on suprime le node choisi du vecteur ouvert
        openNodes.erase(openNodes.begin()+index);

        //verification si on est a destination alors on quitte la boucle
        if (current.GetX() == destination.GetX() && current.GetY() == destination.GetY()){
            solution = true;
            break;
        }

        //Verification de la case en bas a gauche
        if( Passable(current.GetBottomLeftNode(),pathingMap) && !VectorContainsNode(current.GetBottomLeftNode(),closedNodes))
        {
            if(!VectorContainsNode(current.GetBottomLeftNode(),openNodes)){
                Node nodeToAdd = current.GetBottomLeftNode();
                nodeToAdd.SetG(current.GetG()+14);
                nodeToAdd.SetH(DistanceManhattan(nodeToAdd,destination)*10);
                nodeToAdd.SetParent(&closedNodes[currentIndex]);
                parents[nodeToAdd] = closedNodes[currentIndex];
                openNodes.push_back(nodeToAdd);
            }
            else
            {
                UpdateNodeScoreInVector(&closedNodes[currentIndex],current.GetBottomLeftNode(),openNodes, 14,parents);
            }
        }

        //Verification de la case en bas
        if( Passable(current.GetBottomNode(),pathingMap) && !VectorContainsNode(current.GetBottomNode(),closedNodes))
        {
            if(!VectorContainsNode(current.GetBottomNode(),openNodes)){
                Node nodeToAdd = current.GetBottomNode();
                nodeToAdd.SetG(current.GetG()+10);
                nodeToAdd.SetH(DistanceManhattan(nodeToAdd,destination)*10);
                nodeToAdd.SetParent(&closedNodes[currentIndex]);
                parents[nodeToAdd] = closedNodes[currentIndex];
                openNodes.push_back(nodeToAdd);
            }
            else
            {
                UpdateNodeScoreInVector(&closedNodes[currentIndex],current.GetBottomNode(),openNodes, 10,parents);
            }
        }
        //Verification de la case a gauche
        if( Passable(current.GetLeftNode(),pathingMap) && !VectorContainsNode(current.GetLeftNode(),closedNodes))
        {
            if(!VectorContainsNode(current.GetLeftNode(),openNodes)){
                Node nodeToAdd = current.GetLeftNode();
                nodeToAdd.SetG(current.GetG()+10);
                nodeToAdd.SetH(DistanceManhattan(nodeToAdd,destination)*10);
                nodeToAdd.SetParent(&closedNodes[currentIndex]);
                parents[nodeToAdd] = closedNodes[currentIndex];
                openNodes.push_back(nodeToAdd);
            }
            else
            {
                UpdateNodeScoreInVector(&closedNodes[currentIndex],current.GetLeftNode(),openNodes, 10,parents);
            }
        }
        // Verification de la case en haut a gauche
        if( Passable(current.GetTopLeftNode(),pathingMap) && !VectorContainsNode(current.GetTopLeftNode(),closedNodes))
        {
            if(!VectorContainsNode(current.GetTopLeftNode(),openNodes)){
                Node nodeToAdd = current.GetTopLeftNode();
                nodeToAdd.SetG(current.GetG()+14);
                nodeToAdd.SetH(DistanceManhattan(nodeToAdd,destination)*10);
                nodeToAdd.SetParent(&closedNodes[currentIndex]);
                parents[nodeToAdd] = closedNodes[currentIndex];
                openNodes.push_back(nodeToAdd);
            }
            else
            {
                UpdateNodeScoreInVector(&closedNodes[currentIndex],current.GetTopLeftNode(),openNodes, 14,parents);
            }
        }
        //Verification de la case en haut
        if( Passable(current.GetTopNode(),pathingMap) && !VectorContainsNode(current.GetTopNode(),closedNodes))
        {
            if(!VectorContainsNode(current.GetTopNode(),openNodes)){
                Node nodeToAdd = current.GetTopNode();
                nodeToAdd.SetG(current.GetG()+10);
                nodeToAdd.SetH(DistanceManhattan(nodeToAdd,destination)*10);
                nodeToAdd.SetParent(&closedNodes[currentIndex]);
                parents[nodeToAdd] = closedNodes[currentIndex];
                openNodes.push_back(nodeToAdd);
            }
            else
            {
                UpdateNodeScoreInVector(&closedNodes[currentIndex],current.GetTopNode(),openNodes, 10,parents);
            }
        }
        // Verification de la case en haut a droite
        if( Passable(current.GetTopRightNode(),pathingMap) && !VectorContainsNode(current.GetTopRightNode(),closedNodes))
        {
            if(!VectorContainsNode(current.GetTopRightNode(),openNodes)){
                Node nodeToAdd = current.GetTopRightNode();
                nodeToAdd.SetG(current.GetG()+14);
                nodeToAdd.SetH(DistanceManhattan(nodeToAdd,destination)*10);
                nodeToAdd.SetParent(&closedNodes[currentIndex]);
                parents[nodeToAdd] = closedNodes[currentIndex];
                openNodes.push_back(nodeToAdd);
            }
            else
            {
                UpdateNodeScoreInVector(&closedNodes[currentIndex],current.GetTopRightNode(),openNodes, 14,parents);
            }
        }
        //Verification de la case a droite
        if( Passable(current.GetRightNode(),pathingMap) && !VectorContainsNode(current.GetRightNode(),closedNodes))
        {
            if(!VectorContainsNode(current.GetRightNode(),openNodes)){
                Node nodeToAdd = current.GetRightNode();
                nodeToAdd.SetG(current.GetG()+10);
                nodeToAdd.SetH(DistanceManhattan(nodeToAdd,destination)*10);
                nodeToAdd.SetParent(&closedNodes[currentIndex]);
                parents[nodeToAdd] = closedNodes[currentIndex];
                openNodes.push_back(nodeToAdd);
            }
            else
            {
                UpdateNodeScoreInVector(&closedNodes[currentIndex],current.GetRightNode(),openNodes, 10,parents);
            }
        }
        // Verification de la case en bas a droite
        if( Passable(current.GetBottomRightNode(),pathingMap) && !VectorContainsNode(current.GetBottomRightNode(),closedNodes))
        {
            if(!VectorContainsNode(current.GetBottomRightNode(),openNodes)){
                Node nodeToAdd = current.GetBottomRightNode();
                nodeToAdd.SetG(current.GetG()+14);
                nodeToAdd.SetH(DistanceManhattan(nodeToAdd,destination)*10);
                nodeToAdd.SetParent(&closedNodes[currentIndex]);
                parents[nodeToAdd] = closedNodes[currentIndex];
                openNodes.push_back(nodeToAdd);
            }
            else
            {
                UpdateNodeScoreInVector(&closedNodes[currentIndex],current.GetBottomRightNode(),openNodes, 14,parents);
            }
        }
    }

    //Si on trouve une solution alors on Backtrack jusqu'au noeux d'origine
    if(solution == true){

//      Implementation avec les pointeur parent directement dans les Node
//        Node *currentBactrack = &closedNodes[currentIndex];
//        path.push_back(*currentBactrack);
//        while (currentBactrack->HasParent()){
//            std::cout << "solution x : " << currentBactrack->GetX()<<" solution y : " << currentBactrack->GetY() << "\n";
//            std::cout << "trackback : "<< path.size() << "\n";
//            currentBactrack = currentBactrack->GetParent();
//            std::cout << "test";
//            path.push_back(*currentBactrack);
//            std::cout << " solution x : " << currentBactrack->GetX()<<" solution y : " << currentBactrack->GetY() << "\n";
//
//        }

        //Implementation en utilisant une map entre les Nodes et leur parents
        Node currentBactrack = closedNodes[currentIndex];
        path.push_back(currentBactrack);
        std::map<Node,Node>::iterator it = parents.find(currentBactrack);
        while(it != parents.end()) {
            currentBactrack = it->second;
            //std::cout << "solution x : " << currentBactrack.GetX()<<" solution y : " << currentBactrack.GetY() << "\n";
            std::cout << "trackback : "<< path.size() << "\n";
            path.push_back(currentBactrack);
            it = parents.find(currentBactrack);

        }
    }
    return true;
}

void Tools::UpdateNodeScoreInVector(Node *currentNode,Node updatedNode,std::vector<Node>& nodeVector, int gAdd, std::map<Node,Node>& parents)
{

    for(std::vector<Node>::iterator it = nodeVector.begin(); it != nodeVector.end(); ++it) {
        Node itNode = *it;
        if ( updatedNode.GetX() == itNode.GetX() && updatedNode.GetY() == itNode.GetY()){

            int tempScore = currentNode->GetG() + gAdd + itNode.GetH();
            //std::cout << "UPDAAAAATTTEEEEEE: " << itNode.GetScore()<< " into :" << tempScore << "\n";
            if(tempScore < itNode.GetScore()){
                itNode.SetG(currentNode->GetG() + gAdd);
                parents[itNode] = *currentNode;
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
                //std::cout << addedNode.GetX() << " : " << addedNode.GetY() << " contains " << currentNode.GetX() << " : " << currentNode.GetY() <<"\n";
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
    //std::cout << pathingMap[testedNode.GetX()][testedNode.GetY()];
    if(pathingMap[testedNode.GetX()][testedNode.GetY()]){
        //std::cout << testedNode.GetX() << "oba" << testedNode.GetY() << "\n";
    }
    return pathingMap[testedNode.GetX()][testedNode.GetY()];
}

Node Tools::BestNodeInVector(std::vector<Node> nodeVector, int& index)
{
    Node bestNode = *nodeVector.begin();
    int i = 0;
    //std::cout << "new test" << "\n";
    for(std::vector<Node>::iterator it = nodeVector.begin(); it != nodeVector.end(); ++it) {
            Node currentNode = *it;
            if (currentNode.GetScore() < bestNode.GetScore()){
                bestNode = currentNode;
                index = i;
            }
            i++;
        }
    //std::cout << "best score is : " << bestNode.GetScore() << "\n";
    return bestNode;
}

int Tools::DistanceEuclidienne(int x1, int x2, int y1, int y2)
{
    return (int) sqrt( (x1-x2)^2 + (y1-y2)^2);
}
float Tools::DistanceEuclidienneF(int x1, int x2, int y1, int y2)
{
    std::cout << sqrt( (x1-x2)^2 + (y1-y2)^2) << "\n";
    return sqrt( (x1-x2)^2 + (y1-y2)^2);
}

Node Tools::GetNodeFromAxis(int x, int y)
{
    Node result(x/32,y/32);
    return result;
}
Node Tools::FindClosestPassable(Node start, Node unpassable,bool **pathingMap)
{
    Node passable;
    bool found = false;
    std::vector<Node> unpassableNodes;
    std::vector<Node> passableNodes;
    unpassableNodes.push_back(start);
    while(!found){
        for(std::vector<Node>::iterator it = unpassableNodes.begin(); it != unpassableNodes.end();) {

            Node currentNode = *it;
            if (Passable(currentNode.GetBottomNode(),pathingMap)){
                passableNodes.push_back(currentNode.GetBottomNode());
            }
            else{
                unpassableNodes.push_back(currentNode.GetBottomNode());
            }
            if (Passable(currentNode.GetBottomLeftNode(),pathingMap)){
                passableNodes.push_back(currentNode.GetBottomLeftNode());
            }
            else{
                unpassableNodes.push_back(currentNode.GetBottomLeftNode());
            }
            if (Passable(currentNode.GetLeftNode(),pathingMap)){
                passableNodes.push_back(currentNode.GetLeftNode());
            }
            else{
                unpassableNodes.push_back(currentNode.GetLeftNode());
            }
            if (Passable(currentNode.GetTopLeftNode(),pathingMap)){
                passableNodes.push_back(currentNode.GetTopLeftNode());
            }
            else{
                unpassableNodes.push_back(currentNode.GetTopLeftNode());
            }
            if (Passable(currentNode.GetTopNode(),pathingMap)){
                passableNodes.push_back(currentNode.GetTopNode());
            }
            else{
                unpassableNodes.push_back(currentNode.GetTopNode());
            }
            if (Passable(currentNode.GetTopRightNode(),pathingMap)){
                passableNodes.push_back(currentNode.GetTopRightNode());
            }
            else{
                unpassableNodes.push_back(currentNode.GetTopRightNode());
            }
            if (Passable(currentNode.GetRightNode(),pathingMap)){
                passableNodes.push_back(currentNode.GetRightNode());
            }
            else{
                unpassableNodes.push_back(currentNode.GetRightNode());
            }
            if (Passable(currentNode.GetBottomRightNode(),pathingMap)){
                passableNodes.push_back(currentNode.GetBottomRightNode());
            }
            else{
                unpassableNodes.push_back(currentNode.GetBottomRightNode());
            }
            it = unpassableNodes.erase(it);
        }
        if(!passableNodes.empty()){
                found = true;
        }

    }
    passable = passableNodes[0];
    for(std::vector<Node>::iterator it = passableNodes.begin(); it != passableNodes.end(); ++it) {
            Node currentNode = *it;
            if (DistanceEuclidienne(start.GetX(),passable.GetX(),start.GetY(),passable.GetY()) > DistanceEuclidienne(start.GetX(),currentNode.GetX(),start.GetY(),currentNode.GetY())){
                passable = currentNode;
            }
    }
    return passable;
}

