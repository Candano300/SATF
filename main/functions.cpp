#include "essential.h"


using namespace std;

//columns returns transpose 
vector<vector<double> > functions::reader(ifstream &myfile) {
    // Some variables
    string input;
    string line;
    vector<vector<string> > matrix;
    vector<vector<double> > empty;
    ifstream file;
    int n_rows = 0;
    int n_columns = 0;


    while (getline(myfile, line)) {

        istringstream ss(line);
        string element;
        vector<string> row;

        while (ss >> element) {
            row.push_back(element);
        }
        matrix.push_back(row);
        n_rows++;
        if (n_columns == 0) {
            n_columns = row.size();
        }
    }

    myfile.close();

    // Transpose the matrix:
    vector<vector<double> > transpose(n_columns, vector<double>(n_rows));
    for (int i = 0; i < n_columns; i++){
        for (int j = 0; j < n_rows; j++){
            transpose[i][j] = stof(matrix[j][i]);
        }
    }

    cout << "\n" " " "# of rows      :  " <<  n_rows << "\n"
         <<      " " "# of columns   :  " <<  n_columns << "\n" << endl;


    return transpose;
};

void functions::outputToTree(string output_file, const vector<vector<double>>* input) {


    //----------PRELIMINARIES----------//

    // Get back to this if statement later. Since there is also an if statement in the interface.cpp
    //  one of them is unnecessary.

    if (input->empty()) {
        cout << RED << "outputToTree_ERROR: No input." << RESET << endl;
        return;
    }

    //convert output_file to const* char SignalTree =  &
    TString currentpath = gDirectory -> GetPath();
    string output_path = string(currentpath.Data()) + "/outputs/" + output_file;
    cout << currentpath << endl;
    const char *SignalTree = output_path.c_str();

    // --------------------------------//

    // Macro begins here:
    TFile  *file = new TFile(SignalTree, "RECREATE");
    TTree  *signaltree = new TTree("tree", "Signal Tree");


    //this got much more complicated than it needs to be. input = &output in the interface.cpp
    // get back here and find an easier soln.
    int n_rows = (*input)[0].size();
    int n_columns = input->size();
    vector<double> output_row(n_columns);

    // create branches
    for (int i = 0; i < n_columns; i++) {
        string branch_name = "branch_" + to_string(i);
        signaltree->Branch(branch_name.c_str(), &output_row[i]);
    }

    // fill the tree
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_columns; j++) {
            output_row[j] = (*input)[j][i];
        }
        signaltree->Fill();
    }

    file->Write();
    file->Close();
    
    cout << GREEN << "Successfully output data to tree!" << RESET << endl;


    
    

}

 



