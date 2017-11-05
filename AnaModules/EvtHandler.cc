#include "EvtHandler.h"

using namespace std;

//
EvtHandler::EvtHandler()
{
}

//
bool EvtHandler::attachToTree(TTree *t)
{
  if ( t == 0 ) return false;
  ti = t;

  //event info
  ti->SetBranchAddress("run",       &evSummary_.run);
  ti->SetBranchAddress("lumi",      &evSummary_.lumi);
  ti->SetBranchAddress("event",       &evSummary_.event);

  //trigger
  ti->SetBranchAddress("hasTrigger",    &evSummary_.hasTrigger);
  ti->SetBranchAddress("triggerType",   &evSummary_.triggerType);

  //muon
  ti->SetBranchAddress("mn",            &evSummary_.mn);
  ti->SetBranchAddress("mn_px",           evSummary_.mn_px);
  ti->SetBranchAddress("mn_py",           evSummary_.mn_py);
  ti->SetBranchAddress("mn_pz",           evSummary_.mn_pz);
  ti->SetBranchAddress("mn_en",           evSummary_.mn_en);
  ti->SetBranchAddress("mn_passId",  evSummary_.mn_passId);
  ti->SetBranchAddress("mn_passIso",  evSummary_.mn_passIso);

  //electron
  ti->SetBranchAddress("en",            &evSummary_.en);
  ti->SetBranchAddress("en_px",           evSummary_.en_px);
  ti->SetBranchAddress("en_py",           evSummary_.en_py);
  ti->SetBranchAddress("en_pz",           evSummary_.en_pz);
  ti->SetBranchAddress("en_en",           evSummary_.en_en);
  ti->SetBranchAddress("en_passId", evSummary_.en_passId);
  ti->SetBranchAddress("en_passIso", evSummary_.en_passIso);

  //jet (ak4PFJetsCHS)
  ti->SetBranchAddress("jet",           &evSummary_.jet);
  ti->SetBranchAddress("jet_px",          evSummary_.jet_px);
  ti->SetBranchAddress("jet_py",          evSummary_.jet_py);
  ti->SetBranchAddress("jet_pz",          evSummary_.jet_pz);
  ti->SetBranchAddress("jet_en",          evSummary_.jet_en);
  ti->SetBranchAddress("jet_btag0",         evSummary_.jet_btag0);
  //ti->SetBranchAddress("jet_PFLoose",       evSummary_.jet_PFLoose);

  //sv : Inclusive Secondary Vertices from slimmedSecondaryVertices
  ti->SetBranchAddress("sv"        , &evSummary_.sv         ) ;
  ti->SetBranchAddress("sv_px"       , evSummary_.sv_px       ) ;
  ti->SetBranchAddress("sv_py"       , evSummary_.sv_py       ) ;
  ti->SetBranchAddress("sv_pz"       , evSummary_.sv_pz       ) ;
  ti->SetBranchAddress("sv_en"       , evSummary_.sv_en       ) ;
  ti->SetBranchAddress("sv_ntrk"     , evSummary_.sv_ntrk       ) ;
  ti->SetBranchAddress("sv_dxy"      , evSummary_.sv_dxy      ) ;
  ti->SetBranchAddress("sv_dxyz_signif"  , evSummary_.sv_dxyz_signif  ) ;
  ti->SetBranchAddress("sv_cos_dxyz_p"   , evSummary_.sv_cos_dxyz_p   ) ;

  //met
  ti->SetBranchAddress("met_pt",          &evSummary_.met_pt);
  ti->SetBranchAddress("met_phi",         &evSummary_.met_phi);

  return true;
}


