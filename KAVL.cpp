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
    if(m < 10*w + f)
        m = 10*w + f;
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
    knode *closest = tmp;
    int dif = abs(10*root->whole + root->frac - 10*w - f);
    int d = dif;
    while(tmp != nullptr){
        dif = abs(10*tmp->whole + tmp->frac - 10*w - f);
        if(d > dif){
            d = dif;
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
    c = count;
    inOrder(root);
};
void KAVL::inOrder(knode *r){
    if(r != nullptr){
        inOrder(r->left);
        cout<<r->whole<<"."<<r->frac;
        c--;
        if(c > 0)
            cout<<" ";
        inOrder(r->right);
    }
};
void KAVL::preprint(){
    preOrder(root);
}
void KAVL::preOrder(knode *r){
    if(r == nullptr)
        return;
    if(r != root)
        cout<<" ";
    cout<<r->whole<<"."<<r->frac;
    preOrder(r->left);
    preOrder(r->right);
};
knode* KAVL::insert(knode *r, int w, int f){
    if(r == nullptr){
        count++;
        knode *n;
        n = new knode(w,f);
        r = n;
        return r;
    }else if(w < r->whole)
        r->left = insert(r->left, w, f);
    else if(w > r->whole)
        r->right = insert(r->right, w, f);
    else if(w == r->whole){
        if(f < r->frac)
            r->left = insert(r->left, w, f);
        else if(f > r->frac)
            r->right = insert(r->right, w, f);
        else return r;
    }
    r->height = getHeight(r);
    int balance = getBalance(r);
    if(r->left != nullptr){
        if(balance > k && (w < r->left->whole || (w == r->left->whole && f < r->left->frac)))
            return rightRotate(r);
        if(balance > k && (w > r->left->whole || (w == r->left->whole && f > r->left->frac))){
            r->left = leftRotate(r->left);
            return rightRotate(r);
        }
    }
    if(r->right != nullptr){
        if(balance < -k && (w > r->right->whole || (w == r->right->whole && f > r->right->frac)))
            return leftRotate(r);
        if(balance < -k && (w < r->right->whole || (w == r->right->whole && f < r->right->frac))){
            r->right = rightRotate(r->right);
            return leftRotate(r);
        }
    }
    return r;
};
knode* KAVL::del(knode *r, int w, int f){
    if(r == nullptr )
        return r;
    else if(w < r->whole)
        r->left = del(r->left, w, f);
    else if(w > r->whole)
        r->right = del(r->right, w, f);
    else if(w == r->whole){
        if(f < r->frac)
            r->left = del(r->left, w, f);
        else if(f > r->frac)
            r->right = del(r->right, w, f);
        else{
            if(r->left != nullptr){
                knode *tmp;
                tmp = inOrderPredecessor(r->left);
                r->whole = tmp->whole;
                r->frac = tmp->frac;
                del(r->left, w, f);
            }else if(r->right != nullptr){
                count--;
                knode *tmp = new knode();
                tmp = r->right;
                r = nullptr;
                delete r;
                return tmp;
            }else{
                count--;
                delete r;
            }
        }
    }   
    r->height = getHeight(r);
    int balance = getBalance(r);
    if(r->left != nullptr){
        if(balance > k && (w < r->left->whole || (w == r->left->whole && f < r->left->frac)))
            return rightRotate(r);
        if(balance > k && (w > r->left->whole || (w == r->left->whole && f > r->left->frac))){
            r->left = leftRotate(r->left);
            return rightRotate(r);
        }
    }
    if(r->right != nullptr){
        if(balance < -k && (w > r->right->whole || (w == r->right->whole && f > r->right->frac)))
            return leftRotate(r);
        if(balance < -k && (w < r->right->whole || (w == r->right->whole && f < r->right->frac))){
            r->right = rightRotate(r->right);
            return leftRotate(r);
        }
    }
    return r;
};
knode* KAVL::rightRotate(knode *z){
    knode *y;
    knode *t;
    y = z->left;
    t = y->right;
    y->right = z;
    z->left = t;
    return y; 
};
knode* KAVL::leftRotate(knode *z){
    knode *y;
    knode *t;
    y = z->right;
    t = y->left;
    y->left = z;
    z->right = t;
    return y; 
};
knode* KAVL::inOrderPredecessor(knode *r){
    knode* tmp;
    tmp = r;
    while(tmp->right != nullptr)
        tmp = tmp->right;
    return tmp;
};
int KAVL::getHeight(knode *r){
    if(r->left != nullptr && r->right != nullptr)
        return max(r->left->height, r->right->height)+1;
    else if(r->left == nullptr)
        return r->right->height + 1;
    else if(r->right == nullptr)
        return r->left->height + 1;
    else return 1;
};
int KAVL::getBalance(knode *r){
    if(r->left != nullptr && r->right != nullptr)
        return r->left->height - r->right->height;
    else if(r->left == nullptr)
        return -1*(r->right->height);
    else if(r->right == nullptr)
        return r->left->height;
    else return 0;
}
void KAVL::destruct(knode *r){
    if(r != nullptr){
        destruct(r->left);
        destruct(r->right);
        r = nullptr;
        delete r;
    }
};