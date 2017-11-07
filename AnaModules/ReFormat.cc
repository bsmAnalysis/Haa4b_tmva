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
  //root://eoscms.cern.ch//eos/cms/store/user/georgia/results_2017_09_21/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_MC13TeV_WJets_2016_0/170921_184723/0000/analysis_25.root
  //root://eoscms.cern.ch//eos/cms/store/user/georgia/results_2017_09_21/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/crab_MC13TeV_SingleT_atW_2016_0/170921_184252/0000/analysis_15.root
  std::string input_str(argv[1]);
  //std::string output_str = OutputFileNameGenerator( input_str, false);
  std::string output_str = OutputFileNameGenerator( input_str, true);
  //std::string output_str = "Test.root";
  
  //handler
  EvtHandler Handler_;

  //set input for handler
  TFile *inputFile = TFile::Open( input_str.c_str() );
  if( inputFile->IsZombie() ) return -1;
  Handler_.attachToTree( (TTree *)inputFile->Get("mainNtuplizer/data") );
  int nEntries = Handler_.getEntries();
  std::cout << "NTot " << nEntries << std::endl;

  //set out put for handler
  TFile* output = new TFile((output_str).c_str(), "RECREATE");
  TDirectory *mydict = output->mkdir("mainNtuplizer"); mydict->cd();
  TTree* selectedTree = new TTree("data","data");
  Handler_.initTree( selectedTree );
 
  //for ( int iev = 0; iev < 1000; iev++)
  for ( int iev = 0; iev < nEntries; iev++)
  {
    //##############################################   EVENT LOOP STARTS   ##############################################
    //load the event content from tree
    Handler_.getEntry(iev);
    Handler_.VecGenerator();
    Handler_.fillTree();
    //DataEvtContainer &ev = Handler_.getEvent();
    //std::cout << "NEvent " << iev << ", Event " << ev.event << std::endl;
  }

  selectedTree->Write();
  output->Write(); 
  output->Close();

  inputFile->Close();

  //std::string d = "root://eosuser.cern.ch//eos/user/h/hua/Haa4b/";
  std::string d = "root://eosuser.cern.ch//eos/user/h/hua/Haa4b/Data";
  //std::system( ( "xrdcp " + output_str + " " + d + getTag( input_str, false) ).c_str() );
  //std::system( ( "xrdcp " + output_str + " " + d + getTag( input_str, true) ).c_str() );
  std::system( ( "xrdcp " + output_str + " " + d ).c_str() );
  std::system( ( "rm " + output_str ).c_str() );
  return 0;
}
