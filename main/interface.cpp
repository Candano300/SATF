#include "essential.h"


using namespace std;



void greetings(){             
cout << BOLDORANGE << "\n"
    << "_____________________________________________"     << "\n"      
    << "                                             "     << "\n"    
    << "    _____      _______            ______     "     << "\n"
    << "   / ____|  /\\|__   __|          |  ____|   "     << "\n"
    << "  | (___   /  \\  | |     ______  | |__      "     << "\n"
    << "   \\___ \\ / /\\ \\ | |    |______| |  __|  "     << "\n"
    << "   ____) / ____ \\| |             | |        "     << "\n"
    << "  |_____/_/    \\_\\_|             |_|       "     << "\n"
    << "                                             "     << "\n"      
    << RESET << ORANGE 
    << "        SAT-Force Analysis Interface         "     << "\n"
    << RESET << BOLDORANGE
    << "_____________________________________________"     << "\n"      
    << RESET << endl;

 // Options:
         cout << YELLOW << 
         "Commands" << "\n"
         "   q    : exit"                         << "\n" 
         "   col  : extract .tsv file as vectors"  << "\n"
         "   root : create a .root file from col" << "\n"
         << RESET << endl; 
};


functions fn; 
vector<vector<double> > output;
vector<vector<double> >* input; 


int interface(){
    greetings();
    string s;
    vector<string > commands = {"col", "root", "q"};


    while (true){
        cout << "> "  << flush;
        getline(cin, s); 
        if (find(commands.begin(), commands.end(), s) != commands.end()){
            break;
        } else {
            cout << RED << " Invalid command." << RESET << endl;
        }
    }

    if (s == "q"){
        return 0;
    }
    if(s == "col") {
        output = fn.columns();
        input= &output;
    }
    if(s=="root"){
        fn.outputToTree("output.root",input);
    }


    return 0;
};
