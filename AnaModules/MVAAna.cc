#include "MVAAna.h"


int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr <<" Please give at least 2 arguments " << "RunMode TrainMode" << std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./QCD RunMode TrainMode" << std::endl;
    return -1;
  }

  std::string RunMode = argv[1];
  std::string TrainMode = argv[2]; //TribMVA or QuabMVA
  
  std::string channel = "Zh";
  unsigned short int yearBits = 1; // 1 for 2016, 2 for 2017 and 4 for 2018  
  
  bool is2016 = yearBits & 0x01;
  bool is2017 = (yearBits >> 1) & 0x01;
  bool is2018 = (yearBits >> 2) & 0x01;
  if(is2017) LumiScale = 41529.152;
  else if(is2018) LumiScale = 59740.565;
  std::string dir_out = "OutDir/";
  //dir_out = dir_out + channel + "/";
  std::string command = "mkdir -p " + dir_out;
  system(command.c_str());
  if ( RunMode == "BasicCheck" )
  {

  }
  else if ( RunMode == "Train" )
  { 
    TMVATrainer myTMVATrainer;
    myTMVATrainer.GenSGReWeight(TrainMode);
    myTMVATrainer.InitTMVAFactory("MVATrainTestOut" + TrainMode + ".root", "Haa4bSBClassification" + TrainMode);
    myTMVATrainer.SetupMVAFactory(TrainMode);
    myTMVATrainer.TnTstMVAFactory();
    myTMVATrainer.CloseMVAFactory();
  }
  else if ( RunMode == "CV" )
  {
    std::vector<std::string> TestBDTparStringVec;

    TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=200:MinNodeSize=5.0%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");

    TMVATrainer myTMVATrainer;
    myTMVATrainer.InitTMVAFactory("MVACVTestOut" + TrainMode + ".root", "Haa4bSBClassification" + TrainMode);
    myTMVATrainer.SetupMVAFactory( TrainMode );
    myTMVATrainer.CrossValidation( TestBDTparStringVec );
    //myTMVATrainer.CloseMVAFactory();
  }
  else if ( RunMode == "Application" )
  {  
    MVACutFlowHist myMVACutFlowHist;
    myMVACutFlowHist.BookHistgram( (dir_out + "MVACutFlow" + TrainMode + ".root").c_str() );
    
    TMVAReader myTMVAReader;
    myTMVAReader.InitTMVAReader();
    myTMVAReader.SetupMVAReader( "Haa4bSBClassification" + TrainMode, "dataset/weights_"+channel+"/Haa4bSBClassification" + TrainMode + "_BDT.weights.xml" );
 
    QCDSampleWeight mySGSampleWeight;
    //    if(is2016){
    LumiScale=36300.000;
      if(channel == "Wh"){
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass12_2016" , 1.37*0.61*1.076, 1010516 - 0.0,  LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass15_2016" , 1.37*0.61*1.076, 996279 - 0.0,  LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass20_2016" , 1.37*0.61*1.076, 999279.0 - 0.0,  LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass25_2016" , 1.37*0.61*1.076, 1010277.0 - 0.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass30_2016" , 1.37*0.61*1.076, 998095.0 - 0.0,  LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass40_2016" , 1.37*0.61*1.076, 1010418.0 - 0.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass50_2016" , 1.37*0.61*1.076, 995119.0 - 0.0,  LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass60_2016" , 1.37*0.61*1.076, 1008303.0 - 0.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
      }
      else if(channel == "Zh"){
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass12_2016" , 0.8549*0.7435*1.0474, 965463 - 0.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass15_2016" , 0.8549*0.7435*1.0474, 990410 - 0.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass20_2016" , 0.8549*0.7435*1.0474, 965694.0 - 0.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass25_2016" , 0.8549*0.7435*1.0474, 985066.0 - 0.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass30_2016" , 0.8549*0.7435*1.0474, 994159.0 - 0.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass40_2016" , 0.8549*0.7435*1.0474, 986613.0 - 0.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass50_2016" , 0.8549*0.7435*1.0474, 993354.0 - 0.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass60_2016" , 0.8549*0.7435*1.0474, 974094.0 - 0.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
      }
      // }
      //  else if(is2017){
      LumiScale = 41529.152;
      
      if(channel == "Wh"){
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass12_2017" , 1.37*0.61*1.076, 954064.0 - 243.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass15_2017" , 1.37*0.61*1.076, 938279.0 - 194.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass20_2017" , 1.37*0.61*1.076, 958291.0 - 253.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass25_2017" , 1.37*0.61*1.076, 934752.0 - 245.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass30_2017" , 1.37*0.61*1.076, 934392.0 - 228.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass40_2017" , 1.37*0.61*1.076, 955312.0 - 232.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass50_2017" , 1.37*0.61*1.076, 938132.0 - 219.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass60_2017" , 1.37*0.61*1.076, 953671.0 - 238.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
      }
      else if(channel == "Zh"){
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass12_2017" , 0.8594*0.75*1.0474, 494867.0 - 137.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass15_2017" , 0.8594*0.75*1.0474, 497352.0 - 146.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass20_2017" , 0.8594*0.75*1.0474, 496923.0 - 156.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass25_2017" , 0.8594*0.75*1.0474, 494046.0 - 113.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass30_2017" , 0.8594*0.75*1.0474, 494844.0 - 105.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass40_2017" , 0.8594*0.75*1.0474, 493834.0 - 130.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass50_2017" , 0.8594*0.75*1.0474, 496778.0 - 141.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass60_2017" , 0.8594*0.75*1.0474, 496260.0 - 155.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
      }
      // }
      //  else if(is2018){
      LumiScale=59740.565;
      if(channel == "Wh"){
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass12_2018" , 1.37*0.61*1.076, 1020552.0 - 252.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass15_2018" , 1.37*0.61*1.076, 1022841.0 - 277.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass20_2018" , 1.37*0.61*1.076, 1020865.0 - 260.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass25_2018" , 1.37*0.61*1.076, 1021745.0 - 220.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass30_2018" , 1.37*0.61*1.076, 1011608.0 - 256.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass40_2018" , 1.37*0.61*1.076, 1019676.0 - 258.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass50_2018" , 1.37*0.61*1.076, 1015362.0 - 233.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass60_2018" , 1.37*0.61*1.076, 1019268.0 - 221.0, LumiScale, 1, "FileList/WH_MVASGMCFileList.txt", TrainMode );
      }
      else if(channel == "Zh"){
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass12_2018" , 0.8594*0.75*1.0474, 496864.0 - 143.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass15_2018" , 0.8594*0.75*1.0474, 297591.0 - 90.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass20_2018" , 0.8594*0.75*1.0474, 494953.0 - 133.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass25_2018" , 0.8594*0.75*1.0474, 484526.0 - 63.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass30_2018" , 0.8594*0.75*1.0474, 132903.0 - 44.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass40_2018" , 0.8594*0.75*1.0474, 484354.0 - 40.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass50_2018" , 0.8594*0.75*1.0474, 472247.0 - 60.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass60_2018" , 0.8594*0.75*1.0474, 495637.0 - 45.0, LumiScale, 1, "FileList/ZH_MVASGMCFileList.txt", TrainMode );
      }
      // }
    std::cout << "Processing signal MC samples..." << std::endl;
    for(std::vector<QCDSampleInfo>::iterator iter_SampleInfos = mySGSampleWeight.QCDSampleInfos.begin(); iter_SampleInfos != mySGSampleWeight.QCDSampleInfos.end(); iter_SampleInfos++)
    { 
      //print out basic information 
      float ls = (*iter_SampleInfos).weight; //luminosity
      std::cout <<"Sample Type: "<< (*iter_SampleInfos).QCDTag << "; LUMI Scale: " << ls << std::endl;
      //Loading chain info
      long long int nTot = (*iter_SampleInfos).chain->GetEntries();
      float WpT, Hmass, HpT, bbdRAve, bbdMMin, HHt, WHdR;
      float lepPt, pfMET, MTw, ljDR;
      (*iter_SampleInfos).chain->SetBranchAddress( "WpT", &WpT );
      (*iter_SampleInfos).chain->SetBranchAddress( "Hmass", &Hmass );
      (*iter_SampleInfos).chain->SetBranchAddress( "HpT", &HpT );
      (*iter_SampleInfos).chain->SetBranchAddress( "bbdRAve", &bbdRAve );
      if(TrainMode.find("QuabMVA") != std::string::npos )
	(*iter_SampleInfos).chain->SetBranchAddress( "bbdMMin", &bbdMMin );
      (*iter_SampleInfos).chain->SetBranchAddress( "HHt", &HHt );
      (*iter_SampleInfos).chain->SetBranchAddress( "WHdR", &WHdR );
      (*iter_SampleInfos).chain->SetBranchAddress( "lepPt", &lepPt );  
      (*iter_SampleInfos).chain->SetBranchAddress( "pfMET", &pfMET );  
      (*iter_SampleInfos).chain->SetBranchAddress( "MTw", &MTw );  
      (*iter_SampleInfos).chain->SetBranchAddress( "ljDR", &ljDR );  
      float weight;
      (*iter_SampleInfos).chain->SetBranchAddress( "weight", &weight );
      float xsecWeight;
      (*iter_SampleInfos).chain->SetBranchAddress( "xsecWeight", &xsecWeight );  
      weight *= xsecWeight;

      //Determine histogram indice
      int ih = -1;
      if      ((*iter_SampleInfos).QCDTag.find("_amass12_") != std::string::npos) ih = 0;
      else if ((*iter_SampleInfos).QCDTag.find("_amass15_") != std::string::npos) ih = 1;
      else if ((*iter_SampleInfos).QCDTag.find("_amass20_") != std::string::npos) ih = 2;
      else if ((*iter_SampleInfos).QCDTag.find("_amass25_") != std::string::npos) ih = 3;
      else if ((*iter_SampleInfos).QCDTag.find("_amass30_") != std::string::npos) ih = 4;
      else if ((*iter_SampleInfos).QCDTag.find("_amass40_") != std::string::npos) ih = 5;
      else if ((*iter_SampleInfos).QCDTag.find("_amass50_") != std::string::npos) ih = 6;
      else if ((*iter_SampleInfos).QCDTag.find("_amass60_") != std::string::npos) ih = 7;
      
      for (long long int ievt = 0; ievt < nTot; ievt++) 
      {
        (*iter_SampleInfos).chain->GetEvent(ievt);
        float mvaout = myTMVAReader.GenReMVAReader
                       (
                        WpT,
                        Hmass, HpT, bbdRAve, bbdMMin, HHt,
                        WHdR, lepPt, pfMET, MTw, ljDR,
                        "Haa4bSBClassification" + TrainMode
                       );
        if ( ih >= 0 )
        {
          (myMVACutFlowHist.h_b_WpT_SGMC[ih])->Fill( WpT, weight * ls );
          (myMVACutFlowHist.h_b_Hmass_SGMC[ih])->Fill( Hmass, weight * ls );
          (myMVACutFlowHist.h_b_HpT_SGMC[ih])->Fill( HpT, weight * ls );
          (myMVACutFlowHist.h_b_bbdRAve_SGMC[ih])->Fill( bbdRAve, weight * ls );
	  if(TrainMode.find("QuabMVA") != std::string::npos )
	     (myMVACutFlowHist.h_b_bbdMMin_SGMC[ih])->Fill( bbdMMin, weight * ls );
          (myMVACutFlowHist.h_b_HHt_SGMC[ih])->Fill( HHt, weight * ls );
          (myMVACutFlowHist.h_b_WHdR_SGMC[ih])->Fill( WHdR, weight * ls );
	  (myMVACutFlowHist.h_b_lepPt_SGMC[ih])->Fill( lepPt, weight * ls );       
	  (myMVACutFlowHist.h_b_pfMET_SGMC[ih])->Fill( pfMET, weight * ls );       
	  (myMVACutFlowHist.h_b_MTw_SGMC[ih])->Fill( MTw, weight * ls );       
	  (myMVACutFlowHist.h_b_ljDR_SGMC[ih])->Fill( ljDR, weight * ls );       

          (myMVACutFlowHist.h_b_BDT_SGMC[ih])->Fill( mvaout, weight * ls );

          int lobin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout, TrainMode ).first, hibin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout, TrainMode ).second;
          if ( hibin >= 0 )
          {
            for ( int j = lobin; j <= hibin ; j++ )
            {
              (myMVACutFlowHist.h_b_n_SGMC[ih])->Fill( j, weight * ls );
              //(myMVACutFlowHist.h_b_n_SGMC[ih])->Fill( j, 1.0 );
            }
          }
          //else
          //{ 
            //(myMVACutFlowHist.h_b_n_SGMC[ih])->Fill( 0.0, weight * ls );
            //(myMVACutFlowHist.h_b_n_SGMC[ih])->Fill( 0.0, 1.0 );
          //}
        }
     
      }
    }

    QCDSampleWeight myBGSampleWeight;
    // if(is2016){
      TString FilePath = "FileList/WH_MVABGMCFileList.txt";
      if(channel.compare("Zh") == 0) FilePath = "FileList/ZH_MVABGMCFileList.txt";

      LumiScale=36300.000;
      //Single Top
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_s_2016"           ,             3.362, 811495.0 - 188505.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_atW_2016"         ,              35.6,    6933094.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_tW_2016"          ,              35.6,    6952830.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_at_2016"          ,             80.95,   38811017.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_t_2016"           ,            136.02,   67240808.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      //TTJets
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTJets_powheg_2016"              ,            831.76, 76915549 - 0.0, LumiScale, 1, FilePath, TrainMode );
   
       //WJets
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_2016"                 ,           50690, 59028040.0 + 10020533., LumiScale, 1.21, FilePath, TrainMode ); 
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_ext2_2016"            ,           50690, 10020533 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT70to100_2016"       ,           1319, 10020533 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT100to200_2016"       ,           1345, 9945478 + 29503700.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT100to200_ext1_2016"       ,           1345, 29503700.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT100to200_ext2_2016"       ,           1345, 29503700.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT200to400_2016"       ,           359.7, 4963240.0 + 14106492.0 + 19914590.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT200to400_ext1_2016"       ,           359.7, 14106492.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT200to400_ext2_2016"       ,           359.7, 19914590.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT400to600_2016"       ,           48.91, 1963464.0 + 5796237.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT400to600_ext1_2016"       ,           48.91, 5796237.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT600to800_2016"       ,           12.05, 3779141.0 + 14908339.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT600to800_ext1_2016"       ,           12.05, 14908339.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT800to1200_2016"       ,           5.501, 1544513.0 + 6286023.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT800to1200_ext1_2016"       ,           5.501, 6286023.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT1200to2500_2016"       ,           1.329, 244532.0 + 6627909.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT1200to2500_ext1_2016"       ,           1.329, 6627909.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT2500toInf_2016"       ,           0.03216, 253561.0 + 2384260.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT2500toInf_ext1_2016"       ,           0.03216, 2384260.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      //DY [10,50]
      //myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_10to50_"    ,             18610, 62001124.0 - 4211038.0, LumiScale, 1.21, FilePath, TrainMode );
      // DY [50,Inf]
      myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_50toInf_ext1_2016"   ,              4895, 247721443.0 - 20137162.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_50toInf_ext2_2016"   ,              4895, 247721443.0 - 20137162.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY1JetsToLL_50toInf_2016"  ,              1016,         62627174.0 - 0.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY2JetsToLL_50toInf_2016"  ,             331.4,         19970551.0 - 0.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY3JetsToLL_50toInf_2016"  ,             96.36,          5856110.0 - 0.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY4JetsToLL_50toInf_2016"  ,              51.4,          4197868.0 - 0.0, LumiScale, 1.18, FilePath, TrainMode );
      //TG, TTG, TTW, TTZ
      myBGSampleWeight.QCDSampleInfo_push_back( "_TGJets_2016"              ,             2.967, 1109033.0 - 740471.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTGJets_2016"             ,             3.697, 3224372.0 - 1646539.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTWJetslnu_2016"          ,            0.2043, 2361962.0 - 758435.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTZJets2l2nu_2016"        ,            0.2529, 1460207.0 - 532231.0, LumiScale, 1, FilePath, TrainMode );
      //Di-boson
      myBGSampleWeight.QCDSampleInfo_push_back( "_WW2l2nu_2016"             ,            12.178,  1999000.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WWlnu2q_2016"             ,            49.997, 18973950.0 - 0.0, LumiScale, 1, FilePath, TrainMode ); //
      //   myBGSampleWeight.QCDSampleInfo_push_back( "_WW4q_"                ,            51.723,  1998400.0 - 0.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_WZ_2016"                  ,             47.13,  1000000.0 - 0.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_ZZ_2016"                  ,             17.72,  1988098.0 - 0.0, LumiScale, 1, FilePath, TrainMode ); //
      //Tri-boson
      myBGSampleWeight.QCDSampleInfo_push_back( "_WWW_4F_2016"                 ,            0.2086, 225269.0 - 14731.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WWZ_2016"                 ,            0.1651, 235734.0 - 14266.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WZZ_2016"                 ,           0.05565, 231583.0 - 15217.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_ZZZ_2016"                 ,           0.01398, 231217.0 - 18020.0, LumiScale, 1, FilePath, TrainMode );
      //VHBB
      myBGSampleWeight.QCDSampleInfo_push_back( "_WplusH_HToBB_WToLNu_2016" ,   0.01398, 231217.0 - 18020.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WminusH_HToBB_WToLNu_ext1_2016" ,   0.01398, 231217.0 - 18020.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WminusH_HToBB_WToLNu_2016" ,   0.01398, 231217.0 - 18020.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_ZH_HToBB_ZToLL_2016" ,   0.01398, 231217.0 - 18020.0, LumiScale, 1, FilePath, TrainMode );
      //QCD
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt80To120_EMEnr_2016"     ,     2800000*0.125, 77695287.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt120To170_EMEnr_2016"    ,      477000*0.132, 77771316.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt120To170_EMEnr_ext1_2016"    ,      477000*0.132, 77771316.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt170To300_EMEnr_2016"    ,      114000*0.165, 11540163.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300ToInf_EMEnr_2016"    ,         9000*0.15,  7373633.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt80to120_MuEnrPt5_2016"  ,       106033.6648, 23584215.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt80to120_MuEnrPt5_ext1_2016"  ,       106033.6648, 23584215.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt120to170_MuEnrPt5_2016" ,       25190.51514,  8042721.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt170to300_MuEnrPt5_2016" ,        8654.49315, 17350231.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt170to300_MuEnrPt5_ext1_2016" ,        8654.49315, 17350231.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300to470_MuEnrPt5_2016" ,         797.35269, 48214485.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300to470_MuEnrPt5_ext2_2016" ,         797.35269, 48214485.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt470to600_MuEnrPt5_2016" ,       79.02553776, 19362943.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt470to600_MuEnrPt5_ext1_2016" ,       79.02553776, 19362943.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt470to600_MuEnrPt5_ext2_2016" ,       79.02553776, 19362943.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt600to800_MuEnrPt5_2016" ,       25.09505908,  9981311.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt600to800_MuEnrPt5_ext1_2016" ,       25.09505908,  9981311.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt800to1000_MuEnrPt5_2016",       4.707368272, 19767439.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt800to1000_MuEnrPt5_ext1_2016",       4.707368272, 19767439.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt800to1000_MuEnrPt5_ext2_2016",       4.707368272, 19767439.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt1000toInf_MuEnrPt5_2016",        1.62131692, 13599938.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt1000toInf_MuEnrPt5_ext1_2016",        1.62131692, 13599938.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt_80to170_bcToE_2016"    ,           3221000, 14976689.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt_170to250_bcToE_2016"   ,            105771,  9720760.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt_250toInf_bcToE_2016"   ,           21094.1,  9773617.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      //  }
      //  else if(is2017){
      //FilePath = "FileList/WH_MVABGMCFileList.txt";
      // if(channel.compare("Zh") == 0) FilePath = "FileList/ZH_MVABGMCFileList.txt";

      LumiScale=41529.152;
      //Single Top
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_s_2017"           ,             3.354,8050005.0 - 1864943.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_tW_antitop_2017"  ,              35.6,  7715654.0 - 29622.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_tW_top_2017"      ,              35.6,  7914815.0 - 30427.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_t_antitop_2017"   ,          26.30875,      3675910.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_t_top_2017"       ,           44.2065,      5982064.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      //TTJets
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTTo2L2Nu_2017"           ,             88.29, 68875708.0 - 280100.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTToHadronic_2017"        ,            377.96,129736822.0 - 525618.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTToSemiLeptonic_2017"    ,            365.34, 43555789.0 - 176656.0, LumiScale, 1, FilePath, TrainMode );
      //WJets
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_2017"                 ,           50690, 33043732.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode ); //be careful about kf, already NNLO
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT70to100_2017"       ,           1319, 22229710 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT100to200_2017"       ,           1345, 35804623 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT200to400_2017"       ,           359.7, 21192211.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT400to600_2017"       ,           48.91, 14250114.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT600to800_2017"       ,           12.05, 21582309.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT800to1200_2017"       ,           5.501, 20272990.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT1200to2500_2017"       ,           1.329, 19991892.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT2500toInf_2017"       ,           0.03216, 20629585.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      
      //DY
      // myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_10to50_"    ,             18610, 39837070.0 - 15903.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_M50_2017"	 ,              4895, 97757863.0 - 43076.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_M50_ext1_2017"	 ,              4895, 97757863.0 - 43076.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY1JetsToLL_M50_2017"	 ,              1016, 75971677.0 - 28745.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY1JetsToLL_M50_ext1_2017"	 ,              1016, 75971677.0 - 28745.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY2JetsToLL_M50_2017"	 ,             331.4,  10121430.0 - 5316.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY2JetsToLL_M50_ext1_2017"	 ,             331.4,  10121430.0 - 5316.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY3JetsToLL_M50_2017"	 ,             96.36,   6892913.0 - 5020.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY3JetsToLL_M50_ext1_2017"	 ,             96.36,   6892913.0 - 5020.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY4JetsToLL_M50_2017"	 ,              51.4,   4323202.0 - 5446.0, LumiScale, 1.18, FilePath, TrainMode );
      
      //TG, TTG, TTW, TTZ
      myBGSampleWeight.QCDSampleInfo_push_back( "_TGJets_2017"              ,             2.967,  1140561.0 - 768439.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTGJets_ext1_v2_2017"             ,             3.697,21062657.0 - 9277474.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTGJets_v1_2017"             ,             3.697,21062657.0 - 9277474.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTGJets_ext1_v1_2017"             ,             3.697,21062657.0 - 9277474.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTGJets_2017"             ,             3.697,21062657.0 - 9277474.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTWJetslnu_2017"          ,            0.2043, 3855275.0 - 1139268.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTZJets2l2nu_2017"        ,            0.2529, 5838974.0 - 2093676.0, LumiScale, 1, FilePath, TrainMode );
      //Di-boson
      myBGSampleWeight.QCDSampleInfo_push_back( "_WplusH_HToBB_WToLNu_2017"             ,           0.03369, 2319634.0 - 62866.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_WminusH_HToBB_WToLNu_2017"              ,             0.053, 2412283.0 - 68917.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_ZH_HToBB_ZToLL_2017"              ,             0.053, 2412283.0 - 68917.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_WZ_2017"                  ,             47.13,     3928630.0 - 0.0, LumiScale, 1, FilePath, TrainMode ); //
      //  myBGSampleWeight.QCDSampleInfo_push_back( "_ZZ_"                  ,            16.523,     1925931.0 - 0.0, LumiScale, 1, FilePath, TrainMode ); //
      //Tri-boson
      myBGSampleWeight.QCDSampleInfo_push_back( "_WWW_4F_2017"                 ,            0.2086, 217773.0 - 14527.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WWZ_2017"                 ,            0.1651, 234982.0 - 15018.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WZZ_2017"                 ,           0.05565, 234830.0 - 15170.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_ZZZ_2017"                 ,           0.01398, 232159.0 - 17841.0, LumiScale, 1, FilePath, TrainMode );
      //QCD
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt80To120_EMEnr_"	    ,     2800000*0.125, 9104852.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt120To170_EMEnr_"    ,      477000*0.132, 8515107.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300ToInf_EMEnr_"    ,              1350, 2874295.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt80to120_MuEnrPt5_"  ,       106033.6648,23248995.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt120to170_MuEnrPt5_2017" ,       25190.51514,20774848.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt170to300_MuEnrPt5_2017" ,        8654.49315,46170668.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300to470_MuEnrPt5_2017" ,         797.35269,17744779.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt470to600_MuEnrPt5_2017" ,       79.02553776,24243589.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt_80to170_bcToE_"    ,           3221000,15999466.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt_170to250_bcToE_2017"   ,            105771, 9847660.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt_250toInf_bcToE_2017"   ,           21094.1, 9996886.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      //  }
      //  else if(is2018){
      // FilePath = "FileList/WH_MVABGMCFileList.txt";
      // if(channel.compare("Zh") == 0) FilePath = "FileList/ZH_MVABGMCFileList.txt";

      LumiScale=59740.565;
      //Single Top
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_s_2018"           ,             3.354,16211819.0 - 3753181.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_tW_antitop_2018"  ,              35.6,  7605590.0 - 17410.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_tW_top_2018"      ,              35.6,  9575956.0 - 22044.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_t_antitop_2018"   ,          26.30875,76658965.0 - 2431835.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_t_top_2018"       ,           44.2065,149201191.0 - 5106409.0, LumiScale, 1, FilePath, TrainMode );
      //TTJets
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTTo2L2Nu_2018"           ,             88.29, 64050742.0 - 259258.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTToHadronic_2018"        ,            377.96,133266791.0 - 541209.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTToSemiLeptonic_2018"    ,            365.34,101139378.0 - 410622.0, LumiScale, 1, FilePath, TrainMode );
      //WJets
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_2018"                 ,           50690, 70966439.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode ); //be careful about kf, already NNLO
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT70to100_2018"       ,           1319, 28060302.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT100to200_2018"       ,           1345, 29488310.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT200to400_2018"       ,           359.7, 25423155.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT400to600_2018"       ,           48.91, 5915969.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT600to800_2018"       ,           12.05, 19699782.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT800to1200_2018"       ,           5.501, 8362227.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT1200to2500_2018"       ,           1.329, 7571583.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_HT2500toInf_2018"       ,           0.03216, 3191612.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      
      //DY
      //  myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_10to50_"    ,             18610, 39376427.0 - 15635.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_M50_2018"	 ,              4895,100154500.0 - 40097.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY1JetsToLL_M50_2018"	 ,              1016,106839361.0 - 35389.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY2JetsToLL_M50_2018"	 ,             331.4,  20448554.0 - 7483.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY3JetsToLL_M50_2018"	 ,             96.36,   5649476.0 - 2881.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY4JetsToLL_M50_2018"	 ,              51.4,  2815147.0 - 2665.0, LumiScale, 1.18, FilePath, TrainMode );
      //TG, TTG, TTW, TTZ
      myBGSampleWeight.QCDSampleInfo_push_back( "_TGJets_2018"              ,             2.967,  1152139.0 - 777861.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTGJets_2018"             ,             3.697, 3267151.0 - 1424764.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTWJetslnu_2018"          ,            0.2043, 3799018.0 - 1112923.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTZJets2l2nu_2018"        ,            0.2529, 9777023.0 - 3502977.0, LumiScale, 1, FilePath, TrainMode );
      //Di-boson
      myBGSampleWeight.QCDSampleInfo_push_back( "_WplusH_HToBB_WToLNu_2018"             ,           0.03369, 1926589.0 - 52030.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_WplusH_HToBB_WToLNu_ext1_2018"              ,             0.053, 1892215.0 - 53980.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_WminusH_HToBB_WToLNu_2018"			,           0.04865,6830527.0 - 206173.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_WminusH_HToBB_WToLNu_ext1_2018"			,             118.7,     7850000.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_ZH_HToBB_ZToLL_2018"			,             118.7,     7850000.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_ZH_HToBB_ZToLL_ext1_2018"			,             118.7,     7850000.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WZ_2018"                  ,             47.13,     3885000.0 - 0.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_ZZ_2018"                  ,            16.523,     1979000.0 - 0.0, LumiScale, 1, FilePath, TrainMode ); //
      //Tri-boson
      myBGSampleWeight.QCDSampleInfo_push_back( "_WWW_4F_2018"                 ,            0.2086, 225050.0 - 14950.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WWZ_2018"                 ,            0.1651, 234955.0 - 15045.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WZZ_2018"                 ,           0.05565, 234625.0 - 15375.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_ZZZ_2018"                 ,           0.01398, 232141.0 - 17859.0, LumiScale, 1, FilePath, TrainMode );
      //QCD
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt80To120_EMEnr_2018"	    ,     2800000*0.125, 9648791.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt120To170_EMEnr_2018"    ,      477000*0.132, 9964143.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      //  myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt170To300_EMEnr_2018"    ,             18810, 3712174.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300ToInf_EMEnr_2018"    ,              1350, 2901355.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt80to120_MuEnrPt5_2018"  ,       106033.6648,25652280.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt120to170_MuEnrPt5_" ,       25190.51514,  633668.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt170to300_MuEnrPt5_" ,        8654.49315,35978539.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300to470_MuEnrPt5_2018" ,         797.35269,  492418.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300to470_ext3_MuEnrPt5_2018" ,         797.35269,  492418.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt470to600_MuEnrPt5_2018" ,       79.02553776,  492716.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt470to600_ext1_MuEnrPt5_2018" ,       79.02553776,  492716.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt600to800_MuEnrPt5_2018" ,       25.09505908,16618977.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt800to1000_ext3_MuEnrPt5_2018",  4.707368272,23123897.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt1000toInf_MuEnrPt5_2018",        1.62131692,10719790.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      //  }
      //      myBGSampleWeight.GenLatexTable();
   
    std::cout << "Processing background MC samples..." << std::endl;
    for(std::vector<QCDSampleInfo>::iterator iter_SampleInfos = myBGSampleWeight.QCDSampleInfos.begin(); iter_SampleInfos != myBGSampleWeight.QCDSampleInfos.end(); iter_SampleInfos++)
    { 
      //print out basic information 
      float ls = (*iter_SampleInfos).weight; // luminosity
      std::cout <<"Sample Type: "<< (*iter_SampleInfos).QCDTag << "; LUMI Scale: " << ls << std::endl;
      //Loading chain info
      long long int nTot = (*iter_SampleInfos).chain->GetEntries();
      float WpT, Hmass, HpT, bbdRAve, bbdMMin, HHt, WHdR;
      float lepPt, pfMET, MTw, ljDR;
      (*iter_SampleInfos).chain->SetBranchAddress( "WpT", &WpT );
      (*iter_SampleInfos).chain->SetBranchAddress( "Hmass", &Hmass );
      (*iter_SampleInfos).chain->SetBranchAddress( "HpT", &HpT );
      (*iter_SampleInfos).chain->SetBranchAddress( "bbdRAve", &bbdRAve );
      if(TrainMode.find("QuabMVA") != std::string::npos )
	(*iter_SampleInfos).chain->SetBranchAddress( "bbdMMin", &bbdMMin );
      (*iter_SampleInfos).chain->SetBranchAddress( "HHt", &HHt );
      (*iter_SampleInfos).chain->SetBranchAddress( "WHdR", &WHdR );
      (*iter_SampleInfos).chain->SetBranchAddress( "lepPt", &lepPt );
      (*iter_SampleInfos).chain->SetBranchAddress( "pfMET", &pfMET ); 
      (*iter_SampleInfos).chain->SetBranchAddress( "MTw", &MTw ); 
      (*iter_SampleInfos).chain->SetBranchAddress( "ljDR", &ljDR ); 
      float weight;
      (*iter_SampleInfos).chain->SetBranchAddress( "weight", &weight );
      float xsecWeight;
      (*iter_SampleInfos).chain->SetBranchAddress( "xsecWeight", &xsecWeight );    
      weight *= xsecWeight;

      int lheNJets;
      (*iter_SampleInfos).chain->SetBranchAddress( "lheNJets", &lheNJets );
      //Determine histogram indice
      //  bool isWJets = (*iter_SampleInfos).QCDTag == "_WJets" || (*iter_SampleInfos).QCDTag == "_W1Jets" || (*iter_SampleInfos).QCDTag == "_W2Jets" || (*iter_SampleInfos).QCDTag == "_W3Jets" || (*iter_SampleInfos).QCDTag == "_W4Jets";
      bool isDYJets = (*iter_SampleInfos).QCDTag.find("_DYJetsToLL") != std::string::npos || (*iter_SampleInfos).QCDTag.find("_DY1JetsToLL") != std::string::npos || (*iter_SampleInfos).QCDTag.find("_DY2JetsToLL") != std::string::npos || (*iter_SampleInfos).QCDTag.find("_DY3JetsToLL") != std::string::npos || (*iter_SampleInfos).QCDTag.find("_DY4JetsToLL") != std::string::npos;
      int ih = -1;
      if      ( (*iter_SampleInfos).QCDTag.find("_SingleT") != std::string::npos ) ih = 0;
      else if (
	       ((*iter_SampleInfos).QCDTag.find("_TTJets_") != std::string::npos )
	       ||  ((*iter_SampleInfos).QCDTag.find("_TTTo") != std::string::npos )
	       ) ih = 1;
      else if ( //isWJets )
	       ((*iter_SampleInfos).QCDTag.find("_WJets_") != std::string::npos))
	{
	  ih = 2;
	}
      else if ( isDYJets )
	{
	  ih = 3;
	}
      else if (
	       ( (*iter_SampleInfos).QCDTag.find("_TGJets_") != std::string::npos)
	       || ((*iter_SampleInfos).QCDTag.find("_TTGJets_") != std::string::npos)
	       || ((*iter_SampleInfos).QCDTag.find("_TTWJets") != std::string::npos)
	       || ((*iter_SampleInfos).QCDTag.find("_TTZJets") != std::string::npos)
               //    (*iter_SampleInfos).QCDTag == "_TGJets_" 
               // //|| (*iter_SampleInfos).QCDTag == "_TGJets_ext1_2016"
               // || (*iter_SampleInfos).QCDTag == "_TTGJets_"
               // || (*iter_SampleInfos).QCDTag == "_TTWJetslnu_"
               // || (*iter_SampleInfos).QCDTag == "_TTZJets2l2nu_"
              ) ih = 4;
      else if (
	       ((*iter_SampleInfos).QCDTag.find("_WW_") != std::string::npos)
	       ||  ((*iter_SampleInfos).QCDTag.find("_WW2l2nu_") != std::string::npos)
	       ||  ((*iter_SampleInfos).QCDTag.find("_WWlnu2q_") != std::string::npos)
	       || ((*iter_SampleInfos).QCDTag.find("_ZZ_") != std::string::npos)
	       || ((*iter_SampleInfos).QCDTag.find("_WZ_") != std::string::npos)
	       || ((*iter_SampleInfos).QCDTag.find("_WplusH") != std::string::npos)
	       || ((*iter_SampleInfos).QCDTag.find("_WminusH") != std::string::npos)
	       || ((*iter_SampleInfos).QCDTag.find("_ZH_H") != std::string::npos)
              ) ih = 5;
      else if ( 
                  (*iter_SampleInfos).QCDTag == "_WWW_" 
               || (*iter_SampleInfos).QCDTag == "_WWZ_" 
               || (*iter_SampleInfos).QCDTag == "_WZZ_" 
               || (*iter_SampleInfos).QCDTag == "_ZZZ_" 
              ) ih = 6;
      else if ( (*iter_SampleInfos).QCDTag.find("_QCD") != std::string::npos ) ih = 7;
      else 
      {
        std::cout << "Em... Unclassified sample. Tag: " << (*iter_SampleInfos).QCDTag << std::endl;
      }
      for (long long int ievt = 0; ievt < nTot; ievt++) 
      {
	// if ( isWJets ){ ls = LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(0, lheNJets, yearBits); }
	//        if ( isDYJets ){ (*iter_SampleInfos).QCDTag.find("_10to50_") != std::string::npos ? ls = LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(1, lheNJets, yearBits) : ls = LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(2, lheNJets, yearBits); }

        (*iter_SampleInfos).chain->GetEvent(ievt);
        float mvaout = myTMVAReader.GenReMVAReader
                       (
                        WpT,
                        Hmass, HpT, bbdRAve, bbdMMin, HHt,
                        WHdR, lepPt, pfMET, MTw, ljDR,
                        "Haa4bSBClassification" + TrainMode
                       );
        if ( ih >= 0 )
        {
          (myMVACutFlowHist.h_b_WpT_BGMC[ih])->Fill( WpT, weight * ls );
	  (myMVACutFlowHist.h_b_WpT_BGMC[8])->Fill( WpT, weight * ls );   // Fill for all bkgMC 
	  
          (myMVACutFlowHist.h_b_Hmass_BGMC[ih])->Fill( Hmass, weight * ls );
	  (myMVACutFlowHist.h_b_Hmass_BGMC[8])->Fill( Hmass, weight * ls );    

          (myMVACutFlowHist.h_b_HpT_BGMC[ih])->Fill( HpT, weight * ls );
	  (myMVACutFlowHist.h_b_HpT_BGMC[8])->Fill( HpT, weight * ls );    

          (myMVACutFlowHist.h_b_bbdRAve_BGMC[ih])->Fill( bbdRAve, weight * ls );
	  (myMVACutFlowHist.h_b_bbdRAve_BGMC[8])->Fill( bbdRAve, weight * ls );   

           if(TrainMode.find("QuabMVA") != std::string::npos )
	     (myMVACutFlowHist.h_b_bbdMMin_BGMC[ih])->Fill( bbdMMin, weight * ls );
	   if(TrainMode.find("QuabMVA") != std::string::npos )
	     (myMVACutFlowHist.h_b_bbdMMin_BGMC[8])->Fill( bbdMMin, weight * ls ); 

          (myMVACutFlowHist.h_b_HHt_BGMC[ih])->Fill( HHt, weight * ls );
	  (myMVACutFlowHist.h_b_HHt_BGMC[8])->Fill( HHt, weight * ls );  

          (myMVACutFlowHist.h_b_WHdR_BGMC[ih])->Fill( WHdR, weight * ls );
	  (myMVACutFlowHist.h_b_WHdR_BGMC[8])->Fill( WHdR, weight * ls );        

	  (myMVACutFlowHist.h_b_lepPt_BGMC[ih])->Fill( lepPt, weight * ls ); 
	  (myMVACutFlowHist.h_b_lepPt_BGMC[8])->Fill( lepPt, weight * ls );   

          (myMVACutFlowHist.h_b_pfMET_BGMC[ih])->Fill( pfMET, weight * ls ); 
	  (myMVACutFlowHist.h_b_pfMET_BGMC[8])->Fill( pfMET, weight * ls );   

          (myMVACutFlowHist.h_b_MTw_BGMC[ih])->Fill( MTw, weight * ls ); 
	  (myMVACutFlowHist.h_b_MTw_BGMC[8])->Fill( MTw, weight * ls );     

          (myMVACutFlowHist.h_b_ljDR_BGMC[ih])->Fill( ljDR, weight * ls ); 
	  (myMVACutFlowHist.h_b_ljDR_BGMC[8])->Fill( ljDR, weight * ls ); 

          (myMVACutFlowHist.h_b_BDT_BGMC[ih])->Fill( mvaout, weight * ls );
	  (myMVACutFlowHist.h_b_BDT_BGMC[8])->Fill( mvaout, weight * ls );        

          int lobin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout, TrainMode ).first, hibin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout, TrainMode ).second;
          if ( hibin >= 0 )
          {
            for ( int j = lobin; j <= hibin ; j++ )
            {
              (myMVACutFlowHist.h_b_n_BGMC[ih])->Fill( j, weight * ls );
	      (myMVACutFlowHist.h_b_n_BGMC[8])->Fill( j, weight * ls );              
              weight >= 0 ? (myMVACutFlowHist.h_b_posW_BGMC[ih])->Fill( j, weight * ls ) : (myMVACutFlowHist.h_b_negW_BGMC[ih])->Fill( j, -weight * ls );
	      weight >= 0 ? (myMVACutFlowHist.h_b_posW_BGMC[8])->Fill( j, weight * ls ) : (myMVACutFlowHist.h_b_negW_BGMC[8])->Fill( j, -weight * ls );        
            }
          }
          //else 
          //{ 
            //(myMVACutFlowHist.h_b_n_BGMC[ih])->Fill( 0.0, weight * ls );
          //}
        }
      
      }
    }


    myTMVAReader.CloseMVAReader();
    (myMVACutFlowHist.oFile)->Write();
    (myMVACutFlowHist.oFile)->Close();
    return 0;
  }
  else 
  {
    std::cout << "Invalid run mode" << std::endl;
    return -1;
  }
  return -1;
}
