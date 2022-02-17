#ifndef tmvaTrainer_h
#define tmvaTrainer_h

#include <iostream>
#include <vector>
#include <string>
#include <utility>      // std::pair, std::make_pair
#include <cstdlib>

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
//#include "TMVA/Types.h"
#include "TMVA/TMVAGui.h"
#include "TMVA/HyperParameterOptimisation.h"
#include "TMVA/CrossValidation.h"

#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"


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

  std::string dir = "/afs/cern.ch/work/g/georgia/BSMAnalysis/CMSSW_9_4_9/src/UserCode/Haa4b_tmva/EOSTools/MVAFILES/";

  float lumi2016=36300.000;
  float lumi2017=41529.152;
  float lumi2018=59740.565;
  /*  
  // WH signal weights:
  float GenSGReWeightArr[24] = {1010516.,996279.,999279.,1010277.,998095.,1010418.,995119.,1008303.,
				953821.,938085.,958038.,934507.,934164.,955080.,937913.,953433.,
				1020300.,1022564.,1020605.,1021525.,1011352.,1019418.,1015129.,1019047.};
  */
  
    //ZH weights:
  float GenSGReWeightArr[24] = {965463.,990410.,965694.,985066.,994159.,986613.,993354.,974094.,
				494730.,497206.,496767.,493933.,494739.,493704.,496637.,496105.,
				496721.,297501.,494820.,484463.,490005.,484314.,472187.,495592.};
 
    /*
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
				1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
				1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    */
  std::vector<std::pair<std::string, float> > SGfileURLWeightVec_Wh = 
  {
    std::make_pair( dir + "WH_2016_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass12_2016.root"), 1.0),
    std::make_pair( dir + "WH_2016_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass15_2016.root"), 1.0),
    std::make_pair( dir + "WH_2016_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass20_2016.root"), 1.0),
    std::make_pair( dir + "WH_2016_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass25_2016.root"), 1.0),
    std::make_pair( dir + "WH_2016_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass30_2016.root"), 1.0),
    std::make_pair( dir + "WH_2016_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass40_2016.root"), 1.0),
    std::make_pair( dir + "WH_2016_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass50_2016.root"), 1.0),
    std::make_pair( dir + "WH_2016_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass60_2016.root"), 1.0),

    std::make_pair( dir + "WH_2017_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass12_2017.root"), 1.0),
    std::make_pair( dir + "WH_2017_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass15_2017.root"), 1.0),
    std::make_pair( dir + "WH_2017_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass20_2017.root"), 1.0),
    std::make_pair( dir + "WH_2017_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass25_2017.root"), 1.0),
    std::make_pair( dir + "WH_2017_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass30_2017.root"), 1.0),
    std::make_pair( dir + "WH_2017_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass40_2017.root"), 1.0),
    std::make_pair( dir + "WH_2017_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass50_2017.root"), 1.0),
    std::make_pair( dir + "WH_2017_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass60_2017.root"), 1.0),

    std::make_pair( dir + "WH_2018_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass12_2018.root"), 1.0),
    std::make_pair( dir + "WH_2018_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass15_2018.root"), 1.0),
    std::make_pair( dir + "WH_2018_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass20_2018.root"), 1.0),
    std::make_pair( dir + "WH_2018_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass25_2018.root"), 1.0),
    std::make_pair( dir + "WH_2018_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass30_2018.root"), 1.0),
    std::make_pair( dir + "WH_2018_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass40_2018.root"), 1.0),
    std::make_pair( dir + "WH_2018_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass50_2018.root"), 1.0),
    std::make_pair( dir + "WH_2018_MVABGMCFileList/" + std::string("mva_MC13TeV_Wh_amass60_2018.root"), 1.0)

  };
  std::vector<std::pair<std::string, float> > SGfileURLWeightVec_Zh = 
  {
    std::make_pair( dir + "ZH_2016_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass12_2016.root"), 1.0),
    std::make_pair( dir + "ZH_2016_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass15_2016.root"), 1.0),
    std::make_pair( dir + "ZH_2016_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass20_2016.root"), 1.0),
    std::make_pair( dir + "ZH_2016_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass25_2016.root"), 1.0),
    std::make_pair( dir + "ZH_2016_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass30_2016.root"), 1.0),
    std::make_pair( dir + "ZH_2016_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass40_2016.root"), 1.0),
    std::make_pair( dir + "ZH_2016_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass50_2016.root"), 1.0),
    std::make_pair( dir + "ZH_2016_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass60_2016.root"), 1.0),
 
    std::make_pair( dir + "ZH_2017_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass12_2017.root"), 1.0),
    std::make_pair( dir + "ZH_2017_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass15_2017.root"), 1.0),
    std::make_pair( dir + "ZH_2017_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass20_2017.root"), 1.0),
    std::make_pair( dir + "ZH_2017_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass25_2017.root"), 1.0),
    std::make_pair( dir + "ZH_2017_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass30_2017.root"), 1.0),
    std::make_pair( dir + "ZH_2017_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass40_2017.root"), 1.0),
    std::make_pair( dir + "ZH_2017_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass50_2017.root"), 1.0),
    std::make_pair( dir + "ZH_2017_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass60_2017.root"), 1.0),

    std::make_pair( dir + "ZH_2018_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass12_2018.root"), 1.0),
    std::make_pair( dir + "ZH_2018_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass15_2018.root"), 1.0),
    std::make_pair( dir + "ZH_2018_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass20_2018.root"), 1.0),
    std::make_pair( dir + "ZH_2018_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass25_2018.root"), 1.0),
    std::make_pair( dir + "ZH_2018_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass30_2018.root"), 1.0),
    std::make_pair( dir + "ZH_2018_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass40_2018.root"), 1.0),
    std::make_pair( dir + "ZH_2018_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass50_2018.root"), 1.0),
    std::make_pair( dir + "ZH_2018_MVABGMCFileList/" + std::string("mva_MC13TeV_Zh_amass60_2018.root"), 1.0)

  };

  std::vector<std::pair<std::string, float> > BGfileURLWeightVec_Wh =
  {
    //Single top
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_SingleT_s_2016.root"               ), lumi2016), //0.193558),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_SingleT_atW_2016.root"             ), lumi2016),//0.184169),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_SingleT_tW_2016.root"              ), lumi2016), //0.183646),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_SingleT_at_2016.root"              ), lumi2016), //0.0748094),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_SingleT_t_2016.root"               ), lumi2016), //0.0725545),
    //TTJets
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_TTJets_powheg_2016.root"          ), lumi2016), //0.387029),
    //WJets
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_2016.root"), lumi2016), //25.3643), //25.7282),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_ext2_2016.root"), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_HT70to100_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_HT100to200_ext1_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_HT100to200_ext2_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_HT200to400_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_HT200to400_ext1_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_HT200to400_ext2_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_HT400to600_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_HT400to600_ext1_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_HT600to800_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_HT600to800_ext1_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_HT800to1200_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_HT800to1200_ext1_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_HT1200to2500_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_HT1200to2500_ext1_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_HT2500toInf_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WJets_HT2500toInf_ext1_2016.root"), lumi2016), //1),

    //DY
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DYJetsToLL_10to50_2016.root"   ), 13.9757), // 18.9134), //comment out because 0 events
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DY1JetsToLL_10to50_2016.root"   ),  0.78975), //wh4b_0
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DY2JetsToLL_10to50_2016.root"   ), 0.880572), //wh4b_0
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DY3JetsToLL_10to50_2016.root"   ), 0.843379), //wh4b_0
//    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DY4JetsToLL_10to50_2016.root"   ), 0.7242), //0.763872),
  
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DYJetsToLL_50toInf_ext1_2016.root"  ), lumi2016), // 0.910305), //1.41826),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DYJetsToLL_50toInf_ext2_2016.root"  ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DY1JetsToLL_50toInf_2016.root"  ), lumi2016), //0.686605), //wh4b_0
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DY2JetsToLL_50toInf_2016.root"  ), lumi2016), //0.702326), //wh4b_0
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DY3JetsToLL_50toInf_2016.root"  ), lumi2016), //0.696408), //0.469104),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_DY4JetsToLL_50toInf_2016.root"  ), lumi2016), //0.518216), //0.381347),
    //TG, TTG, TTW, TTZ
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_TGJets_2016.root"                  ), lumi2016), //0.288736),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_TTGJets_2016.root"                 ), lumi2016), //0.0840393), //
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_TTWJetslnu_2016.root"              ), lumi2016), //0.00456969), //
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_TTZJets2l2nu_2016.root"            ), lumi2016), //0.00456969), //
    //Di-boson
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WW2l2nu_2016.root"                 ), lumi2016), //0.218503), //wh4b_0
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WWlnu2q_2016.root"                   ), lumi2016), //0.0945106),//wh4b_0
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WZ_2016.root"                   ), lumi2016), //1.69041),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_ZZ_2016.root"                   ), lumi2016), //0.319683),
    //Tri-boson
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_ZZZ_2016.root"                     ), lumi2016), //0.0355368),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WZZ_2016.root"                     ), lumi2016), //0.0267381),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WWZ_2016.root"                     ), lumi2016), //0.00922509),//wh4b_0
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WWW_4F_2016.root"                  ), lumi2016), // 0.00235191),//wh4b_0
    //VHBB
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WplusH_HToBB_WToLNu_2016.root"      ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WminusH_HToBB_WToLNu_ext1_2016.root" ), lumi2016), 
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_WminusH_HToBB_WToLNu_2016.root"     ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_ZH_HToBB_ZToLL_2016.root"           ), lumi2016), 
    //QCD
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt80To120_EMEnr_2016.root"     ), lumi2016),
    //    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt80To120_EMEnr_ext1_2016.root"     ), lumi2016), 
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt120To170_EMEnr_2016.root"    ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt120To170_EMEnr_ext1_2016.root"    ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt170To300_EMEnr_2016.root"    ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt300ToInf_EMEnr_2016.root"    ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt80to120_MuEnrPt5_2016.root"    ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt80to120_MuEnrPt5_ext1_2016.root"    ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt120to170_MuEnrPt5_2016.root"    ), lumi2016), 
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt170to300_MuEnrPt5_2016.root"    ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt170to300_MuEnrPt5_ext1_2016.root"    ), lumi2016), 
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt300to470_MuEnrPt5_2016.root"    ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt300to470_MuEnrPt5_ext2_2016.root"    ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt470to600_MuEnrPt5_2016.root"    ), lumi2016), 
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt470to600_MuEnrPt5_ext1_2016.root"    ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt470to600_MuEnrPt5_ext2_2016.root"    ), lumi2016),  
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt600to800_MuEnrPt5_2016.root"    ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt600to800_MuEnrPt5_ext1_2016.root"    ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt800to1000_MuEnrPt5_2016.root"    ), lumi2016),  
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt800to1000_MuEnrPt5_ext1_2016.root"    ), lumi2016), 
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt800to1000_MuEnrPt5_ext2_2016.root"    ), lumi2016), 
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt1000toInf_MuEnrPt5_2016.root"    ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt1000toInf_MuEnrPt5_ext1_2016.root"    ), lumi2016), 
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt_80to170_bcToE_2016.root"    ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt_170to250_bcToE_2016.root"    ), lumi2016),
    std::make_pair( dir + subdir_2016wh + std::string("mva_MC13TeV_QCD_Pt_250toInf_bcToE_2016.root"    ), lumi2016),
  
    //Single top
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_SingleT_s_2017.root"               ), lumi2017), // 0.0225202),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_SingleT_tW_antitop_2017.root"      ), lumi2017), //0.192354),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_SingleT_tW_top_2017.root"          ), lumi2017), //0.187515),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_SingleT_t_antitop_2017.root"       ), lumi2017), //0.297227),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_SingleT_t_top_2017.root"           ), lumi2017), //0.306894),
    //TTJets
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_TTTo2L2Nu_2017.root"       ), lumi2017), //0.0534525),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_TTToHadronic_2017.root"    ), lumi2017), //0.121478), //wh4b_0
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_TTToSemiLeptonic_2017.root"), lumi2017), //0.349759),
    //WJets
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WJets_2017.root"), lumi2017), //25.3643), //25.7282),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WJets_HT70to100_2017.root"), lumi2017), //1),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WJets_HT100to200_2017.root"), lumi2017), //1),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WJets_HT200to400_2017.root"), lumi2017), //1),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WJets_HT400to600_2017.root"), lumi2017), //1),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WJets_HT600to800_2017.root"), lumi2017), //1),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WJets_HT800to1200_2017.root"), lumi2017), //1),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WJets_HT1200to2500_2017.root"), lumi2017), //1),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WJets_HT2500toInf_2017.root"), lumi2017), //1),
    
    //DY
    //    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_DYJetsToLL_10to50_2017.root"    ), lumi2017), //23.4839),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_DYJetsToLL_M50_2017.root"       ), lumi2017), //2.45486),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_DYJetsToLL_M50_ext1_2017.root"       ), lumi2017), //2.45486),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_DY1JetsToLL_M50_2017.root"      ), lumi2017), //0.655604),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_DY1JetsToLL_M50_ext1_2017.root"      ), lumi2017), 
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_DY2JetsToLL_M50_2017.root"   ), lumi2017), //1.60537),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_DY2JetsToLL_M50_ext1_2017.root"   ), lumi2017),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_DY3JetsToLL_M50_2017.root"   ), lumi2017), //0.68556),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_DY3JetsToLL_M50_ext1_2017.root"   ), lumi2017),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_DY4JetsToLL_M50_2017.root"   ), lumi2017), //0.583365),
    //TG, TTG, TTW, TTZ
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_TGJets_2017.root"             ), lumi2017), //0.33112),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_TTGJets_ext1_v2_2017.root"            ), lumi2017), //0.0130277),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_TTGJets_v1_2017.root"            ), lumi2017),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_TTGJets_ext1_v1_2017.root"            ), lumi2017),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_TTGJets_v2_2017.root"            ), lumi2017),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_TTWJetslnu_2017.root"         ), lumi2017), //0.00312385),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_TTZJets2l2nu_2017.root"       ), lumi2017), //0.00280424),
    //Di-boson
    //    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WW_2017.root"                 ), lumi2017), //0.634769), //wh4b_0
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WZ_2017.root"                 ), lumi2017), //0.498206), //wh4b_0
    //  std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WminusH_2017.root"            ), lumi2017), //0.000619965),
    //std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WplusH_2017.root"             ), lumi2017), //0.000939266),
    // std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_ZH_2017.root"                 ), lumi2017), //0.000939266),
    //  std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_ZZ_2017.root"                 ), lumi2017), //0.356288), 
    //Tri-boson
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WWW_4F_2017.root"             ), lumi2017), //0.0426231), //wh4b_0
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WWZ_2017.root"                ), lumi2017), //0.0311708), //wh4b_0
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WZZ_2017.root"                ), lumi2017), //0.0105212),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_ZZZ_2017.root"                ), lumi2017), //0.00270895), //wh4b_0

    //VHBB 
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WplusH_HToBB_WToLNu_2017.root"), lumi2017),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_WminusH_HToBB_WToLNu_2017.root"), lumi2017), 
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_ZH_HToBB_ZToLL_2017.root"), lumi2017), 

    //QCD
    //std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt80To120_EMEnr_2017.root"), lumi2017),
    //std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt120To170_EMEnr_2017.root"), lumi2017),
    //std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt300ToInf_EMEnr_2017.root"), lumi2017), 
    //    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt80to120_MuEnrPt5_2017.root"), lumi2017), 
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt120to170_MuEnrPt5_2017.root"), lumi2017),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt170to300_MuEnrPt5_2017.root"), lumi2017), 
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt300to470_MuEnrPt5_2017.root"), lumi2017), 
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt470to600_MuEnrPt5_2017.root"), lumi2017), 
    //    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt_80to170_bcToE_2017.root"), lumi2017),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt_170to250_bcToE_2017.root"), lumi2017),
    std::make_pair( dir + subdir_2017wh + std::string("mva_MC13TeV_QCD_Pt_250toInf_bcToE_2017.root"), lumi2017),

      //Single top
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_SingleT_s_2018.root"               ), lumi2018), // 0.0225202),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_SingleT_tW_antitop_2018.root"      ), lumi2018), //0.192354),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_SingleT_tW_top_2018.root"          ), lumi2018), //0.187515),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_SingleT_t_antitop_2018.root"       ), lumi2018), //0.297227),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_SingleT_t_top_2018.root"           ), lumi2018), //0.306894),
    //TTJets
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_TTTo2L2Nu_2018.root"       ), lumi2018), //0.0534525),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_TTToHadronic_2018.root"    ), lumi2018), //0.121478), //wh4b_0
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_TTToSemiLeptonic_2018.root"), lumi2018), //0.349759),
    //WJets
    // std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WJets_2018.root" ), 32.8114),
    //WJets
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WJets_2018.root"), lumi2018), //25.3643), //25.7282),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WJets_HT70to100_2018.root"), lumi2018), //1),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WJets_HT100to200_2018.root"), lumi2018), //1),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WJets_HT200to400_2018.root"), lumi2018), //1),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WJets_HT400to600_2018.root"), lumi2018), //1),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WJets_HT600to800_2018.root"), lumi2018), //1),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WJets_HT800to1200_2018.root"), lumi2018), //1),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WJets_HT1200to2500_2018.root"), lumi2018), //1),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WJets_HT2500toInf_2018.root"), lumi2018), //1),
    
    //DY
    //    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_DYJetsToLL_10to50_2018.root"    ), lumi2018), //23.4839),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_DYJetsToLL_M50_2018.root"       ), lumi2018), //2.45486),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_DY1JetsToLL_M50_2018.root"      ), lumi2018), //0.655604),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_DY2JetsToLL_M50_2018.root"   ), lumi2018), //1.60537),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_DY3JetsToLL_M50_2018.root"   ), lumi2018), //0.68556),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_DY4JetsToLL_M50_2018.root"   ), lumi2018), //0.583365),
    //TG, TTG, TTW, TTZ
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_TGJets_2018.root"             ), lumi2018), //0.33112),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_TTGJets_2018.root"             ), lumi2018),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_TTWJetslnu_2018.root"         ), lumi2018), //0.00312385),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_TTZJets2l2nu_2018.root"       ), lumi2018), //0.00280424),
    //Di-boson
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_ZZ_2018.root"                 ), lumi2018), 
    //    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WW_2018.root"                 ), lumi2018), //0.634769), //wh4b_0
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WZ_2018.root"                 ), lumi2018), //0.498206), //wh4b_0
    //  std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WminusH_2018.root"            ), lumi2018), //0.000619965),
    //std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WplusH_2018.root"             ), lumi2018), //0.000939266),
    // std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_ZH_2018.root"                 ), lumi2018), //0.000939266),
    //  std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_ZZ_2018.root"                 ), lumi2018), //0.356288), 
    //Tri-boson
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WWW_4F_2018.root"             ), lumi2018), //0.0426231), //wh4b_0
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WWZ_2018.root"                ), lumi2018), //0.0311708), //wh4b_0
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WZZ_2018.root"                ), lumi2018), //0.0105212),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_ZZZ_2018.root"                ), lumi2018), //0.00270895), //wh4b_0

    //VHBB
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WplusH_HToBB_WToLNu_2018.root"        ), lumi2018),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WplusH_HToBB_WToLNu_ext1_2018.root"   ), lumi2018),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WminusH_HToBB_WToLNu_2018.root"       ), lumi2018), 
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_WminusH_HToBB_WToLNu_ext1_2018.root"  ), lumi2018),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_ZH_HToBB_ZToLL_2018.root"             ), lumi2018),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_ZH_HToBB_ZToLL_ext1_2018.root"        ), lumi2018),

    //QCD
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt80To120_EMEnr_2018.root"        ), lumi2018), 
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt120To170_EMEnr_2018.root"        ), lumi2018),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt300ToInf_EMEnr_2018.root"        ), lumi2018),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt80to120_MuEnrPt5_2018.root"        ), lumi2018), 
    //std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt80to120_MuEnrPt5_ext1_2018.root"        ), lumi2018), 
    //    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt120to170_MuEnrPt5_2018.root"        ), lumi2018),
    //    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt120to170_ext1_MuEnrPt5_2018.root"        ), lumi2018),  
    //    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt170to300_MuEnrPt5_2018.root"        ), lumi2018),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt300to470_MuEnrPt5_2018.root"        ), lumi2018),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt300to470_ext3_MuEnrPt5_2018.root"        ), lumi2018),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt470to600_MuEnrPt5_2018.root"        ), lumi2018),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt470to600_ext1_MuEnrPt5_2018.root"        ), lumi2018),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt600to800_MuEnrPt5_2018.root"        ), lumi2018),  
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt800to1000_ext3_MuEnrPt5_2018.root"        ), lumi2018),
    std::make_pair( dir + subdir_2018wh + std::string("mva_MC13TeV_QCD_Pt1000toInf_MuEnrPt5_2018.root"        ), lumi2018)

  };

  std::vector<std::pair<std::string, float> > BGfileURLWeightVec_Zh =
  {
    //Single top
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_SingleT_s_2016.root"               ), lumi2016), //0.193558),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_SingleT_atW_2016.root"             ), lumi2016),//0.184169),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_SingleT_tW_2016.root"              ), lumi2016), //0.183646),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_SingleT_at_2016.root"              ), lumi2016), //0.0748094),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_SingleT_t_2016.root"               ), lumi2016), //0.0725545),
    //TTJets
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_TTJets_powheg_2016.root"          ), lumi2016), //0.387029),
    //WJets
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_2016.root"), lumi2016), //25.3643), //25.7282),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_ext2_2016.root"), lumi2016),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_HT70to100_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_HT100to200_ext1_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_HT100to200_ext2_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_HT200to400_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_HT200to400_ext1_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_HT200to400_ext2_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_HT400to600_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_HT400to600_ext1_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_HT600to800_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_HT600to800_ext1_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_HT800to1200_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_HT800to1200_ext1_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_HT1200to2500_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_HT1200to2500_ext1_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_HT2500toInf_2016.root"), lumi2016), //1),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WJets_HT2500toInf_ext1_2016.root"), lumi2016), //1),

    //DY
