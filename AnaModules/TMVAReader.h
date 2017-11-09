#ifndef tmvaReader_h
#define tmvaReader_h

#include <iostream>
#include <vector>
#include <string>
#include <utility>      // std::pair, std::make_pair

#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include "TString.h"
#include "TFile.h"
#include "TTree.h"

class TMVAReader
{
 public:
  Float_t WpT, Hmass, HpT, bbdRAve, bbdMMin, HHt, WHdR;
  TMVA::Reader *myreader;

  void InitTMVAReader();
  void SetupMVAReader( std::string methodName, std::string modelPath );
  float GenReMVAReader(
                       float thisWpT,
                       float thisHmass, float thisHpT, float thisbbdRAve, float thisbbdMMin, float thisHHt, 
                       float thisWHdR,
                       std::string methodName
                      );
  void CloseMVAReader();

 private:

};
#endif
