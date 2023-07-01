#include "essential.h"

using namespace std;
namespace fs = std::filesystem;

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

vector<vector<double> > reader(ifstream &thefile) {

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
}

void graph(vector<vector<double> > input , string output_path) {

    int no_of_datasets = int(input.size());
    vector<double> peak_voltages(no_of_datasets);
    vector<double> peak_time;
    vector<double> integrals;


    int no_of_datas = input[0].size();
    vector<double> x_axis(no_of_datas); // time
    for (int i = 0; i < no_of_datas; i++) {
        x_axis[i] = i * 2.5e-9;  // 2.5 ns is the sampling time
    }

    //const char* newoutputpath = output_root.c_str();
    //TFile *f = new TFile(newoutputpath, "RECREATE");


    for (int j = 0; j < no_of_datasets; j++) { 
        //string output_root = "/Users/Hazal/Desktop/output/graph_" + to_string(j+1) + ".root";
        //const char* newoutputpath = output_root.c_str();
        vector<double> y_axis = input[j]; 
        auto it = min_element(y_axis.begin(), y_axis.end());
        peak_voltages[j] = *it; // find the peak y value
        int min_index = distance(y_axis.begin(), it); 
        peak_time.push_back(x_axis[min_index]);
        //

        string canvasname = "c" + to_string(j);
        string canvas = "Graph_" + to_string(j+1);
        TCanvas *c1 = new TCanvas(canvasname.c_str(), canvas.c_str(), 200, 10, 600, 400);
        TGraph  *graph = new TGraph(no_of_datas, &x_axis[0], &y_axis[0]);
        c1->SetGrid();
        c1->Draw();


        graph->SetTitle(Form("Voltage vs. Time  (No. %d) ", j + 1));
        graph->GetXaxis()->SetTitle("Time (s)");
        graph->GetYaxis()->SetTitle("Voltage (V)");
        graph->SetMarkerStyle(8);
        graph->SetMarkerColor(kBlue);
        graph->SetMarkerSize(0.7);
        graph->SetLineColor(kBlue);
        graph->SetLineWidth(3);
        graph->Draw("ACP");


        gStyle->SetOptFit(1111);

        string output = output_path + "/graph_" + to_string(j+1) + ".root";
        c1-> SaveAs(output.c_str());

        // find the integral of the graph via trapezoidal rule (for now):
        int     n = graph->GetN();
        double *x = graph->GetX();
        double *y = graph->GetY();
        double integral = 0.0;
        for (int i = 1; i < n; i++) {
            double dx = x[i] - x[i-1];
            double area = (y[i] + y[i-1]) / 2.0 * dx; 
            integral += area;
        }
        integrals.push_back(integral); 
    }

    cout << "\n\n\n";
    cout << "  Graph     Integrals (Wb)      Peaks (V)      Time (s)" << "\n"
        << "--------------------------------------------------------" << endl;
    for(int i = 0; i < no_of_datasets; i++){
    cout << setw(4) << i+1 << "       " << setw(12) << integrals[i] << "       " << setw(9) << peak_voltages[i] 
    << "       "<< setw(6) << peak_time[i] << endl;
    }
}


int main(){

    ifstream *datafile;
    vector<vector<double>> output;


    string path_of_output_directory = string(fs::current_path()) + "/outputs/";
    fs::create_directory(path_of_output_directory);

    // Check if directory creation was successful
    if (!fs::exists(path_of_output_directory)) {
        cout << RED "ERROR: Failed to create the output directory." RESET << endl;
        return 0;
    }



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



    cout << YELLOW << "Enter the path of the .txt file:" << RESET << endl;

    string filename;
    while (true) {
        cout << YELLOW "> " RESET << flush;
        getline(cin, filename);
        string extension = filename.substr(filename.length() - 4);
        if (extension == ".txt") {
            break;
        } else {
            cout << RED "ERROR: Please enter a .txt file." RESET << endl;
        }
    }

    datafile = open_data_file(filename);
    if (datafile != nullptr) {
        cout << "\n" GREEN "Successfully opened the file." RESET << endl;
        cout << YELLOW << "File name: " << RESET << filename << endl;
        
        // Skipping the first 24 lines of the oscilloscope data file since it is not what we need
        for (int i = 0; i < 24; ++i) {
            string line;
            getline(*datafile, line);
        }

        output = reader(*datafile);

        string outputname = filename.substr(0, filename.length() - 4);
        int index = outputname.find_last_of("/");
        outputname = outputname.substr(index + 1);
        string outputpath = string(fs::current_path()) + "/outputs/" + outputname;
        fs::create_directory(outputpath);
        graph(output, outputpath);
        cout << GREEN <<  "Output is saved to the directory: " << RESET << outputpath << endl;



    }else{
    cout << RED "ERROR: Could not open the file." RESET << endl;   
    }
    

    


    return 0;
}
