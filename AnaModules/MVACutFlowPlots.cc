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
    std::cerr <<" ./BasicCheckPlots BasicCheckQCD20151209 or ./BasicCheckPlots BasicCheckLL20151211" << std::endl;
    return -1;
  }

  std::string DirName = argv[1];

  BasicCheckPlots myBasicCheckPlots;
  myBasicCheckPlots.Initialization(DirName);
  //initialize the closure plots parameter we want to investigate
  std::vector<Plotting_Parameter> myPlotting_Paramete = 
  { 
    //MVA basic check plots
    {"_WpT"    , "WpT [GeV]"    ,    0, 2000},
    {"_Hmass"  , "Hmass [GeV]"  ,    0, 2000}, 
    {"_HpT"    , "HpT [GeV]"    ,    0, 2000},  
    {"_bbdRAve", "bbdRAve"      ,    0, 5   },                                               
    {"_bbdMMin", "bbdMMin [GeV]",    0, 2000},
    {"_HHt"    , "HHt [GeV]"    ,    0, 2000},
    {"_WHdR"   , "WHdR"         ,    0, 4   },
    {"_BDT"    , "BDT"          , -0.5, 0.5 }
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

