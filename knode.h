#ifndef KNODE_H
#define NODE_H

class Node{
    public:
        Node();
        ~Node();
        Node(int w, int f);
        int whole, frac, height;
        Node *left;
        Node *right;
}

#endif