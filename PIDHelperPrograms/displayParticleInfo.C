//----------------------------------------------------------------------------------

//displayParticleInfo(string filelist)
//Written by Andrew Boldy
//University of South Carolina
//Spring 2025

//----------------------------------------------------------------------------------

//Program that displays particle information of interest, specifically: PDG Number, Tracker Hits, Process Code, and Rank
//INCOMPLETE

//----------------------------------------------------------------------------------

//My Inclusions

//Standard Inclusions
#include <string>
#include <fstream>
#include <iostream>

//CERN ROOT Inclusions
#include <TFile.h>

//Mu2e Inclusions
#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"

//Personal Inclusions (if any)
#include "makeTChain.C"

void displayParticleInfo(std::string filelist)
{
  TChain* ntuple = makeTChain(filelist); //Pointing to the TChain created in the makeTChain program

  TObjArray* fileElements = ntuple->GetListOfFiles(); //constructs an array of files 

  int numFiles = fileElements->GetEntries(); //construct the number of files and outpu thte number of files 
  std::cout << "Number of files to work through: " << numFiles << std::endl;

  for (int i; i < numFiles; i++)
  {
    TFile* file = (TFile*)fileElements->At(i);
    std::string fileName = file->GetName();
    std::cout << "Working on file: " << fileName << std::endl;
    RooUtil util(fileName;

    int eventNumber = 
    for (int i_event = 0; i_event < eventNumber; i_event++)
    {
        const auto& event = util.GetEvent(i_event);
        if (event.trkmcsim != nullptr)
        {
            for (const auto& trkmcsim : *(event.trkmcsim))
            {
                //cout << "New Track!" << endl;
                for (const auto& sim : trkmcsim)
                {
                    cout << "Entry Number: " << i_event
                    << " PDG Number: " << sim.pdg
                    << " Tracker Hits: " << sim.nhits
                    << " Process Code: " << sim.startCode
                   << " Rank: " << sim.rank << endl;
                }
            }
        }
    }
  }
}
