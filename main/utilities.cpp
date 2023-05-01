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
    string currentpath = string(cwd) + "/outputs/" + nameofthefile;
    const char *currentpath_char = (currentpath).c_str();
    return currentpath_char;
}


string testpath(){

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    string testpath = string(cwd) + "/tests/" + "test_6.txt";
    return testpath;
}


// this will prepare the data file for the program to read, if not, will return a nullptr
ifstream *open_data_file(string filename){
    ifstream *file = new ifstream;
    if (filename == "q"){
        exit(0);
    }
    file->open(filename);

    if (file->is_open()) {
        return file; 
    }

    delete file; 
    return nullptr; 

}


string prompt_taker(vector<string> command_list){
    string s;
    cout << YELLOW "> " RESET << flush;
    getline(cin, s);

    if(s == "q"){
        exit(0);
    }else if (find(command_list.begin(), command_list.end(), s) == command_list.end()) {
        cout << RED "ERROR: Invalid command." RESET << endl;
    }
    return s;
}



void print_options(){
        cout << YELLOW << 
         "Commands"                                                             << "\n"
         "   q    : exit"                                                       << "\n" 
         "   /Users/Hazal/Desktop/sat-force/workspace/project/tests/test_6.txt" << "\n"
         "   tree : create a .root file from col"                               << "\n"
         
         << RESET << endl; 
}


void clear_line(string input){
            std::cout << "\033[2K"; // Clear the current line
            std::cout << "\033[1G"; // Move the cursor to the beginning of the line
            for (int i = 0; i < int(input.length() ); i++) {
                std::cout << "\b \b" << std::flush; // Move the cursor back and print a space to overwrite the wrong input
            }
}