#include <fstream>
#include <map>
#include <iomanip>
#include <locale>
#include <sstream>
#include <stdlib.h>

#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "TInterpreter.h"

#include "nEvts.h"

int main(int argc, char* argv[])
{
  if (argc < 1)
  {
    std::cerr <<"Please give 1 argument " << "inputFileName " << std::endl;
    std::cerr <<"Valid configurations are: " << std::endl;
    std::cerr <<"./ReFormat root://eoscms.cern.ch//eos/cms/store/user/georgia/results_2017_09_21/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_MC13TeV_TTJets_2016_0/171005_184952/0000/analysis_94.root" << std::endl; 
    return -1;
  }
  ///uscms_data/d3/hwei/Haa4b/signalNtuple/MC13TeV_Wh_amass12_0.root
  //root://eoscms.cern.ch//eos/cms/store/user/georgia/results_2017_09_21/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_MC13TeV_WJets_2016_0/170921_184723/0000/analysis_25.root
  //root://eoscms.cern.ch//eos/cms/store/user/georgia/results_2017_09_21/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/crab_MC13TeV_SingleT_atW_2016_0/170921_184252/0000/analysis_15.root
  std::string input_str(argv[1]);
  
  //set input for handler
  TFile *inputFile = TFile::Open( input_str.c_str() );
  if( inputFile->IsZombie() ) return -1;
  TTree* thisTree = (TTree *)inputFile->Get("mainNtuplizer/data");
  
  float genWeight = 0;
  thisTree->SetBranchAddress("genWeight", &genWeight);
  int nEntries = thisTree->GetEntriesFast();
  std::cout << "NTot " << nEntries << std::endl;

  long long int nPos = 0, nNeg = 0;
  //for ( int iev = 0; iev < 1000; iev++)
  for ( int iev = 0; iev < nEntries; iev++)
  {
    //(*iter_SampleInfos).chain->GetEvent(iev);
    thisTree->GetEntry(iev);
    genWeight > 0 ? nPos++ : nNeg++;
  }

  std::cout << "nPos: " << nPos << ", nNeg: " << nNeg << std::endl;
  inputFile->Close();

  return 0;
}
