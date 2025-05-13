//----------------------------------------------------------------------------------

//printEntranceMomentumTest.C
//Written by Andrew Boldy
//University of South Carolina
//Summer 2025

//----------------------------------------------------------------------------------

//Printing the momentum of the entrance for trkseg and trksegmc and then the resolution. 

//----------------------------------------------------------------------------------

//My Inclusions

//Standard Inclusions
#include <string>
#include <fstream>
#include <iostream>

//CERN ROOT Inclusions

//Mu2e Inclusions
#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"
#include "EventNtuple/utils/rooutil/inc/common_cuts.hh"

//Personal Inclusions (if any)

void printEntranceMomentumTest()
{
  string filename = "/exp/mu2e/data/users/aboldy/myfiles.list";
  // Create the histogram you want to fill
  TH1F* hRecoMomRes = new TH1F("hRecoMomRes", "Momentum Resolution at Tracker Entrance", 200,-10,10);
  // Set up RooUtil
  RooUtil util(filename);
  cout << "There are " << util.GetNEvents() << " to go over. Printing momenta from trkseg and trksegmc and their differences." << endl;
  // Loop through the events
  for (int i_event = 0; i_event < util.GetNEvents(); ++i_event)
  {
    // Get the next event
    auto& event = util.GetEvent(i_event);

    // Get the e_minus tracks from the event
    auto e_minus_tracks = event.GetTracks(is_e_minus);

    // Loop through the e_minus tracks
    for (auto& track : e_minus_tracks)
    {

      // Get the track segments at the tracker entrance and has an MC step
      auto trk_ent_segments = track.GetSegments([](TrackSegment& segment){ return tracker_entrance(segment) && has_mc_step(segment) && has_reco_step(segment); });

      // Loop through the tracker entrance track segments
      for (auto& segment : trk_ent_segments)
      {
        cout << "Track Seg Momentum: " << segment.trkseg->mom.R()
        << "   TrackMC Seg Momentum: " << segment.trksegmc->mom.R()
        << "  Resolution: " << segment.trkseg->mom.R() - segment.trksegmc->mom.R() << endl;
        // Fill the histogram
       // hRecoMomRes->Fill(segment.trkseg->mom.R() - segment.trksegmc->mom.R());
      }
    }
  }
}

