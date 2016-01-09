#include "node.h"
#include <cstddef>
#include <iostream>
#include <stdlib.h>

Node::Node()
{

}
Node::Node(int x, int y)
{
    this->x = x;
    this->y = y;
}

Node::~Node()
{
    //dtor
}

int Node::GetX()
{
    return x;
}

int Node::GetY()
{
    return y;
}

int Node::GetG()
{
    return  G;
}

int Node::GetH()
{
    return  H;
}

int Node::GetWorldX()
{
    return x * (800/40) + (40/2);
}

int Node::GetWorldY()
{
    return y * (800/40) + (40/2);
}

Node* Node::GetParent()
{
    return  parentNode;
}

int Node::GetScore()
{
    return G + H;
}

void Node::SetParent(Node *parent)
{
    std::cout << "added parent x :" << parent->GetX() << " y : " << parent->GetY() << "\n";
     parentNode = parent;
}

void Node::SetH(int H)
{
    this->H = H;
}

void Node::SetG(int G)
{
    this->G = G;
}

void Node::SetY(int y)
{
    this->y = y;
}

void Node::SetX(int x)
{
    this->x = x;
}

Node Node::GetRightNode()
{
    Node node = Node(x + 1, y);
    return node;
}

Node Node::GetTopRightNode()
{
    Node node = Node(x+1,y+1);
    return node;
}
Node Node::GetTopNode()
{
    Node node = Node(x,y+1);
    return node;
}
Node Node::GetBottomRightNode()
{
    Node node = Node( x+1, y-1);
    return node;
}
Node Node::GetBottomNode()
{
    Node node = Node( x, y-1);
    return node;
}
Node Node::GetLeftNode()
{
    Node node = Node( x-1, y);
    return node;
}
Node Node::GetTopLeftNode()
{
    Node node = Node( x-1, y+1);
    return node;
}
Node Node::GetBottomLeftNode()
{
    Node node = Node( x-1, y-1);
    return node;
}

bool Node::HasParent()
{
    if (this->parentNode != NULL){
        return true;
    }
    else{
        return false;
    }
}
