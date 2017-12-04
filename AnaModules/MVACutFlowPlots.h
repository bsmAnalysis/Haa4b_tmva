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

class MVACutFlowPlots
{
 private:
  float GetBGMCStatUnc( const THStack& stack, int bin );

 public:
  std::string TrainMode;
  std::string target_DIR;

  TFile * fin;
  TList * list;

  std::string lumi_str;  

  double scale = 1;

  void Initialization(std::string trainmode, std::string dir); 
  void PrintPlotsName();
  void BasicCheckTemplate(
                          TString hist_tag,
                          TString XTitle,
                          double min, double max,
                          bool sgMC, bool bgMC, bool Data
                         );
  void SensitivityMap( int bit );
};

float MVACutFlowPlots::GetBGMCStatUnc( const THStack& stack, int bin )
{
  TList* hists = stack.GetHists();
  TIter next(hists->MakeIterator());
  TH1F* hist = NULL;
  float StatUnc = 0;
  while ((hist = (TH1F*) next()))
  {
    float thisStatUnc = hist->GetBinError( bin );
    //std::cout << thisStatUnc << std::endl;
    StatUnc += thisStatUnc * thisStatUnc;
  }
  return std::sqrt(StatUnc);
}

void MVACutFlowPlots::Initialization(std::string trainmode, std::string dir)
{
  TrainMode = trainmode;
  target_DIR = dir;
  system( ("mkdir " + target_DIR).c_str() );

  fin = TFile::Open( ("OutDir/MVACutFlow" + TrainMode + ".root").c_str() );

  //fin = TFile::Open("OutDir/MVACutFlowTribMVA.root");
  //fin = TFile::Open("OutDir/MVACutFlowQuabMVA.root");

  list = fin->GetListOfKeys();

  //convert lumi from double pb-1 to string, fb-1
  std::ostringstream strs;
  strs << (4000/1000);
  lumi_str = strs.str();
}

void MVACutFlowPlots::PrintPlotsName()
{
  for(int i  = 0 ; i < list->GetSize() ; i++)
  {
    std::cout<<"Name: "<< list->At(i)->GetName() << "("<< i <<")"<<std::endl;
  }
  
  return ;
}

