

#include "histio.c"

TH1F* get_hist( const char* hname ) ;

//=====================================================================

   void optimization1( int sigmass = 30, double bg_syst = 0.1,  int nb = 3 ) {

      gStyle -> SetPaintTextFormat( "5.2f" ) ;
      gStyle -> SetMarkerSize( 1.4 ) ;

      char answ ;
      char outfile[1000] ;
      char infile[1000] ;
      char label[1000] ;

      if ( nb == 3 ) {
         sprintf( infile, "MVACutFlowTribMVA.root" ) ;
      } else if ( nb == 4 ) {
         sprintf( infile, "MVACutFlowQuabMVA.root" ) ;
      } else {
         printf("\n\n nb must be 3 or 4.\n\n") ;
         return ;
      }

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

      gSystem -> Exec( "mkdir -p outputfiles" ) ;

      TCanvas* can1 = (TCanvas*) gDirectory -> FindObject( "can1" ) ;
      if ( can1 == 0x0 ) can1 = new TCanvas( "can1", "", 1500, 1200 ) ;
      can1 -> Clear() ;
      can1 -> Divide(2,2) ;
      can1 -> cd(1) ;

      gDirectory -> Delete( "*" ) ;

      loadHist( infile, 0, "*BDT*" ) ;

      char hname[1000] ;

      sprintf( hname, "h_b_BDT_SGMC_Wh%2d", sigmass ) ;
      TH1F* h_sig = get_hist( hname ) ;

      sprintf( hname, "h_b_BDT_BGMC_SumBKG" ) ;
      TH1F* h_bg = get_hist( hname ) ;

      int nvals_highbinedge(0) ;
      int nvals_lowbinedge(0) ;
      double highbinedge_vals[100] ;
      double lowbinedge_vals[100] ;

      if ( nb == 3 ) {
         int i(0) ;
         highbinedge_vals[i] = 0.14 ; i++ ;
         highbinedge_vals[i] = 0.16 ; i++ ;
         highbinedge_vals[i] = 0.18 ; i++ ;
         highbinedge_vals[i] = 0.20 ; i++ ;
         highbinedge_vals[i] = 0.22 ; i++ ;
         highbinedge_vals[i] = 0.24 ; i++ ;
         nvals_highbinedge = i ;
         i = 0 ;
         lowbinedge_vals[i] = 0.04 ; i++ ;
         lowbinedge_vals[i] = 0.06 ; i++ ;
         lowbinedge_vals[i] = 0.08 ; i++ ;
         lowbinedge_vals[i] = 0.10 ; i++ ;
         lowbinedge_vals[i] = 0.12 ; i++ ;
         lowbinedge_vals[i] = 0.14 ; i++ ;
         lowbinedge_vals[i] = 0.16 ; i++ ;
         lowbinedge_vals[i] = 0.18 ; i++ ;
         lowbinedge_vals[i] = 0.20 ; i++ ;
         lowbinedge_vals[i] = 0.22 ; i++ ;
         nvals_lowbinedge = i ;
      } else {
         int i(0) ;
         highbinedge_vals[i] = 0.10 ; i++ ;
         highbinedge_vals[i] = 0.12 ; i++ ;
         highbinedge_vals[i] = 0.14 ; i++ ;
         highbinedge_vals[i] = 0.16 ; i++ ;
         highbinedge_vals[i] = 0.18 ; i++ ;
         highbinedge_vals[i] = 0.20 ; i++ ;
         nvals_highbinedge = i ;
         i = 0 ;
         lowbinedge_vals[i] = 0.00 ; i++ ;
         lowbinedge_vals[i] = 0.02 ; i++ ;
         lowbinedge_vals[i] = 0.04 ; i++ ;
         lowbinedge_vals[i] = 0.06 ; i++ ;
         lowbinedge_vals[i] = 0.08 ; i++ ;
         lowbinedge_vals[i] = 0.10 ; i++ ;
         lowbinedge_vals[i] = 0.12 ; i++ ;
         lowbinedge_vals[i] = 0.14 ; i++ ;
         lowbinedge_vals[i] = 0.16 ; i++ ;
         lowbinedge_vals[i] = 0.18 ; i++ ;
         nvals_lowbinedge = i ;
      }

      TH2F* h_s_over_sigmab_quadsum = new TH2F( "h_s_over_sigmab_quadsum", "h_s_over_sigmab_quadsum",
                 nvals_highbinedge, 0.5, nvals_highbinedge+0.5,
                 nvals_lowbinedge, 0.5, nvals_lowbinedge+0.5 ) ;

      for ( int i=1; i<=nvals_highbinedge; i++ ) {
         char label[100] ;
         sprintf( label, "%.2f", highbinedge_vals[i-1] ) ;
         h_s_over_sigmab_quadsum -> GetXaxis() -> SetBinLabel( i, label ) ;
         h_s_over_sigmab_quadsum -> SetXTitle( "low edge of highest BDT bin" ) ;
      }
      for ( int i=1; i<=nvals_lowbinedge; i++ ) {
         char label[100] ;
         sprintf( label, "%.2f", lowbinedge_vals[i-1] ) ;
         h_s_over_sigmab_quadsum -> GetYaxis() -> SetBinLabel( i, label ) ;
         h_s_over_sigmab_quadsum -> SetYTitle( "low edge of 2nd highest BDT bin" ) ;
      }

      TH2F* h_s_over_sigmab_highbin = (TH2F*) h_s_over_sigmab_quadsum -> Clone( "h_s_over_sigmab_highbin" ) ;
      TH2F* h_s_over_sigmab_lowbin = (TH2F*) h_s_over_sigmab_quadsum -> Clone( "h_s_over_sigmab_lowbin" ) ;


      int nbins_1d_hist = h_sig -> GetNbinsX() ;

      for ( int hbi=1; hbi<=nvals_highbinedge; hbi++ ) {

         int high_bdt_bin_low_edge_1d_hist_bin = h_sig -> FindBin( highbinedge_vals[hbi-1] + 0.001 ) ;
         printf("   hbi = %2d : high_bdt_bin_low_edge_1d_hist_bin = %2d, edge = %.2f\n", hbi, high_bdt_bin_low_edge_1d_hist_bin, highbinedge_vals[hbi-1] ) ;

         for ( int lbi=1; lbi<=nvals_lowbinedge; lbi++ ) {

            if ( lowbinedge_vals[lbi-1] >= highbinedge_vals[hbi-1] ) continue ;

            int low_bdt_bin_low_edge_1d_hist_bin = h_sig -> FindBin( lowbinedge_vals[lbi-1] + 0.001 ) ;
            printf("   lbi = %2d :  low_bdt_bin_low_edge_1d_hist_bin = %2d, edge = %.2f\n", lbi, low_bdt_bin_low_edge_1d_hist_bin, lowbinedge_vals[lbi-1] ) ;

            float high_bdt_bin_sig_val = h_sig -> Integral( high_bdt_bin_low_edge_1d_hist_bin, nbins_1d_hist ) ;
            float  low_bdt_bin_sig_val = h_sig -> Integral( low_bdt_bin_low_edge_1d_hist_bin, high_bdt_bin_low_edge_1d_hist_bin-1 ) ;

            float high_bdt_bin_bg_val = h_bg -> Integral( high_bdt_bin_low_edge_1d_hist_bin, nbins_1d_hist ) ;
            float  low_bdt_bin_bg_val = h_bg -> Integral( low_bdt_bin_low_edge_1d_hist_bin, high_bdt_bin_low_edge_1d_hist_bin-1 ) ;

            if ( high_bdt_bin_bg_val <= 0 ) high_bdt_bin_bg_val = 1. ; // always have at least one bg event.
            float high_bdt_bin_bg_err = sqrt( high_bdt_bin_bg_val + pow( high_bdt_bin_bg_val * bg_syst, 2 ) ) ;

            if ( low_bdt_bin_bg_val <= 0 ) low_bdt_bin_bg_val = 1. ; // always have at least one bg event.
            float low_bdt_bin_bg_err = sqrt( low_bdt_bin_bg_val + pow( low_bdt_bin_bg_val * bg_syst, 2 ) ) ;

            printf("     High bin, S = %8.1f, B = %8.1f +/- %7.1f\n", high_bdt_bin_sig_val, high_bdt_bin_bg_val, high_bdt_bin_bg_err ) ;
            printf("      Low bin, S = %8.1f, B = %8.1f +/- %7.1f\n", low_bdt_bin_sig_val, low_bdt_bin_bg_val, low_bdt_bin_bg_err ) ;

            float high_bdt_bin_s_over_sigmab = high_bdt_bin_sig_val / high_bdt_bin_bg_err ;
            float low_bdt_bin_s_over_sigmab = low_bdt_bin_sig_val / low_bdt_bin_bg_err ;
            float quad_sum_s_over_sigmab = sqrt( high_bdt_bin_s_over_sigmab * high_bdt_bin_s_over_sigmab + low_bdt_bin_s_over_sigmab * low_bdt_bin_s_over_sigmab ) ;

            printf("     S / sigma B :   high bin = %7.2f, low bin = %7.2f , quad sum = %7.2f\n\n",
               high_bdt_bin_s_over_sigmab, low_bdt_bin_s_over_sigmab, quad_sum_s_over_sigmab ) ;

            h_s_over_sigmab_quadsum -> SetBinContent( hbi, lbi, quad_sum_s_over_sigmab ) ;
            h_s_over_sigmab_highbin -> SetBinContent( hbi, lbi, high_bdt_bin_s_over_sigmab ) ;
            h_s_over_sigmab_lowbin -> SetBinContent( hbi, lbi, low_bdt_bin_s_over_sigmab ) ;

         } // lbi

      } // hbi

      can1 -> Clear() ;
      can1 -> Divide(2,2) ;

      int ci(1) ;

      can1 -> cd( ci ) ; ci ++ ;
      h_s_over_sigmab_quadsum -> Draw("colz2") ;
      h_s_over_sigmab_quadsum -> Draw("text same") ;
      sprintf( label, "%db : mh = %2d : Bsyst = %4.2f : S / sigma B, sum in quad.", nb, sigmass, bg_syst ) ;
      label_tt -> DrawTextNDC( 0.1, 0.93, label ) ;

      can1 -> cd( ci ) ; ci ++ ;
      h_s_over_sigmab_highbin -> Draw("colz2") ;
      h_s_over_sigmab_highbin -> Draw("text same") ;
      sprintf( label, "%db : mh = %2d : Bsyst = %4.2f : S / sigma B, high bin", nb, sigmass, bg_syst ) ;
      label_tt -> DrawTextNDC( 0.1, 0.93, label ) ;

      can1 -> cd( ci ) ; ci ++ ;
      h_s_over_sigmab_lowbin -> Draw("colz2") ;
      h_s_over_sigmab_lowbin -> Draw("text same") ;
      sprintf( label, "%db : mh = %2d : Bsyst = %4.2f : S / sigma B, low bin", nb, sigmass, bg_syst ) ;
      label_tt -> DrawTextNDC( 0.1, 0.93, label ) ;




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
