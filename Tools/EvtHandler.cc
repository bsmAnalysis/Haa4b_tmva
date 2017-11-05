#include "EvtHandler.h"

using namespace std;

//
EvtHandler::EvtHandler()
{
}

//
bool EvtHandler::initTree(TTree *t)
{
  if(t==0) return false;
  t_ = t;

  //event info
  t_->Branch("run",   &evSummary_.run,   "run/I");
  t_->Branch("lumi",  &evSummary_.lumi,  "lumi/I");
  t_->Branch("event", &evSummary_.event, "event/L");

  //trigger
  t_->Branch("hasTrigger",  &evSummary_.hasTrigger,  "hasTrigger/O");
  t_->Branch("triggerType", &evSummary_.triggerType, "triggerType/I");

  //muon
  t_->Branch("mn",         &evSummary_.mn,        "mn/I");
  t_->Branch("mn_px",      evSummary_.mn_px,      "mn_px[mn]/F");
  t_->Branch("mn_py",      evSummary_.mn_py,      "mn_py[mn]/F");
  t_->Branch("mn_pz",      evSummary_.mn_pz,      "mn_pz[mn]/F");
  t_->Branch("mn_en",      evSummary_.mn_en,      "mn_en[mn]/F");
  t_->Branch("mn_passId",  evSummary_.mn_passId,  "mn_passId[mn]/O");
  t_->Branch("mn_passIso", evSummary_.mn_passIso, "mn_passIso[mn]/O");

  //electron
  t_->Branch("en",         &evSummary_.en,        "en/I");
  t_->Branch("en_px",      evSummary_.en_px,      "en_px[en]/F");
  t_->Branch("en_py",      evSummary_.en_py,      "en_py[en]/F");
  t_->Branch("en_pz",      evSummary_.en_pz,      "en_pz[en]/F");
  t_->Branch("en_en",      evSummary_.en_en,      "en_en[en]/F");
  t_->Branch("en_passId",  evSummary_.en_passId,  "en_passId[en]/O");
  t_->Branch("en_passIso", evSummary_.en_passIso, "en_passIso[en]/O"); 

  //jet (ak4PFJetsCHS)
  t_->Branch("jet",       &evSummary_.jet,      "jet/I");
  t_->Branch("jet_px",    evSummary_.jet_px,    "jet_px[jet]/F");
  t_->Branch("jet_py",    evSummary_.jet_py,    "jet_py[jet]/F");
  t_->Branch("jet_pz",    evSummary_.jet_pz,    "jet_pz[jet]/F");
  t_->Branch("jet_en",    evSummary_.jet_en,    "jet_en[jet]/F");
  t_->Branch("jet_btag0", evSummary_.jet_btag0, "jet_btag0[jet]/F");
  //t_->Branch("jet_PFLoose", evSummary_.jet_PFLoose,       "jet_PFLoose[jet]/O");
  
  //sv : Inclusive Secondary Vertices from slimmedSecondaryVertices
  t_->Branch("sv"            , &evSummary_.sv           , "sv/I" ) ;
  t_->Branch("sv_px"         , evSummary_.sv_px         , "sv_px[sv]/F" ) ;
  t_->Branch("sv_py"         , evSummary_.sv_py         , "sv_py[sv]/F" ) ;
  t_->Branch("sv_pz"         , evSummary_.sv_pz         , "sv_pz[sv]/F" ) ;
  t_->Branch("sv_en"         , evSummary_.sv_en         , "sv_en[sv]/F" ) ;
  t_->Branch("sv_ntrk"       , evSummary_.sv_ntrk       , "sv_ntrk[sv]/I" ) ;
  t_->Branch("sv_dxy"        , evSummary_.sv_dxy        , "sv_dxy[sv]/F" ) ;
  t_->Branch("sv_dxyz_signif", evSummary_.sv_dxyz_signif, "sv_dxyz_signif[sv]/F" ) ;
  t_->Branch("sv_cos_dxyz_p" , evSummary_.sv_cos_dxyz_p , "sv_cos_dxyz_p[sv]/F" ) ;

  //met
  t_->Branch("met_pt",  &evSummary_.met_pt,  "met_pt/F");
  t_->Branch("met_phi", &evSummary_.met_phi, "met_phi/F");

  return true;
}

