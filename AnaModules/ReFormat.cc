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

#include "ReFormat.h"

int main(int argc, char* argv[])
{
  if (argc < 1)
  {
    std::cerr <<"Please give 1 argument " << "inputFileName " << std::endl;
    std::cerr <<"Valid configurations are: " << std::endl;
    std::cerr <<"./ReFormat root://eoscms.cern.ch//eos/cms/store/user/georgia/results_2017_09_21/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_MC13TeV_TTJets_2016_0/171005_184952/0000/analysis_94.root" << std::endl; 
    return -1;
  }
  std::string input_str(argv[1]);
  //std::string output_str = OutputFileNameGenerator(input_str,false);
  std::string output_str = "MVATest.root";

  TChain *originalTree = new TChain("mainNtuplizer/data");
  originalTree->Add(input_str.c_str());
  //int nEntries = originalTree->GetEntries();

  TFile* output = new TFile((output_str).c_str(), "RECREATE");
  TDirectory *mydict = output->mkdir("mainNtuplizer"); mydict->cd();
  TTree* selectedTree = new TTree("data","data");
  
  while (1)
  {
    //std::cout << "NEvent " << << std::endl;

  }
  selectedTree->Write();
  output->Write(); 
  output->Close();

  if (originalTree) delete originalTree;

  //std::string d = "root://cmseos.fnal.gov//store/group/lpcsusyhad/hua/Skimmed_2015Nov15";
  //std::system(("xrdcp " + output_str + " " + d).c_str());
  //std::system(("rm " + output_str).c_str());

  return 0;
}
