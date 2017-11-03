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

  NTupleReader *tr;
  TLorentzVector metLvec;
  //PreProcessing()
  template<typename T> void ArrayToVec( int size, std::string name, const T* var );
  std::vector<TLorentzVector> ConstructVecLVec( std::vector<float> px, std::vector<float> py, std::vector<float> pz, std::vector<float> en );
  //PassBaseline()
  void prepareWHMVA( const std::vector<TLorentzVector>& selmuLvecVec, const std::vector<TLorentzVector>& selelLvecVec, const TLorentzVector& metLvec, const std::vector<TLorentzVector>& selhardbLvecVec, const std::vector<TLorentzVector>& selsoftbLvecVec, std::string MVATag);

 public:
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Member ~~~~~
  bool debug;

  bool passBaseline;
  bool passSelPreMVA;

  BaselineVessel(NTupleReader &tr_, const std::string specialization = "", const std::string filterString = "");
  ~BaselineVessel();

  void PreProcessing();
  void PassBaseline();

  void operator()(NTupleReader& tr);
};

inline void passBaselineFunc(NTupleReader &tr, std::string filterstring)
{
  BaselineVessel blv(tr, "", filterstring);
  blv.PassBaseline();
}

#endif
