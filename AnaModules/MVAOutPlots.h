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
  void BDTSBComparePlots( std::string histtag, std::string histtagtrain );
  void CVPlots();
};

void MVAOutPlots::Initialization(std::string trainmode, std::string dir)
{
  TrainMode = trainmode;
  target_DIR = dir;
  system( ("mkdir " + target_DIR).c_str() );

  std::string din = "/afs/cern.ch/work/g/georgia/BSMAnalysis/CMSSW_9_2_14_patch1/src/UserCode/Haa4b_tmva/AnaModules/";      

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
  TH1D *ROCtr = (TH1D*)fin->Get("dataset/Method_BDT/BDT/MVA_BDT_trainingRejBvsS");   
  ROC->GetYaxis()->SetRangeUser(0, 1.2*ROC->GetMaximum());
  ROC->SetTitle( "ROC" );
  ROC->Draw();
  ROCtr->Draw("same"); ROCtr->SetLineColor(2);

  TLegend* leg = new TLegend(0.70,0.75,0.90,0.90);
  leg->SetBorderSize(1);
  leg->SetLineColor(1);
  leg->SetLineWidth(2);
  leg->SetFillColor(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);    
  leg->AddEntry(ROCtr,"Training sample"); 
  leg->AddEntry(ROC,"Test sample");  
  leg->Draw("same");

  c->SaveAs( target_DIR + TString("/") + TrainMode + TString("ROC_MVAOut.png") );
  c->SaveAs( target_DIR + TString("/") + TrainMode + TString("ROC_MVAOut.pdf") );
  c->SaveAs( target_DIR + TString("/") + TrainMode + TString("ROC_MVAOut.C") );
  return ;
}

void MVAOutPlots::BDTSBComparePlots( std::string histtag, std::string histtagtrain )
{
  TCanvas *c = new TCanvas("c","A Simple Graph Example",200,10,700,500);
  gStyle->SetOptStat(0);

  // test sample
  TH1D *sgBDT = (TH1D*)fin->Get( ("dataset/Method_BDT/BDT/" + histtag + "S").c_str() ); sgBDT->Rebin(2);
  TH1D *bgBDT = (TH1D*)fin->Get( ("dataset/Method_BDT/BDT/" + histtag + "B").c_str() ); bgBDT->Rebin(2);
  // training sample
  TH1D *sgBDTtr = (TH1D*)fin->Get( ("dataset/Method_BDT/BDT/" + histtagtrain + "S").c_str() );  sgBDTtr->Rebin(2);
  TH1D *bgBDTtr = (TH1D*)fin->Get( ("dataset/Method_BDT/BDT/" + histtagtrain + "B").c_str() );  bgBDTtr->Rebin(2);

  sgBDT->SetLineColor(4); bgBDT->SetLineColor(1);
  sgBDT->SetMarkerColor(4); bgBDT->SetMarkerColor(1);
  sgBDT->SetMarkerStyle(20); bgBDT->SetMarkerStyle(21);

  sgBDTtr->SetLineColor(4); bgBDTtr->SetLineColor(1);
  if (!(histtag.find("eff")!=std::string::npos)) {
    sgBDTtr->SetFillColor(4); bgBDTtr->SetFillColor(1);     
    sgBDTtr->SetFillStyle(3001); bgBDTtr->SetFillStyle(3001);
  } else {
    sgBDT->SetMarkerSize(0.1); bgBDT->SetMarkerSize(0.1);      
    sgBDTtr->SetLineStyle(2); bgBDTtr->SetLineStyle(2); 
  }
  sgBDT->SetTitle( (histtag).c_str() );
  //  bgBDT->SetTitle( (TrainMode + "_" + histtag).c_str() );
  
  sgBDT->Draw("p"); sgBDTtr->Draw("histsame");
  bgBDT->Draw("psame"); bgBDTtr->Draw("histsame");   

  sgBDT->GetYaxis()->SetRangeUser(0.,1.5*sgBDT->GetMaximum());
  sgBDT->GetXaxis()->SetTitle("MVA BDT");

  TLegend* leg = new TLegend(0.54,0.70,0.90,0.90);
  leg->SetBorderSize(1);
  leg->SetLineColor(1);
  leg->SetLineWidth(2);
  leg->SetFillColor(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);    
  leg->AddEntry(sgBDTtr,"Signal (training sample)"); 
  leg->AddEntry(sgBDT,"Signal (test sample)");  
  leg->AddEntry(bgBDTtr,"Background (training sample)");
  leg->AddEntry(bgBDT,"Background (test sample)"); 
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
  else if ( TrainMode == "H4bMVA" ){ std::copy(std::begin(cv_eval_trib), std::end(cv_eval_trib), std::begin(y)); std::copy(std::begin(cv_err_trib), std::end(cv_err_trib), std::begin(ey)); }     

  TCanvas *c = new TCanvas("c","",200,10,700,500);
  gStyle->SetOptStat(0);
  TGraphErrors *gr = new TGraphErrors(n,x,y,ex,ey);
  gr->SetLineColor(2);
  gr->SetLineWidth(4);
  gr->SetMarkerColor(4);
  gr->SetMarkerStyle(21);
  gr->SetTitle( " CV" );
  gr->GetXaxis()->SetTitle("Cross Validation Fold");
  gr->GetYaxis()->SetTitle("ROC-Int");
  gr->GetYaxis()->SetRangeUser(0.85, 0.95);
  gr->Draw("ACP");
  c->SaveAs( target_DIR + TString("/") + TrainMode + TString("CV_MVAOut.png") );
  c->SaveAs( target_DIR + TString("/") + TrainMode + TString("CV_MVAOut.pdf") );
  c->SaveAs( target_DIR + TString("/") + TrainMode + TString("CV_MVAOut.C") );
  return ;
}
