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
  std::string firstSpec;

  NTupleReader *tr;
  TLorentzVector metLvec;

  template<typename T> void ArrayToVec( int size, std::string name, const T* var );
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

  void operator()(NTupleReader& tr);
};

inline void passBaselineFunc(NTupleReader &tr, std::string filterstring)
{
  BaselineVessel blv(tr, "", filterstring);
  blv.PassBaseline();
}

#endif
