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

#ifndef essentialh
#define essentialh

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>


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
std::string isRoot(std::string s);