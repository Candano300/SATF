// COLORS

#ifndef COLORS
#define COLORS

#define RESET "\033[0m"
#define WHITE "\033[1;29m"
#define RED "\033[31m"
#define BOLDORANGE "\033[1;38;5;202m"
#define ORANGE "\033[38;5;202m"
#define BLUE "\033[34m" 
#define YELLOW "\033[33m" 
#define BOLDYELLOW "\033[1;33m"
#define GREEN "\033[32m"

#endif 

// BASIC LIBRARIES

#ifndef basich
#define basich

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>


#endif

// ROOT HEADERS

#ifndef rooth
#define rooth

#include "TDirectory.h"
#include "TFile.h"
#include "TTree.h"
#include <TMath.h>
#include "TString.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TApplication.h"
#include "TBrowser.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TStyle.h"

#endif

// DEFINITION OF FUNCTIONS

#ifndef functionsh
#define functionsh


class functions{
public: 
    std::vector<std::vector<double> > reader(std::ifstream &myfile);
    void outputToTree(std::string output_file, const std::vector<std::vector<double>>* input);
    void graph(std::vector<std::vector<double > > input);
};


#endif

// INTERFACE
int interface();
void greetings();

// UTILITIES
#ifndef utilitiesh
#define utilitiesh

std::string isRoot(std::string s); // checks whether the input is a .root file or not, if it is not it will add .root extension to the end of the input.
const char *initializepath(std::string nameofthefile);  // returns the current path of the program
std::string testpath(); // returns the path of the test files
std::ifstream* open_data_file(std::string filename); // asks the user to enter the full path of the data file
std::string prompt_taker(std::vector<std::string> command_list); // takes the input from the user and returns it as a string
void print_options(); // prints the options
void clear_line(std::string filename); // clears the line

#endif