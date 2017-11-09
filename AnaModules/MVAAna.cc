#include "MVAAna.h"


int main()
{
  /*
  TMVATrainer myTMVATrainer;
  
  myTMVATrainer.InitTMVAFactory("MVAOutTest.root", "Haa4bSBClassification");
  myTMVATrainer.SetupMVAFactory("TribMVA");
  //myTMVATrainer.SetupMVAFactory("QuabMVA");
  myTMVATrainer.TnTstMVAFactory();
  myTMVATrainer.CloseMVAFactory();
  */

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
