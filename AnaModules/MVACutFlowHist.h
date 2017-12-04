#include <iostream>
#include <utility>      // std::pair, std::make_pair
#include <algorithm>    // std::copy

#include "TFile.h"
#include "TH1F.h"

class MVACutFlowHist
{
 public:
  void BookHistgram(const char *);

  TFile *oFile;

  const static int SGBin = 8;
  const static int BGBin = 8;
  const static int MVACutFlowBin = 9;
  //const float mvaCutFlow[MVACutFlowBin] = { -0.2, -0.15, -0.1, -0.05, 0.0, 0.05, 0.1, 0.15, 0.2 };
  //const float mvaCutFlow[MVACutFlowBin] = { 0, 0.05, 0.075, 0.1, 0.125, 0.15, 0.175, 0.2, 0.225 };
  //const float mvaCutFlow_Trib[MVACutFlowBin] = { 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.20 };
  //const float mvaCutFlow_Quab[MVACutFlowBin] = { 0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15 };
  const float mvaCutFlow_Trib[MVACutFlowBin] = { 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.20, 0.21 };
  const float mvaCutFlow_Quab[MVACutFlowBin] = { 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17 };
  //const float mvaCutFlow_Trib[MVACutFlowBin] = { 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.20 };
  //const float mvaCutFlow_Quab[MVACutFlowBin] = { 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16 };

  std::pair<int, int> getHistoBinEdgeFromMVA( float thismva, std::string TrainMode )
  {
    std::pair <int, int> edge ( 0, -1 );

    float thismvaCutFlow[MVACutFlowBin];
    if      ( TrainMode == "TribMVA" ) std::copy(std::begin(mvaCutFlow_Trib), std::end(mvaCutFlow_Trib), std::begin(thismvaCutFlow));
    else if ( TrainMode == "QuabMVA" ) std::copy(std::begin(mvaCutFlow_Quab), std::end(mvaCutFlow_Quab), std::begin(thismvaCutFlow));

    for ( int i = MVACutFlowBin-1; i >=0 ; i-- )
    {
      if (thismva > thismvaCutFlow[i] ) 
      { 
        edge.second = i; 
        break;
      }
    }
    return edge;
  }

  TH1F *h_b_WpT_SGMC[SGBin];
  TH1F *h_b_Hmass_SGMC[SGBin], *h_b_HpT_SGMC[SGBin], *h_b_bbdRAve_SGMC[SGBin], *h_b_bbdMMin_SGMC[SGBin], *h_b_HHt_SGMC[SGBin];
  TH1F *h_b_WHdR_SGMC[SGBin];
  TH1F *h_b_BDT_SGMC[SGBin];
  TH1F *h_b_n_SGMC[SGBin];

  TH1F *h_b_WpT_BGMC[BGBin];
  TH1F *h_b_Hmass_BGMC[BGBin], *h_b_HpT_BGMC[BGBin], *h_b_bbdRAve_BGMC[BGBin], *h_b_bbdMMin_BGMC[BGBin], *h_b_HHt_BGMC[BGBin];
  TH1F *h_b_WHdR_BGMC[BGBin];
  TH1F *h_b_BDT_BGMC[BGBin];
  TH1F *h_b_n_BGMC[BGBin];

  //check negative weight in MVA, MC bg
  TH1F *h_b_negW_BGMC[BGBin], *h_b_posW_BGMC[BGBin];

  TH1F *h_b_WpT_Data;
  TH1F *h_b_Hmass_Data, *h_b_HpT_Data, *h_b_bbdRAve_Data, *h_b_bbdMMin_Data, *h_b_HHt_Data;
  TH1F *h_b_WHdR_Data;
  TH1F *h_b_BDT_Data;
  TH1F *h_b_n_Data;
};

