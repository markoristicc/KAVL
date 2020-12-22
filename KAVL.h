#include "knode.h"

#ifndef KAVL_H
#define KAVL_H
class KAVL{
    public:
        KAVL(int k);
        ~KAVL();
        bool ins(int w, int f);
        bool del(int w, int f);
        bool search(int w, int f);
        knode* approx(int w, int f);
        void inprint();
        void preprint();
        void inOrder(knode *r);
        void preOrder(knode *r);
    private:
        knode* insert(knode *r, int w, int f);
        knode* del(knode *r, int w, int f);
        knode* rightRotate(knode *z);
        knode* leftRotate(knode *z);
        knode* inOrderPredecessor(knode *r);
        void destruct(knode *r);
        knode *root = nullptr;
        int count = 0;
        int k = 0;
        //restruct() ---- figure out everything else THEN restruct
};

#endif