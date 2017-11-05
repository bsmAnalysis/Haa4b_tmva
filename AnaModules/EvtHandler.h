#ifndef dataevtsummaryhandler_h
#define dataevtsummaryhandler_h

#include <string.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <set>
#include <cmath>
#include <vector>

#include "TMath.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TChain.h"

#define MAXPARTICLES 50

struct DataEvtContainer
{
  int run,lumi;
  Long64_t event;
  
  bool hasTrigger;
  int triggerType;

  //muon
  int mn;
  float mn_px[MAXPARTICLES], mn_py[MAXPARTICLES], mn_pz[MAXPARTICLES], mn_en[MAXPARTICLES];
  bool mn_passId[MAXPARTICLES], mn_passIso[MAXPARTICLES];
  std::vector<float> mn_px_vec, mn_py_vec, mn_pz_vec, mn_en_vec;
  std::vector<bool> mn_passId_vec, mn_passIso_vec;

  //electron
  int en;
  float en_px[MAXPARTICLES], en_py[MAXPARTICLES], en_pz[MAXPARTICLES], en_en[MAXPARTICLES];
  bool en_passId[MAXPARTICLES], en_passIso[MAXPARTICLES];
  std::vector<float> en_px_vec, en_py_vec, en_pz_vec, en_en_vec;
  std::vector<bool> en_passId_vec, en_passIso_vec;

  //jet (ak4PFJetsCHS)
  int jet;
  float jet_px[MAXPARTICLES],jet_py[MAXPARTICLES],jet_pz[MAXPARTICLES],jet_en[MAXPARTICLES];
  float jet_btag0[MAXPARTICLES];
  //bool jet_PFLoose[MAXPARTICLES];
  std::vector<float> jet_px_vec, jet_py_vec, jet_pz_vec, jet_en_vec;
  std::vector<float> jet_btag0_vec;
  //std::vector<bool> jet_PFLoose_vec;

  //sv : Inclusive Secondary Vertices from slimmedSecondaryVertices
  int sv ;
  float sv_px[MAXPARTICLES], sv_py[MAXPARTICLES], sv_pz[MAXPARTICLES], sv_en[MAXPARTICLES];
  int sv_ntrk[MAXPARTICLES];
  float sv_dxy[MAXPARTICLES], sv_dxyz_signif[MAXPARTICLES], sv_cos_dxyz_p[MAXPARTICLES];
  std::vector<float> sv_px_vec, sv_py_vec, sv_pz_vec, sv_en_vec;
  std::vector<int> sv_ntrk_vec;
  std::vector<float> sv_dxy_vec, sv_dxyz_signif_vec, sv_cos_dxyz_p_vec;

  //met
  float met_pt, met_phi;
};

class EvtHandler 
{
 public:
  //
  EvtHandler();
  ~EvtHandler();

  //current event
  DataEvtContainer evSummary_;
  DataEvtContainer &getEvent() 
  {
    return evSummary_;
  }

  //read mode, from array
  bool attachToTree(TTree *t);
  int getEntries() { return (ti ? ti->GetEntriesFast() : 0); }
  void getEntry(int ientry)
  {
    resetStruct();
    if(ti) ti->GetEntry(ientry);
    return ;
  }
  void resetStruct();

  //array to vector, for all array variables needed
  void VecGenerator();

  //write mode, to vector
  bool initTree(TTree *t);
  void fillTree();

 private:
  //the tree
  TTree *ti;
  TTree *to;
  template<typename T> void ArrToVec( int size, const T arr[], std::vector<T>& vec )
  {
    //int n = arr.size();
    for (int i = 0; i < size; i++)
    {
      vec.push_back( arr[i] );
    }
    return ;
  }
};

#endif
