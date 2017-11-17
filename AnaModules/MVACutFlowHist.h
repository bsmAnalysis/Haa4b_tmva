#include <iostream>
#include <utility>      // std::pair, std::make_pair

#include "TFile.h"
#include "TH1F.h"

class MVACutFlowHist
{
 public:
  void BookHistgram(const char *);

  TFile *oFile;

  const static int SGBin = 2;
  const static int BGBin = 8;
  const static int MVACutFlowBin = 9;
  const float mvaCutFlow[MVACutFlowBin ] = { -0.2, -0.15, -0.1, -0.05, 0, 0.05, 0.1, 0.15, 0.2 };

  std::pair<int, int> getHistoBinEdgeFromMVA( float thismva )
  {
    std::pair <int, int> edge ( 1, -1 );
    
    for ( int i = MVACutFlowBin-1; i >=0 ; i-- )
    {
      if (thismva > mvaCutFlow[i] ) 
      { 
        edge.second = i+1; 
        break;
      }
    }
    return edge;
  }

  TH1F *h_b_WpT_SGMC[SGBin];
  TH1F *h_b_Hmass_SGMC[SGBin], *h_b_HpT_SGMC[SGBin], *h_b_bbdRAve_SGMC[SGBin], *h_b_bbdMMin_SGMC[SGBin], *h_b_HHt_SGMC[SGBin];
  TH1F *h_b_WHdR_SGMC[SGBin];
  TH1F *h_b_n_SGMC[SGBin];

  TH1F *h_b_WpT_BGMC[BGBin];
  TH1F *h_b_Hmass_BGMC[BGBin], *h_b_HpT_BGMC[BGBin], *h_b_bbdRAve_BGMC[BGBin], *h_b_bbdMMin_BGMC[BGBin], *h_b_HHt_BGMC[BGBin];
  TH1F *h_b_WHdR_BGMC[BGBin];
  TH1F *h_b_n_BGMC[BGBin];

  TH1F *h_b_WpT_Data;
  TH1F *h_b_Hmass_Data, *h_b_HpT_Data, *h_b_bbdRAve_Data, *h_b_bbdMMin_Data, *h_b_HHt_Data;
  TH1F *h_b_WHdR_Data;
  TH1F *h_b_n_Data;
};

