#include <iostream>
#include <utility>      // std::pair, std::make_pair

#include "TFile.h"
#include "TH1D.h"

class MVACutFlowHist
{
 public:
  void BookHistgram(const char *);

  TFile *oFile;

  const static int BCBin = 6;
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

  TH1D *h_b_met_MC[BCBin], *h_b_mt2_MC[BCBin], *h_b_ntopjets_MC[BCBin], *h_b_nbjets_MC[BCBin];
  TH1D *h_b_ht_MC[BCBin], *h_b_mht_MC[BCBin], *h_b_njets30_MC[BCBin], *h_b_njets50_MC[BCBin];
  TH1D *h_b_sb_MC[BCBin];

  TH1D *h_b_met_Data, *h_b_mt2_Data, *h_b_ntopjets_Data, *h_b_nbjets_Data;
  TH1D *h_b_ht_Data, *h_b_mht_Data, *h_b_njets30_Data, *h_b_njets50_Data;
  TH1D *h_b_sb_Data;
  //TH1D *h_b_mt2_nbnt, *h_b_mt2_ybyt, *h_b_met_nbnt, *h_b_met_ybyt;
  //TH1D *h_b_dphi0_nbnt, *h_b_dphi0_ybyt, *h_b_dphi1_nbnt, *h_b_dphi1_ybyt, *h_b_dphi2_nbnt, *h_b_dphi2_ybyt;
  //TH1D *h_inverted_met, *h_inverted_njets, *h_inverted_mt2, *h_inverted_ht, *h_inverted_mht, *h_inverted_ntopjets, *h_inverted_nbjets;
  //TH1D *h_b_ttz_weight;
};

