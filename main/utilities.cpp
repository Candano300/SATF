#include "essential.h" 

using namespace std; 

// This function will check whether the input is a .root file or not, if it is not it will
// add .root extension to the end of the input.

string isRoot(string nameofthefile){
    // Get back here later: 
    //str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    if(nameofthefile != ""){
        string extension = nameofthefile.substr(nameofthefile.length() - 5);
        if(extension != ".root"){
            return nameofthefile + ".root";
        }
    }
    return "signal_tree.root" ;

}


const char *initializepath(string nameofthefile){
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    string outputpath = string(cwd) + "/outputs/" + nameofthefile;
    cout << "Output: " << outputpath << endl;
    const char *outputpath_char = (outputpath).c_str();
    return outputpath_char;
}


// this will evolve into a function that scans every file within a given directory 
string testpath(){
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    string testpath = string(cwd) + "/tests/" + "test_6.txt";
    cout << testpath << endl;
    return testpath;
}


// this will prepare the data file for the program to read, if not, will return a nullptr
ifstream *open_data_file(string filename){
    
    
    if (filename == "q"){
        exit(0);
    }

    if (filename == "test"){
        filename = testpath();
    }

    
    ifstream *file = new ifstream;
    file->open(filename);
    if (file->is_open()) {
        return file; 
    }else{

    delete file; 
    return nullptr; 

    }

}


string prompt_taker(vector<string> command_list){
    string s;
    cout << YELLOW "> " RESET << flush;
    getline(cin, s);
    auto it = find(command_list.begin(), command_list.end(), s);
    if(s == "q"){
        //the file has to be closed before quitting though.
        //how to do that?
        exit(0);
    
    
    }else if ( it == command_list.end()) {
        cout << RED "ERROR: Invalid command." RESET << endl;
    }
    return s;
}



void printer(int option){
        switch(option){

        case 0: 
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

            break;



        
        case 1: 

            cout <<  "\nENTER: \n"
                    "- Path of the data file, or " "\"test\" to open the test file." "\n"
                    "- \"q\" to quit" "\n" 
                << RESET << endl;

            break;

        case 2:

            cout << "\n" YELLOW << 
            "Commands"                                                             << "\n"
            "   q    : exit"                                                       << "\n" 
            "   tree : create a .root file"                                        << "\n"
            "   graph: display TGraphs on the screen"                              << "\n" 
            << RESET << endl;   

             break;

        }
}

