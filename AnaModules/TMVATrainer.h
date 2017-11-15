#ifndef tmvaTrainer_h
#define tmvaTrainer_h

#include <iostream>
#include <vector>
#include <string>
#include <utility>      // std::pair, std::make_pair

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"
#include "TMVA/HyperParameterOptimisation.h"
#include "TMVA/CrossValidation.h"

#include "TString.h"
#include "TFile.h"
#include "TTree.h"

class TMVATrainer
{
 public:
  TMVA::DataLoader *mydataloader;
  TFile *myMVAout;
  TMVA::Factory *myfactory;

  std::vector<TFile*> SGFileVec, BGFileVec;

  void InitTMVAFactory( std::string OutFileName, std::string JobName );
  void SetupMVAFactory( std::string catName );
  void CrossValidation( std::vector<std::string> parStringVec );
  void TnTstMVAFactory();
  void CloseMVAFactory();
  //void CheckTTree();
 private:
  std::vector<std::pair<std::string, float>> SGfileURLWeightVec = 
  {
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass20.root" ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass50.root" ), 1.0),
  };
  std::vector<std::pair<std::string, float>> BGfileURLWeightVec =
  {
  //Single top
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_SingleT_atW_2016.root"             ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_SingleT_at_2016.root"              ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_SingleT_s_2016.root"               ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_SingleT_tW_2016.root"              ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_SingleT_t_2016.root"               ), 1.0),
  //TTJets
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TTJets_2016.root"                  ), 1.0),
  //WJets
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WJets.root"                        ), 1.0),
  //DY
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_DYJetsToLL_10to50_2016.root"       ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_DYJetsToLL_50toInf_2016.root"      ), 1.0),
  //TG, TTG, TTW, TTZ
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TGJets_2016.root"                  ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TGJets_ext1_2016.root"             ), 1.0),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TTGJets_2016.root"                 ), 1.0), // co4b
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TTWJetslnu_2016.root"              ), 1.0), //no busket, co3b, co4b
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TTZJets2l2nu_2016.root"            ), 1.0), //no busket, co3b, co4b
  //Di-boson
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WW2l2nu_2016.root"                 ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WWlnu2q_2016.root"                 ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WWlnu2q_ext1_2016.root"            ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WZ_2016.root"                      ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WZ_ext1_2016.root"                 ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_ZZ_2016.root"                      ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_ZZ_ext1_2016.root"                 ), 1.0),
  //Tri-boson
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_ZZZ_2016.root"                     ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WZZ_2016.root"                     ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WWZ_2016.root"                     ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WWW_4F_2016.root"                  ), 1.0),
  //QCD
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt20To30_EMEnr_2016.root"      ), 1.0), //0 events, co3b, co4b
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt30To50_EMEnr_2016.root"      ), 1.0), //0 events, co3b, co4b
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt30To50_EMEnr_ext1_2016.root" ), 1.0), //0 events, co3b, co4b
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt50To80_EMEnr_2016.root"      ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt80To120_EMEnr_2016.root"     ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt120To170_EMEnr_2016.root"    ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt170To300_EMEnr_2016.root"    ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt300ToInf_EMEnr_2016.root"    ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt20ToInf_MuEnr_2016.root"     ), 1.0)
  };
};
#endif
