//----------------------------------------------------------------------------------

//makePCHists(string filelist)
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
#include <TH1I.h>
//Mu2e Inclusions
#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"
#include "EventNtuple/utils/rooutil/inc/common_cuts.hh"

//Personal Inclusions (if any)

void makePCHists(string filelist)
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
  TH1I* protonPCHist = new TH1I("protonPCHist", "Test Files Protons by Process Code", 193, -0.5, 192.5);
  //TH1I* protonPCHist = new TH1I("protonPCHist", "MDC2020an_.._best_.. All Protons by Process Code", 193, -0.5, 192.5);
  protonPCHist->GetXaxis()->SetTitle("Assigned Process Code from ProcessCode.hh");

  //initialize the e- process code histogram
  TH1I* eMinusPCHist = new TH1I("eminusPCHist","Test Files Electrons by Process Code", 193, -0.5, 192.5);
  //TH1I* eMinusPCHist = new TH1I("eminusPCHist","MDC2020an_.._best_.. All Electrons by Process Code", 193, -0.5, 192.5);
  eMinusPCHist->GetXaxis()->SetTitle("Assigned Process Code from ProcessCode.hh");

  //initialize the e+ process code histogram
  TH1I* ePlusPCHist = new TH1I("eplusPCHist", "Test Files Positrons by Process Code", 193, -0.5, 192.5);
  //TH1I* ePlusPCHist = new TH1I("eplusPCHist", "MDC2020an_.._best_.. All Positrons by Process Code", 193, -0.5, 192.5);
  ePlusPCHist->GetXaxis()->SetTitle("Assigned Process Code from ProcessCode.hh");

  //initialize the muon process code histogram
  TH1I* muMinusPCHist = new TH1I("muminusPCHist", "TestFiles Muons by Process Code", 193, -0.5, 192.5);
  //TH1I* muMinusPCHist = new TH1I("muminusPCHist", "MDC2020an_.._best_.. All Muons by Process Code", 193, -0.5, 192.5);
  muMinusPCHist->GetXaxis()->SetTitle("Assigned Process Code from ProcessCode.hh");

  //initialize Deuteron process code histogram
  TH1I* deutPCHist = new TH1I("deutPCHist", "Test Files Deuterons by Process Code", 193, -0.5, 192.5);
  //TH1I* deutPCHist = new TH1I("deutPCHist", "MDC2020an_.._best_.. All Deuterons by Process Code", 193, -0.5, 192.5);
  deutPCHist->GetXaxis()->SetTitle("Assigned Process Code from ProcessCode.hh");

  //Populating the histograms
  for (int j_event = 0; j_event < numEvents; j_event++)
       {
          auto& event = util.GetEvent(j_event);
          auto e_minus_tracks = event.GetTracks(is_e_minus);
               for (auto& track : e_minus_tracks)
               {
                   for (const auto& mctrack : *(track.trkmcsim))
                   {
                       //Now that we are inside the object, we can populate our histograms || debating going between histogram drawing piece by pice
                       if (mctrack.pdg == 11) //electron
                       {
                           eMinusPCHist->Fill(mctrack.startCode);
                       }

                       if (mctrack.pdg == -11) //positron
                       {
                           ePlusPCHist->Fill(mctrack.startCode);
                       }

                       if (mctrack.pdg == 2212) //proton
                       {
                           protonPCHist->Fill(mctrack.startCode);
                       }

                       if (mctrack.pdg == 13) //muon
                       {
                           muMinusPCHist->Fill(mctrack.startCode);
                       }

                       if (mctrack.pdg == 1000010020) //deuteron
                       {
                           deutPCHist->Fill(mctrack.startCode);
                       }
                    }
           }
       }
       //Draw the Histograms, save them as pdfs and then clear before drawing the next one
       //PC Histograms First
       protonPCHist->SetStats(0);
       protonPCHist->Draw();
       //c1->SaveAs("multiFileHistograms/protonHists/protonPCHistTest.pdf");
       c1->SaveAs("multiFileHistograms/protonHists/protonPCHistMDC2020an_bestTest.pdf");
       //c1->SaveAs("multiFileHistograms/protonHists/protonPCHistMDC2020an_bestAll.pdf");
       c1->Clear();

       eMinusPCHist->SetStats(0);
       eMinusPCHist->Draw();
       //c1->SaveAs("multiFileHistograms/eMinusHists/eMinusPCHistTest.pdf");
       c1->SaveAs("multiFileHistograms/eMinusHists/eMinusPCHistMDC2020an_bestTest.pdf");
       //c1->SaveAs("multiFileHistograms/eMinusHists/eMinusPCHistMDC2020an_bestAll.pdf");
       c1->Clear();

       ePlusPCHist->SetStats(0);
       ePlusPCHist->Draw();
       //c1->SaveAs("multiFileHistograms/ePlusHists/ePlusPCHistTest.pdf");
       c1->SaveAs("multiFileHistograms/ePlusHists/ePlusPCHistMDC2020an_bestTest.pdf");
       //c1->SaveAs("multiFileHistograms/ePlusHists/ePlusPCHistMDC2020an_bestAll.pdf");
       c1->Clear();

       muMinusPCHist->SetStats(0);
       muMinusPCHist->Draw();
       //c1->SaveAs("multiFileHistograms/muMinusHists/muMinusPCHistTest.pdf");
       c1->SaveAs("multiFileHistograms/muMinusHists/muMinusPCHistMDC2020an_bestTest.pdf");
       //c1->SaveAs("multiFileHistograms/muMinusHists/muMinusPCHistMDC2020an_bestAll.pdf");
       c1->Clear();

       deutPCHist->SetStats(0);
       deutPCHist->Draw();
       //c1->SaveAs("multiFileHistograms/deutHists/deutPCHistTest.pdf");
       c1->SaveAs("multiFileHistograms/deutHists/deutPCHistMDC2020an_bestTest.pdf");
       //c1->SaveAs("multiFileHistograms/deutHists/deutPCHistMDC2020an_bestAll.pdf");
       c1->Clear();

  delete c1;
}
