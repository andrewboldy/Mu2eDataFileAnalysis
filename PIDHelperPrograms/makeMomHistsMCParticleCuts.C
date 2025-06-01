//----------------------------------------------------------------------------------

//makeMomHistsMCParticleCuts(string filelist)
//Written by Andrew Boldy
//University of South Carolina
//Summer 2025

//----------------------------------------------------------------------------------

//Creates particle start histograms and saves them in the appropriate folder.
//Testing --> Have names of histograms to be denoted as "Test". For formal analysis, switch to the non-test lines

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
#include <TLegend.h>

//Mu2e Inclusions
#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"
#include "EventNtuple/utils/rooutil/inc/common_cuts.hh"

//Personal Inclusions (if any)


//Global Switches (if any)


void makeMomHistsMCParticleCuts(string filelist)
{
  //Open up the file and create the RooUtil and then check the file
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

  //Initialize RooUtil
  RooUtil util(filelist);

  //write out the number of events to be gone over
  int numEvents = util.GetNEvents();
  cout << "There are " << numEvents << " events to go over." << endl;
  cout << "Finding the maximum and minimum momenta for the process(es) of interest." << endl;

  //Initialize Canvas and Histograms and Set Axis Titles
  TCanvas* c1 = new TCanvas("c1","c1");
  
  //CeEndpoint
  TH1F* CeEndpointStartMomHist = new TH1F("CeEndpointStartMomHist", "Starting Momentum for CeMinusEndpoint MCParticle Cut", 55, 0, 110);
  CeEndpointStartMomHist->GetXaxis()->SetTitle("Momentum (MeV/c)");
  CeEndpointStartMomHist->SetStats(0);
  TH1F* CeEndpointEndMomHist = new TH1F("CeEndpointEndMomHist", "Ending Momentum for CeMinusEndpoint MCParticleCut", 55, 0 ,5);
  CeEndpointEndMomHist->GetXaxis()->SetTitle("Momentum (MeV/c)");
  CeEndpointEndMomHist->SetStats(0);

  //DIO
  TH1F* DIOStartMomHist = new TH1F("DIOStartMomHist", "Starting Momentum for DIO MCParticle Cut", 55, 0, 110);
  DIOStartMomHist->GetXaxis()->SetTitle("Momentum (MeV/c)");
  DIOStartMomHist->SetStats(0);
  TH1F* DIOEndMomHist = new TH1F("DIOEndMomHist", "Ending Momentum for DIO MCParticle Cut", 55, 0, 5);
  DIOEndMomHist->GetXaxis()->SetTitle("Momentum (MeV/c)");
  DIOEndMomHist->SetStats(0);

  //Cosmics
  TH1F* cosmicStartMomHist = new TH1F("CosmicStartMomHist", "Starting Momentum for Cosmic MCParticle Cut", 55, 0, 110);
  cosmicStartMomHist->GetXaxis()->SetTitle("Momentum (MeV/c)");
  cosmicStartMomHist->SetStats(0);
  TH1F* cosmicEndMomHist = new TH1F("CosmicEndMomHist", "Ending Momentum for Cosmic MCParticle Cut", 55, 0, 5);
  cosmicEndMomHist->GetXaxis()->SetTitle("Momentum (MeV/c)");
  cosmicEndMomHist->SetStats(0);

  //Run Over Events and Populate
  for (int i_events = 0; i_events < numEvents; i_events++)
  {
    auto& event = util.GetEvent(i_events);
    auto e_minus_tracks = event.GetTracks(is_e_minus);

    for (auto& track : e_minus_tracks)
    {
        auto CeEndpoints = track.GetMCParticles(is_CeMinusEndpoint);
        auto DIOs = track.GetMCParticles(is_DIO);
        auto cosmics = track.GetMCParticles(is_cosmic);

        for (auto particle : CeEndpoints)
        {
            CeEndpointStartMomHist->Fill(particle.mcsim->mom.R());
            CeEndpointEndMomHist->Fill(particle.mcsim->endmom.R());
        }
        for (auto particle : DIOs)
        {
            DIOStartMomHist->Fill(particle.mcsim->mom.R());
            DIOEndMomHist->Fill(particle.mcsim->endmom.R());
        }
        for (auto particle : cosmics)
        {
            cosmicStartMomHist->Fill(particle.mcsim->mom.R());
            cosmicEndMomHist->Fill(particle.mcsim->endmom.R());
        }
    }
  }
  
  //Save Histograms to their respective locations
  //Individual (need to do this better)

  //CeEndpoint
  CeEndpointStartMomHist->Draw();
  c1->SaveAs("multiFileHistograms/processCutHists/CeEndpointHists/CeEndpointStartMomHistTest.pdf");
  c1->Clear();

  CeEndpointEndMomHist->Draw();
  c1->SaveAs("multiFileHistograms/processCutHists/CeEndpointHists/CeEndpointEndMomHistTest.pdf");
  c1->Clear();

  //DIO
  DIOStartMomHist->Draw();
  c1->SaveAs("multiFileHistograms/processCutHists/DIOHists/DIOStartMomHistTest.pdf");
  c1->Clear();

  DIOEndMomHist->Draw();
  c1->SaveAs("multiFileHistograms/processCutHists/DIOHists/DIOEndMomHistTest.pdf");
  c1->Clear();

  //Cosmics
  cosmicStartMomHist->Draw();
  c1->SaveAs("multiFileHistograms/processCutHists/cosmicHists/cosmicStartMomHistTest.pdf");
  c1->Clear();

  cosmicEndMomHist->Draw();
  c1->SaveAs("multiFileHistograms/processCutHists/cosmicHists/cosmicEndMomHistTest.pdf");
  c1->Clear();
  
  //Combined Start Histogram
  CeEndpointStartMomHist->SetFillColorAlpha(kRed, 0.5);
  CeEndpointStartMomHist->SetTitle("Start Momentum Histograms for CeEndpoint, DIO, and Cosmic MCParticle Cuts");
  CeEndpointStartMomHist->Draw();
  DIOStartMomHist->SetFillColorAlpha(kBlue,0.5);
  DIOStartMomHist->Draw("SAME");
  cosmicStartMomHist->SetFillColorAlpha(kGreen,0.5);
  cosmicStartMomHist->Draw("SAME");

  TLegend* startLegend = new TLegend(0.8, 0.8, 0.9, 0.9);
  startLegend->SetHeader("MCParticle Process Cuts");
  startLegend->AddEntry(CeEndpointStartMomHist, "CeEndpoint", "f");
  startLegend->AddEntry(DIOStartMomHist, "DIO", "f");
  startLegend->AddEntry(cosmicStartMomHist, "Cosmics", "f");
  startLegend->Draw();
  c1->SetLogy();
  c1->SaveAs("multiFileHistograms/processCutHists/combinedProcessHists/CeEndpointDIOCosmicStartMomHistTest.pdf");
  c1->Clear();

  //Combined End Histogram
  CeEndpointEndMomHist->SetFillColorAlpha(kRed, 0.5);
  CeEndpointEndMomHist->SetTitle("End Momentum Histograms for CeEndpoint, DIO, and Cosmic MCParticle Cuts");
  CeEndpointEndMomHist->Draw();
  DIOEndMomHist->SetFillColorAlpha(kBlue,0.5);
  DIOEndMomHist->Draw("SAME");
  cosmicEndMomHist->SetFillColorAlpha(kGreen,0.5);
  cosmicEndMomHist->Draw("SAME");

  TLegend* endLegend = new TLegend(0.8, 0.8, 0.9, 0.9);
  endLegend->SetHeader("MCParticle Process Cuts");
  endLegend->AddEntry(CeEndpointEndMomHist, "CeEndpoint", "f");
  endLegend->AddEntry(DIOEndMomHist, "DIO", "f");
  endLegend->AddEntry(cosmicEndMomHist, "Cosmics", "f");
  endLegend->Draw();
  c1->SetLogy();
  c1->SaveAs("multiFileHistograms/processCutHists/combinedProcessHists/CeEndpointDIOCosmicEndMomHistTest.pdf");
}
