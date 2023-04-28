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
         "   /Users/Hazal/Desktop/sat-force/workspace/project/tests/test_6.txt" << "\n"
         "   tree : create a .root file from col" << "\n"
         
         << RESET << endl; 
};


functions fn; 
vector<vector<double> > output;
vector<vector<double> >* input; 


int interface(){
    string s;
    vector<string > commands = {"col", "tree", "q"};


    while (true){
        cout << YELLOW "> " RESET << flush;
        getline(cin, s); 
        if (find(commands.begin(), commands.end(), s) != commands.end()){
            break;
        } else {
            cout << RED << "ERROR: Invalid command." << RESET << endl;
        }
    }
    
    if (s == "q"){
        return 0;
    }
    if(s == "col") {
        fn.columns();

    }
    if(s=="tree"){
        output = fn.columns();
        if (output.size() != 0){
            input= &output; // input is now equal to the adress of output
            string filename;
            cout << YELLOW "Enter a name for the output file: " RESET << flush;
            getline(cin,filename);
            string fileinput;
            fileinput = isRoot(filename);
            fn.outputToTree(fileinput,input);
        }

    }

    interface();


    return 0;
};
