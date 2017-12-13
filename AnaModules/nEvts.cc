#include <fstream>
#include <map>
#include <iomanip>
#include <locale>
#include <sstream>
#include <stdlib.h>
#include <fstream>

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
    std::cerr <<"./nEvt FileText.txt" << std::endl; 
    return -1;
  }
  ///uscms_data/d3/hwei/Haa4b/signalNtuple/MC13TeV_Wh_amass12_0.root
  //root://eoscms.cern.ch//eos/cms/store/user/georgia/results_2017_09_21/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_MC13TeV_WWW_4F_2016_0/170921_183958/0000/analysis_1.root
  //root://eoscms.cern.ch//eos/cms/store/user/georgia/results_2017_09_21/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_MC13TeV_WWZ_2016_0/170921_183914/0000/analysis_1.root
  //root://eoscms.cern.ch//eos/cms/store/user/georgia/results_2017_09_21/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_MC13TeV_WZZ_2016_0/170921_183833/0000/analysis_1.root
  //root://eoscms.cern.ch//eos/cms/store/user/georgia/results_2017_09_21/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_MC13TeV_ZZZ_2016_0/170921_183749/0000/analysis_1.root
  //root://eoscms.cern.ch//eos/cms/store/user/georgia/results_2017_09_21/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_MC13TeV_TTJets_2016_0/171005_184952/0000/analysis_1.root
  
  std::string input_str(argv[1]);
  /* 
  //set input for handler
  TFile *inputFile = TFile::Open( input_str.c_str() );
  if( inputFile->IsZombie() ) return -1;
  TH1F* nevtH = (TH1F *) inputFile->Get("mainNtuplizer/nevents");
  TH1F* posH = (TH1F *) inputFile->Get("mainNtuplizer/n_posevents");
  TH1F* negH = (TH1F *) inputFile->Get("mainNtuplizer/n_negevents");
  std::cout << "Read from histo: " << std::endl;
  std::cout << "nTot: " << nevtH->GetBinContent(1) << std::endl;
  if( posH && negH ) std::cout << posH->GetBinContent(1) << " - " << negH->GetBinContent(1) << std::endl;
  inputFile->Close();
  */
  
  std::ifstream inputFile( input_str );
  std::cout << "File list name: " << input_str << std::endl;
  std::vector<std::string> fnames;
  for( std::string line; getline( inputFile, line ); )
  {
    fnames.push_back(line);
  }
  long long int nTot = 0;
  long long int nPos = 0, nNeg = 0;
  for (int i = 0; i < fnames.size(); i++)
  {
    TFile *inputFile = TFile::Open( fnames.at(i).c_str() );
    if( inputFile->IsZombie() ) return -1;
    TH1F* nevtH = (TH1F *) inputFile->Get("mainNtuplizer/nevents");
    TH1F* posH = (TH1F *) inputFile->Get("mainNtuplizer/n_posevents");
    TH1F* negH = (TH1F *) inputFile->Get("mainNtuplizer/n_negevents");

    nTot += nevtH->GetBinContent(1);  
    nPos += posH->GetBinContent(1);
    nNeg += negH->GetBinContent(1);
    //std::cout << "Read from histo: " << std::endl;
    //std::cout << "nTot: " << nevtH->GetBinContent(1) << std::endl;
    //if( posH && negH ) std::cout << posH->GetBinContent(1) << " - " << negH->GetBinContent(1) << std::endl;
    inputFile->Close();
  }
  std::cout << "nTot: " << nTot << std::endl;
  std::cout << "nPos: " << nPos << ", nNeg: " << nNeg << std::endl;
  std::cout << nPos << " - " << nNeg << std::endl;
  
  /*
  TChain *chain = new TChain("mainNtuplizer/data");
  for (int i = 0; i < fnames.size(); i++)
  {
    chain->Add(fnames.at(i).c_str());
  }
  chain->SetBranchStatus("*", 0);
  //TTree* thisTree = (TTree *)inputFile->Get("mainNtuplizer/data");  
  float genWeight = 0;
  //thisTree->SetBranchAddress("genWeight", &genWeight);
  //int nEntries = thisTree->GetEntriesFast();
  chain->SetBranchStatus("genWeight", 1);
  chain->SetBranchAddress("genWeight", &genWeight);
  int nEntries = chain->GetEntries();
  std::cout << "Read from Tree: " << std::endl;
  std::cout << "NTot " << nEntries << std::endl;

  long long int nPos = 0, nNeg = 0;
  for ( int iev = 0; iev < nEntries; iev++)
  {
    //if ( iev%20000 == 0){ std::cout << iev << " events proceed!"<< std::endl; }
    chain->GetEvent(iev);
    //thisTree->GetEntry(iev);
    genWeight > 0 ? nPos++ : nNeg++;
  }

  std::cout << "nPos: " << nPos << ", nNeg: " << nNeg << std::endl;
  std::cout << nPos << " - " << nNeg << std::endl;
  */
  //inputFile->Close();
  return 0;
}
