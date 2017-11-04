#include "customize.h"

namespace AnaFunctions
{
  //common
  float DeltaPhi(const TLorentzVector& LvecA, const TLorentzVector& LvecB)
  {
    float dphi = LvecA.Phi() - LvecB.Phi();
    while ( dphi > TMath::Pi() )
    {
      dphi = dphi - 2 * TMath::Pi();
    }
    while ( dphi < -TMath::Pi() )
    {
      dphi = dphi + 2 * TMath::Pi();
    }
    return dphi;
  }

  float DeltaR(const TLorentzVector& LvecA, const TLorentzVector& LvecB)
  {
    float deta = LvecA.Eta() - LvecB.Eta();
    float dphi = DeltaPhi(LvecA, LvecB);
    float dr = std::sqrt( deta*deta + dphi*dphi );
    return dr;
  }
  //TL sort boolean, from big to small
  bool TLvecSortByPt(const TLorentzVector& a, const TLorentzVector& b)
  {
    return a.Pt() > b.Pt();
  }

  bool TLvecSortByM(const TLorentzVector& a, const TLorentzVector& b)
  {
    return a.M() > b.M();
  }
  //end common

  //muon
  bool passMu(const TLorentzVector& muLvec, bool passId, bool passIso, const AnaConsts::MuIsoAccRec& musArr)
  {
    const float minAbsEta = musArr.minAbsEta, maxAbsEta = musArr.maxAbsEta, minPt = musArr.minPt, maxPt = musArr.maxPt; 
    float permupt = muLvec.Pt(), permueta = muLvec.Eta();
    return ( minAbsEta == -1 || fabs(permueta) >= minAbsEta )
      && ( maxAbsEta == -1 || fabs(permueta) < maxAbsEta )
      && (     minPt == -1 || permupt >= minPt )
      && (     maxPt == -1 || permupt < maxPt )
      && passId
      && passIso;
  }

  int countMus(const std::vector<TLorentzVector> &muLvecVec, const std::vector<bool> &passmuId, const std::vector<bool> &passmuIso, const AnaConsts::MuIsoAccRec& musArr, std::vector<TLorentzVector> &selmuLvecVec)
  {
    int cntNMus = 0;
    for (unsigned int im = 0; im < muLvecVec.size(); im++)
    {
      if (passMu(muLvecVec[im], passmuId[im],  passmuIso[im], musArr))
      {
        selmuLvecVec.push_back(muLvecVec[im]);
        cntNMus ++;
      }
    }
    return cntNMus;
  }
  //end muon

  //electron
  bool passEl(const TLorentzVector& elLvec, bool passId, bool passIso, const AnaConsts::ElIsoAccRec& elsArr)
  {
    const float minAbsEta = elsArr.minAbsEta, maxAbsEta = elsArr.maxAbsEta, minPt = elsArr.minPt, maxPt = elsArr.maxPt;
    float perelpt = elLvec.Pt(), pereleta = elLvec.Eta();
    return ( minAbsEta == -1 || fabs(pereleta) >= minAbsEta )
      && ( maxAbsEta == -1 || fabs(pereleta) < maxAbsEta )
      && (     minPt == -1 || perelpt >= minPt )
      && (     maxPt == -1 || perelpt < maxPt ) 
      && passId
      && passIso;
  }

  int countEls(const std::vector<TLorentzVector> &elLvecVec, const std::vector<bool> &passelId, const std::vector<bool> &passelIso, const AnaConsts::ElIsoAccRec& elsArr, std::vector<TLorentzVector> &selelLvecVec)
  {
    int cntNEls = 0;
    for (unsigned int ie = 0; ie < elLvecVec.size(); ie++)
    {
      if (passEl(elLvecVec[ie], passelId[ie], passelIso[ie], elsArr))
      {
        selelLvecVec.push_back(elLvecVec[ie]);
        cntNEls ++;
      }
    }
    return cntNEls;
  }
  //end electron

  //calculate mtw
  float calcMtW( TLorentzVector metLvec, TLorentzVector lepLvec)
  {
    /*
    float dphi = metLvec.Phi() - lepLvec.Phi();
    while ( dphi > TMath::Pi() )
    {
      dphi = dphi - 2 * TMath::Pi();
    }
    while ( dphi < -TMath::Pi() )
    {
      dphi = dphi + 2 * TMath::Pi();
    }
    */
    //std::cout << dphi << "," << DeltaPhi(metLvec, lepLvec) << std::endl;

    float mtw = std::sqrt ( 2.0 * metLvec.Pt() * lepLvec.Pt() * ( 1.0 - std::cos( DeltaPhi(metLvec, lepLvec) ) ) );
    return mtw;
  }
  //end mtw

