#include "knode.h"
#include "KAVL.h"
#include <cstdlib>
#include <iostream>
using namespace std;

KAVL::KAVL(int k){
    this->k = k;
};
KAVL::~KAVL(){
    destruct(root);
};
bool KAVL::ins(int w, int f){
    int tmp = count;
    root = insert(root, w, f);
    if(tmp == count)
        return false;
    else return true;
};
bool KAVL::del(int w, int f){
    int tmp = count;
    root = del(root, w, f);
    if(tmp == count)
        return false;
    else return true;
};
bool KAVL::search(int w, int f){
    knode *tmp = root;
    while(tmp != nullptr){
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
knode* KAVL::approx(int w, int f){
    knode *tmp = root;
    knode *closest = root;
    double difference = abs(root->whole + (0.1*root->frac) - w - (0.1*f));
    while(tmp != nullptr){
        if(difference < abs(tmp->whole + (0.1*tmp->frac) - w - (0.1*f))){
            difference = abs(tmp->whole + 0.1*tmp->frac - w - (0.1*f));
            closest = tmp;
        }
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
            }else return tmp;
        }
    }
    return closest;
};
void KAVL::inprint(){
    inOrder(root);
};
void KAVL::inOrder(knode *r){
    if(r != nullptr){
        inOrder(r->left);
        cout<<r->whole<<"."<<r->frac<<" ";
        inOrder(r->right);
    }
};
void KAVL::preprint(){
    preOrder(root);
}
void KAVL::preOrder(knode *r){
    if(r != nullptr){
        if(r != root)
            cout<<" ";
        cout<<r->whole<<"."<<r->frac;
        preOrder(r->left);
        preOrder(r->right);
    }
};
knode* KAVL::insert(knode *r, int w, int f){
    int balance;
    if(r == nullptr){
        count++;
        r = (knode *)malloc(sizeof(knode));
        r->left = nullptr;
        r->right = nullptr;
        r->height = 0;
        r->whole = w;
        r->frac = f;
        return root;
    }else if(w < r->whole)
        r->right = insert(r->right, w, f);
    else if(w > r->whole)
        r->left = insert(r->left, w, f);
    else if(w == r->whole){
        if(f < r->frac)
            r->right = insert(r->right, w, f);
        else if(f > r->frac)
            r->left = insert(r->left, w, f);
    }
    r->height = max(r->left->height,r->right->height) + 1;
    balance = r->left->height - r->right->height;
    balance = 0;
    if(balance > k && (w < r->left->whole || (w == r->left->whole && f < r->left->frac)))
        return rightRotate(r);
    if(balance < -k && (w > r->right->whole || (w == r->right->whole && f > r->right->frac)))
        return leftRotate(r);
    if(balance > k && (w > r->left->whole || (w == r->left->whole && f >r->left->frac))){
        r->left = leftRotate(r->left);
        return rightRotate(r);
    }
    if(balance > k && (w > r->left->whole || (w == r->left->whole && f >r->left->frac))){
        r->right = rightRotate(r->right);
        return leftRotate(r);
    }
    return r;
};
knode* KAVL::del(knode *r, int w, int f){
    if(r == nullptr)
        return nullptr;
    else if(w < r->whole)
        r->right = del(r->right, w, f);
    else if(w > r->whole)
        r->left = del(r->left, w, f);
    else if(w == r->whole){
        if(f < r->frac)
            r->right = del(r->right, w, f);
        else if(f > r->frac)
            r->left = del(r->left, w, f);
        else{
            if(r->left == nullptr && r->right == nullptr){
                r = nullptr;
                delete r;
            }else if(r->left != nullptr){
                knode *tmp = inOrderPredecessor(r->left);
                r->whole = tmp->whole;
                r->frac = tmp->frac;
                r->left = del(r->left, tmp->whole, tmp->frac);
            }else if(r->right != nullptr){
                knode *tmp = r->right;
                r->whole = tmp->whole;
                r->frac = tmp->frac;
                r->left = tmp->left;
                r->right = tmp->right;
                delete tmp; 
            }
        }
    }   
    r->height = max(r->left->height,r->right->height) + 1;
    int balance = r->left->height - r->right->height;
    if(balance > k && (w < r->left->whole || (w == r->left->whole && f < r->left->frac)))
        return rightRotate(r);
    if(balance < -k && (w > r->right->whole || (w == r->right->whole && f > r->right->frac)))
        return leftRotate(r);
    if(balance > k && (w > r->left->whole || (w == r->left->whole && f >r->left->frac))){
        r->left = leftRotate(r->left);
        return rightRotate(r);
    }
    if(balance > k && (w > r->left->whole || (w == r->left->whole && f >r->left->frac))){
        r->right = rightRotate(r->right);
        return leftRotate(r);
    }
    return r;
};
knode* KAVL::rightRotate(knode *z){
    knode *y = z->left;
    knode *T3 = y->right;
    z->left = T3;
    y->right = z;
    z->height = max(z->left->height, z->right->height) + 1;
    y->height = max(y->left->height, y->right->height) + 1;
    return y;
};
knode* KAVL::leftRotate(knode *z){
    knode *y = z->right;
    knode *T2 = y->left;
    z->right = T2;
    y->left = z;
    z->height = max(z->left->height, z->right->height) + 1;
    y->height = max(y->left->height, y->right->height) + 1;
    return y;
};
knode* KAVL::inOrderPredecessor(knode *r){
    knode* tmp = r;
    while(tmp->right != nullptr)
        tmp = tmp->right;
    return tmp;
};
void KAVL::destruct(knode *r){
    if(r != nullptr){
        del(r->left,r->left->whole,r->left->frac);
        del(r->right,r->right->whole,r->right->frac);
        r = nullptr;
        delete r;
    }
};