#include "knode.h"

Node::Node(){
    whole = 0;
    frac = 0;
    height = 1;
    left = NULL;
    right = NULL;
};
Node::Node(int w, int f){
    whole = w;
    frac = f;
    height = 1;
    left = NULL;
    right = NULL;
};
~Node::Node(){
    delete right;
    delete left;
}