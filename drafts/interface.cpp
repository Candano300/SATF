#include "essential.h"

using namespace std;
namespace fs = std::filesystem;
functions fn; 


int interface(){
    
    ifstream *datafile;
    vector<vector<double>> output;
    vector<string> file_list; // list of files to be opened within the directory 


    printer(0);
    printer(1);

    cout << YELLOW "> " RESET << flush;
    string filename;
    getline(cin, filename);

    // check if it is a .txt file first! 
    string extension = filename.substr(filename.length() - 4);
    if( filename.substr(filename.length() - 4) == ".txt"){   
        datafile = open_data_file(filename);
        if (datafile != nullptr) {
            cout << "\n" GREEN "Successfully opened the file." RESET << endl;
            output = fn.reader(*datafile);
            //break;
        }
        cout << RED "ERROR: Could not open the file." RESET << endl;   
    }
    // if it is not a file, then it must be a directory, start a for loop that opens all the files one by one within the directory
    else{
        
        // check if the directory exists
        if (fs::exists(filename)){
            cout << "\n" GREEN "Successfully opened the directory." RESET << endl;
            // start a for loop that opens all the files one by one within the directory

            for (const auto & entry : fs::directory_iterator(filename)){
                string file = entry.path();
                datafile = open_data_file(file);
                if (datafile != nullptr) {
                    // print the name of the file
                    cout << YELLOW << "File name: " << RESET << file << endl;
                    file_list.push_back(file);
                }
            }
            
        }
        else{
            cout << RED "ERROR: The directory does not exist." RESET << endl;
        }
    }


// create the output directory 
string path_of_output_directory = string(fs::current_path()) + "/outputs/";
fs::create_directory(path_of_output_directory);


for (int i = 0; i < file_list.size(); i++){

    // create a directory for each file
    string file = file_list[i];
    string outputname = file.substr(0, file.length() - 4);
    // get the name of the file by searching for the first "/" character, starting from the end of the string 
    int index = outputname.find_last_of("/");
    outputname = outputname.substr(index + 1);
    
    string outputpath = string(fs::current_path()) + "/outputs/" + outputname;
    fs::create_directory(outputpath);

    datafile = open_data_file(file);
    if (datafile != nullptr) {
        cout << "\n" GREEN "Successfully opened the file: " RESET << i << endl;
        cout << "\n" YELLOW "File name: " << RESET << outputname << endl;

        // Skipping the first 24 lines of the oscilloscope data file since it is not what we are in need of. Also, fn.reader can only read double values.
        for (int i = 0; i < 24; ++i) {
            string line;
            getline(*datafile, line);
        }

        output = fn.reader(*datafile);
        fn.graph(output, outputpath);

    }else{
    cout << RED "ERROR: Could not open the file." RESET << endl;
    }


}

    return 0;
}

    /*
    vector<string> commands = {"tree", "graph"}; // list of commands 
    string s = prompt_taker(commands);

    if (s == "tree") {
            cout << YELLOW "Enter a name for the output file: " RESET << flush;
            string outputname;
            getline(cin, outputname);
            fn.outputToTree(outputname , &output);
            cout << GREEN "Data is written to n-tuples succesfully" RESET << endl;
    }
    if (s == "graph") {
        cout << "\n" ;
        fn.graph(output);
    }
}

*/