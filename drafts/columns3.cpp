cout << WHITE << "\nSAT-FORCE SIGNAL ANALYSIS" << RESET << endl; 
cout << "(Enter "".q"" to quit the program)\n" << endl; 


while (true){
    cout << "Enter the full path of the data file: "  << endl;
    cout << "> " << flush;
    cin >> s;
    ifstream file(s);


    if (s == ".q"){
        return 0;
    }
    if ( !file.is_open() ){
        cout << RED << "ERROR: Could not open the file."  << RESET << endl;
    }else{
        break;
    }
    }




}


int main() {

    columns();

    
    
    return 0;
}
