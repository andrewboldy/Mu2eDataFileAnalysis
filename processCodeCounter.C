//Particle Process Code Counter
//Written by Andrew Boldy
//University of South Carolina
//Spring 2025

//Standard inclusions
#include <string>
#include <fstream>
#include <iostream>

#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"

void processCodeCounter()
{
    int eMinusCounter[194] = {0}; //create a count array and initializes the counter to 0
    int ePlusCounter[194] = {0};
    int muMinusCounter[194] = {0};
    int protonCounter[194] = {0};
    int deuteronCounter[194] = {0};
    string filename = "/pnfs/mu2e/tape/phy-nts/nts/mu2e/CeEndpointMix1BBTriggered/MDC2020an_v06_01_01_best_v1_3/root/04/2e/nts.mu2e.CeEndpointMix1BBTriggered.MDC2020an_v06_01_01_best_v1_3.001210_00000046.root";
    //initialize RooUtil to begin reading files
    RooUtil util(filename);
    int eventNumber = util.GetNEvents();
    cout << filename << " has " << eventNumber << " entries.";

    for (int i_event=0; i_event < eventNumber;i_event++)
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
                            eMinusCounter[sim.startCode]++;
                        }
                        if (sim.pdg == -11)
                        {
                            ePlusCounter[sim.startCode]++;
                        }
                        if (sim.pdg == 13)
                        {
                            muMinusCounter[sim.startCode]++;
                        }
                        if (sim.pdg == 2212)
                        {
                            protonCounter[sim.startCode]++;
                        }
                        if (sim.pdg == 1000010020)
                        {
                            deuteronCounter[sim.startCode]++;
                        }
                    }
                } 
            }
        }
    cout << "Printing Counts by Particle for Nonzero Instances of Process Codes" << endl;

    cout << "Electron Process Code Counts:" << endl;
    for (int eMinusCounterElement=0; eMinusCounterElement<194; eMinusCounterElement++)
    {
        if (eMinusCounter[eMinusCounterElement] != 0)
        {
            cout << "Process Code " << eMinusCounterElement << " has " << eMinusCounter[eMinusCounterElement] << " entires" << endl;
        }
    }

    cout << "Postron Process Code Counts:" << endl;
    for (int ePlusCounterElement=0; ePlusCounterElement<194; ePlusCounterElement++)
    {
        if (ePlusCounter[ePlusCounterElement] != 0)
        {
            cout << "Process code " << ePlusCounterElement << " has " << ePlusCounter[ePlusCounterElement] << " entries." << endl;
        }
    }
    cout << "Muon Process Code Counts:" << endl;
    for (int muMinusCounterElement=0; muMinusCounterElement<194; muMinusCounterElement++)
    {
        if (muMinusCounter[muMinusCounterElement] != 0)
        {
            cout << "Process code " << muMinusCounterElement << " has " << muMinusCounter[muMinusCounterElement] << " entries." << endl;
        }
    }
    cout << "Proton Process Code Counts:" << endl;
    for (int protonCounterElement=0; protonCounterElement<194; protonCounterElement++)
    {
        if (protonCounter[protonCounterElement] != 0)
        {
            cout << "Process Code " << protonCounterElement << " has " << protonCounter[protonCounterElement] << " entries" << endl;
        }
    }
    cout << "Deuteron Process Code Counts:" << endl;
    for (int deuteronCounterElement=0; deuteronCounterElement<194; deuteronCounterElement++)
    {
        if (deuteronCounter[deuteronCounterElement] != 0)
        {
            cout << "Process Code " << deuteronCounterElement << " has " << deuteronCounter[deuteronCounterElement] << " entries." << endl;
        }
    }
}
