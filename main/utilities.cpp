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
