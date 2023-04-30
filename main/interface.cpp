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
ifstream *file = new ifstream;



int interface() {
    vector<string> commands = {"tree", "graph", "q"}; // list of commands
    string s;

    while (true) {
        cout << YELLOW "> " RESET << flush;
        getline(cin, s);

        if (find(commands.begin(), commands.end(), s) == commands.end()) {
            cout << RED "ERROR: Invalid command." RESET << endl;
            continue; 
        }

        if (s == "q") {
            return 0;
        }

        if (s == "tree") {
            string filename;
            cout << YELLOW "Enter the full path of the data file: " RESET << flush;
            getline(cin, filename);

            file->open(filename);

            if (!file->is_open()) {
                cout << RED "ERROR: Could not open the file." RESET << endl;
                continue; 
            }

            vector<vector<double>> output = fn.reader(*file);

            if (output.size() != 0) {
                cout << YELLOW "Enter a name for the output file: " RESET << flush;
                getline(cin, filename);

                fn.outputToTree(isRoot(filename), &output);
                cout << GREEN "Successfully output data to n-tuples!" RESET << endl;
            }
        }

        if (s == "graph") {
            file->open("/Users/Hazal/Desktop/sat-force/workspace/project/tests/test_6.txt");
            vector<vector<double>> output = fn.reader(*file);
            fn.graph(output);
        }
    }

    return 0;
};
