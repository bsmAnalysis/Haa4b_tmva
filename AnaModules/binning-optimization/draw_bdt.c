

#include "histio.c"

TH1F* get_hist( const char* hname ) ;

//=====================================================================

   void draw_bdt( int sigmass = 30, double bg_syst = 0.1,  const char* infile = "MVACutFlowQuabMVA.root" ) {

      char answ ;
      char outfile[1000] ;

      int nb(0) ;
      if ( strcmp( infile, "MVACutFlowQuabMVA.root" ) == 0 ) { nb = 4 ; }
      if ( strcmp( infile, "MVACutFlowTribMVA.root" ) == 0 ) { nb = 3 ; }

      gStyle -> SetOptTitle(0) ;
      gStyle -> SetPadBottomMargin( 0.13 ) ;

      TText* label_tt = new TText() ;
      TText* xtitle_tt = new TText() ;
      TText* ytitle_tt = new TText() ;
      ytitle_tt -> SetTextAngle( 90 ) ;
      ytitle_tt -> SetTextAlign( 31 ) ;
      xtitle_tt -> SetTextAlign( 31 ) ;
      label_tt -> SetTextSize( 0.04 ) ;
      xtitle_tt -> SetTextSize( 0.04 ) ;
      ytitle_tt -> SetTextSize( 0.04 ) ;
      char label[1000] ;

      gSystem -> Exec( "mkdir -p outputfiles" ) ;

      TCanvas* can1 = (TCanvas*) gDirectory -> FindObject( "can1" ) ;
      if ( can1 == 0x0 ) can1 = new TCanvas( "can1", "", 900, 700 ) ;
      can1 -> Clear() ;
      can1 -> cd() ;

      gDirectory -> Delete( "*" ) ;

      loadHist( infile, 0, "*BDT*" ) ;

      char hname[1000] ;

      sprintf( hname, "h_b_BDT_SGMC_Wh%2d", sigmass ) ;
      TH1F* h_sig = get_hist( hname ) ;

      sprintf( hname, "h_b_BDT_BGMC_SumBKG" ) ;
      TH1F* h_bg = get_hist( hname ) ;

      TH2F* h_dummy = new TH2F( "h_dummy", "", 200, -0.3, 0.3, 200, 0., 15. ) ;

      double sigmax = h_sig -> GetMaximum() ;

      h_sig -> SetFillStyle(0) ;
      h_sig -> SetFillColor(0) ;
      h_sig -> SetLineWidth(2) ;
      h_sig -> SetLineColor(4) ;
      h_sig -> SetLineStyle(1) ;

      h_sig -> SetMaximum( 2.5 * sigmax ) ;

      h_bg -> SetFillStyle(0) ;
      h_bg -> SetFillColor(0) ;
      h_bg -> SetLineWidth(2) ;
      h_bg -> SetLineColor(2) ;
      h_bg -> SetLineStyle(1) ;

      h_sig -> Draw( "hist" ) ;

      h_bg -> Draw("same hist" ) ;

      xtitle_tt -> DrawTextNDC( 0.95, 0.02, "BDT value" ) ;

      gPad -> SetGridx(1) ;
      gPad -> SetGridy(1) ;
      sprintf( label, "%s : signal mass %d\n", infile, sigmass ) ;
      label_tt -> DrawTextNDC( 0.1, 0.95, label ) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;

      sprintf( outfile, "outputfiles/sig-and-bg-hists-%db-hmass%02d.pdf", nb, sigmass ) ;
      can1 -> SaveAs( outfile ) ;
      answ = getchar() ;

   //---------------------------

      double sum_sig(0) ;
      double sum_bg(0) ;

      int nbins = h_sig -> GetNbinsX() ;

      double y[1000] ;
      double x[1000] ;
      int np(0) ;

      for ( int bi=nbins; bi >= 1 ; bi-- ) {

         double bg_val = h_bg -> GetBinContent( bi ) ;
         double sig_val = h_sig -> GetBinContent( bi ) ;

         if ( bg_val <= 0 ) bg_val = 1. ; // always have at least on BG event in bin.

         sum_sig += sig_val ;
         sum_bg += bg_val ;


         double bg_err = sqrt( sum_bg + pow( sum_bg * bg_syst, 2. ) ) ;

         double s_over_sigmab(0) ;
         if ( bg_err > 0 ) s_over_sigmab = sum_sig / bg_err ;

         double bin_edge = h_sig -> GetBinLowEdge( bi ) ;

         printf(" %2d :  BDT > %7.3f,  Sig = %7.1f , BG = %7.1f +/- %7.1f :  S/sigmaB = %7.3f\n",
             bi, bin_edge, sum_sig, sum_bg, bg_err, s_over_sigmab ) ;

         if ( s_over_sigmab > 0 ) {
            y[np] = s_over_sigmab ;
            x[np] = bin_edge ;
            np++ ;
         }

      } // bi

      TGraph* gr = new TGraph( np, x, y ) ;
      gr -> SetMarkerStyle(20) ;

      h_dummy -> Draw() ;
      gr -> Draw( "pl same" ) ;
      sprintf( label, "%s : signal mass %d , BG syst %.2f\n", infile, sigmass, bg_syst ) ;
      label_tt -> DrawTextNDC( 0.1, 0.95, label ) ;
      xtitle_tt -> DrawTextNDC( 0.95, 0.02, "Minimum BDT value" ) ;
      ytitle_tt -> DrawTextNDC( 0.05, 0.95, "S / sigma B" ) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;
      sprintf( outfile, "outputfiles/s-over-sigmab-vs-bdt-cut-%db-hmass%02d-syst%.2f.pdf", nb, sigmass, bg_syst ) ;
      can1 -> SaveAs( outfile ) ;
      answ = getchar() ;


   //---------------------------

      TH1F* h_s_over_sigmab = (TH1F*) h_sig -> Clone( "h_s_over_sigmab" ) ;
      h_s_over_sigmab -> Reset() ;

      TH1F* h_cumulative_s_over_sigmab = (TH1F*) h_sig -> Clone( "h_cumulative_s_over_sigmab" ) ;
      h_cumulative_s_over_sigmab -> Reset() ;
      h_cumulative_s_over_sigmab -> SetLineColor(3) ;


      double sum_s_over_sigmab_squared(0.) ;

      for ( int bi=nbins; bi >= 1 ; bi-- ) {

         double sig_val = h_sig -> GetBinContent( bi ) ;
         double bg_val  = h_bg -> GetBinContent( bi ) ;

         if ( bg_val <= 0 ) bg_val = 1. ; // always have at least on BG event in bin.

         double bg_err = sqrt( bg_val + pow( bg_val * bg_syst, 2. ) ) ;

         double s_over_sigmab(0) ;
         if ( bg_err > 0 ) {
            s_over_sigmab = sig_val / bg_err ;
            h_s_over_sigmab -> SetBinContent( bi, s_over_sigmab ) ;
            sum_s_over_sigmab_squared += s_over_sigmab * s_over_sigmab ;
         }

         double quadsum_s_over_sigmab = sqrt( sum_s_over_sigmab_squared ) ;

         h_cumulative_s_over_sigmab -> SetBinContent( bi, quadsum_s_over_sigmab ) ;

         double bin_edge = h_sig -> GetBinLowEdge( bi ) ;

         printf(" %2d :  BDT > %7.3f,  Sig = %7.1f , BG = %7.1f +/- %7.1f :  S/sigmaB = %7.3f , quad sum S/sigmaB = %7.3f\n",
             bi, bin_edge, sum_sig, sum_bg, bg_err, s_over_sigmab, quadsum_s_over_sigmab ) ;

         if ( s_over_sigmab > 0 ) {
            y[np] = s_over_sigmab ;
            x[np] = bin_edge ;
            np++ ;
         }


      } // bi

      h_s_over_sigmab -> SetMaximum(16) ;
      h_s_over_sigmab -> Draw() ;
      h_cumulative_s_over_sigmab -> Draw("same") ;
      h_s_over_sigmab -> Draw("same") ;

      sprintf( label, "%s : signal mass %d , BG syst %.2f\n", infile, sigmass, bg_syst ) ;
      label_tt -> DrawTextNDC( 0.1, 0.95, label ) ;
      sprintf( label, "Quadrature sum of S / sigma B : %5.2f", sqrt( sum_s_over_sigmab_squared ) ) ;
      label_tt -> DrawTextNDC( 0.25, 0.85, label ) ;
      xtitle_tt -> DrawTextNDC( 0.95, 0.02, "BDT value" ) ;
      ytitle_tt -> DrawTextNDC( 0.05, 0.95, "S / sigma B" ) ;

      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;
      sprintf( outfile, "outputfiles/s-over-sigmab-per-bin-%db-hmass%02d-syst%.2f.pdf", nb, sigmass, bg_syst ) ;
      can1 -> SaveAs( outfile ) ;
      answ = getchar() ;




   //---------------------------

///   vector<string> bgtypes ;
///   bgtypes.push_back( "TTJets" ) ;
///   bgtypes.push_back( "WJets" ) ;
///   bgtypes.push_back( "QCD" ) ;
///   bgtypes.push_back( "SingleT" ) ;
///   bgtypes.push_back( "TTGZW" ) ;
///   bgtypes.push_back( "DiBoson" ) ;
///   bgtypes.push_back( "TriBoson" ) ;


///   for ( unsigned int bi=0; bi<bgtypes.size(); bi++ ) {
///      sprintf( hname, "h_b_BDT_BGMC_%s", bgtypes[bi].c_str() ) ;
///      TH1F* hp = get_hist( hname ) ;
///      hp -> Draw( "hist" ) ;
///      label_tt -> DrawTextNDC( 0.1, 0.95, hname ) ;
///      hp -> Print("all") ;
///      printf( " %2d : %s\n", bi, hname ) ;
///      can1 -> Update() ; can1 -> Draw() ; gSystem -> ProcessEvents() ;
///      answ = getchar() ;
///   }






   } // draw_bdt

//=====================================================================

TH1F* get_hist( const char* hname ) {
   TH1F* rp = (TH1F*) gDirectory -> FindObject( hname ) ;
   if ( rp == 0x0 ) {
      printf("\n\n *** get_hist : can't find %s\n\n", hname ) ;
      gSystem -> Exit(-1) ;
   }
   return rp ;
}

//=====================================================================
