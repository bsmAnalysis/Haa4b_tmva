#include "TROOT.h"
#include "TMath.h"
#include "TTree.h"
#include "TArrayD.h"
#include "TStyle.h"
#include "TFile.h"
#include "TRandom.h"
#include "Riostream.h"
#include "TCanvas.h"
#include "TMatrixD.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TBranch.h"
#include <vector>
void plot( TString fname = "data.root", TString var0="var0", TString var1="var1" )
{
  TFile* dataFile = TFile::Open( fname );
  if (!dataFile) {
    cout << "ERROR: cannot open file: " << fname << endl;
    return;
  }
  TTree *treeS = (TTree*)dataFile->Get("TreeS");
  TTree *treeB = (TTree*)dataFile->Get("TreeB");
  TCanvas* c = new TCanvas( "c", "", 0, 0, 550, 550 );
  TStyle *TMVAStyle = gROOT->GetStyle("Plain"); // our style is based on Plain
  TMVAStyle->SetOptStat(0);
  TMVAStyle->SetPadTopMargin(0.02);
  TMVAStyle->SetPadBottomMargin(0.16);
  TMVAStyle->SetPadRightMargin(0.03);
  TMVAStyle->SetPadLeftMargin(0.15);
  TMVAStyle->SetPadGridX(0);
  TMVAStyle->SetPadGridY(0);
  TMVAStyle->SetOptTitle(0);
  TMVAStyle->SetTitleW(.4);
  TMVAStyle->SetTitleH(.10);
  TMVAStyle->SetTitleX(.5);
  TMVAStyle->SetTitleY(.9);
  TMVAStyle->SetMarkerStyle(20);
  TMVAStyle->SetMarkerSize(1.6);
  TMVAStyle->cd();
  Float_t xmin = TMath::Min( treeS->GetMinimum( var0 ), treeB->GetMinimum( var0 ) );
  Float_t xmax = TMath::Max( treeS->GetMaximum( var0 ), treeB->GetMaximum( var0 ) );
  Float_t ymin = TMath::Min( treeS->GetMinimum( var1 ), treeB->GetMinimum( var1 ) );
  Float_t ymax = TMath::Max( treeS->GetMaximum( var1 ), treeB->GetMaximum( var1 ) );
  Int_t nbin = 500;
  TH2F* frameS = new TH2F( "DataS", "DataS", nbin, xmin, xmax, nbin, ymin, ymax );
  TH2F* frameB = new TH2F( "DataB", "DataB", nbin, xmin, xmax, nbin, ymin, ymax );
  // project trees
  treeS->Draw( Form("%s:%s>>DataS",var1.Data(),var0.Data()), "", "0" );
  treeB->Draw( Form("%s:%s>>DataB",var1.Data(),var0.Data()
		    ), "", "0" );
  // set style
  frameS->SetMarkerSize( 0.1 );
  frameS->SetMarkerColor( 4 );
  frameB->SetMarkerSize( 0.1 );
  frameB->SetMarkerColor( 2 );
  // legend
  frameS->SetTitle( var1+" versus "+var0+" for signal and background" );
  frameS->GetXaxis()->SetTitle( var0 );
  frameS->GetYaxis()->SetTitle( var1 );
  frameS->SetLabelSize( 0.04, "X" );
  frameS->SetLabelSize( 0.04, "Y" );
  frameS->SetTitleSize( 0.05, "X" );
  frameS->SetTitleSize( 0.05, "Y" );
  // and plot
  frameS->Draw();
  frameB->Draw( "same" );
  // Draw legend
  TLegend *legend = new TLegend( 1 - c->GetRightMargin() - 0.32, 1 - c->GetTopMargin() - 0.12,
				 1 - c->GetRightMargin(), 1 - c->GetTopMargin() );
  legend->SetFillStyle( 1 );
  legend->AddEntry(frameS,"Signal","p");
  legend->AddEntry(frameB,"Background","p");
  legend->Draw("same");
  legend->SetBorderSize(1);
  legend->SetMargin( 0.3 );
}
TMatrixD* produceSqrtMat( const TMatrixD& covMat )
{
  Double_t sum = 0;
  Int_t size = covMat.GetNrows();;
  TMatrixD* sqrtMat = new TMatrixD( size, size );
  for (Int_t i=0; i< size; i++) {
    sum = 0;
    for (Int_t j=0;j< i; j++) sum += (*sqrtMat)(i,j) * (*sqrtMat)(i,j);
    (*sqrtMat)(i,i) = TMath::Sqrt(TMath::Abs(covMat(i,i) - sum));
    for (Int_t k=i+1 ;k<size; k++) {
      sum = 0;
      for (Int_t l=0; l<i; l++) sum += (*sqrtMat)(k,l) * (*sqrtMat)(i,l);
      (*sqrtMat)(k,i) = (covMat(k,i) - sum) / (*sqrtMat)(i,i);
    }
  }
  return sqrtMat;
}
void getGaussRnd( TArrayD& v, const TMatrixD& sqrtMat, TRandom& R )
{
  // generate "size" correlated Gaussian random numbers
  // sanity check
  const Int_t size = sqrtMat.GetNrows();
  if (size != v.GetSize())
    cout << "<getGaussRnd> too short input vector: " << size << " " << v.GetSize() << endl;
  Double_t* tmpVec = new Double_t[size];
  for (Int_t i=0; i<size; i++) {
    Double_t x, y, z;
    y = R.Rndm();
    z = R.Rndm();
    x = 2*TMath::Pi()*z;
    tmpVec[i] = TMath::Sin(x) * TMath::Sqrt(-2.0*TMath::Log(y));
  }
  for (Int_t i=0; i<size; i++) {
    v[i] = 0;
    for (Int_t j=0; j<=i; j++) v[i] += sqrtMat(i,j) * tmpVec[j];
  }
  delete[] tmpVec;
}
// create the data
void create_lin_Nvar_withFriend(Int_t N = 2000)
{
  const Int_t nvar  = 4;
  const Int_t nvar2 = 1;
  Float_t xvar[nvar];
  // output flie
  TFile* dataFile = TFile::Open( "data.root", "RECREATE" );
  // create signal and background trees
  TTree* treeS = new TTree( "TreeS", "TreeS", 1 );
  TTree* treeB = new TTree( "TreeB", "TreeB", 1 );
  for (Int_t ivar=0; ivar<nvar-nvar2; ivar++) {
    cout << "Creating branch var" << ivar+1 << " in signal tree" << endl;
    treeS->Branch( TString(Form( "var%i", ivar+1 )).Data(), &xvar[ivar], TString(Form( "var%i/F", ivar+1 )).Data() );
    treeB->Branch( TString(Form( "var%i", ivar+1 )).Data(), &xvar[ivar], TString(Form( "var%i/F", ivar+1 )).Data() );
  }
  TTree* treeSF = new TTree( "TreeSF", "TreeS", 1 );
  TTree* treeBF = new TTree( "TreeBF", "TreeB", 1 );
  for (Int_t ivar=nvar-nvar2; ivar<nvar; ivar++) {
    treeSF->Branch( TString(Form( "var%i", ivar+1 )).Data(), &xvar[ivar], TString(Form( "var%i/F", ivar+1 )).Data() );
    treeBF->Branch( TString(Form( "var%i", ivar+1 )).Data(), &xvar[ivar], TString(Form( "var%i/F", ivar+1 )).Data() );
  }
  TRandom R( 100 );
  Float_t xS[nvar] = {  0.2,  0.3,  0.5,  0.9 };
  Float_t xB[nvar] = { -0.2, -0.3, -0.5, -0.6 };
  Float_t dx[nvar] = {  1.0,  1.0, 1.0, 1.0 };
  TArrayD* v = new TArrayD( nvar );
  Float_t rho[20];
  rho[1*2] = 0.4;
  rho[1*3] = 0.6;
  rho[1*4] = 0.9;
  rho[2*3] = 0.7;
  rho[2*4] = 0.8;
  rho[3*4] = 0.93;
  // create covariance matrix
  TMatrixD* covMatS = new TMatrixD( nvar, nvar );
  TMatrixD* covMatB = new TMatrixD( nvar, nvar );
  for (Int_t ivar=0; ivar<nvar; ivar++) {
    (*covMatS)(ivar,ivar) = dx[ivar]*dx[ivar];
    (*covMatB)(ivar,ivar) = dx[ivar]*dx[ivar];
    for (Int_t jvar=ivar+ivar]*dx[jvar];
    (*covMatB)(jvar,ivar) = (*covMatB)(ivar,jvar);
  }
}
cout << "signal covariance matrix: " << endl;
covMatS->Print();
cout << "background covariance matri
         treeF->Fill();
      }
   }
