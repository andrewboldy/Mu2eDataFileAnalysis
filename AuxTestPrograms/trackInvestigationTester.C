#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"
#include "EventNtuple/utils/rooutil/inc/common_cuts.hh"

void trackInvestigationTester()
{
  string filelist = "/exp/mu2e/data/users/aboldy/myfiles.list";
  //Initialize RooUtil
  RooUtil util(filelist);
  int numEvents = util.GetNEvents();
  cout << "There are " << numEvents << " events in the list." << endl;
  cout << "Printing out information from trk branch." << endl;

  for (int i_event = 0; i_event < numEvents; i_event++)
  {
    auto& event = util.GetEvent(i_event);
    auto e_minus_tracks = event.GetTracks(is_e_minus);

    //Printing out the various information from trk and nhits from trkmc in order to test track branch access and code structure.
    for (auto& track : e_minus_tracks)
    {
      cout << "Track PDG: " << track.trk->pdg << "   Track NHits: " << track.trk->nhits << "   TrackMC NHits: " << track.trkmc->nhits << endl;
      for (const auto& mctrack : *(track.trkmcsim))
      {
        //        cout << mctrack << endl;
        //        cout << track.trkmcsim << endl;
        //        for (const auto& sim : mctrack)
        //        {
          cout << "Track Mom: " << mctrack.pdg << endl;
          //        }
      }
     }
  }
}
