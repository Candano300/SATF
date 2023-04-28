#include "essential.h"

functions fn; 

using namespace std;

std::vector<std::vector<double> > output ;


int interface(){
    string s;   
    while (true){
        cout << "> " << flush;
        getline(cin, s); 
        if (s == "q"){
            return 0;
        }
        if(s == "col") {
            output = fn.columns();
            std::vector<std::vector<double> >* input= &output;
            fn.outputToTree("output.root",input);
        }
    }
    





    return 0;
};