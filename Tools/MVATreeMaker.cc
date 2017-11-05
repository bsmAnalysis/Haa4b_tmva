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

#include "MVATreeMaker.h"

int main(int argc, char* argv[])
{
  if (argc < 1)
  {
    std::cerr <<"Please give 1 argument " << "inputFileName " << std::endl;
    std::cerr <<"Valid configurations are: " << std::endl;
    std::cerr <<"./MVATreeMaker root://cmseos.fnal.gov//store/user/lpcsusyhad/Spring16_80X_Jun_2016_Ntp_v5X/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Spring16_80X_Jun_2016_Ntp_v5p0_QCD_HT2000toInf_ext1/160609_112453/0000/stopFlatNtuples_105.root" << std::endl;
    return -1;
  }
  std::string input_str(argv[1]);
  //std::string output_str = OutputFileNameGenerator(input_str,false);
  std::string output_str = "MVATest.root";

  TChain *originalTree = new TChain("mainNtuplizer/data");
  originalTree->Add(input_str.c_str());
   
  TFile* output = new TFile((output_str).c_str(), "RECREATE");
  TDirectory *mydict = output->mkdir("TreeMaker"); mydict->cd();
  TTree* selectedTree = new TTree("MVATree","MVATree");
  
  //MVA variables
  Float_t WpT, Hmass, HpT, bbdRAve, bbdMMin, HHt, WHdR;
  Int_t nBJets;
  selectedTree->Branch("WpT",&WpT,"WpT/F");
  selectedTree->Branch("Hmass",&Hmass,"Hmass/F");
  selectedTree->Branch("HpT",&HpT,"HpT/F");
  selectedTree->Branch("bbdRAve",&bbdRAve,"bbdRAve/F");
  selectedTree->Branch("bbdMMin",&bbdMMin,"bbdMMin/F");
  selectedTree->Branch("HHt",&HHt,"HHt/F");
  selectedTree->Branch("WHdR",&WHdR,"WHdR/F");

  selectedTree->Branch("nBJets",&nBJets,"nBJets/I");

  //Cut flow bit
  /*
  Bool_t passLeptVeto, passTagger,passBJets,passQCDHighMETFilter,passdPhis,passNoiseEventFilter;
  selectedTree->Branch("passLeptVeto"        ,&passLeptVeto        ,"passLeptVeto/O");
  selectedTree->Branch("passTagger"          ,&passTagger          ,"passTagger/O");
  selectedTree->Branch("passBJets"           ,&passBJets           ,"passBJets/O");
  selectedTree->Branch("passQCDHighMETFilter",&passQCDHighMETFilter,"passQCDHighMETFilter/O");
  selectedTree->Branch("passdPhis"           ,&passdPhis           ,"passdPhis/O");
  selectedTree->Branch("passNoiseEventFilter",&passNoiseEventFilter,"passNoiseEventFilter/O");
  */
  NTupleReader *tr=0;
  tr = new NTupleReader(originalTree);
  //tr = new NTupleReader(originalTree, AnaConsts::activatedBranchNames);

  const std::string spec = "Test";
  BaselineVessel *myBaselineVessel = 0;
  myBaselineVessel = new BaselineVessel(*tr, spec);
  tr->registerFunction(*myBaselineVessel);
  
  while (tr->getNextEvent())
  {
    bool passSelPreMVA = tr->getVar<bool>("passSelPreMVA");
    if (passSelPreMVA)
    {
      //MVA variables
      WpT     = tr->getVar<float>("WpT_calcMVA");
      Hmass   = tr->getVar<float>("Hmass_calcMVA");
      HpT     = tr->getVar<float>("HpT_calcMVA");
      bbdRAve = tr->getVar<float>("bbdRAve_calcMVA");
      bbdMMin = tr->getVar<float>("bbdMMin_calcMVA");
      HHt     = tr->getVar<float>("HHt_calcMVA");
      WHdR    = tr->getVar<float>("WHdR_calcMVA");
      nBJets = tr->getVar<int>("nBJets_calcMVA");
      std::cout << "NEvent " << tr->getEvtNum() << std::endl;
      selectedTree->Fill();
    }
    else continue;
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