//
void EvtHandler::resetStruct()
{
  evSummary_.run=0;
  evSummary_.lumi=0;
  evSummary_.event=0;
  evSummary_.mn=0;
  evSummary_.en=0;
  evSummary_.jet=0;
  evSummary_.sv=0;

  //vector clear
  //muon
  evSummary_.mn_px_vec.clear(); evSummary_.mn_py_vec.clear(); evSummary_.mn_pz_vec.clear(); evSummary_.mn_en_vec.clear();
  evSummary_.mn_passId_vec.clear(); evSummary_.mn_passIso_vec.clear();

  //electron
  evSummary_.en_px_vec.clear(); evSummary_.en_py_vec.clear(); evSummary_.en_pz_vec.clear(); evSummary_.en_en_vec.clear();
  evSummary_.en_passId_vec.clear(); evSummary_.en_passIso_vec.clear();

  //jet (ak4PFJetsCHS)
  evSummary_.jet_px_vec.clear(); evSummary_.jet_py_vec.clear(); evSummary_.jet_pz_vec.clear(); evSummary_.jet_en_vec.clear();
  evSummary_.jet_btag0_vec.clear();
  //evSummary_.jet_PFLoose_vec;

  //sv : Inclusive Secondary Vertices from slimmedSecondaryVertices
  evSummary_.sv_px_vec.clear(); evSummary_.sv_py_vec.clear(); evSummary_.sv_pz_vec.clear(); evSummary_.sv_en_vec.clear();
  evSummary_.sv_ntrk_vec.clear();
  evSummary_.sv_dxy_vec.clear(); evSummary_.sv_dxyz_signif_vec.clear(); evSummary_.sv_cos_dxyz_p_vec.clear();
}

//reformat

void EvtHandler::VecGenerator()
{
  //muon
  ArrToVec( evSummary_.mn, evSummary_.mn_px, evSummary_.mn_px_vec );
  ArrToVec( evSummary_.mn, evSummary_.mn_py, evSummary_.mn_py_vec );
  ArrToVec( evSummary_.mn, evSummary_.mn_pz, evSummary_.mn_pz_vec );
  ArrToVec( evSummary_.mn, evSummary_.mn_en, evSummary_.mn_en_vec );
  ArrToVec( evSummary_.mn, evSummary_.mn_passId, evSummary_.mn_passId_vec );
  ArrToVec( evSummary_.mn, evSummary_.mn_passIso, evSummary_.mn_passIso_vec );

  //electron
  ArrToVec( evSummary_.en, evSummary_.en_px, evSummary_.en_px_vec );
  ArrToVec( evSummary_.en, evSummary_.en_py, evSummary_.en_py_vec );
  ArrToVec( evSummary_.en, evSummary_.en_pz, evSummary_.en_pz_vec );
  ArrToVec( evSummary_.en, evSummary_.en_en, evSummary_.en_en_vec );
  ArrToVec( evSummary_.en, evSummary_.en_passId, evSummary_.en_passId_vec );
  ArrToVec( evSummary_.en, evSummary_.en_passIso, evSummary_.en_passIso_vec );

  //jet
  ArrToVec( evSummary_.jet, evSummary_.jet_px, evSummary_.jet_px_vec );
  ArrToVec( evSummary_.jet, evSummary_.jet_py, evSummary_.jet_py_vec );
  ArrToVec( evSummary_.jet, evSummary_.jet_pz, evSummary_.jet_pz_vec );
  ArrToVec( evSummary_.jet, evSummary_.jet_en, evSummary_.jet_en_vec );
  ArrToVec( evSummary_.jet, evSummary_.jet_btag0, evSummary_.jet_btag0_vec );

  //sv
  ArrToVec( evSummary_.sv, evSummary_.sv_px, evSummary_.sv_px_vec );
  ArrToVec( evSummary_.sv, evSummary_.sv_py, evSummary_.sv_py_vec );
  ArrToVec( evSummary_.sv, evSummary_.sv_pz, evSummary_.sv_pz_vec );
  ArrToVec( evSummary_.sv, evSummary_.sv_en, evSummary_.sv_en_vec );
  ArrToVec( evSummary_.sv, evSummary_.sv_ntrk, evSummary_.sv_ntrk_vec );
  ArrToVec( evSummary_.sv, evSummary_.sv_dxy, evSummary_.sv_dxy_vec );
  ArrToVec( evSummary_.sv, evSummary_.sv_dxyz_signif, evSummary_.sv_dxyz_signif_vec );
  ArrToVec( evSummary_.sv, evSummary_.sv_cos_dxyz_p, evSummary_.sv_cos_dxyz_p_vec );

  return ;
}

