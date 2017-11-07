#include "baselineDef.h"
#include "TFile.h"
#include "TF1.h"

//**************************************************************************//
//                              BaselineVessel                              //
//**************************************************************************//

BaselineVessel::BaselineVessel(NTupleReader &tr_, const std::string specialization, const std::string filterString) : 
  tr(&tr_), spec(specialization)
{
  debug                 = false;
  passBaseline          = true;
  passSelPreMVA         = true;
  metLvec.SetPtEtaPhiM(0, 0, 0, 0);
  
  //what do you want to do when initializing class?

  //PredefineSpec();
}

// ===  FUNCTION  ============================================================
//         Name:  BaselineVessel::~BaselineVessel
//  Description:  
// ===========================================================================
BaselineVessel::~BaselineVessel() 
{
}
// -----  end of function BaselineVessel::~BaselineVessel  -----

void BaselineVessel::PreProcessing()
{
  //Muon
  //int mn = tr->getVar<int>("mn");
  //ArrayToVec( mn, "mn_px", & ( tr->getVar<float>("mn_px") ) ); ArrayToVec( mn, "mn_py", & ( tr->getVar<float>("mn_py") ) ); ArrayToVec( mn, "mn_pz", & ( tr->getVar<float>("mn_pz") ) ); ArrayToVec( mn, "mn_en", & ( tr->getVar<float>("mn_en") ) );
  std::vector<TLorentzVector> * mnLVec = new std::vector<TLorentzVector>();
  (* mnLVec) = ConstructVecLVec( tr->getVec<float>("mn_px_vec"), tr->getVec<float>("mn_py_vec"), tr->getVec<float>("mn_pz_vec"), tr->getVec<float>("mn_en_vec") );
  //(* mnLVec) = ConstructVecLVec( mn, &(tr->getVar<float>("mn_px")), &(tr->getVar<float>("mn_py")), &(tr->getVar<float>("mn_pz")), &(tr->getVar<float>("mn_en")) );
  tr->registerDerivedVec("mnLVec", mnLVec);
  //Muon id and iso
  //ArrayToVec( mn, "mn_passId", & ( tr->getVar<bool>("mn_passId") ) ); ArrayToVec( mn, "mn_passIso", & ( tr->getVar<bool>("mn_passIso") ) );

  //Electron
  //int en = tr->getVar<int>("en");
  //ArrayToVec( en, "en_px", & ( tr->getVar<float>("en_px") ) ); ArrayToVec( en, "en_py", & ( tr->getVar<float>("en_py") ) ); ArrayToVec( en, "en_pz", & ( tr->getVar<float>("en_pz") ) ); ArrayToVec( en, "en_en", & ( tr->getVar<float>("en_en") ) );
  std::vector<TLorentzVector> * enLVec = new std::vector<TLorentzVector>();
  (* enLVec) = ConstructVecLVec( tr->getVec<float>("en_px_vec"), tr->getVec<float>("en_py_vec"), tr->getVec<float>("en_pz_vec"), tr->getVec<float>("en_en_vec") );
  //(* enLVec) = ConstructVecLVec( en, &(tr->getVar<float>("en_px")), &(tr->getVar<float>("en_py")), &(tr->getVar<float>("en_pz")), &(tr->getVar<float>("en_en")) );
  tr->registerDerivedVec("enLVec", enLVec);
  //Electron id and iso
  //ArrayToVec( en, "en_passId", & ( tr->getVar<bool>("en_passId") ) ); ArrayToVec( en, "en_passIso", & ( tr->getVar<bool>("en_passIso") ) );
  
  //jet
  //int jet = tr->getVar<int>("jet");
  //ArrayToVec( jet, "jet_px", & ( tr->getVar<float>("jet_px") ) ); ArrayToVec( jet, "jet_py", & ( tr->getVar<float>("jet_py") ) ); ArrayToVec( jet, "jet_pz", & ( tr->getVar<float>("jet_pz") ) ); ArrayToVec( jet, "jet_en", & ( tr->getVar<float>("jet_en") ) );
  std::vector<TLorentzVector> * jetLVec = new std::vector<TLorentzVector>();
  (* jetLVec) = ConstructVecLVec( tr->getVec<float>("jet_px_vec"), tr->getVec<float>("jet_py_vec"), tr->getVec<float>("jet_pz_vec"), tr->getVec<float>("jet_en_vec") );
  //(* jetLVec) = ConstructVecLVec( jet, &(tr->getVar<float>("jet_px")), &(tr->getVar<float>("jet_py")), &(tr->getVar<float>("jet_pz")), &(tr->getVar<float>("jet_en")) );
  tr->registerDerivedVec("jetLVec", jetLVec);
  //to select a b jet with pt > 20
  //ArrayToVec( jet, "jet_PFLoose", & ( tr->getVar<bool>("jet_PFLoose") ) );
  //ArrayToVec( jet, "jet_btag0", & ( tr->getVar<float>("jet_btag0") ) );

  //sv
  //int sv = tr->getVar<int>("sv");
  //ArrayToVec( sv, "sv_px", & ( tr->getVar<float>("sv_px") ) ); ArrayToVec( sv, "sv_py", & ( tr->getVar<float>("sv_py") ) ); ArrayToVec( sv, "sv_pz", & ( tr->getVar<float>("sv_pz") ) ); ArrayToVec( sv, "sv_en", & ( tr->getVar<float>("sv_en") ) );
  std::vector<TLorentzVector> * svLVec = new std::vector<TLorentzVector>();
  (* svLVec) = ConstructVecLVec( tr->getVec<float>("sv_px_vec"), tr->getVec<float>("sv_py_vec"), tr->getVec<float>("sv_pz_vec"), tr->getVec<float>("sv_en_vec") );
  //(* svLVec) = ConstructVecLVec( sv, &(tr->getVar<float>("sv_px")), &(tr->getVar<float>("sv_py")), &(tr->getVar<float>("sv_pz")), &(tr->getVar<float>("sv_en")) );
  tr->registerDerivedVec("svLVec", svLVec);
  //to select a sv for soft b jet pt < 20
  //ArrayToVec( sv, "sv_ntrk"       , & ( tr->getVar<int>("sv_ntrk") ) );
  //ArrayToVec( sv, "sv_dxy"        , & ( tr->getVar<float>("sv_dxy") ) );
  //ArrayToVec( sv, "sv_dxyz_signif", & ( tr->getVar<float>("sv_dxyz_signif") ) );
  //ArrayToVec( sv, "sv_cos_dxyz_p" , & ( tr->getVar<float>("sv_cos_dxyz_p") ) );

  //fjet
  //int fjet = tr->getVar<int>("fjet");
  //ArrayToVec( fjet, "fjet_px" ); ArrayToVec( fjet, "fjet_py" ); ArrayToVec( fjet, "fjet_pz" ); ArrayToVec( fjet, "fjet_en" );
  //std::vector<TLorentzVector> * fjetLVec = new std::vector<TLorentzVector>();
  //(* fjetLVec) = ConstructVecLVec( tr->getVec<float>("fjet_px_vec"), tr->getVec<float>("fjet_py_vec"), tr->getVec<float>("fjet_pz_vec"), tr->getVec<float>("fjet_en_vec") );
  //tr->registerDerivedVec("fjetLVec", fjetLVec);

  return ;
}