void MVACutFlowPlots::BasicCheckTemplate(
                                         TString hist_tag,
                                         TString XTitle,
                                         double min, double max,
                                         bool sgMC, bool bgMC, bool Data
                                        )
{ 
  TH1D * h_Data;
  TH1D * h_signal_loMa, * h_signal_hiMa;
  THStack * hs_MC = new THStack("hs_MC","");

  TLegend* leg = new TLegend(0.6,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);

  std::string smalltag;
  int NHist = list->GetSize();

  for(int i  = 0 ; i < NHist ; i++)
  {
    if( TString(list->At(i)->GetName()).Contains( hist_tag ) )
    {
      if( TString(list->At(i)->GetName()).Contains( "_Data" ) )
      {
        h_Data = (TH1D*)fin->Get(list->At(i)->GetName())->Clone();
        smalltag = "Data"; 
        leg->AddEntry( (TH1D*)fin->Get(list->At(i)->GetName()), smalltag.c_str(), "l");
      }
      else if( TString(list->At(i)->GetName()).Contains( "_SGMC_Wh20" ) )
      {
        h_signal_loMa = (TH1D*)fin->Get(list->At(i)->GetName())->Clone();
        smalltag = "Wh(20)";
        leg->AddEntry( (TH1D*)fin->Get(list->At(i)->GetName()), smalltag.c_str(), "l");
      }
      else if( TString(list->At(i)->GetName()).Contains( "_SGMC_Wh50" ) )
      {
        h_signal_hiMa = (TH1D*)fin->Get(list->At(i)->GetName())->Clone();
        smalltag = "Wh(50)";
        leg->AddEntry( (TH1D*)fin->Get(list->At(i)->GetName()), smalltag.c_str(), "l");
      }
    }
    if( TString(list->At(i)->GetName()).Contains( hist_tag ) )
    {
      if( TString(list->At(i)->GetName()).Contains( "_BGMC" ) )
      {
        hs_MC->Add( (TH1D*)fin->Get(list->At(i)->GetName()) );
        //std::cout << TString(list->At(i)->GetName()) << std::endl;
        if( TString(list->At(i)->GetName()).Contains( "SingleT" ) ) { smalltag = "SingleT"; leg->AddEntry( (TH1D*)fin->Get(list->At(i)->GetName()), smalltag.c_str(), "f"); }
        if( TString(list->At(i)->GetName()).Contains( "TTJets" ) ) { smalltag = "TTJets"; leg->AddEntry( (TH1D*)fin->Get(list->At(i)->GetName()), smalltag.c_str(), "f"); }
        if( TString(list->At(i)->GetName()).Contains( "WJets" ) ) { smalltag = "WJets"; leg->AddEntry( (TH1D*)fin->Get(list->At(i)->GetName()), smalltag.c_str(), "f"); }
        if( TString(list->At(i)->GetName()).Contains( "DY" ) ) { smalltag = "DY"; leg->AddEntry( (TH1D*)fin->Get(list->At(i)->GetName()), smalltag.c_str(), "f"); }
        if( TString(list->At(i)->GetName()).Contains( "TTGZW" ) ) { smalltag = "TTGZW"; leg->AddEntry( (TH1D*)fin->Get(list->At(i)->GetName()), smalltag.c_str(), "f"); }
        if( TString(list->At(i)->GetName()).Contains( "DiBoson" ) ) { smalltag = "DiBoson"; leg->AddEntry( (TH1D*)fin->Get(list->At(i)->GetName()), smalltag.c_str(), "f"); }
        if( TString(list->At(i)->GetName()).Contains( "TriBoson" ) ) { smalltag = "TriBoson"; leg->AddEntry( (TH1D*)fin->Get(list->At(i)->GetName()), smalltag.c_str(), "f"); }
        if( TString(list->At(i)->GetName()).Contains( "QCD" ) ) { smalltag = "QCD"; leg->AddEntry( (TH1D*)fin->Get(list->At(i)->GetName()), smalltag.c_str(), "f"); }
      }
    }
    else
      continue;
  }

  TCanvas *c = new TCanvas("c","A Simple Graph Example",200,10,700,500); 
  gStyle->SetOptStat(0);
  if ( !sgMC && bgMC && !Data )
  {
    c->SetLogy();
    //hs_MC->GetXaxis()->SetLimits(min, max);
    //hs_MC->GetXaxis()->SetRangeUser(min,max);
    //hs_MC->GetXaxis()->SetTitle(XTitle);
    //hs_MC->Draw("text hist");
    hs_MC->SetMaximum(100000); hs_MC->SetMinimum(0.001);
    hs_MC->SetTitle( hist_tag + TrainMode );
    hs_MC->Draw("nostackb hist");
    leg->Draw("same");
    c->SaveAs( target_DIR + TString("/") + hist_tag + TrainMode + TString("_BasicCheck.png") );
    c->SaveAs( target_DIR + TString("/") + hist_tag + TrainMode + TString("_BasicCheck.pdf") );
    c->SaveAs( target_DIR + TString("/") + hist_tag + TrainMode + TString("_BasicCheck.C") );
    return ;
  }

  TPad *pad = (TPad*) c->GetPad(0); 
  pad->Clear();
  pad->Divide(2, 1);

  double divRatio = 0.20;
  double labelRatio = (1-divRatio)/divRatio;
  double small = 0;

  pad->cd(1); 
  TPad *pad1 = (TPad*) pad->GetPad(1);
  pad1->SetPad("", "", 0, divRatio, 1.0, 1.0, kWhite);
  pad1->SetBottomMargin(0.005);
  pad1->SetBorderMode(0);

  h_Data->GetXaxis()->SetRangeUser(min,max);
  h_Data->GetXaxis()->SetTitle(XTitle);
  h_Data->SetLineColor(1);
  h_Data->SetLineWidth(3);
  h_Data->Sumw2();
  h_Data->Scale(scale);

  //hs_MC->GetXaxis()->SetLimits(min, max);
  //hs_MC->GetXaxis()->SetRangeUser(min,max);
  //hs_MC->GetXaxis()->SetTitle(XTitle);
  //hs_MC->SetLineColor(2);
  //hs_MC->SetLineWidth(3);
  //hs_MC->Sumw2();
  //hs_MC->Scale(scale);
  h_signal_loMa->Scale(100);  
  h_signal_hiMa->Scale(100);  

  h_Data->Draw("e0");
  hs_MC->Draw("same hist");
  h_Data->Draw("same e0");
  h_signal_loMa->Draw("same e0");
  h_signal_hiMa->Draw("same e0");

  //hs_MC->Draw("hist");
  //h_Data->Draw("same e0");

  //const std::string titre="CMS Preliminary 2015, "+ lumi_str + " fb^{-1}, #sqrt{s} = 13 TeV";
  const std::string titre="CMS Preliminary 2017, 35.9 fb^{-1}, #sqrt{s} = 13 TeV";
  TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  title->SetNDC();
  title->SetTextSize(0.045);
  title->Draw("same");
  
  leg->Draw("same");

  c->Update(); 
 
  pad->cd(2); 
  TPad *pad2 = (TPad*) pad->GetPad(2);
  pad2->SetPad("ratio", "", 0, 0, 1.0, divRatio, kWhite);
  pad2->SetBottomMargin(0.3);
  pad2->SetTopMargin(small);
  pad2->SetBorderMode(0);

  TH1D *h_MC_all = merge_stack( *hs_MC );
  TH1D *ratio = (TH1D*) h_Data->Clone();
  TH1D *allmc = (TH1D*) h_MC_all->Clone();

  ratio->Add(allmc, -1);
  ratio->Divide(allmc);
  ratio->GetYaxis()->SetTitle( "(Data-MC)/MC" );

  TAxis* xHT = ratio->GetXaxis();

  xHT->SetTickLength(xHT->GetTickLength()*labelRatio);
  xHT->SetLabelSize(xHT->GetLabelSize()*labelRatio);
  xHT->SetLabelOffset(xHT->GetLabelOffset()*labelRatio);
  ratio->SetMinimum(-1.0);
  ratio->SetMaximum(1.0);

  TAxis* yHT = ratio->GetYaxis();
  yHT->SetNdivisions(010);
  yHT->SetLabelSize(yHT->GetLabelSize()*2.0);
  yHT->SetTitleOffset(0.3);
  yHT->SetTitleSize(0.08);

  ratio->SetTitleSize(0.15);
  ratio->SetStats(kFALSE);
  ratio->SetMarkerStyle(kFullDotMedium);
  //ratio->Sumw2();
  ratio->DrawCopy();

  TH1D *zero = (TH1D*)ratio->Clone(); 
  zero->Reset();
  for(int ib=0; ib<ratio->GetNbinsX(); ib++){ zero->SetBinContent(ib+1, 0); }
  zero->SetLineColor(kRed); zero->SetLineWidth(1);
  zero->DrawCopy("same");

  c->SaveAs( target_DIR + TString("/") + hist_tag + TrainMode + TString("_BasicCheck.png") );
  c->SaveAs( target_DIR + TString("/") + hist_tag + TrainMode + TString("_BasicCheck.pdf") );
  c->SaveAs( target_DIR + TString("/") + hist_tag + TrainMode + TString("_BasicCheck.C") );
}