//    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_DYJetsToLL_10to50_2016.root"   ), 13.9757), // 18.9134), //comment out because 0 events
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_DYJetsToLL_50toInf_ext1_2016.root"  ), lumi2016), // 0.910305), //1.41826),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_DYJetsToLL_50toInf_ext2_2016.root"  ), lumi2016),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_DY1JetsToLL_50toInf_2016.root"  ), lumi2016), //0.686605), //wh4b_0
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_DY2JetsToLL_50toInf_2016.root"  ), lumi2016), //0.702326), //wh4b_0
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_DY3JetsToLL_50toInf_2016.root"  ), lumi2016), //0.696408), //0.469104),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_DY4JetsToLL_50toInf_2016.root"  ), lumi2016), //0.518216), //0.381347),
    //TG, TTG, TTW, TTZ
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_TGJets_2016.root"                  ), lumi2016), //0.288736),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_TTGJets_2016.root"                 ), lumi2016), //0.0840393), //
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_TTWJetslnu_2016.root"              ), lumi2016), //0.00456969), //
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_TTZJets2l2nu_2016.root"            ), lumi2016), //0.00456969), //
    //Di-boson
    //    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WW2l2nu_2016.root"                 ), lumi2016), //0.218503), //wh4b_0
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WWlnu2q_2016.root"                   ), lumi2016), //0.0945106),//wh4b_0
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WZ_2016.root"                   ), lumi2016), //1.69041),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_ZZ_2016.root"                   ), lumi2016), //0.319683),
    //Tri-boson
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_ZZZ_2016.root"                     ), lumi2016), //0.0355368),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WZZ_2016.root"                     ), lumi2016), //0.0267381),
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WWZ_2016.root"                     ), lumi2016), //0.00922509),//wh4b_0
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WWW_4F_2016.root"                  ), lumi2016), // 0.00235191),//wh4b_0

    //VHBB
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WplusH_HToBB_WToLNu_2016.root"      ), lumi2016), 
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WminusH_HToBB_WToLNu_ext1_2016.root" ), lumi2016), 
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_WminusH_HToBB_WToLNu_2016.root"     ), lumi2016), 
    std::make_pair( dir + subdir_2016zh + std::string("mva_MC13TeV_ZH_HToBB_ZToLL_2016.root"           ), lumi2016), 

    //Single top
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_SingleT_s_2017.root"               ), lumi2017), // 0.0225202),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_SingleT_tW_antitop_2017.root"      ), lumi2017), //0.192354),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_SingleT_tW_top_2017.root"          ), lumi2017), //0.187515),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_SingleT_t_antitop_2017.root"       ), lumi2017), //0.297227),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_SingleT_t_top_2017.root"           ), lumi2017), //0.306894),
    //TTJets
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_TTTo2L2Nu_2017.root"       ), lumi2017), //0.0534525),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_TTToHadronic_2017.root"    ), lumi2017), //0.121478), //zh4b_0
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_TTToSemiLeptonic_2017.root"), lumi2017), //0.349759),

    //WJets
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WJets_2017.root"), lumi2017), //25.3643), //25.7282),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WJets_HT70to100_2017.root"), lumi2017), //1),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WJets_HT100to200_2017.root"), lumi2017), //1),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WJets_HT200to400_2017.root"), lumi2017), //1),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WJets_HT400to600_2017.root"), lumi2017), //1),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WJets_HT600to800_2017.root"), lumi2017), //1),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WJets_HT800to1200_2017.root"), lumi2017), //1),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WJets_HT1200to2500_2017.root"), lumi2017), //1),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WJets_HT2500toInf_2017.root"), lumi2017), //1),
    
    //DY
    //    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_DYJetsToLL_10to50_2017.root"    ), lumi2017), //23.4839),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_DYJetsToLL_M50_2017.root"       ), lumi2017), //2.45486),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_DYJetsToLL_M50_ext1_2017.root"       ), lumi2017), //2.45486),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_DY1JetsToLL_M50_2017.root"      ), lumi2017), //0.655604),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_DY1JetsToLL_M50_ext1_2017.root"      ), lumi2017), 
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_DY2JetsToLL_M50_2017.root"   ), lumi2017), //1.60537),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_DY2JetsToLL_M50_ext1_2017.root"   ), lumi2017),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_DY3JetsToLL_M50_2017.root"   ), lumi2017), //0.68556),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_DY3JetsToLL_M50_ext1_2017.root"   ), lumi2017),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_DY4JetsToLL_M50_2017.root"   ), lumi2017), //0.583365),
    //TG, TTG, TTW, TTZ
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_TGJets_2017.root"             ), lumi2017), //0.33112),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_TTGJets_ext1_v2_2017.root"            ), lumi2017), //0.0130277),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_TTGJets_v1_2017.root"            ), lumi2017),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_TTGJets_ext1_v1_2017.root"            ), lumi2017),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_TTGJets_v2_2017.root"            ), lumi2017),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_TTWJetslnu_2017.root"         ), lumi2017), //0.00312385),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_TTZJets2l2nu_2017.root"       ), lumi2017), //0.00280424),
    //Di-boson
    //    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WW_2017.root"                 ), lumi2017), //0.634769), //zh4b_0
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WZ_2017.root"                 ), lumi2017), //0.498206), //zh4b_0
    //  std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WminusH_2017.root"            ), lumi2017), //0.000619965),
    //std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WplusH_2017.root"             ), lumi2017), //0.000939266),
    // std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_ZH_2017.root"                 ), lumi2017), //0.000939266),
    //  std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_ZZ_2017.root"                 ), lumi2017), //0.356288), 
    //Tri-boson
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WWW_4F_2017.root"             ), lumi2017), //0.0426231), //zh4b_0
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WWZ_2017.root"                ), lumi2017), //0.0311708), //zh4b_0
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WZZ_2017.root"                ), lumi2017), //0.0105212),
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_ZZZ_2017.root"                ), lumi2017), //0.00270895), //zh4b_0
    //VHBB
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WplusH_HToBB_WToLNu_2017.root"), lumi2017), 
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_WminusH_HToBB_WToLNu_2017.root"), lumi2017), 
    std::make_pair( dir + subdir_2017zh + std::string("mva_MC13TeV_ZH_HToBB_ZToLL_2017.root"), lumi2017), 

    //Single top
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_SingleT_s_2018.root"               ), lumi2018), // 0.0225202),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_SingleT_tW_antitop_2018.root"      ), lumi2018), //0.192354),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_SingleT_tW_top_2018.root"          ), lumi2018), //0.187515),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_SingleT_t_antitop_2018.root"       ), lumi2018), //0.297227),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_SingleT_t_top_2018.root"           ), lumi2018), //0.306894),
    //TTJets
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_TTTo2L2Nu_2018.root"       ), lumi2018), //0.0534525),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_TTToHadronic_2018.root"    ), lumi2018), //0.121478), //zh4b_0
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_TTToSemiLeptonic_2018.root"), lumi2018), //0.349759),

    //WJets
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WJets_2018.root"), lumi2018), //25.3643), //25.7282),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WJets_HT70to100_2018.root"), lumi2018), //1),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WJets_HT100to200_2018.root"), lumi2018), //1),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WJets_HT200to400_2018.root"), lumi2018), //1),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WJets_HT400to600_2018.root"), lumi2018), //1),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WJets_HT600to800_2018.root"), lumi2018), //1),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WJets_HT800to1200_2018.root"), lumi2018), //1),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WJets_HT1200to2500_2018.root"), lumi2018), //1),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WJets_HT2500toInf_2018.root"), lumi2018), //1),
    
    //DY
    //    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_DYJetsToLL_10to50_2018.root"    ), lumi2018), //23.4839),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_DYJetsToLL_M50_2018.root"       ), lumi2018), //2.45486),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_DY1JetsToLL_M50_2018.root"      ), lumi2018), //0.655604),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_DY2JetsToLL_M50_2018.root"   ), lumi2018), //1.60537),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_DY3JetsToLL_M50_2018.root"   ), lumi2018), //0.68556),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_DY4JetsToLL_M50_2018.root"   ), lumi2018), //0.583365),
    //TG, TTG, TTW, TTZ
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_TGJets_2018.root"             ), lumi2018), //0.33112),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_TTGJets_2018.root"            ), lumi2018), //0.0130277),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_TTWJetslnu_2018.root"         ), lumi2018), //0.00312385),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_TTZJets2l2nu_2018.root"       ), lumi2018), //0.00280424),
    //Di-boson
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_ZZ_2018.root"                 ), lumi2018), 
    //    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WW_2018.root"                 ), lumi2018), //0.634769), //zh4b_0
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WZ_2018.root"                 ), lumi2018), //0.498206), //zh4b_0
    //Tri-boson
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WWW_4F_2018.root"             ), lumi2018), //0.0426231), //zh4b_0
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WWZ_2018.root"                ), lumi2018), //0.0311708), //zh4b_0
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WZZ_2018.root"                ), lumi2018), //0.0105212),
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_ZZZ_2018.root"                ), lumi2018), //0.00270895), //zh4b_0

    //VHBB 
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WplusH_HToBB_WToLNu_2018.root"        ), lumi2018), 
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WplusH_HToBB_WToLNu_ext1_2018.root"   ), lumi2018), 
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WminusH_HToBB_WToLNu_2018.root"       ), lumi2018), 
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_WminusH_HToBB_WToLNu_ext1_2018.root"  ), lumi2018), 
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_ZH_HToBB_ZToLL_2018.root"             ), lumi2018), 
    std::make_pair( dir + subdir_2018zh + std::string("mva_MC13TeV_ZH_HToBB_ZToLL_ext1_2018.root"        ), lumi2018) 

  };
  
  std::vector<std::pair<std::string, float> > SGfileURLWeightVec = SGfileURLWeightVec_Zh;
  std::vector<std::pair<std::string, float> > BGfileURLWeightVec = BGfileURLWeightVec_Zh;  

};
#endif