void BaselineVessel::PassBaseline()
{
  //Initial value
  passBaseline = true;
  passSelPreMVA = true;

  //trigger go first
  //https://github.com/bsmAnalysis/BSMHiggs_fwk/blob/master/plugins/mainNtuplizer.cc#L613-L618
  bool passTriggerSel = TriggerSel( tr->getVar<int>("triggerType") );
  tr->registerDerivedVar("passTriggerSel", passTriggerSel);
  //end of trigger sel

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

  //MET cut
  metLvec.SetPtEtaPhiM(tr->getVar<float>("met_pt"), 0, tr->getVar<float>("met_phi"), 0);
  bool passMET = (metLvec.Pt() >= AnaConsts::defaultMETcut);
  tr->registerDerivedVar("passMET", passMET);
  //end MET

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
  //hard b jet, jet pre selection, acc and lepton clean
  std::vector<TLorentzVector> jetLvecVec = tr->getVec<TLorentzVector>("jetLVec");
  std::vector<bool> passJetPreSel = AnaFunctions::preSelJet(jetLvecVec, AnaConsts::jetsArr, selmuLvecVec, selelLvecVec);
  //hard b jet
  std::vector<TLorentzVector> selhardbLvecVec;
  int nhardbjets = AnaFunctions::countHardBJets(jetLvecVec, passJetPreSel, tr->getVec<float>("jet_btag0_vec"), selhardbLvecVec);
  tr->registerDerivedVar("nHardBJets", nhardbjets);
  //int nhardbjets_test = AnaFunctions::countHardBJets(jetLvecVec, passJetPreSel, tr->getVec<bool>("jet_PFLoose_vec"), selhardbLvecVec);
  //tr->registerDerivedVar("nHardBJets_Test", nhardbjets_test);
  bool passHardBJets = (nhardbjets >= AnaConsts::minNHardBJets);
  tr->registerDerivedVar("passHardBJets", passHardBJets);

  //soft b jet, jet pre selection, acc and lepton clean
  std::vector<TLorentzVector> svLvecVec = tr->getVec<TLorentzVector>("svLVec");
  std::vector<bool> passSVPreSel = AnaFunctions::preSelSV(svLvecVec, AnaConsts::svsArr, selhardbLvecVec);
  //soft b jet
  std::vector<bool> SoftBTag = AnaFunctions::passSoftBTag(tr->getVec<int>("sv_ntrk_vec"), tr->getVec<float>("sv_dxy_vec"), tr->getVec<float>("sv_dxyz_signif_vec"), tr->getVec<float>("sv_cos_dxyz_p_vec"));
  std::vector<TLorentzVector> selsoftbLvecVec;
  int nsoftbjets = AnaFunctions::countSoftBJets(svLvecVec, passSVPreSel, SoftBTag, selsoftbLvecVec);
  tr->registerDerivedVar("nSoftBJets", nsoftbjets);
  bool passAllBJets = ((nhardbjets + nsoftbjets) >= AnaConsts::minNAllBJets); //no upper limit!
  //bool passAllBJets = ( (nhardbjets + nsoftbjets) >= AnaConsts::minNAllBJets ) && ( (nhardbjets + nsoftbjets) <= AnaConsts::maxNAllBJets );
  tr->registerDerivedVar("passAllBJets", passAllBJets);
  //end b jets selection
  //done with pre mva selection

  //additional b requirement, greater than 4 b jets
  tr->registerDerivedVar("passQuaBCat", ((nhardbjets + nsoftbjets) >= 4) );

  //prepare for MVA variables, except for mtw
  //W = lepton + MET
  prepareWHMVA(selmuLvecVec, selelLvecVec, metLvec, selhardbLvecVec, selsoftbLvecVec, "_calcMVA");


  passSelPreMVA = passTriggerSel
               && passLeptonSel
               && passMET
               && passMtW
               && passHardBJets
               && passAllBJets;
  
  tr->registerDerivedVar("passSelPreMVA", passSelPreMVA);
  /*
  // Calculate number of jets and b-tagged jets
  tr->registerDerivedVar("passBaseline" + spec, passBaseline);
  if( debug ) std::cout<<"passBaseline : "<<passBaseline<<"  passBaseline : "<<passBaseline<<std::endl;
  */
} 

