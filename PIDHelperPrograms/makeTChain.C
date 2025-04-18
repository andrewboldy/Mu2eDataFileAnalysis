//----------------------------------------------------------------------------------

//makeTChain(string filelist)
//Written by Andrew Boldy
//University of South Carolina
//Spring 2025

//----------------------------------------------------------------------------------

//Creates a TChain, specifically for TTrees EventNtuple/ntuple

//----------------------------------------------------------------------------------

//My Inclusions

//Standard Inclusions
#include <string>
#include <fstream>
#include <iostream>

//CERN ROOT Inclusions
#include <TChain.h>

//Personal Inclusions (if any)


//----------------------------------------------------------------------------------
TChain* makeTChain(std::string filelist)
{
    TChain* ntuple = new TChain("EventNtuple/ntuple");

    std::ifstream input_filelist(filelist);  // open the file

    if (input_filelist.is_open())
    {
        std::string filename;
        while (getline(input_filelist, filename))
        {
            ntuple->Add(filename.c_str());  // add each line as a file to the chain
        }
        input_filelist.close();
    }
    else
    {
        std::cerr << "Error: could not open filelist " << filelist << std::endl;
    }

    std::cout << "Number of entries in the TChain: " << ntuple->GetEntries() << std::endl;
    return ntuple;
}

