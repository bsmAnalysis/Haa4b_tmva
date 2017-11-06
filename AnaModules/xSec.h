#include <string>
#include <map>

const std::map<std::string, float> xBGSec = 
{
  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
  //TTJets 
  {"TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8", 831.76},
  //single top
  {"ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1", 3.36},
  {"ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1", 80.95},
  {"ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1", 136.02},
  {"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1", 35.85},
  {"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1", 35.85},
  //WJetsToLNu
  {"WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8", 61526.7},
  //Diboson
  {"WWTo2L2Nu_13TeV-powheg", 12.178},
  {"WWToLNuQQ_13TeV-powheg", 49.997},
  {"WZ_TuneCUETP8M1_13TeV-pythia8", 47.13},
  {"ZZ_TuneCUETP8M1_13TeV-pythia8", 16.523},
  //tri boson
  {"WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8", 0.2086},
  {"WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8", 0.1651},
  {"WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8", 0.05565},
  {"ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8", 0.01398},
  //QCD
  {"QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8", 557600000*0.0096},
  {"QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8", 136000000*0.073},
  {"QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8", 19800000*0.146},
  {"QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8", 2800000*0.125},
  {"QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8", 477000*0.132},
  {"QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8", 114000*0.165},
  {"QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8", 9000*0.15},
  {"QCD_Pt-20toInf_MuEnrichedPt15_TuneCUETP8M1_13TeV_pythia8", 720648000*0.00042},
  //DY
  {"DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8", 18610},
  {"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8", 1921.8*3},
  //tt gamma, w z
  {"TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8", 2.967},
  {"TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8", 3.697},
  {"TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8", 0.2043},
  {"TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8", 0.2529}, 
};