  //jet pre-selection (for hard b jet, pt>20)
  bool passJetLepClean(const TLorentzVector &jetLvec, const std::vector<TLorentzVector> &selmuLvecVec, const std::vector<TLorentzVector> &selelLvecVec)
  {
    bool thispassJetLepClean = true;
    int selmusize = selmuLvecVec.size(); int selelsize = selelLvecVec.size();

    if (selmusize != 0)
    {
      for ( int i = 0; i < selmusize; i++)
      {
        if ( DeltaR(jetLvec, selmuLvecVec[i]) < AnaConsts::minDeltaRJetMu) { return false; }
      }
    }

    if (selelsize != 0)
    {
      for ( int i = 0; i < selelsize; i++)
      { 
        if ( DeltaR(jetLvec, selelLvecVec[i]) < AnaConsts::minDeltaRJetEl) { return false; }
      }
    }
    return thispassJetLepClean;
  }

  std::vector<bool> preSelJet(const std::vector<TLorentzVector> &jetLvecVec, const AnaConsts::JetAccRec& jetsArr, const std::vector<TLorentzVector> &selmuLvecVec, const std::vector<TLorentzVector> &selelLvecVec)
  {
    std::vector<bool> passJetPreSel;
    const float minAbsEta = jetsArr.minAbsEta, maxAbsEta = jetsArr.maxAbsEta, minPt = jetsArr.minPt, maxPt = jetsArr.maxPt;
    for ( int i = 0; i < jetLvecVec.size(); i++ )
    {
      bool thispassJetPreSel = true;
      float perjetpt = jetLvecVec[i].Pt(), perjeteta = jetLvecVec[i].Eta();
      bool thispassJetAcc = 
         ( minAbsEta == -1 || fabs(perjeteta) >= minAbsEta )
      && ( maxAbsEta == -1 || fabs(perjeteta) < maxAbsEta )
      && (     minPt == -1 || perjetpt >= minPt )
      && (     maxPt == -1 || perjetpt < maxPt );
      bool thispassJetLepClean = passJetLepClean(jetLvecVec[i], selmuLvecVec, selelLvecVec);
      thispassJetPreSel = thispassJetAcc && thispassJetLepClean;
      //if ( thispassJetAcc && !thispassJetLepClean ){ std::cout <<  perjetpt << "," << perjeteta << std::endl; }
      //if (thispassJetPreSel){ std::cout <<  perjetpt << "," << perjeteta << std::endl; }
      passJetPreSel.push_back(thispassJetPreSel);
    }
    return passJetPreSel;
  }

  //hard b-jet selection
  int countHardBJets(const std::vector<TLorentzVector> &jetLvecVec, const std::vector<bool> & passJetPreSel, const std::vector<bool> &passBTag, std::vector<TLorentzVector> &selhardbLvecVec)
  {
    int cntHardBJets = 0;
    for ( int i = 0; i < jetLvecVec.size(); i++ )
    {
      if ( passJetPreSel[i] && passBTag[i] )
      {
        cntHardBJets ++;
        selhardbLvecVec.push_back(jetLvecVec[i]);
      }
    }
    return cntHardBJets;
  }
  
  int countHardBJets(const std::vector<TLorentzVector> &jetLvecVec, const std::vector<bool> & passJetPreSel, const std::vector<float> &BTagCSV, std::vector<TLorentzVector> &selhardbLvecVec)
  {
    int cntHardBJets = 0;
    for ( int i = 0; i < jetLvecVec.size(); i++ )
    {
      if ( passJetPreSel[i] && (BTagCSV[i] > AnaConsts::HardBJetsCSVLooseWP) )
      {
        cntHardBJets ++;
        selhardbLvecVec.push_back(jetLvecVec[i]);
      }
    }
    return cntHardBJets;
  }
  
  //sv pre-selection (for soft b jet, pt<20)
  bool passSVJetClean(const TLorentzVector &svLvec, const std::vector<TLorentzVector> &selhardbLvecVec)
  {
    bool thispassSVJetClean = true;
    int selhardbsize = selhardbLvecVec.size();
    
    if (selhardbsize != 0)
    { 
      for ( int i = 0; i < selhardbsize; i++)
      { 
        if ( DeltaR(svLvec, selhardbLvecVec[i]) < AnaConsts::minDeltaRSVJet) { return false; }
      }
    }
    
    return thispassSVJetClean;
  }

