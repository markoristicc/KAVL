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
        knode approx(int w, int f);
        void inOrder();
        void preOrder();
    private:
        knode* insert(knode *r, int w, int f);
        knode* rightRotate(knode *z);
        knode* leftRotate(knode *z);
        Node *root;
        int count = 0;
        int k = 0;
        //restruct() ---- figure out everything else THEN restruct
}

#endif