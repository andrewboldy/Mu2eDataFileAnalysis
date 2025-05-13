//----------------------------------------------------------------------------------

//makePCandMomHists(string filelist)
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
#include "EventNtuple/utils/rooutil/inc/common_cuts.hh"

//Personal Inclusions (if any)

void makePCandMomHists(string filelist)
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
  //Create the Histograms
  cout << "Calculation Complete!" << endl;
  cout << "Now creating 2-D histograms for PC and start / end momenta!" << endl;

  //Create TCanvas
  TCanvas* c1 = new TCanvas("c1","c1");

  //next create a 2-d histogram with start momentum by process code (best to look at electron first!)
    TH2F* eMinusPCStartMomHist = new TH2F("eMinusPCStartMomHist", "MDC2020an_.._best_..Test Files Electrons by Process Code and Start Momentum", numBins,eMinusMinStartMom, 200,193,-0.5,192.5);
    //TH2F* eMinusPCStartMomHist = new TH2F("eMinusPCStartMomHist", "MDC2020an_.._best_..Test Files Electrons by Process Code and Start Momentum", numBins,eMinusMinStartMom, eMinusMaxStartMom,193,-0.5,192.5);
    //TH2F* eMinusPCStartMomHist = new TH2F("eMinusPCStartMomHist", "MDC2020an_.._best_..All Electrons by Process Code and Start Momentum", numBins,eMinusMinStartMom, eMinusMaxStartMom,193,-0.5,192.5);
    eMinusPCStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");
    eMinusPCStartMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* ePlusPCStartMomHist = new TH2F("ePlusPCStartMomHist", "MDC2020an_.._best_..Test Files Positrons by Process Code and Start Momentum", numBins, ePlusMinStartMom, ePlusMaxStartMom, 193,-0.5,192.5);
    //TH2F* ePlusPCStartMomHist = new TH2F("ePlusPCStartMomHist", "MDC2020an_.._best_..All Positrons by Process Code and Start Momentum", numBins, ePlusMinStartMom, ePlusMaxStartMom, 193,-0.5,192.5);
    ePlusPCStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");
    ePlusPCStartMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* protonPCStartMomHist = new TH2F("protonPCStartMomHist","MDC2020an_.._best_..Test Files Protons by Process Code and Start Momentum", numBins, protonMinStartMom, protonMaxStartMom, 193,-0.5,192.5);
    //TH2F* protonPCStartMomHist = new TH2F("protonPCStartMomHist","MDC2020an_.._best_..All Protons by Process Code and Start Momentum", numBins, protonMinStartMom, protonMaxStartMom, 193,-0.5,192.5);
    protonPCStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");
    protonPCStartMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* deutPCStartMomHist = new TH2F("deutPCStartMomHist", "MDC2020an_.._best_..Test Files Deuterons by Process Code and Start Momentum", numBins, deutMinStartMom, deutMaxStartMom, 193,-0.5,192.5);
    //TH2F* deutPCStartMomHist = new TH2F("deutPCStartMomHist", "MDC2020an_.._best_..All Deuterons by Process Code and Start Momentum", numBins, deutMinStartMom, deutMaxStartMom, 193,-0.5,192.5);
    deutPCStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");
    deutPCStartMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* muMinusPCStartMomHist = new TH2F("muMinusPCStartMomHist", "MDC2020an_.._best_..Test Files Muons by Process Code and Start Momentum", numBins, muMinStartMom,muMaxStartMom, 193,-0.5,192.5);
    //TH2F* muMinusPCStartMomHist = new TH2F("muMinusPCStartMomHist", "MDC2020an_.._best_.. All Muons by Process Code and Start Momentum", numBins, muMinStartMom,muMaxStartMom, 193,-0.5,192.5);
    muMinusPCStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");
    muMinusPCStartMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    //next create a 2-d histogram with end momentum by process code
    TH2F* eMinusPCEndMomHist = new TH2F("eMinusPCEndMomHist", "MDC2020an_.._best_..Test Files Electrons by Process Code and End Momentum", numBins,eMinusMinEndMom, eMinusMaxEndMom,193,-0.5,192.5);
    //TH2F* eMinusPCEndMomHist = new TH2F("eMinusPCEndMomHist", "MDC2020an_.._best_..All Electrons by Process Code and End Momentum", numBins,eMinusMinEndMom, eMinusMaxEndMom,193,-0.5,192.5);
    eMinusPCEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");
    eMinusPCEndMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* ePlusPCEndMomHist = new TH2F("ePlusPCEndMomHist", "MDC2020an_.._best_..Test Files Positrons by Process Code and End Momentum", numBins, ePlusMinEndMom, ePlusMaxEndMom, 193,-0.5,192.5);
    //TH2F* ePlusPCEndMomHist = new TH2F("ePlusPCEndMomHist", "MDC2020an_.._best_..All Positrons by Process Code and End Momentum", numBins, ePlusMinEndMom, ePlusMaxEndMom, 193,-0.5,192.5);
    ePlusPCEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");
    ePlusPCEndMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* protonPCEndMomHist = new TH2F("protonPCEndMomHist","MDC2020an_.._best_..Test Files Protons by Process Code and End Momentum", numBins, protonMinEndMom, protonMaxEndMom, 193,-0.5,192.5);
    //TH2F* protonPCEndMomHist = new TH2F("protonPCEndMomHist","MDC2020an_.._best_..All Protons by Process Code and End Momentum", numBins, protonMinEndMom, protonMaxEndMom, 193,-0.5,192.5);
    protonPCEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");
    protonPCEndMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* deutPCEndMomHist = new TH2F("deutPCEndMomHist", "MDC2020an_.._best_..Test Files Deuterons by Process Code and End Momentum", numBins, deutMinEndMom, deutMaxEndMom, 193,-0.5,192.5);
    //TH2F* deutPCEndMomHist = new TH2F("deutPCEndMomHist", "MDC2020an_.._best_..All Deuterons by Process Code and End Momentum", numBins, deutMinEndMom, deutMaxEndMom, 193,-0.5,192.5);
    deutPCEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");
    deutPCEndMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* muMinusPCEndMomHist = new TH2F("muMinusPCEndMomHist", "MDC2020an_.._best_..Test Files Muons by Process Code and End Momentum", numBins, muMinEndMom,muMaxEndMom, 193,-0.5,192.5);
    //TH2F* muMinusPCEndMomHist = new TH2F("muMinusPCEndMomHist", "MDC2020an_.._best_..All Muons by Process Code and End Momentum", numBins, muMinEndMom,muMaxEndMom, 193,-0.5,192.5);
    muMinusPCEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");
    muMinusPCEndMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    //Populate the Histograms
    for (int m_event = 0; m_event < numEvents; m_event++)
        {
            auto& event = util.GetEvent(m_event);
            auto e_minus_tracks = event.GetTracks(is_e_minus);
                for (auto& track : e_minus_tracks)
                {
                    for (auto& mctrack : *(track.trkmcsim))
                    {
                        //Now that we are inside the object, we can populate our histograms || debating going between histogram drawing piece by pice
                        if (mctrack.pdg == 11) //electron
                        {
                            eMinusPCStartMomHist->Fill(mctrack.mom.R(),mctrack.startCode);
                            eMinusPCEndMomHist->Fill(mctrack.endmom.R(),mctrack.startCode);
                        }

                        if (mctrack.pdg == -11) //positron
                        {
                            ePlusPCStartMomHist->Fill(mctrack.mom.R(),mctrack.startCode);
                            ePlusPCEndMomHist->Fill(mctrack.endmom.R(),mctrack.startCode);

                        }

                        if (mctrack.pdg == 2212) //proton
                        {
                            protonPCStartMomHist->Fill(mctrack.mom.R(),mctrack.startCode);
                            protonPCEndMomHist->Fill(mctrack.endmom.R(),mctrack.startCode);
                        }

                        if (mctrack.pdg == 13) //muon
                        {
                            muMinusPCStartMomHist->Fill(mctrack.mom.R(),mctrack.startCode);
                            muMinusPCEndMomHist->Fill(mctrack.endmom.R(),mctrack.startCode);
                        }

                        if (mctrack.pdg == 1000010020) //deuteron
                        {
                            deutPCStartMomHist->Fill(mctrack.mom.R(),mctrack.startCode);
                            deutPCEndMomHist->Fill(mctrack.endmom.R(),mctrack.startCode);
                        }
                    }
            }
        }
        //Momentum Histograms (need to get the histograms right first, so need to first look at the relevant numbers)
        protonPCStartMomHist->SetStats(0);
       	protonPCStartMomHist->Draw();
        //c1->SaveAs("multiFileHistograms/protonHists/protonPCStartMomHistTest.pdf");
        c1->SaveAs("multiFileHistograms/protonHists/protonPCStartMomHistMDC2020an_best_Test.pdf");
	//c1->SaveAs("multiFileHistograms/protonHists/protonPCStartMomHistMDC2020an_best_All.pdf");
        c1->Clear();

	eMinusPCStartMomHist->SetStats(0);
        eMinusPCStartMomHist->Draw();
        //c1->SaveAs("multiFileHistograms/eMinusHists/eMinusPCStartMomHistTest.pdf");
         c1->SaveAs("multiFileHistograms/eMinusHists/eMinusPCStartMomHistMDC2020an_best_Test.pdf");
	//c1->SaveAs("multiFileHistograms/eMinusHists/eMinusPCStartMomHistMDC2020an_best_All.pdf");
        c1->Clear();

	ePlusPCStartMomHist->SetStats(0);
        ePlusPCStartMomHist->Draw();
        //c1->SaveAs("multiFileHistograms/ePlusHists/ePlusPCStartMomHistTest.pdf");
        c1->SaveAs("multiFileHistograms/ePlusHists/ePlusPCStartMomHistMDC2020an_best_Test.pdf");
	//c1->SaveAs("multiFileHistograms/ePlusHists/ePlusPCStartMomHistMDC2020an_best_All.pdf");
        c1->Clear();

	muMinusPCStartMomHist->SetStats(0);
        muMinusPCStartMomHist->Draw();
        //c1->SaveAs("multiFileHistograms/muMinusHists/muMinusPCStartMomHistTest.pdf");
        c1->SaveAs("multiFileHistograms/muMinusHists/muMinusPCStartMomHistMDC2020an_best_Test.pdf");
	//c1->SaveAs("multiFileHistograms/muMinusHists/muMinusPCStartMomHistMDC2020an_best_All.pdf");
        c1->Clear();

	deutPCStartMomHist->SetStats(0);
        deutPCStartMomHist->Draw();
        //c1->SaveAs("multiFileHistograms/deutHists/deutPCStartMomHistTest.pdf");
        c1->SaveAs("multiFileHistograms/deutHists/deutPCStartMomHistMDC2020an_best_Test.pdf");
	//c1->SaveAs("multiFileHistograms/deutHists/deutPCStartMomHistMDC2020an_best_All.pdf");
        c1->Clear();


        //Momentum Histograms (need to get the histograms right first, so need to first look at the relevant numbers)
        protonPCEndMomHist->SetStats(0);
	protonPCEndMomHist->Draw();
        //c1->SaveAs("multiFileHistograms/protonHists/protonPCEndMomHistTest.pdf");
        c1->SaveAs("multiFileHistograms/protonHists/protonPCEndMomHistMDC2020an_best_Test.pdf");
	//c1->SaveAs("multiFileHistograms/protonHists/protonPCEndMomHistMDC2020an_best_All.pdf");
        c1->Clear();

	eMinusPCEndMomHist->SetStats(0);
        eMinusPCEndMomHist->Draw();
        //c1->SaveAs("multiFileHistograms/eMinusHists/eMinusPCEndMomHistTest.pdf");
        c1->SaveAs("multiFileHistograms/eMinusHists/eMinusPCEndMomHistMDC2020an_best_Test.pdf");
	//c1->SaveAs("multiFileHistograms/eMinusHists/eMinusPCEndMomHistMDC2020an_best_All.pdf");
        c1->Clear();

	ePlusPCEndMomHist->SetStats(0);
        ePlusPCEndMomHist->Draw();
        //c1->SaveAs("multiFileHistograms/ePlusHists/ePlusPCEndMomHistTest.pdf");
        c1->SaveAs("multiFileHistograms/ePlusHists/ePlusPCEndMomHistMDC2020an_best_Test.pdf");
	//c1->SaveAs("multiFileHistograms/ePlusHists/ePlusPCEndMomHistMDC2020an_best_All.pdf");
        c1->Clear();

	muMinusPCEndMomHist->SetStats(0);
        muMinusPCEndMomHist->Draw();
        //c1->SaveAs("multiFileHistograms/muMinusHists/muMinusPCEndMomHistTest.pdf");
        c1->SaveAs("multiFileHistograms/muMinusHists/muMinusPCEndMomHistMDC2020an_best_Test.pdf");
	//c1->SaveAs("multiFileHistograms/muMinusHists/muMinusPCEndMomHistMDC2020an_best_All.pdf");
        c1->Clear();

	deutPCEndMomHist->SetStats(0);
        deutPCEndMomHist->Draw();
        //c1->SaveAs("multiFileHistograms/deutHists/deutPCEndMomHistTest.pdf");
        c1->SaveAs("multiFileHistograms/deutHists/deutPCEndMomHistMDC2020an_best_Test.pdf");
	//c1->SaveAs("multiFileHistograms/deutHists/deutPCEndMomHistMDC2020an_best_All.pdf");
        c1->Clear();

    delete c1;
}
