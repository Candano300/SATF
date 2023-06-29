#include "essential.h" 

using namespace std; 


// INITIALIZE PATH FUNC. STARTS HERE

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
    nameofthefile = isRoot(nameofthefile);
    string outputpath = string(cwd) + "/outputs/" + nameofthefile;
    const char *outputpath_char = (outputpath).c_str();
    return outputpath_char;
}

// END OF INITIALIZE PATH FUNC.



// this will prepare the data file for the program to read, if not, will return a nullptr
ifstream *open_data_file(string filename){
    ifstream *file = new ifstream;
    file->open(filename);
    if (file->is_open()) {
        return file; 
    }else{
        delete file; 
        return nullptr; 
    }

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

        cout << YELLOW << "\nENTER: \n"
                "- Full path of the directory that contains the data files \n"
                "OR \n"
                "- Full path of the data file .txt \n"
            << RESET << endl;

        break;
    };


}


