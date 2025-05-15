//----------------------------------------------------------------------------------

//eMinusPosPlotter(string filelist)
//Written by Andrew Boldy
//University of South Carolina
//Summer 2025

//----------------------------------------------------------------------------------

//Displays and makes histograms from the position of electrons in the written filelist. 
//Testing Phase: Check to make sure that the outputs are good before moving on 
//Print out the momenta of interest. (X)
//Create the TH1F histograms. ( ) 
//Create the TH2F histograms. ( )
//Create the TH3F histogram. ( )

//----------------------------------------------------------------------------------

//My Inclusions

//Standard Inclusions
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

//CERN ROOT Inclusions
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>

//Mu2e Inclusions
#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"
#include "EventNtuple/utils/rooutil/inc/common_cuts.hh"

void eMinusPosPlotter(string filelist)
{
  //Produce the number of files in the filelist
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
  
  //Initialize Canvas 
  TCanvas* c1 = new TCanvas("c1","c1");

  //Initialize TH1Fs
  TH1F* eMinusXPos = new TH1F("eMinusXPos", "x Position of Electrons in the Tracker Simulation for MDC2020anBestTest for CeEndpointMix1BBTriggered",320,-800,800);
  eMinusXPos->GetXaxis()->SetTitle("x Position (mm)");
  TH1F* eMinusYPos = new TH1F("eMinusYPos","y Position of Electrons in the Tracker Simulation for MDC2020anBestTest for CeEndpointMix1BBTriggered", 320, -800, 800);
  eMinusYPos->GetXaxis()->SetTitle("y Position (mm)");
  TH1F* eMinusZPos = new TH1F("eMinusZPos","z Position of Electrons in the Tracker Simulation for MDC2020anBestTest for CeEndpointMix1BBTriggered", 1700, -6500, 2000);
  eMinusZPos->GetXaxis()->SetTitle("z Position (mm)");
  TH1F* eMinusXYRadiusPos = new TH1F("eMinusXYRadiusPos", "XY Plane Radius Position of Electrons in the Tracker Simulation for MDC2020anBestTest for CeEndpointMix1BBTriggered",150,0,750);
  eMinusXYRadiusPos->GetXaxis()->SetTitle("xy Radial Position (mm)");
  TH1F* eMinusPosMagnitude = new TH1F("eMinusPosMagnitude", "Position Magnitude of Electrons in the Tracker Simulation for MDC2020anBestTest for CeEndpointMix1BBTriggered",1000,0,6500);
  eMinusPosMagnitude->GetXaxis()->SetTitle("Position Magnitude (mm)");

  //Initialize TH2Fs
  TH2F* eMinusXYPos = new TH2F("eMinusXYPos", "x,y Position of Electrons in the Tracker Simulation for MDC2020anBestTest for CeEndpointMix1BBTriggered",320,-800,800,320,-800,800);
  eMinusXYPos->GetXaxis()->SetTitle("x Position (mm)");
  eMinusXYPos->GetYaxis()->SetTitle("y Position (mm)");
  TH2F* eMinusXZPos = new TH2F("eMinusXZPos", "x,z Position of Electrons in the Tracker Simulation for MDC2020anBestTest for CeEndpointMix1BBTriggered",320,-800,800,1700,-6500,2000);
  eMinusXZPos->GetXaxis()->SetTitle("x Position (mm)");
  eMinusXZPos->GetYaxis()->SetTitle("y Position (mm)");
  TH2F* eMinusYZPos = new TH2F("eMinusYZPos", "y,z Position of Electrons in the Tracker Simulation for MDC2020anBestTest for CeEndpointMix1BBTriggered",320,-800,800,1700,-6500,2000);
  eMinusYZPos->GetXaxis()->SetTitle("y Position (mm)");
  eMinusYZPos->GetYaxis()->SetTitle("z Position (mm)");

  //Initialize TH3Fs (unsure how to do this yet)
  TH3F* eMinusXYZPos = new TH3F("eMinusXYZPos", "x,y,z Position of Electrons in the Tracker Simulation for MDC2020anBestTest for CeEndpointMix1BBTriggered", 320,-800,800,320,-800,800,1700,-6500,2000);
  eMinusXYZPos->GetXaxis()->SetTitle("x Position (mm)");
  eMinusXYZPos->GetYaxis()->SetTitle("y Position (mm)");
  eMinusXYZPos->GetZaxis()->SetTitle("z Position (mm)");
  
  //Initialize RooUtil and print out the total number of events
  RooUtil util(filelist);
  int numEvents = util.GetNEvents();
  cout << "There are " << numEvents << " entries. Printing x, y, and z position values, xy radius values, and full magnitudes." << endl;

  //Loop through events
  for (int i_event = 0; i_event < numEvents; i_event++)
  {
    //cout << " " << endl;
    //cout << "Printing Particle Positions for Particles in Event Number: " << i_event+1 << endl;
    //cout << "-----------------------------------------------------------------" << endl; //Creating a break between events 
    auto& event = util.GetEvent(i_event);
    auto e_minus_tracks = event.GetTracks(is_e_minus);

    for (auto& track : e_minus_tracks)
    {
      auto all_particles = track.GetMCParticles();
      
      for (auto& particle : all_particles)
      {
        if (particle.mcsim->pdg==11 && particle.mcsim->rank==0)
        {
          //Define variables
          float x = particle.mcsim->pos.x();
          float y = particle.mcsim->pos.y();
          float z = particle.mcsim->pos.z();
          float xyR = sqrt(x*x+y*y);
          float magPos = particle.mcsim->pos.R();

          //Print out the various position values we are interested in
          //cout << "e x Pos: " << x 
          //     << "; e y Pos: " << y
          //     << "; e z Pos: " << z
          //     << "; e xy radial Pos: " << xyR 
          //     << "; e position Pos: " << magPos
          //     << endl;

          //Populate Histograms 
          // TH1Fs
          eMinusXPos->Fill(x);
          eMinusYPos->Fill(y);
          eMinusZPos->Fill(z);
          eMinusXYRadiusPos->Fill(xyR);
          eMinusPosMagnitude->Fill(magPos);
          
          // TH2Fs
	  eMinusXYPos->Fill(x,y);
          eMinusXZPos->Fill(x,z);
          eMinusYZPos->Fill(y,z);

          //TH3F (if possible)
          eMinusXYZPos->Fill(x,y,z);
        }
      }
    }
  }
  //Draw Histograms
  // TH1Fs
  eMinusXPos->Draw();
  c1->SaveAs("multiFileHistograms/eMinusHists/posHists/rank0eMinusXPos_MDC2020anBestCeEndpointTest.pdf");
  c1->Clear();
  eMinusYPos->Draw();
  c1->SaveAs("multiFileHistograms/eMinusHists/posHists/rank0eMinusYPos_MDC2020anBestCeEndpointTest.pdf");
  c1->Clear();
  eMinusZPos->Draw();
  c1->SaveAs("multiFileHistograms/eMinusHists/posHists/rank0eMinusZPos_MDC2020anBestCeEndpointTest.pdf");
  c1->Clear();
  eMinusXYRadiusPos->Draw();
  c1->SaveAs("multiFileHistograms/eMinusHists/posHists/rank0eMinusXYRadiusPos_MDC2020anBestCeEndpointTest.pdf");
  c1->Clear();
  eMinusPosMagnitude->Draw();
  c1->SaveAs("multiFileHistograms/eMinusHists/posHists/rank0eMinusPosMagnitude_MDC2020anBestCeEndpointTest.pdf");
  c1->Clear();
  // TH2Fs
  eMinusXYPos->Draw();
  c1->SaveAs("multiFileHistograms/eMinusHists/posHists/rank0eMinusXYPos_MDC2020anBestCeEndpointTest.pdf");
  c1->Clear();
  eMinusXZPos->Draw();
  c1->SaveAs("multiFileHistograms/eMinusHists/posHists/rank0eMinusXZPos_MDC2020anBestCeEndpointTest.pdf");
  c1->Clear();
  eMinusYZPos->Draw();
  c1->SaveAs("multiFileHistograms/eMinusHists/posHists/rank0eMinusYZPos_MDC2020anBestCeEndpointTest.pdf");
  c1->Clear();
  
  // TH3F (if possible)
  TFile* eMinusXYZPosFile = new TFile("multiFileHistograms/eMinusHists/posHists/rank0eMinusXYZPosHistOutput.root", "RECREATE");
  eMinusXYZPos->Write();
  eMinusXYZPosFile->Close();
}

