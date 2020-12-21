#include  "knode.h"
#include  "KAVL.h"
#include <iostream>
using namespace std;

int main(){
    KAVL t = KAVL(3);
    t.ins(9,9);
    t.preprint();
    t.inprint();
    return 0;
}