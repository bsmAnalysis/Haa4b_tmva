#include "baselineDef.h"
#include "TFile.h"
#include "TF1.h"

//**************************************************************************//
//                              BaselineVessel                              //
//**************************************************************************//

BaselineVessel::BaselineVessel(NTupleReader &tr_, const std::string specialization, const std::string filterString) : 
  tr(&tr_), spec(specialization)
{

  bToFake               = 1;
  debug                 = false;
  incZEROtop            = false;
  UseLepCleanJet        = false;
  jetVecLabel           = "jetsLVec";
  CSVVecLabel           = "recoJetsBtag_0";
  METLabel              = "met";
  METPhiLabel           = "metphi";
  jetVecLabelAK8        = "ak8JetsLVec";
  qgLikehoodLabel       = "qgLikelihood";
  muonsFlagIDLabel      = "muonsFlagMedium";
  elesFlagIDLabel       = "elesFlagVeto";
  toptaggerCfgFile      = "TopTagger.cfg";
  doIsoTrksVeto         = true;
  doMuonVeto            = true;
  doEleVeto             = true;
  doMET                 = true;
  dodPhis               = true;
  passBaseline          = true;
  metLvec.SetPtEtaPhiM(0, 0, 0, 0);

  if(filterString.compare("fastsim") ==0) isfastsim = true; else isfastsim = false; 

  //Check if simplified tagger is called for
  std::string taggerLabel = "";
  const std::string aggBinLabel = "AggregatedBins";
  size_t loc = spec.find(aggBinLabel);
  if(loc != std::string::npos)
  {
    toptaggerCfgFile = "TopTagger_Simplified.cfg";
    taggerLabel = "AggBins";
    //Remove aggBinLabel from spec
    spec.erase(loc, aggBinLabel.size());
    //Strip any white space ledt in spec
    spec.erase(spec.begin(), std::find_if(spec.begin(), spec.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    spec.erase(std::find_if(spec.rbegin(), spec.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), spec.end());
  }

  if( !spec.empty() )
  {
    TString stripT = spec;
    TObjArray * objArr = stripT.Tokenize(" ");
    TObjString* firstObj = dynamic_cast<TObjString*>(objArr->At(0));
    firstSpec = firstObj->GetString().Data();
    std::cout<<"\nfirstSpec : "<<firstSpec.c_str()<<"  spec : "<<spec.c_str()<<"  isfastsim : "<<isfastsim<<std::endl<<std::endl;
  }
  firstSpec += taggerLabel;

  printOnce = false;

  PredefineSpec();
}

// ===  FUNCTION  ============================================================
//         Name:  BaselineVessel::~BaselineVessel
//  Description:  
// ===========================================================================
BaselineVessel::~BaselineVessel() 
{
}
// -----  end of function BaselineVessel::~BaselineVessel  -----

// ===  FUNCTION  ============================================================
//         Name:  BaselineVessel::PredefineSpec
//  Description:  
// ===========================================================================
bool BaselineVessel::PredefineSpec()
{

  if( spec.compare("noIsoTrksVeto") == 0)
  {
    doIsoTrksVeto = false;
  }
  else if( spec.compare("incZEROtop") == 0)
  {
    incZEROtop = true;
  }
  else if( spec.compare("hadtau") == 0)
  {
    doMuonVeto = false;
    doIsoTrksVeto = false;
    METLabel = "met_hadtau";
    METPhiLabel = "metphi_hadtau";
    jetVecLabel = "jetsLVec_hadtau";
    CSVVecLabel = "recoJetsBtag_0_hadtau";
  }
  else if( spec.compare("lostlept") == 0)
  {
    doMuonVeto = false;
    doEleVeto = false; 
    doIsoTrksVeto = false;
  }
  else if(spec.compare("Zinv") == 0 || spec.compare("Zinv1b") == 0 || spec.compare("Zinv2b") == 0 || spec.compare("Zinv3b") == 0 || spec.compare("ZinvJEUUp") == 0 || spec.compare("ZinvJEUDn") == 0 || spec.compare("ZinvMEUUp") == 0 || spec.compare("ZinvMEUDn") == 0) 
  {
    jetVecLabel = "jetsLVecLepCleaned";
    CSVVecLabel = "recoJetsBtag_0_LepCleaned";
    METLabel    = "cleanMetPt";
    METPhiLabel = "cleanMetPhi";
    doMuonVeto  = false;
    doEleVeto   = false;
    doIsoTrksVeto = false;
    if(spec.compare("Zinv1b") == 0)
    {
      CSVVecLabel = "cleanJetpt30ArrBTag1fake";
      bToFake = 1;
    }
    else if(spec.compare("Zinv2b") == 0)
    {
      CSVVecLabel = "cleanJetpt30ArrBTag2fake";
      bToFake = 1; // This is not a typo
    }
    else if(spec.compare("Zinv3b") == 0)
    {
      CSVVecLabel = "cleanJetpt30ArrBTag3fake";
      bToFake = 1; // This is not a typo
    }
    else if(spec.compare("ZinvJEUUp") == 0)
    {
      jetVecLabel = "jetLVecUp";
    }
    else if(spec.compare("ZinvJEUDn") == 0)
    {
      jetVecLabel = "jetLVecDn";
    }
    else if(spec.compare("ZinvMEUUp") == 0)
    {
      METLabel    = "metMEUUp";
    }
    else if(spec.compare("ZinvMEUDn") == 0)
    {
      METLabel    = "metMEUDn";
    }
  }
  else if(spec.compare("QCD") == 0)
  {
    doMET = false;
    dodPhis = false;
  }
  else if( spec.find("jecUp") != std::string::npos || spec.find("jecDn") != std::string::npos || spec.find("metMagUp") != std::string::npos || spec.find("metMagDn") != std::string::npos || spec.find("metPhiUp") != std::string::npos || spec.find("metPhiDn") != std::string::npos )
  {
    if( spec.find("jecUp") != std::string::npos )
    {
      jetVecLabel = "jetLVec_jecUp";
      CSVVecLabel = "recoJetsBtag_jecUp";
    }
    else if(spec.find("jecDn") != std::string::npos )
    {
      jetVecLabel = "jetLVec_jecDn";
      CSVVecLabel = "recoJetsBtag_jecDn";
    }
    else if(spec.find("metMagUp") != std::string::npos )
    {
      METLabel = "met_metMagUp";
    }
    else if(spec.find("metMagDn") != std::string::npos )
    {
      METLabel = "met_metMagDn";
    }
    else if(spec.find("metPhiUp") != std::string::npos )
    {
      METPhiLabel = "metphi_metPhiUp";
    }
    else if(spec.find("metPhiDn") != std::string::npos )
    {
      METPhiLabel = "metphi_metPhiDn";
    }
    if( spec.find("usegenmet") != std::string::npos )
    {
      METLabel = "genmet";
      METPhiLabel = "genmetphi";
    } 
  }
  else if( spec.compare("usegenmet") == 0 )
  {
    METLabel = "genmet";
    METPhiLabel = "genmetphi";
  }

  if( !printOnce )
  {
    printOnce = true;
    std::cout<<"spec : "<<spec.c_str()<<"  jetVecLabel : "<<jetVecLabel.c_str() <<"  CSVVecLabel : "<<CSVVecLabel.c_str() <<"  METLabel : "<<METLabel.c_str()<< std::endl;
  }  
  
  return true;
}
// -----  end of function BaselineVessel::PredefineSpec  -----

void BaselineVessel::PreProcessing()
{
  //sv
  int sv = tr->getVar<int>("sv");
  ArrayToVec( sv, "sv_px" ); ArrayToVec( sv, "sv_py" ); ArrayToVec( sv, "sv_pz" ); ArrayToVec( sv, "sv_en" );
  std::vector<TLorentzVector> * svLVec = new std::vector<TLorentzVector>();
  (* svLVec) = ConstructVecLVec( tr->getVec<float>("sv_px_vec"), tr->getVec<float>("sv_py_vec"), tr->getVec<float>("sv_pz_vec"), tr->getVec<float>("sv_en_vec") );
  tr->registerDerivedVec("svLVec", svLVec);
  //to select a sv for soft b jet pt < 20

  //jet
  int jet = tr->getVar<int>("jet");
  ArrayToVec( jet, "jet_px" ); ArrayToVec( jet, "jet_py" ); ArrayToVec( jet, "jet_pz" ); ArrayToVec( jet, "jet_en" );
  std::vector<TLorentzVector> * jetLVec = new std::vector<TLorentzVector>();
  (* jetLVec) = ConstructVecLVec( tr->getVec<float>("jet_px_vec"), tr->getVec<float>("jet_py_vec"), tr->getVec<float>("jet_pz_vec"), tr->getVec<float>("jet_en_vec") );
  tr->registerDerivedVec("jetLVec", jetLVec);
  //to select a b jet with pt > 20
  //ArrayToVec( jet, "jet_PFLoose" );

  //fjet
  //int fjet = tr->getVar<int>("fjet");
  //ArrayToVec( fjet, "fjet_px" ); ArrayToVec( fjet, "fjet_py" ); ArrayToVec( fjet, "fjet_pz" ); ArrayToVec( fjet, "fjet_en" );
  //std::vector<TLorentzVector> * fjetLVec = new std::vector<TLorentzVector>();
  //(* fjetLVec) = ConstructVecLVec( tr->getVec<float>("fjet_px_vec"), tr->getVec<float>("fjet_py_vec"), tr->getVec<float>("fjet_pz_vec"), tr->getVec<float>("fjet_en_vec") );
  //tr->registerDerivedVec("fjetLVec", fjetLVec);

  //Muon
  int mn = tr->getVar<int>("mn");
  ArrayToVec( mn, "mn_px" ); ArrayToVec( mn, "mn_py" ); ArrayToVec( mn, "mn_pz" ); ArrayToVec( mn, "mn_en" );
  std::vector<TLorentzVector> * mnLVec = new std::vector<TLorentzVector>();
  (* mnLVec) = ConstructVecLVec( tr->getVec<float>("mn_px_vec"), tr->getVec<float>("mn_py_vec"), tr->getVec<float>("mn_pz_vec"), tr->getVec<float>("mn_en_vec") );
  tr->registerDerivedVec("mnLVec", mnLVec);
  //Muon id and iso
  ArrayToVec( mn, "mn_passId" ); ArrayToVec( mn, "mn_passIso" );

  //Electron
  int en = tr->getVar<int>("en");
  ArrayToVec( en, "en_px" ); ArrayToVec( en, "en_py" ); ArrayToVec( en, "en_pz" ); ArrayToVec( en, "en_en" );
  std::vector<TLorentzVector> * enLVec = new std::vector<TLorentzVector>();
  (* enLVec) = ConstructVecLVec( tr->getVec<float>("en_px_vec"), tr->getVec<float>("en_py_vec"), tr->getVec<float>("en_pz_vec"), tr->getVec<float>("en_en_vec") );
  tr->registerDerivedVec("enLVec", enLVec);
  //Electron id and iso
  ArrayToVec( en, "en_passId" ); ArrayToVec( en, "en_passIso" );

  return ;
}

void BaselineVessel::PassBaseline()
{
  //Initial value
  passBaseline = true;

  //MET cut
  metLvec.SetPtEtaPhiM(tr->getVar<float>("met_pt"), 0, tr->getVar<float>("met_phi"), 0);
  bool passMET = (metLvec.Pt() >= AnaConsts::defaultMETcut);
  tr->registerDerivedVar("passMET", passMET);
  //end MET
  //lepton selection
  std::vector<TLorentzVector> selmuLvecVec;
  int nmus = AnaFunctions::countMus(tr->getVec<TLorentzVector>("mnLVec"), tr->getVec<bool>("mn_passId_vec"), tr->getVec<bool>("mn_passIso_vec"), AnaConsts::musArr, selmuLvecVec);
  tr->registerDerivedVar("nmus_CUT", nmus);
  std::vector<TLorentzVector> selelLvecVec;
  int nels = AnaFunctions::countEls(tr->getVec<TLorentzVector>("enLVec"), tr->getVec<bool>("en_passId_vec"), tr->getVec<bool>("en_passIso_vec"), AnaConsts::elsArr, selelLvecVec);
  tr->registerDerivedVar("nels_CUT", nels);

  bool passMusSel = (nmus == AnaConsts::nMusSel), passElsSel = (nels == AnaConsts::nElsSel);
  tr->registerDerivedVar("passMusSel", passMusSel); tr->registerDerivedVar("passElsSel", passElsSel);
  bool passLeptonSel = ( passMusSel && !passElsSel ) || ( !passMusSel && passElsSel );
  tr->registerDerivedVar("passLeptonSel", passLeptonSel);
  //end lepton selection
  //MtW cut, note, must done it after lepton selection! force to be 0 if no lepton selected
  float mtw = 0;
  if ( ( passMusSel && !passElsSel ) )
  {
    //std::cout << selmuLvecVec.at(0).Pt() << std::endl;
    mtw = AnaFunctions::calcMtW( metLvec, selmuLvecVec.at(0) );
  }
  else if ( ( !passMusSel && passElsSel ) )
  {
    //std::cout << selelLvecVec.at(0).Pt() << std::endl;
    mtw = AnaFunctions::calcMtW( metLvec, selelLvecVec.at(0) );
  }
  else mtw = 0;
  tr->registerDerivedVar("mtw", mtw);
  bool passMtW = ( mtw >= AnaConsts::minMtW ) && ( mtw < AnaConsts::maxMtW );
  tr->registerDerivedVar("passMtW", passMtW);
  //end MtW

  //b jets selection
  //jet pre selection, acc and lepton clean

  std::vector<TLorentzVector> selhardbLvecVec;
  int nhardbjets = 0;
  //AnaFunctions::countHardBJets(tr->getVec<TLorentzVector>("mnLVec"), tr->getVec<bool>("mn_passId_vec"), tr->getVec<bool>("mn_passIso_vec"), AnaConsts::musArr, selmuLvecVec);
  tr->registerDerivedVar("nHardBjets", nhardbjets);
  std::vector<TLorentzVector> selsoftbLvecVec;
  int nsoftbjets = 0;
  //AnaFunctions::countSoftBJets(tr->getVec<TLorentzVector>("enLVec"), tr->getVec<bool>("en_passId_vec"), tr->getVec<bool>("en_passIso_vec"), AnaConsts::elsArr, selelLvecVec);
  tr->registerDerivedVar("nSoftBJets", nsoftbjets);

  bool passHardBJets = nhardbjets >= AnaConsts::minNHardBJets;
  tr->registerDerivedVar("passHardBJets", passHardBJets);
  bool passAllBJets = ( (nhardbjets + nsoftbjets) >= AnaConsts::minNAllBJets ) && ( (nhardbjets + nsoftbjets) <= AnaConsts::maxNAllBJets );
  tr->registerDerivedVar("passAllBJets", passAllBJets);

  /*
  // Calculate number of jets and b-tagged jets
  int cntCSVS = AnaFunctions::countCSVS(tr->getVec<TLorentzVector>(jetVecLabel), tr->getVec<double>(CSVVecLabel), AnaConsts::cutCSVS, AnaConsts::bTagArr);
  int cntNJetsPt50Eta24 = AnaFunctions::countJets(tr->getVec<TLorentzVector>(jetVecLabel), AnaConsts::pt50Eta24Arr);
  int cntNJetsPt30Eta24 = AnaFunctions::countJets(tr->getVec<TLorentzVector>(jetVecLabel), AnaConsts::pt30Eta24Arr);
  int cntNJetsPt30      = AnaFunctions::countJets(tr->getVec<TLorentzVector>(jetVecLabel), AnaConsts::pt30Arr);

  // Calculate deltaPhi
  std::vector<double> * dPhiVec = new std::vector<double>();
  (*dPhiVec) = AnaFunctions::calcDPhi(tr->getVec<TLorentzVector>(jetVecLabel), metLVec.Phi(), 3, AnaConsts::dphiArr);

  // Pass lepton veto?
  bool passMuonVeto = (nMus == AnaConsts::nMusSel), passEleVeto = (nElectrons == AnaConsts::nElectronsSel);
  bool passLeptVeto = passMuonVeto && passEleVeto;
  if ( doMuonVeto && !passMuonVeto ){ passBaseline = false; }
  if ( doEleVeto && !passEleVeto ){ passBaseline = false; }

  if ( debug ) std::cout<<"nMus : "<<nMus<<"  nElectrons : "<<nElectrons<<"  passBaseline : "<<passBaseline<<std::endl;

  // Pass number of jets?
  bool passnJets = true;
  if( cntNJetsPt50Eta24 < AnaConsts::nJetsSelPt50Eta24 ){ passBaseline = false; passnJets = false; passBaselineNoLepVeto = false; }
  if( cntNJetsPt30Eta24 < AnaConsts::nJetsSelPt30Eta24 ){ passBaseline = false; passnJets = false; passBaselineNoLepVeto = false; }
  if( debug ) std::cout<<"cntNJetsPt50Eta24 : "<<cntNJetsPt50Eta24<<"  cntNJetsPt30Eta24 : "<<cntNJetsPt30Eta24<<"  cntNJetsPt30 : "<<cntNJetsPt30<<"  passBaseline : "<<passBaseline<<std::endl;

  // Pass deltaPhi?
  bool passdPhis = (dPhiVec->at(0) >= AnaConsts::dPhi0_CUT && dPhiVec->at(1) >= AnaConsts::dPhi1_CUT && dPhiVec->at(2) >= AnaConsts::dPhi2_CUT);
  if( dodPhis && !passdPhis ){ passBaseline = false; passBaselineNoLepVeto = false; }
  if( debug ) std::cout<<"dPhi0 : "<<dPhiVec->at(0)<<"  dPhi1 : "<<dPhiVec->at(1)<<"  dPhi2 : "<<dPhiVec->at(2)<<"  passBaseline : "<<passBaseline<<std::endl;

  // Pass number of b-tagged jets?
  bool passBJets = true;
  if( !( (AnaConsts::low_nJetsSelBtagged == -1 || cntCSVS >= AnaConsts::low_nJetsSelBtagged) && (AnaConsts::high_nJetsSelBtagged == -1 || cntCSVS < AnaConsts::high_nJetsSelBtagged ) ) ){ passBaseline = false; passBJets = false; passBaselineNoLepVeto = false; }
  if( debug ) std::cout<<"cntCSVS : "<<cntCSVS<<"  passBaseline : "<<passBaseline<<std::endl;

  // Pass the baseline MET requirement?
  bool passMET = (metLVec.Pt() >= AnaConsts::defaultMETcut);
  if( doMET && !passMET ){ passBaseline = false; passBaselineNoTagMT2 = false; passBaselineNoTag = false; passBaselineNoLepVeto = false; }
  if( debug ) std::cout<<"met : "<<tr->getVar<double>("met")<<"  defaultMETcut : "<<AnaConsts::defaultMETcut<<"  passBaseline : "<<passBaseline<<std::endl;

  // Pass the HT cut for trigger?
  double HT = AnaFunctions::calcHT(tr->getVec<TLorentzVector>(jetVecLabel), AnaConsts::pt30Eta24Arr);
  bool passHT = true;
  if( HT < AnaConsts::defaultHTcut ){ passHT = false; passBaseline = false; passBaselineNoTagMT2 = false; passBaselineNoTag = false; passBaselineNoLepVeto = false; }
  if( debug ) std::cout<<"HT : "<<HT<<"  defaultHTcut : "<<AnaConsts::defaultHTcut<<"  passHT : "<<passHT<<"  passBaseline : "<<passBaseline<<std::endl;

  bool passNoiseEventFilter = true;
  if( !passNoiseEventFilterFunc() ) { passNoiseEventFilter = false; passBaseline = false; passBaselineNoTagMT2 = false; passBaselineNoTag = false; passBaselineNoLepVeto = false; }
  if( debug ) std::cout<<"passNoiseEventFilterFunc : "<<passNoiseEventFilterFunc()<<"  passBaseline : "<<passBaseline<<std::endl;

  // pass the special filter for fastsim
  bool passFastsimEventFilter = true;
  if( !passFastsimEventFilterFunc() ) { passFastsimEventFilter = false; passBaseline = false; passBaselineNoTagMT2 = false; passBaselineNoTag = false; passBaselineNoLepVeto = false; }
  if( debug ) std::cout<<"passFastsimEventFilterFunc : "<<passFastsimEventFilterFunc()<<"  passBaseline : "<<passBaseline<<std::endl;
  */

  /*
  tr->registerDerivedVar("nMuons_CUT" + firstSpec, nMuons);
  tr->registerDerivedVar("nElectrons_CUT" + firstSpec, nElectrons);
  tr->registerDerivedVar("nIsoTrks_CUT" + firstSpec, nIsoTrks);
  tr->registerDerivedVar("cntNJetsPt50Eta24" + firstSpec, cntNJetsPt50Eta24);
  tr->registerDerivedVar("cntNJetsPt30Eta24" + firstSpec, cntNJetsPt30Eta24);
  tr->registerDerivedVec("dPhiVec" + firstSpec, dPhiVec);
  tr->registerDerivedVar("cntCSVS" + firstSpec, cntCSVS);
  tr->registerDerivedVar("cntNJetsPt30" + firstSpec, cntNJetsPt30);
  tr->registerDerivedVar("HT" + firstSpec, HT);

  tr->registerDerivedVar("passLeptVeto" + firstSpec, passLeptVeto);
  tr->registerDerivedVar("passMuonVeto" + firstSpec, passMuonVeto);
  tr->registerDerivedVar("passEleVeto" + firstSpec, passEleVeto);
  tr->registerDerivedVar("passIsoTrkVeto" + firstSpec, passIsoTrkVeto);
  tr->registerDerivedVar("passIsoLepTrkVeto" + firstSpec, passIsoLepTrkVeto);
  tr->registerDerivedVar("passIsoPionTrkVeto" + firstSpec, passIsoPionTrkVeto);
  tr->registerDerivedVar("passnJets" + firstSpec, passnJets);
  tr->registerDerivedVar("passdPhis" + firstSpec, passdPhis);
  tr->registerDerivedVar("passBJets" + firstSpec, passBJets);
  tr->registerDerivedVar("passMET" + firstSpec, passMET);
  tr->registerDerivedVar("passHT" + firstSpec, passHT);
  tr->registerDerivedVar("passNoiseEventFilter" + firstSpec, passNoiseEventFilter);
  tr->registerDerivedVar("passFastsimEventFilter" + firstSpec, passFastsimEventFilter);
  tr->registerDerivedVar("passBaseline" + firstSpec, passBaseline);

  if( debug ) std::cout<<"passBaseline : "<<passBaseline<<"  passBaseline : "<<passBaseline<<std::endl;
  */
} 

bool BaselineVessel::passNoiseEventFilterFunc()
{
  // According to https://twiki.cern.ch/twiki/bin/view/CMS/SUSRecommendationsICHEP16#Filters_to_be_applied,
  // "Do not apply filters to signal monte carlo (fastsim)"
  if( isfastsim ) return true;

  try
  {
    bool cached_rethrow = tr->getReThrow();
    tr->setReThrow(false);

    bool passDataSpec = true;
    if( tr->getVar<unsigned int>("run") >= 100000 ){ // hack to know if it's data or MC...
      int goodVerticesFilter = tr->getVar<int>("goodVerticesFilter");
      // new filters
      const int & globalTightHalo2016Filter = tr->getVar<int>("globalTightHalo2016Filter");
      bool passglobalTightHalo2016Filter = (&globalTightHalo2016Filter) != nullptr? tr->getVar<int>("globalTightHalo2016Filter") !=0 : true;

      int eeBadScFilter = tr->getVar<int>("eeBadScFilter");

      passDataSpec = goodVerticesFilter && eeBadScFilter && passglobalTightHalo2016Filter;
    }

    unsigned int hbheNoiseFilter = isfastsim? 1:tr->getVar<unsigned int>("HBHENoiseFilter");
    unsigned int hbheIsoNoiseFilter = isfastsim? 1:tr->getVar<unsigned int>("HBHEIsoNoiseFilter");
    int ecalTPFilter = tr->getVar<int>("EcalDeadCellTriggerPrimitiveFilter");

    int jetIDFilter = isfastsim? 1:tr->getVar<int>("looseJetID_NoLep");
    // new filters
    const unsigned int & BadPFMuonFilter = tr->getVar<unsigned int>("BadPFMuonFilter");
    bool passBadPFMuonFilter = (&BadPFMuonFilter) != nullptr? tr->getVar<unsigned int>("BadPFMuonFilter") !=0 : true;

    const unsigned int & BadChargedCandidateFilter = tr->getVar<unsigned int>("BadChargedCandidateFilter");
    bool passBadChargedCandidateFilter = (&BadChargedCandidateFilter) != nullptr? tr->getVar<unsigned int>("BadChargedCandidateFilter") !=0 : true;

    bool passMETratioFilter = tr->getVar<double>("calomet")!=0 ? tr->getVar<double>("met")/tr->getVar<double>("calomet") < 5 : true;

    tr->setReThrow(cached_rethrow);
    return passDataSpec && hbheNoiseFilter && hbheIsoNoiseFilter && ecalTPFilter && jetIDFilter && passBadPFMuonFilter && passBadChargedCandidateFilter && passMETratioFilter;
  }
  catch (std::string var)
  {
    if(tr->isFirstEvent()) 
    {
      printf("NTupleReader::getTupleObj(const std::string var):  Variable not found: \"%s\"!!!\n", var.c_str());
      printf("Running with PHYS14 Config\n");
    }
  }
  return true;
}

bool BaselineVessel::passFastsimEventFilterFunc()
{
  bool passFilter = true;

  if( isfastsim ){
    bool cached_rethrow = tr->getReThrow();
    tr->setReThrow(false);
    const std::vector<TLorentzVector> & genjetsLVec = tr->getVec<TLorentzVector>("genjetsLVec");
    const std::vector<TLorentzVector> & recoJetsLVec = tr->getVec<TLorentzVector>("jetsLVec");
    const std::vector<double> & recoJetschargedHadronEnergyFraction = tr->getVec<double>("recoJetschargedHadronEnergyFraction");

    if( recoJetschargedHadronEnergyFraction.size() != recoJetsLVec.size() ) std::cout<<"\nWARNING ... Non-equal recoJetschargedHadronEnergyFraction.size : "<<recoJetschargedHadronEnergyFraction.size()<<"  recoJetsLVec.size : "<<recoJetsLVec.size()<<std::endl<<std::endl;

    if( !recoJetsLVec.empty() && (&genjetsLVec) != nullptr )
    {
      for(unsigned int ij=0; ij<recoJetsLVec.size(); ij++)
      {
        //                if( !AnaFunctions::jetPassCuts(recoJetsLVec[ij], AnaConsts::pt20Eta25Arr) ) continue;
        //if( !AnaFunctions::jetPassCuts(recoJetsLVec[ij], AnaConsts::pt30Eta24Arr) ) continue;
        double mindeltaR = 999.0;
        int matchedgenJetsIdx = -1;
        for(unsigned int ig=0; ig<genjetsLVec.size(); ig++){
          double dR = recoJetsLVec[ij].DeltaR(genjetsLVec[ig]);
          if( mindeltaR > dR ){ mindeltaR = dR; matchedgenJetsIdx = (int)ig; }
        }
        if( matchedgenJetsIdx != -1 && mindeltaR > 0.3 && recoJetschargedHadronEnergyFraction[ij] < 0.1 ) passFilter = false;
      }
    }
    tr->setReThrow(cached_rethrow);
  }
  return passFilter;
}

void BaselineVessel::operator()(NTupleReader& tr_)
{
  tr = &tr_;
  PreProcessing();
  PassBaseline();
  //GetMHT();
  //GetLeptons();
  //GetRecoZ(81, 101);
}

// ===  FUNCTION  ============================================================
//         Name:  BaselineVessel::GetMHT
//  Description:  /* cursor */
// ===========================================================================
bool BaselineVessel::GetMHT() const
{
  // Calculate MHT
  TLorentzVector MHT(0, 0, 0, 0);
  double SumHT = 0.0; //Using jet > 30 , |eta| < 5
  for(auto &jet : tr->getVec<TLorentzVector>("jetsLVecLepCleaned"))
  {
    if (jet.Pt() >= 30)
    {
      MHT -= jet;
      SumHT += jet.Pt();
    }
  }
  tr->registerDerivedVar("MHT"+firstSpec, MHT.Pt());
  tr->registerDerivedVar("MHTPhi"+firstSpec, MHT.Phi());
  tr->registerDerivedVar("MHTSig"+firstSpec, MHT.Pt()/ sqrt(SumHT));
  tr->registerDerivedVar("METSig"+firstSpec, tr->getVar<double>(METLabel)/ sqrt(SumHT));
  return true;
}
// -----  end of function BaselineVessel::GetMHT  -----

// ===  FUNCTION  ============================================================
//         Name:  BaselineVessel::GetLeptons
//  Description:  
// ===========================================================================
bool BaselineVessel::GetLeptons() const
{

  return true;
}
// -----  end of function BaselineVessel::GetLeptons  -----


// ===  FUNCTION  ============================================================
//         Name:  BaselineVessel::GetRecoZ
//  Description:  
// ===========================================================================
bool BaselineVessel::GetRecoZ( const int zMassMin, const int zMassMax) const
{
  std::vector<TLorentzVector>* recoZVec = new std::vector<TLorentzVector>();
  std::map<unsigned int, std::pair<unsigned int, unsigned int> > *ZLepIdx = 
    new std::map<unsigned int, std::pair<unsigned int, unsigned int> >();

  GetRecoZ("cutMuVec"+firstSpec,"cutMuCharge"+firstSpec, recoZVec, ZLepIdx, zMassMin, zMassMax );
  GetRecoZ("cutEleVec"+firstSpec,"cutEleCharge"+firstSpec, recoZVec, ZLepIdx, zMassMin, zMassMax );

  tr->registerDerivedVec("recoZVec"+spec, recoZVec);
  tr->registerDerivedVec("ZLepIdx"+spec, ZLepIdx);
  return true;
}
// -----  end of function BaselineVessel::GetRecoZ  -----


// ===  FUNCTION  ============================================================
//         Name:  BaselineVessel::GetRecoZ
//  Description:  
// ===========================================================================
bool BaselineVessel::GetRecoZ(const std::string leptype, const std::string lepchg, 
    std::vector<TLorentzVector>* recoZVec ,
    std::map<unsigned int, std::pair<unsigned int, unsigned int> > *ZLepIdx,
    const int zMassMin, const int zMassMax) const
{
  
  const std::vector<TLorentzVector> & LepVec = tr->getVec<TLorentzVector>(leptype);
  const std::vector<int> & LepChg = tr->getVec<int>(lepchg);

  for(unsigned int i = 0; i < LepVec.size(); ++i)
  {
    for(unsigned int j = i; j < LepVec.size(); ++j)
    {
      double zm = (LepVec.at(i) + LepVec.at(j)).M();
      int sumchg = LepChg.at(i) + LepChg.at(j); 
      if (sumchg == 0 && zm > zMassMin && zm < zMassMax)
      {
        recoZVec->push_back((LepVec.at(i) + LepVec.at(j)));
        if (leptype.find("Mu") != std::string::npos)
        {
          ZLepIdx->insert(std::make_pair( recoZVec->size(), 
                std::make_pair(i, j)));
        }
        if (leptype.find("Ele") != std::string::npos) // offset by 100
        {
          ZLepIdx->insert(std::make_pair( recoZVec->size(), 
                std::make_pair(i+100, j+100)));
        }
      }
    }
  }
  return true;
}

void BaselineVessel::ArrayToVec( int size, std::string name )
{
  const float * arr_head = & ( tr->getVar<float>(name) );
  std::vector<float> * vec = new std::vector<float>();

  for (int i = 0; i < size; i++)
  {
    vec->push_back( *(arr_head + i) );
  }
  tr->registerDerivedVec( name + "_vec", vec);

  return ;
}

std::vector<TLorentzVector> BaselineVessel::ConstructVecLVec( std::vector<float> px, std::vector<float> py, std::vector<float> pz, std::vector<float> en )
{
  std::vector<TLorentzVector> VecLVec;
  for (int i = 0; i < px.size(); i++)
  {
    TLorentzVector thisLVec;
    thisLVec.SetPxPyPzE( px.at(i), py.at(i), pz.at(i), en.at(i) );
    VecLVec.push_back( thisLVec );
  }
  return VecLVec;
}
// -----  end of function BaselineVessel::GetRecoZ  -----
