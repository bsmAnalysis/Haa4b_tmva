import glob, os, sys

#d_hadd_source = "/afs/cern.ch/work/g/georgia/BSMAnalysis/CMSSW_8_0_26_patch1/src/UserCode/bsmhiggs_fwk/test/haa4b/results_Ntpl_2018_08_17/"
d_hadd_source = "/eos/cms/store/user/georgia/results_Ntpl_WH_mva_mc_2019_11_22/"
#/eos/cms/store/user/georgia/bsm_analysis/ZH/"
d_final_target = "/eos/cms/store/user/georgia/bsm_analysis/WH_2018/"   

#MGM = "root://cmseos.fnal.gov/"
MGM = ""
#MGM = "root://eoscms.cern.ch/"

sample_tag_list_Data = [
"mva_Data13TeV_SingleElectron2016B_ver2_",
"mva_Data13TeV_SingleElectron2016C_", 
"mva_Data13TeV_SingleElectron2016D_", 
"mva_Data13TeV_SingleElectron2016E_", 
"mva_Data13TeV_SingleElectron2016F_", 
"mva_Data13TeV_SingleElectron2016G_", 
"mva_Data13TeV_SingleElectron2016H_ver2_", 
"mva_Data13TeV_SingleElectron2016H_ver3_", 
"mva_Data13TeV_SingleMuon2016B_ver2_", 
"mva_Data13TeV_SingleMuon2016C_", 
"mva_Data13TeV_SingleMuon2016D_", 
"mva_Data13TeV_SingleMuon2016E_", 
"mva_Data13TeV_SingleMuon2016F_", 
"mva_Data13TeV_SingleMuon2016G_", 
"mva_Data13TeV_SingleMuon2016H_ver2_", 
"mva_Data13TeV_SingleMuon2016H_ver3_", 
"mva_Data13TeV_DoubleEle2016B_ver2_",
"mva_Data13TeV_DoubleEle2016C_",
"mva_Data13TeV_DoubleEle2016D_",
"mva_Data13TeV_DoubleEle2016E_",
"mva_Data13TeV_DoubleEle2016F_",
"mva_Data13TeV_DoubleEle2016G_",
"mva_Data13TeV_DoubleEle2016H_ver2_",
"mva_Data13TeV_DoubleEle2016H_ver3_",
"mva_Data13TeV_DoubleMuon2016B_ver2_",
"mva_Data13TeV_DoubleMuon2016C_",
"mva_Data13TeV_DoubleMuon2016D_",
"mva_Data13TeV_DoubleMuon2016E_",
"mva_Data13TeV_DoubleMuon2016F_",
"mva_Data13TeV_DoubleMuon2016G_",
"mva_Data13TeV_DoubleMuon2016H_ver2_",
"mva_Data13TeV_DoubleMuon2016H_ver3_",
                       ]

sample_tag_list_TT = [
"mva_MC13TeV_TT",
#"mva_MC13TeV_TTJets_powheg_",
#"mva_MC13TeV_TTJets_slt_",
#"mva_MC13TeV_TTJets_slat_",
#"mva_MC13TeV_TTJets_dl_",
#"mva_MC13TeV_TTJets_slt_ext1_",
#"mva_MC13TeV_TTJets_slat_ext1_",
#"mva_MC13TeV_TTJets_dl_ext1_",
"mva_MC13TeV_SingleT_atW_",
"mva_MC13TeV_SingleT_tW_",
"mva_MC13TeV_SingleT_at_",
"mva_MC13TeV_SingleT_t_",
"mva_MC13TeV_SingleT_s_",
"mva_MC13TeV_TGJets_"
#"mva_MC13TeV_TTGJets_", 
#"mva_MC13TeV_TTWJetslnu_", 
#"mva_MC13TeV_TTZJets2l2nu_"
]
sample_tag_list_W = [
"mva_MC13TeV_WJets_",
#"mva_MC13TeV_WJets_ext2_",
"mva_MC13TeV_W1Jets_",
"mva_MC13TeV_W2Jets_",
#"mva_MC13TeV_W2Jets_ext1_",
"mva_MC13TeV_W3Jets_",
#"mva_MC13TeV_W3Jets_ext1_",
"mva_MC13TeV_W4Jets_"
#"mva_MC13TeV_W4Jets_ext1_",
#"mva_MC13TeV_W4Jets_ext2_",
]

