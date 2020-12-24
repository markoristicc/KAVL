#include "knode.h"

knode::knode(){
    whole = 0;
    frac = 0;
    height = 1;
    left = nullptr;
    right = nullptr;
};
knode::knode(int w, int f){
    whole = w;
    frac = f;
    height = 1;
    left = nullptr;
    right = nullptr;
};