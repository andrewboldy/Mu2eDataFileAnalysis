//----------------------------------------------------------------------------------

//ParticleIdentificationFullDataset(string filelist)
//Written by Andrew Boldy
//University of South Carolina
//Spring 2025

//----------------------------------------------------------------------------------

//Modular Approach to printing particle info and particle momentum and the creation of histograms
//Five Helper Files Required as listed in the Inclusions
//INCOMPLETE-->NEED TO COMPLETE displayParticleInfo.C, displayParticleMomentum.C, makePCHists.C, makeMomHists.C, and makePCandMomHists.C

//----------------------------------------------------------------------------------

//My Inclusions

//Regular Inclusions



//ROOT Inclusions


//Including RooUtil

//Including Helper Files 
#include "PIDHelperPrograms/displayParticleInfo.C"
#include "PIDHelperPrograms/displayParticleMomentum.C"
#include "PIDHelperPrograms/makePCHists.C"
#include "PIDHelperPrograms/makeMomHists.C"
#include "PIDHelperPrograms/makePCandMomHists.C"

//Switches
bool DISPLAY_PARTICLE_INFO = true;
bool DISPLAY_PARTICLE_MOMENTUM = true;
bool MAKE_PC_HISTS = true;
bool MAKE_MOM_HISTS = true;
bool MAKE_START_MOM_HISTS = true;
bool MAKE_END_MOM_HISTS = true;
bool MAKE_PC_AND_MOM_HISTS = true;


void ParticleIdentificationFullDataset(string filelist) 
{
  if (DISPLAY_PARTICLE_INFO == true)
  {
    displayParticleInfo(filelist);
  }
  if(DISPLAY_PARTICLE_MOMENTUM == true)
  {
    displayParticleMomentum(filelist);
  }
  if (MAKE_PC_HISTS == true)
  {
    makePCHists(filelist);
  }
  if (MAKE_MOM_HISTS == true)
  {
    makeMomHists(filelist);
  }
  if (MAKE_PC_AND_MOM_HISTS == true)
  {
    makePCandMomHists(filelist);
  }
}

