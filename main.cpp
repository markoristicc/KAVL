#include "knode.h"
#include "KAVL.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
    int k, w=0, f=0;
    knode* a;
    if(argv[1] == NULL)
        cerr<<"please input the correct amount of arguments"<<endl;
    string s = argv[1];
    s += ", ";
    string parse = ", ";
    size_t position = s.find(parse);
    size_t pos = 0;
    string tmp = s.substr(0,position);
    string tmp2 = "";
    k = stoi(tmp);
    KAVL tree = KAVL(k);
    s.erase(0, position+2);
    while((position = s.find(parse)) != string::npos){
        tmp = s.substr(0,position);
        s.erase(0, position + 2);
        if(tmp == "in_order"){
            tree.inprint();
            cout<<endl;
        }else if(tmp == "pre_order"){
            tree.preprint();
            cout<<endl;
        }else{
            tmp+=" ";
            pos = tmp.find(" ");
            tmp2 = tmp.substr(0,pos);
            tmp.erase(0,pos+1);
            if(tmp2 == "insert"){
                pos = tmp.find(" ");
                w = stoi(tmp.substr(0, pos));
                tmp.erase(0,pos+1);
                pos = tmp.find(" ");
                f = stoi(tmp.substr(0, pos));
                tmp.erase(0,pos+1);
                if(tree.ins(w,f))
                    cout<<w<<"."<<f<<" inserted"<<endl;
            }if(tmp2 == "search"){
                pos = tmp.find(" ");
                w = stoi(tmp.substr(0, pos));
                tmp.erase(0,pos+1);
                pos = tmp.find(" ");
                f = stoi(tmp.substr(0, pos));
                tmp.erase(0,pos+1);
                if(tree.search(w,f))
                    cout<<w<<"."<<f<<" found"<<endl;
                else cout<<w<<"."<<f<<" not found"<<endl;
            }if(tmp2 == "approx_search"){
                pos = tmp.find(" ");
                w = stoi(tmp.substr(0, pos));
                tmp.erase(0,pos+1);
                pos = tmp.find(" ");
                f = stoi(tmp.substr(0, pos));
                tmp.erase(0,pos+1);
                a = tree.approx(w,f);
                cout<<"closest to "<<w<<"."<<f<<" is "<<a->whole<<"."<<a->frac<<endl;
            }if(tmp2 == "delete"){
                pos = tmp.find(" ");
                w = stoi(tmp.substr(0, pos));
                tmp.erase(0,pos+1);
                pos = tmp.find(" ");
                f = stoi(tmp.substr(0, pos));
                tmp.erase(0,pos+1);
                if(tree.del(w,f))
                    cout<<w<<"."<<f<<" deleted"<<endl;
            }
        }
    }
    return 0; //maybe not the best code but it works, i suppose
}