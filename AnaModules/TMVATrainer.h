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
  void GenSGReWeight( std::string catName );
 private:
  float GenSGReWeightArr[8] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
  std::vector<std::pair<std::string, float>> SGfileURLWeightVec = 
  {
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass12.root" ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass15.root" ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass20.root" ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass25.root" ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass30.root" ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass40.root" ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass50.root" ), 1.0),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass60.root" ), 1.0),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass12.root" ), 0.12371),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass15.root" ), 0.12293),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass20.root" ), 0.12827),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass25.root" ), 0.123152),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass30.root" ), 0.12298),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass40.root" ), 0.123598),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass50.root" ), 0.12309),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_Wh_amass60.root" ), 0.123375),
  };
  std::vector<std::pair<std::string, float>> BGfileURLWeightVec =
  {
  //Single top
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_SingleT_s_2016.root"               ), 0.193558),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_SingleT_atW_2016.root"             ), 0.184169),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_SingleT_tW_2016.root"              ), 0.183646),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_SingleT_at_2016.root"              ), 0.0765989),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_SingleT_t_2016.root"               ), 0.0725545),
  //TTJets
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TTJets_2016.root"                  ), 1.9437),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TTJets_slt_2016.root"              ), 0.105736*0.1929),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TTJets_slt_ext1_2016.root"         ), 0.105736*0.8071),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/HaddExt/mva_MC13TeV_TTJets_slt_all_2016.root"    ), 0.105736),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TTJets_slat_2016.root"             ), 0.108833*0.1984),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TTJets_slat_ext1_2016.root"        ), 0.109933*0.8016),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/HaddExt/mva_MC13TeV_TTJets_slat_all_2016.root"    ), 0.109933),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TTJets_dl_2016.root"               ), 0.104012*0.2002),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TTJets_dl_ext1_2016.root"          ), 0.104012*0.7998),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/HaddExt/mva_MC13TeV_TTJets_dl_all_2016.root"    ), 0.104012),
  //WJets
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WJets_2016.root"                   ), 30.7868*0.3425),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WJets_ext2_2016.root"              ), 30.7868*0.6575),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/HaddExt/mva_MC13TeV_WJets_all_2016.root"                   ), 25.4437),
  //DY
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_DYJetsToLL_10to50_2016.root"       ), 12.8647*0.434),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_DYJetsToLL_10to50_ext1_2016.root"  ), 12.8647*0.566),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/HaddExt/mva_MC13TeV_DYJetsToLL_10to50_all_2016.root"                   ), 12.8647),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_DYJetsToLL_50toInf_2016.root"      ), 2.52855),
  //TG, TTG, TTW, TTZ
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TGJets_2016.root"                  ), 0.288736*0.25),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TGJets_ext1_2016.root"             ), 0.288736*0.75), //ext1
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/HaddExt/mva_MC13TeV_TGJets_all_2016.root"                   ), 0.288736),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TTGJets_2016.root"                 ), 0.0840393), //
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TTWJetslnu_2016.root"              ), 0.00456969), //
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_TTZJets2l2nu_2016.root"            ), 0.00977476), //
  //Di-boson
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WW2l2nu_2016.root"                 ), 0.218503),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WWlnu2q_2016.root"                 ), 0.199298*0.5),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WWlnu2q_ext1_2016.root"            ), 0.199298*0.5), //ext1
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/HaddExt/mva_MC13TeV_WWlnu2q_all_2016.root"                   ), 0.199298),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WZ_2016.root"                      ), 0.436678*0.25),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WZ_ext1_2016.root"                 ), 0.436678*0.75), //ext1
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/HaddExt/mva_MC13TeV_WZ_all_2016.root"                   ), 0.436678),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_ZZ_2016.root"                      ), 0.298089*0.5),
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_ZZ_ext1_2016.root"                 ), 0.298089*0.5), //ext1
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/HaddExt/mva_MC13TeV_ZZ_all_2016.root"                   ), 0.298089),
  //Tri-boson
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_ZZZ_2016.root"                     ), 0.0355368),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WZZ_2016.root"                     ), 0.0267381),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WWZ_2016.root"                     ), 0.00922509),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_WWW_4F_2016.root"                  ), 0.00235191),
  //QCD
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt20To30_EMEnr_2016.root"      ), 1.0), //0 events, co3b, co4b
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt30To50_EMEnr_2016.root"      ), 1.0), //0 events, co3b, co4b
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt30To50_EMEnr_ext1_2016.root" ), 1.0), //0 events, co3b, co4b
  //std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt50To80_EMEnr_2016.root"      ), 4416.95),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt80To120_EMEnr_2016.root"     ), 350.246),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt120To170_EMEnr_2016.root"    ), 63.0513),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt170To300_EMEnr_2016.root"    ), 58.4617),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt300ToInf_EMEnr_2016.root"    ), 6.56669),
  std::make_pair( std::string("root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/mva_MC13TeV_QCD_Pt20ToInf_MuEnr_2016.root"     ), 491.35)
  };
};
#endif
