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
  std::string subdir_2016wh = "WH_2016_MVABGMCFileList/";
  std::string subdir_2016zh = "ZH_2016_MVABGMCFileList/";
  std::string subdir_2017wh = "WH_2017_MVABGMCFileList/";
  std::string subdir_2017zh = "ZH_2017_MVABGMCFileList/";
  std::string subdir_2018wh = "WH_2018_MVABGMCFileList/";
  std::string subdir_2018zh = "ZH_2018_MVABGMCFileList/";
  std::string dir = "/afs/cern.ch/work/y/yuanc/Analysis/H2a4b/bdt/CMSSW_9_2_14_patch1/src/UserCode/Haa4bTools/Data/";

  //std::string dir = "/eos/cms/store/user/georgia/bsm_analysis/haa4b/MVARes/"; 
  float GenSGReWeightArr[8] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0}; //, 1.0, 1.0};
  std::vector<std::pair<std::string, float> > SGfileURLWeightVec_2016Wh = 
  {
    std::make_pair( dir + "WH_2016_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass12_2016.root"), 1.0),
    std::make_pair( dir + "WH_2016_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass15_2016.root"), 1.0),
    std::make_pair( dir + "WH_2016_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass20_2016.root"), 1.0),
    std::make_pair( dir + "WH_2016_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass25_2016.root"), 1.0),
    std::make_pair( dir + "WH_2016_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass30_2016.root"), 1.0),
    std::make_pair( dir + "WH_2016_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass40_2016.root"), 1.0),
    std::make_pair( dir + "WH_2016_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass50_2016.root"), 1.0),
    std::make_pair( dir + "WH_2016_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass60_2016.root"), 1.0),
  };
  std::vector<std::pair<std::string, float> > SGfileURLWeightVec_2016Zh = 
  {
    std::make_pair( dir + "ZH_2016_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass12_2016.root"), 1.0),
    std::make_pair( dir + "ZH_2016_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass15_2016.root"), 1.0),
    std::make_pair( dir + "ZH_2016_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass20_2016.root"), 1.0),
    std::make_pair( dir + "ZH_2016_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass25_2016.root"), 1.0),
    std::make_pair( dir + "ZH_2016_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass30_2016.root"), 1.0),
    std::make_pair( dir + "ZH_2016_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass40_2016.root"), 1.0),
    std::make_pair( dir + "ZH_2016_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass50_2016.root"), 1.0),
    std::make_pair( dir + "ZH_2016_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass60_2016.root"), 1.0),
  };
  std::vector<std::pair<std::string, float> > SGfileURLWeightVec_2017Zh = 
  {
    std::make_pair( dir + "ZH_2017_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass12_2017.root"), 1.0),
    std::make_pair( dir + "ZH_2017_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass15_2017.root"), 1.0),
    std::make_pair( dir + "ZH_2017_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass20_2017.root"), 1.0),
    std::make_pair( dir + "ZH_2017_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass25_2017.root"), 1.0),
    std::make_pair( dir + "ZH_2017_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass30_2017.root"), 1.0),
    std::make_pair( dir + "ZH_2017_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass40_2017.root"), 1.0),
    std::make_pair( dir + "ZH_2017_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass50_2017.root"), 1.0),
    std::make_pair( dir + "ZH_2017_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass60_2017.root"), 1.0),
  };
  std::vector<std::pair<std::string, float> > SGfileURLWeightVec_2017Wh = 
  {
    std::make_pair( dir + "WH_2017_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass12_2017.root"), 1.0),
    std::make_pair( dir + "WH_2017_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass15_2017.root"), 1.0),
    std::make_pair( dir + "WH_2017_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass20_2017.root"), 1.0),
    std::make_pair( dir + "WH_2017_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass25_2017.root"), 1.0),
    std::make_pair( dir + "WH_2017_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass30_2017.root"), 1.0),
    std::make_pair( dir + "WH_2017_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass40_2017.root"), 1.0),
    std::make_pair( dir + "WH_2017_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass50_2017.root"), 1.0),
    std::make_pair( dir + "WH_2017_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass60_2017.root"), 1.0),
  };
  std::vector<std::pair<std::string, float> > SGfileURLWeightVec_2018Zh = 
  {
    std::make_pair( dir + "ZH_2018_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass12_2018.root"), 1.0),
    std::make_pair( dir + "ZH_2018_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass15_2018.root"), 1.0),
    std::make_pair( dir + "ZH_2018_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass20_2018.root"), 1.0),
    std::make_pair( dir + "ZH_2018_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass25_2018.root"), 1.0),
    std::make_pair( dir + "ZH_2018_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass30_2018.root"), 1.0),
    std::make_pair( dir + "ZH_2018_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass40_2018.root"), 1.0),
    std::make_pair( dir + "ZH_2018_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass50_2018.root"), 1.0),
    std::make_pair( dir + "ZH_2018_MVASGMCFileList/" + std::string("mva_MC13TeV_Zh_amass60_2018.root"), 1.0),
  };
  std::vector<std::pair<std::string, float> > SGfileURLWeightVec_2018Wh = 
  {
    std::make_pair( dir + "WH_2018_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass12_2018.root"), 1.0),
    std::make_pair( dir + "WH_2018_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass15_2018.root"), 1.0),
    std::make_pair( dir + "WH_2018_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass20_2018.root"), 1.0),
    std::make_pair( dir + "WH_2018_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass25_2018.root"), 1.0),
    std::make_pair( dir + "WH_2018_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass30_2018.root"), 1.0),
    std::make_pair( dir + "WH_2018_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass40_2018.root"), 1.0),
    std::make_pair( dir + "WH_2018_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass50_2018.root"), 1.0),
    std::make_pair( dir + "WH_2018_MVASGMCFileList/" + std::string("mva_MC13TeV_Wh_amass60_2018.root"), 1.0),
  };
  std::vector<std::pair<std::string, float> > BGfileURLWeightVec_2016Wh =
  {
    //Single top
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_SingleT_s_2016.root"               ), 0.193558),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_SingleT_atW_2016.root"             ), 0.184169),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_SingleT_tW_2016.root"              ), 0.183646),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_SingleT_at_2016.root"              ), 0.0748094),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_SingleT_t_2016.root"               ), 0.0725545),
    //TTJets
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_TTJets_2016.root"          ), 0.387029),
    //WJets
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_2016.root"), 25.3643), //25.7282),
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_W1Jets_2016.root"), 9.08119), //wh4b_0
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_W2Jets_2016.root"), 2.24933), //2.11101),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_W3Jets_2016.root"), 0.700273), //0.687131),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_W4Jets_2016.root"), 0.758444), //0.750822),
    //DY
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DYJetsToLL_10to50_2016.root"   ), 13.9757), // 18.9134), //comment out because 0 events
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DY1JetsToLL_10to50_2016.root"   ),  0.78975), //wh4b_0
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DY2JetsToLL_10to50_2016.root"   ), 0.880572), //wh4b_0
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DY3JetsToLL_10to50_2016.root"   ), 0.843379), //wh4b_0
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DY4JetsToLL_10to50_2016.root"   ), 0.7242), //0.763872),
  
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DYJetsToLL_50toInf_2016.root"  ), 0.910305), //1.41826),
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DY1JetsToLL_50toInf_2016.root"  ), 0.686605), //wh4b_0
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DY2JetsToLL_50toInf_2016.root"  ), 0.702326), //wh4b_0
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DY3JetsToLL_50toInf_2016.root"  ), 0.696408), //0.469104),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DY4JetsToLL_50toInf_2016.root"  ), 0.518216), //0.381347),
    //TG, TTG, TTW, TTZ
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_TGJets_2016.root"                  ), 0.288736),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_TTGJets_2016.root"                 ), 0.0840393), //
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_TTWJetslnu_2016.root"              ), 0.00456969), //
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_TTZJets2l2nu_2016.root"            ), 0.00456969), //
    //Di-boson
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WW2l2nu_2016.root"                 ), 0.218503), //wh4b_0
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WWlnu2q_2016.root"                   ), 0.0945106),//wh4b_0
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WZ_2016.root"                   ), 1.69041),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_ZZ_2016.root"                   ), 0.319683),
    //Tri-boson
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_ZZZ_2016.root"                     ), 0.0355368),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WZZ_2016.root"                     ), 0.0267381),
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WWZ_2016.root"                     ), 0.00922509),//wh4b_0
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WWW_4F_2016.root"                  ), 0.00235191),//wh4b_0
    //QCD
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt80To120_EMEnr_2016.root"     ), 161.573),
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt120To170_EMEnr_2016.root"    ), 29.038),
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt170To300_EMEnr_2016.root"    ), 58.4617),
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt300ToInf_EMEnr_2016.root"    ), 6.56669),
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt80to120_MuEnrPt5_2016.root"  ), 161.256),
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt120to170_MuEnrPt5_2016.root" ), 112.338),
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt170to300_MuEnrPt5_2016.root" ), 17.8908),
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt300to470_MuEnrPt5_2016.root" ), 0.593154),
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt470to600_MuEnrPt5_2016.root" ), 0.146383),
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt600to800_MuEnrPt5_2016.root" ), 0.0901768),
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt800to1000_MuEnrPt5_2016.root"), 0.00854126),
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt1000toInf_MuEnrPt5_2016.root"), 0.00427588),
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt_80to170_bcToE_2016.root"    ), 7713.81),
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt_170to250_bcToE_2016.root"   ), 390.266),
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt_250toInf_bcToE_2016.root"   ), 77.4105)
  };
  std::vector<std::pair<std::string, float> > BGfileURLWeightVec_2016Zh =
  {
    //Single top
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_SingleT_s_2016.root"               ), 0.193558),//zh4b_0
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_SingleT_atW_2016.root"             ), 0.184169),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_SingleT_tW_2016.root"              ), 0.183646),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_SingleT_at_2016.root"              ), 0.0748094),//zh4b_0
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_SingleT_t_2016.root"               ), 0.0725545),//zh4b_0
    //TTJets
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_TTJets_2016.root"          ), 0.387029),
    //WJets
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_2016.root"), 25.3643), //25.7282),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_W1Jets_2016.root"), 9.08119), //6.85513),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_W2Jets_2016.root"), 2.24933), //2.11101),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_W3Jets_2016.root"), 0.700273), //0.687131),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_W4Jets_2016.root"), 0.758444), //0.750822), //zh4b_0
    //DY
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_DYJetsToLL_10to50_2016.root"   ), 13.9757), // 18.9134), //comment out because 0 events
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_DY1JetsToLL_10to50_2016.root"   ),  0.78975), //0.829979),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_DY2JetsToLL_10to50_2016.root"   ), 0.880572), //0.92078),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_DY3JetsToLL_10to50_2016.root"   ), 0.843379), //0.883706),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_DY4JetsToLL_10to50_2016.root"   ), 0.7242), //0.763872),
  
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_DYJetsToLL_50toInf_2016.root"  ), 0.910305), //1.41826),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_DY1JetsToLL_50toInf_2016.root"  ), 0.686605), //0.468798),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_DY2JetsToLL_50toInf_2016.root"  ), 0.702326), //0.471764),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_DY3JetsToLL_50toInf_2016.root"  ), 0.696408), //0.469104),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_DY4JetsToLL_50toInf_2016.root"  ), 0.518216), //0.381347),
    //TG, TTG, TTW, TTZ
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_TGJets_2016.root"                  ), 0.288736),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_TTGJets_2016.root"                 ), 0.0840393), //
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_TTWJetslnu_2016.root"              ), 0.00456969), //
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_TTZJets2l2nu_2016.root"            ), 0.00456969), //
    //Di-boson
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WW2l2nu_2016.root"                 ), 0.218503),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WWlnu2q_2016.root"                   ), 0.0945106),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WZ_2016.root"                   ), 1.69041),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_ZZ_2016.root"                   ), 0.319683),
    //Tri-boson
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_ZZZ_2016.root"                     ), 0.0355368),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WZZ_2016.root"                     ), 0.0267381),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WWZ_2016.root"                     ), 0.00922509), //zh4b_0
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WWW_4F_2016.root"                  ), 0.00235191),
    //QCD
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_QCD_Pt80To120_EMEnr_2016.root"     ), 161.573),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_QCD_Pt120To170_EMEnr_2016.root"    ), 29.038),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_QCD_Pt170To300_EMEnr_2016.root"    ), 58.4617),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_QCD_Pt300ToInf_EMEnr_2016.root"    ), 6.56669),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_QCD_Pt80to120_MuEnrPt5_2016.root"  ), 161.256),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_QCD_Pt120to170_MuEnrPt5_2016.root" ), 112.338),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_QCD_Pt170to300_MuEnrPt5_2016.root" ), 17.8908),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_QCD_Pt300to470_MuEnrPt5_2016.root" ), 0.593154),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_QCD_Pt470to600_MuEnrPt5_2016.root" ), 0.146383),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_QCD_Pt600to800_MuEnrPt5_2016.root" ), 0.0901768),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_QCD_Pt800to1000_MuEnrPt5_2016.root"), 0.00854126),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_QCD_Pt1000toInf_MuEnrPt5_2016.root"), 0.00427588),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_QCD_Pt_80to170_bcToE_2016.root"    ), 7713.81),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_QCD_Pt_170to250_bcToE_2016.root"   ), 390.266),
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_QCD_Pt_250toInf_bcToE_2016.root"   ), 77.4105)
  };
  std::vector<std::pair<std::string, float> > BGfileURLWeightVec_2017Wh =
  {
    //Single top
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_SingleT_s_2017.root"               ), 0.0225202),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_SingleT_tW_antitop_2017.root"      ), 0.192354),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_SingleT_tW_top_2017.root"          ), 0.187515),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_SingleT_t_antitop_2017.root"       ), 0.297227),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_SingleT_t_top_2017.root"           ), 0.306894),
    //TTJets
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_TTTo2L2Nu_powheg_2017.root"       ), 0.0534525),
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_TTToHadronic_powheg_2017.root"    ), 0.121478), //wh4b_0
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_TTToSemiLeptonic_powheg_2017.root"), 0.349759),
    //WJets
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WJets_2017.root" ), 32.8114),
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_W1Jets_2017.root"), 8.81635), //wh4b_0
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_W2Jets_2017.root"), 23.8615), //wh4b_0
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_W3Jets_2017.root"), 2.4073),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_W4Jets_2017.root"), 2.37865), 
    //DY
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_DYJetsToLL_10to50_2017.root"    ), 23.4839),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_DYJetsToLL_M50_2017.root"       ), 2.45486),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_DY1JetsToLL_M50_2017.root"      ), 0.655604),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_DY2JetsToLL_M50_2017.root"   ), 1.60537),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_DY3JetsToLL_M50_2017.root"   ), 0.68556),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_DY4JetsToLL_M50_2017.root"   ), 0.583365),
    //TG, TTG, TTW, TTZ
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_TGJets_2017.root"             ), 0.33112),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_TTGJets_2017.root"            ), 0.0130277),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_TTWJetslnu_2017.root"         ), 0.00312385),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_TTZJets2l2nu_2017.root"       ), 0.00280424),
    //Di-boson
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WW_2017.root"                 ), 0.634769), //wh4b_0
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WZ_2017.root"                 ), 0.498206), //wh4b_0
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WminusH_2017.root"            ), 0.000619965),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WplusH_2017.root"             ), 0.000939266),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_ZH_2017.root"                 ), 0.000939266),
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_ZZ_2017.root"                 ), 0.356288), 
    //Tri-boson
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WWW_4F_2017.root"             ), 0.0426231), //wh4b_0
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WWZ_2017.root"                ), 0.0311708), //wh4b_0
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WZZ_2017.root"                ), 0.0105212),
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_ZZZ_2017.root"                ), 0.00270895), //wh4b_0
    //QCD
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt80To120_EMEnr_2017.root"       ), 1596.42),
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt120To170_EMEnr_2017.root"      ), 307.083),
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt300ToInf_EMEnr_2017.root"      ), 19.5054),
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt80to120_MuEnrPt5_2017.root"    ), 189.406), //wh4b_0
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt120to170_MuEnrPt5_2017.root"   ), 50.3561), //wh4b_0
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt170to300_MuEnrPt5_2017.root"   ), 7.78446), //wh4b_0
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt300to470_MuEnrPt5_2017.root"   ), 1.86609), //wh4b_0
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt470to600_MuEnrPt5_2017.root"   ), 0.13537), //wh4b_0
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt_80to170_bcToE_2017.root"      ), 8360.62), //wh4b_0
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt_170to250_bcToE_2017.root"     ), 446.053), //wh4b_0
//    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt_250toInf_bcToE_2017.root"     ), 87.6293) //wh4b_0
  };
  std::vector<std::pair<std::string, float> > BGfileURLWeightVec_2017Zh =
  {
    //Single top
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_SingleT_s_2017.root"               ), 0.0225202),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_SingleT_tW_antitop_2017.root"      ), 0.192354),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_SingleT_tW_top_2017.root"          ), 0.187515),
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_SingleT_t_antitop_2017.root"       ), 0.297227), //zh4b_0
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_SingleT_t_top_2017.root"           ), 0.306894), //zh4b_0
    //TTJets
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_TTTo2L2Nu_powheg_2017.root"       ), 0.0534525),
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_TTToHadronic_powheg_2017.root"    ), 0.121478), //zh4b_0 
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_TTToSemiLeptonic_powheg_2017.root"), 0.349759),
    //WJets
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WJets_2017.root" ), 32.8114),
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_W1Jets_2017.root"), 8.81635),
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_W2Jets_2017.root"), 23.8615),
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_W3Jets_2017.root"), 2.4073),
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_W4Jets_2017.root"), 2.37865), 
    //DY
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_DYJetsToLL_10to50_2017.root"    ), 23.4839),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_DYJetsToLL_M50_2017.root"       ), 2.45486),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_DY1JetsToLL_M50_2017.root"      ), 0.655604),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_DY2JetsToLL_M50_2017.root"   ), 1.60537),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_DY3JetsToLL_M50_2017.root"   ), 0.68556),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_DY4JetsToLL_M50_2017.root"   ), 0.583365),
    //TG, TTG, TTW, TTZ
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_TGJets_2017.root"             ), 0.33112), //zh4b_0
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_TTGJets_2017.root"            ), 0.0130277),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_TTWJetslnu_2017.root"         ), 0.00312385),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_TTZJets2l2nu_2017.root"       ), 0.00280424),
    //Di-boson
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WW_2017.root"                 ), 0.634769),  //zh4b_0
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WZ_2017.root"                 ), 0.498206), //zh4b_0
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WminusH_2017.root"            ), 0.000619965), //zh4b_0
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WplusH_2017.root"             ), 0.000939266),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_ZH_2017.root"                 ), 0.000939266),
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_ZZ_2017.root"                 ), 0.356288), 
    //Tri-boson
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WWW_4F_2017.root"             ), 0.0426231), 
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WWZ_2017.root"                ), 0.0311708), //zh4b_0
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WZZ_2017.root"                ), 0.0105212),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_ZZZ_2017.root"                ), 0.00270895), 
    //QCD
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_QCD_Pt80To120_EMEnr_2017.root"       ), 1596.42),
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_QCD_Pt120To170_EMEnr_2017.root"      ), 307.083),
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_QCD_Pt300ToInf_EMEnr_2017.root"      ), 19.5054),
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_QCD_Pt80to120_MuEnrPt5_2017.root"    ), 189.406),
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_QCD_Pt120to170_MuEnrPt5_2017.root"   ), 50.3561),
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_QCD_Pt170to300_MuEnrPt5_2017.root"   ), 7.78446),
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_QCD_Pt300to470_MuEnrPt5_2017.root"   ), 1.86609),
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_QCD_Pt470to600_MuEnrPt5_2017.root"   ), 0.13537),
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_QCD_Pt_80to170_bcToE_2017.root"      ), 8360.62),
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_QCD_Pt_170to250_bcToE_2017.root"     ), 446.053),
//    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_QCD_Pt_250toInf_bcToE_2017.root"     ), 87.6293)
  };
  std::vector<std::pair<std::string, float> > BGfileURLWeightVec_2018Wh =
  {
    //Single top
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_SingleT_s_2018.root"               ), 0.0160828),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_SingleT_tW_antitop_2018.root"      ), 0.280273),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_SingleT_tW_top_2018.root"          ), 0.222607),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_SingleT_t_antitop_2018.root"       ), 0.0211742),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_SingleT_t_top_2018.root"           ), 0.0183277),
    //TTJets
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_TTTo2L2Nu_powheg_2018.root"       ), 0.0826834),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_TTToHadronic_powheg_2018.root"    ), 0.170122),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_TTToSemiLeptonic_powheg_2018.root"), 0.216677),
    //WJets
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WJets_2018.root" ), 51.6326), //wh4b_0
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_W1Jets_2018.root"), 13.4425), //wh4b_0
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_W2Jets_2018.root"), 9.69082), 
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_W3Jets_2018.root"), 4.6999),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_W4Jets_2018.root"), 3.76576), 
    //DY
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_DYJetsToLL_10to50_2018.root"    ), 34.1773),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_DYJetsToLL_M50_2018.root"       ), 3.44673),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_DY1JetsToLL_M50_2018.root"      ), 0.670591),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_DY2JetsToLL_M50_2018.root"   ), 1.14288), //wh4b_0
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_DY3JetsToLL_M50_2018.root"   ), 1.20299),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_DY4JetsToLL_M50_2018.root"   ), 1.28832),
    //TG, TTG, TTW, TTZ
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_TGJets_2018.root"             ), 0.473579),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_TTGJets_2018.root"            ), 0.119878),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_TTWJetslnu_2018.root"         ), 0.00454377),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_TTZJets2l2nu_2018.root"       ), 0.00240808),
    //Di-boson
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WW_2018.root"                 ), 0.903338),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WZ_2018.root"                 ), 0.724729),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WminusH_2018.root"            ), 0.00107367),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WplusH_2018.root"             ), 0.00172244),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_ZH_2018.root"                 ), 0.000438741),
//    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_ZZ_2018.root"                 ), 0.498784),
    //Tri-boson
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WWW_4F_2018.root"             ), 0.0593141), //wh4b_0
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WWZ_2018.root"                ), 0.0448509), //wh4b_0
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WZZ_2018.root"                ), 0.0151633),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_ZZZ_2018.root"                ), 0.00389754),
    //QCD
