#ifndef ANACONST_CUSTOMIZE_H
#define ANACONST_CUSTOMIZE_H

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "Math/VectorUtil.h"

#include <algorithm>    // std::sort
#include <iostream>
#include <cstdio>
#include <string>
#include <ctime>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <math.h>
/*
   This file is used to customize the NTupleReader and the flat ntuples for our baseline and search region definitions.
   Currently these include jet pt, eta requirements for counting, functions to calculate nJets, nbJets, deltaphi, and so on.
   The functions here have nothing to do with NTupleReader so that can be used in other cases independent of the reader.
   An example baseline cut flow is defined in a separate code, i.e., baselineDef.C.
*/

namespace AnaConsts
{    
  struct MuIsoAccRec
  {
    float minAbsEta, maxAbsEta, minPt, maxPt;
  };

  struct ElIsoAccRec
  {
    float minAbsEta, maxAbsEta, minPt, maxPt;
  };

  struct JetAccRec
  {
    float minAbsEta, maxAbsEta, minPt, maxPt;
  };

  struct SVAccRec
  {
    float minAbsEta, maxAbsEta, minPt, maxPt;
  };

  //then select lepton
  const int nMusSel = 1, nElsSel = 1, nLepSel = 1;
  //                           minAbsEta, maxAbsEta, minPt, maxPt
  const MuIsoAccRec musArr = {   -1,       2.4,      25,     -1   };

  //                           minAbsEta, maxAbsEta, minPt, maxPt
  const ElIsoAccRec elsArr = {   -1,       2.5,      30,     -1,  };
 
  //cut met first
  const float defaultMETcut = 25.0;

  //then calculate mtw
  const float minMtW = 50.0, maxMtW = 250.0;

  //then for jets preselection
  //                         minAbsEta, maxAbsEta, minPt, maxPt
  const JetAccRec jetsArr = {   -1,        2.5,      20,    -1  };
  const float minDeltaRJetMu = 0.4, minDeltaRJetEl= 0.2;

  //then select hard b jets from jet collection
  ////https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation76X
  const float HardBJetsCSVLooseWP = 0.5426, HardBJetsCSVMediumWP = 0.800, HardBJetsCSVTightWP = 0.935;
  const int minNHardBJets = 2, maxNHardBJets = -1;
  const int minNAllBJets = 3, maxNAllBJets = -1;

  //then for svs preselection
  //                       minAbsEta, maxAbsEta, minPt, maxPt
  const SVAccRec svsArr = {   -1,        -1,      0,    20  };
  const float minDeltaRSVJet = 0.4;

  //select soft b jets from sv
  const int minSVnTrk = 3;
  const float maxSVPVdxy = 3.0, minSVPVdxyzSignif = 4.0, minSVPVCosdiffAngle = 0.98;
  
  static std::set<std::string> activatedBranchNames_Common = 
  {
    "hasTrigger", "triggerType",
    "met_pt", "met_phi", // met vector
    "mn", "mn_px_vec", "mn_py_vec", "mn_pz_vec", "mn_en_vec", "mn_passId_vec", "mn_passIso_vec", //muon 
    "en", "en_px_vec", "en_py_vec", "en_pz_vec", "en_en_vec", "en_passId_vec", "en_passIso_vec", //electron 
    "jet", "jet_px_vec", "jet_py_vec", "jet_pz_vec", "jet_en_vec", "jet_btag0_vec", //jet
    "sv", "sv_px_vec", "sv_py_vec", "sv_pz_vec", "sv_en_vec", "sv_ntrk_vec", "sv_dxy_vec", "sv_dxyz_signif_vec", "sv_cos_dxyz_p_vec" //sv 
  };
  /*
  static std::set<std::string> activatedBranchNames_Common =
  {
    //"mn", "mn_px", "mn_py", "mn_pz", "mn_en", "mn_passId", "mn_passIso", //muon 
    //"en", "en_px", "en_py", "en_pz", "en_en", "en_passId", "en_passIso", //electron 
    //"jet", "jet_px", "jet_py", "jet_pz", "jet_en", "jet_btag0", //jet
    //"sv", "sv_px", "sv_py", "sv_pz", "sv_en", "sv_ntrk", "sv_dxy", "sv_dxyz_signif", "sv_cos_dxyz_p", //sv 
    //"met_pt", "met_phi" // met vector
  };
  */
  static std::set<std::string> activatedBranchNames_MCOnly = 
  {
    // Only exist in MC samples
    "genDecayIdxVec", "genDecayLVec", "genDecayMomIdxVec", "genDecayPdgIdVec", "genDecayStrVec", "genDecayMomRefVec"
  };
}

