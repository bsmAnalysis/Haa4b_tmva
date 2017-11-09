#include "TMVATrainer.h"

void TMVATrainer::InitTMVAFactory( TString OutFileName, TString JobName )
{
  mydataloader = new TMVA::DataLoader("dataset");
  myMVAout = TFile::Open( OutFileName, "RECREATE" );
  myfactory = new TMVA::Factory( JobName, myMVAout, "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
  //myfactory = new TMVA::Factory( JobName, myMVAout, "!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification" );
  return ;
}

void TMVATrainer::SetupMVAFactory( TString catName )
{
  //load sg file
  int nSG = SGfileURLWeightVec.size();
  for (int i = 0; i < nSG; i++)
  {
    TFile *thissgfile = TFile::Open( SGfileURLWeightVec.at(i).first.c_str() );
    SGFileVec.push_back(thissgfile);
  }
  for (int i = 0; i < nSG; i++)
  {
    //TTree *thissgtree = (TTree *)(SGFileVec.at(i))->Get(catName);
    //if ( thissgtree->GetEntries() != 0 )
    //{
      mydataloader->AddSignalTree( (TTree *)(SGFileVec.at(i))->Get(catName), SGfileURLWeightVec.at(i).second );
      //myfactory->AddSignalTree( (TTree *)(SGFileVec.at(i))->Get(catName), SGfileURLWeightVec.at(i).second );
    //}
    //else
    //{
      //std::cout << "The file " <<  SGfileURLWeightVec.at(i).first.c_str() << " is excluded due to 0 events" << std::endl;
    //}
  }

  //load bg file
  int nBG = BGfileURLWeightVec.size();
  for (int i = 0; i < nBG; i++)
  {
    TFile *thisbgfile = TFile::Open( BGfileURLWeightVec.at(i).first.c_str() );
    BGFileVec.push_back(thisbgfile);
  }
  for (int i = 0; i < nBG; i++)
  {
    //TTree *thisbgtree = (TTree *)(BGFileVec.at(i))->Get(catName);
    //if ( thisbgtree->GetEntries() != 0 )
    //{ 
      mydataloader->AddBackgroundTree( (TTree *)(BGFileVec.at(i))->Get(catName), BGfileURLWeightVec.at(i).second );
      //myfactory->AddBackgroundTree( (TTree *)(BGFileVec.at(i))->Get(catName), BGfileURLWeightVec.at(i).second );
    //}
    //else
    //{
      //std::cout << "The file " <<  BGfileURLWeightVec.at(i).first.c_str() << " is excluded due to 0 events" << std::endl;
    //}
  }

  mydataloader->AddVariable( "WpT"    , 'F' );
  mydataloader->AddVariable( "Hmass"  , 'F' );
  mydataloader->AddVariable( "HpT"    , 'F' );
  mydataloader->AddVariable( "bbdRAve", 'F' );
  //mydataloader->AddVariable( "bbdMMin", 'F' );
  mydataloader->AddVariable( "HHt"   , 'F' );
  mydataloader->AddVariable( "WHdR"   , 'F' );
  /*
  myfactory->AddVariable( "WpT"    , 'F' );
  myfactory->AddVariable( "Hmass"  , 'F' );
  myfactory->AddVariable( "HpT"    , 'F' );
  myfactory->AddVariable( "bbdRAve", 'F' );
  //myfactory->AddVariable( "bbdMMin", 'F' );
  myfactory->AddVariable( "HHt"   , 'F' );
  myfactory->AddVariable( "WHdR"   , 'F' );
  */
  return ;
}

void TMVATrainer::TnTstMVAFactory( )
{
  // Apply additional cuts on the signal and background samples (can be different)
  //TCut mycuts = "WpT>0.5 && Hmass>0.5 && HpT>0.5 && HHt>0.5 && WHdR>0.001"; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
  //TCut mycutb = "WpT>0.5 && Hmass>0.5 && HpT>0.5 && HHt>0.5 && WHdR>0.001"; // for example: TCut mycutb = "abs(var1)<0.5";
  TCut mycuts = "";
  TCut mycutb = "";
  //myfactory->PrepareTrainingAndTestTree( mycuts, mycutb,
  mydataloader->PrepareTrainingAndTestTree( mycuts, mycutb,
                                        "SplitMode=Random:NormMode=NumEvents:nTrain_Signal=0:nTest_Signal=0:nTrain_Background=0:nTest_Background=0:V" );
  // Boosted Decision Trees
  // Gradient Boost
  //myfactory->BookMethod( TMVA::Types::kBDT, "BDTG",
  //                       "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2" );
  // Adaptive Boost
  //myfactory->BookMethod( TMVA::Types::kBDT, "BDT",
  myfactory->BookMethod( mydataloader, TMVA::Types::kBDT, "BDT",
                         "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
  // Bagging
  //myfactory->BookMethod( TMVA::Types::kBDT, "BDTB",
  //                       "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20" );

  // Decorrelation + Adaptive Boost
  //myfactory->BookMethod( TMVA::Types::kBDT, "BDTD",
  //                       "!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate" );

  // Allow Using Fisher discriminant in node splitting for (strong) linearly correlated variables
  //myfactory->BookMethod( TMVA::Types::kBDT, "BDTMitFisher",
  //                       "!H:!V:NTrees=50:MinNodeSize=2.5%:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20" );

  // Train MVAs using the set of training events
  myfactory->TrainAllMethods();

  // ---- Evaluate all MVAs using the set of test events
  myfactory->TestAllMethods();

  // ----- Evaluate and compare performance of all configured MVAs
  myfactory->EvaluateAllMethods();

  // --------------------------------------------------------------

  // Save the output
  myMVAout->Close();

  std::cout << "==> Wrote root file: " << myMVAout->GetName() << std::endl;
  std::cout << "==> TMVAClassification is done!" << std::endl;

  return ;
}

void TMVATrainer::CloseMVAFactory()
{
  delete myfactory;
  delete mydataloader;  
  int nSG = SGFileVec.size();
  for (int i = 0; i < nSG; i++)
  { 
    (SGFileVec.at(i))->Close();
  }

  int nBG = BGFileVec.size();
  for (int i = 0; i < nBG; i++)
  { 
    (BGFileVec.at(i))->Close();
  }

  return ;
}
