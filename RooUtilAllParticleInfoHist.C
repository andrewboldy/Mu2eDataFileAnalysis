//----------------------------------------------------------------------------------

//RooUtilAllParticleInfoHist()
//Written by Andrew Boldy
//University of South Carolina
//Spring 2025

//----------------------------------------------------------------------------------

//Takes the Same Process as In RooUtilParticleInfoHist.C and applies it to all the files in the dataset of interest

//----------------------------------------------------------------------------------

//My Inclusions

//Regular Inclusions
#include <string>
#include <fstream>
#include <iostream>
#include <vector>


//ROOT Inclusions
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH1I.h>
#include <TCanvas.h>

//Including RooUtil
#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"

//Switches
bool DISPLAY_PARTICLE_INFO = true;

void RooUtilAllParticleInfoHist()
{
    //Initialize the TChain
    TChain* ntuple = new TChain("EventNtuple/ntuple");

    //Initialize the file reader
    ifstream input_filelist("filelists/MDC2020anBestFileList_staged.list");
    
    //begin reading the file after checking its open
    if (input_filelist.is_open())
    {
        string filename;
        while(getline(input_filelist,filename))
        {
            ntuple->Add(filename.c_str()); //add filenames to the TChain line by line from the list
        }
        input_filelist.close(); //close the filelist
    }

    //Print out the Number of Files in the List
    int numFiles = ntuple->GetEntries();
    cout << "There are now " << numFiles << " in the chaint. Beginning analysis, item by item." << endl;

    for (int i_file = 0; i_file < numFiles; i_file++)
    {
        ntuple->GetEntry(i_file); //get each entry in the ntuple for each file name
        string file = ntuple->GetCurrentFile()->GetName();  //pull the file name
        RooUtil util(file); //initialize RooUtil 
        int eventNumber = util.GetNEvents();
        cout << "File number: " << i_file+1 << " has " << eventNumber << " events." << endl;

        if (DISPLAY_PARTICLE_INFO == true)
        {
            for (int i_event = 0; i_event < eventNumber; i_event++)
            {
                const auto& event = util.GetEvent(i_event);
                if (event.trkmcsim != nullptr)
                {
                    for (const auto& trkmcsim : *(event.trkmcsim))
                    {
                        cout << "New Track!" << endl;
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
}
