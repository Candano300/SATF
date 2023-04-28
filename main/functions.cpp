#include "essential.h"


using namespace std;

//columns returns transpose 
vector<vector<double> > functions::columns() {
    // Some variables
    string input;
    string line;
    vector<vector<string> > matrix;
    vector<vector<double> > empty;
    ifstream file;
    int n_rows = 0;
    int n_columns = 0;


    // Ask for the file path
    while (true) {
        cout <<  YELLOW "Enter the full path of the data file: " RESET << endl;
        cout << YELLOW "> " RESET << flush;
        getline(cin, input);
       
        file.open(input);
        if (!file.is_open()) {
            cout << RED << "ERROR: Could not open the file." << RESET << endl;
            return empty;
        } else {
            break;
        }
    }
    // Actual function starts here:

    //Read each line and append them to a matrix
    while (getline(file, line)) {
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

    file.close();
    // Transpose the matrix
    // Define the transpose first
    vector<vector<double> > transpose(n_columns, vector<double>(n_rows));

    for (int i = 0; i < n_columns; i++){
        for (int j = 0; j < n_rows; j++){
            transpose[i][j] = stof(matrix[j][i]);
        }
    }

    cout << "# of rows      :  " <<  n_rows << endl;
    cout << "# of columns   :  " <<  n_columns << endl;


    return transpose;
};

void functions::outputToTree(string output_file, const vector<vector<double>>* input) {

    /// Get back to this if statement later, since there is also an if statement in the interface
    // this is kind of unnecessary? 
    if (input->empty()) {
        cout << RED << "outputToTree_ERROR: No input." << RESET << endl;
        return;
    }
    ///

    //convert output_file to const* char fileee =  &
    const char *fileee = output_file.c_str();
    TFile* file = new TFile(fileee, "RECREATE");
    TTree* tree = new TTree("tree", "tree");

    int n_columns = input->size();
    vector<double> output_row(n_columns);

    for (int i = 0; i < n_columns; i++) {
        string branch_name = "branch_" + to_string(i);
        tree->Branch(branch_name.c_str(), &output_row[i]);
    }

    int n_rows = (*input)[0].size();
    vector<vector<double>> output_branches(n_columns, vector<double>(n_rows));

    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_columns; j++) {
            output_branches[j][i] = (*input)[j][i];
        }
    }

    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_columns; j++) {
            output_row[j] = output_branches[j][i];
        }
        tree->Fill();
    }

    file->Write();
    file->Close();
    
    cout << GREEN << "Successfully output data to tree!" << RESET << endl;


    
    

}

 



