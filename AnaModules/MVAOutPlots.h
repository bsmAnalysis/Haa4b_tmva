#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include <utility>      // std::pair, std::make_pair

#include "TFile.h"
#include "TList.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"


TH1D* merge_hist_list(const TList& hists)
{
  TIter next(hists.MakeIterator());
  TH1D* hist = NULL;
  TH1D* res = NULL;
  int icount = 0;
  while ((hist = (TH1D*) next()))
  {
    if(icount == 0)
    {
      res = (TH1D*) hist->Clone("my_all");
      icount++;
    }
    else
    {
      res->Add(hist);
    }
  }
  return res;
}

TH1D* merge_stack(const THStack& stack)
{
  TList* hists = stack.GetHists();
  return merge_hist_list(*hists);
}

class MVAOutPlots
{
 public:
  std::string TrainMode;
  std::string target_DIR;

  TFile * fin;
  TList * list;

  std::string lumi_str;  

  double scale = 1;

  void Initialization(std::string trainmode, std::string dir); 
  void SensitivityMap( int bit );
};

void MVAOutPlots::Initialization(std::string trainmode, std::string dir)
{
  TrainMode = trainmode;
  target_DIR = dir;
  system( ("mkdir " + target_DIR).c_str() );

  std::string din = "/afs/cern.ch/user/h/hua/workarea/Haa4b/TrainRes/20171116/";
  fin = TFile::Open( (din + "MVATrainTestOut" + TrainMode + ".root").c_str() );

  //fin = TFile::Open("OutDir/MVACutFlowTribMVA.root");
  //fin = TFile::Open("OutDir/MVACutFlowQuabMVA.root");

  list = fin->GetListOfKeys();
}

void MVAOutPlots::SensitivityMap( int bit )
{
  TCanvas *c = new TCanvas("c","A Simple Graph Example",200,10,700,500);
  gStyle->SetOptStat(0);

  //TH2F *corrSG = (TH2F*)fin->Get("dataset/CorrelationMatrixS");
  //corrSG->Draw("TEXT COLZ");

  //TH2F *corrBG = (TH2F*)fin->Get("dataset/CorrelationMatrixB");
  //corrBG->Draw("TEXT COLZ");

  //TH1D *ROC = (TH1D*)fin->Get("dataset/Method_BDT/BDT/MVA_BDT_rejBvsS");
  //ROC->SetTitle("Trib ROC");
  //ROC->SetTitle("Quab ROC");
  //ROC->Draw();

  //TH1D *sgBDT = (TH1D*)fin->Get("dataset/Method_BDT/BDT/MVA_BDT_S");
  //TH1D *bgBDT = (TH1D*)fin->Get("dataset/Method_BDT/BDT/MVA_BDT_B");

  TH1D *sgBDT = (TH1D*)fin->Get("dataset/Method_BDT/BDT/MVA_BDT_effS");
  TH1D *bgBDT = (TH1D*)fin->Get("dataset/Method_BDT/BDT/MVA_BDT_effB");

  sgBDT->SetLineColor(1); bgBDT->SetLineColor(2);
  sgBDT->SetMarkerColor(1); bgBDT->SetMarkerColor(2);
  sgBDT->SetMarkerStyle(20); bgBDT->SetMarkerStyle(21);

  //sgBDT->SetTitle("Triple b-jets BDT");
  //bgBDT->SetTitle("Triple b-jets BDT");
  //sgBDT->SetTitle("Quadruple b-jets BDT");
  //bgBDT->SetTitle("Quadruple b-jets BDT");

  //sgBDT->SetTitle("Triple b-jets Eff");
  //bgBDT->SetTitle("Triple b-jets Eff");
  sgBDT->SetTitle("Quadruple b-jets Eff");
  bgBDT->SetTitle("Quadruple b-jets Eff");
  
  sgBDT->Draw();
  bgBDT->Draw("same");

  TLegend* leg = new TLegend(0.75,0.75,0.90,0.90);
  leg->SetBorderSize(1);
  leg->SetLineColor(1);
  leg->SetLineWidth(2);
  leg->SetFillColor(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);    
  leg->AddEntry(sgBDT,"Signal"); 
  leg->AddEntry(bgBDT,"Background");
  leg->Draw("same");

  c->SaveAs( target_DIR + TString("/") + TrainMode + TString("_MVAOut.png") );
  c->SaveAs( target_DIR + TString("/") + TrainMode + TString("_MVAOut.pdf") );
  c->SaveAs( target_DIR + TString("/") + TrainMode + TString("_MVAOut.C") );
}
