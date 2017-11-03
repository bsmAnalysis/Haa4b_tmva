#ifndef ANABASELINE_BASELINEDEF_H
#define ANABASELINE_BASELINEDEF_H

#include "NTupleReader.h"
#include "customize.h"
//#include "EventListFilter.h"

#include "Math/VectorUtil.h"

#include <memory>
#include <iostream>

class TFile;
class TF1;

class BaselineVessel
{
 private:
  std::string spec;
  bool isfastsim;
  std::string firstSpec;
  bool printOnce;

  NTupleReader *tr;
  TFile *WMassCorFile;
  TF1   *puppisd_corrGEN;
  TF1   *puppisd_corrRECO_cen;
  TF1   *puppisd_corrRECO_for;
  TLorentzVector metLVec;

  void ArrayToVec( int size, std::string name );
  std::vector<TLorentzVector> ConstructVecLVec( std::vector<float> px, std::vector<float> py, std::vector<float> pz, std::vector<float> en );
 public:
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Member ~~~~~
  // Obtain all TLVec vectors
  void PreProcessing();
  
  int  bToFake;
  bool debug;
  bool incZEROtop;
  bool UseLepCleanJet;

  std::string jetVecLabel;
  std::string CSVVecLabel;
  std::string METLabel;
  std::string METPhiLabel;
  std::string jetVecLabelAK8;
  std::string muonsFlagIDLabel;
  std::string elesFlagIDLabel;
  std::string qgLikehoodLabel;
  std::string toptaggerCfgFile;
  bool doIsoTrksVeto;
  bool doMuonVeto;
  bool doEleVeto;
  bool doMET;
  bool dodPhis;
  bool passBaseline;

  BaselineVessel(NTupleReader &tr_, const std::string specialization = "", const std::string filterString = "");
  ~BaselineVessel();

  void PassBaseline();
  bool passNoiseEventFilterFunc();
  bool passQCDHighMETFilterFunc();
  bool passFastsimEventFilterFunc();
  bool PredefineSpec();
  bool UseLepCleanJets();
  bool OpenWMassCorrFile();

  void operator()(NTupleReader& tr);

  bool GetMHT() const;
  bool GetLeptons() const;
  bool GetRecoZ( const int zMassMin, const int zMassMax) const;
  bool GetRecoZ(const std::string leptype, const std::string lepchg, std::vector<TLorentzVector>* recoZVec,
  std::map<unsigned int, std::pair<unsigned int, unsigned int> > *TypeZLepIdx, 
  const int zMassMin, const int zMassMax) const;
};

inline void passBaselineFunc(NTupleReader &tr, std::string filterstring)
{
  BaselineVessel blv(tr, "", filterstring);
  blv.PassBaseline();
  blv.GetMHT();
}

#endif
