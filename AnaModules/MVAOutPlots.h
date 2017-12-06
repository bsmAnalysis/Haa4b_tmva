#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include <utility>      // std::pair, std::make_pair
#include <algorithm>    // std::copy

#include "TFile.h"
#include "TList.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TGraphErrors.h"

class MVAOutPlots
{
 public:
  std::string TrainMode;
  std::string target_DIR;

  TFile * fin;

  void Initialization(std::string trainmode, std::string dir); 
  void CorrPlots( std::string histtag );
  void ROCPlots();
  void BDTSBComparePlots( std::string histtag );
  void CVPlots();
};

void MVAOutPlots::Initialization(std::string trainmode, std::string dir)
{
  TrainMode = trainmode;
  target_DIR = dir;
  system( ("mkdir " + target_DIR).c_str() );

  //std::string din = "/afs/cern.ch/user/h/hua/workarea/Haa4b/TrainRes/20171116/"; //first version with negative weight and correct weight for BG
  //std::string din = "/afs/cern.ch/user/h/hua/workarea/Haa4b/TrainRes/20171121/"; // drop QCD 50To80, for both Train and Application
  std::string din = "/afs/cern.ch/user/h/hua/workarea/Haa4b/TrainRes/20171130/"; // balanced weight in signal samples
  std::cout << "Input Directory: " << din << std::endl;
  fin = TFile::Open( (din + "MVATrainTestOut" + TrainMode + ".root").c_str() );
}

void MVAOutPlots::CorrPlots( std::string histtag )
{
  TCanvas *c = new TCanvas("c","A Simple Graph Example",200,10,700,500);
  gStyle->SetOptStat(0);
  TH2F *corr = (TH2F*)fin->Get( ("dataset/CorrelationMatrix" + histtag).c_str() );
  corr->Draw("TEXT COLZ");
  c->SaveAs( target_DIR + TString("/") + TrainMode + histtag + TString("corr_MVAOut.png") );
  c->SaveAs( target_DIR + TString("/") + TrainMode + histtag + TString("corr_MVAOut.pdf") );
  c->SaveAs( target_DIR + TString("/") + TrainMode + histtag + TString("corr_MVAOut.C") );
  return ;
}

void MVAOutPlots::ROCPlots()
{
  TCanvas *c = new TCanvas("c","A Simple Graph Example",200,10,700,500);
  gStyle->SetOptStat(0);
  TH1D *ROC = (TH1D*)fin->Get("dataset/Method_BDT/BDT/MVA_BDT_rejBvsS");
  ROC->SetTitle( (TrainMode + " ROC").c_str() );
  ROC->Draw();
  c->SaveAs( target_DIR + TString("/") + TrainMode + TString("ROC_MVAOut.png") );
  c->SaveAs( target_DIR + TString("/") + TrainMode + TString("ROC_MVAOut.pdf") );
  c->SaveAs( target_DIR + TString("/") + TrainMode + TString("ROC_MVAOut.C") );
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

void MVAOutPlots::CVPlots()
{
  const int n = 5;
  float x[n] = {1,2,3,4,5}, y[n] = {0,0,0,0,0};
  float cv_eval_trib[n] = {0.8937, 0.8909, 0.8905, 0.8913, 0.8905}, cv_eval_quab[n] = {0.8889, 0.8910, 0.8946, 0.8875, 0.8965};
  float ex[n] = {0,0,0,0,0}, ey[n] = {0,0,0,0,0};
  float cv_err_trib[n] = {0.0013, 0.0013, 0.0013, 0.0013, 0.0013}, cv_err_quab[n] = {0.0038, 0.0038, 0.0038, 0.0038, 0.0038};
  if      ( TrainMode == "TribMVA" ){ std::copy(std::begin(cv_eval_trib), std::end(cv_eval_trib), std::begin(y)); std::copy(std::begin(cv_err_trib), std::end(cv_err_trib), std::begin(ey)); }
  else if ( TrainMode == "QuabMVA" ){ std::copy(std::begin(cv_eval_quab), std::end(cv_eval_quab), std::begin(y)); std::copy(std::begin(cv_err_quab), std::end(cv_err_quab), std::begin(ey)); }

  TCanvas *c = new TCanvas("c","",200,10,700,500);
  gStyle->SetOptStat(0);
  TGraphErrors *gr = new TGraphErrors(n,x,y,ex,ey);
  gr->SetLineColor(2);
  gr->SetLineWidth(4);
  gr->SetMarkerColor(4);
  gr->SetMarkerStyle(21);
  gr->SetTitle( (TrainMode + " CV").c_str() );
  gr->GetXaxis()->SetTitle("Cross Validation Fold");
  gr->GetYaxis()->SetTitle("ROC-Int");
  gr->GetYaxis()->SetRangeUser(0.85, 0.95);
  gr->Draw("ACP");
  c->SaveAs( target_DIR + TString("/") + TrainMode + TString("CV_MVAOut.png") );
  c->SaveAs( target_DIR + TString("/") + TrainMode + TString("CV_MVAOut.pdf") );
  c->SaveAs( target_DIR + TString("/") + TrainMode + TString("CV_MVAOut.C") );
  return ;
}
