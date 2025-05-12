//----------------------------------------------------------------------------------

//makePCandMomHistsAllTracks(string filelist)
//Written by Andrew Boldy
//University of South Carolina
//Summer 2025

//----------------------------------------------------------------------------------

//Creates particle start and end momentum histograms and saves them in the appropriate folder.
//Testing --> Have names of histograms to be denoted as "Test". For formal analysis, switch to the non-test lines
//Next Steps, have the filename be dynamic
//----------------------------------------------------------------------------------

//My Inclusions

//Standard Inclusions
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

//CERN ROOT Inclusions
#include <TCanvas.h>
#include <TH2F.h>
//Mu2e Inclusions
#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"

//Personal Inclusions (if any)

void makePCandMomHistsAllTracks(string filelist)
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
            const auto& event = util.GetEvent(i_event);
            if (event.trkmcsim != nullptr)
            {
                for (const auto& trkmcsim : *(event.trkmcsim))
                {
                    for (const auto& sim : trkmcsim)
                    {
                        if (sim.pdg == 11)
                        {
                            if (sim.mom.R() > eMinusMaxStartMom)
                            {
                                eMinusMaxStartMom = sim.mom.R();
                            }
                            if (sim.endmom.R() > eMinusMaxEndMom)
                            {
                                eMinusMaxEndMom = sim.endmom.R();
                            }
                            if (sim.mom.R() < eMinusMinStartMom)
                            {
                                eMinusMinStartMom = sim.mom.R();
                            }
                            if (sim.endmom.R() < eMinusMinEndMom)
                            {
                                eMinusMinEndMom = sim.endmom.R();
                            }
                        }

                        if (sim.pdg == -11)
                        {
                            if (sim.mom.R() > ePlusMaxStartMom)
                            {
                                ePlusMaxStartMom = sim.mom.R();
                            }
                            if (sim.endmom.R() > ePlusMaxEndMom)
                            {
                                ePlusMaxEndMom = sim.endmom.R();
                            }
                            if (sim.mom.R() < ePlusMinStartMom)
                            {
                                ePlusMinStartMom = sim.mom.R();
                            }
                            if (sim.endmom.R() < ePlusMinEndMom)
                            {
                                ePlusMinEndMom = sim.endmom.R();
                            }
                        }
                        if (sim.pdg == 13)
                        {
                            if (sim.mom.R() > muMaxStartMom)
                            {
                                muMaxStartMom = sim.mom.R();
                            }
                            if (sim.endmom.R() > muMaxEndMom)
                            {
                                muMaxEndMom = sim.endmom.R();
                            }
                            if (sim.mom.R() < muMinStartMom)
                            {
                                muMinStartMom = sim.mom.R();
                            }
                            if (sim.endmom.R() < muMinEndMom)
                            {
                                muMinEndMom = sim.endmom.R();
                            }
                        }
                        if (sim.pdg == 2212)
                        {
                            if (sim.mom.R() > protonMaxStartMom)
                            {
                                protonMaxStartMom = sim.mom.R();
                            }
                            if (sim.endmom.R() > protonMaxEndMom)
                            {
                                protonMaxEndMom = sim.endmom.R();
                            }
                            if (sim.mom.R() < protonMinStartMom)
                            {
                                protonMinStartMom = sim.mom.R();
                            }
                            if (sim.endmom.R() < protonMinEndMom)
                            {
                                protonMinEndMom = sim.endmom.R();
                            }
                        }
                        if (sim.pdg == 1000010020)
                        {
                            if (sim.mom.R() > deutMaxStartMom)
                            {
                                deutMaxStartMom = sim.mom.R();
                            }
                            if (sim.endmom.R() > deutMaxEndMom)
                            {
                                deutMaxEndMom = sim.endmom.R();
                            }
                            if (sim.mom.R() < deutMinStartMom)
                            {
                                deutMinStartMom = sim.mom.R();
                            }
                            if (sim.endmom.R() < deutMinEndMom)
                            {
                                deutMinEndMom = sim.endmom.R();
                            }
                        }
                    }
                }
            }
        }
  //Create the Histograms
  cout << "Calculation Complete!" << endl;
  cout << "Now creating 2-D histograms for PC and start / end momenta!" << endl;

  //Create TCanvas
  TCanvas* c1 = new TCanvas("c1","c1");

  //next create a 2-d histogram with start momentum by process code (best to look at electron first!)
    TH2F* eMinusPCStartMomHist = new TH2F("eMinusPCStartMomHist", "MDC2020an_.._best_..Test Files Electrons by Process Code and Start Momentum (All Tracks)", numBins,eMinusMinStartMom, eMinusMaxStartMom,193,-0.5,192.5);
    //TH2F* eMinusPCStartMomHist = new TH2F("eMinusPCStartMomHist", "MDC2020an_.._best_..All Electrons by Process Code and Start Momentum (All Tracks)", numBins,eMinusMinStartMom, eMinusMaxStartMom,193,-0.5,192.5);
    eMinusPCStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");
    eMinusPCStartMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* ePlusPCStartMomHist = new TH2F("ePlusPCStartMomHist", "MDC2020an_.._best_..Test Files Positrons by Process Code and Start Momentum (All Tracks)", numBins, ePlusMinStartMom, ePlusMaxStartMom, 193,-0.5,192.5);
    //TH2F* ePlusPCStartMomHist = new TH2F("ePlusPCStartMomHist", "MDC2020an_.._best_..All Positrons by Process Code and Start Momentum (All Tracks)", numBins, ePlusMinStartMom, ePlusMaxStartMom, 193,-0.5,192.5);
    ePlusPCStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");
    ePlusPCStartMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* protonPCStartMomHist = new TH2F("protonPCStartMomHist","MDC2020an_.._best_..Test Files Protons by Process Code and Start Momentum (All Tracks)", numBins, protonMinStartMom, protonMaxStartMom, 193,-0.5,192.5);
    //TH2F* protonPCStartMomHist = new TH2F("protonPCStartMomHist","MDC2020an_.._best_..All Protons by Process Code and Start Momentum (All Tracks)", numBins, protonMinStartMom, protonMaxStartMom, 193,-0.5,192.5);
    protonPCStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");
    protonPCStartMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* deutPCStartMomHist = new TH2F("deutPCStartMomHist", "MDC2020an_.._best_..Test Files Deuterons by Process Code and Start Momentum (All Tracks)", numBins, deutMinStartMom, deutMaxStartMom, 193,-0.5,192.5);
    //TH2F* deutPCStartMomHist = new TH2F("deutPCStartMomHist", "MDC2020an_.._best_..All Deuterons by Process Code and Start Momentum (All Tracks)", numBins, deutMinStartMom, deutMaxStartMom, 193,-0.5,192.5);
    deutPCStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");
    deutPCStartMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* muMinusPCStartMomHist = new TH2F("muMinusPCStartMomHist", "MDC2020an_.._best_..Test Files Muons by Process Code and Start Momentum (All Tracks)", numBins, muMinStartMom,muMaxStartMom, 193,-0.5,192.5);
    //TH2F* muMinusPCStartMomHist = new TH2F("muMinusPCStartMomHist", "MDC2020an_.._best_.. All Muons by Process Code and Start Momentum (All Tracks)", numBins, muMinStartMom,muMaxStartMom, 193,-0.5,192.5);
    muMinusPCStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");
    muMinusPCStartMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    //next create a 2-d histogram with end momentum by process code
    TH2F* eMinusPCEndMomHist = new TH2F("eMinusPCEndMomHist", "MDC2020an_.._best_..Test Files Electrons by Process Code and End Momentum (All Tracks)", numBins,eMinusMinEndMom, eMinusMaxEndMom,193,-0.5,192.5);
    //TH2F* eMinusPCEndMomHist = new TH2F("eMinusPCEndMomHist", "MDC2020an_.._best_..All Electrons by Process Code and End Momentum (All Tracks)", numBins,eMinusMinEndMom, eMinusMaxEndMom,193,-0.5,192.5);
    eMinusPCEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");
    eMinusPCEndMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* ePlusPCEndMomHist = new TH2F("ePlusPCEndMomHist", "MDC2020an_.._best_..Test Files Positrons by Process Code and End Momentum (All Tracks)", numBins, ePlusMinEndMom, ePlusMaxEndMom, 193,-0.5,192.5);
    //TH2F* ePlusPCEndMomHist = new TH2F("ePlusPCEndMomHist", "MDC2020an_.._best_..All Positrons by Process Code and End Momentum (All Tracks)", numBins, ePlusMinEndMom, ePlusMaxEndMom, 193,-0.5,192.5);
    ePlusPCEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");
    ePlusPCEndMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* protonPCEndMomHist = new TH2F("protonPCEndMomHist","MDC2020an_.._best_..Test Files Protons by Process Code and End Momentum (All Tracks)", numBins, protonMinEndMom, protonMaxEndMom, 193,-0.5,192.5);
    //TH2F* protonPCEndMomHist = new TH2F("protonPCEndMomHist","MDC2020an_.._best_..All Protons by Process Code and End Momentum (All Tracks)", numBins, protonMinEndMom, protonMaxEndMom, 193,-0.5,192.5);
    protonPCEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");
    protonPCEndMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* deutPCEndMomHist = new TH2F("deutPCEndMomHist", "MDC2020an_.._best_..Test Files Deuterons by Process Code and End Momentum (All Tracks)", numBins, deutMinEndMom, deutMaxEndMom, 193,-0.5,192.5);
    //TH2F* deutPCEndMomHist = new TH2F("deutPCEndMomHist", "MDC2020an_.._best_..All Deuterons by Process Code and End Momentum (All Tracks)", numBins, deutMinEndMom, deutMaxEndMom, 193,-0.5,192.5);
    deutPCEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");
    deutPCEndMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* muMinusPCEndMomHist = new TH2F("muMinusPCEndMomHist", "MDC2020an_.._best_..Test Files Muons by Process Code and End Momentum (All Tracks)", numBins, muMinEndMom,muMaxEndMom, 193,-0.5,192.5);
    //TH2F* muMinusPCEndMomHist = new TH2F("muMinusPCEndMomHist", "MDC2020an_.._best_..All Muons by Process Code and End Momentum (All Tracks)", numBins, muMinEndMom,muMaxEndMom, 193,-0.5,192.5);
    muMinusPCEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");
    muMinusPCEndMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    //Populate the Histograms
    for (int m_event = 0; m_event < numEvents; m_event++)
        {
            const auto& event = util.GetEvent(m_event);
            if (event.trkmcsim != nullptr)
            {
                for (const auto& trkmcsim : *(event.trkmcsim))
                {
                    for (const auto& sim : trkmcsim)
                    {
                        //Now that we are inside the object, we can populate our histograms || debating going between histogram drawing piece by pice
                        if (sim.pdg == 11) //electron
                        {
                            eMinusPCStartMomHist->Fill(sim.mom.R(),sim.startCode);
                            eMinusPCEndMomHist->Fill(sim.endmom.R(),sim.startCode);
                        }

                        if (sim.pdg == -11) //positron
                        {
                            ePlusPCStartMomHist->Fill(sim.mom.R(),sim.startCode);
                            ePlusPCEndMomHist->Fill(sim.endmom.R(),sim.startCode);

                        }

                        if (sim.pdg == 2212) //proton
                        {
                            protonPCStartMomHist->Fill(sim.mom.R(),sim.startCode);
                            protonPCEndMomHist->Fill(sim.endmom.R(),sim.startCode);
                        }

                        if (sim.pdg == 13) //muon
                        {
                            muMinusPCStartMomHist->Fill(sim.mom.R(),sim.startCode);
                            muMinusPCEndMomHist->Fill(sim.endmom.R(),sim.startCode);
                        }

                        if (sim.pdg == 1000010020) //deuteron
                        {
                            deutPCStartMomHist->Fill(sim.mom.R(),sim.startCode);
                            deutPCEndMomHist->Fill(sim.endmom.R(),sim.startCode);
                        }
                    }
                }
            }
        }
        //Momentum Histograms (need to get the histograms right first, so need to first look at the relevant numbers)
        protonPCStartMomHist->SetStats(0);
       	protonPCStartMomHist->Draw();
        c1->SaveAs("multiFileHistograms/protonHists/protonPCStartMomHistTestAllTracks.pdf");
        //c1->SaveAs("multiFileHistograms/protonHists/protonPCStartMomHistMDC2020an_bestAllTracks.pdf");
        c1->Clear();

	       eMinusPCStartMomHist->SetStats(0);
        eMinusPCStartMomHist->Draw();
        c1->SaveAs("multiFileHistograms/eMinusHists/eMinusPCStartMomHistTestAllTracks.pdf");
        //c1->SaveAs("multiFileHistograms/eMinusHists/eMinusPCStartMomHistMDC2020an_bestAllTracks.pdf");
        c1->Clear();

	       ePlusPCStartMomHist->SetStats(0);
        ePlusPCStartMomHist->Draw();
        c1->SaveAs("multiFileHistograms/ePlusHists/ePlusPCStartMomHistTestAllTracks.pdf");
        //c1->SaveAs("multiFileHistograms/ePlusHists/ePlusPCStartMomHistMDC2020an_bestAllTracks.pdf");
        c1->Clear();

	      muMinusPCStartMomHist->SetStats(0);
        muMinusPCStartMomHist->Draw();
        c1->SaveAs("multiFileHistograms/muMinusHists/muMinusPCStartMomHistTestAllTracks.pdf");
        //c1->SaveAs("multiFileHistograms/muMinusHists/muMinusPCStartMomHistMDC2020an_bestAllTracks.pdf");
        c1->Clear();

	       deutPCStartMomHist->SetStats(0);
        deutPCStartMomHist->Draw();
        c1->SaveAs("multiFileHistograms/deutHists/deutPCStartMomHistTestAllTracks.pdf");
        //c1->SaveAs("multiFileHistograms/deutHists/deutPCStartMomHistMDC2020an_bestAllTracks.pdf");
        c1->Clear();


        //Momentum Histograms (need to get the histograms right first, so need to first look at the relevant numbers)
        protonPCEndMomHist->SetStats(0);
	       protonPCEndMomHist->Draw();
        c1->SaveAs("multiFileHistograms/protonHists/protonPCEndMomHistTestAllTracks.pdf");
        //c1->SaveAs("multiFileHistograms/protonHists/protonPCEndMomHistMDC2020an_bestAllTracks.pdf");
        c1->Clear();

	       eMinusPCEndMomHist->SetStats(0);
        eMinusPCEndMomHist->Draw();
        c1->SaveAs("multiFileHistograms/eMinusHists/eMinusPCEndMomHistTestAllTracks.pdf");
        //c1->SaveAs("multiFileHistograms/eMinusHists/eMinusPCEndMomHistMDC2020an_bestAllTracks.pdf");
        c1->Clear();

	       ePlusPCEndMomHist->SetStats(0);
        ePlusPCEndMomHist->Draw();
        c1->SaveAs("multiFileHistograms/ePlusHists/ePlusPCEndMomHistTestAllTracks.pdf");
        //c1->SaveAs("multiFileHistograms/ePlusHists/ePlusPCEndMomHistMDC2020an_bestAllTracks.pdf");
        c1->Clear();

	       muMinusPCEndMomHist->SetStats(0);
        muMinusPCEndMomHist->Draw();
        c1->SaveAs("multiFileHistograms/muMinusHists/muMinusPCEndMomHistTestAllTracks.pdf");
        //c1->SaveAs("multiFileHistograms/muMinusHists/muMinusPCEndMomHistMDC2020an_bestAllTracks.pdf");
        c1->Clear();

	       deutPCEndMomHist->SetStats(0);
        deutPCEndMomHist->Draw();
        c1->SaveAs("multiFileHistograms/deutHists/deutPCEndMomHistTestAllTracks.pdf");
        //c1->SaveAs("multiFileHistograms/deutHists/deutPCEndMomHistMDC2020an_bestAllTracks.pdf");
        c1->Clear();

    delete c1;
}

