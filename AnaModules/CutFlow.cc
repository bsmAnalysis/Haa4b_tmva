#include <fstream>
#include <map>
#include <iomanip>
#include <locale>
#include <sstream>
#include <stdlib.h>

#include "TTree.h"
#include "TChain.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "TInterpreter.h"

#include "CutFlow.h"

void CutFlowHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");
  h_b_CutFlow = new TH1D("h_b_CutFlow", "", TotBit, 0, TotBit);

  return ;
}

int CutFlowHistgram::getUpperBit( const std::vector<bool> &bits )
{
  int n = bits.size();
  if ( n > (TotBit - 1) ){ std::cout << "too many bits! please increase bin" << std::endl; }
  for ( int i = 0; i < n; i++ )
  {
    if ( !bits[i] )
    {
      return i;
    }
  } 

  return 0;
}

int main(int argc, char* argv[])
{
  if (argc < 1)
  {
    std::cerr <<"Please give 1 argument " << "inputFileName " << std::endl;
    std::cerr <<"Valid configurations are: " << std::endl;
    std::cerr <<"./CutFlow root://eosuser.cern.ch//eos/user/h/hua/Haa4b/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RF_TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_analysis_1.root" << std::endl; 
    return -1;
  }
  //root://eosuser.cern.ch//eos/user/h/hua/Haa4b/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RF_TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8_analysis_1.root
  std::string input_str(argv[1]);
  //std::string output_str = OutputFileNameGenerator( input_str, false);
  //std::string output_str = OutputFileNameGenerator( input_str, true);
  std::string output_str = "CF_Test.root";
 
  TChain *originalTree = new TChain("mainNtuplizer/data");
  originalTree->Add(input_str.c_str());
 
  CutFlowHistgram myCutFlowHistgram;
  myCutFlowHistgram.BookHistgram( output_str.c_str() );

  NTupleReader *tr=0;
  tr = new NTupleReader(originalTree, AnaConsts::activatedBranchNames_Common);

  const std::string spec = "Test";
  BaselineVessel *myBaselineVessel = 0;
  myBaselineVessel = new BaselineVessel(*tr, spec);
  tr->registerFunction(*myBaselineVessel);

  while (tr->getNextEvent())
  {
    //std::cout << "NEvent " << tr->getEvtNum() << std::endl;

    std::vector<bool> thisbits;

    thisbits.push_back( true );
    thisbits.push_back( tr->getVar<bool>("passTriggerSel") );
    thisbits.push_back( tr->getVar<bool>("passLeptonSel") );
    thisbits.push_back( tr->getVar<bool>("passMET") );
    thisbits.push_back( tr->getVar<bool>("passMtW") );
    thisbits.push_back( tr->getVar<bool>("passHardBJets") );
    thisbits.push_back( tr->getVar<bool>("passAllBJets") );
    thisbits.push_back( tr->getVar<bool>("passQuaBCat") );
    thisbits.push_back( false );
    //std::cout << "nBJets: " << tr->getVar<int>("nBJets_calcMVA") << std::endl;

    int UpperBit = myCutFlowHistgram.getUpperBit( thisbits );
    thisbits.clear();
    for (int i = 0; i < UpperBit; i++)
    {
      (myCutFlowHistgram.h_b_CutFlow)->Fill(i);
    }
    
    bool passSelPreMVA = tr->getVar<bool>("passSelPreMVA");
    if (passSelPreMVA)
    {
      //std::cout << "NEvent " << tr->getEvtNum() << std::endl;
      //MVA variables
      float WpT     = tr->getVar<float>("WpT_calcMVA");
      float Hmass   = tr->getVar<float>("Hmass_calcMVA");
      float HpT     = tr->getVar<float>("HpT_calcMVA");
      float bbdRAve = tr->getVar<float>("bbdRAve_calcMVA");
      float bbdMMin = tr->getVar<float>("bbdMMin_calcMVA");
      float HHt     = tr->getVar<float>("HHt_calcMVA");
      float WHdR    = tr->getVar<float>("WHdR_calcMVA");
      int nBJets    = tr->getVar<int>("nBJets_calcMVA");
      if (nBJets >= 4) { std::cout << "NBJets " << nBJets << std::endl; }
    }
    
  }

  (myCutFlowHistgram.oFile)->Write();
  (myCutFlowHistgram.oFile)->Close();

  if (originalTree) delete originalTree;

  //std::string d = "root://eosuser.cern.ch//eos/user/h/hua/Haa4b/";
  //std::system(("xrdcp " + output_str + " " + d + getTag( input_str, false) ).c_str());
  //std::system(("xrdcp " + output_str + " " + d + getTag( input_str, true) ).c_str());
  //std::system(("rm " + output_str).c_str());
  return 0;
}
