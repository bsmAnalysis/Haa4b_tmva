#include "EvtHandler.h"

using namespace std;

//
DataEvtSummaryHandler::DataEvtSummaryHandler()
{
}

//
bool DataEvtSummaryHandler::initTree(TTree *t)
{
  if(t==0) return false;
  t_ = t;

  //event info
  t_->Branch("run",    	&evSummary_.run,      "run/I");
  t_->Branch("lumi",     	&evSummary_.lumi,       "lumi/I");
  t_->Branch("event",    	&evSummary_.event,      "event/L");
  
  t_->Branch("hasTrigger",   	&evSummary_.hasTrigger,   "hasTrigger/O");
  t_->Branch("triggerType",	&evSummary_.triggerType,  "triggerType/I");

  //primary vertex
  t_->Branch("nvtx",    	&evSummary_.nvtx,       "nvtx/I");
  t_->Branch("vtx_x",     &evSummary_.vtx_x,      "vtx_x/F");
  t_->Branch("vtx_y",     &evSummary_.vtx_y,      "vtx_y/F");
  t_->Branch("vtx_z",     &evSummary_.vtx_z,      "vtx_z/F");

  //generator level info
  //mc truth
  //muon
  t_->Branch("mn",          &evSummary_.mn,           "mn/I");
  t_->Branch("mn_px",         evSummary_.mn_px,           "mn_px[mn]/F");
  t_->Branch("mn_py",         evSummary_.mn_py,           "mn_py[mn]/F");
  t_->Branch("mn_pz",         evSummary_.mn_pz,           "mn_pz[mn]/F");
  t_->Branch("mn_en",         evSummary_.mn_en,           "mn_en[mn]/F");
  t_->Branch("mn_id",         evSummary_.mn_id,           "mn_id[mn]/I");
  t_->Branch("mn_type",         evSummary_.mn_type,         "mn_type[mn]/I");
  t_->Branch("mn_passId",   evSummary_.mn_passId,  "mn_passId[mn]/O");
  t_->Branch("mn_passIdLoose",   evSummary_.mn_passIdLoose,  "mn_passIdLoose[mn]/O");
  t_->Branch("mn_passSoftMuon",   evSummary_.mn_passSoftMuon,  "mn_passSoftMuon[mn]/O");
  t_->Branch("mn_passIso",   evSummary_.mn_passIso,  "mn_passIso[mn]/O");

  //electron
  t_->Branch("en",          &evSummary_.en,           "en/I");
  t_->Branch("en_px",         evSummary_.en_px,           "en_px[en]/F");
  t_->Branch("en_py",         evSummary_.en_py,           "en_py[en]/F");
  t_->Branch("en_pz",         evSummary_.en_pz,           "en_pz[en]/F");
  t_->Branch("en_en",         evSummary_.en_en,           "en_en[en]/F");
  t_->Branch("en_id",         evSummary_.en_id,           "en_id[en]/I");
  t_->Branch("en_passId",   evSummary_.en_passId,  "en_passId[en]/O");
  t_->Branch("en_passIdLoose",   evSummary_.en_passIdLoose,  "en_passIdLoose[en]/O"); 
  t_->Branch("en_passIso",   evSummary_.en_passIso,  "en_passIso[en]/O"); 

  //jet (ak4PFJetsCHS)
  t_->Branch("jet",           &evSummary_.jet,          "jet/I");
  t_->Branch("jet_px",        evSummary_.jet_px,          "jet_px[jet]/F");
  t_->Branch("jet_py",        evSummary_.jet_py,          "jet_py[jet]/F");
  t_->Branch("jet_pz",        evSummary_.jet_pz,          "jet_pz[jet]/F");
  t_->Branch("jet_en",        evSummary_.jet_en,          "jet_en[jet]/F");
  t_->Branch("jet_btag0",       evSummary_.jet_btag0,         "jet_btag0[jet]/F");
  t_->Branch("jet_mass",        evSummary_.jet_mass,        "jet_mass[jet]/F");
  t_->Branch("jet_area",        evSummary_.jet_area,        "jet_area[jet]/F");
  t_->Branch("jet_pu",        evSummary_.jet_pu,          "jet_pu[jet]/F");
  t_->Branch("jet_puId",        evSummary_.jet_puId,        "jet_puId[jet]/F");
  t_->Branch("jet_PFLoose",       evSummary_.jet_PFLoose,       "jet_PFLoose[jet]/O");
  t_->Branch("jet_PFTight",       evSummary_.jet_PFTight,       "jet_PFTight[jet]/O");
  t_->Branch("jet_partonFlavour",   evSummary_.jet_partonFlavour,     "jet_partonFlavour[jet]/I");
  t_->Branch("jet_hadronFlavour",   evSummary_.jet_hadronFlavour,     "jet_hadronFlavour[jet]/I");
  t_->Branch("jet_mother_id",     evSummary_.jet_mother_id,       "jet_mother_id[jet]/I");
  t_->Branch("jet_parton_px",     evSummary_.jet_parton_px,    "jet_parton_px[jet]/F");
  t_->Branch("jet_parton_py",     evSummary_.jet_parton_py,    "jet_parton_py[jet]/F");
  t_->Branch("jet_parton_pz",     evSummary_.jet_parton_pz,    "jet_parton_pz[jet]/F");
  t_->Branch("jet_parton_en",     evSummary_.jet_parton_en,    "jet_parton_en[jet]/F");
  t_->Branch("jet_genpt",       evSummary_.jet_genpt,         "jet_genpt[jet]/F");
  
  //sv : Inclusive Secondary Vertices from slimmedSecondaryVertices
  t_->Branch("sv"        , &evSummary_.sv        , "sv/I" ) ;
  t_->Branch("sv_px"       , evSummary_.sv_px      , "sv_px[sv]/F" ) ;
  t_->Branch("sv_py"       , evSummary_.sv_py      , "sv_py[sv]/F" ) ;
  t_->Branch("sv_pz"       , evSummary_.sv_pz      , "sv_pz[sv]/F" ) ;
  t_->Branch("sv_en"       , evSummary_.sv_en      , "sv_en[sv]/F" ) ;
  t_->Branch("sv_ntrk"     , evSummary_.sv_ntrk      , "sv_ntrk[sv]/I" ) ;
  t_->Branch("sv_dxy"      , evSummary_.sv_dxy       , "sv_dxy[sv]/F" ) ;
  t_->Branch("sv_dxyz"     , evSummary_.sv_dxyz      , "sv_dxyz[sv]/F" ) ;
  t_->Branch("sv_dxyz_signif"  , evSummary_.sv_dxyz_signif   , "sv_dxyz_signif[sv]/F" ) ;
  t_->Branch("sv_cos_dxyz_p"   , evSummary_.sv_cos_dxyz_p  , "sv_cos_dxyz_p[sv]/F" ) ;
  t_->Branch("sv_chi2"     , evSummary_.sv_chi2      , "sv_chi2[sv]/F" ) ;
  t_->Branch("sv_ndof"     , evSummary_.sv_ndof      , "sv_ndof[sv]/F" ) ;
  t_->Branch("sv_mc_nbh_moms"  , evSummary_.sv_mc_nbh_moms   , "sv_mc_nbh_moms[sv]/I" ) ;
  t_->Branch("sv_mc_nbh_daus"  , evSummary_.sv_mc_nbh_daus   , "sv_mc_nbh_daus[sv]/I" ) ;
  t_->Branch("sv_mc_mcbh_ind"  , evSummary_.sv_mc_mcbh_ind   , "sv_mc_mcbh_ind[sv]/I" ) ;

  //met
  t_->Branch("met_pt",         	&evSummary_.met_pt,         "met_pt/F");
  t_->Branch("met_phi",         &evSummary_.met_phi,        "met_phi/F");
  t_->Branch("met_sumMET",      &evSummary_.met_sumMET,       "met_sumMET/F");

  return true;
}

