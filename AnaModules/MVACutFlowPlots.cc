#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <set>

#include "TFile.h"
#include "TList.h"
#include "TString.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"
#include "THStack.h"

#include "MVACutFlowPlots.h"

int main(int argc, char* argv[])
{

  if (argc < 1)
  {
    std::cerr <<"Please give at least 2 arguments " << "TrainMode TargetDirName" << std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./MVACutFlowPlots TribMVA Test" << std::endl;
    return -1;
  }

  std::string TrainMode = argv[1];
  std::string DirName = argv[2];

  MVACutFlowPlots myMVACutFlowPlots;
  myMVACutFlowPlots.Initialization(TrainMode, DirName);
  //initialize the closure plots parameter we want to investigate
  std::vector<Plotting_Parameter> myPlotting_Paramete = 
  { 
    //MVA basic check plots
    {"_WpT_"    , "p_{T}^{V} [GeV]"           ,    0, 400,  true, true,  true},
    {"_Hmass_"  , "m_{h} [GeV]"               ,    0, 800,  true, true,  true}, 
    {"_HpT_"    , "p_{T}^{h} [GeV]"           ,    0, 400,  true, true,  true},  
    {"_bbdRAve_", "#Delta R_{b,b}^{ave}"      ,    0,   5,  true, true,  true},
    {"_bbdMMin_", "#Delta m_{b,b}^{min} [GeV]",    0, 400,  true, true,  true},
    {"_HHt_"    , "H_{T} [GeV]"               ,    0, 600,  true, true,  true},
    {"_WHdR_"   , "#Delta #phi (V,h)"         ,    0, 3.2,  true, true,  true},
    {"_lepPt_"  , "Lepton p_{T} [GeV]"              ,    20, 200,  true, true, true},
    {"_pfMET_"  , "pfMET [GeV]"               ,    0, 300, true, true, true}, 
    {"_MTw_"    , "M_{T} [GeV]"               ,    40, 250, true, true, true}, 
    {"_ljDR_"  , "min |#Delta #phi(j, MET)|" ,    0, 3.15, true, true, true}, 
    {"_BDT_"    , "BDT"                       , -0.5, 0.5,  true, true,  true},
    /*
    {"_n_"      , "Cut"                       ,    0,   9,  true, true,  true},
    {"_negW_"   , "Cut"                       ,    0,   9, false, true, false},
    {"_posW_"   , "Cut"                       ,    0,   9, false, true, false}
    */
  };

  std::vector<Plotting_Parameter>::iterator iter_p;

  for( iter_p = myPlotting_Paramete.begin() ; iter_p != myPlotting_Paramete.end() ; iter_p ++)
  {
    myMVACutFlowPlots.BasicCheckTemplate(
                                         (*iter_p).hist_tag,
                                         (*iter_p).XTitle,
                                         (*iter_p).min, (*iter_p).max,
                                         (*iter_p).sgMC, (*iter_p).bgMC, (*iter_p).Data 
                                        );
  }
  
  myPlotting_Paramete.clear();

  myMVACutFlowPlots.SensitivityMap(0);
  myMVACutFlowPlots.SensitivityMap(1);
  myMVACutFlowPlots.SensitivityMap(2);
  myMVACutFlowPlots.SensitivityMap(3);
  myMVACutFlowPlots.SensitivityMap(4);
  myMVACutFlowPlots.SensitivityMap(5);
  myMVACutFlowPlots.SensitivityMap(6);
  return 0;
}

