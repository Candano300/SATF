#include "essential.h"


using namespace std;


vector<vector<double> > functions::reader(ifstream &thefile) {
    string input;
    string line;
    vector<vector<string> > matrix;
    vector<vector<double> > empty;
    int n_rows = 0;
    int n_columns = 0;


    while (getline(thefile, line)) {

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

    thefile.close();

    // Transpose the matrix:
    vector<vector<double> > transpose(n_columns, vector<double>(n_rows));
    for (int i = 0; i < n_columns; i++){
        for (int j = 0; j < n_rows; j++){
            transpose[i][j] = stof(matrix[j][i]); // convert string to float
        }
    }

    cout << "\n" " " "# of rows      :  " <<  n_rows << "\n"
         <<      " " "# of columns   :  " <<  n_columns << "\n" << endl;


    return transpose;
};

void functions::outputToTree(string output_file, const vector<vector<double>>* input) {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    string outputpath_str = string(cwd) + "/outputs/" + output_file ;
    const char *outputpath = (outputpath_str).c_str();
    cout << outputpath << endl;



    // Macro begins here:
    TFile  *file = new TFile(outputpath, "RECREATE");
    TTree  *signaltree = new TTree("tree", "Signal Tree");


    //this got much more complicated than it needs to be. input = &output in the interface.cpp
    // get back here and find an easier soln.
    int n_rows = (*input)[0].size();
    int n_columns = input->size();
    vector<double> output_row(n_columns);

    // create branches
    for (int i = 0; i < n_columns; i++) {
        string branch_name = "branch_" + to_string(i+1);
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
    
}

void functions::graph(vector<vector<double> > input) {
    pid_t pid = fork();
    

    if (pid == 0) {    
    TApplication *myApp = new TApplication("myApp", 0, 0);



    int nPoints = input[0].size();
    vector<double> x(nPoints);
    for (int i = 0; i < nPoints; i++) {
        x[i] = i * 2.5e-9;
    }
    int no_of_columns = int(input.size());

    for (int j = 0; j < no_of_columns; j++) {
    //int j = 0;
    //while(j<no_of_columns){
        vector<double> y = input[j];
        string canvasname = "c" + to_string(j);
        string canvas = "Graph_" + to_string(j+1);
        TCanvas *c1 = new TCanvas(canvasname.c_str(), canvas.c_str(), 200, 10, 600, 400);
        c1->SetGrid();
        TGraph *graph = new TGraph(nPoints, &x[0], &y[0]);
        

        graph->GetXaxis()->SetTitle("Time (s)");
        graph->GetYaxis()->SetTitle("Voltage (V)");
        graph->SetMarkerStyle(8);
        graph->SetMarkerColor(kBlue);
        graph->SetMarkerSize(0.7);
        graph->SetLineColor(kBlue);
        graph->SetLineWidth(3);
        graph->SetTitle(Form("Voltage vs. Time (Column No. %d) ", j + 1));
        
        graph->Draw("ACP");



        c1->Draw();
        gStyle->SetOptFit(1111);
        //j++;
    }


        cout << YELLOW "Press enter to exit TBrowser" RESET << endl;
        myApp->Run();     
    }else if (pid > 0){

        // Parent process
        // Wait for user input to stop the child process
        
        getchar();

        // Send a signal to the child process to stop
        kill(pid, SIGTERM);

        // Wait for the child process to terminate

    }

}