//
bool DataEvtSummaryHandler::attachToTree(TTree *t)
{
  if(t==0) return false;
  t_ = t;


  //event info
  t_->SetBranchAddress("run",       &evSummary_.run);
  t_->SetBranchAddress("lumi",      &evSummary_.lumi);
  t_->SetBranchAddress("event",       &evSummary_.event);
  t_->SetBranchAddress("hasTrigger",   	&evSummary_.hasTrigger);
  t_->SetBranchAddress("triggerType",   &evSummary_.triggerType);

  //muon
  t_->SetBranchAddress("mn",            &evSummary_.mn);
  t_->SetBranchAddress("mn_px",           evSummary_.mn_px);
  t_->SetBranchAddress("mn_py",           evSummary_.mn_py);
  t_->SetBranchAddress("mn_pz",           evSummary_.mn_pz);
  t_->SetBranchAddress("mn_en",           evSummary_.mn_en);
  t_->SetBranchAddress("mn_id",           evSummary_.mn_id);
  t_->SetBranchAddress("mn_type",         evSummary_.mn_type);
  t_->SetBranchAddress("mn_passId",  evSummary_.mn_passId);
  t_->SetBranchAddress("mn_passIdLoose",  evSummary_.mn_passIdLoose);
  t_->SetBranchAddress("mn_passSoftMuon",  evSummary_.mn_passSoftMuon);
  t_->SetBranchAddress("mn_passIso",  evSummary_.mn_passIso);

  //electron
  t_->SetBranchAddress("en",            &evSummary_.en);
  t_->SetBranchAddress("en_px",           evSummary_.en_px);
  t_->SetBranchAddress("en_py",           evSummary_.en_py);
  t_->SetBranchAddress("en_pz",           evSummary_.en_pz);
  t_->SetBranchAddress("en_en",           evSummary_.en_en);
  t_->SetBranchAddress("en_id",           evSummary_.en_id);
  t_->SetBranchAddress("en_passId", evSummary_.en_passId);
  t_->SetBranchAddress("en_passIdLoose", evSummary_.en_passIdLoose);
  t_->SetBranchAddress("en_passIso", evSummary_.en_passIso);

  //jet (ak4PFJetsCHS)
  t_->SetBranchAddress("jet",           &evSummary_.jet);
  t_->SetBranchAddress("jet_px",          evSummary_.jet_px);
  t_->SetBranchAddress("jet_py",          evSummary_.jet_py);
  t_->SetBranchAddress("jet_pz",          evSummary_.jet_pz);
  t_->SetBranchAddress("jet_en",          evSummary_.jet_en);
  t_->SetBranchAddress("jet_btag0",         evSummary_.jet_btag0);
  t_->SetBranchAddress("jet_mass",        evSummary_.jet_mass);
  t_->SetBranchAddress("jet_area",        evSummary_.jet_area);
  t_->SetBranchAddress("jet_pu",          evSummary_.jet_pu);
  t_->SetBranchAddress("jet_puId",        evSummary_.jet_puId);
  t_->SetBranchAddress("jet_PFLoose",       evSummary_.jet_PFLoose);
  t_->SetBranchAddress("jet_PFTight",       evSummary_.jet_PFTight);
  t_->SetBranchAddress("jet_mother_id",       evSummary_.jet_mother_id);
  t_->SetBranchAddress("jet_partonFlavour",     evSummary_.jet_partonFlavour);
  t_->SetBranchAddress("jet_hadronFlavour",     evSummary_.jet_hadronFlavour);
  t_->SetBranchAddress("jet_parton_px",       evSummary_.jet_parton_px);
  t_->SetBranchAddress("jet_parton_py",       evSummary_.jet_parton_py);
  t_->SetBranchAddress("jet_parton_pz",       evSummary_.jet_parton_pz);
  t_->SetBranchAddress("jet_parton_en",       evSummary_.jet_parton_en);
  t_->SetBranchAddress("jet_genpt",         evSummary_.jet_genpt);


  //sv : Inclusive Secondary Vertices from slimmedSecondaryVertices
  t_->SetBranchAddress("sv"        , &evSummary_.sv         ) ;
  t_->SetBranchAddress("sv_px"       , evSummary_.sv_px       ) ;
  t_->SetBranchAddress("sv_py"       , evSummary_.sv_py       ) ;
  t_->SetBranchAddress("sv_pz"       , evSummary_.sv_pz       ) ;
  t_->SetBranchAddress("sv_en"       , evSummary_.sv_en       ) ;
  t_->SetBranchAddress("sv_ntrk"     , evSummary_.sv_ntrk       ) ;
  t_->SetBranchAddress("sv_dxy"      , evSummary_.sv_dxy      ) ;
  t_->SetBranchAddress("sv_dxyz"     , evSummary_.sv_dxyz       ) ;
  t_->SetBranchAddress("sv_dxyz_signif"  , evSummary_.sv_dxyz_signif  ) ;
  t_->SetBranchAddress("sv_cos_dxyz_p"   , evSummary_.sv_cos_dxyz_p   ) ;
  t_->SetBranchAddress("sv_chi2"     , evSummary_.sv_chi2       ) ;
  t_->SetBranchAddress("sv_ndof"     , evSummary_.sv_ndof       ) ;
  t_->SetBranchAddress("sv_mc_nbh_moms"  , evSummary_.sv_mc_nbh_moms  ) ;
  t_->SetBranchAddress("sv_mc_nbh_daus"  , evSummary_.sv_mc_nbh_daus  ) ;
  t_->SetBranchAddress("sv_mc_mcbh_ind"  , evSummary_.sv_mc_mcbh_ind  ) ;

  //met
  t_->SetBranchAddress("met_pt",          &evSummary_.met_pt);
  t_->SetBranchAddress("met_phi",         &evSummary_.met_phi);
  t_->SetBranchAddress("met_sumMET",        &evSummary_.met_sumMET);

  return true;
}


//
void DataEvtSummaryHandler::resetStruct()
{
  evSummary_.nmcparticles=0;
  evSummary_.nmcjparticles=0;
  evSummary_.run=0;
  evSummary_.lumi=0;
  evSummary_.event=0;
  evSummary_.mn=0;
  evSummary_.en=0;
  evSummary_.ta=0;
  evSummary_.jet=0;
  evSummary_.sv=0;
  evSummary_.fjet=0;
  evSummary_.npdfs=0;
  evSummary_.nalphaS=0;
}

//
void DataEvtSummaryHandler::fillTree()
{
  if(t_) t_->Fill();
}

//
DataEvtSummaryHandler::~DataEvtSummaryHandler()
{
}
