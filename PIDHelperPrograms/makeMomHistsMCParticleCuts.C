//----------------------------------------------------------------------------------

//makeMomHistsMCParticleCuts(string filelist)
//Written by Andrew Boldy
//University of South Carolina
//Summer 2025

//----------------------------------------------------------------------------------

//Creates particle start and end histograms and saves them in the appropriate folder.
//commenting out lines to change the folder they go in for various different datasets and whether test or full dataset


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
  TH1F* CeEndpointEndMomHist = new TH1F("CeEndpointEndMomHist", "Ending Momentum for CeMinusEndpoint MCParticleCut", 55, 0 ,5);
  CeEndpointEndMomHist->GetXaxis()->SetTitle("Momentum (MeV/c)");
  
  //DIO
  TH1F* DIOStartMomHist = new TH1F("DIOStartMomHist", "Starting Momentum for DIO MCParticle Cut", 55, 0, 110);
  DIOStartMomHist->GetXaxis()->SetTitle("Momentum (MeV/c)");
  TH1F* DIOEndMomHist = new TH1F("DIOEndMomHist", "Ending Momentum for DIO MCParticle Cut", 55, 0, 5);
  DIOEndMomHist->GetXaxis()->SetTitle("Momentum (MeV/c)");

  //Cosmics
  TH1F* cosmicStartMomHist = new TH1F("CosmicStartMomHist", "Starting Momentum for Cosmic MCParticle Cut", 2000, 0, 10000);
  cosmicStartMomHist->GetXaxis()->SetTitle("Momentum (MeV/c)");
  TH1F* cosmicEndMomHist = new TH1F("CosmicEndMomHist", "Ending Momentum for Cosmic MCParticle Cut", 240, 0, 1200);
  cosmicEndMomHist->GetXaxis()->SetTitle("Momentum (MeV/c)");


  //Run Over Events and Populate
  for (int i_events = 0; i_events < numEvents; i_events++)
  //for (int i_events = 0; i_events < 50; i_events++)
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
  //c1->SaveAs("multiFileHistograms/processCutHists/CeEndpointHists/MDC2020anBestCeEndpoint1BBMix/CeEndpointStartMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/CeEndpointHists/MDC2020anBestCeEndpoint1BBMix/CeEndpointStartMomHistAll.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/CeEndpointHists/MDC2020arDIOtail/CeEndpointStartMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/CeEndpointHists/MDC2020arDIOtail/CeEndpointStartMomHistAll.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/CeEndpointHists/MDC2020aqCosmicOnSpillAll/CeEndpointStartMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/CeEndpointHists/MDC2020aqCosmicOnSpillAll/CeEndpointStartMomHistAll.pdf");
  c1->SaveAs("multiFileHistograms/processCutHists/CeEndpointHists/MDS1b/CeEndpointStartMomHistTest.pdf");
  c1->Clear();

  CeEndpointEndMomHist->Draw();
  //c1->SaveAs("multiFileHistograms/processCutHists/CeEndpointHists/MDC2020anBestCeEndpoint1BBMix/CeEndpointEndMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/CeEndpointHists/MDC2020anBestCeEndpoint1BBMix/CeEndpointEndMomHistAll.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/CeEndpointHists/MDC2020arDIOtail/CeEndpointEndMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/CeEndpointHists/MDC2020arDIOtail/CeEndpointEndMomHistAll.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/CeEndpointHists/MDC2020aqCosmicOnSpillAll/CeEndpointEndMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/CeEndpointHists/MDC2020aqCosmicOnSpillAll/CeEndpointEndMomHistAll.pdf");
  c1->SaveAs("multiFileHistograms/processCutHists/CeEndpointHists/MDS1b/CeEndpointEndMomHistTest.pdf");
  c1->Clear();

  //DIO
  DIOStartMomHist->Draw();
  //c1->SaveAs("multiFileHistograms/processCutHists/DIOHists/MDC2020anBestCeEndpoint1BBMix/DIOStartMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/DIOHists/MDC2020anBestCeEndpoint1BBMix/DIOStartMomHistAll.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/DIOHists/MDC2020arDIOtail/DIOStartMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/DIOHists/MDC2020arDIOtail/DIOStartMomHistAll.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/DIOHists/MDC2020aqCosmicOnSpillAll/DIOStartMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/DIOHists/MDC2020aqCosmicOnSpillAll/DIOStartMomHistAll.pdf");
  c1->SaveAs("multiFileHistograms/processCutHists/DIOHists/MDS1b/DIOStartMomHistTest.pdf");
  c1->Clear();

  DIOEndMomHist->Draw();
  //c1->SaveAs("multiFileHistograms/processCutHists/DIOHists/MDC2020anBestCeEndpoint1BBMix/DIOEndMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/DIOHists/MDC2020anBestCeEndpoint1BBMix/DIOEndMomHistAll.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/DIOHists/MDC2020arDIOtail/DIOEndMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/DIOHists/MDC2020arDIOtail/DIOEndMomHistAll.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/DIOHists/MDC2020aqCosmicOnSpillAll/DIOEndMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/DIOHists/MDC2020aqCosmicOnSpillAll/DIOEndMomHistAll.pdf");
  c1->SaveAs("multiFileHistograms/processCutHists/DIOHists/MDS1b/DIOEndMomHistTest.pdf");
  c1->Clear();

  //Cosmics
  cosmicStartMomHist->Draw();
  //c1->SaveAs("multiFileHistograms/processCutHists/cosmicHists/MDC2020anBestCeEndpoint1BBMix/cosmicStartMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/cosmicHists/MDC2020anBestCeEndpoint1BBMix/cosmicStartMomHistAll.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/cosmicHists/MDC2020arDIOtail/cosmicStartMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/cosmicHists/MDC2020arDIOtail/cosmicStartMomHistAll.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/cosmicHists/MDC2020aqCosmicOnSpillAll/cosmicStartMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/cosmicHists/MDC2020aqCosmicOnSpillAll/cosmicStartMomHistAll.pdf");
  c1->SaveAs("multiFileHistograms/processCutHists/cosmicHists/MDS1b/cosmicStartMomHistTest.pdf");
  c1->Clear();

  cosmicEndMomHist->Draw();
  //c1->SaveAs("multiFileHistograms/processCutHists/cosmicHists/MDC2020anBestCeEndpoint1BBMix/cosmicEndMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/cosmicHists/MDC2020anBestCeEndpoint1BBMix/cosmicEndMomHistAll.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/cosmicHists/MDC2020arDIOtail/cosmicEndMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/cosmicHists/MDC2020arDIOtail/cosmicEndMomHistAll.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/cosmicHists/MDC2020aqCosmicOnSpillAll/cosmicEndMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/cosmicHists/MDC2020aqCosmicOnSpillAll/cosmicEndMomHistAll.pdf");
  c1->SaveAs("multiFileHistograms/processCutHists/cosmicHists/MDS1b/cosmicEndMomHistTest.pdf");
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
  //c1->SaveAs("multiFileHistograms/processCutHists/combinedProcessHists/MDC2020anBestCeEndpoint1BBMix/CeEndpointDIOCosmicStartMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/combinedProcessHists/MDC2020anBestCeEndpoint1BBMix/CeEndpointDIOCosmicStartMomHistAll.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/combinedProcessHists/MDC2020arDIOtail/CeEndpointDIOCosmicStartMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/combinedProcessHists/MDC2020arDIOtail/CeEndpointDIOCosmicStartMomHistAll.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/combinedProcessHists/MDC2020aqCosmicOnSpillAll/CeEndpointDIOCosmicStartMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/combinedProcessHists/MDC2020aqCosmicOnSpillAll/CeEndpointDIOCosmicStartMomHistAll.pdf");
  c1->SaveAs("multiFileHistograms/processCutHists/combinedProcessHists/MDS1b/CeEndpointDIOCosmicStartMomHistTest.pdf");
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
  //c1->SaveAs("multiFileHistograms/processCutHists/combinedProcessHists/MDC2020anBestCeEndpoint1BBMix/CeEndpointDIOCosmicEndMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/combinedProcessHists/MDC2020anBestCeEndpoint1BBMix/CeEndpointDIOCosmicEndMomHistAll.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/combinedProcessHists/MDC2020arDIOtail/CeEndpointDIOCosmicEndMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/combinedProcessHists/MDC2020arDIOtail/CeEndpointDIOCosmicEndMomHistAll.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/combinedProcessHists/MDC2020aqCosmicOnSpillAll/CeEndpointDIOCosmicEndMomHistTest.pdf");
  //c1->SaveAs("multiFileHistograms/processCutHists/combinedProcessHists/MDC2020aqCosmicOnSpillAll/CeEndpointDIOCosmicEndMomHistAll.pdf");
  c1->SaveAs("multiFileHistograms/processCutHists/combinedProcessHists/MDS1b/CeEndpointDIOCosmicEndMomHistTest.pdf");
}
