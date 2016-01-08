#include "node.h"
#include <cstddef>

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
    return this->G;
}

int Node::GetH()
{
    return this->H;
}

Node* Node::GetParent()
{
    return this->parentNode;
}

int Node::GetScore()
{
    return G + H;
}

void Node::SetParent(Node *parent)
{
    this->parentNode = parent;
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
    Node node = Node(this->x + 1, this->y);
    return node;
}

Node Node::GetTopRightNode()
{
    Node node = Node(this->x+1,this->y+1);
    return node;
}
Node Node::GetTopNode()
{
    Node node = Node(this->x+1,this->y);
    return node;
}
Node Node::GetBottomRightNode()
{
    Node node = Node(this->x+1,this->y-1);
    return node;
}
Node Node::GetBottomNode()
{
    Node node = Node(this->x,this->y-1);
    return node;
}
Node Node::GetLeftNode()
{
    Node node = Node(this->x-1,this->y);
    return node;
}
Node Node::GetTopLeftNode()
{
    Node node = Node(this->x-1,this->y+1);
    return node;
}
Node Node::GetBottomLeftNode()
{
    Node node = Node(this->x-1,this->y-1);
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
