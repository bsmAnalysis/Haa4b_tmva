#include "MVAAna.h"


int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr <<" Please give at least 2 arguments " << "RunMode TrainMode" << std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./QCD RunMode TrainMode" << std::endl;
    return -1;
  }

  std::string RunMode = argv[1];
  std::string TrainMode = argv[2]; //TribMVA or QuabMVA
  
  if ( RunMode == "BasicCheck" )
  {

  }
  else if ( RunMode == "Train" )
  { 
    TMVATrainer myTMVATrainer;
  
    myTMVATrainer.InitTMVAFactory("MVATrainTestOut" + TrainMode + ".root", "Haa4bSBClassification" + TrainMode);
    myTMVATrainer.SetupMVAFactory(TrainMode);
    myTMVATrainer.TnTstMVAFactory();
    myTMVATrainer.CloseMVAFactory();
  }
  else if ( RunMode == "CV" )
  {
    std::vector<std::string> TestBDTparStringVec;
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=6:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=7:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=8:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=9:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=15:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=1%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=2.5%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5.0%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=7.5%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=10%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=15%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=20%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=25%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");

    TMVATrainer myTMVATrainer;
    myTMVATrainer.InitTMVAFactory("MVACVTestOut" + TrainMode + ".root", "Haa4bSBClassification" + TrainMode);
    myTMVATrainer.SetupMVAFactory(TrainMode);
    myTMVATrainer.CrossValidation( TestBDTparStringVec );
    //myTMVATrainer.CloseMVAFactory();
  }
  else if ( RunMode == "Application" )
  {  
    MVACutFlowHist myMVACutFlowHist;
    std::string dir_out = "OutDir/";
    myMVACutFlowHist.BookHistgram( (dir_out + "MVACutFlow.root").c_str() );
    
    TMVAReader myTMVAReader;
    myTMVAReader.InitTMVAReader();
    myTMVAReader.SetupMVAReader( "Haa4bSBClassification" + TrainMode, "dataset/weights/Haa4bSBClassification" + TrainMode + "_BDT.weights.xml" );
 
    //Test loop macro
    //TFile *f = new TFile("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_Data13TeV_SingleElectron2016B_ver2.root");
    TFile *f = new TFile("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass30.root");
    TTree *t = (TTree*)f->Get(TrainMode.c_str());
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
                      "Haa4bSBClassification" + TrainMode
                     );
      if ( ievt < 200 )
      {
        std::cout << "MVA output : " << mvaout << ", [" << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).first << ","  << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).second << "]" << std::endl;
        //std::cout << "MVA vars : " << WpT << "," << Hmass << std::endl;
        //std::cout << "MVA vars : " << myTMVAReader.WpT << "," << myTMVAReader.Hmass << std::endl;
      }
    }
    f->Close();
    myTMVAReader.CloseMVAReader();

    (myMVACutFlowHist.oFile)->Write();
    (myMVACutFlowHist.oFile)->Close();
    return 0;
  }
  else 
  {
    std::cout << "Invalid run mode" << std::endl;
    return -1;
  }
  return -1;
}
