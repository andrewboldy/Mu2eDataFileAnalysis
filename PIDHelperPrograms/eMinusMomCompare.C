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
  
  TH1F* eMinusTrkSegEntMoms = new TH1F("eMinusTrkSegEntMoms", "MDC2020anBestTest e Minus Momenta (MeV/c) at entrance from trkseg Branch",100,-0.5, 150);
  eMinusTrkSegEntMoms->GetXaxis()->SetTitle("Tracker Reco Entrance Momentum (MeV/c)");
  eMinusTrkSegEntMoms->SetStats(0);

  TH1F* eMinusTrkSegMCEntMoms = new TH1F("eMinusTrkSegMCEntMoms", "MDC2020anBestTest e Minus Momenta (MeV/c) at entrance from trksegmc Branch",100, -0.5, 150);
  eMinusTrkSegMCEntMoms->GetXaxis()->SetTitle("Tracker True Entrance Momentum (MeV/c)");
  eMinusTrkSegMCEntMoms->SetStats(0);

  TH1F* eMinusTrkMCSimMoms = new TH1F("eMinusTrkMCSimMoms", "MDC2020anBestTest e Minus Momenta (MeV/c) for rank 0 electrons from trkmcsim Branch", 100, -0.5, 150);
  eMinusTrkMCSimMoms->GetXaxis()->SetTitle("Thrown Simulated Momentum (MeV/c)");
  eMinusTrkMCSimMoms->SetStats(0);
  
  TH1F* eMinusTrkSegTrkSegMCDiff = new TH1F("eMinusTrkSegTrkSegMCDiff", "MDC2020anBestTest e Minus Momentum Difference (MeV/c) Between trkseg and trksegmc Branches", 50, -5,5);
  eMinusTrkSegTrkSegMCDiff->GetXaxis()->SetTitle("trkseg and trksegmc Momentum Differences (MeV/c)");
  eMinusTrkSegTrkSegMCDiff->SetStats(0);
  
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
    }
  }
  //Print out the Histograms on different canvases and then put them together just to see 
  eMinusTrkSegEntMoms->Draw();
  c1->SaveAs("multiFileHistograms/eMinusHists/momCompares/eMinusTrkSegEntMoms.pdf");
  c1->Clear();

  eMinusTrkSegMCEntMoms->Draw();
  c1->SaveAs("multiFileHistograms/eMinusHists/momCompares/eMinusTrkSegMCEntMoms.pdf");
  c1->Clear();

  eMinusTrkSegTrkSegMCDiff->Draw();
  c1->SaveAs("multiFileHistograms/eMinusHists/momCompares/eMinusTrkSegTrkSegMCDiff.pdf");
  c1->Clear();

  eMinusTrkMCSimMoms->Draw();
  c1->SaveAs("multiFileHistograms/eMinusHists/momCompares/eMinusTrkMCSimMoms.pdf");
  c1->Clear();

  //Print out the histograms for trkseg, trksegmc, and trkmcsim on the same canvas 
  eMinusTrkSegEntMoms->SetLineColor(kBlue);
  eMinusTrkSegEntMoms->Draw("HIST E");

  eMinusTrkSegMCEntMoms->SetLineColor(kRed);
  eMinusTrkSegMCEntMoms->Draw("HIST E SAME");

  eMinusTrkMCSimMoms->SetLineColor(kGreen);
  eMinusTrkMCSimMoms->Draw("HIST E SAME");

  c1->SaveAs("multiFileHistograms/eMinusHists/momCompares/eMinus3Compare.pdf");
  c1->Clear();
  delete c1;
} 
