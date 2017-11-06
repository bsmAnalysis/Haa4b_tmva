#ifndef _CutFlow_H_
#define _CutFlow_H_

#include <string>
#include <iostream>
#include <vector>

#include "TFile.h"
#include "TH1D.h"

#include "UserCode/Haa4bTools/Tools/NTupleReader.h"
#include "UserCode/Haa4bTools/Tools/baselineDef.h"

const double trigger_turn_on_met = 200;
const double cut_mtwmu = 100;
const double cut_mtwel = 100;
const int nth_slash_nametag_MC = 9;
const int nth_slash_nametag_Data = 9;
//root://eoscms.cern.ch//eos/cms/store/user/georgia/results_2017_09_20/SingleElectron/crab_Data13TeV_SingleElectron2016B_ver2_0/170919_052415/0000
inline size_t find_Nth
(
  const std::string & str ,   // where to work
  unsigned            N ,     // N'th ocurrence
  const std::string & find    // what to 'find'
)
{
  if ( 0==N ) { return std::string::npos; }
  size_t pos,from=0;
  unsigned i=0;
  while ( i<N )
  {
    pos=str.find(find,from);
    if ( std::string::npos == pos ) { break; }
    from = pos + 1; // from = pos + find.size();
    ++i;
  }
  return pos;
}

std::string getTag(std::string input_str, bool isData)
{
  //here is a little bit tricky when dealing with the slash... need to improve
  //root://eosuser.cern.ch//eos/user/h/hua/Haa4b/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RF_TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_analysis_24.root
  std::string tag = "";
  if ( isData ) tag = input_str.substr(find_Nth(input_str,nth_slash_nametag_Data,"/") + 1,find_Nth(input_str,nth_slash_nametag_Data+1,"/")-find_Nth(input_str,nth_slash_nametag_Data,"/")-1);
  else tag = input_str.substr(find_Nth(input_str,nth_slash_nametag_MC,"/") + 1,find_Nth(input_str,nth_slash_nametag_MC+1,"/")-find_Nth(input_str,nth_slash_nametag_MC,"/")-1);
  return tag;
}

std::string OutputFileNameGenerator(std::string input_str, bool isData)
{
  //here is a little bit tricky when dealing with the slash... need to improve
  //root://eoscms.cern.ch//eos/cms/store/user/georgia/results_2017_09_21/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_MC13TeV_TTJets_2016_0/171005_184952/0000/analysis_94.root
  std::string tag = "";
  if ( isData ) tag = input_str.substr(find_Nth(input_str,nth_slash_nametag_Data,"/") + 1,find_Nth(input_str,nth_slash_nametag_Data+1,"/")-find_Nth(input_str,nth_slash_nametag_Data,"/")-1);
  else tag = input_str.substr(find_Nth(input_str,nth_slash_nametag_MC,"/") + 1,find_Nth(input_str,nth_slash_nametag_MC+1,"/")-find_Nth(input_str,nth_slash_nametag_MC,"/")-1);
  std::size_t idpos = input_str.find("analysis");
  std::string fileid = input_str.substr (idpos);
  std::string output_str = "CF_" + tag + "_" + fileid;
  std::cout << "Output File Name: " << output_str << std::endl;
  return output_str;
}

class CutFlowHistgram
{
 public:
  void BookHistgram(const char *);
  
  TFile *oFile;
  TH1D *h_b_CutFlow;

  int getUpperBit( const std::vector<bool> &bits );
 private:
  const int TotBit = 10;
};

#endif
