#include "essential.h"

using namespace std;

functions fn; 
int interface() {
    
    ifstream *dfile;
    vector<vector<double>> output;

    //printer(0);

    printer(1);
    
    while (true){
        cout << YELLOW "> " RESET << flush;
        string filename;
        getline(cin, filename);
        dfile = open_data_file(filename);
        if (dfile != nullptr) {
        cout << "\n" GREEN "Successfully opened the file." RESET << endl;
        output = fn.reader(*dfile);
        break;
        }
        cout << RED "ERROR: Could not open the file." RESET << endl;   
    }
    
    printer(2);  

    while (true) {
        vector<string> commands = {"tree", "graph"}; // list of commands
        string s = prompt_taker(commands);

        if (s == "tree") {
                cout << YELLOW "Enter a name for the output file: " RESET << flush;
                string filename;
                getline(cin,filename);
                fn.outputToTree( isRoot(filename) , &output);
                cout << GREEN "Data is written to n-tuples succesfully" RESET << endl;
        }
        if (s == "graph") {
            cout << "\n" ;
            fn.graph(output);
        }
    }

    return 0;
};
