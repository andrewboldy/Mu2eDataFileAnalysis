//----------------------------------------------------------------------------------

//makeMomHistsAllTracks(string filelist)
//Written by Andrew Boldy
//University of South Carolina
//Summer 2025

//----------------------------------------------------------------------------------

//Creates particle start and end momentum histograms and saves them in the appropriate folder.
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
//Mu2e Inclusions
#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"
#include "EventNtuple/utils/rooutil/inc/common_cuts.hh"

//Personal Inclusions (if any)

void makeMomHists(string filelist)
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
  RooUtil util(filelist);
  int numEvents = util.GetNEvents();
  cout << "There are " << numEvents << " entries. Calculating the maximum and minimum momenta for each particle type of interest." << endl;

  //Finding the Max and Min Values Again:

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
                        //if (mctrack.pdg == 11 && mctrack.rank == 0)
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
  //Create the Histograms
  cout << "Calculation Complete!" << endl;
  cout << "Now creating histograms for start and end momenta!" << endl;
  //Make the TCanvas
  TCanvas* c1 = new TCanvas("c1","c1");
  //initialize the proton momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* protonStartMomHist = new TH1F("protonStartMomHist", "Files Protons by Start Momentum", numBins, protonMinStartMom,protonMaxStartMom);
    //TH1F* protonStartMomHist = new TH1F("protonStartMomHist", "MDC2020an_.._best_..All Protons by Start Momentum", numBins, protonMinStartMom,protonMaxStartMom);
    protonStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");

    //initalize the electron momentum histogram //need to get to the point where we have constructed the histograms correctly
    //TH1F* eMinusStartMomHist = new TH1F("eMinusStartMomHist", "MDC2020an_.._best_..Test Files Electrons  by Start Momentum", numBins, eMinusMinStartMom, eMinusMaxStartMom);
     TH1F* eMinusStartMomHist = new TH1F("eMinusStartMomHist", "Electrons  by Start Momentum", numBins, eMinusMinStartMom, 200);
    //TH1F* eMinusStartMomHist = new TH1F("eMinusStartMomHist", "MDC2020an_.._best_..Test Files Electrons (Only track) by Start Momentum", numBins, eMinusMinStartMom, eMinusMaxStartMom);
    //TH1F* eMinusStartMomHist = new TH1F("eMinusStartMomHist", "MDC2020an_.._best_..All Electrons by Start Momentum", numBins, eMinusMinStartMom, eMinusMaxStartMom);
    eMinusStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");

    //initialize the positron momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* ePlusStartMomHist = new TH1F("ePlusStartMomHist", "Positrons by Start Momentum", numBins, ePlusMinStartMom,ePlusMaxStartMom);
    //TH1F* ePlusStartMomHist = new TH1F("ePlusStartMomHist", "MDC2020an_.._best_..All Positrons by Start Momentum", numBins, ePlusMinStartMom,ePlusMaxStartMom);
    ePlusStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");

    //initialize the muon momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* muMinusStartMomHist = new TH1F("muMinusStartMomHist", "Muons by Start Momentum", numBins, muMinStartMom, muMaxStartMom);
    //TH1F* muMinusStartMomHist = new TH1F("muMinusStartMomHist", "MDC2020an_.._best_..All Muons by Start Momentum", numBins, muMinStartMom, muMaxStartMom);
    muMinusStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");

    //inialize the deuteron momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* deutStartMomHist = new TH1F("deutStartMomHist", "Deuterons by Start Momentum", numBins, deutMinStartMom, deutMaxStartMom);
    //TH1F* deutStartMomHist = new TH1F("deutStartMomHist", "MDC2020an_.._best_..All Deuterons by Start Momentum", numBins, deutMinStartMom, deutMaxStartMom);
    deutStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");

    //initialize the proton momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* protonEndMomHist = new TH1F("protonEndMomHist", "Protons by End Momentum", numBins, protonMinEndMom,protonMaxEndMom);
    //TH1F* protonEndMomHist = new TH1F("protonEndMomHist", "MDC2020an_.._best_..All Protons by End Momentum", numBins, protonMinEndMom,protonMaxEndMom);
    protonEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");

    //initalize the electron momentum histogram //need to get to the point where we have constructed the histograms correctly
    //TH1F* eMinusEndMomHist = new TH1F("eMinusEndMomHist", "MDC2020an_.._best_..All Electrons by End Momentum", numBins, eMinusMinEndMom, eMinusMaxEndMom);
    TH1F* eMinusEndMomHist = new TH1F("eMinusEndMomHist", "Electrons by End Momentum", numBins, 0, 5);
    //TH1F* eMinusEndMomHist = new TH1F("eMinusEndMomHist", "MDC2020an_.._best_..All Electrons by End Momentum", numBins, 0, 5);
    eMinusEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");

    //initialize the positron momentum histogram //need to get to the point where we have constructed the histograms correctly
    //TH1F* ePlusEndMomHist = new TH1F("ePlusEndMomHist", "MDC2020an_.._best_..All Positrons by End Momentum", numBins, ePlusMinEndMom,ePlusMaxEndMom);
    TH1F* ePlusEndMomHist = new TH1F("ePlusEndMomHist", "Positrons by End Momentum", numBins, 0,5);
    //TH1F* ePlusEndMomHist = new TH1F("ePlusEndMomHist", "MDC2020an_.._best_..All Positrons by End Momentum", numBins, 0,5);
    ePlusEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");

    //initialize the muon momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* muMinusEndMomHist = new TH1F("muMinusEndMomHist", "Muons by End Momentum", numBins, muMinEndMom, muMaxEndMom);
    //TH1F* muMinusEndMomHist = new TH1F("muMinusEndMomHist", "MDC2020an_.._best_..All Muons by End Momentum", numBins, muMinEndMom, muMaxEndMom);
    muMinusEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");

    //inialize the deuteron momentum histogram //need to get to the point where we have constructed the histograms correctly
   //TH1F* deutEndMomHist = new TH1F("deutEndMomHist", "MDC2020an_.._best_..All Deuterons by End Momentum", numBins, deutMinEndMom, deutMaxEndMom);
    TH1F* deutEndMomHist = new TH1F("deutEndMomHist", "Deuterons by End Momentum", numBins, 0, 5); //want to look specifically at the peak around 0 to determine by low momentum
    //TH1F* deutEndMomHist = new TH1F("deutEndMomHist", "MDC2020an_.._best_..All Deuterons by End Momentum", numBins, 0, 5); //want to look specifically at the peak around 0 to determine by low momentum
    deutEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");

    //Populate the Histograms
    for (int l_event = 0; l_event < numEvents; l_event++)
      {
        auto& event = util.GetEvent(l_event);
        auto e_minus_tracks = event.GetTracks(is_e_minus);
              for (auto& track : e_minus_tracks)
              {
                  for (const auto& mctrack : *(track.trkmcsim))
                  {
                      //Now that we are inside the object, we can populate our histograms || debating going between histogram drawing piece by pice
                      //if (mctrack.pdg == 11)
		      if (mctrack.pdg == 11 && mctrack.rank == 0) //electron
                      {
                          eMinusStartMomHist->Fill(mctrack.mom.R());
                          eMinusEndMomHist->Fill(mctrack.endmom.R());
                      }

                      if (mctrack.pdg == -11) //positron
                      {
                          ePlusStartMomHist->Fill(mctrack.mom.R());
                          ePlusEndMomHist->Fill(mctrack.endmom.R());

                      }

                      if (mctrack.pdg == 2212) //proton
                      {
                          protonStartMomHist->Fill(mctrack.mom.R());
                          protonEndMomHist->Fill(mctrack.endmom.R());
                      }

                      if (mctrack.pdg == 13) //muon
                      {
                          muMinusStartMomHist->Fill(mctrack.mom.R());
                          muMinusEndMomHist->Fill(mctrack.endmom.R());
                      }

                      if (mctrack.pdg == 1000010020) //deuteron
                      {
                          deutStartMomHist->Fill(mctrack.mom.R());
                          deutEndMomHist->Fill(mctrack.endmom.R());
                      }
                  }
          }
      }
      //Momentum Histograms (need to get the histograms right first, so need to first look at the relevant numbers)
      protonStartMomHist->SetStats(0);
      protonStartMomHist->Draw();
       c1->SaveAs("multiFileHistograms/protonHists/protonStartMomHistMDS1bAll.pdf");
      //c1->SaveAs("multiFileHistograms/protonHists/protonStartMomHistMDC2020an_best_Test.pdf");
      //c1->SaveAs("multiFileHistograms/protonHists/protonStartMomHistMDC2020an_best_All.pdf");
      c1->Clear();

      eMinusStartMomHist->SetStats(0);
      eMinusStartMomHist->Draw();
      c1->SaveAs("multiFileHistograms/eMinusHists/eMinusStartMomHistMDS1bAll.pdf");
      //c1->SaveAs("multiFileHistograms/eMinusHists/eMinusStartMomHistMDC2020an_best_Test.pdf");
      //c1->SaveAs("multiFileHistograms/eMinusHists/rank0eMinusStartMomHistMDC2020an_best_Test.pdf");
      //c1->SaveAs("multiFileHistograms/eMinusHists/eMinusStartMomHistMDC2020an_best_All.pdf");
      c1->Clear();

      ePlusStartMomHist->SetStats(0);
      ePlusStartMomHist->Draw();
      c1->SaveAs("multiFileHistograms/ePlusHists/ePlusStartMomHistMDS1bAll.pdf");
      //c1->SaveAs("multiFileHistograms/ePlusHists/ePlusStartMomHistMDC2020an_best_Test.pdf");
      //c1->SaveAs("multiFileHistograms/ePlusHists/ePlusStartMomHistMDC2020an_best_All.pdf");
      c1->Clear();

      muMinusStartMomHist->SetStats(0);
      muMinusStartMomHist->Draw();
      c1->SaveAs("multiFileHistograms/muMinusHists/muMinusStartMomHistMDS1bAll.pdf");
      //c1->SaveAs("multiFileHistograms/muMinusHists/muMinusStartMomHistMDC2020an_best_Test.pdf");
      //c1->SaveAs("multiFileHistograms/muMinusHists/muMinusStartMomHistMDC2020an_best_All.pdf");
      c1->Clear();

      deutStartMomHist->SetStats(0);
      deutStartMomHist->Draw();
      c1->SaveAs("multiFileHistograms/deutHists/deutStartMomHistMDS1bAll.pdf");
      //c1->SaveAs("multiFileHistograms/deutHists/deutStartMomHistMDC2020an_best_Test.pdf");
      //c1->SaveAs("multiFileHistograms/deutHists/deutStartMomHistMDC2020an_best_All.pdf");
      c1->Clear();


      //Momentum Histograms (need to get the histograms right first, so need to first look at the relevant numbers)
      protonEndMomHist->SetStats(0);
      protonEndMomHist->Draw();
      c1->SaveAs("multiFileHistograms/protonHists/protonEndMomHistMDS1bAll.pdf");
      //c1->SaveAs("multiFileHistograms/protonHists/protonEndMomHistMDC2020an_best_Test.pdf");
      //c1->SaveAs("multiFileHistograms/protonHists/protonEndMomHistMDC2020an_best_Test.pdf");
      c1->Clear();

      eMinusEndMomHist->SetStats(0);
      eMinusEndMomHist->Draw();
      c1->SaveAs("multiFileHistograms/eMinusHists/rank0eMinusEndMomHistMDS1bAll.pdf");
      //c1->SaveAs("multiFileHistograms/eMinusHists/rank0eMinusEndMomHistMDC2020an_best_Test.pdf");
      //c1->SaveAs("multiFileHistograms/eMinusHists/eMinusEndMomHistMDC2020an_best_Test.pdf");
      //c1->SaveAs("multiFileHistograms/eMinusHists/eMinusEndMomHistMDC2020an_best_All.pdf");
      c1->Clear();

      ePlusEndMomHist->SetStats(0);
      ePlusEndMomHist->Draw();
      c1->SaveAs("multiFileHistograms/ePlusHists/ePlusEndMomHistMDS1bAll.pdf");
      //c1->SaveAs("multiFileHistograms/ePlusHists/ePlusEndMomHistMDC2020an_best_Test.pdf");
      //c1->SaveAs("multiFileHistograms/ePlusHists/ePlusEndMomHistMDC2020an_best_All.pdf");
      c1->Clear();

      muMinusEndMomHist->SetStats(0);
      muMinusEndMomHist->Draw();
      c1->SaveAs("multiFileHistograms/muMinusHists/muMinusEndMomHistMDS1bAll.pdf");
      //c1->SaveAs("multiFileHistograms/muMinusHists/muMinusEndMomHistMDC2020an_best_Test.pdf");
      //c1->SaveAs("multiFileHistograms/muMinusHists/muMinusEndMomHistMDC2020an_best_All.pdf");
      c1->Clear();

      deutEndMomHist->SetStats(0);
      deutEndMomHist->Draw();
      c1->SaveAs("multiFileHistograms/deutHists/deutEndMomHistMDS1bAll.pdf");
      //c1->SaveAs("multiFileHistograms/deutHists/deutEndMomHistMDC2020an_best_Test.pdf");
      //c1->SaveAs("multiFileHistograms/deutHists/deutEndMomHistMDC2020an_best_All.pdf");
      c1->Clear();

    delete c1;
}

