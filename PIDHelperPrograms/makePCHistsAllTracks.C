//----------------------------------------------------------------------------------

//makePCHistsAllTracks(string filelist)
//Written by Andrew Boldy
//University of South Carolina
//Summer 2025

//----------------------------------------------------------------------------------

//Creates particle process code histograms and saves them in the appropriate folder.
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
#include <TH1D.h>

//Mu2e Inclusions
#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"

//Personal Inclusions (if any)

void makePCHistsAllTracks(string filelist)
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
  RooUtil util(filelist);
  int numEvents = util.GetNEvents();
  cout << "There are " << numEvents << " entries. Creating process code histograms for all entries." << endl;

  //create the canvas
  TCanvas* c1 = new TCanvas("c1","c1");

  //initialize the proton process code histogram
  TH1I* protonPCHist = new TH1I("protonPCHist", "Test Files Protons by Process Code (All Tracks)", 193, -0.5, 192.5);
  //TH1I* protonPCHist = new TH1I("protonPCHist", "MDC2020an_.._best_..All Protons by Process Code (All Tracks)", 193, -0.5, 192.5);
  protonPCHist->GetXaxis()->SetTitle("Assigned Process Code from ProcessCode.hh");

  //initialize the e- process code histogram
  TH1I* eMinusPCHist = new TH1I("eminusPCHist","Test Files Electrons by Process Code (All Tracks)", 193, -0.5, 192.5);
  //TH1I* eMinusPCHist = new TH1I("eminusPCHist","MDC2020an_.._best_..All Electrons by Process Code (All Tracks)", 193, -0.5, 192.5);
  eMinusPCHist->GetXaxis()->SetTitle("Assigned Process Code from ProcessCode.hh");

  //initialize the e+ process code histogram
  TH1I* ePlusPCHist = new TH1I("eplusPCHist", "Test Files Positrons by Process Code (All Tracks)", 193, -0.5, 192.5);
  //TH1I* ePlusPCHist = new TH1I("eplusPCHist", "MDC2020an_.._best_..All Positrons by Process Code (All Tracks)", 193, -0.5, 192.5);
  ePlusPCHist->GetXaxis()->SetTitle("Assigned Process Code from ProcessCode.hh");

  //initialize the muon process code histogram
  TH1I* muMinusPCHist = new TH1I("muminusPCHist", "Test Files Muons by Process Code (All Tracks)", 193, -0.5, 192.5);
  //TH1I* muMinusPCHist = new TH1I("muminusPCHist", "MDC2020an_.._best_..All Muons by Process Code (All Tracks)", 193, -0.5, 192.5);
  muMinusPCHist->GetXaxis()->SetTitle("Assigned Process Code from ProcessCode.hh");

  //initialize Deuteron process code histogram
  TH1I* deutPCHist = new TH1I("deutPCHist", "Test Files Deuterons by Process Code (All Tracks)", 193, -0.5, 192.5);
  //TH1I* deutPCHist = new TH1I("deutPCHist", "MDC2020an_.._best_..All Deuterons by Process Code (All Tracks)", 193, -0.5, 192.5);
  deutPCHist->GetXaxis()->SetTitle("Assigned Process Code from ProcessCode.hh");

  //Populating the histograms
  for (int j_event = 0; j_event < numEvents; j_event++)
       {
           const auto& event = util.GetEvent(j_event);
           if (event.trkmcsim != nullptr)
           {
               for (const auto& trkmcsim : *(event.trkmcsim))
               {
                   for (const auto& sim : trkmcsim)
                   {
                       //Now that we are inside the object, we can populate our histograms || debating going between histogram drawing piece by pice
                       if (sim.pdg == 11) //electron
                       {
                           eMinusPCHist->Fill(sim.startCode);
                       }

                       if (sim.pdg == -11) //positron
                       {
                           ePlusPCHist->Fill(sim.startCode);
                       }

                       if (sim.pdg == 2212) //proton
                       {
                           protonPCHist->Fill(sim.startCode);
                       }

                       if (sim.pdg == 13) //muon
                       {
                           muMinusPCHist->Fill(sim.startCode);
                       }

                       if (sim.pdg == 1000010020) //deuteron
                       {
                           deutPCHist->Fill(sim.startCode);
                       }
                   }
               }
           }
       }
       //Draw the Histograms, save them as pdfs and then clear before drawing the next one
       //PC Histograms First
       protonPCHist->SetStats(0);
       protonPCHist->Draw();
       c1->SaveAs("multiFileHistograms/protonHists/protonPCHistTestAllTracks.pdf");
       //c1->SaveAs("multiFileHistograms/protonHists/protonPCHistMDC2020an_bestAllTracks.pdf");
       c1->Clear();

 eMinusPCHist->SetStats(0);
       eMinusPCHist->Draw();
       c1->SaveAs("multiFileHistograms/eMinusHists/eMinusPCHistTestAllTracks.pdf");
       //c1->SaveAs("multiFileHistograms/eMinusHists/eMinusPCHistMDC2020an_bestAllTracks.pdf");
       c1->Clear();

 ePlusPCHist->SetStats(0);
       ePlusPCHist->Draw();
       c1->SaveAs("multiFileHistograms/ePlusHists/ePlusPCHistTestAllTracks.pdf");
       //c1->SaveAs("multiFileHistograms/ePlusHists/ePlusPCHistMDC2020an_bestAllTracks.pdf");
       c1->Clear();

 muMinusPCHist->SetStats(0);
       muMinusPCHist->Draw();
       c1->SaveAs("multiFileHistograms/muMinusHists/muMinusPCHistTestAllTracks.pdf");
       //c1->SaveAs("multiFileHistograms/muMinusHists/muMinusPCHistMDC2020an_bestAllTracks.pdf");
       c1->Clear();

 deutPCHist->SetStats(0);
       deutPCHist->Draw();
       c1->SaveAs("multiFileHistograms/deutHists/deutPCHistTestAllTracks.pdf");
       //c1->SaveAs("multiFileHistograms/deutHists/deutPCHistMDC2020an_bestAllTracks.pdf");
       c1->Clear();
 delete c1;
}
