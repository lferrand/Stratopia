#ifndef NODE_H
#define NODE_H

class Node
{
    public:
        Node();
        Node(int x,int y);
        virtual ~Node();
        int GetX();
        int GetY();
        int GetG();
        int GetH();
        int GetScore();
        int GetWorldX();
        int GetWorldY();
        Node* GetParent();
        void SetX(int x);
        void SetY(int y);
        void SetG(int G);
        void SetH(int H);
        void SetParent(Node *parent);
        Node GetRightNode();
        Node GetTopRightNode();
        Node GetTopNode();
        Node GetBottomRightNode();
        Node GetBottomNode();
        Node GetLeftNode();
        Node GetTopLeftNode();
        Node GetBottomLeftNode();
        bool HasParent();
    protected:
    private:
        int x;
        int y;
        Node *parentNode;
        int G;
        int H;
};

#endif // NODE_H