void BaselineVessel::operator()(NTupleReader& tr_)
{
  tr = &tr_;
  PreProcessing();
  PassBaseline();
}

// ===  FUNCTION  ============================================================
//         Name:  BaselineVessel::GetMHT
//  Description:  /* cursor */
// ===========================================================================

template<typename T> void BaselineVessel::ArrayToVec( int size, std::string name, const T* var )
{
  std::vector<T> * vec = new std::vector<T>();
  //if ( size == 0 ) { std::cout << "tag" << std::endl; }
  for (int i = 0; i < size; i++)
  {
    vec->push_back( *(var + i) );
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

std::vector<TLorentzVector> BaselineVessel::ConstructVecLVec( int size, const float* px, const float* py, const float* pz, const float* en )
{
  std::vector<TLorentzVector> VecLVec;
  for (int i = 0; i < size; i++)
  {
    TLorentzVector thisLVec;
    thisLVec.SetPxPyPzE( *(px + i), *(py + i), *(pz + i), *(en + i) );
    VecLVec.push_back( thisLVec );
  }
  return VecLVec;
}

bool BaselineVessel::TriggerSel( int TriggerBit )
{
  bool passTrigger = ( (TriggerBit >> 1 ) & 0x1 ) || ( (TriggerBit >> 4 ) & 0x1 );
  return passTrigger;
}

void BaselineVessel::prepareWHMVA( const std::vector<TLorentzVector>& selmuLvecVec, const std::vector<TLorentzVector>& selelLvecVec, const TLorentzVector& metLvec, const std::vector<TLorentzVector>& selhardbLvecVec, const std::vector<TLorentzVector>& selsoftbLvecVec, std::string MVATag)
{
  //merge lepton and b classes first
  std::vector<TLorentzVector> mergedLepLvecVec;
  mergedLepLvecVec.reserve( selmuLvecVec.size() + selelLvecVec.size() );
  mergedLepLvecVec.insert( mergedLepLvecVec.end(), selmuLvecVec.begin(), selmuLvecVec.end() );
  mergedLepLvecVec.insert( mergedLepLvecVec.end(), selelLvecVec.begin(), selelLvecVec.end() );

  std::vector<TLorentzVector> mergedBJetsLvecVec;
  mergedBJetsLvecVec.reserve( selhardbLvecVec.size() + selsoftbLvecVec.size() );
  mergedBJetsLvecVec.insert( mergedBJetsLvecVec.end(), selhardbLvecVec.begin(), selhardbLvecVec.end() );
  mergedBJetsLvecVec.insert( mergedBJetsLvecVec.end(), selsoftbLvecVec.begin(), selsoftbLvecVec.end() );

  //W boson related only
  float WpT = -1.0;
  bool validW = mergedLepLvecVec.size() == AnaConsts::nLepSel;
  TLorentzVector WLvec;
  if ( validW )
  { 
    WLvec = mergedLepLvecVec[0] + metLvec;
    WpT = WLvec.Pt(); 
  }

  //Higgs boson related only
  float Hmass = -1.0, HpT = -1.0;
  float bbdRAve = -1.0, bbdMMin = -1.0;
  float HHt = -1.0;
  bool validH = (selhardbLvecVec.size() >= AnaConsts::minNHardBJets) && (mergedBJetsLvecVec.size() >= AnaConsts::minNAllBJets);
  TLorentzVector HLvec;
  if ( validH )
  {
    for (int i = 0; i < mergedBJetsLvecVec.size(); i++)
    {
      HLvec += mergedBJetsLvecVec[i];
    }
    Hmass = HLvec.M();
    HpT = HLvec.Pt();
    //be careful!!! sort b collection with pt before we calculate the following variables
    std::vector<TLorentzVector> mergedBJetsLvecVec_copyPtSort (mergedBJetsLvecVec.begin(), mergedBJetsLvecVec.end());
    std::sort (mergedBJetsLvecVec_copyPtSort.begin(), mergedBJetsLvecVec_copyPtSort.end(), AnaFunctions::TLvecSortByPt);
    bbdRAve = AnaFunctions::calcbbdRAve(mergedBJetsLvecVec_copyPtSort);
    bbdMMin = AnaFunctions::calcbbdMMin(mergedBJetsLvecVec_copyPtSort);
    HHt = AnaFunctions::calcHHt(mergedBJetsLvecVec_copyPtSort);
  }

  //dr W and Higgs 
  float WHdR = -1.0;
  if ( validW && validH )
  {
    WHdR = AnaFunctions::DeltaR(WLvec, HLvec);
  }

  //May be useful
  int nBJets = mergedBJetsLvecVec.size();

  //reg W related only var
  tr->registerDerivedVar("WpT"     + MVATag, WpT);
  //reg H related only var
  tr->registerDerivedVar("Hmass"   + MVATag, Hmass);
  tr->registerDerivedVar("HpT"     + MVATag, HpT);
  tr->registerDerivedVar("bbdRAve" + MVATag, bbdRAve);
  tr->registerDerivedVar("bbdMMin" + MVATag, bbdMMin);
  tr->registerDerivedVar("HHt"     + MVATag, HHt);
  //reg W and H var
  tr->registerDerivedVar("WHdR"    + MVATag, WHdR);
  //MVA cat?
  tr->registerDerivedVar("nBJets"  + MVATag, nBJets);

  return ;
}

