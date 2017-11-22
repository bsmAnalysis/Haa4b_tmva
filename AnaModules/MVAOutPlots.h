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
#include "TH2F.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"

class MVAOutPlots
{
 public:
  std::string TrainMode;
  std::string target_DIR;

  TFile * fin;

  void Initialization(std::string trainmode, std::string dir); 
  void CorrPlots();
  void ROCPlots();
  void BDTSBComparePlots( std::string histtag );
};

void MVAOutPlots::Initialization(std::string trainmode, std::string dir)
{
  TrainMode = trainmode;
  target_DIR = dir;
  system( ("mkdir " + target_DIR).c_str() );

  std::string din = "/afs/cern.ch/user/h/hua/workarea/Haa4b/TrainRes/20171116/";
  fin = TFile::Open( (din + "MVATrainTestOut" + TrainMode + ".root").c_str() );
}

void MVAOutPlots::CorrPlots()
{
  //TH2F *corrSG = (TH2F*)fin->Get("dataset/CorrelationMatrixS");
  //corrSG->Draw("TEXT COLZ");

  //TH2F *corrBG = (TH2F*)fin->Get("dataset/CorrelationMatrixB");
  //corrBG->Draw("TEXT COLZ");
  return ;
}

void MVAOutPlots::ROCPlots()
{
  //TH1D *ROC = (TH1D*)fin->Get("dataset/Method_BDT/BDT/MVA_BDT_rejBvsS");
  //ROC->SetTitle("Trib ROC");
  //ROC->SetTitle("Quab ROC");
  //ROC->Draw();
  return ;
}

void MVAOutPlots::BDTSBComparePlots( std::string histtag )
{
  TCanvas *c = new TCanvas("c","A Simple Graph Example",200,10,700,500);
  gStyle->SetOptStat(0);

  TH1D *sgBDT = (TH1D*)fin->Get( ("dataset/Method_BDT/BDT/" + histtag + "S").c_str() );
  TH1D *bgBDT = (TH1D*)fin->Get( ("dataset/Method_BDT/BDT/" + histtag + "B").c_str() );

  sgBDT->SetLineColor(1); bgBDT->SetLineColor(2);
  sgBDT->SetMarkerColor(1); bgBDT->SetMarkerColor(2);
  sgBDT->SetMarkerStyle(20); bgBDT->SetMarkerStyle(21);

  sgBDT->SetTitle( (TrainMode + "_" + histtag).c_str() );
  bgBDT->SetTitle( (TrainMode + "_" + histtag).c_str() );
  
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

  c->SaveAs( target_DIR + TString("/") + TrainMode + histtag + TString("_MVAOut.png") );
  c->SaveAs( target_DIR + TString("/") + TrainMode + histtag + TString("_MVAOut.pdf") );
  c->SaveAs( target_DIR + TString("/") + TrainMode + histtag + TString("_MVAOut.C") );
  return ;
}
