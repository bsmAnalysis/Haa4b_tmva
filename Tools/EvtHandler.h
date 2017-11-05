#ifndef dataevtsummaryhandler_h
#define dataevtsummaryhandler_h

#include <string.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <set>
#include <cmath>

#include "Math/LorentzVector.h"
#include "TMath.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TTree.h"
#include "TLorentzVector.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double>> LorentzVector;
typedef std::vector<LorentzVector> LorentzVectorCollection;

#define MAXPARTICLES 50
#define MAXMCPARTICLES 250
#define MAXLHEWEIGHTS 500

struct DataEvtSummary_t
{
  Int_t run,lumi;
  Long64_t event;
  
  Bool_t hasTrigger;
  Int_t triggerType;

  //muon
  Int_t mn;
  Float_t mn_px[MAXPARTICLES],mn_py[MAXPARTICLES],mn_pz[MAXPARTICLES],mn_en[MAXPARTICLES];
  Int_t mn_id[MAXPARTICLES], mn_type[MAXPARTICLES];
  Float_t mn_d0[MAXPARTICLES],mn_dZ[MAXPARTICLES],mn_ip3d[MAXPARTICLES],mn_ip3dsig[MAXPARTICLES];
  Bool_t mn_IsLoose[MAXPARTICLES],mn_IsMedium[MAXPARTICLES],mn_IsTight[MAXPARTICLES],mn_IsSoft[MAXPARTICLES],mn_IsHighPt[MAXPARTICLES];
  Float_t mn_pileupIsoR03[MAXPARTICLES],mn_chargedIsoR03[MAXPARTICLES],mn_photonIsoR03[MAXPARTICLES],mn_neutralHadIsoR03[MAXPARTICLES];
  Float_t mn_pileupIsoR04[MAXPARTICLES],mn_chargedIsoR04[MAXPARTICLES],mn_photonIsoR04[MAXPARTICLES],mn_neutralHadIsoR04[MAXPARTICLES];
  Bool_t mn_passId[MAXPARTICLES],mn_passIdLoose[MAXPARTICLES],mn_passSoftMuon[MAXPARTICLES],mn_passIso[MAXPARTICLES];
  Float_t mn_nMatches[MAXPARTICLES],mn_nMatchedStations[MAXPARTICLES],mn_validMuonHits[MAXPARTICLES],mn_innerTrackChi2[MAXPARTICLES],mn_trkLayersWithMeasurement[MAXPARTICLES],mn_pixelLayersWithMeasurement[MAXPARTICLES];

  //electron
  Int_t en;
  Float_t en_px[MAXPARTICLES],en_py[MAXPARTICLES],en_pz[MAXPARTICLES],en_en[MAXPARTICLES];
  Int_t en_id[MAXPARTICLES];
  Float_t en_pileupIso[MAXPARTICLES],en_chargedIso[MAXPARTICLES],en_photonIso[MAXPARTICLES],en_neutralHadIso[MAXPARTICLES];
  Float_t en_relIsoWithEA[MAXPARTICLES],en_relIsoWithDBeta[MAXPARTICLES],en_MissingHits[MAXPARTICLES],en_passConversionVeto[MAXPARTICLES];
  Bool_t en_passVeto[MAXPARTICLES],en_passLoose[MAXPARTICLES],en_passMedium[MAXPARTICLES],en_passTight[MAXPARTICLES],en_passHEEP[MAXPARTICLES];
  Bool_t en_passMVATrigMedium[MAXPARTICLES], en_passMVATrigTight[MAXPARTICLES];
  Float_t en_IDMVATrigValue[MAXPARTICLES];
  Int_t   en_IDMVATrigCategory[MAXPARTICLES];
  Int_t en_istrue[MAXPARTICLES];
  Bool_t en_passId[MAXPARTICLES],en_passIdLoose[MAXPARTICLES],en_passIso[MAXPARTICLES];

  //jet (ak4PFJetsCHS)
  Int_t jet;
  Float_t jet_px[MAXPARTICLES],jet_py[MAXPARTICLES],jet_pz[MAXPARTICLES],jet_en[MAXPARTICLES];
  Float_t jet_btag0[MAXPARTICLES]; //,jet_btag1[MAXPARTICLES],jet_btag2[MAXPARTICLES],jet_btag3[MAXPARTICLES];
  Float_t jet_mass[MAXPARTICLES],jet_area[MAXPARTICLES],jet_pu[MAXPARTICLES],jet_puId[MAXPARTICLES],jet_genpt[MAXPARTICLES];
  Bool_t jet_PFLoose[MAXPARTICLES], jet_PFTight[MAXPARTICLES];
  Int_t jet_partonFlavour[MAXPARTICLES], jet_hadronFlavour[MAXPARTICLES], jet_mother_id[MAXPARTICLES];
  Float_t jet_parton_px[MAXPARTICLES], jet_parton_py[MAXPARTICLES], jet_parton_pz[MAXPARTICLES], jet_parton_en[MAXPARTICLES];


  //sv : Inclusive Secondary Vertices from slimmedSecondaryVertices
  Int_t sv ;
  Float_t sv_px[MAXPARTICLES], sv_py[MAXPARTICLES], sv_pz[MAXPARTICLES], sv_en[MAXPARTICLES] ;
  Int_t   sv_ntrk[MAXPARTICLES] ;
  Float_t sv_dxy[MAXPARTICLES], sv_dxyz[MAXPARTICLES], sv_dxyz_signif[MAXPARTICLES] ;
  Float_t sv_cos_dxyz_p[MAXPARTICLES] ;
  Float_t sv_chi2[MAXPARTICLES], sv_ndof[MAXPARTICLES] ;
  Int_t   sv_mc_nbh_moms[MAXPARTICLES] ;
  Int_t   sv_mc_nbh_daus[MAXPARTICLES] ;
  Int_t   sv_mc_mcbh_ind[MAXPARTICLES] ;

  //met
  Float_t met_pt,met_phi,met_sumMET;
  Float_t metNoHF_pt,metNoHF_phi,metNoHF_sumMET;
  Float_t metPuppi_pt,metPuppi_phi,metPuppi_sumMET;
  Float_t rawpfmet_pt,rawpfmet_phi,rawpfmet_sumMET;
  Float_t rawcalomet_pt,rawcalomet_phi,rawcalomet_sumMET;
};

class DataEvtSummaryHandler 
{
 public:
  //
  DataEvtSummaryHandler();
  ~DataEvtSummaryHandler();

  //current event
  DataEvtSummary_t evSummary_;
  DataEvtSummary_t &getEvent() 
  {
    return evSummary_;
  }

  //write mode
  bool initTree(TTree *t);
  void fillTree();

  //read mode
  bool attachToTree(TTree *t);
  int getEntries() { return (t_ ? t_->GetEntriesFast() : 0); }
  void getEntry(int ientry)
  {
    resetStruct();
    if(t_) t_->GetEntry(ientry);
  }

  void resetStruct();

 private:
  //the tree
  TTree *t_;
};

#endif
