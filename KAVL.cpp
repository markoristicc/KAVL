#include "knode.h"
#include "KAVL.h"
using namespace std;

KAVL::KAVL(int k){
    this->k = k;
};
KAVL::~KAVL(){
    //idk
};
bool ins(int w, int f){
    int tmp = count;
    root = insert(root, w, f);
    if(tmp == count)
        return false;
    else return true;
};
bool del(int w, int f){

};
bool search(int w, int f){
    knode *tmp = root;
    while(tmp != NULL){
        if(w < tmp->whole){
            tmp = tmp->left;
        }
        else if(w > tmp->whole){
            tmp = tmp->right;
        }
        else if(w == tmp->whole){
            if(f < tmp->frac){
                tmp = tmp->left;
            }else if(f > tmp->frac){
                tmp = tmp->right;
            }else return true;
        }
    }
    return false;
};
knode approx(int w, int f){

}
void inOrder(){

}
void preOrder(){

}
knode* insert(knode *r, int w, int f){
    if(r = NULL)
        return new Node(w, f);
    else if(w < r->whole)
        r->right = insert(r->right, w, f);
    else if(w > r->whole)
        r->left = insert(r->left, w, f);
    else if(w == r->whole){
        if(f < r->frac)
            r->right = insert(r->right, w, f);
        else if(f > f->frac)
            r->left = insert(f->left, w, f);
        else break;
    }
    int balance = r->left->height - r->right->height;
    if(balance > k && (w < r->left->whole || (w == r->left->whole && f < r->left->frac)))
        rightRotate(r);
    if(balance < -k && (w > r->right->whole || (w == r->right->whole && f > r->right->frac)))
        leftRotate(r);
    if(balance > k && (w > r->left->whole || (w == r->left->whole && f >r->left->frac))){
        r->left = leftRotate(r->left);
        rightRotate(r);
    }
    if(balance > k && (w > r->left->whole || (w == r->left->whole && f >r->left->frac))){
        r->right = rightRotate(r->right);
        leftRotate(r);
    }
    return r;
}
knode* rightRotate(knode *z){
    knode *y = z->left;
    knode *T3 = y->right;
    z->left = T3;
    y->right = z;
    z->height = max(z->left, z->right) + 1;
    y->height = max(y->left, y->right) + 1;
    return y;
};
knode *leftRotate(knode *z){
    knode *y = z->right;
    knode *T2 = y->left;
    z->right = T2;
    y->left = z;
    z->height = max(z->left, z->right) + 1;
    y->height = max(y->left, y->right) + 1;
    return y;
}
