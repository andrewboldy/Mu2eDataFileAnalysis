//----------------------------------------------------------------------------------------

//RooUtilParticleInfoHist(string filename)
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
#include <T1HF.h>
#include <T1HI.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>

//Including RooUtil
#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"

void RooUtilParticleInfoHist()
{
    string filename = "/pnfs/mu2e/tape/phy-nts/nts/mu2e/CeEndpointMix1BBTriggered/MDC2020an_v06_01_01_best_v1_3/root/04/2e/nts.mu2e.CeEndpointMix1BBTriggered.MDC2020an_v06_01_01_best_v1_3.001210_00000046.root";
    //initialize RooUtil to begin reading files
    RooUtil util(filename);
    int eventNumber = util.GetNEvents();
    cout << filename << " has " << eventNumber << " entries.";

    //Print the Outputs of Entry NUmber, PDG, nhits, startCode, and rank for each particle track
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
    //Work towards developing the histograms for each item

    //still have RooUtil initialized, however, now we need to create the histograms and populate them
    
    //create the canvas
    TCanvas* c1 = new TCanvas("c1","c1");

    //initialize the proton process code histogram
    TH1I* protonPCHist = new TH1I("protonPCHist", "Protons by Process Code", 193, -0.5, 192.5);

    //initialize the e- process code histogram
    TH1I* eMinusPCHist = new TH1I("eminusPCHist","Electrons by Process Code", 193, -0.5, 192.5);

    //initialize the e+ process code histogram
    TH1I* ePlustPCHist = new TH1I("eplusPCHist", "Positrons by Process Code", 193, -0.5, 192.5);

    //initialize the muon process code histogram
    TH1I* muMinusPCHist = new TH1I("muminusPCHist", "Muons by Process Code", 193, -0.5, 192.5);

    //initialize Deuteron process code histogram
    TH1I* deutPCHist = new TH1I("deutPCHist", "Deuterons by Process Code", 193, -0.5, 192.5);

    //initialize teh proton momentum histogram //need to get to the point where we have constructed the histograms correctly
    //TH1F* protonMomHist = new TH1F("protonMomHist", "Protons by Momentum", numBins, minProtonMom,maxProtonMom);

    //initalize the electron momentum histogram //need to get to the point where we have constructed the histograms correctly
    //TH1F* eMinusMomHist = new TH1F("eMinusMomHist", "Electrons by Momentum", numBins, mineMinusMom, maxeMinusMom);

    //initialize the positron momentum histogram //need to get to the point where we have constructed the histograms correctly
    //TH1F* ePlusMomHist = new TH1F("ePlusMomHist", "Positrons by Momentum", numBins, minePlusMom, maxePlusMom);

    //initialize the muon momentum histogram //need to get to the point where we have constructed the histograms correctly
    //TH1F* muMinusMomHist = new TH1F("muMinusMomHist", "Muons by Momentum", numBins, minMuMinusMom, maxMuMinusMom);

    //inialize the deuteron momentum histogram //need to get to the point where we have constructed the histograms correctly
    //TH1F* deutMomHist = new TH1F("deutMomHist", "Deuterons by Momentum", numBins, minDeutMom, maxDeutMom);


    //Populate the histograms here:
    //Specifically Populating for Process Code
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
    c1->SaveAs("protonPCHist.pdf");
    c1->Clear();

    eMinusPCHist->Draw();
    c1->SaveAs("eMinusPCHist.pdf");
    c1->Clear();

    ePlusPCHist->Draw();
    c1->SaveAs("ePlusPCHist.pdf");
    c1->Clear();

    muMinusPCHist->Draw();
    c1->SaveAs("muMinusPCHist.pdf");
    c1->Clear();

    deutPCHist->Draw();
    c1->SaveAs("deutPCHist.pdf");
    c1->Clear();

    //Momentum Histograms (need to get the histograms right first, so need to first look at the relevant numbers)
    //protonMomHist->Draw();
    //c1->SaveAs("protonMomHist.pdf");
    //c1->Clear();

    //eMinusMomHist->Draw();
    //c1->SaveAs("eMinusMomHist.pdf");
    //c1->Clear();

    //ePlusMomHist->Draw();
    //c1->SaveAs("ePlusMomHist.pdf");
    //c1->Clear();

    //muMinusMomHist->Draw();
    //c1->SaveAs("muMinusMomHist.pdf");
    //c1->Clear();

    //deutMomHist->Draw();
    //c1->SaveAs("deutMomHist.pdf");
    //c1->Clear();

    //Eventually delete c1
    delete c1; 
}
