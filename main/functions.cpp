#include "essential.h"


using namespace std;


vector<vector<double> > functions::reader(ifstream &thefile) {

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

    // Transpose the matrix:
    vector<vector<double> > transpose(n_columns, vector<double>(n_rows));
    for (int i = 0; i < n_columns; i++){
        for (int j = 0; j < n_rows; j++){
            transpose[i][j] = stof(matrix[j][i]); // convert string to float values
        }
    }

    cout << "\n" " " "# of rows      :  " <<  n_rows << "\n"
         <<      " " "# of columns   :  " <<  n_columns << "\n" << endl;


    return transpose;
};

void functions::outputToTree(string output_file, const vector<vector<double>> *input) {
    const char* outputpath = initializepath(output_file);


    // Macro begins here:
    TFile  *file = new TFile(outputpath, "RECREATE");
    TTree  *signaltree = new TTree("tree", "Signal Tree");


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

    // I had to use a parent child process in here because 
    // myApp->Run() can't be executed otherwise. 

    initializepath("graph.root");
    TFile *f = new TFile("output.root", "RECREATE");
    double integral = 0.0;

    pid_t pid = fork();

        

        
    // parent    
    if (pid > 0){ 

        getchar();
        cout << "parent" <<  integral << endl; 

    }
        


    //child
    if (pid == 0){ 
        TApplication *myApp = new TApplication("myApp", 0, 0);


        int no_of_datas = input[0].size();
        vector<double> x_axis(no_of_datas); // time
        for (int i = 0; i < no_of_datas; i++) {
            x_axis[i] = i * 2.5e-9;
        }
        
        int no_of_datasets = int(input.size());

        for (int j = 0; j < no_of_datasets; j++) {

            vector<double> y_axis = input[j]; // voltage
            string canvasname = "c" + to_string(j);
            string canvas = "Graph_" + to_string(j+1);
            
            TCanvas *c1 = new TCanvas(canvasname.c_str(), canvas.c_str(), 200, 10, 600, 400);
            c1->SetGrid();
            TGraph *graph = new TGraph(no_of_datas, &x_axis[0], &y_axis[0]);
            

            graph->GetXaxis()->SetTitle("Time (s)");
            graph->GetYaxis()->SetTitle("Voltage (V)");
            graph->SetMarkerStyle(8);
            graph->SetMarkerColor(kBlue);
            graph->SetMarkerSize(0.7);
            graph->SetLineColor(kBlue);
            graph->SetLineWidth(3);

            // title name can be an input? check
            graph->SetTitle(Form("Voltage vs. Time  (No. %d) ", j + 1));
            
            graph->Draw("ACP");



            c1->Draw();
            gStyle->SetOptFit(1111);
            

            // find the integral of the graph:
            int     n = graph->GetN();
            double *x = graph->GetX();
            double *y = graph->GetY();


            //take the integral via trapezoidal rule: 
            for (int i = 1; i < n; i++) {
                double dx = x[i] - x[i-1];
                double area = (y[i] + y[i-1]) / 2.0 * dx; 
                //
                integral += area;
            };
            
            cout << "Data " << setw(2) << j+1 << " : " << setw(2) <<  integral << endl;
            //

                      
        }

            cout << YELLOW "\nPress any key to exit to the main menu" RESET << endl;
            myApp->Run();


    }

    cout << "parent is dead. check if the child is living" << endl;
    cout << integral; 
    getchar();
    kill( pid, SIGTERM);
    cout << "Exiting..." << endl;







}