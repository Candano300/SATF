#ifndef  COLORS
#define COLORS

#define RESET "\033[0m"
#define WHITE "\033[1;29m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"

#endif 

//////////////////////////////

#ifndef essentialh
#define essentialh

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "TFile.h"
#include <TMath.h>

#endif

//////////////////////////////

#ifndef rooth
#define rooth

#include "TFile.h"
#include "TTree.h"

#endif

//////////////////////////////


#ifndef functionsh
#define functionsh

int interface();

class functions{
public: 
    std::vector<std::vector<double> > columns();
    void greetings();
    void outputToTree(const char* output_file, const std::vector<std::vector<double>>* input);
};


#endif