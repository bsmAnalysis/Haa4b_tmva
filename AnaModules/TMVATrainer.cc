#include "TMVATrainer.h"

void TMVATrainer::InitTMVAFactory( TString OutFileName, TString JobName )
{
  myMVAout = TFile::Open( OutFileName, "RECREATE" );
  myfactory = new TMVA::Factory( JobName, myMVAout, "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

  return ;
}

void TMVATrainer::LoadTrees( TString catName )
{
  int nBG = BGfileURLWeightVec.size();
  for (int i = 0; i < nBG; i++)
  {
    TFile *thisfile = TFile::Open( BGfileURLWeightVec.at(i).first.c_str() );
    TTree *thisbkgTree = (TTree *)thisfile->Get(catName);
    thisbkgTree->SetDirectory(0);
    myfactory->AddBackgroundTree( thisbkgTree, BGfileURLWeightVec.at(i).second );
    thisfile->Close();
  }

  return ;
}
