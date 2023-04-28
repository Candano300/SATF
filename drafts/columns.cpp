#include "columns.h"

using namespace std;

vector<vector<string> >  columns(){

    string s;
    ifstream file(s);
    string line;
    vector<vector<string> > mylist;
    vector<vector<string> > empty;


    while (true){
        cout << "Enter the full path of the data file: "  << endl;
        cout << "> " << flush;
        cin >> s;
        if (s == ".q"){
            return empty;
        }
        if ( !file.is_open() ){
            cout << RED << "ERROR: Could not open the file."  << RESET << endl;
        }else{
            break;
        }
    }



    while (getline(file, line)) {
        istringstream ss(line);
        string word;
        vector<string> row;
        while (ss >> word) {
            row.push_back(word);
        }
        mylist.push_back(row);
    }
   
    int line_count = mylist.size(); // line_count = # of rows
   
    cout << WHITE << "The number of rows in the data: " << RESET << line_count << endl;
   
    vector<vector<string> > result(mylist[0].size()); //mylist[0].size() = # of columns. Initialize a 
    for (int i = 0; i < mylist[0].size(); i++) {
        for (int j = 0; j < mylist.size(); j++) {
            result[i].push_back(mylist[j][i]);
        }
    }

    cout << WHITE << result[0].back() << RESET << endl;
    




    return result;
};

