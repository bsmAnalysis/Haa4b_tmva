import glob, os, sys

#hadd mva_MC13TeV_ZZ_ext1_2016All.root `ls /afs/cern.ch/work/h/hua/Haa4b/CMSSW_8_0_26_patch1/src/UserCode/bsmhiggs_fwk/test/haa4b/results_Ntpl_2017_09_21 | grep 'mva_MC13TeV_ZZ_ext1_2016_'`
#d_hadd_source = "/afs/cern.ch/work/h/hua/Haa4b/CMSSW_8_0_26_patch1/src/UserCode/bsmhiggs_fwk/test/haa4b/results_Ntpl_2017_09_20"
#d_hadd_source = "/afs/cern.ch/work/h/hua/Haa4b/CMSSW_8_0_26_patch1/src/UserCode/bsmhiggs_fwk/test/haa4b/results_Ntpl_2017_09_21"
d_hadd_source = "/afs/cern.ch/work/h/hua/Haa4b/CMSSW_8_0_26_patch1/src/UserCode/bsmhiggs_fwk/test/haa4b/results_Ntpl_2018_03_03"
#d_hadd_source = "/afs/cern.ch/work/h/hua/Haa4b/CMSSW_8_0_26_patch1/src/UserCode/bsmhiggs_fwk/test/haa4b/results_Ntpl_2017_12_12"
d_final_target = "/eos/user/h/hua/Haa4b/MVARes"

#MGM = "root://cmseos.fnal.gov/"
MGM = "root://eosuser.cern.ch/"
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
                       ]

sample_tag_list_TT = [
#"mva_MC13TeV_TTJets_powheg_2016_",
#"mva_MC13TeV_TTJets_slt_2016_",
#"mva_MC13TeV_TTJets_slat_2016_",
#"mva_MC13TeV_TTJets_dl_2016_",
#"mva_MC13TeV_TTJets_slt_ext1_2016_",
#"mva_MC13TeV_TTJets_slat_ext1_2016_",
#"mva_MC13TeV_TTJets_dl_ext1_2016_",
"mva_MC13TeV_SingleT_atW_2016_",
"mva_MC13TeV_SingleT_tW_2016_",
"mva_MC13TeV_SingleT_at_2016_",
"mva_MC13TeV_SingleT_t_2016_",
"mva_MC13TeV_SingleT_s_2016_",
"mva_MC13TeV_WJets_2016_",
"mva_MC13TeV_WJets_ext2_2016_",
"mva_MC13TeV_W1Jets_2016_",
"mva_MC13TeV_W2Jets_2016_",
"mva_MC13TeV_W2Jets_ext1_2016_",
"mva_MC13TeV_W3Jets_2016_",
"mva_MC13TeV_W3Jets_ext1_2016_",
"mva_MC13TeV_W4Jets_2016_",
"mva_MC13TeV_W4Jets_ext1_2016_",
"mva_MC13TeV_W4Jets_ext2_2016_",
"mva_MC13TeV_TGJets_2016_",
"mva_MC13TeV_TGJets_ext1_2016_",
"mva_MC13TeV_TTGJets_2016_",
"mva_MC13TeV_TTWJetslnu_2016_",
"mva_MC13TeV_TTZJets2l2nu_2016_",
]

sample_tag_list_DY = [
"mva_MC13TeV_DYJetsToLL_10to50_2016_",
#"mva_MC13TeV_DYJetsToLL_10to50_ext1_2016_",
"mva_MC13TeV_DY1JetsToLL_10to50_2016_",
"mva_MC13TeV_DY2JetsToLL_10to50_2016_",
"mva_MC13TeV_DY3JetsToLL_10to50_2016_",
"mva_MC13TeV_DY4JetsToLL_10to50_2016_",
"mva_MC13TeV_DYJetsToLL_50toInf_ext1_2016_",
"mva_MC13TeV_DYJetsToLL_50toInf_ext2_2016_",
#"mva_MC13TeV_DYJetsToLL_50toInf_ext3_2016_",
#"mva_MC13TeV_DYJetsToLL_50toInf_ext4_2016_",
#"mva_MC13TeV_DYJetsToLL_50toInf_ext5_2016_",
#"mva_MC13TeV_DYJetsToLL_50toInf_ext6_2016_",
"mva_MC13TeV_DY1JetsToLL_50toInf_2016_",
"mva_MC13TeV_DY2JetsToLL_50toInf_2016_",
"mva_MC13TeV_DY3JetsToLL_50toInf_2016_",
"mva_MC13TeV_DY4JetsToLL_50toInf_2016_",
                       ]

