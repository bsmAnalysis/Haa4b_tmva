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
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=6:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=7:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=8:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=9:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5%:MaxDepth=15:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=1%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=2.5%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=5.0%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=7.5%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=10%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=15%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=20%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=25%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
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
    std::string dir_out = "OutDir/";
    myMVACutFlowHist.BookHistgram( (dir_out + "MVACutFlow" + TrainMode + ".root").c_str() );
    
    TMVAReader myTMVAReader;
    myTMVAReader.InitTMVAReader();
    myTMVAReader.SetupMVAReader( "Haa4bSBClassification" + TrainMode, "dataset/weights/Haa4bSBClassification" + TrainMode + "_BDT.weights.xml" );
 
    QCDSampleWeight mySGSampleWeight;
    //    mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass12"  , 0.8594*0.067316, 397600 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    // mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass15"  , 0.8594*0.067316, 399120 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass20"  , 0.8594*0.067316, 383440 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );  
					      //0.8594*0.067316, 487600 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );  //383440 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass25"  ,0.8594*0.067316, 399360 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode ); 
					      //0.8594*0.067316, 493600 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );      //399360 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass30"  ,0.8594*0.067316, 399560 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode ); 
					      //0.8594*0.067316, 498500 - 0  , LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode ); //399560 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass40"  ,0.8594*0.067316, 398000 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );
					      //0.8594*0.067316, 500000 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode ); //398000 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass50"  , 0.8594*0.067316, 399000 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );  
					      //0.8594*0.067316, 498600 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );  //399000 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass60"  ,0.8594*0.067316, 398720 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode ); 
					      //0.8594*0.067316, 500000 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );  //398720 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );

    std::cout << "Processing signal MC samples..." << std::endl;
    for(std::vector<QCDSampleInfo>::iterator iter_SampleInfos = mySGSampleWeight.QCDSampleInfos.begin(); iter_SampleInfos != mySGSampleWeight.QCDSampleInfos.end(); iter_SampleInfos++)
    { 
      //print out basic information 
      float ls = (*iter_SampleInfos).weight; 
      std::cout <<"Sample Type: "<< (*iter_SampleInfos).QCDTag << "; LUMI Scale: " << ls << std::endl;
      //Loading chain info
      long long int nTot = (*iter_SampleInfos).chain->GetEntries();
      float WpT, Hmass, HpT, bbdRAve, bbdMMin, HHt, WHdR;
      float lepPt, pfMET, MTw, ljDR;
      (*iter_SampleInfos).chain->SetBranchAddress( "WpT", &WpT );
      (*iter_SampleInfos).chain->SetBranchAddress( "Hmass", &Hmass );
      (*iter_SampleInfos).chain->SetBranchAddress( "HpT", &HpT );
      (*iter_SampleInfos).chain->SetBranchAddress( "bbdRAve", &bbdRAve );
      (*iter_SampleInfos).chain->SetBranchAddress( "bbdMMin", &bbdMMin );
      (*iter_SampleInfos).chain->SetBranchAddress( "HHt", &HHt );
      (*iter_SampleInfos).chain->SetBranchAddress( "WHdR", &WHdR );
      (*iter_SampleInfos).chain->SetBranchAddress( "lepPt", &lepPt );  
      (*iter_SampleInfos).chain->SetBranchAddress( "pfMET", &pfMET );  
      (*iter_SampleInfos).chain->SetBranchAddress( "MTw", &MTw );  
      (*iter_SampleInfos).chain->SetBranchAddress( "ljDR", &ljDR );  
      float weight;
      (*iter_SampleInfos).chain->SetBranchAddress( "weight", &weight );

      //Determine histogram indice
      int ih = -1;
      if      ( (*iter_SampleInfos).QCDTag == "_Zh_amass12" ) ih = 0;
      else if ( (*iter_SampleInfos).QCDTag == "_Zh_amass15" ) ih = 1;
      else if ( (*iter_SampleInfos).QCDTag == "_Zh_amass20" ) ih = 2;
      else if ( (*iter_SampleInfos).QCDTag == "_Zh_amass25" ) ih = 3;
      else if ( (*iter_SampleInfos).QCDTag == "_Zh_amass30" ) ih = 4;
      else if ( (*iter_SampleInfos).QCDTag == "_Zh_amass40" ) ih = 5;
      else if ( (*iter_SampleInfos).QCDTag == "_Zh_amass50" ) ih = 6;
      else if ( (*iter_SampleInfos).QCDTag == "_Zh_amass60" ) ih = 7;

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
        /*
        if ( ievt < 20 )
        {
          std::cout << "MVA output : " << mvaout << ", [" << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout, TrainMode ).first << ","  << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout, TrainMode ).second << "]" << std::endl;
          std::cout << "Weight: " << weight << std::endl;
          //std::cout << "MVA vars : " << WpT << "," << Hmass << std::endl;
          //std::cout << "MVA vars : " << myTMVAReader.WpT << "," << myTMVAReader.Hmass << std::endl;
        }
        */
      }
    }

    QCDSampleWeight myBGSampleWeight;
    //    float TTbar_SingleLept_BR = 0.43930872; // 2*W_Lept_BR*(1-W_Lept_BR)
    //    float TTbar_DiLept_BR = 0.10614564; // W_Lept_BR^2

    //Single Top
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_s"           ,             3.362, 811495 - 188505, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_atW"         ,              35.6,     6933094 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_tW"          ,              35.6,     6952830 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_at"          ,             80.95,    38303066 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_t"           ,            136.02,    66240656 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    //TTJets
    //myBGSampleWeight.QCDSampleInfo_push_back( "_TTJets_"              ,            831.76, 29849450 - 14501083, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_TTJets_"              ,            831.76, 77081156 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    //myBGSampleWeight.QCDSampleInfo_push_back( "_TTJets_slt_"          ,            831.76*0.5*TTbar_SingleLept_BR, 61973977 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    //myBGSampleWeight.QCDSampleInfo_push_back( "_TTJets_slt_ext1_"     ,            831.76*0.5*TTbar_SingleLept_BR, 61973977 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    //myBGSampleWeight.QCDSampleInfo_push_back( "_TTJets_slat_"         ,            831.76*0.5*TTbar_SingleLept_BR, 60210394 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    //myBGSampleWeight.QCDSampleInfo_push_back( "_TTJets_slat_ext1_"    ,            831.76*0.5*TTbar_SingleLept_BR, 60210394 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    //myBGSampleWeight.QCDSampleInfo_push_back( "_TTJets_dl_"           ,            831.76*TTbar_DiLept_BR, 30444678 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    //myBGSampleWeight.QCDSampleInfo_push_back( "_TTJets_dl_ext1_"      ,            831.76*TTbar_DiLept_BR, 30444678 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    //WJets
    //myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_"                 ,           61526.7, 20308674 - 3811645, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );

    myBGSampleWeight.QCDSampleInfo_push_back( "_WJets"                 ,           50690, 86731806 - 0, LumiScale, 1.21, "FileList/MVABGMCFileList.txt", TrainMode ); //be careful about kf, already NNLO
    myBGSampleWeight.QCDSampleInfo_push_back( "_W1Jets"                ,              9493, 45367044 - 0, LumiScale, 1.21, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_W2Jets"                ,              3120, 60039784 - 0, LumiScale, 1.21, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_W3Jets"                ,             942.3, 56623793 - 0, LumiScale, 1.21, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_W4Jets"                ,             524.2, 29995313 - 0, LumiScale, 1.21, "FileList/MVABGMCFileList.txt", TrainMode );
    //DY [10,50]
    myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_10to50"    ,             18610,  35291566 - 0, LumiScale, 1.21, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_DY1JetsToLL_10to50"   ,               725,  39840774 - 0, LumiScale, 1.21, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_DY2JetsToLL_10to50"   ,             394.5,  19442927 - 0, LumiScale, 1.21, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_DY3JetsToLL_10to50"   ,             96.47,   4964197 - 0, LumiScale, 1.21, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_DY4JetsToLL_10to50"   ,             34.84,   2087849 - 0, LumiScale, 1.21, "FileList/MVABGMCFileList.txt", TrainMode );
    // DY [50,Inf]
    myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_50toInf"   ,            4895, 145803217 - 0, LumiScale, 1.17, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_DY1JetsToLL_50toInf"  ,              1016,  62627174 - 0, LumiScale, 1.17, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_DY2JetsToLL_50toInf"  ,             331.4,  19970551 - 0, LumiScale, 1.17, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_DY3JetsToLL_50toInf"  ,             96.36,   5856110 - 0, LumiScale, 1.17, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_DY4JetsToLL_50toInf"  ,              51.4,   4197868 - 0, LumiScale, 1.17, "FileList/MVABGMCFileList.txt", TrainMode );
    //TG, TTG, TTW, TTZ
    myBGSampleWeight.QCDSampleInfo_push_back( "_TGJets"              ,             2.967, 1109033 - 740471, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    //myBGSampleWeight.QCDSampleInfo_push_back( "_TGJets_ext1_2016"     ,        2.967*0.75, 1, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //ext1, 0.75
    myBGSampleWeight.QCDSampleInfo_push_back( "_TTGJets"             ,             3.697, 3224372 - 1646539, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_TTWJetslnu"          ,            0.2043, 2361962 - 758435, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_TTZJets2l2nu_"        ,            0.2529, 1068793 - 389531, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    //Di-boson
    myBGSampleWeight.QCDSampleInfo_push_back( "_WW2l2nu"             ,            12.178, 1999000 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WWlnu2q"             ,            49.997, 8997800 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //
    myBGSampleWeight.QCDSampleInfo_push_back( "_WZ"                  ,             47.13, 3995828 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //
    myBGSampleWeight.QCDSampleInfo_push_back( "_ZZ"                  ,            16.523, 1988098 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //
    //Tri-boson
    myBGSampleWeight.QCDSampleInfo_push_back( "_WWW"                 ,            0.2086, 225269 - 14731, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WWZ"                 ,            0.1651, 235734 - 14266, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WZZ"                 ,           0.05565, 231583 - 15217, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_ZZZ"                 ,           0.01398, 231217 - 18020, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    //QCD
    //myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt50To80_EMEnr_"  ,    19800000*0.146, 23474171 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt80To120_EMEnr" ,     2800000*0.125, 35841783 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt120To170_EMEnr",      477000*0.132, 35817281 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt170To300_EMEnr",      114000*0.165, 11540163 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300ToInf_EMEnr",         9000*0.15,  7373633 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt20ToInf_MuEnr" , 720648000*0.00042, 22094081 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.GenLatexTable();
    //return 0;
    //return -1;
    std::cout << "Processing background MC samples..." << std::endl;
    for(std::vector<QCDSampleInfo>::iterator iter_SampleInfos = myBGSampleWeight.QCDSampleInfos.begin(); iter_SampleInfos != myBGSampleWeight.QCDSampleInfos.end(); iter_SampleInfos++)
    { 
      //print out basic information 
      float ls = (*iter_SampleInfos).weight;
      std::cout <<"Sample Type: "<< (*iter_SampleInfos).QCDTag << "; LUMI Scale: " << ls << std::endl;
      //Loading chain info
      long long int nTot = (*iter_SampleInfos).chain->GetEntries();
      float WpT, Hmass, HpT, bbdRAve, bbdMMin, HHt, WHdR;
      float lepPt, pfMET, MTw, ljDR;
      (*iter_SampleInfos).chain->SetBranchAddress( "WpT", &WpT );
      (*iter_SampleInfos).chain->SetBranchAddress( "Hmass", &Hmass );
      (*iter_SampleInfos).chain->SetBranchAddress( "HpT", &HpT );
      (*iter_SampleInfos).chain->SetBranchAddress( "bbdRAve", &bbdRAve );
      (*iter_SampleInfos).chain->SetBranchAddress( "bbdMMin", &bbdMMin );
      (*iter_SampleInfos).chain->SetBranchAddress( "HHt", &HHt );
      (*iter_SampleInfos).chain->SetBranchAddress( "WHdR", &WHdR );
      (*iter_SampleInfos).chain->SetBranchAddress( "lepPt", &lepPt );
      (*iter_SampleInfos).chain->SetBranchAddress( "pfMET", &pfMET ); 
      (*iter_SampleInfos).chain->SetBranchAddress( "MTw", &MTw ); 
      (*iter_SampleInfos).chain->SetBranchAddress( "ljDR", &ljDR ); 
      float weight;
      (*iter_SampleInfos).chain->SetBranchAddress( "weight", &weight );
      int lheNJets;
      (*iter_SampleInfos).chain->SetBranchAddress( "lheNJets", &lheNJets );
      //Determine histogram indice
      bool isWJets = (*iter_SampleInfos).QCDTag == "_WJets" || (*iter_SampleInfos).QCDTag == "_W1Jets" || (*iter_SampleInfos).QCDTag == "_W2Jets" || (*iter_SampleInfos).QCDTag == "_W3Jets" || (*iter_SampleInfos).QCDTag == "_W4Jets";
      bool isDYJets = (*iter_SampleInfos).QCDTag.find("_DYJetsToLL") != std::string::npos || (*iter_SampleInfos).QCDTag.find("_DY1JetsToLL") != std::string::npos || (*iter_SampleInfos).QCDTag.find("_DY2JetsToLL") != std::string::npos || (*iter_SampleInfos).QCDTag.find("_DY3JetsToLL") != std::string::npos || (*iter_SampleInfos).QCDTag.find("_DY4JetsToLL") != std::string::npos;
      int ih = -1;
      if      ( (*iter_SampleInfos).QCDTag.find("_SingleT") != std::string::npos ) ih = 0;
      else if (   (*iter_SampleInfos).QCDTag == "_TTJets_" 
               || (*iter_SampleInfos).QCDTag == "_TTJets_slt_"
               || (*iter_SampleInfos).QCDTag == "_TTJets_slat_"
               || (*iter_SampleInfos).QCDTag == "_TTJets_dl_"
              ) ih = 1;
      else if ( isWJets )
      {
        ih = 2;
        std::cout << "W0Jets: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(0, 0) << std::endl;
        std::cout << "W1Jets: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(0, 1) << std::endl;
        std::cout << "W2Jets: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(0, 2) << std::endl;
        std::cout << "W3Jets: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(0, 3) << std::endl;
        std::cout << "W4Jets: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(0, 4) << std::endl;
      }
      else if ( isDYJets )
      {
        ih = 3;
        if( (*iter_SampleInfos).QCDTag.find("_10to50") != std::string::npos )
        {
          std::cout << "DY0Jets_10to50: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(1, 0) << std::endl;
          std::cout << "DY1Jets_10to50: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(1, 1) << std::endl;
          std::cout << "DY2Jets_10to50: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(1, 2) << std::endl;
          std::cout << "DY3Jets_10to50: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(1, 3) << std::endl;
          std::cout << "DY4Jets_10to50: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(1, 4) << std::endl;
        }
        else
        {
          std::cout << "DY0Jets_50toInf: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(2, 0) << std::endl;
          std::cout << "DY1Jets_50toInf: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(2, 1) << std::endl;
          std::cout << "DY2Jets_50toInf: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(2, 2) << std::endl;
          std::cout << "DY3Jets_50toInf: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(2, 3) << std::endl;
          std::cout << "DY4Jets_50toInf: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(2, 4) << std::endl;
        }
      }
      else if ( 
                  (*iter_SampleInfos).QCDTag == "_TGJets" 
               //|| (*iter_SampleInfos).QCDTag == "_TGJets_ext1_2016"
               || (*iter_SampleInfos).QCDTag == "_TTGJets"
               || (*iter_SampleInfos).QCDTag == "_TTWJetslnu"
               || (*iter_SampleInfos).QCDTag == "_TTZJets2l2nu"
              ) ih = 4;
      else if ( 
                  (*iter_SampleInfos).QCDTag == "_WW2l2nu" 
               || (*iter_SampleInfos).QCDTag == "_WWlnu2q"
               //|| (*iter_SampleInfos).QCDTag == "_WWlnu2q_ext1_2016"
               || (*iter_SampleInfos).QCDTag == "_WZ"
               //|| (*iter_SampleInfos).QCDTag == "_WZ_ext1_2016"
               || (*iter_SampleInfos).QCDTag == "_ZZ"
               //|| (*iter_SampleInfos).QCDTag == "_ZZ_ext1_2016"
              ) ih = 5;
      else if ( 
                  (*iter_SampleInfos).QCDTag == "_WWW" 
               || (*iter_SampleInfos).QCDTag == "_WWZ" 
               || (*iter_SampleInfos).QCDTag == "_WZZ" 
               || (*iter_SampleInfos).QCDTag == "_ZZZ" 
              ) ih = 6;
      else if ( (*iter_SampleInfos).QCDTag.find("_QCD_Pt") != std::string::npos ) ih = 7;
      else 
      {
        std::cout << "Em... Unclassified sample. Tag: " << (*iter_SampleInfos).QCDTag << std::endl;
      }
      for (long long int ievt = 0; ievt < nTot; ievt++) 
      {
        if ( isWJets ){ ls = LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(0, lheNJets); }
        if ( isDYJets ){ (*iter_SampleInfos).QCDTag.find("_10to50") != std::string::npos ? ls = LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(1, lheNJets) : ls = LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(2, lheNJets); }

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

          (myMVACutFlowHist.h_b_bbdMMin_BGMC[ih])->Fill( bbdMMin, weight * ls );
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
        /*
        if ( ievt < 20 )
        {
          std::cout << "MVA output : " << mvaout << ", [" << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout, TrainMode ).first << ","  << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout, TrainMode ).second << "]" << std::endl;
          std::cout << "Weight: " << weight << std::endl;
          //std::cout << "MVA vars : " << WpT << "," << Hmass << std::endl;
          //std::cout << "MVA vars : " << myTMVAReader.WpT << "," << myTMVAReader.Hmass << std::endl;
        }
        */
      }
    }

    QCDSampleWeight myDataSampleWeight;
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016B_ver2"  , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016C"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016D"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016E"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016F"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016G"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    //myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016G"       , 1  , 1, LumiScale/7544.01559, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016H_ver2"  , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016H_ver3"  , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016B_ver2"  , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016C"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016D"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016E"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016F"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016G"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    //myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016G"       , 1  , 1, LumiScale/7544.01559, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016H_ver2"  , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016H_ver3"  , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    std::cout << "Processing data samples..." << std::endl;
    for(std::vector<QCDSampleInfo>::iterator iter_SampleInfos = myDataSampleWeight.QCDSampleInfos.begin(); iter_SampleInfos != myDataSampleWeight.QCDSampleInfos.end(); iter_SampleInfos++)
    {
      float ls = (*iter_SampleInfos).weight;
      //print out basic information 
      std::cout <<"Sample Type: "<< (*iter_SampleInfos).QCDTag << "; Lumi Scale: " << ls << std::endl;
      //Loading chain info
      long long int nTot = (*iter_SampleInfos).chain->GetEntries();
      float WpT, Hmass, HpT, bbdRAve, bbdMMin, HHt, WHdR;
      float lepPt, pfMET, MTw, ljDR;
      (*iter_SampleInfos).chain->SetBranchAddress( "WpT", &WpT );
      (*iter_SampleInfos).chain->SetBranchAddress( "Hmass", &Hmass );
      (*iter_SampleInfos).chain->SetBranchAddress( "HpT", &HpT );
      (*iter_SampleInfos).chain->SetBranchAddress( "bbdRAve", &bbdRAve );
      (*iter_SampleInfos).chain->SetBranchAddress( "bbdMMin", &bbdMMin );
      (*iter_SampleInfos).chain->SetBranchAddress( "HHt", &HHt );
      (*iter_SampleInfos).chain->SetBranchAddress( "WHdR", &WHdR );
      (*iter_SampleInfos).chain->SetBranchAddress( "lepPt", &lepPt );
      (*iter_SampleInfos).chain->SetBranchAddress( "pfMET", &pfMET ); 
      (*iter_SampleInfos).chain->SetBranchAddress( "MTw", &MTw ); 
      (*iter_SampleInfos).chain->SetBranchAddress( "ljDR", &ljDR );      
      float weight;
      (*iter_SampleInfos).chain->SetBranchAddress( "weight", &weight );

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
        (myMVACutFlowHist.h_b_WpT_Data)->Fill( WpT, weight * ls );
        (myMVACutFlowHist.h_b_Hmass_Data)->Fill( Hmass, weight * ls );
        (myMVACutFlowHist.h_b_HpT_Data)->Fill( HpT, weight * ls );
        (myMVACutFlowHist.h_b_bbdRAve_Data)->Fill( bbdRAve, weight * ls );
        (myMVACutFlowHist.h_b_bbdMMin_Data)->Fill( bbdMMin, weight * ls );
        (myMVACutFlowHist.h_b_HHt_Data)->Fill( HHt, weight * ls );
        (myMVACutFlowHist.h_b_WHdR_Data)->Fill( WHdR, weight * ls );
	(myMVACutFlowHist.h_b_lepPt_Data)->Fill( lepPt, weight * ls );                                                                                                                                                                 
	(myMVACutFlowHist.h_b_pfMET_Data)->Fill( pfMET, weight * ls ); 
	(myMVACutFlowHist.h_b_MTw_Data)->Fill( MTw, weight * ls ); 
	(myMVACutFlowHist.h_b_ljDR_Data)->Fill( ljDR, weight * ls ); 
        (myMVACutFlowHist.h_b_BDT_Data)->Fill( mvaout, weight * ls );

        int lobin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout, TrainMode ).first, hibin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout, TrainMode ).second;
        if ( hibin >= 0 )
        {
          for ( int j = lobin; j <= hibin ; j++ )
          {
            (myMVACutFlowHist.h_b_n_Data)->Fill( j, weight * ls );
            //(myMVACutFlowHist.h_b_n_Data)->Fill( j, 1 );
          }
        }
        //else 
        //{ 
          //(myMVACutFlowHist.h_b_n_Data)->Fill( 0.0, weight * ls );
          //(myMVACutFlowHist.h_b_n_Data)->Fill( 0.0, 1 );
        //}
        /*
        if ( ievt < 20 )
        {
          std::cout << "MVA output : " << mvaout << ", [" << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout, TrainMode ).first << ","  << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout, TrainMode ).second << "]" << std::endl;
          std::cout << "Weight: " << weight << std::endl;
          //std::cout << "MVA vars : " << WpT << "," << Hmass << std::endl;
          //std::cout << "MVA vars : " << myTMVAReader.WpT << "," << myTMVAReader.Hmass << std::endl;
        }
        */
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