//
bool EvtHandler::initTree(TTree *t)
{
  if ( t == 0 ) return false;
  to = t;

  //event info
  to->Branch("run",   &evSummary_.run,   "run/I");
  to->Branch("lumi",  &evSummary_.lumi,  "lumi/I");
  to->Branch("event", &evSummary_.event, "event/L");

  //trigger
  to->Branch("hasTrigger",  &evSummary_.hasTrigger,  "hasTrigger/O");
  to->Branch("triggerType", &evSummary_.triggerType, "triggerType/I");

  //muon
  to->Branch("mn",         &evSummary_.mn,        "mn/I");
  to->Branch("mn_px_vec", &evSummary_.mn_px_vec);

  /*
  to->Branch("mn_px",      evSummary_.mn_px,      "mn_px[mn]/F");
  to->Branch("mn_py",      evSummary_.mn_py,      "mn_py[mn]/F");
  to->Branch("mn_pz",      evSummary_.mn_pz,      "mn_pz[mn]/F");
  to->Branch("mn_en",      evSummary_.mn_en,      "mn_en[mn]/F");
  to->Branch("mn_passId",  evSummary_.mn_passId,  "mn_passId[mn]/O");
  to->Branch("mn_passIso", evSummary_.mn_passIso, "mn_passIso[mn]/O");

  //electron
  to->Branch("en",         &evSummary_.en,        "en/I");
  to->Branch("en_px",      evSummary_.en_px,      "en_px[en]/F");
  to->Branch("en_py",      evSummary_.en_py,      "en_py[en]/F");
  to->Branch("en_pz",      evSummary_.en_pz,      "en_pz[en]/F");
  to->Branch("en_en",      evSummary_.en_en,      "en_en[en]/F");
  to->Branch("en_passId",  evSummary_.en_passId,  "en_passId[en]/O");
  to->Branch("en_passIso", evSummary_.en_passIso, "en_passIso[en]/O"); 

  //jet (ak4PFJetsCHS)
  to->Branch("jet",       &evSummary_.jet,      "jet/I");
  to->Branch("jet_px",    evSummary_.jet_px,    "jet_px[jet]/F");
  to->Branch("jet_py",    evSummary_.jet_py,    "jet_py[jet]/F");
  to->Branch("jet_pz",    evSummary_.jet_pz,    "jet_pz[jet]/F");
  to->Branch("jet_en",    evSummary_.jet_en,    "jet_en[jet]/F");
  to->Branch("jet_btag0", evSummary_.jet_btag0, "jet_btag0[jet]/F");
  //to->Branch("jet_PFLoose", evSummary_.jet_PFLoose,       "jet_PFLoose[jet]/O");
  
  //sv : Inclusive Secondary Vertices from slimmedSecondaryVertices
  to->Branch("sv"            , &evSummary_.sv           , "sv/I" ) ;
  to->Branch("sv_px"         , evSummary_.sv_px         , "sv_px[sv]/F" ) ;
  to->Branch("sv_py"         , evSummary_.sv_py         , "sv_py[sv]/F" ) ;
  to->Branch("sv_pz"         , evSummary_.sv_pz         , "sv_pz[sv]/F" ) ;
  to->Branch("sv_en"         , evSummary_.sv_en         , "sv_en[sv]/F" ) ;
  to->Branch("sv_ntrk"       , evSummary_.sv_ntrk       , "sv_ntrk[sv]/I" ) ;
  to->Branch("sv_dxy"        , evSummary_.sv_dxy        , "sv_dxy[sv]/F" ) ;
  to->Branch("sv_dxyz_signif", evSummary_.sv_dxyz_signif, "sv_dxyz_signif[sv]/F" ) ;
  to->Branch("sv_cos_dxyz_p" , evSummary_.sv_cos_dxyz_p , "sv_cos_dxyz_p[sv]/F" ) ;
  */
  //met
  to->Branch("met_pt",  &evSummary_.met_pt,  "met_pt/F");
  to->Branch("met_phi", &evSummary_.met_phi, "met_phi/F");

  return true;
}

//
void EvtHandler::fillTree()
{
  if ( to ) to->Fill();
}

//
EvtHandler::~EvtHandler()
{
}
