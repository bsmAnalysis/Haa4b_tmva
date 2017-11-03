#include "customize.h"

namespace AnaFunctions
{
  bool jetPassCuts(const TLorentzVector& jet, const AnaConsts::AccRec& jetCutsArr)
  {
    const double minAbsEta = jetCutsArr.minAbsEta, maxAbsEta = jetCutsArr.maxAbsEta, minPt = jetCutsArr.minPt, maxPt = jetCutsArr.maxPt;
    double perjetpt = jet.Pt(), perjeteta = jet.Eta();
    return  ( minAbsEta == -1 || fabs(perjeteta) >= minAbsEta )
      && ( maxAbsEta == -1 || fabs(perjeteta) < maxAbsEta )
      && (     minPt == -1 || perjetpt >= minPt )
      && (     maxPt == -1 || perjetpt < maxPt );
  }       

  int countJets(const std::vector<TLorentzVector> &inputJets, const AnaConsts::AccRec& jetCutsArr)
  {
    int cntNJets =0;
    for(unsigned int ij=0; ij<inputJets.size(); ij++){
      if(jetPassCuts(inputJets[ij], jetCutsArr)) cntNJets ++;
    }
    return cntNJets;
  }

  int countCSVS(const std::vector<TLorentzVector> &inputJets, const std::vector<double> &inputCSVS, const double cutCSVS, const AnaConsts::AccRec& jetCutsArr)
  {
    const double minAbsEta = jetCutsArr.minAbsEta, maxAbsEta = jetCutsArr.maxAbsEta, minPt = jetCutsArr.minPt, maxPt = jetCutsArr.maxPt;
    int cntNJets =0;
    for(unsigned int ij=0; ij<inputJets.size(); ij++){
      if( !jetPassCuts(inputJets[ij], jetCutsArr) ) continue;
      if( std::isnan(inputCSVS[ij]) ) continue;
      if( inputCSVS[ij] > cutCSVS ) cntNJets ++;
    }
    return cntNJets;
  }

  std::vector<double> calcDPhi(const std::vector<TLorentzVector> &inputJets, const double metphi, const int nDPhi, const AnaConsts::AccRec& jetCutsArr)
  {
    const double minAbsEta = jetCutsArr.minAbsEta, maxAbsEta = jetCutsArr.maxAbsEta, minPt = jetCutsArr.minPt, maxPt = jetCutsArr.maxPt;
    int cntNJets =0;
    std::vector<double> outDPhiVec(nDPhi, 999);
    for(unsigned int ij=0; ij<inputJets.size(); ij++){
      if( !jetPassCuts(inputJets[ij], jetCutsArr) ) continue;
      if( cntNJets < nDPhi ){
        double perDPhi = fabs(TVector2::Phi_mpi_pi( inputJets[ij].Phi() - metphi ));
        outDPhiVec[cntNJets] = perDPhi;
      }
      cntNJets ++;
    }
    return outDPhiVec;
  }

  double calcDeltaT(unsigned int pickedJetIdx, const std::vector<TLorentzVector> &inputJets, const AnaConsts::AccRec& jetCutsArr)
  {
    double deltaT = 0;
    double jres = 0.1;
    double sum = 0.0;
    for(unsigned int ij=0; ij<inputJets.size(); ij++)
    {
      if( ij == pickedJetIdx ) continue;
      if( !jetPassCuts(inputJets.at(ij), jetCutsArr) ) continue;
      sum = sum + ( inputJets.at(pickedJetIdx).Px()*inputJets.at(ij).Py() - inputJets.at(ij).Px()*inputJets.at(pickedJetIdx).Py() ) * ( inputJets.at(pickedJetIdx).Px()*inputJets.at(ij).Py() - inputJets.at(ij).Px()*inputJets.at(pickedJetIdx).Py() );
    }
    deltaT = jres*sqrt(sum)/inputJets.at(pickedJetIdx).Pt();

    return deltaT;
  }

  std::vector<double> calcDPhiN(const std::vector<TLorentzVector> &inputJets, const TLorentzVector &metLVec, const int nDPhi, const AnaConsts::AccRec& jetCutsArr)
  {
    int cntNJets =0;
    std::vector<double> outDPhiVec(nDPhi, 999);
    for(unsigned int ij=0; ij<inputJets.size(); ij++){
      if( !jetPassCuts(inputJets.at(ij), jetCutsArr) ) continue;
      if( cntNJets < nDPhi ){
        double perDphi = std::abs(TVector2::Phi_mpi_pi( inputJets.at(ij).Phi() - metLVec.Phi() ));
        double dT = calcDeltaT(ij, inputJets, jetCutsArr);
        if( dT/metLVec.Pt()>=1.0 ) outDPhiVec[cntNJets] = perDphi/(TMath::Pi()/2.0);
        else outDPhiVec[cntNJets] = perDphi/std::asin(dT/metLVec.Pt());
      }
      cntNJets ++; 
    }
    return outDPhiVec;
  }

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

