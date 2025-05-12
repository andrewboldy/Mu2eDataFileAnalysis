//----------------------------------------------------------------------------------

//displayParticleMomentum(string filelist)
//Written by Andrew Boldy
//University of South Carolina
//Summer 2025

//----------------------------------------------------------------------------------

//Displays particle momentum in MeV/c for a list of files.
//Testing
// 1) Display the number of files that are in the list
// 2)
//Need to run this using the command:  root -l 'displayParticleMomentum.C++("/exp/mu2e/data/users/aboldy/myfiles.list")'
//----------------------------------------------------------------------------------

//My Inclusions

//Standard Inclusions
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

//CERN ROOT Inclusions

//Mu2e Inclusions
#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"
#include "EventNtuple/utils/rooutil/inc/common_cuts.hh"
//Personal Inclusions (if any)

void displayParticleMomentum(string filelist)
{
  //Print out the number of files
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
  cout << "There are " << fileCount << " files in the list." << endl;
  RooUtil util(filelist);
  int numEvents = util.GetNEvents();
  cout << "There are " << numEvents << " entries. Calculating the maximum and minimum momenta for each particle type of interest." << endl;

  //Starting values:

  //Starting Maxes (all zero)
  float protonMaxStartMom = 0.0f;
  float protonMaxEndMom   = 0.0f;
  float eMinusMaxStartMom = 0.0f;
  float eMinusMaxEndMom   = 0.0f;
  float ePlusMaxStartMom  = 0.0f;
  float ePlusMaxEndMom    = 0.0f;
  float muMaxStartMom     = 0.0f;
  float muMaxEndMom       = 0.0f;
  float deutMaxStartMom   = 0.0f;
  float deutMaxEndMom     = 0.0f;

  //Starting Mins (largest possible float, thank you internet for this format)
  const float BIG = numeric_limits<float>::max();

  float protonMinStartMom = BIG;
  float protonMinEndMom   = BIG;
  float eMinusMinStartMom = BIG;
  float eMinusMinEndMom   = BIG;
  float ePlusMinStartMom  = BIG;
  float ePlusMinEndMom    = BIG;
  float muMinStartMom     = BIG;
  float muMinEndMom       = BIG;
  float deutMinStartMom   = BIG;
  float deutMinEndMom     = BIG;

  int numBins = 100;

  for (int i_event=0; i_event < numEvents;i_event++)
        {
            auto& event = util.GetEvent(i_event);
            auto e_minus_tracks = event.GetTracks(is_e_minus);
            for (auto& track : e_minus_tracks)
            {
                for (const auto& mctrack : *(track.trkmcsim))
                {
                    if (mctrack.pdg == 11)
                    {
                        if (mctrack.mom.R() > eMinusMaxStartMom)
                        {
                            eMinusMaxStartMom = mctrack.mom.R();
                        }
                        if (mctrack.endmom.R() > eMinusMaxEndMom)
                        {
                            eMinusMaxEndMom = mctrack.endmom.R();
                        }
                        if (mctrack.mom.R() < eMinusMinStartMom)
                        {
                            eMinusMinStartMom = mctrack.mom.R();
                        }
                        if (mctrack.endmom.R() < eMinusMinEndMom)
                        {
                            eMinusMinEndMom = mctrack.endmom.R();
                        }
                    }

                    if (mctrack.pdg == -11)
                    {
                        if (mctrack.mom.R() > ePlusMaxStartMom)
                        {
                            ePlusMaxStartMom = mctrack.mom.R();
                        }
                        if (mctrack.endmom.R() > ePlusMaxEndMom)
                        {
                            ePlusMaxEndMom = mctrack.endmom.R();
                        }
                        if (mctrack.mom.R() < ePlusMinStartMom)
                        {
                            ePlusMinStartMom = mctrack.mom.R();
                        }
                        if (mctrack.endmom.R() < ePlusMinEndMom)
                        {
                            ePlusMinEndMom = mctrack.endmom.R();
                        }
                    }
                    if (mctrack.pdg == 13)
                    {
                        if (mctrack.mom.R() > muMaxStartMom)
                        {
                            muMaxStartMom = mctrack.mom.R();
                        }
                        if (mctrack.endmom.R() > muMaxEndMom)
                        {
                            muMaxEndMom = mctrack.endmom.R();
                        }
                        if (mctrack.mom.R() < muMinStartMom)
                        {
                            muMinStartMom = mctrack.mom.R();
                        }
                        if (mctrack.endmom.R() < muMinEndMom)
                        {
                            muMinEndMom = mctrack.endmom.R();
                        }
                    }
                    if (mctrack.pdg == 2212)
                    {
                        if (mctrack.mom.R() > protonMaxStartMom)
                        {
                            protonMaxStartMom = mctrack.mom.R();
                        }
                        if (mctrack.endmom.R() > protonMaxEndMom)
                        {
                            protonMaxEndMom = mctrack.endmom.R();
                        }
                        if (mctrack.mom.R() < protonMinStartMom)
                        {
                            protonMinStartMom = mctrack.mom.R();
                        }
                        if (mctrack.endmom.R() < protonMinEndMom)
                        {
                            protonMinEndMom = mctrack.endmom.R();
                        }
                    }
                    if (mctrack.pdg == 1000010020)
                    {
                        if (mctrack.mom.R() > deutMaxStartMom)
                        {
                            deutMaxStartMom = mctrack.mom.R();
                        }
                        if (mctrack.endmom.R() > deutMaxEndMom)
                        {
                            deutMaxEndMom = mctrack.endmom.R();
                        }
                        if (mctrack.mom.R() < deutMinStartMom)
                        {
                            deutMinStartMom = mctrack.mom.R();
                        }
                        if (mctrack.endmom.R() < deutMinEndMom)
                        {
                            deutMinEndMom = mctrack.endmom.R();
                        }
                    }
                }
            }
        }
  cout << "Calculation complete!" << endl;
  cout << "Printing Results..." << endl;
  cout << "| Min Start | Max Start | Min End | Max End | Momenta by Particle in MeV/c:" << endl;
  cout << "Electron: | " << eMinusMinStartMom << " | " << eMinusMaxStartMom << " | " << eMinusMinEndMom << " | " << eMinusMaxEndMom << " | " << endl;
  cout << "Positron: | " << ePlusMinStartMom << " | " << ePlusMaxStartMom << " | " << ePlusMinEndMom << " | " << ePlusMaxEndMom << " | " << endl;
  cout << "Muon: | " << muMinStartMom << " | " << muMaxStartMom << " | " << muMinEndMom << " | " << muMaxEndMom << " | " << endl;
  cout << "Proton: | " << protonMinStartMom << " | " << protonMaxStartMom << " | " << protonMinEndMom << " | "  << protonMaxEndMom << " | " << endl;
  cout << "Deuteron: | " << deutMinStartMom << " | " << deutMaxStartMom << " | " << deutMinEndMom << " | " << deutMaxEndMom << " | " << endl;
}
