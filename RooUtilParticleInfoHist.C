//----------------------------------------------------------------------------------------

//RooUtilParticleInfoHist()
//Written by Andrew Boldy
//University of South Carolina
//Spring 2025

//Brief description: takes in file, outputs list of pdg, nhits, processcode and rank to console and constructs desired histograms

//----------------------------------------------------------------------------------------

//Standard inclusions
#include <string>
#include <fstream>
#include <iostream>

//CERN ROOT Inclusions
#include <TH1F.h>
#include <TH1I.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>

//Including RooUtil
#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"

//Switches
bool DISPLAY_PARTICLE_INFO = true;
bool DISPLAY_MAXMIN_MOM = true;
bool CREATE_PC_HISTS = true;
bool CREATE_MOM_HISTS = true;
bool CREATE_PC_MOM_HISTS = true;



void RooUtilParticleInfoHist()
{
    //initialize start and end momenta maxes and mins 
    float protonMaxStartMom = 0;
    float protonMaxEndMom = 0;
    float eMinusMaxStartMom = 0;
    float eMinusMaxEndMom = 0;
    float ePlusMaxStartMom = 0;
    float ePlusMaxEndMom = 0;
    float muMaxStartMom = 0;
    float muMaxEndMom = 0;
    float deutMaxStartMom = 0;
    float deutMaxEndMom = 0;

    float protonMinStartMom = 999999999999999999;
    float protonMinEndMom = 999999999999999999;
    float eMinusMinStartMom = 999999999999999999;
    float eMinusMinEndMom = 999999999999999999;
    float ePlusMinStartMom = 999999999999999999;
    float ePlusMinEndMom = 999999999999999999;
    float muMinStartMom = 999999999999999999;
    float muMinEndMom = 999999999999999999;
    float deutMinStartMom = 999999999999999999;
    float deutMinEndMom = 999999999999999999;

    int numBins = 100;

    string filename = "/pnfs/mu2e/tape/phy-nts/nts/mu2e/CeEndpointMix1BBTriggered/MDC2020an_v06_01_01_best_v1_3/root/04/2e/nts.mu2e.CeEndpointMix1BBTriggered.MDC2020an_v06_01_01_best_v1_3.001210_00000046.root";
    //initialize RooUtil to begin reading files
    RooUtil util(filename);
    int eventNumber = util.GetNEvents();
    cout << filename << " has " << eventNumber << " entries.";

    //Print the Outputs of Entry NUmber, PDG, nhits, startCode, and rank for each particle track
    if (DISPLAY_PARTICLE_INFO == true)
    {
        for (int i_event=0; i_event < eventNumber;i_event++)
        {
            const auto& event = util.GetEvent(i_event);
            if (event.trkmcsim != nullptr)
            {
                for (const auto& trkmcsim : *(event.trkmcsim))
                {
                    // cout << "New Track!" << endl;
                    for (const auto& sim : trkmcsim)
                    { 
		//	if (sim.pdg != 1000290660 && sim.pdg != 1000080160 && sim.pdg != 1000791980 && sim.pdg != -321 && sim.pdg !=-13 && sim.pdg != 310 && sim.pdg != 321 && sim.pdg != 3112 && sim.pdg != 130 && sim.pdg != 211 && sim.pdg != 3122 && sim.pdg != 3212 && sim.pdg != -211 && sim.pdg != 2112 && sim.pdg != 22 && sim.pdg != 11 && sim.pdg != -11 && sim.pdg != 13 && sim.pdg != 2212 && sim.pdg != 1000010020)
			//{	
                        cout << "Entry Number: " << i_event
                             << " PDG Number: " << sim.pdg
                             << " Tracker Hits: " << sim.nhits
                             << " Process Code: " << sim.startCode
                            << " Rank: " << sim.rank << endl;
                                //if want to manually print these out in the console, open the file in root, then enter the tree and use the scan feature-> ntuple->Scan("trkmcsim.pdg:trkmcsim.nhits:trkmcsim.startCode:trkmcsim.rank"
                    	//}
		    }
                } 
            }
        }
    }

    if (DISPLAY_MAXMIN_MOM == true)
    {
        for (int i_event=0; i_event < eventNumber;i_event++)
        {
            const auto& event = util.GetEvent(i_event);
            if (event.trkmcsim != nullptr)
            {
                for (const auto& trkmcsim : *(event.trkmcsim))
                {
                    //cout << "New Track!" << endl;
                    for (const auto& sim : trkmcsim)
                    {
			//if (sim.pdg != 3122 && sim.pdg != 3212 && sim.pdg != -211 && sim.pdg != 2112 && sim.pdg != 22 && sim.pdg != 11 && sim.pdg != -11 && sim.pdg != 13 && sim.pdg != 2212 && sim.pdg != 1000010020)
			//{
                       // cout << "Entry Number: " << i_event
                       //      << " PDG Number: " << sim.pdg
                       //      << " Start Momentum: " << sim.mom.R()
                       //      << " End Momentum: " << sim.endmom.R()
                       //      << endl;
                    //}
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
        cout << "| Min Start | Max Start | Min End | Max End | Momenta by Particle in MeV/c:" << endl;
        cout << "Electron: | " << eMinusMinStartMom << " | " << eMinusMaxStartMom << " | " << eMinusMinEndMom << " | " << eMinusMaxEndMom << " | " << endl;
        cout << "Positron: | " << ePlusMinStartMom << " | " << ePlusMaxStartMom << " | " << ePlusMinEndMom << " | " << ePlusMaxEndMom << " | " << endl;
        cout << "Muon: | " << muMinStartMom << " | " << muMaxStartMom << " | " << muMinEndMom << " | " << muMaxEndMom << " | " << endl;
        cout << "Proton: | " << protonMinStartMom << " | " << protonMaxStartMom << " | " << protonMinEndMom << " | "  << protonMaxEndMom << " | " << endl;
        cout << "Deuteron: | " << deutMinStartMom << " | " << deutMaxStartMom << " | " << deutMinEndMom << " | " << deutMaxEndMom << " | " << endl;
    }
    //Work towards developing the histograms for each item

    //still have RooUtil initialized, however, now we need to create the histograms and populate them
    
    //create the canvas
    TCanvas* c1 = new TCanvas("c1","c1");

    //initialize the proton process code histogram
    TH1I* protonPCHist = new TH1I("protonPCHist", "MDC2020an_.._best_..00000046 Protons by Process Code", 193, -0.5, 192.5);
    protonPCHist->GetXaxis()->SetTitle("Assigned Process Code from ProcessCode.hh");

    //initialize the e- process code histogram
    TH1I* eMinusPCHist = new TH1I("eminusPCHist","MDC2020an_.._best_..00000046 Electrons by Process Code", 193, -0.5, 192.5);
    eMinusPCHist->GetXaxis()->SetTitle("Assigned Process Code from ProcessCode.hh");

    //initialize the e+ process code histogram
    TH1I* ePlusPCHist = new TH1I("eplusPCHist", "MDC2020an_.._best_..00000046 Positrons by Process Code", 193, -0.5, 192.5);
    ePlusPCHist->GetXaxis()->SetTitle("Assigned Process Code from ProcessCode.hh");

    //initialize the muon process code histogram
    TH1I* muMinusPCHist = new TH1I("muminusPCHist", "MDC2020an_.._best_..00000046 Muons by Process Code", 193, -0.5, 192.5);
    muMinusPCHist->GetXaxis()->SetTitle("Assigned Process Code from ProcessCode.hh");

    //initialize Deuteron process code histogram
    TH1I* deutPCHist = new TH1I("deutPCHist", "MDC2020an_.._best_..00000046 Deuterons by Process Code", 193, -0.5, 192.5);
    deutPCHist->GetXaxis()->SetTitle("Assigned Process Code from ProcessCode.hh");

    //initialize the proton momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* protonStartMomHist = new TH1F("protonStartMomHist", "MDC2020an_.._best_..00000046 Protons by Start Momentum", numBins, protonMinStartMom,protonMaxStartMom);
    protonStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");

    //initalize the electron momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* eMinusStartMomHist = new TH1F("eMinusStartMomHist", "MDC2020an_.._best_..00000046 Electrons by Start Momentum", numBins, eMinusMinStartMom, eMinusMaxStartMom);
    eMinusStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");

    //initialize the positron momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* ePlusStartMomHist = new TH1F("ePlusStartMomHist", "MDC2020an_.._best_..00000046 Positrons by Start Momentum", numBins, ePlusMinStartMom,ePlusMaxStartMom);
    ePlusStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");

    //initialize the muon momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* muMinusStartMomHist = new TH1F("muMinusStartMomHist", "MDC2020an_.._best_..00000046 Muons by Start Momentum", numBins, muMinStartMom, muMaxStartMom);
    muMinusStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");

    //inialize the deuteron momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* deutStartMomHist = new TH1F("deutStartMomHist", "MDC2020an_.._best_..00000046 Deuterons by Start Momentum", numBins, deutMinStartMom, deutMaxStartMom);
    deutStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");

    //initialize the proton momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* protonEndMomHist = new TH1F("protonEndMomHist", "MDC2020an_.._best_..00000046 Protons by End Momentum", numBins, protonMinEndMom,protonMaxEndMom);
    protonEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");

    //initalize the electron momentum histogram //need to get to the point where we have constructed the histograms correctly
    //TH1F* eMinusEndMomHist = new TH1F("eMinusEndMomHist", "MDC2020an_.._best_..00000046 Electrons by End Momentum", numBins, eMinusMinEndMom, eMinusMaxEndMom);
    TH1F* eMinusEndMomHist = new TH1F("eMinusEndMomHist", "MDC2020an_.._best_..00000046 Electrons by End Momentum", numBins, 0, 5);
    eMinusEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");

    //initialize the positron momentum histogram //need to get to the point where we have constructed the histograms correctly
    //TH1F* ePlusEndMomHist = new TH1F("ePlusEndMomHist", "MDC2020an_.._best_..00000046 Positrons by End Momentum", numBins, ePlusMinEndMom,ePlusMaxEndMom);
    TH1F* ePlusEndMomHist = new TH1F("ePlusEndMomHist", "MDC2020an_.._best_..00000046 Positrons by End Momentum", numBins, 0,5);
    ePlusEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");

    //initialize the muon momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* muMinusEndMomHist = new TH1F("muMinusEndMomHist", "MDC2020an_.._best_..00000046 Muons by End Momentum", numBins, muMinEndMom, muMaxEndMom);
    muMinusEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");

    //inialize the deuteron momentum histogram //need to get to the point where we have constructed the histograms correctly
   //TH1F* deutEndMomHist = new TH1F("deutEndMomHist", "MDC2020an_.._best_..00000046 Deuterons by End Momentum", numBins, deutMinEndMom, deutMaxEndMom);
    TH1F* deutEndMomHist = new TH1F("deutEndMomHist", "MDC2020an_.._best_..00000046 Deuterons by End Momentum", numBins, 0, 5); //want to look specifically at the peak around 0 to determine by low momentum
    deutEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");

    //next create a 2-d histogram with start momentum by process code (best to look at electron first!)
    TH2F* eMinusPCStartMomHist = new TH2F("eMinusPCStartMomHist", "MDC2020an_.._best_..00000046 Electrons by Process Code and Start Momentum", numBins,eMinusMinStartMom, eMinusMaxStartMom,193,-0.5,192.5);
    eMinusPCStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");
    eMinusPCStartMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* ePlusPCStartMomHist = new TH2F("ePlusPCStartMomHist", "MDC2020an_.._best_..00000046 Positrons by Process Code and Start Momentum", numBins, ePlusMinStartMom, ePlusMaxStartMom, 193,-0.5,192.5);
    ePlusPCStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");
    ePlusPCStartMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* protonPCStartMomHist = new TH2F("protonPCStartMomHist","MDC2020an_.._best_..00000046 Protons by Process Code and Start Momentum", numBins, protonMinStartMom, protonMaxStartMom, 193,-0.5,192.5);
    protonPCStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");
    protonPCStartMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");
    
    TH2F* deutPCStartMomHist = new TH2F("deutPCStartMomHist", "MDC2020an_.._best_..00000046 Deuterons by Process Code and Start Momentum", numBins, deutMinStartMom, deutMaxStartMom, 193,-0.5,192.5);
    deutPCStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");
    deutPCStartMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    TH2F* muMinusPCStartMomHist = new TH2F("muMinusPCStartMomHist", "MDC2020an_.._best_..00000046 Muons by Process Code and Start Momentum", numBins, muMinStartMom,muMaxStartMom, 193,-0.5,192.5);
    muMinusPCStartMomHist->GetXaxis()->SetTitle("Start Momentum (MeV/c)");
    muMinusPCStartMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");

    //next create a 2-d histogram with end momentum by process code
    TH2F* eMinusPCEndMomHist = new TH2F("eMinusPCEndMomHist", "MDC2020an_.._best_..00000046 Electrons by Process Code and End Momentum", numBins,eMinusMinEndMom, eMinusMaxEndMom,193,-0.5,192.5);
    eMinusPCEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");
    eMinusPCEndMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");
   
    TH2F* ePlusPCEndMomHist = new TH2F("ePlusPCEndMomHist", "MDC2020an_.._best_..00000046 Positrons by Process Code and End Momentum", numBins, ePlusMinEndMom, ePlusMaxEndMom, 193,-0.5,192.5);
    ePlusPCEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");
    ePlusPCEndMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");
   
    TH2F* protonPCEndMomHist = new TH2F("protonPCEndMomHist","MDC2020an_.._best_..00000046 Protons by Process Code and End Momentum", numBins, protonMinEndMom, protonMaxEndMom, 193,-0.5,192.5);
    protonPCEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");
    protonPCEndMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");
   
    TH2F* deutPCEndMomHist = new TH2F("deutPCEndMomHist", "MDC2020an_.._best_..00000046 Deuterons by Process Code and End Momentum", numBins, deutMinEndMom, deutMaxEndMom, 193,-0.5,192.5);
    deutPCEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");
    deutPCEndMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");
   
    TH2F* muMinusPCEndMomHist = new TH2F("muMinusPCEndMomHist", "MDC2020an_.._best_..00000046 Muons by Process Code and End Momentum", numBins, muMinEndMom,muMaxEndMom, 193,-0.5,192.5);
    muMinusPCEndMomHist->GetXaxis()->SetTitle("End Momentum (MeV/c)");
    muMinusPCEndMomHist->GetYaxis()->SetTitle("Assigned ProcessCode from ProcessCode.hh");


    //Populate the histograms here:
    //Specifically Populating for Process Code
    if (CREATE_PC_HISTS == true)
    {
        for (int j_event = 0; j_event < eventNumber; j_event++)
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
                            //eMinusMomHist->Fill(sim.mom.R()); //need to get to the point where we have constructed the histograms correctly
                        }

                        if (sim.pdg == -11) //positron
                        {
                            ePlusPCHist->Fill(sim.startCode);
                            //ePlussMomHist->Fill(sim.mom.R()); //need to get to the point where we have constructed the histograms correctly
                        }

                        if (sim.pdg == 2212) //proton
                        {
                            protonPCHist->Fill(sim.startCode);
                            //protonMomHist->Fill(sim.mom.R());//need to get to the point where we have constructed the histograms correctly
                        }

                        if (sim.pdg == 13) //muon
                        {
                            muMinusPCHist->Fill(sim.startCode);
                            //muMinusMomHist->Fill(sim.mom.R());//need to get to the point where we have constructed the histograms correctly
                        }

                        if (sim.pdg == 1000010020) //deuteron
                        {
                            deutPCHist->Fill(sim.startCode);
                            //deutMomHist->Fill(sim.mom.R());//need to get to the point where we have constructed the histograms correctly
                        }
                    }
                }
            }
        }
        //Draw the Histograms, save them as pdfs and then clear before drawing the next one
        //PC Histograms First
        protonPCHist->SetStats(0);
       	protonPCHist->Draw();
        c1->SaveAs("protonHists/protonPCHist.pdf");
        c1->Clear();

	eMinusPCHist->SetStats(0);
        eMinusPCHist->Draw();
        c1->SaveAs("eMinusHists/eMinusPCHist.pdf");
        c1->Clear();

	ePlusPCHist->SetStats(0);
        ePlusPCHist->Draw();
        c1->SaveAs("ePlusHists/ePlusPCHist.pdf");
        c1->Clear();

	muMinusPCHist->SetStats(0);
        muMinusPCHist->Draw();
        c1->SaveAs("muMinusHists/muMinusPCHist.pdf");
        c1->Clear();

	deutPCHist->SetStats(0);
        deutPCHist->Draw();
        c1->SaveAs("deutHists/deutPCHist.pdf");
        c1->Clear();
    }
    if (CREATE_MOM_HISTS==true)
    {
        for (int l_event = 0; l_event < eventNumber; l_event++)
        {
            const auto& event = util.GetEvent(l_event);
            if (event.trkmcsim != nullptr)
            {
                for (const auto& trkmcsim : *(event.trkmcsim))
                {
                    for (const auto& sim : trkmcsim)
                    {
                        //Now that we are inside the object, we can populate our histograms || debating going between histogram drawing piece by pice 
                        if (sim.pdg == 11) //electron
                        {
                            eMinusStartMomHist->Fill(sim.mom.R());
                            eMinusEndMomHist->Fill(sim.endmom.R());
                        }

                        if (sim.pdg == -11) //positron
                        {
                            ePlusStartMomHist->Fill(sim.mom.R());
                            ePlusEndMomHist->Fill(sim.endmom.R());
                            
                        }

                        if (sim.pdg == 2212) //proton
                        {
                            protonStartMomHist->Fill(sim.mom.R());
                            protonEndMomHist->Fill(sim.endmom.R());
                        }

                        if (sim.pdg == 13) //muon
                        {
                            muMinusStartMomHist->Fill(sim.mom.R());
                            muMinusEndMomHist->Fill(sim.endmom.R());
                        }

                        if (sim.pdg == 1000010020) //deuteron
                        {
                            deutStartMomHist->Fill(sim.mom.R());
                            deutEndMomHist->Fill(sim.endmom.R());
                        }
                    }
                }
            }
        }
        //Momentum Histograms (need to get the histograms right first, so need to first look at the relevant numbers)
        protonStartMomHist->SetStats(0);
	protonStartMomHist->Draw();
        c1->SaveAs("protonHists/protonStartMomHist.pdf");
        c1->Clear();

	eMinusStartMomHist->SetStats(0);
        eMinusStartMomHist->Draw();
        c1->SaveAs("eMinusHists/eMinusStartMomHist.pdf");
        c1->Clear();

	ePlusStartMomHist->SetStats(0);
        ePlusStartMomHist->Draw();
        c1->SaveAs("ePlusHists/ePlusStartMomHist.pdf");
        c1->Clear();

	muMinusStartMomHist->SetStats(0);
        muMinusStartMomHist->Draw();
        c1->SaveAs("muMinusHists/muMinusStartMomHist.pdf");
        c1->Clear();

	deutStartMomHist->SetStats(0);
        deutStartMomHist->Draw();
        c1->SaveAs("deutHists/deutStartMomHist.pdf");
        c1->Clear();


        //Momentum Histograms (need to get the histograms right first, so need to first look at the relevant numbers)
        protonEndMomHist->SetStats(0);
       	protonEndMomHist->Draw();
        c1->SaveAs("protonHists/protonEndMomHist.pdf");
        c1->Clear();

	eMinusEndMomHist->SetStats(0);
        eMinusEndMomHist->Draw();
        c1->SaveAs("eMinusHists/eMinusEndMomHist.pdf");
        c1->Clear();

	ePlusEndMomHist->SetStats(0);
        ePlusEndMomHist->Draw();
        c1->SaveAs("ePlusHists/ePlusEndMomHist.pdf");
        c1->Clear();

	muMinusEndMomHist->SetStats(0);
        muMinusEndMomHist->Draw();
        c1->SaveAs("muMinusHists/muMinusEndMomHist.pdf");
        c1->Clear();

	deutEndMomHist->SetStats(0);
        deutEndMomHist->Draw();
        c1->SaveAs("deutHists/deutEndMomHist.pdf");
        c1->Clear();


    } 
    
    if (CREATE_PC_MOM_HISTS==true)
    {
        for (int m_event = 0; m_event < eventNumber; m_event++)
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
        c1->SaveAs("protonHists/protonPCStartMomHist.pdf");
        c1->Clear();

	eMinusPCStartMomHist->SetStats(0);
        eMinusPCStartMomHist->Draw();
        c1->SaveAs("eMinusHists/eMinusPCStartMomHist.pdf");
        c1->Clear();

	ePlusPCStartMomHist->SetStats(0);
        ePlusPCStartMomHist->Draw();
        c1->SaveAs("ePlusHists/ePlusPCStartMomHist.pdf");
        c1->Clear();

	muMinusPCStartMomHist->SetStats(0);
        muMinusPCStartMomHist->Draw();
        c1->SaveAs("muMinusHists/muMinusPCStartMomHist.pdf");
        c1->Clear();

	deutPCStartMomHist->SetStats(0);
        deutPCStartMomHist->Draw();
        c1->SaveAs("deutHists/deutPCStartMomHist.pdf");
        c1->Clear();


        //Momentum Histograms (need to get the histograms right first, so need to first look at the relevant numbers)
        protonPCEndMomHist->SetStats(0);
	protonPCEndMomHist->Draw();
        c1->SaveAs("protonHists/protonPCEndMomHist.pdf");
        c1->Clear();

	eMinusPCEndMomHist->SetStats(0);
        eMinusPCEndMomHist->Draw();
        c1->SaveAs("eMinusHists/eMinusPCEndMomHist.pdf");
        c1->Clear();

	ePlusPCEndMomHist->SetStats(0);
        ePlusPCEndMomHist->Draw();
        c1->SaveAs("ePlusHists/ePlusPCEndMomHist.pdf");
        c1->Clear();

	muMinusPCEndMomHist->SetStats(0);
        muMinusPCEndMomHist->Draw();
        c1->SaveAs("muMinusHists/muMinusPCEndMomHist.pdf");
        c1->Clear();

	deutPCEndMomHist->SetStats(0);
        deutPCEndMomHist->Draw();
        c1->SaveAs("deutHists/deutPCEndMomHist.pdf");
        c1->Clear();


    } 
    //Eventually delete c1
    delete c1;
}