//    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt80To120_EMEnr_2018.root"       ), 2167.03),
//    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt120To170_EMEnr_2018.root"      ), 377.504),
//    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt170To300_EMEnr_2018.root"      ), 302.712),
//    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt300ToInf_EMEnr_2018.root"      ), 27.7973),
//    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt80to120_MuEnrPt5_2018.root"    ), 246.938),
//    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt120to170_MuEnrPt5_2018.root"   ), 2374.9),
//    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt170to300_MuEnrPt5_2018.root"   ), 14.3704),
//    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt300to470_MuEnrPt5_2018.root"   ), 96.7355),
//    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt470to600_MuEnrPt5_2018.root"   ), 9.58165),
//    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt600to800_MuEnrPt5_2018.root"   ), 0.0902097),
//    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt800to1000_ext3_MuEnrPt5_2018.root"), 0.0121615),
//    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt1000toInf_MuEnrPt5_2018.root"  ),0.00903547)
  };
  std::vector<std::pair<std::string, float> > BGfileURLWeightVec_2018Zh =
  {
    //Single top
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_SingleT_s_2018.root"               ), 0.0160828),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_SingleT_tW_antitop_2018.root"      ), 0.280273),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_SingleT_tW_top_2018.root"          ), 0.222607),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_SingleT_t_antitop_2018.root"       ), 0.0211742),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_SingleT_t_top_2018.root"           ), 0.0183277),
    //TTJets
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_TTTo2L2Nu_powheg_2018.root"       ), 0.0826834),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_TTToHadronic_powheg_2018.root"    ), 0.170122),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_TTToSemiLeptonic_powheg_2018.root"), 0.216677),
    //WJets
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WJets_2018.root" ), 51.6326),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_W1Jets_2018.root"), 13.4425),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_W2Jets_2018.root"), 9.69082), 
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_W3Jets_2018.root"), 4.6999), //zh4b_0
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_W4Jets_2018.root"), 3.76576), 
    //DY
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_DYJetsToLL_10to50_2018.root"    ), 34.1773),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_DYJetsToLL_M50_2018.root"       ), 3.44673),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_DY1JetsToLL_M50_2018.root"      ), 0.670591),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_DY2JetsToLL_M50_2018.root"   ), 1.14288),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_DY3JetsToLL_M50_2018.root"   ), 1.20299),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_DY4JetsToLL_M50_2018.root"   ), 1.28832),
    //TG, TTG, TTW, TTZ
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_TGJets_2018.root"             ), 0.473579),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_TTGJets_2018.root"            ), 0.119878),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_TTWJetslnu_2018.root"         ), 0.00454377),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_TTZJets2l2nu_2018.root"       ), 0.00240808),
    //Di-boson
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WW_2018.root"                 ), 0.903338),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WZ_2018.root"                 ), 0.724729), //zh4b_0
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WminusH_2018.root"            ), 0.00107367),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WplusH_2018.root"             ), 0.00172244), //zh4b_0
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_ZH_2018.root"                 ), 0.000438741),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_ZZ_2018.root"                 ), 0.498784),
    //Tri-boson
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WWW_4F_2018.root"             ), 0.0593141),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WWZ_2018.root"                ), 0.0448509), //zh4b_0
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WZZ_2018.root"                ), 0.0151633),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_ZZZ_2018.root"                ), 0.00389754),
    //QCD
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_QCD_Pt80To120_EMEnr_2018.root"       ), 2167.03),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_QCD_Pt120To170_EMEnr_2018.root"      ), 377.504),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_QCD_Pt170To300_EMEnr_2018.root"      ), 302.712),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_QCD_Pt300ToInf_EMEnr_2018.root"      ), 27.7973),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_QCD_Pt80to120_MuEnrPt5_2018.root"    ), 246.938),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_QCD_Pt120to170_MuEnrPt5_2018.root"   ), 2374.9),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_QCD_Pt170to300_MuEnrPt5_2018.root"   ), 14.3704),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_QCD_Pt300to470_MuEnrPt5_2018.root"   ), 96.7355),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_QCD_Pt470to600_MuEnrPt5_2018.root"   ), 9.58165),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_QCD_Pt600to800_MuEnrPt5_2018.root"   ), 0.0902097),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_QCD_Pt800to1000_ext3_MuEnrPt5_2018.root"), 0.0121615),
//    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_QCD_Pt1000toInf_MuEnrPt5_2018.root"  ),0.00903547)
  };
  
  
  std::vector<std::pair<std::string, float> > SGfileURLWeightVec = SGfileURLWeightVec_2018Wh;
  std::vector<std::pair<std::string, float> > BGfileURLWeightVec = BGfileURLWeightVec_2018Wh;
};
#endif