sample_tag_list_DY = [
"mva_MC13TeV_DYJetsToLL_10to50_",
"mva_MC13TeV_DY1JetsToLL_10to50_",
"mva_MC13TeV_DY2JetsToLL_10to50_",
"mva_MC13TeV_DY3JetsToLL_10to50_",
"mva_MC13TeV_DY4JetsToLL_10to50_",
"mva_MC13TeV_DYJetsToLL_50toInf_",
"mva_MC13TeV_DY1JetsToLL_50toInf_",
"mva_MC13TeV_DY2JetsToLL_50toInf_",
"mva_MC13TeV_DY3JetsToLL_50toInf_",
"mva_MC13TeV_DY4JetsToLL_50toInf_"
                       ]

sample_tag_list_QCD = [
#"mva_MC13TeV_QCD_Pt20To30_EMEnr_",
#"mva_MC13TeV_QCD_Pt30To50_EMEnr_",
#"mva_MC13TeV_QCD_Pt50To80_EMEnr_",
"mva_MC13TeV_QCD_Pt80To120_EMEnr_",
"mva_MC13TeV_QCD_Pt120To170_EMEnr_",
"mva_MC13TeV_QCD_Pt170To300_EMEnr_",
"mva_MC13TeV_QCD_Pt300ToInf_EMEnr_",
"mva_MC13TeV_QCD_Pt20ToInf_MuEnr_"
                      ]

sample_tag_list_VV = [
##Di-boson
"mva_MC13TeV_WW2l2nu_",
"mva_MC13TeV_WWlnu2q_",
"mva_MC13TeV_WW4q_",
#"mva_MC13TeV_WWlnu2q_ext1_",
"mva_MC13TeV_WZ_",
#"mva_MC13TeV_WZ_ext1_",
"mva_MC13TeV_ZZ_",
#"mva_MC13TeV_ZZ_ext1_",
##Tri-boson
"mva_MC13TeV_WWW_4F_",
"mva_MC13TeV_WWZ_",
"mva_MC13TeV_WZZ_",
"mva_MC13TeV_ZZZ_",
                      ]


sample_tag_list_SG = [
"mva_MC13TeV_Zh_amass12_",
"mva_MC13TeV_Zh_amass15_",
"mva_MC13TeV_Zh_amass20_",
"mva_MC13TeV_Zh_amass25_",
"mva_MC13TeV_Zh_amass30_",
"mva_MC13TeV_Zh_amass40_",
"mva_MC13TeV_Zh_amass50_",
"mva_MC13TeV_Zh_amass60_",
                      ]


#example of sample tag: SSTrimmed_SMS-T2tt_mStop-850_mLSP-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_stopFlatNtuples_, always end with "_"
sample_tag = sys.argv[1]

sample_tag_list = []

if(sample_tag == 'Data') :
  sample_tag_list = sample_tag_list_Data
elif(sample_tag == 'TT') :
  sample_tag_list = sample_tag_list_TT
elif(sample_tag == 'W') :
  sample_tag_list = sample_tag_list_W 
elif(sample_tag == 'DY') :
  sample_tag_list = sample_tag_list_DY
elif(sample_tag == 'QCD') :
  sample_tag_list = sample_tag_list_QCD
elif(sample_tag == 'VV') :
  sample_tag_list = sample_tag_list_VV
elif(sample_tag == 'SG') :
  sample_tag_list = sample_tag_list_SG
else:
  print "wrong run type!"

for tag in sample_tag_list :
  #hadd
  cmd = 'hadd ' + tag[:-1] + '.root ' + d_hadd_source + tag + '*.root'   
  #cmd = 'hadd ' + tag[:-1] + '.root `xrdfsls -u ' + d_hadd_source + ' | grep \'' + tag + '\'`'
#  cmd = 'hadd ' + tag[:-1] + '.root `ls ' + d_hadd_source + ' | grep \'' + tag + '\'`'
  print(cmd)
  os.system(cmd)
  cmd = 'cp ' + tag[:-1] + '.root ' + MGM + d_final_target   
#  cmd = 'xrdcp ' + tag[:-1] + '.root ' + MGM + d_final_target
  print(cmd)
  os.system(cmd)     


