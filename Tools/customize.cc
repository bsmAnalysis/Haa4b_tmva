#include "customize.h"

namespace AnaFunctions
{
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
    float dphi = metLvec.Phi() - lepLvec.Phi();
    while ( dphi > TMath::Pi() )
    {
      dphi = dphi - 2 * TMath::Pi();
    }
    while ( dphi < -TMath::Pi() )
    {
      dphi = dphi + 2 * TMath::Pi();
    }
    float mtw = std::sqrt ( 2.0 * metLvec.Pt() * lepLvec.Pt() * ( 1.0 - std::cos( dphi ) ) );
    return mtw;
  }
  //end mtw

  //jet pre-selection (for hard b jet, pt>20)
  std::vector<bool> preSelJet(const std::vector<TLorentzVector> &jetLvecVec, const AnaConsts::JetAccRec& jetsArr, const std::vector<TLorentzVector> &selmuLvecVec, const std::vector<TLorentzVector> &selelLvecVec)
  {
    std::vector<bool> passJetPreSel;
    for ( int i = 0; i < jetLvecVec.size(); i++ )
    {
      bool thispassJetPreSel =  true;

      passJetPreSel.push_back(thispassJetPreSel);
    }
    return passJetPreSel;
  }

  //hard b-jet selection
  int countHardBJets(const std::vector<TLorentzVector> &jetLvecVec, const std::vector<bool> & passJetPreSel, const std::vector<bool> &passBTag, std::vector<TLorentzVector> &selbjetLvecVec)
  {
    int cntHardBJets = 0;
    for ( int i = 0; i < jetLvecVec.size(); i++ )
    {
      if ( passJetPreSel[i] && passBTag[i] )
      {
        cntHardBJets ++;
        selbjetLvecVec.push_back(jetLvecVec[i]);
      }
    }
    return cntHardBJets;
  }
}
