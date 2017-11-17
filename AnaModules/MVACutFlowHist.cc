#include "MVACutFlowHist.h"

void MVACutFlowHist::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");

  for( int i = 0 ; i < SGBin ; i++ )
  {
    std::string smalltag;

    if (i == 0) smalltag = "Wh20";
    else if (i == 1) smalltag = "Wh50";

    h_b_WpT_SGMC[i] = new TH1F( ("h_b_WpT_SGMC_" + smalltag).c_str(),"",200,0,2000);
    h_b_Hmass_SGMC[i] = new TH1F( ("h_b_Hmass_SGMC_" + smalltag).c_str(),"",500,0,5000);
    h_b_HpT_SGMC[i] = new TH1F( ("h_b_HpT_SGMC_" + smalltag).c_str(),"",200,0,2000);
    h_b_bbdRAve_SGMC[i] = new TH1F( ("h_b_bbdRAve_SGMC_" + smalltag).c_str(),"",500,0,5);
    h_b_bbdMMin_SGMC[i] = new TH1F( ("h_b_bbdMMin_SGMC_" + smalltag).c_str(),"",200,0,2000);
    h_b_HHt_SGMC[i] = new TH1F( ("h_b_HHt_SGMC_" + smalltag).c_str(),"",400,0,4000);
    h_b_WHdR_SGMC[i] = new TH1F( ("h_b_WHdR_SGMC_" + smalltag).c_str(),"",400,0,4);

    h_b_n_SGMC[i] = new TH1F( ("h_b_n_SGMC_" + smalltag).c_str(),"",60,0,60);

    /*
    h_b_WpT_SGMC[i]->SetFillColor(i+2);
    h_b_Hmass_SGMC[i]->SetFillColor(i+2);
    h_b_HpT_SGMC[i]->SetFillColor(i+2);
    h_b_bbdRAve_SGMC[i]->SetFillColor(i+2);
    h_b_bbdMMin_SGMC[i]->SetFillColor(i+2);
    h_b_HHt_SGMC[i]->SetFillColor(i+2);
    h_b_WHdR_SGMC[i]->SetFillColor(i+2);

    h_b_n_SGMC[i]->SetFillColor(i+2);

    h_b_WpT_SGMC[i]->SetLineColor(i+2);
    h_b_Hmass_SGMC[i]->SetLineColor(i+2);
    h_b_HpT_SGMC[i]->SetLineColor(i+2);
    h_b_bbdRAve_SGMC[i]->SetLineColor(i+2);
    h_b_bbdMMin_SGMC[i]->SetLineColor(i+2);
    h_b_HHt_SGMC[i]->SetLineColor(i+2);
    h_b_WHdR_SGMC[i]->SetLineColor(i+2);

    h_b_n_SGMC[i]->SetLineColor(i+2);
    */
  }

  for( int i = 0 ; i < BGBin ; i++ )
  {
    std::string smalltag;

    if (i == 0) smalltag = "SingleT";
    else if (i == 1) smalltag = "TTJets";
    else if (i == 2) smalltag = "WJets";
    else if (i == 3) smalltag = "DY";
    else if (i == 4) smalltag = "TTGZW";
    else if (i == 5) smalltag = "VV";
    else if (i == 6) smalltag = "VVV";
    else if (i == 7) smalltag = "QCD";

    h_b_WpT_BGMC[i] = new TH1F( ("h_b_WpT_BGMC_" + smalltag).c_str(),"",200,0,2000);
    h_b_Hmass_BGMC[i] = new TH1F( ("h_b_Hmass_BGMC_" + smalltag).c_str(),"",500,0,5000);
    h_b_HpT_BGMC[i] = new TH1F( ("h_b_HpT_BGMC_" + smalltag).c_str(),"",200,0,2000);
    h_b_bbdRAve_BGMC[i] = new TH1F( ("h_b_bbdRAve_BGMC_" + smalltag).c_str(),"",500,0,5);
    h_b_bbdMMin_BGMC[i] = new TH1F( ("h_b_bbdMMin_BGMC_" + smalltag).c_str(),"",200,0,2000);
    h_b_HHt_BGMC[i] = new TH1F( ("h_b_HHt_BGMC_" + smalltag).c_str(),"",400,0,4000);
    h_b_WHdR_BGMC[i] = new TH1F( ("h_b_WHdR_BGMC_" + smalltag).c_str(),"",400,0,4);

    h_b_n_BGMC[i] = new TH1F( ("h_b_n_BGMC_" + smalltag).c_str(),"",60,0,60);

    h_b_WpT_BGMC[i]->SetFillColor(i+2);
    h_b_Hmass_BGMC[i]->SetFillColor(i+2);
    h_b_HpT_BGMC[i]->SetFillColor(i+2);
    h_b_bbdRAve_BGMC[i]->SetFillColor(i+2);
    h_b_bbdMMin_BGMC[i]->SetFillColor(i+2);
    h_b_HHt_BGMC[i]->SetFillColor(i+2);
    h_b_WHdR_BGMC[i]->SetFillColor(i+2);

    h_b_n_BGMC[i]->SetFillColor(i+2);

    h_b_WpT_BGMC[i]->SetLineColor(i+2);
    h_b_Hmass_BGMC[i]->SetLineColor(i+2);
    h_b_HpT_BGMC[i]->SetLineColor(i+2);
    h_b_bbdRAve_BGMC[i]->SetLineColor(i+2);
    h_b_bbdMMin_BGMC[i]->SetLineColor(i+2);
    h_b_HHt_BGMC[i]->SetLineColor(i+2);
    h_b_WHdR_BGMC[i]->SetLineColor(i+2);

    h_b_n_BGMC[i]->SetLineColor(i+2);
  }

  h_b_WpT_Data = new TH1F("h_b_WpT_Data","",200,0,2000);
  h_b_Hmass_Data = new TH1F("h_b_Hmass_Data","",500,0,5000);
  h_b_HpT_Data = new TH1F("h_b_HpT_Data","",200,0,2000);
  h_b_bbdRAve_Data = new TH1F("h_b_bbdRAve_Data","",500,0,5);
  h_b_bbdMMin_Data = new TH1F("h_b_bbdMMin_Data","",200,0,2000);
  h_b_HHt_Data = new TH1F("h_b_HHt_Data","",400,0,4000);
  h_b_WHdR_Data = new TH1F("h_b_WHdR_Data","",400,0,4);

  h_b_n_Data = new TH1F("h_b_n_Data","",60,0,60);

  return ;
}
