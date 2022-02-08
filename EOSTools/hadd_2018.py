import glob, os, sys

vh_tag = sys.argv[3]   
year_tag = sys.argv[2]   

#d_hadd_source = "/afs/cern.ch/work/g/georgia/BSMAnalysis/CMSSW_8_0_26_patch1/src/UserCode/bsmhiggs_fwk/test/haa4b/results_Ntpl_2018_08_17/"
d_hadd_source = "/afs/cern.ch/work/g/georgia/BSMAnalysis/limits-combine-v8.1.0/CMSSW_10_2_13/src/UserCode/bsmhiggs_fwk/test/haa4b/results_Ntpl_"+vh_tag+"_"+year_tag+"_2020_02_05/MC/"

d_final_target = "/afs/cern.ch/work/g/georgia/BSMAnalysis/CMSSW_9_4_9/src/UserCode/Haa4b_tmva/EOSTools/MVAFILES/"

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
#"mva_MC13TeV_TTJets_",
"mva_MC13TeV_TTTo2L2Nu_",
"mva_MC13TeV_TTToSemiLeptonic_",
"mva_MC13TeV_TTToHadronic_",
"mva_MC13TeV_SingleT_tW_top_",
"mva_MC13TeV_SingleT_tW_antitop_",  
"mva_MC13TeV_SingleT_t_top_",
"mva_MC13TeV_SingleT_t_antitop_",   
"mva_MC13TeV_SingleT_s_",
"mva_MC13TeV_TGJets_",
"mva_MC13TeV_TTGJets_", #ext1_v2_",
"mva_MC13TeV_TTWJetslnu_", 
"mva_MC13TeV_TTZJets2l2nu_",
"mva_MC13TeV_WplusH_HToBB_WToLNu_20",
"mva_MC13TeV_WplusH_HToBB_WToLNu_ext1_",   
"mva_MC13TeV_WminusH_HToBB_WToLNu_ext1_", 
"mva_MC13TeV_WminusH_HToBB_WToLNu_20", 
"mva_MC13TeV_ZH_HToBB_ZToLL_20",
"mva_MC13TeV_ZH_HToBB_ZToLL_ext1_", 
]

sample_tag_list_W = [
"mva_MC13TeV_WJets_201",
"mva_MC13TeV_WJets_HT70to100_",
"mva_MC13TeV_WJets_HT100to200_",
"mva_MC13TeV_WJets_HT200to400_",
"mva_MC13TeV_WJets_HT400to600_",
"mva_MC13TeV_WJets_HT600to800_",
"mva_MC13TeV_WJets_HT800to1200_",
"mva_MC13TeV_WJets_HT1200to2500_",
"mva_MC13TeV_WJets_HT2500toInf_"
]

sample_tag_list_DY = [
"mva_MC13TeV_DYJetsToLL_10to50_",
#"mva_MC13TeV_DY1JetsToLL_10to50_",
#"mva_MC13TeV_DY2JetsToLL_10to50_",
#"mva_MC13TeV_DY3JetsToLL_10to50_",
#"mva_MC13TeV_DY4JetsToLL_10to50_",
"mva_MC13TeV_DYJetsToLL_M50_",
"mva_MC13TeV_DY1JetsToLL_M50_",
"mva_MC13TeV_DY2JetsToLL_M50_",
"mva_MC13TeV_DY3JetsToLL_M50_",
"mva_MC13TeV_DY4JetsToLL_M50_"    
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
"mva_MC13TeV_WW_",
"mva_MC13TeV_WZ_",
"mva_MC13TeV_ZZ_",
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

"mva_MC13TeV_Wh_amass12_", 
"mva_MC13TeV_Wh_amass15_", 
"mva_MC13TeV_Wh_amass20_", 
"mva_MC13TeV_Wh_amass25_", 
"mva_MC13TeV_Wh_amass30_", 
"mva_MC13TeV_Wh_amass40_", 
"mva_MC13TeV_Wh_amass50_",
"mva_MC13TeV_Wh_amass60_" 
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


#year_tag = sys.argv[2] 
#vh_tag = sys.argv[3] 

for tag in sample_tag_list :
  #hadd
  cmd = 'hadd ' + tag[:-1] + '_'+year_tag+'.root ' + d_hadd_source + tag + '*.root'   
  #cmd = 'hadd ' + tag[:-1] + '.root `xrdfsls -u ' + d_hadd_source + ' | grep \'' + tag + '\'`'
#  cmd = 'hadd ' + tag[:-1] + '.root `ls ' + d_hadd_source + ' | grep \'' + tag + '\'`'
  print(cmd)
  os.system(cmd)
  cmd = 'mv ' + tag[:-1] + '_'+year_tag+'.root ' + MGM + d_final_target + '/' + vh_tag + '_'+year_tag+'_MVABGMCFileList/'   
#  cmd = 'xrdcp ' + tag[:-1] + '.root ' + MGM + d_final_target
  print(cmd)
  os.system(cmd)     