//
bool EvtHandler::attachToTree(TTree *t)
{
  if (t==0) return false;
  t_ = t;

  //event info
  t_->SetBranchAddress("run",       &evSummary_.run);
  t_->SetBranchAddress("lumi",      &evSummary_.lumi);
  t_->SetBranchAddress("event",       &evSummary_.event);

  //trigger
  t_->SetBranchAddress("hasTrigger",    &evSummary_.hasTrigger);
  t_->SetBranchAddress("triggerType",   &evSummary_.triggerType);

  //muon
  t_->SetBranchAddress("mn",            &evSummary_.mn);
  t_->SetBranchAddress("mn_px",           evSummary_.mn_px);
  t_->SetBranchAddress("mn_py",           evSummary_.mn_py);
  t_->SetBranchAddress("mn_pz",           evSummary_.mn_pz);
  t_->SetBranchAddress("mn_en",           evSummary_.mn_en);
  t_->SetBranchAddress("mn_passId",  evSummary_.mn_passId);
  t_->SetBranchAddress("mn_passIso",  evSummary_.mn_passIso);

  //electron
  t_->SetBranchAddress("en",            &evSummary_.en);
  t_->SetBranchAddress("en_px",           evSummary_.en_px);
  t_->SetBranchAddress("en_py",           evSummary_.en_py);
  t_->SetBranchAddress("en_pz",           evSummary_.en_pz);
  t_->SetBranchAddress("en_en",           evSummary_.en_en);
  t_->SetBranchAddress("en_passId", evSummary_.en_passId);
  t_->SetBranchAddress("en_passIso", evSummary_.en_passIso);

  //jet (ak4PFJetsCHS)
  t_->SetBranchAddress("jet",           &evSummary_.jet);
  t_->SetBranchAddress("jet_px",          evSummary_.jet_px);
  t_->SetBranchAddress("jet_py",          evSummary_.jet_py);
  t_->SetBranchAddress("jet_pz",          evSummary_.jet_pz);
  t_->SetBranchAddress("jet_en",          evSummary_.jet_en);
  t_->SetBranchAddress("jet_btag0",         evSummary_.jet_btag0);
  //t_->SetBranchAddress("jet_PFLoose",       evSummary_.jet_PFLoose);

  //sv : Inclusive Secondary Vertices from slimmedSecondaryVertices
  t_->SetBranchAddress("sv"        , &evSummary_.sv         ) ;
  t_->SetBranchAddress("sv_px"       , evSummary_.sv_px       ) ;
  t_->SetBranchAddress("sv_py"       , evSummary_.sv_py       ) ;
  t_->SetBranchAddress("sv_pz"       , evSummary_.sv_pz       ) ;
  t_->SetBranchAddress("sv_en"       , evSummary_.sv_en       ) ;
  t_->SetBranchAddress("sv_ntrk"     , evSummary_.sv_ntrk       ) ;
  t_->SetBranchAddress("sv_dxy"      , evSummary_.sv_dxy      ) ;
  t_->SetBranchAddress("sv_dxyz_signif"  , evSummary_.sv_dxyz_signif  ) ;
  t_->SetBranchAddress("sv_cos_dxyz_p"   , evSummary_.sv_cos_dxyz_p   ) ;

  //met
  t_->SetBranchAddress("met_pt",          &evSummary_.met_pt);
  t_->SetBranchAddress("met_phi",         &evSummary_.met_phi);

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

//
void EvtHandler::fillTree()
{
  if(t_) t_->Fill();
}

//
EvtHandler::~EvtHandler()
{
}