namespace AnaFunctions
{
  //common 
  float DeltaPhi(const TLorentzVector& LvecA, const TLorentzVector& LvecB);
  float DeltaR(const TLorentzVector& LvecA, const TLorentzVector& LvecB);
  //TL sort boolean, from big to small
  bool TLvecSortByM(const TLorentzVector& a, const TLorentzVector& b);
  bool TLvecSortByPt(const TLorentzVector& a, const TLorentzVector& b);

  //muon
  bool passMu(const TLorentzVector& muLvec, bool passId, bool passIso, const AnaConsts::MuIsoAccRec& musArr);
  int countMus(const std::vector<TLorentzVector> &muLvecVec, const std::vector<bool> &passmuId, const std::vector<bool> &passmuIso, const AnaConsts::MuIsoAccRec& musArr, std::vector<TLorentzVector> &selmuLvecVec);
  
  //electron
  bool passEl(const TLorentzVector& elLvec, bool passId, bool passIso, const AnaConsts::ElIsoAccRec& elsArr);
  int countEls(const std::vector<TLorentzVector> &elLvecVec, const std::vector<bool> &passelId, const std::vector<bool> &passelIso, const AnaConsts::ElIsoAccRec& elsArr, std::vector<TLorentzVector> &selelLvecVec);
  
  //calculate mtw
  float calcMtW(TLorentzVector metLvec, TLorentzVector lepLvec);

  //jet pre-selection (for hard b jet, pt>20)
  bool passJetLepClean(const TLorentzVector &jetLvec, const std::vector<TLorentzVector> &selmuLvecVec, const std::vector<TLorentzVector> &selelLvecVec);
  std::vector<bool> preSelJet(const std::vector<TLorentzVector> &jetLvecVec, const AnaConsts::JetAccRec& jetsArr, const std::vector<TLorentzVector> &selmuLvecVec, const std::vector<TLorentzVector> &selelLvecVec);
  //hard b-jet selection
  int countHardBJets(const std::vector<TLorentzVector> &jetLvecVec, const std::vector<bool> & passJetPreSel, const std::vector<bool> &passBTag, std::vector<TLorentzVector> &selhardbLvecVec);
  int countHardBJets(const std::vector<TLorentzVector> &jetLvecVec, const std::vector<bool> & passJetPreSel, const std::vector<float> &BTagCSV, std::vector<TLorentzVector> &selhardbLvecVec);

  //sv pre-selection (for soft b jet, pt<20)
  bool passSVJetClean(const TLorentzVector &svLvec, const std::vector<TLorentzVector> &selhardbLvecVec);
  std::vector<bool> preSelSV(const std::vector<TLorentzVector> &svLvecVec, const AnaConsts::SVAccRec& svsArr, const std::vector<TLorentzVector> &selhardbLvecVec);
  //soft b-jet selection
  std::vector<bool> passSoftBTag(const std::vector<int> sv_ntrk_vec, std::vector<float> sv_dxy_vec, std::vector<float> sv_dxyz_signif_vec, std::vector<float> sv_cos_dxyz_p_vec);
  int countSoftBJets(const std::vector<TLorentzVector> &svLvecVec, const std::vector<bool> & passSVPreSel, const std::vector<bool> &SoftBTag, std::vector<TLorentzVector> &selsoftbLvecVec);

  //MVA variable calculator
  //note, we need pt sorted bjets TLvec vector input in here!! And also note, we are hard coded with 4 bs in here!!
  float calcbbdRAve(const std::vector<TLorentzVector> &mergedBJetsLvecVec_PtSorted);
  float calcbbdMMin(const std::vector<TLorentzVector> &mergedBJetsLvecVec_PtSorted);
  float calcHHt(const std::vector<TLorentzVector> &mergedBJetsLvecVec_PtSorted);
}
#endif
