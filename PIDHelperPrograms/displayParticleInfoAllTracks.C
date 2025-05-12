//----------------------------------------------------------------------------------

//displayParticleInfo(string filelist)
//Written by Andrew Boldy
//University of South Carolina
//Spring 2025

//----------------------------------------------------------------------------------

//Displays particle information for a list of files. 
//TESTING STAGE 
// 1) Make sure it prints out the number of files and the number of events in each file.
// 2) Check to make sure it prints the particle PDG number by event.
// 3) Check to see if it will print all the information for all the particles.

//----------------------------------------------------------------------------------

//My Inclusions

//Standard Inclusions
#include <string>
#include <fstream>
#include <iostream>

//CERN ROOT Inclusions

//Mu2e Inclusions
#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"
#include "EventNtuple/utils/rooutil/inc/common_cuts.hh"

//Personal Inclusions (if any)

void displayParticleInfoAllTracks(std::string filelist)
{
  ifstream listOfFiles(filelist);
  int fileCount = 0;
  string line;
  while (getline(listOfFiles,line))
  {
    if (!line.empty())
    {
      fileCount++;
    }
  }
  RooUtil util(filelist);
  int numEntries = util.GetNEvents();
  cout << "There are " << numEntries << " entries. Printing PDG, process code, number of hits, and rank for each." << endl;
  for (int i_event = 0; i_event < numEntries; i_event++)
  {
    auto event = util.GetEvent(i_event);
    //auto e_minus_tracks = event.GetTracks(is_e_minus);
    if (event.trkmcsim != nullptr) 
    {
      for (const auto& trkmcsim : *(event.trkmcsim)) 
      {
	cout << "New Track!" << endl;
        for (const auto& sim : trkmcsim) 
        {
          cout << "Entry Number: " << i_event + 1
               << " PDG Number: " << sim.pdg
               << " Tracker Hits: " << sim.nhits
               << " Process Code: " << sim.startCode
               << " Rank: " << sim.rank << endl; 
	}
      }
    }
  }
}
