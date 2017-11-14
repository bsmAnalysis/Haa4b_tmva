#include "MVAAna.h"


int main(int argc, char* argv[])
{
  if (argc < 1)
  {
    std::cerr <<"Please give at least 1 arguments " << "RunMode " << std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./QCD RunMode" << std::endl;
    return -1;
  }

  std::string RunMode = argv[1];
 
  if ( RunMode == "Train" )
  { 
    TMVATrainer myTMVATrainer;
  
    myTMVATrainer.InitTMVAFactory("MVAOutTest.root", "Haa4bSBClassification");
    myTMVATrainer.SetupMVAFactory("TribMVA");
    //myTMVATrainer.SetupMVAFactory("QuabMVA");
    myTMVATrainer.TnTstMVAFactory();
    myTMVATrainer.CloseMVAFactory();
  }
  else if ( RunMode == "CV" )
  {
    std::vector<std::string> TestBDTparStringVec;
    TestBDTparStringVec.push_back("!H:!V:NTrees=350:MinNodeSize=5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NTrees=350:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NTrees=350:MinNodeSize=5%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NTrees=350:MinNodeSize=5%:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NTrees=350:MinNodeSize=5%:MaxDepth=6:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");

    TMVATrainer myTMVATrainer;
    myTMVATrainer.InitTMVAFactory("MVAOutCVTest.root", "Haa4bSBClassification");
    myTMVATrainer.SetupMVAFactory("TribMVA");
    myTMVATrainer.CrossValidation( TestBDTparStringVec );
    //myTMVATrainer.CloseMVAFactory();
  }
  else if ( RunMode == "Application" )
  {  
    TMVAReader myTMVAReader;

    myTMVAReader.InitTMVAReader();
    myTMVAReader.SetupMVAReader( "Haa4bSBClassification", "weights/Haa4bSBClassification_BDT.weights.xml" );
 
    //Test loop macro
    TFile *f = new TFile("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_Data13TeV_SingleElectron2016B_ver2.root");
    TTree *t = (TTree*)f->Get("TribMVA");
    long long int nTot = t->GetEntries();
    float WpT, Hmass, HpT, bbdRAve, bbdMMin, HHt, WHdR;
    t->SetBranchAddress( "WpT", &WpT );
    t->SetBranchAddress( "Hmass", &Hmass );
    t->SetBranchAddress( "HpT", &HpT );
    t->SetBranchAddress( "bbdRAve", &bbdRAve );
    t->SetBranchAddress( "bbdMMin", &bbdMMin );
    t->SetBranchAddress( "HHt", &HHt );
    t->SetBranchAddress( "WHdR", &WHdR );
  
    for ( int ievt = 0; ievt < nTot; ievt++ )
    { 
      t->GetEntry( ievt ); 
      float mvaout = myTMVAReader.GenReMVAReader
                     (
                      WpT,
                      Hmass, HpT, bbdRAve, bbdMMin, HHt,
                      WHdR,
                      "Haa4bSBClassification"
                     );
      if ( ievt <= 20 )
      {
        std::cout << "MVA output : " << mvaout << std::endl;
        std::cout << "MVA vars : " << WpT << "," << Hmass << std::endl;
        std::cout << "MVA vars : " << myTMVAReader.WpT << "," << myTMVAReader.Hmass << std::endl;
      }
    }
    f->Close();
    myTMVAReader.CloseMVAReader();
    return 0;
  }
  else 
  {
    std::cout << "Invalid run mode" << std::endl;
    return -1;
  }
  return -1;
}