void MVACutFlowPlots::SensitivityMap( int bit )
{
  std::vector< std::pair<std::string, TH1D*> > SGHistsVec;
  THStack * hs_MC = new THStack("hs_MC","");

  std::string smalltag;
  int NHist = list->GetSize();

  for(int i  = 0 ; i < NHist ; i++)
  {
    if( TString(list->At(i)->GetName()).Contains( "_n_" ) )
    {
      if     ( TString(list->At(i)->GetName()).Contains( "_SGMC_Wh12" ) )
      { 
        SGHistsVec.push_back( std::make_pair( std::string("Wh(12)" ), (TH1D*)fin->Get(list->At(i)->GetName())->Clone() ) );
      }
      else if( TString(list->At(i)->GetName()).Contains( "_SGMC_Wh15" ) )
      { 
        SGHistsVec.push_back( std::make_pair( std::string("Wh(20)" ), (TH1D*)fin->Get(list->At(i)->GetName())->Clone() ) );
      }
      else if( TString(list->At(i)->GetName()).Contains( "_SGMC_Wh20" ) )
      {
        SGHistsVec.push_back( std::make_pair( std::string("Wh(20)" ), (TH1D*)fin->Get(list->At(i)->GetName())->Clone() ) );
      }
      else if( TString(list->At(i)->GetName()).Contains( "_SGMC_Wh25" ) )
      {
        SGHistsVec.push_back( std::make_pair( std::string("Wh(25)" ), (TH1D*)fin->Get(list->At(i)->GetName())->Clone() ) );
      }
      else if( TString(list->At(i)->GetName()).Contains( "_SGMC_Wh30" ) )
      {
        SGHistsVec.push_back( std::make_pair( std::string("Wh(30)" ), (TH1D*)fin->Get(list->At(i)->GetName())->Clone() ) );
      }
      else if( TString(list->At(i)->GetName()).Contains( "_SGMC_Wh40" ) )
      {
        SGHistsVec.push_back( std::make_pair( std::string("Wh(40)" ), (TH1D*)fin->Get(list->At(i)->GetName())->Clone() ) );
      }
      else if( TString(list->At(i)->GetName()).Contains( "_SGMC_Wh50" ) )
      {
        SGHistsVec.push_back( std::make_pair( std::string("Wh(50)" ), (TH1D*)fin->Get(list->At(i)->GetName())->Clone() ) );
      }
      else if( TString(list->At(i)->GetName()).Contains( "_SGMC_Wh60" ) )
      {
        SGHistsVec.push_back( std::make_pair( std::string("Wh(60)" ), (TH1D*)fin->Get(list->At(i)->GetName())->Clone() ) );
      }
    }
    if( TString(list->At(i)->GetName()).Contains( "_n_" ) )
    {
      if( TString(list->At(i)->GetName()).Contains( "_BGMC" ) )
      {
        hs_MC->Add( (TH1D*)fin->Get(list->At(i)->GetName()) );
      }
    }
    else
      continue;
  }

  std::vector<std::string> BitTagMapVec =
  {
    "nSG", //bit 0
    "nBG", //bit 1
    "SGStatUnc", //bit 2
    "BGStatUnc", //bit 3
    "naiveSS", //bit 4
    "nMCStatSS", //bit 5
    "10SG20BGSS", //bit 6
  };

  TCanvas *c = new TCanvas("c","A Simple Graph Example",200,10,700,500); 
  gStyle->SetOptStat(0);

  const static int nsigs = 8;
  const static int ncuts = 8;
  const char *sigschar[nsigs] = {"Wh12", "Wh15", "Wh20", "Wh25", "Wh30", "Wh40", "Wh50", "Wh60"};
  const char *cutschar[ncuts] = {"Cut0", "Cut1", "Cut2", "Cut3", "Cut4", "Cut5", "Cut6", "Cut7"};
  TH2D * SSScan = new TH2D("hSSScan", "", nsigs, 0, nsigs, ncuts, 0, ncuts);
  SSScan->SetTitle( (TrainMode + " " + BitTagMapVec.at(bit) + " Scan").c_str() );
  /*
  float sensitivity[nsigs][ncuts] = {{0}};
  float bg[ncuts] = {0};
  for ( int j = 1; j <= ncuts; j++ )
  {
    bg[j-1] = ((TH1*)(hs_MC->GetStack()->Last()))->GetBinContent(j);
    //float thisbg = ((TH1*)(hs_MC->GetStack()->Last()))->GetBinContent(j);
    std::cout << "BG sum: " << bg[j-1] << std::endl;
  }

  for ( int i = 1; i <= nsigs; i++ )
  {
    for ( int j = 1; j <= ncuts; j++ )
    {
      float thissg = (SGHistsVec.at(i-1).second)->GetBinContent(j);
      float thisbg = bg[j-1];
      //std::cout << SGHistsVec.at(i-1).first << "," << thissg << ", BG, "<< thisbg << ", Sensitivity: " << thissg / std::sqrt(thissg + thisbg) << std::endl;
      sensitivity[i-1][j-1] = thissg / std::sqrt(thissg + thisbg);
      std::cout << SGHistsVec.at(i-1).first << "," << thissg << ", BG, "<< thisbg << ", Sensitivity: " << sensitivity[i-1][j-1] << std::endl;
    }
  }
  */
  for ( int i = 1; i <= nsigs; i++ )
  {
    for ( int j = 1; j <= ncuts; j++ )
    {
      float thissg = (SGHistsVec.at(i-1).second)->GetBinContent(j);
      float thissgStatUnc = (SGHistsVec.at(i-1).second)->GetBinError(j);
      float thisbg = ((TH1*)(hs_MC->GetStack()->Last()))->GetBinContent(j);
      float thisbgStatUnc = GetBGMCStatUnc( *hs_MC, j );
      //std::cout << "bg: " << thisbg << ", bgStatUnc: " << thisbgStatUnc << std::endl;
      float thisss_1 = thissg / std::sqrt( thissg + thisbg );
      float thisss_2 = thissg / std::sqrt( std::pow(thisbgStatUnc, 2) );
      float thisss_3 = thissg / std::sqrt( thissg + thisbg + std::pow(0.1*thisbg, 2) + std::pow(0.2*thisbg, 2) ); // 10% syst unc on signal, 20% syst unc on bg
      if (thisbg <= 0) { thisss_1 = 0; thisss_2 = 0; thisss_3 = 0; }
      // plot for different bit
      if      ( bit == 0) SSScan->Fill( sigschar[i-1], cutschar[j-1], thissg );
      else if ( bit == 1) SSScan->Fill( sigschar[i-1], cutschar[j-1], thisbg );
      else if ( bit == 2) SSScan->Fill( sigschar[i-1], cutschar[j-1], thissgStatUnc/thissg );
      else if ( bit == 3) SSScan->Fill( sigschar[i-1], cutschar[j-1], thisbgStatUnc/thisbg );
      else if ( bit == 4) SSScan->Fill( sigschar[i-1], cutschar[j-1], thisss_1 );
      else if ( bit == 5) SSScan->Fill( sigschar[i-1], cutschar[j-1], thisss_2 );
      else if ( bit == 6) SSScan->Fill( sigschar[i-1], cutschar[j-1], thisss_3 );
      //SSScan->SetBinContent( i, j, thissg / std::sqrt(thissg + thisbg) );
      //std::cout << SGHistsVec.at(i-1).first << "," << thissg << ", BG, "<< thisbg << ", Sensitivity: " << thissg / std::sqrt(thissg + thisbg) << std::endl;
    }
  }

  SSScan->Draw("colz text");
  //const std::string titre="CMS Preliminary 2015, "+ lumi_str + " fb^{-1}, #sqrt{s} = 13 TeV";
  //const std::string titre="CMS Preliminary 2017, 35.9 fb^{-1}, #sqrt{s} = 13 TeV";
  //TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  //title->SetNDC();
  //title->SetTextSize(0.045);
  //title->Draw("same");
  
  c->SaveAs( target_DIR + TString("/") + TrainMode + BitTagMapVec.at(bit) + TString("_SSScan.png") );
  c->SaveAs( target_DIR + TString("/") + TrainMode + BitTagMapVec.at(bit) + TString("_SSScan.pdf") );
  c->SaveAs( target_DIR + TString("/") + TrainMode + BitTagMapVec.at(bit) + TString("_SSScan.C") );
}

struct Plotting_Parameter
{
  TString hist_tag;
  TString XTitle;
  double min;
  double max;
  bool sgMC; 
  bool bgMC; 
  bool Data;
};
