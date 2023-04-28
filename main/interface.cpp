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
         "   /Users/Hazal/Desktop/sat-force/workspace/project/tests/test_6.txt" << "\n"
         "   tree : create a .root file from col" << "\n"
         
         << RESET << endl; 
};


functions fn; 
vector<vector<double> > output;
vector<vector<double> >* input; 


int interface(){
    string s;
    vector<string > commands = {"tree", "q"};


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

    if(s=="tree"){
        ifstream *file = new ifstream;
        string s;
        cout <<  YELLOW "Enter the full path of the data file: " RESET "\n"
             <<  "> " RESET << flush;
        getline(cin, s);
        file->open(s);
        if (!file->is_open()) {
            cout << RED "ERROR: Could not open the file." RESET << endl;
        }else {
            output = fn.reader(*file);
            if (output.size() != 0){
                cout << YELLOW "Enter a name for the output file: " RESET << flush;
                string filename; 
                getline(cin,filename);
                fn.outputToTree(isRoot(filename),&output);
            } 
        }
    }

    interface();


    return 0;
};