//    treeS->AddFriend(treeSF);
//    treeB->AddFriend(treeBF);
   // write trees
   treeS->Write();
   treeB->Write();
   treeSF->Write();
   treeBF->Write();
   treeS->Show(0);
   treeB->Show(1);
   dataFile->Close();
   cout << "<nvar; ivar++) {
     (*covMat)(ivar,ivar) = dx[ivar]*dx[ivar];
     for (Int_t jvar=ivar+1; jvar<nvar; jvar++) {
       (*covMat)(ivar,jvar) = rho[(ivar+1)*(jvar+1)]*dx[ivar]*dx[jvar];
       (*covMat)(jvar,ivar) = (*covMat)(ivar,jvar);
     }
			   }
//cout <<y size does not work in interactive mode
// create signal and background trees
TTree* tree = new TTree( treeName, treeTitle, 1 );
for (Int_t ivar=0; ivar<nvar; ivar++) {
  tree->Branch( TString(Form( "var%i", ivar+1 )).Data(), &xvar[ivar], TString(Fovar[j] = dfn*R.Rndm()+fnmin;
									      tree->Fill();
									      }
		for (Int_t i=0; i<Nn; i++) {
		  xvar[0] = dfn*R.Rndm()+fnmin;
		  xvar[1] = dfn*R.Rndm()+fnmin;
		  for( Int_t j = 2; j<nvar; ++j )
		    xvar[j] = dfn*R.Rndm()+fnmin;
		  tree->Fill();
		}
		tree->Show(0);
		// write trees
		cout << "created tree:e->GetName() << endl;
}
// create the data
void create_lin_Nvar(Int_t N = 50000)
{
   const Int_t nvar = 4;
   Float_t xvar[nvar];
   // output flie
   TFile* dataFile = TFile::Open( "data.root", "RECREATE" );
   // create signal and background trees
   TTree* treeS = new TTrerixD* covMatS = new TMatrixD( nvar, nvar );
   TMatrixD* covMatB = new TMatrixD( nvar, nvar );
   for (Int_t ivar=0; ivar<nvar; ivar++) {
      (*covMatS)(ivar,ivar) = dx[ivar]*dx[ivar];
      (*covMatB)(ivar,ivar) = dx[ivar]*dx[ivar];
      for (Int_t jvar=ivar+1; jvar<nvar; jvar++) {
         (*covMatS)(ivar,jvar) = rho[(ivar+1)*(jvar+1)]*dx[ivar]*dx[jvar];
         (*covMatS)(jvar,ivar) = (*covMatS)(ivar,jvar);
         (*covMatB)(ivar,jvar) = rho[(ivar+1)*(jvar+l" << endl; }
  else            { x = xB; m = sqrtMatB; cout << "- produce background" << endl; }
  // event loop
  TTree* tree = (itype==0) ? treeS : treeB;
  for (Int_t i=0; i<N; i++) {
    if (i%1000 == 0) cout << "... event: " << i << " (" << N << ")" << endl;
    getGaussRnd( *v, *m, R );
    for (Int_t ivar=0; ivar<nvar; ivar++) xvar[ivar] = (*v)[ivar] + x[ivar];
    tree->Fill();
  }
 }
// write trees
treeS->Write();
treeB->Write();
treeS->Show(0);
tre( "TreeB", "TreeB", 1 );
for (Int_t ivar=0; ivar<nvar; ivar++) {
  treeS->Branch( TString(Form( "var%i", ivar+1 )).Data(), &xvar[ivar], TString(Form( "var%i/F", ivar+1 )).Data() );
  treeB->Branch( TString(Form( "var%i", ivar+1 )).Data(), &xvar[ivar], TString(Form( "var%iMatB = new TMatrixD( nvar, nvar );
   for (Int_t ivar=0; ivar<nvar; ivar++) {
      (*covMatS)(ivar,ivar) = dx[ivar]*dx[ivar];
      (*covMatB)(ivar,ivar) = dx[ivar]*dx[ivar];
      for (Int_t jvar=ivar+1; jvar<nvar; jvar++) {
         (*covMatS)(ivar,jvar) = rho[(ivar+1)*(jvar+1)]*dx[ivar]*dx[jvar];
         (*covMatS)(jvar,ivar) = (*covMcout << "- produce background" << endl; }
      // event loop
      TTree* tree = (itype==0) ? treeS : treeB;
      for (Int_t i=0; i<N; i++) {
         if (i%1000 == 0) cout << "... event: " << i << " (" << N << ")" << endl;
         getGaussRnd( *v, *m, R );
         eta = 2.5*2*(Rendl << endl;
   cout << "please use .L createData.C++ if you want to run this MC geneation" <<endl;
   cout << "otherwise you will wait for ages!!! " << endl;
   cout << endl << endl << endl;
   // output flie
   TString fileName;
   if (BackgroundContamination) fileName = Form("linCorGauss%d_weighted+background.root",seed);
   else                         fileName = Form("linCorGauss%d_weighted.root",seed);
   TFile* dataFile = TFile::Open( fileName.Data(), "RECREATE" );
   // create signal and background trees
   TTree* treeS = new TTree( "TreeS", "TreeS", 1 );
   TTree* treeB = new TTree( "TreeB", "TreeB", 1 );
   for (Int_t ivar=0; ivar<nvar; ivar++) {
      treeS->Branch( TString(Form( "var%i", ivar+1 )).Data(), &xvar[ivar], TString(Form( "var%i/F", ivar+1 )).Data() );
      treeB->Branch( TString(Form( "var%i", ivar+1 )).Data(), &xvar[ivar], TString(Form( "var%i/F", ivar+1 )).Data() );
   }
   if (WeightedSignal||BackgroundContamination>0||1) treeS->Branch( "weight", &weight,"weight/F" );
   if (WeightedBkg)    treeB->Branch( "weight", &weight,"weight/F" );
   TRandom R( seed );
   Float_t xS[nvar] = {  0.2,  0.3,  0.4,  0.8 };
   Float_t xB[nvar] = { ) );
         weight = 0.8 / (TMath::Gaus( ((*v)[nvar-1]), 0, 1.09) );
         Double_t tmp=R.Uniform()/0.00034;
         if (itype==0 && !WeightedSignal) {
            weight = 1;
            tree->Fill();
            i++;
         } else if (itype==1 && !WeightedBkg) {
            weight = < i << " (" << N << ")" << endl;
         getGaussRnd( *v, *m, R );
         for (Int_t ivar=0; ivar<nvar; ivar++) xvar[ivar] = (*v)[ivar] + x[ivar];
         // add weights
         if (i%2) weight = 1;
         else weight = -1;
         tree->Fill();
      }
   }
   // write trees
   treeS->Write();
   treeB->Write();
   treeS->Show(0);
   treeB->Show(1);
   TH1d data file: " << dataFile->GetName() << endl;
										     }
									       // create the data
									       void create_lin_Nvar_Arr(Int_t N = 1000)
									       {
										 const Int_t nvar = 4;
										 std::vector<float>* xvar[nvar];
										 // output flie
										 TFile* dataFile = TFile::Open( "data.root", "RECREATE" );
										 // create signal and background trees
										 TTree* treeS = new TTree( "TreeS", "TreeS", 1 );
										 TTree* treeB = new TTree( "TreeB", "TreeB", 1 );
										 for (Int_t ivar=0; ivar<nvar; ivar++) {
										   xvar[ivar] = new std::vector<float>();
										   treeS->Branch( TString(Form( "var%i", ivar+1 )).Data(), "vector<float>", &xvar[ivar], 6400o[3*4] = 0.93;
												  // create covariance matrix
												  TMatrixD* covMatS = new TMatrixD( nvar, nvar );
												  TMatrixD* covMatB = new TMatrixD( nvar, nvar );
												  for (Int_t ivar=0; ivar<nvar; ivar++) {
												    (*covMatS)(ivar,ivar) = dx[ivar]*dx[ivar];
												    (*covMatB)(ivar,ivar) = dx[ivar]*dx[ivar];
												    for (Int_t jvar=ivar+1; jvar<nvar; jvar++) {
												      (*covMatS)(ivar,jvar) = rho[(ivar+1)*(jvar+1)]*dx[ivar]*dx[jvar];
												      (*covMatS)(jvar,ivar) = (*covMatS)(i= 0) { x = xS; m = sqrtMatS; cout << "- produce signal" << endl; }
												      else            { x = xB; m = sqrtMatB; cout << "- produce background" << endl; }
												      // event loop
												      TTree* tree = (itype==0) ? treeS : treeB;
												      for (Int_t i=0; i<N; i++) {
													if (i%100 == 0) cout << "... event: " << i << " (" << N << ")" << endl;
													Int_t aSize = (Int_t)(gRandom->Rndm()*10); // size File->GetName() << endl;
													//plot();
												      }
												      // create the data
												      void create_lin_Nvar_double()
												      {
													Int_t N = 10000;
													const Int_t nvar = 4;
													Double_t xvar[nvar];
													Double_t xvarD[nvar];
													Float_t  xvarF[nvar];
													// output flie
													TFile* dataFile = TFile::Open( "data.root", "RECREATE" );
													// create signal and background trees
													TTree* treeS = new TTree( "TreeS", "TreeS", 1 );
													TTree* treeB = new TTree( "TreeB",    }
													  TRandom R( 100 );
													Double_t xS[nvar] = {  0.2,  0.3,  0.5,  0.6 };
													Double_t xB[nvar] = { -0.2, -0.3, -0.5, -0.6 };
													Double_t dx[nvar] = {  1.0,  1.0, 1.0, 1.0 };
													TArrayD* v = new TArrayD( nvar );
													Double_t rho[20];
													rho[1*2] = 0.4;
													rho[1*3] = 0.6;
													rho[1*4] = 0.9;
													rho[2*3] = 0.7;
													rho[2*4] = 0.8;
													rho[3*4] = 0.93;
													// create covariance matrix
													TMatrixD* covMatS = new TMatrixD( nvar, nvar );
													TMatrixD* covMatB = new TMatrixD( nvar, nvar );
													for (Int_t ivar=0; ivar<nvar; ivar++) {
													  (*covMatS)(ivar,ivar) = dx[ivar]*dx[ivar];
													  (*c cout << "background covariance matrix: " << endl;
													   covMatB->Print();
													   // produce the square-root matrix
													   TMatrixD* sqrtMatS = produceSqrtMat( *covMatS );
													   TMatrixD* sqrtMatB = produceSqrtMat( *covMatB );
													   // loop over species
													   for (Int_t itype=0; itype<2; itype++) {
													     Double_t*  x;
													     TMatrixD* m;
													     if (itype == 0) { x = xS; m = sqrtMatS; cout << "- produce signal" << endl; }
													     else            { x = xB; m = sqrtMatB; cout << "- produce background" << endl; }
													     // event loop
													     TTree* tree = (itype==0) ? treeS : treeB;
													     for (Int_t i=0; i<N; i++) {
													       if (i%1000 == 0) cout << "... event: " << i << " (" << N << ")" << endl;
													       getGaussRnd( *v, *m, R );
													       for (Int_t ivar=0; ivar<nvar; ivar++) xvar[ivar] = (*v)[ivar] + x[ivar];
													       for (Int_t ivar=0; ivar<nvar; ivar++) {
														 if (ivar<2) xvarD[ivar] = xvar[ivar];
														 else        xvarF[ivar] = xvar[ivar];
													       }
													       tree->Fill();
													     }
													   }
													   // write trees
													   treeS->Writerm( "var%i", ivar+nvar-2+1 )).Data(), &xvarI[ivar], TString(Form( "var%i/I", ivar+nvar-2+1 )).Data() );
												      }
												      TRandom R( 100 );
												      Float_t xS[nvar] = {  0.2,  0.3,  1,  2 };
												      Float_t xB[nvar] = { -0.2, -0.3,  0,  0 };
												      Float_t dx[nvax[jvar];
														 (*covMatB)(jvar,ivar) = (*covMatB)(ivar,jvar);
														 }
												    }
												    cout << "signal covariance matrix: " << endl;
												    covMatS->Print();
												    cout << "background covariance matrix: " << endl;
												    covMatB->Print();
												    // produce the square-root matrix
												    TMatrixD* sqrtMatS = produceSqrtMat(xvar[nvar-1]);
												    tree->Fill();
												  }
												  }
										     // write trees
										     treeS->Write();
										   treeB->Write();
										   treeS->Show(0);
										   treeB->Show(1);
										   dataFile->Close();
										   cout << "created data file: " << dataFile->GetName() << endl;
										   plot();
										 }
										 // create the data
										 void create_ManyVars()
										 {
										   Int_t N = 20000;
										   const Int_t var*0.05;
										   dx[ivar] = 1;
										 }
										 xS[0] =   0.2;
										 xB[0] =  -0.2;
										 dx[0] =   1.0;
										 xS[1] =   0.3;
										 xB[1] =  -0.3;
										 dx[1] =   1.0;
										 xS[2] =   0.4;
										 xB[2] =  -0.4;
										 dx[2] =  1.0 ;
										 xS[3] =   0.8 ;
										 xB[3] =  -0.5 ;
										 dx[3] =   1.0 ;
										 //   TArrayD* v = new TArrayD( nvar );
										 Float_t rho[20];
										 rho[1*2] = 0.4;
										 rho[1*3] = 0.6;
										 rho[1*4] = 0.9;
										 rho[2*3] = 0.7;
										 rho[2*4] = 0.8;
										 rho[3*4] = 0.93;
										 TRandom R( 10   treeB->Write();
											    treeS->Show(0);
											    treeB->Show(1);
											    dataFile->Close();
											    plot();
											    cout << "created data file: " << dataFile->GetName() << endl;
											    }
										   // create the data
										   void create_lin_NvarObsolete()
										   {
										     Int_t N = 20000;
										     const Int_t nvar = 20;
										     Float_t xvar[nvar];
										     // output flie
										     TFile* dataFile = TFi   Float_t rho[50];
										     for (Int_t i=0; i<50; i++) rho[i] = 0;
										     rho[1*2] = 0.3;
										     rho[1*3] = 0.0;
										     rho[1*4] = 0.0;
										     rho[2*3] = 0.0;
										     rho[2*4] = 0.0;
										     rho[3*4] = 0.0;
										     // create covariance matrix
										     TMatrixD* covMatS = new TMatrixD( nvar, nvar );
										     TMatrixD* covMatB = new TMatrixD( nvar, nvar );
										     for (Int_t ivar=0; ivar<nvar; ivar++) {
										       (*covMatS)(ivar,ivasqrtMatB = produceSqrtMat( *covMatB );
												  // loop over species
												  for (Int_t itype=0; itype<2; itype++) {
												    Float_t*  x;
												    TMatrixD* m;
												    if (itype == 0) { x = xS; m = sqrtMatS; cout << "- produce signal" << endl; }
												    else            { x = xB; m = sqrtMatB; cout << "- produce background" << endl; }
												    // event loop
												    TTree* tree = (itype==0) ? treeS : treeB;
												    for (Int_t i=0; i<N; i++) {
												      if (i%1000 == 0) coutata.root", "RECREATE" );
   // create signal and background trees
   TTree* treeS = new TTree( "TreeS", "TreeS", 1 );
   TTree* treeB = new TTree( "TreeB", "TreeB", 1 );
   for (Int_t ivar=0; ivar<nvar; ivar++) {
      treeS->Branch( TString(Form( "var%i", ivar )).Data(), &xvar[ivar], TString(Form( "var%i/D", ivar )).Data() );
      treeB->Branch( TString(Form( "var%i", ivar )).Data(), &xvar[ivar], TString(Form( "var%i/D", ivar  = dx[ivar]*dx[ivar];
      for (Int_t jvar=ivar+1; jvar<nvar; jvar++) {
         (*covMatS)(ivar,jvar) = rhoS*dx[ivar]*dx[jvar];
         (*covMatS)(jvar,ivar) = (*covMatS)(ivar,jvar);
         (*covMatB)(ivar,jvar) = rhoB*dx[ivar]*dx[jvar];
         (*covMatB)(jvar,ivar) = (*covMatB)(ivar,jvar);
      }
   }
   cout << "signal covariance matrix: " << endl;
   covMatS->Print();
   cout << "background covariance matrix: " << endl;
   covMatB->Print();
   // produce the square-root matrix
   TMatrixD* sqrtMatS = produceSqrtMat( *covMatS );
   TMatrixD* sqrtMatB = produceSqrtMat( *covMatB );
   // loop over species
   for (Int_t itype=0; itype<2; itype++) {
      Float_t*  x;
      TMatrixD* m;
      if (itype == 0) { x = xS; m = sqrtMatS; cout << "- produce signal" << endl; }
      else            { x = xB; m = sqrtMatB; cout << "- produce background" << endl; }
      // event loop
      TTree* tree = (itype==0) ? treeS : treeB;
      for (Int_t i=0; i<N; i++) {
 ).Data(), &xvar[ivar], TString(Form( "var%i/F", ivar)).Data() );
      treeB->Branch( TString(Form( "var%i", ivar )).Data(), &xvar[ivar], TString(Form( "var%i/F", ivar)).Data() );
   }
   treeS->Branch("weight", &weight, "weight/F");
   treeB->Branch("weight", &weight, "war[nvar];
												      // output flie
												      TFile* dataFile = TFile::Open( "data.root", "RECREATE" );
												      // create signal and background trees
												      TTree* treeS = new TTree( "TreeS", "TreeS", 1 );
												      TTree* treeB = new TTree( "TreeB", "TreeB", 1 );
												      for (Int_t ivar=0; fnmin = -(rS+4.0*rsig);
													   Float_t fnmax = +(rS+4.0*rsig);
													   Float_t dfn = fnmax-fnmin;
													   // loop over species
													   for (Int_t itype=0; itype<2; itype++) {
													     // event loop
													     TTree* tree = (itype==0) ? treeS : treeB;
													     for (Int_t i=0; i<N; i++) {
													       Double_t r1=R.Rndm(),r2=R.Rndm(), r3;
													       if (itype==0) r3= r1>r2->GetName() << endl;
													       plot();
													     }
													     void create_schachbrett(Int_t nEvents = 20000) {
													       const Int_t nvar =-m_nDim; i <=  m_nDim; i++){
													       ytype  =  1;
													       for (Int_t j=-m_nDim; j <=  m_nDim; j++){
														 meanX=Double_t(i);
														 meanY=Double_t(j);
														 xvar[0]=m_rand->Gaus(meanY,sigma);
														 xvarr++) {
														 treeS->Branch( TString(Form( "var%i", ivar )).Data(), &xvar[ivar], TString(Form( "var%i/F", ivar )).Data() );
														 treeB->Branch( TString(Form( "var%i", ivar )).Data(), &xvar[ivar], TString(Form( "var%i/F", ivar )).Data() );
													       }
													       Int_t   nSeed   = 12345;
													       TRandom *m_rand = new TRandom(nSeed);
													       Double_t sigma=0.3;
													       Int_t itype[nvar];
													       Int_t iev=      Int_t type   = itype[0];
													       for (Int_t i=0;i<nvar;i++){
														 xvar[i]=m_rand->Gaus(Double_t(idx[i]),sigma);
														 if (i>0) type *= itype[i];
													       }
													       TTree* tree = (type==1) ? treeS : treeB;
													       tree->Fill();
													       "TreeS", "TreeS", 1 );
													     TTree* treeB = new TTree( "TreeB", "TreeB", 1 );
													     for (Int_t ivar=0; ivar<nvar; ivar++) {
													       treeS->Branch( TString(Form( "var%i", ivar )).Data(), &xvar[ivar], TString(Form( "var%i/F", ivar )).Data() );
													       treeB->Branch( TString(Form( "var%i", ivar )).Data(), &xvar[ivar], TString(Form( "var%i/F", ivar )).Data() );
													     }
													     Int_t   nSeed   = 12345;
													     TRandom *m_rand = new TRandom(nSe                Int_t type   = itype[0];
																	   for (Int_t i=0;i<nvar;i++){
																	     xvar[i]=m_rand->Gaus(Double_t(idx[i]),sigma);
																	     if (i>0) type *= itype[i];
																	   }
																	   TTree* tree = (type==1) ? treeS : treeB;
																	   tree->Fill();
																	   iev++;
																	   itype[3] *= -1;
																	   }
													       itype[2] *= -1;
													   }
													     itype[1] *= -1;
													   }
												      itype[0] *= -1;
												    }
												  }
												  // write trees
												  treeS->Write();
												  treeB->Write();
												  treeS->Show(0);
												  treeB->Show(1);
												  dataFile->Close();
												  cout << "created data file: " << dataFile->GetName() << endl;
												  plot();
												  }
											 void create_schachbrett_3D(Int_t nEvents = 20000) {
											 const Int_t nvar = 3;
											 Float_t xvar[nvar];
											 // output flie
											 TFile* dataFile = TFile::Open( "data.root", "RECREATE" );
											 // create signal and background trees
											 TTree* treeS = new TTree( "TreeS", "TreeS", 1 );
											 TTree* treeB = new TTree( "TreeB", "TreeB", 1 );
											 for (Int_t ivar=0; ivar<nvar; ivar++) {
											   treeS->Branch( TString(Form( "var%i", ivar )).Data(), &xvar[ivar], TString(Form( "var%i/F", ivar )).Data() );
											   treeB->Branch( TStri if (i>0) type *= itype[i];
													  }
											     TTree* tree = (type==1) ? treeS : treeB;
											   tree->Fill();
											   iev++;
											   itype[2] *= -1;
											 }
											 itype[1] *= -1;
										       }
										       itype[0] *= -1;
										     }
										   }
										 // write trees
										 treeS->Write();
										 treeB->Write();
										 treeS->ta(), &xvar[ivar], TString(Form( "var%i/F", ivar )).Data() );
									       }
		 Int_t   nSeed   = 345;
		 TRandom *m_rand = new TRandom(nSeed);
		 Double_t sigma=0.35;
		 Int_t itype[nvar];
		 Int_t iev=0;
		 Int_t m_nDim = nbumps; // actually the boundary, there is a "bump" for every interger value
		 // between in the Inteval [-m_nDim,m_nDim]
		 int idx[nvar];
		 while (iev < nEvents){
		   ataFile->Close();
		   cout << "created data file: " << dataFile->GetName() << endl;
		   plot();
		 }
		 void create_3Bumps(Int_t nEvents = 5000) {
		   // signal is clustered around (1,0) and (-1,0) where one is two times(1,0)
		   // bkg                        (0,0)
		   const Int_t nvar = 2;
		   Float_0,0,0,0}}; //
  while (iev < nEvents){
    for (int idx=0; idx<6; idx++){
      if (idx==1 || idx==2 || idx==3) type = 0;
      else type=1;
      for (Int_t ivar=0;ivar<nvar;ivar++){
	xvar[ivar]=m_rand->Gaus(Centers[ivar][idx],sigma);
      }
      TTree* tree = (type==1) ? treeS : treeB;
      tree->Fill();
      ar], TString(Form( "var%i/F", ivar+1 )).Data() );
  treeB->Branch( TString(Form( "var%i", ivar+1 )).Data(), &xvar[ivar], TString(Form( "var%i/F", ivar+1 )).Data() );
 }
TRandom R( 100 );
do {
  for (Int_t ivar=0; ivar<nvar; ivar++) { xvar[ivar]=R.Rndm();}
  Float_t xout = sin(2.*acos(-1.)*(xvar[0]*xvar[1]*xvar[2]*xvar[3]+xvar[0]*xvar[1]));
  if (nsig<100) cout << "xout = " << xout<<endl;
  Int_t0.4 },
      { 0.2  ,  0.1, -0.1, 0.7 }} ;
   Float_t xvar[100];
   // create tree using class flag stored in int variable cls
TTree* treeR = new TTree( "TreeR", "TreeR", 1 );
for (Int_t ivar=0; ivar<nvar; ivar++) {
  treeR->Branch( TString(Form( "varndat < nmax ");
   dataFile->Write();
   dataFile->Close();
}
// create the data
void create_array_with_different_lengths(Int_t N = 100)
{
   const Int_t nvar = 4;
   Int_t nvarCurrent = 4;
   Float_t xvar[nvar];
   // output flie
   TFile* dataFile = TFile::Open( "data.root", "RECREATE" );
   // create signal and background trees
   TTree* treeS = new TTree( "TreeS", "TreeS", 1 );
   TTree* treeB = new TTree( "rix
			       TMatrixD* covMatS = new TMatrixD( nvar, nvar );
			       TMatrixD* covMatB = new TMatrixD( nvar, nvar );
			       for (Int_t ivar=0; ivar<nvar; ivar++) {
				 (*covMatS)(ivar,ivar) = dx[ivar]*dx[ivar];
				 (*covMatB)(ivar,ivar) = dx[ivar]*dx[ivar];
				 for (Int_t jvar=ivar+1; jvar<nvar; jvar++) {
				   (*covMatoduce signal" << endl; }
      else            { x = xB; m = sqrtMatB; cout << "- produce background" << endl; }
      // event loop
      TTree* tree = (itype==0) ? treeS : treeB;
      for (Int_t i=0; i<N; i++) {
         if (i%1000 == 0) cout << "... event: " << i << " (" << N << ")" << endl;
         getGaussRnd( *v, *m, R );
         for (Int_t ivar=0; ivar<nvar; ivar++) xvar[ivar] = (*v)[ivar] + x[ivar];
    nvarCurrent = (i%4)+1;
         tree->Fill();
      }
   }
   // write trees
   treeS->Write();
   treeB->Write();
   treeS->Show(0);
   treeB->Show(1);
   dataFile->Close();
   cout << "created data file: " << dataFile->GetName() << endl;
}
