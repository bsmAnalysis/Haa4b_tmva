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
  std::string dir = "/eos/cms/store/user/georgia/bsm_analysis/ZH/MVARes/"; //"root://eosuser.cern.ch//eos/user/h/hua/Haa4b/MVARes/";

  //std::string dir = "/eos/cms/store/user/georgia/bsm_analysis/haa4b/MVARes/"; 
  float GenSGReWeightArr[8] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0}; //, 1.0, 1.0};
  std::vector<std::pair<std::string, float>> SGfileURLWeightVec = 
  {
    //    std::make_pair( dir + std::string("mva_MC13TeV_Zh_amass12.root"), 1.0),
    //    std::make_pair( dir + std::string("mva_MC13TeV_Zh_amass15.root"), 1.0),
    std::make_pair( dir + std::string("mva_MC13TeV_Zh_amass20.root"), 1.0),
    std::make_pair( dir + std::string("mva_MC13TeV_Zh_amass25.root"), 1.0),
    std::make_pair( dir + std::string("mva_MC13TeV_Zh_amass30.root"), 1.0),
    std::make_pair( dir + std::string("mva_MC13TeV_Zh_amass40.root"), 1.0),
    std::make_pair( dir + std::string("mva_MC13TeV_Zh_amass50.root"), 1.0),
    std::make_pair( dir + std::string("mva_MC13TeV_Zh_amass60.root"), 1.0),
    
//  std::make_pair( dir + std::string("mva_MC13TeV_Wh_amass12.root"), 0.12371),
    // std::make_pair( dir + std::string("mva_MC13TeV_Wh_amass15.root"), 0.12293),
    // std::make_pair( dir + std::string("mva_MC13TeV_Wh_amass20.root"), 0.12827),
    // std::make_pair( dir + std::string("mva_MC13TeV_Wh_amass25.root"), 0.123152),
    //std::make_pair( dir + std::string("mva_MC13TeV_Wh_amass30.root"), 0.12298),
  //std::make_pair( dir + std::string("mva_MC13TeV_Wh_amass40.root"), 0.123598),
  //std::make_pair( dir + std::string("mva_MC13TeV_Wh_amass50.root"), 0.12309),
  //std::make_pair( dir + std::string("mva_MC13TeV_Wh_amass60.root"), 0.123375),
  };
  std::vector<std::pair<std::string, float>> BGfileURLWeightVec =
  {
  //Single top
    //  std::make_pair( dir + std::string("mva_MC13TeV_SingleT_s.root"               ), 0.193558),
  std::make_pair( dir + std::string("mva_MC13TeV_SingleT_atW.root"             ), 0.184169),
  std::make_pair( dir + std::string("mva_MC13TeV_SingleT_tW.root"              ), 0.183646),
  std::make_pair( dir + std::string("mva_MC13TeV_SingleT_at.root"              ), 0.0758015),
  std::make_pair( dir + std::string("mva_MC13TeV_SingleT_t.root"               ), 0.0736499),
  //TTJets
  //std::make_pair( dir + std::string("mva_MC13TeV_TTJets.root"                  ), 1.9437),
  //std::make_pair( dir + std::string("mva_MC13TeV_TTJets_slt.root"              ), 0.105736*0.1929),
  //std::make_pair( dir + std::string("mva_MC13TeV_TTJets_slt_ext1.root"         ), 0.105736*0.8071),
  //std::make_pair( dir + std::string("HaddExt/mva_MC13TeV_TTJets_slt.root"    ), 0.105736),
  //std::make_pair( dir + std::string("mva_MC13TeV_TTJets_slat.root"             ), 0.108833*0.1984),
  //std::make_pair( dir + std::string("mva_MC13TeV_TTJets_slat_ext1.root"        ), 0.109933*0.8016),
  //std::make_pair( dir + std::string("HaddExt/mva_MC13TeV_TTJets_slat.root"    ), 0.109933),
  //std::make_pair( dir + std::string("mva_MC13TeV_TTJets_dl.root"               ), 0.104012*0.2002),
  //std::make_pair( dir + std::string("mva_MC13TeV_TTJets_dl_ext1.root"          ), 0.104012*0.7998),
  //std::make_pair( dir + std::string("HaddExt/mva_MC13TeV_TTJets_dl.root"    ), 0.104012),
  std::make_pair( dir + std::string("mva_MC13TeV_TTJets_powheg.root"          ), 0.387029),
  //WJets
  //std::make_pair( dir + std::string("mva_MC13TeV_WJets.root"), 25.648), //25.7282),
  //std::make_pair( dir + std::string("mva_MC13TeV_W1Jets.root"), 9.16444), //6.85513),
  //  std::make_pair( dir + std::string("mva_MC13TeV_W2Jets.root"), 2.25525), //2.11101),
  //  std::make_pair( dir + std::string("mva_MC13TeV_W3Jets.root"), 0.692341), //0.687131),
  //  std::make_pair( dir + std::string("mva_MC13TeV_W4Jets.root"), 0.758444), //0.750822),
  //DY
  //  std::make_pair( dir + std::string("mva_MC13TeV_DYJetsToLL_10to50.root"   ), 22.8852), // 18.9134), //comment out because 0 events
  //  std::make_pair( dir + std::string("mva_MC13TeV_DY1JetsToLL_10to50.root"   ),  0.78975), //0.829979),
  //  std::make_pair( dir + std::string("mva_MC13TeV_DY2JetsToLL_10to50.root"   ), 0.880572), //0.92078),
  //  std::make_pair( dir + std::string("mva_MC13TeV_DY3JetsToLL_10to50.root"   ), 0.843379), //0.883706),
  //  std::make_pair( dir + std::string("mva_MC13TeV_DY4JetsToLL_10to50.root"   ), 0.7242), //0.763872),

  std::make_pair( dir + std::string("mva_MC13TeV_DYJetsToLL_50toInf.root"  ), 1.40885), //1.41826),
  std::make_pair( dir + std::string("mva_MC13TeV_DY1JetsToLL_50toInf.root"  ), 0.689835), //0.468798),
  std::make_pair( dir + std::string("mva_MC13TeV_DY2JetsToLL_50toInf.root"  ), 0.696374), //0.471764),
  std::make_pair( dir + std::string("mva_MC13TeV_DY3JetsToLL_50toInf.root"  ), 0.690506), //0.469104),
  std::make_pair( dir + std::string("mva_MC13TeV_DY4JetsToLL_50toInf.root"  ), 0.513824), //0.381347),
  //TG, TTG, TTW, TTZ
  //std::make_pair( dir + std::string("mva_MC13TeV_TGJets.root"                  ), 0.288736*0.25),
  //std::make_pair( dir + std::string("mva_MC13TeV_TGJets_ext1.root"             ), 0.288736*0.75), //ext1
  //  std::make_pair( dir + std::string("mva_MC13TeV_TGJets.root"      ), 0.288736),
  std::make_pair( dir + std::string("mva_MC13TeV_TTGJets.root"                 ), 0.0840393), //
  std::make_pair( dir + std::string("mva_MC13TeV_TTWJetslnu.root"              ), 0.00456969), //
  std::make_pair( dir + std::string("mva_MC13TeV_TTZJets2l2nu.root"            ), 0.0133538), //
  //Di-boson
  std::make_pair( dir + std::string("mva_MC13TeV_WW2l2nu.root"                 ), 0.218503),
  //  std::make_pair( dir + std::string("mva_MC13TeV_WWlnu2q.root"                   ), 0.199298),
  std::make_pair( dir + std::string("mva_MC13TeV_WZ.root"                   ), 0.423043),
  std::make_pair( dir + std::string("mva_MC13TeV_ZZ.root"                   ), 0.298089),
  //Tri-boson
  std::make_pair( dir + std::string("mva_MC13TeV_ZZZ.root"                     ), 0.0355368),
  std::make_pair( dir + std::string("mva_MC13TeV_WZZ.root"                     ), 0.0267381),
  std::make_pair( dir + std::string("mva_MC13TeV_WWZ.root"                     ), 0.00922509),
  //  std::make_pair( dir + std::string("mva_MC13TeV_WWW_4F.root"                  ), 0.00235191),
  //QCD
  //std::make_pair( dir + std::string("mva_MC13TeV_QCD_Pt20To30_EMEnr.root"      ), 1.0), //0 events, co3b, co4b
  //std::make_pair( dir + std::string("mva_MC13TeV_QCD_Pt30To50_EMEnr.root"      ), 1.0), //0 events, co3b, co4b
  //std::make_pair( dir + std::string("mva_MC13TeV_QCD_Pt30To50_EMEnr_ext1.root" ), 1.0), //0 events, co3b, co4b
  //std::make_pair( dir + std::string("mva_MC13TeV_QCD_Pt50To80_EMEnr.root"      ), 4416.95),
  //  std::make_pair( dir + std::string("mva_MC13TeV_QCD_Pt80To120_EMEnr.root"     ), 350.246),
  //  std::make_pair( dir + std::string("mva_MC13TeV_QCD_Pt120To170_EMEnr.root"    ), 63.0513),
  //  std::make_pair( dir + std::string("mva_MC13TeV_QCD_Pt170To300_EMEnr.root"    ), 58.4617),
  //  std::make_pair( dir + std::string("mva_MC13TeV_QCD_Pt300ToInf_EMEnr.root"    ), 6.56669),
  //  std::make_pair( dir + std::string("mva_MC13TeV_QCD_Pt20ToInf_MuEnr.root"     ), 491.35)
  };
};
#endif
