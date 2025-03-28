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
                    cout << "New Track!" << endl;
                    for (const auto& sim : trkmcsim)
                    {  
                        cout << "Entry Number: " << i_event
                             << " PDG Number: " << sim.pdg
                             << " Tracker Hits: " << sim.nhits
                             << " Process Code: " << sim.startCode
                            << " Rank: " << sim.rank << endl;
                                //if want to manually print these out in the console, open the file in root, then enter the tree and use the scan feature-> ntuple->Scan("trkmcsim.pdg:trkmcsim.nhits:trkmcsim.startCode:trkmcsim.rank"
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
                    cout << "New Track!" << endl;
                    for (const auto& sim : trkmcsim)
                    {
                        cout << "Entry Number: " << i_event
                             << " PDG Number: " << sim.pdg
                             << " Start Momentum: " << sim.mom.R()
                             << " End Momentum: " << sim.endmom.R()
                             << endl;
                    
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
    TH1I* protonPCHist = new TH1I("protonPCHist", "Protons by Process Code", 193, -0.5, 192.5);

    //initialize the e- process code histogram
    TH1I* eMinusPCHist = new TH1I("eminusPCHist","Electrons by Process Code", 193, -0.5, 192.5);

    //initialize the e+ process code histogram
    TH1I* ePlusPCHist = new TH1I("eplusPCHist", "Positrons by Process Code", 193, -0.5, 192.5);

    //initialize the muon process code histogram
    TH1I* muMinusPCHist = new TH1I("muminusPCHist", "Muons by Process Code", 193, -0.5, 192.5);

    //initialize Deuteron process code histogram
    TH1I* deutPCHist = new TH1I("deutPCHist", "Deuterons by Process Code", 193, -0.5, 192.5);

    //initialize the proton momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* protonStartMomHist = new TH1F("protonStartMomHist", "Protons by Start Momentum", numBins, protonMinStartMom,protonMaxStartMom);

    //initalize the electron momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* eMinusStartMomHist = new TH1F("eMinusStartMomHist", "Electrons by Start Momentum", numBins, eMinusMinStartMom, eMinusMaxStartMom);

    //initialize the positron momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* ePlusStartMomHist = new TH1F("ePlusStartMomHist", "Positrons by Start Momentum", numBins, ePlusMinStartMom,ePlusMaxStartMom);

    //initialize the muon momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* muMinusStartMomHist = new TH1F("muMinusStartMomHist", "Muons by Start Momentum", numBins, muMinStartMom, muMaxStartMom);

    //inialize the deuteron momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* deutStartMomHist = new TH1F("deutStartMomHist", "Deuterons by Start Momentum", numBins, deutMinStartMom, deutMaxStartMom);

    //initialize the proton momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* protonEndMomHist = new TH1F("protonEndMomHist", "Protons by End Momentum", numBins, protonMinEndMom,protonMaxEndMom);

    //initalize the electron momentum histogram //need to get to the point where we have constructed the histograms correctly
    //TH1F* eMinusEndMomHist = new TH1F("eMinusEndMomHist", "Electrons by End Momentum", numBins, eMinusMinEndMom, eMinusMaxEndMom);
    TH1F* eMinusEndMomHist = new TH1F("eMinusEndMomHist", "Electrons by End Momentum", numBins, 0, 5);

    //initialize the positron momentum histogram //need to get to the point where we have constructed the histograms correctly
    //TH1F* ePlusEndMomHist = new TH1F("ePlusEndMomHist", "Positrons by End Momentum", numBins, ePlusMinEndMom,ePlusMaxEndMom);
    TH1F* ePlusEndMomHist = new TH1F("ePlusEndMomHist", "Positrons by End Momentum", numBins, 0,5);

    //initialize the muon momentum histogram //need to get to the point where we have constructed the histograms correctly
    TH1F* muMinusEndMomHist = new TH1F("muMinusEndMomHist", "Muons by End Momentum", numBins, muMinEndMom, muMaxEndMom);

    //inialize the deuteron momentum histogram //need to get to the point where we have constructed the histograms correctly
   //TH1F* deutEndMomHist = new TH1F("deutEndMomHist", "Deuterons by End Momentum", numBins, deutMinEndMom, deutMaxEndMom);
    TH1F* deutEndMomHist = new TH1F("deutEndMomHist", "Deuterons by End Momentum", numBins, 0, 5); //want to look specifically at the peak around 0 to determine by low momentum

    //next create a 2-d histogram with start momentum by process code (best to look at electron first!)
    TH2F* eMinusPCStartMomHist = new TH2F("eMinusPCStartMomHist", "Electrons by Process Code and Start Momentum", numBins,eMinusMinStartMom, eMinusMaxStartMom,193,-0.5,192.5);
    TH2F* ePlusPCStartMomHist = new TH2F("ePlusPCStartMomHist", "Positrons by Process Code and Start Momentum", numBins, ePlusMinStartMom, ePlusMaxStartMom, 193,-0.5,192.5);
    TH2F* protonPCStartMomHist = new TH2F("protonPCStartMomHist","Protons by Process Code and Start Momentum", numBins, protonMinStartMom, protonMaxStartMom, 193,-0.5,192.5);
    TH2F* deutPCStartMomHist = new TH2F("deutPCStartMomHist", "Deuterons by Process Code and Start Momentum", numBins, deutMinStartMom, deutMaxStartMom, 193,-0.5,192.5);
    TH2F* muMinusPCStartMomHist = new TH2F("muMinusPCStartMomHist", "Muons by Process Code and Start Momentum", numBins, muMinStartMom,muMaxStartMom, 193,-0.5,192.5);

    //next create a 2-d histogram with end momentum by process code
    TH2F* eMinusPCEndMomHist = new TH2F("eMinusPCEndMomHist", "Electrons by Process Code and End Momentum", numBins,eMinusMinEndMom, eMinusMaxEndMom,193,-0.5,192.5);
    TH2F* ePlusPCEndMomHist = new TH2F("ePlusPCEndMomHist", "Positrons by Process Code and End Momentum", numBins, ePlusMinEndMom, ePlusMaxEndMom, 193,-0.5,192.5);
    TH2F* protonPCEndMomHist = new TH2F("protonPCEndMomHist","Protons by Process Code and End Momentum", numBins, protonMinEndMom, protonMaxEndMom, 193,-0.5,192.5);
    TH2F* deutPCEndMomHist = new TH2F("deutPCEndMomHist", "Deuterons by Process Code and End Momentum", numBins, deutMinEndMom, deutMaxEndMom, 193,-0.5,192.5);
    TH2F* muMinusPCEndMomHist = new TH2F("muMinusPCEndMomHist", "Muons by Process Code and End Momentum", numBins, muMinEndMom,muMaxEndMom, 193,-0.5,192.5);

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
        protonPCHist->Draw();
        c1->SaveAs("protonHists/protonPCHist.pdf");
        c1->Clear();

        eMinusPCHist->Draw();
        c1->SaveAs("eMinusHists/eMinusPCHist.pdf");
        c1->Clear();

        ePlusPCHist->Draw();
        c1->SaveAs("ePlusHists/ePlusPCHist.pdf");
        c1->Clear();

        muMinusPCHist->Draw();
        c1->SaveAs("muMinusHists/muMinusPCHist.pdf");
        c1->Clear();

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
        protonStartMomHist->Draw();
        c1->SaveAs("protonHists/protonStartMomHist.pdf");
        c1->Clear();

        eMinusStartMomHist->Draw();
        c1->SaveAs("eMinusHists/eMinusStartMomHist.pdf");
        c1->Clear();

        ePlusStartMomHist->Draw();
        c1->SaveAs("ePlusHists/ePlusStartMomHist.pdf");
        c1->Clear();

        muMinusStartMomHist->Draw();
        c1->SaveAs("muMinusHists/muMinusStartMomHist.pdf");
        c1->Clear();

        deutStartMomHist->Draw();
        c1->SaveAs("deutHists/deutStartMomHist.pdf");
        c1->Clear();


        //Momentum Histograms (need to get the histograms right first, so need to first look at the relevant numbers)
        protonEndMomHist->Draw();
        c1->SaveAs("protonHists/protonEndMomHist.pdf");
        c1->Clear();

        eMinusEndMomHist->Draw();
        c1->SaveAs("eMinusHists/eMinusEndMomHist.pdf");
        c1->Clear();

        ePlusEndMomHist->Draw();
        c1->SaveAs("ePlusHists/ePlusEndMomHist.pdf");
        c1->Clear();

        muMinusEndMomHist->Draw();
        c1->SaveAs("muMinusHists/muMinusEndMomHist.pdf");
        c1->Clear();

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
        protonPCStartMomHist->Draw();
        c1->SaveAs("protonHists/protonPCStartMomHist.pdf");
        c1->Clear();

        eMinusPCStartMomHist->Draw();
        c1->SaveAs("eMinusHists/eMinusPCStartMomHist.pdf");
        c1->Clear();

        ePlusPCStartMomHist->Draw();
        c1->SaveAs("ePlusHists/ePlusPCStartMomHist.pdf");
        c1->Clear();

        muMinusPCStartMomHist->Draw();
        c1->SaveAs("muMinusHists/muMinusPCStartMomHist.pdf");
        c1->Clear();

        deutPCStartMomHist->Draw();
        c1->SaveAs("deutHists/deutPCStartMomHist.pdf");
        c1->Clear();


        //Momentum Histograms (need to get the histograms right first, so need to first look at the relevant numbers)
        protonPCEndMomHist->Draw();
        c1->SaveAs("protonHists/protonPCEndMomHist.pdf");
        c1->Clear();

        eMinusPCEndMomHist->Draw();
        c1->SaveAs("eMinusHists/eMinusPCEndMomHist.pdf");
        c1->Clear();

        ePlusPCEndMomHist->Draw();
        c1->SaveAs("ePlusHists/ePlusPCEndMomHist.pdf");
        c1->Clear();

        muMinusPCEndMomHist->Draw();
        c1->SaveAs("muMinusHists/muMinusPCEndMomHist.pdf");
        c1->Clear();

        deutPCEndMomHist->Draw();
        c1->SaveAs("deutHists/deutPCEndMomHist.pdf");
        c1->Clear();


    } 
    //Eventually delete c1
    delete c1;
}
