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
         "Commands"                                                             << "\n"
         "   q    : exit"                                                       << "\n" 
         "   /Users/Hazal/Desktop/sat-force/workspace/project/tests/test_6.txt" << "\n"
         "   tree : create a .root file from col"                               << "\n"
         
         << RESET << endl; 
};


functions fn; 
ifstream *file = new ifstream;



int interface() {

    cout << YELLOW "Enter the full path of the data file: " RESET << endl;
    while (true){
        cout << YELLOW "> " RESET << flush;
        string filename;
        getline(cin, filename);
        ifstream *file = open_data_file(filename);
        if (file != nullptr) {
        cout << GREEN "Successfully opened the file." RESET << endl;
        }
        cout << RED "ERROR: Could not open the file." RESET << endl;
        clear_line(filename); // this does not work as expected :(
        
    }
    
    

    while (true) {
        print_options();   // print the options
        vector<string> commands = {"tree", "graph", "q"}; // list of commands
        string s = prompt_taker(commands);

        if (s == "tree") {


            vector<vector<double>> output = fn.reader(*file);

            if (output.size() != 0) {
                cout << YELLOW "Enter a name for the output file: " RESET << flush;
                string filename;
                cin >> filename; 
                fn.outputToTree( isRoot(filename) , &output);
                cout << GREEN "Successfully output data to n-tuples!" RESET << endl;
            }
        }

        if (s == "graph") {
            
            vector<vector<double>> output = fn.reader(*file);
            fn.graph(output);
        }
    }

    return 0;
};