  int countMus(const std::vector<TLorentzVector> &muLvecVec, const std::vector<bool> &passmuId, const std::vector<bool> &passmuIso, const AnaConsts::MuIsoAccRec& musArr)
  {
    int cntNMus = 0;
    for (unsigned int im = 0; im < muLvecVec.size(); im++)
    {
      if (passMu(muLvecVec[im], passmuId[im],  passmuIso[im], musArr)) cntNMus ++;
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

  int countEls(const std::vector<TLorentzVector> &elLvecVec, const std::vector<bool> &passelId, const std::vector<bool> &passelIso, const AnaConsts::ElIsoAccRec& elsArr)
  {
    int cntNEls = 0;
    for (unsigned int ie = 0; ie < elLvecVec.size(); ie++)
    {
      if (passEl(elLvecVec[ie], passelId[ie], passelIso[ie], elsArr)) cntNEls ++;
    }
    return cntNEls;
  }
  //end electron

  // cntNJetsVec stores number of jets counters from tightest requirement to loosest requirement.
  // cutCSVS is the CSV cut value
  void preparecntNJets(const std::vector<TLorentzVector> &inijetsLVec, const std::vector<double> &inirecoJetsBtag, const double cutCSVS, std::vector<int> &cntNJetsVec, std::vector<int> &cntNbJetsVec)
  {
    cntNJetsVec.clear(); cntNbJetsVec.clear();
    int cntNJetsPt50Eta24 = countJets(inijetsLVec, AnaConsts::pt50Eta24Arr);
    int cntNJetsPt30Eta24 = countJets(inijetsLVec, AnaConsts::pt30Eta24Arr);
    int cntNJetsPt30      = countJets(inijetsLVec, AnaConsts::pt30Arr);
    cntNJetsVec.push_back(cntNJetsPt50Eta24);
    cntNJetsVec.push_back(cntNJetsPt30Eta24);
    cntNJetsVec.push_back(cntNJetsPt30);

    int cntCSVS = countCSVS(inijetsLVec, inirecoJetsBtag, cutCSVS, AnaConsts::bTagArr);
    cntNbJetsVec.push_back(cntCSVS);
  }

  void preparecalcDPhi(const std::vector<TLorentzVector> &inijetsLVec, const double metphi, std::vector<double> &outDPhiVec)
  {
    outDPhiVec.clear();
    outDPhiVec = calcDPhi(inijetsLVec, metphi, 3, AnaConsts::dphiArr);
  }

  void prepareForNtupleReader()
  {
    using namespace AnaConsts;
    activatedBranchNames.insert(activatedBranchNames_DataOnly.begin(), activatedBranchNames_DataOnly.end());
  }

  double calcHT(const std::vector<TLorentzVector> &inputJets, const AnaConsts::AccRec& jetCutsArr)
  {
    const double minAbsEta = jetCutsArr.minAbsEta, maxAbsEta = jetCutsArr.maxAbsEta, minPt = jetCutsArr.minPt, maxPt = jetCutsArr.maxPt;

    double ht = 0;
    for(unsigned int ij=0; ij<inputJets.size(); ij++)
    {
      double perjetpt = inputJets[ij].Pt(), perjeteta = inputJets[ij].Eta();
      if(   ( minAbsEta == -1 || fabs(perjeteta) >= minAbsEta )
          && ( maxAbsEta == -1 || fabs(perjeteta) < maxAbsEta )
          && (     minPt == -1 || perjetpt >= minPt )
          && (     maxPt == -1 || perjetpt < maxPt ) )
      {
        ht += perjetpt;
      }
    }
    return ht;
  }

  TLorentzVector calcMHT(const std::vector<TLorentzVector> &inputJets, const AnaConsts::AccRec& jetCutsArr)
  {
    const double minAbsEta = jetCutsArr.minAbsEta, maxAbsEta = jetCutsArr.maxAbsEta, minPt = jetCutsArr.minPt, maxPt = jetCutsArr.maxPt;

    TLorentzVector mhtLVec;
    for(unsigned int ij=0; ij<inputJets.size(); ij++)
    {
      double perjetpt = inputJets[ij].Pt(), perjeteta = inputJets[ij].Eta();
      if(   ( minAbsEta == -1 || fabs(perjeteta) >= minAbsEta )
          && ( maxAbsEta == -1 || fabs(perjeteta) < maxAbsEta )
          && (     minPt == -1 || perjetpt >= minPt )
          && (     maxPt == -1 || perjetpt < maxPt ) )
      {
        TLorentzVector tmpLVec;
        tmpLVec.SetPtEtaPhiM( inputJets[ij].Pt(), 0, inputJets[ij].Phi(), 0 );
        mhtLVec -= tmpLVec;
      }
    }
    return mhtLVec;
  }

  bool passBaseline()
  {
    return true;
  }

  int jetLepdRMatch(const TLorentzVector& lep, const std::vector<TLorentzVector>& jetsLVec, const double jldRMax)
  {
    double dRmin = 999.0;
    int minJMatch = -1;

    for(int iJet = 0; iJet < jetsLVec.size(); ++iJet)
    {
      double dR = ROOT::Math::VectorUtil::DeltaR(jetsLVec[iJet], lep);
      if(dR < dRmin)
      {
        dRmin = dR;
        minJMatch = iJet;
      }
    }
    if(dRmin < jldRMax) return minJMatch;
    else                return -1;
  }
}
