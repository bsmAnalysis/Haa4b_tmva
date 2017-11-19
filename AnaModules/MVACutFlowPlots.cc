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
    std::cerr <<"Please give at least 1 argument " << "TargetDirName" << std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./MVACutFlowPlots TribMVA Test" << std::endl;
    return -1;
  }

  std::string TrainMode = argv[1];
  std::string DirName = argv[2];

  BasicCheckPlots myBasicCheckPlots;
  myBasicCheckPlots.Initialization(TrainMode, DirName);
  //initialize the closure plots parameter we want to investigate
  std::vector<Plotting_Parameter> myPlotting_Paramete = 
  { 
    //MVA basic check plots
    {"_WpT_"    , "p_{T}^{W} [GeV]"           ,    0, 400},
    {"_Hmass_"  , "m_{h} [GeV]"               ,    0, 800}, 
    {"_HpT_"    , "p_{T}^{h} [GeV]"           ,    0, 400},  
    {"_bbdRAve_", "#Delta R_{b,b}^{ave}"      ,    0,   5},                                               
    {"_bbdMMin_", "#Delta m_{b,b}^{min} [GeV]",    0, 400},
    {"_HHt_"    , "H_{T} [GeV]"               ,    0, 600},
    {"_WHdR_"   , "#Delta #phi (W,h)"         ,    0, 3.2},
    {"_BDT_"    , "BDT"                       , -0.5, 0.5},
    {"_n_"      , "Cut"                       ,    0,   9}
  };

  std::vector<Plotting_Parameter>::iterator iter_p;

  for( iter_p = myPlotting_Paramete.begin() ; iter_p != myPlotting_Paramete.end() ; iter_p ++)
  {
    myBasicCheckPlots.BasicCheckTemplate(
                                         (*iter_p).hist_tag,
                                         (*iter_p).XTitle,
                                         (*iter_p).min,
                                         (*iter_p).max 
                                        );
  }

  myPlotting_Paramete.clear();
  
  return 0;
}

