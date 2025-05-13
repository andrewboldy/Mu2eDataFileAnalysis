//----------------------------------------------------------------------------------

//eMinusMomCompare(string filelist)
//Written by Andrew Boldy
//University of South Carolina
//Summer 2025

//----------------------------------------------------------------------------------

//Displays particle momentum in MeV/c for a list of files produced from trkseg, trksegmc, trkmcsim, and (eventually mcsim).


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

void eMinusMomCompare(string filelist)
{
  //Read the filelist first and write out the number of files. Then initialize RooUtil and state the number  of events being covered
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
  cout << "There are " << numEvents << " entries. Printing momenta of each event using trkseg, trksegmc, and trkmcsim." << endl;

  //Initialize the momenta histograms and canvas 
  TCanvas* c1 = new TCanvas("c1","c1");
  
  TH1F* eMinusTrkSegEntMoms = new TH1F("eMinusTrkSegEntMoms", "MDC2020anBestTest e Minus Tracker Entrance Reco Momenta (trkseg)",100, 70, 110);
  eMinusTrkSegEntMoms->GetXaxis()->SetTitle("Momentum Magnitude (MeV/c)");
  eMinusTrkSegEntMoms->SetStats(0);

  TH1F* eMinusTrkSegMCEntMoms = new TH1F("eMinusTrkSegMCEntMoms", "MDC2020anBestTest e Minus Tracker Entrance True Momenta (trksegmc)",100, 70, 110);
  eMinusTrkSegMCEntMoms->GetXaxis()->SetTitle("Momentum Magnitude (MeV/c)");
  eMinusTrkSegMCEntMoms->SetStats(0);

  TH1F* eMinusTrkMCSimMoms = new TH1F("eMinusTrkMCSimMoms", "MDC2020anBestTest Thrown e Minus Simulated Momenta (trkmcsim)", 100, 70, 110);
  eMinusTrkMCSimMoms->GetXaxis()->SetTitle("Momentum Magnitude (MeV/c)");
  eMinusTrkMCSimMoms->SetStats(0);
  
  TH1F* eMinusTrkSegTrkSegMCDiff = new TH1F("eMinusTrkSegTrkSegMCDiff", "MDC2020anBestTest e Minus Momentum Difference (MeV/c) Between trkseg and trksegmc Branches", 50, -5,5);
  eMinusTrkSegTrkSegMCDiff->GetXaxis()->SetTitle("trkseg and trksegmc Momentum Differences (MeV/c)");
  eMinusTrkSegTrkSegMCDiff->SetStats(0);

  TH1F* eMinusMCSimMoms = new TH1F("eMinusMCSimMoms", "MDC2020anBestTest e Minus Momenta (MeV/c) from mcsim Branch under is_CeMinusEndpoint Cut", 100, -0.5, 115);
  eMinusMCSimMoms->GetXaxis()->SetTitle("mcsim Branch Momentum (MeV/c)");
  eMinusMCSimMoms->SetStats(0);
  
  //print the momenta from trkseg, trksegmc, and trkmcsim
  for (int i_event = 0; i_event < numEvents; i_event++)
  {
    cout << " " << endl;
    cout << "Printing momentum for entry number: " << i_event+1 << endl;
    cout << "-----------------------------------------------------------------" << endl;
    auto& event = util.GetEvent(i_event);
    auto e_minus_tracks = event.GetTracks(is_e_minus);
    for (auto& track : e_minus_tracks)
    {
      auto trackEntSegments = track.GetSegments([](TrackSegment& segment){ return tracker_entrance(segment) && has_mc_step(segment) && has_reco_step(segment); });
      cout << "Printing trkseg and trksegmc momenta at the entrace with momenta." << endl;
      for (auto& segment : trackEntSegments)
      {
        cout << "trkseg Momentum (MeV/c): " << segment.trkseg->mom.R() 
             << "; trksegmc Momentum (MeV/c): " << segment.trksegmc->mom.R() 
             << "; Resolution: " << segment.trkseg->mom.R() - segment.trksegmc->mom.R() << endl;
        eMinusTrkSegEntMoms->Fill(segment.trkseg->mom.R());
        eMinusTrkSegMCEntMoms->Fill(segment.trksegmc->mom.R());
        eMinusTrkSegTrkSegMCDiff->Fill(segment.trkseg->mom.R() - segment.trksegmc->mom.R());
      }
      cout << "Printing trkmcsim momenta for rank 0 electrons only." << endl;
      for (auto& mctrack : *(track.trkmcsim))
      {
        if (mctrack.pdg == 11 && mctrack.rank == 0)
        {
          cout << "trkmcsim Momentum (MeV/c): " << mctrack.mom.R() << endl;
          eMinusTrkMCSimMoms->Fill(mctrack.mom.R()); 
        }
      }
      auto CeMinusEndpoints = track.GetMCParticles(is_CeMinusEndpoint);
      cout << "Printing mcsim momenta for CeMinusEndpoint." << endl;
      for (auto& particle : CeMinusEndpoints)
      {
        cout << "mcsim Momentum (MeV/c): " << particle.mcsim->mom.R() << endl;
      }
    }
  }
  //Print out the Histograms on different canvases
  eMinusTrkSegEntMoms->Draw();
  c1->SaveAs("multiFileHistograms/eMinusHists/momCompares/eMinusTrkSegEntMomsTest.pdf");
  c1->Clear();

  eMinusTrkSegMCEntMoms->Draw();
  c1->SaveAs("multiFileHistograms/eMinusHists/momCompares/eMinusTrkSegMCEntMomsTest.pdf");
  c1->Clear();

  eMinusTrkSegTrkSegMCDiff->Draw();
  c1->SaveAs("multiFileHistograms/eMinusHists/momCompares/eMinusTrkSegTrkSegMCDiffTest.pdf");
  c1->Clear();

  eMinusTrkMCSimMoms->Draw();
  c1->SaveAs("multiFileHistograms/eMinusHists/momCompares/eMinusTrkMCSimMomsTest.pdf");
  c1->Clear();

  //Print out the histograms for trkseg, trksegmc, and trkmcsim on the same canvas 
  eMinusTrkMCSimMoms->SetLineColor(kGreen);
  eMinusTrkMCSimMoms->SetTitle("Combined trkseg, trksegmc, and trkmcsim Momenta Histograms");
  eMinusTrkMCSimMoms->Draw();

  eMinusTrkSegEntMoms->SetLineColor(kBlue);
  eMinusTrkSegEntMoms->Draw("SAME");

  eMinusTrkSegMCEntMoms->SetLineColor(kRed);
  eMinusTrkSegMCEntMoms->Draw("SAME");
	
  TLegend* legend = new TLegend(0.8, 0.8, 0.9, 0.9);
  legend->AddEntry(eMinusTrkMCSimMoms, "trkmcsim", "l");
  legend->AddEntry(eMinusTrkSegEntMoms, "trkseg", "l");
  legend->AddEntry(eMinusTrkSegMCEntMoms, "trksegmc", "l");
  legend->Draw();

  c1->SaveAs("multiFileHistograms/eMinusHists/momCompares/eMinus3CompareTest.pdf");

  delete c1;
} 
