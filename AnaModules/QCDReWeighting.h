#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TChain.h"

#include "Math/QuantFuncMathCore.h"
#include "TMath.h"

struct QCDSampleInfo
{
  std::string QCDTag;
  double weight;
  double xsec_in, nevents_in, lumi_in, kf_in;
  TChain *chain;
};

class QCDSampleWeight
{
 public:
  std::vector<QCDSampleInfo> QCDSampleInfos;
  void QCDSampleInfo_push_back( std::string tag, double xsec, double nevents, double lumi, double kf, const TString &inputFileList, std::string TrainMode );
  void GenLatexTable();
 private:
  bool FillChain(TChain *chain, const TString &inputFileList, std::string tag);
  void removeCharsFromString( std::string &str, char* charsToRemove );
};
