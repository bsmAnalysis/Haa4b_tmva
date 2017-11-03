#ifndef ANACONST_CUSTOMIZE_H
#define ANACONST_CUSTOMIZE_H

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "Math/VectorUtil.h"

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

  //cut met first
  const float defaultMETcut = 25.0;
  
  //then select lepton
  const int nMusSel = 1, nElsSel = 1;
  //                           minAbsEta, maxAbsEta, minPt, maxPt
  const MuIsoAccRec musArr = {   -1,       2.4,      25,     -1   };

  //                           minAbsEta, maxAbsEta, minPt, maxPt
  const ElIsoAccRec elsArr = {   -1,       2.5,      30,     -1,  };
  
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
  const int minNAllBJets = 3, maxNAllBJets = 4;

  //then for svs preselection
  //                       minAbsEta, maxAbsEta, minPt, maxPt
  const SVAccRec svsArr = {   -1,        -1,      0,    20  };
  const float minDeltaRSVJet = 0.4;

  //select soft b jets from sv
  const int minSVnTrk = 3;
  const float maxSVPVdxy = 3.0, minSVPVdxyzSignif = 4.0, minSVPVCosdiffAngle = 0.98;

  static std::set<std::string> activatedBranchNames_DataOnly = 
  { 
    "run", "lumi", "event", "evtWeight", 
    "jetsLVec", "recoJetsBtag_0", "muMatchedJetIdx", "eleMatchedJetIdx", "looseisoTrksMatchedJetIdx", "trksForIsoVetoMatchedJetIdx",
    "recoJetsJecUnc", "recoJetsJecScaleRawToFull",
    "muonsLVec", "muonsMtw", "muonsRelIso", "muonsMiniIso", "muonsFlagMedium", "muonsFlagTight", "muonspfActivity",
    "elesLVec", "elesMtw", "elesRelIso", "elesMiniIso", "elesisEB", "elesFlagVeto", "elesFlagMedium", "elespfActivity",
    "loose_isoTrksLVec", "loose_isoTrks_iso", "loose_isoTrks_mtw", "loose_isoTrks_pdgId",
    "met", "metphi", 
    "tru_npv", "vtxSize",
    "recoJetsBtag_0_LepCleaned", "jetsLVecLepCleaned",
    "recoJetschargedEmEnergyFraction", "recoJetsneutralEmEnergyFraction", "recoJetschargedHadronEnergyFraction", "recoJetsmuonEnergyFraction",
    //"looseJetID", "tightJetID", "looseJetID_NoLep", "tightJetID_NoLep", "CSCTightHaloFilter", "EcalDeadCellTriggerPrimitiveFilter", "HBHENoiseFilter", "HBHEIsoNoiseFilter",
    "looseJetID", "tightJetID", "looseJetID_NoLep", "tightJetID_NoLep", "EcalDeadCellTriggerPrimitiveFilter", "HBHENoiseFilter", "HBHEIsoNoiseFilter", "goodVerticesFilter", "eeBadScFilter", "eeBadScListFilter", "CSCTightHaloListFilter", "badResolutionTrackListFilter", "muonBadTrackListFilter",
    "TriggerNames", "PassTrigger", "TriggerPrescales", 
    "stored_weight",
    "globalTightHalo2016Filter", "BadChargedCandidateFilter", "BadPFMuonFilter",
    "calomet"
  };

  static std::set<std::string> activatedBranchNames = 
  {
    // Only exist in MC samples
    "genDecayIdxVec", "genDecayLVec", "genDecayMomIdxVec", "genDecayPdgIdVec", "genDecayStrVec", "genDecayMomRefVec",
    "W_emuVec", "W_tau_emuVec", "W_tau_prongsVec", "W_tau_nuVec",
    "genHT", "PDFweights", "PDFids",
    "id1", "id2", "x1", "x2", "q",
    "W_emu_pfActivityVec", "W_tau_emu_pfActivityVec", "W_tau_prongs_pfActivityVec", "ScaleWeightsMiniAOD",
    "recoJetsJecUncLepCleaned", "metMagUp", "metMagDown", "metPhiUp", "metPhiDown",
    "SusyMotherMass", "SusyLSPMass", "recoJetsFlavor",
    "genjetsLVec", "genmet", "genmetphi",
    "NJetsISR",
    "specialFixtype", "specialFixMuonsCharge", "specialFixMuonsLVec"
  };
}

namespace AnaFunctions
{
  //common 
  float DeltaPhi(const TLorentzVector& LvecA, const TLorentzVector& LvecB);
  float DeltaR(const TLorentzVector& LvecA, const TLorentzVector& LvecB);
  
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

}

#endif
