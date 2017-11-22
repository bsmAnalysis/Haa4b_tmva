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

#include "MVAOutPlots.h"

int main(int argc, char* argv[])
{

  if (argc < 1)
  {
    std::cerr <<"Please give at least 1 argument " << "TrainMode TargetDirName" << std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./MVAOutPlots TribMVA Test" << std::endl;
    return -1;
  }

  std::string TrainMode = argv[1];
  std::string DirName = argv[2];

  MVAOutPlots myMVAOutPlots;
  myMVAOutPlots.Initialization(TrainMode, DirName);
  myMVAOutPlots.SensitivityMap(0);
  myMVAOutPlots.SensitivityMap(1);
  myMVAOutPlots.SensitivityMap(2);
  return 0;
}