  std::vector<bool> preSelSV(const std::vector<TLorentzVector> &svLvecVec, const AnaConsts::SVAccRec& svsArr, const std::vector<TLorentzVector> &selhardbLvecVec)
  {
    std::vector<bool> passSVPreSel;
    const float minAbsEta = svsArr.minAbsEta, maxAbsEta = svsArr.maxAbsEta, minPt = svsArr.minPt, maxPt = svsArr.maxPt;
    for ( int i = 0; i < svLvecVec.size(); i++ )
    {
      bool thispassSVPreSel = true;
      float persvpt = svLvecVec[i].Pt(), persveta = svLvecVec[i].Eta();
      bool thispassSVAcc =
         ( minAbsEta == -1 || fabs(persveta) >= minAbsEta )
      && ( maxAbsEta == -1 || fabs(persveta) < maxAbsEta )
      && (     minPt == -1 || persvpt >= minPt )
      && (     maxPt == -1 || persvpt < maxPt );
      bool thispassSVJetClean = passSVJetClean(svLvecVec[i], selhardbLvecVec);
      thispassSVPreSel = thispassSVAcc && thispassSVJetClean;
      //if ( thispassSVAcc && !thispassSVJetClean ){ std::cout <<  persvpt << "," << persveta << std::endl; }
      //if (thispassSVPreSel){ std::cout <<  persvpt << "," << persveta << std::endl; }
      passSVPreSel.push_back(thispassSVPreSel);
    }
    return passSVPreSel;
  }

  //soft b-jet selection
  std::vector<bool> passSoftBTag(const std::vector<int> sv_ntrk_vec, std::vector<float> sv_dxy_vec, std::vector<float> sv_dxyz_signif_vec, std::vector<float> sv_cos_dxyz_p_vec)
  {
    std::vector<bool> passSoftBTag;
    int size = sv_ntrk_vec.size();
    //if ( (size != sv_dxy_vec.size()) || (size != sv_dxyz_signif_vec.size()) || (size != sv_cos_dxyz_p_vec.size()) ) {  std::cout << "Bug!" << std::endl; }
    for ( int i = 0; i < size; i++ )
    {
      bool thisSoftBTag = 
         ( sv_ntrk_vec[i] >= AnaConsts::minSVnTrk )
      && ( sv_dxy_vec[i] < AnaConsts::maxSVPVdxy )
      && ( sv_dxyz_signif_vec[i] > AnaConsts::minSVPVdxyzSignif )
      && ( sv_cos_dxyz_p_vec[i] > AnaConsts::minSVPVCosdiffAngle );
      passSoftBTag.push_back(thisSoftBTag);
    }
    return passSoftBTag;
  }

  int countSoftBJets(const std::vector<TLorentzVector> &svLvecVec, const std::vector<bool> & passSVPreSel, const std::vector<bool> &SoftBTag, std::vector<TLorentzVector> &selsoftbLvecVec)
  { 
    int cntSoftBJets = 0;
    for ( int i = 0; i < svLvecVec.size(); i++ )
    { 
      if ( passSVPreSel[i] && SoftBTag[i] )
      { 
        cntSoftBJets ++;
        selsoftbLvecVec.push_back(svLvecVec[i]);
      }
    }
    return cntSoftBJets;
  }
  //end of b selection

  //MVA calculator
  float calcbbdRAve(const std::vector<TLorentzVector> &mergedBJetsLvecVec)
  {
    //note, we only use first 4 hardest pt b jet candidate for ave dR calculation
    float bbdRAve = 0;
    std::vector<TLorentzVector> mergedBJetsLvecVec_copy (mergedBJetsLvecVec.begin(), mergedBJetsLvecVec.end());
    std::sort (mergedBJetsLvecVec_copy.begin(), mergedBJetsLvecVec_copy.end(), TLvecSortByPt);
    int n = mergedBJetsLvecVec_copy.size();
    for (int i = 0; i < n; i++)
    {
      std::cout << mergedBJetsLvecVec_copy[i].Pt() << ",";
    }
    std::cout << std::endl;
    return bbdRAve;
  }

  float calcbbdMMin(const std::vector<TLorentzVector> &mergedBJetsLvecVec)
  {
    //note, we all b jets candidates for min dm calculation
    float bbdMMin = 0;
    std::vector<TLorentzVector> mergedBJetsLvecVec_copy (mergedBJetsLvecVec.begin(), mergedBJetsLvecVec.end());
    std::sort (mergedBJetsLvecVec_copy.begin(), mergedBJetsLvecVec_copy.end(), TLvecSortByM);
    int n = mergedBJetsLvecVec_copy.size();
    //for (int i = 0; i < n; i++)
    //{
    //  std::cout << mergedBJetsLvecVec_copy[i].M() << ",";
    //}
    //std::cout << std::endl;
    //float bbdMMin = std::abs ( mergedBJetsLvecVec_copy[1].M() - mergedBJetsLvecVec_copy[0].M() );
    //for (int i = 2 ; i != n ; i++)
    //{
      //bbdMMin = Math.min(bbdMMin, a[i]-a[i-1]);
    //}
    return bbdMMin;
  }
  float calcHHt(const std::vector<TLorentzVector> &mergedBJetsLvecVec)
  {
    float HHt = 0;
    for( int i = 0; i < mergedBJetsLvecVec.size(); i++)
    {
      HHt += (mergedBJetsLvecVec[i]).Pt();
    }
    return HHt;
  }
  //end of MVA calculator
}
