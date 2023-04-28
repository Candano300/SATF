#include "class.h"

functions fn;

using namespace std;


functions func;

int interface(){
    string s;   
    while (true){
        cout << "> " << flush;
        getline(cin, s); 
        if (s == "q"){
            return 0;
        }
        if(s =="q") {
            fn.columns();
            
        }
    }
    





    return 0;
};