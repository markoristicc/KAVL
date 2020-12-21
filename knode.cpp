#include "knode.h"

knode::knode(){
    whole = 0;
    frac = 0;
    height = 0;
};
knode::knode(int w, int f){
    whole = w;
    frac = f;
    height = 0;
};