//----------------------------------------------------------------------------------

//displayParticleInfo(string filelist)
//Written by Andrew Boldy
//University of South Carolina
//Spring/Summer 2025

//----------------------------------------------------------------------------------

//Displays particle information for a list of files, specifically PDG number, number of hits on the detector, process code, and rank.
//Must run in compile mode using the command: root -l 'displayParticleInfo.C++("/exp/mu2e/data/users/aboldy/myfiles.list")'
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

void displayParticleInfo(std::string filelist)
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
  int numEvents = util.GetNEvents();
  cout << "There are " << numEvents << " entries. Printing PDG, process code, number of hits, and rank for each." << endl;
  for (int i_event = 0; i_event < numEvents; i_event++)
  {
    auto& event = util.GetEvent(i_event);
    auto e_minus_tracks = event.GetTracks(is_e_minus);
    for (auto& track : e_minus_tracks)
    {
    if (track.trkmcsim != nullptr)
    {
      cout << "New Track!" << endl;
      for (const auto& mctrack : *(track.trkmcsim))
      {
          cout << "Entry Number: " << i_event
               << "; Geneology Particle PDG Number: " << mctrack.pdg
               << "; Tracker Hits: " << mctrack.nhits
               << "; Process Code: " << mctrack.startCode
               << "; Rank: " << mctrack.rank << endl;
        }
      }
    }
  }
}