sample_tag_list_QCD = [
"mva_MC13TeV_QCD_Pt20To30_EMEnr_2016_",
"mva_MC13TeV_QCD_Pt30To50_EMEnr_2016_",
"mva_MC13TeV_QCD_Pt30To50_EMEnr_ext1_2016_",
"mva_MC13TeV_QCD_Pt50To80_EMEnr_2016_",
"mva_MC13TeV_QCD_Pt80To120_EMEnr_2016_",
"mva_MC13TeV_QCD_Pt120To170_EMEnr_2016_",
"mva_MC13TeV_QCD_Pt170To300_EMEnr_2016_",
"mva_MC13TeV_QCD_Pt300ToInf_EMEnr_2016_",
"mva_MC13TeV_QCD_Pt20ToInf_MuEnr_2016_",
                      ]

sample_tag_list_VV = [
##Di-boson
"mva_MC13TeV_WW2l2nu_2016_",
"mva_MC13TeV_WWlnu2q_2016_",
"mva_MC13TeV_WWlnu2q_ext1_2016_",
"mva_MC13TeV_WZ_2016_",
"mva_MC13TeV_WZ_ext1_2016_",
"mva_MC13TeV_ZZ_2016_",
"mva_MC13TeV_ZZ_ext1_2016_",
##Tri-boson
"mva_MC13TeV_WWW_4F_2016_",
"mva_MC13TeV_WWZ_2016_",
"mva_MC13TeV_WZZ_2016_",
"mva_MC13TeV_ZZZ_2016_",
                      ]


sample_tag_list_SG = [
"mva_MC13TeV_Wh_amass12_",
"mva_MC13TeV_Wh_amass15_",
"mva_MC13TeV_Wh_amass20_",
"mva_MC13TeV_Wh_amass25_",
"mva_MC13TeV_Wh_amass30_",
"mva_MC13TeV_Wh_amass40_",
"mva_MC13TeV_Wh_amass50_",
"mva_MC13TeV_Wh_amass60_",
                      ]


#example of sample tag: SSTrimmed_SMS-T2tt_mStop-850_mLSP-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_stopFlatNtuples_, always end with "_"
sample_tag = sys.argv[1]

sample_tag_list = []

if(sample_tag == 'Data') :
  sample_tag_list = sample_tag_list_Data
elif(sample_tag == 'TT') :
  sample_tag_list = sample_tag_list_TT
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
  #cmd = 'hadd ' + tag[:-1] + '.root `xrdfsls -u ' + d_hadd_source + ' | grep \'' + tag + '\'`'
  cmd = 'hadd ' + tag[:-1] + '.root `ls ' + d_hadd_source + ' | grep \'' + tag + '\'`'
  print(cmd)
  #os.system(cmd)
  cmd = 'xrdcp ' + tag[:-1] + '.root ' + MGM + d_final_target
  print(cmd)

  #xrdcp root://cmseos.fnal.gov//store/user/jjesus/EOSFile.txt \? root://cmseos.fnal.gov//store/user/jjesus/EOSFile1.txt
  #cmd = 'xrdcp ' + MGM + d_hadd_source + '/' + tag[:-1] + '.root ' + MGM + d_final_target + '/' + tag[:-1] + '.root' 
  #print(cmd)
  #cmd = 'eosrm ' + d_hadd_source + '/' + tag[:-1] + '.root'
  #print(cmd)

