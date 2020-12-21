#ifndef KNODE_H
#define KNODE_H

class knode{
    public:
        knode();
        knode(int w, int f);
        int whole, frac, height;
        knode *left;
        knode *right;
};

#endif