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
    TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=10%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=15%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=20%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
    //TestBDTparStringVec.push_back("!H:!V:NegWeightTreatment=InverseBoostNegWeights:NTrees=350:MinNodeSize=25%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");

    TMVATrainer myTMVATrainer;
    myTMVATrainer.InitTMVAFactory("MVACVTestOut" + TrainMode + ".root", "Haa4bSBClassification" + TrainMode);
    myTMVATrainer.SetupMVAFactory(TrainMode);
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
    mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass12"  , 1.37, 397200 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass15"  , 1.37, 399720 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass20"  , 1.37, 383080 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass25"  , 1.37, 399000 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass30"  , 1.37, 399560 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass40"  , 1.37, 397560 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass50"  , 1.37, 399200 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass60"  , 1.37, 398280 - 0, LumiScale, 1, "FileList/MVASGMCFileList.txt", TrainMode );

    std::cout << "Processing signal MC samples..." << std::endl;
    for(std::vector<QCDSampleInfo>::iterator iter_SampleInfos = mySGSampleWeight.QCDSampleInfos.begin(); iter_SampleInfos != mySGSampleWeight.QCDSampleInfos.end(); iter_SampleInfos++)
    { 
      //print out basic information 
      float ls = (*iter_SampleInfos).weight; 
      std::cout <<"Sample Type: "<< (*iter_SampleInfos).QCDTag << "; LUMI Scale: " << ls << std::endl;
      //Loading chain info
      long long int nTot = (*iter_SampleInfos).chain->GetEntries();
      float WpT, Hmass, HpT, bbdRAve, bbdMMin, HHt, WHdR;
      (*iter_SampleInfos).chain->SetBranchAddress( "WpT", &WpT );
      (*iter_SampleInfos).chain->SetBranchAddress( "Hmass", &Hmass );
      (*iter_SampleInfos).chain->SetBranchAddress( "HpT", &HpT );
      (*iter_SampleInfos).chain->SetBranchAddress( "bbdRAve", &bbdRAve );
      (*iter_SampleInfos).chain->SetBranchAddress( "bbdMMin", &bbdMMin );
      (*iter_SampleInfos).chain->SetBranchAddress( "HHt", &HHt );
      (*iter_SampleInfos).chain->SetBranchAddress( "WHdR", &WHdR );
      float weight;
      (*iter_SampleInfos).chain->SetBranchAddress( "weight", &weight );

      //Determine histogram indice
      int ih = -1;
      if      ( (*iter_SampleInfos).QCDTag == "_Wh_amass12" ) ih = 0;
      else if ( (*iter_SampleInfos).QCDTag == "_Wh_amass15" ) ih = 1;
      else if ( (*iter_SampleInfos).QCDTag == "_Wh_amass20" ) ih = 2;
      else if ( (*iter_SampleInfos).QCDTag == "_Wh_amass25" ) ih = 3;
      else if ( (*iter_SampleInfos).QCDTag == "_Wh_amass30" ) ih = 4;
      else if ( (*iter_SampleInfos).QCDTag == "_Wh_amass40" ) ih = 5;
      else if ( (*iter_SampleInfos).QCDTag == "_Wh_amass50" ) ih = 6;
      else if ( (*iter_SampleInfos).QCDTag == "_Wh_amass60" ) ih = 7;

      for (long long int ievt = 0; ievt < nTot; ievt++) 
      {
        (*iter_SampleInfos).chain->GetEvent(ievt);
        float mvaout = myTMVAReader.GenReMVAReader
                       (
                        WpT,
                        Hmass, HpT, bbdRAve, bbdMMin, HHt,
                        WHdR,
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

          (myMVACutFlowHist.h_b_BDT_SGMC[ih])->Fill( mvaout, weight * ls );

          int lobin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).first, hibin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).second;
          if ( hibin >= 0 )
          {
            for ( int j = lobin; j <= hibin ; j++ )
            {
              (myMVACutFlowHist.h_b_n_SGMC[ih])->Fill( j, weight * ls );
              //(myMVACutFlowHist.h_b_n_SGMC[ih])->Fill( j, 1.0 );
            }
          }
          else
          { 
            (myMVACutFlowHist.h_b_n_SGMC[ih])->Fill( 0.0, weight * ls );
            //(myMVACutFlowHist.h_b_n_SGMC[ih])->Fill( 0.0, 1.0 );
          }
        }
        /*
        if ( ievt < 20 )
        {
          std::cout << "MVA output : " << mvaout << ", [" << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).first << ","  << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).second << "]" << std::endl;
          std::cout << "Weight: " << weight << std::endl;
          //std::cout << "MVA vars : " << WpT << "," << Hmass << std::endl;
          //std::cout << "MVA vars : " << myTMVAReader.WpT << "," << myTMVAReader.Hmass << std::endl;
        }
        */
      }
    }

    QCDSampleWeight myBGSampleWeight;
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_s_"           ,             3.362, 811495 - 188505, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_atW_"         ,              35.6, 6933094 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_tW_"          ,              35.6, 6952830 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_at_"          ,             80.95, 37904304 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_t_"           ,            136.02, 67240808 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_TTJets_"              ,            831.76, 29849450 - 14501083, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WJets"                ,           61526.7, 20308674 - 3811645, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_10to50_"   ,             18610, 26709558 - 4211038, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_50toInf_"  ,            5765.4, 101918226 - 20137162, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_TGJets_"              ,             2.967, 1109033 - 740471, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //
    //myBGSampleWeight.QCDSampleInfo_push_back( "_TGJets_ext1_2016"     ,        2.967*0.75, 1, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //ext1, 0.75
    myBGSampleWeight.QCDSampleInfo_push_back( "_TTGJets_"             ,             3.697, 3224372 - 1646539, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_TTWJetslnu_"          ,            0.2043, 2361962 - 758435, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_TTZJets2l2nu_"        ,            0.2529, 1460207 - 532231, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WW2l2nu_"             ,            12.178, 1999000 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WWlnu2q_"             ,            49.997, 8997800 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //
    //myBGSampleWeight.QCDSampleInfo_push_back( "_WWlnu2q_ext1_2016"    ,        49.997*0.5, 1, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //ext1, 0.5
    myBGSampleWeight.QCDSampleInfo_push_back( "_WZ_"                  ,             47.13, 3871065 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //
    //myBGSampleWeight.QCDSampleInfo_push_back( "_WZ_ext1_2016"         ,        47.13*0.75, 1, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //ext1, 0.75
    myBGSampleWeight.QCDSampleInfo_push_back( "_ZZ_"                  ,            16.523, 1988098 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //
    //myBGSampleWeight.QCDSampleInfo_push_back( "_ZZ_ext1_2016"         ,        16.523*0.5, 1, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //ext1, 0.5
    myBGSampleWeight.QCDSampleInfo_push_back( "_WWW_"                 ,            0.2086, 225269 - 14731, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WWZ_"                 ,            0.1651, 235734 - 14266, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WZZ_"                 ,           0.05565, 231583 - 15217, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_ZZZ_"                 ,           0.01398, 231217 - 18020, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt50To80_EMEnr_"  ,    19800000*0.146, 23474171 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt80To120_EMEnr_" ,     2800000*0.125, 35841783 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt120To170_EMEnr_",      477000*0.132, 35817281 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt170To300_EMEnr_",      114000*0.165, 11540163 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300ToInf_EMEnr_",         9000*0.15,  7373633 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt20ToInf_MuEnr_" , 720648000*0.00042, 22094081 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    /*
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_s_"           ,             3.362, 273964 - 63274, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_atW_"         ,              35.6, 1819852 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_tW_"          ,              35.6, 1827501 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_at_"          ,             80.95, 4897626 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_t_"           ,            136.02, 8283432 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_TTJets_"              ,            831.76, 7777144 - 3797606, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WJets"                ,           61526.7, 4965322 - 926405, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_10to50_"   ,             18610, 445741 - 96962, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_50toInf_"  ,            5765.4, 43171824 - 8637336, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_TGJets_"              ,             2.967, 175353 - 117249, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //
    //myBGSampleWeight.QCDSampleInfo_push_back( "_TGJets_ext1_2016"     ,        2.967*0.75, 1, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //ext1, 0.75
    myBGSampleWeight.QCDSampleInfo_push_back( "_TTGJets_"             ,             3.697, 960762 - 490841, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_TTWJetslnu_"          ,            0.2043, 1314867 - 418913, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_TTZJets2l2nu_"        ,            0.2529, 644662 - 235225, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WW2l2nu_"             ,            12.178, 1136158 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WWlnu2q_"             ,            49.997, 2961960 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //
    //myBGSampleWeight.QCDSampleInfo_push_back( "_WWlnu2q_ext1_2016"    ,        49.997*0.5, 1, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //ext1, 0.5
    myBGSampleWeight.QCDSampleInfo_push_back( "_WZ_"                  ,             47.13, 604179 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //
    //myBGSampleWeight.QCDSampleInfo_push_back( "_WZ_ext1_2016"         ,        47.13*0.75, 1, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //ext1, 0.75
    myBGSampleWeight.QCDSampleInfo_push_back( "_ZZ_"                  ,            16.523, 224882 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //
    //myBGSampleWeight.QCDSampleInfo_push_back( "_ZZ_ext1_2016"         ,        16.523*0.5, 1, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode ); //ext1, 0.5
    myBGSampleWeight.QCDSampleInfo_push_back( "_WWW_"                 ,            0.2086, 76326 - 4821, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WWZ_"                 ,            0.1651, 72520 - 4243, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WZZ_"                 ,           0.05565, 56533 - 3496, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_ZZZ_"                 ,           0.01398, 42109 - 3274, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt50To80_EMEnr_"  ,    19800000*0.146, 29782 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt80To120_EMEnr_" ,     2800000*0.125, 86939 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt120To170_EMEnr_",      477000*0.132, 148333 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt170To300_EMEnr_",      114000*0.165, 73680 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300ToInf_EMEnr_",         9000*0.15, 132904 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt20ToInf_MuEnr_" , 720648000*0.00042, 693443 - 0, LumiScale, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    */
    std::cout << "Processing background MC samples..." << std::endl;
    for(std::vector<QCDSampleInfo>::iterator iter_SampleInfos = myBGSampleWeight.QCDSampleInfos.begin(); iter_SampleInfos != myBGSampleWeight.QCDSampleInfos.end(); iter_SampleInfos++)
    { 
      //print out basic information 
      float ls = (*iter_SampleInfos).weight;
      std::cout <<"Sample Type: "<< (*iter_SampleInfos).QCDTag << "; LUMI Scale: " << ls << std::endl;
      //Loading chain info
      long long int nTot = (*iter_SampleInfos).chain->GetEntries();
      float WpT, Hmass, HpT, bbdRAve, bbdMMin, HHt, WHdR;
      (*iter_SampleInfos).chain->SetBranchAddress( "WpT", &WpT );
      (*iter_SampleInfos).chain->SetBranchAddress( "Hmass", &Hmass );
      (*iter_SampleInfos).chain->SetBranchAddress( "HpT", &HpT );
      (*iter_SampleInfos).chain->SetBranchAddress( "bbdRAve", &bbdRAve );
      (*iter_SampleInfos).chain->SetBranchAddress( "bbdMMin", &bbdMMin );
      (*iter_SampleInfos).chain->SetBranchAddress( "HHt", &HHt );
      (*iter_SampleInfos).chain->SetBranchAddress( "WHdR", &WHdR );
      float weight;
      (*iter_SampleInfos).chain->SetBranchAddress( "weight", &weight );

      //Determine histogram indice
      int ih = -1;
      if      ( (*iter_SampleInfos).QCDTag.find("_SingleT_") != std::string::npos ) ih = 0;
      else if ( (*iter_SampleInfos).QCDTag == "_TTJets_" ) ih = 1;
      else if ( (*iter_SampleInfos).QCDTag == "_WJets" ) ih = 2;
      else if ( (*iter_SampleInfos).QCDTag.find("_DYJetsToLL_") != std::string::npos ) ih = 3;
      else if ( 
                  (*iter_SampleInfos).QCDTag == "_TGJets_" 
               //|| (*iter_SampleInfos).QCDTag == "_TGJets_ext1_2016"
               || (*iter_SampleInfos).QCDTag == "_TTGJets_"
               || (*iter_SampleInfos).QCDTag == "_TTWJetslnu_"
               || (*iter_SampleInfos).QCDTag == "_TTZJets2l2nu_"
              ) ih = 4;
      else if ( 
                  (*iter_SampleInfos).QCDTag == "_WW2l2nu_" 
               || (*iter_SampleInfos).QCDTag == "_WWlnu2q_"
               //|| (*iter_SampleInfos).QCDTag == "_WWlnu2q_ext1_2016"
               || (*iter_SampleInfos).QCDTag == "_WZ_"
               //|| (*iter_SampleInfos).QCDTag == "_WZ_ext1_2016"
               || (*iter_SampleInfos).QCDTag == "_ZZ_"
               //|| (*iter_SampleInfos).QCDTag == "_ZZ_ext1_2016"
              ) ih = 5;
      else if ( 
                  (*iter_SampleInfos).QCDTag == "_WWW_" 
               || (*iter_SampleInfos).QCDTag == "_WWZ_" 
               || (*iter_SampleInfos).QCDTag == "_WZZ_" 
               || (*iter_SampleInfos).QCDTag == "_ZZZ_" 
              ) ih = 6;
      else if ( (*iter_SampleInfos).QCDTag.find("_QCD_Pt") != std::string::npos ) ih = 7;

      for (long long int ievt = 0; ievt < nTot; ievt++) 
      {
        (*iter_SampleInfos).chain->GetEvent(ievt);
        float mvaout = myTMVAReader.GenReMVAReader
                       (
                        WpT,
                        Hmass, HpT, bbdRAve, bbdMMin, HHt,
                        WHdR,
                        "Haa4bSBClassification" + TrainMode
                       );
        if ( ih >= 0 )
        {
          (myMVACutFlowHist.h_b_WpT_BGMC[ih])->Fill( WpT, weight * ls );
          (myMVACutFlowHist.h_b_Hmass_BGMC[ih])->Fill( Hmass, weight * ls );
          (myMVACutFlowHist.h_b_HpT_BGMC[ih])->Fill( HpT, weight * ls );
          (myMVACutFlowHist.h_b_bbdRAve_BGMC[ih])->Fill( bbdRAve, weight * ls );
          (myMVACutFlowHist.h_b_bbdMMin_BGMC[ih])->Fill( bbdMMin, weight * ls );
          (myMVACutFlowHist.h_b_HHt_BGMC[ih])->Fill( HHt, weight * ls );
          (myMVACutFlowHist.h_b_WHdR_BGMC[ih])->Fill( WHdR, weight * ls );

          (myMVACutFlowHist.h_b_BDT_BGMC[ih])->Fill( mvaout, weight * ls );

          int lobin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).first, hibin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).second;
          if ( hibin >= 0 )
          {
            for ( int j = lobin; j <= hibin ; j++ )
            {
              (myMVACutFlowHist.h_b_n_BGMC[ih])->Fill( j, weight * ls );
            }
          }
          else 
          { 
            (myMVACutFlowHist.h_b_n_BGMC[ih])->Fill( 0.0, weight * ls );
          }
        }
        /*
        if ( ievt < 20 )
        {
          std::cout << "MVA output : " << mvaout << ", [" << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).first << ","  << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).second << "]" << std::endl;
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
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016H_ver2"  , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016H_ver3"  , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016B_ver2"  , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016C"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016D"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016E"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016F"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016G"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016H_ver2"  , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016H_ver3"  , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
    std::cout << "Processing data samples..." << std::endl;
    for(std::vector<QCDSampleInfo>::iterator iter_SampleInfos = myDataSampleWeight.QCDSampleInfos.begin(); iter_SampleInfos != myDataSampleWeight.QCDSampleInfos.end(); iter_SampleInfos++)
    { 
      //print out basic information 
      std::cout <<"Sample Type: "<< (*iter_SampleInfos).QCDTag << "; Lumi Scale: " << (*iter_SampleInfos).weight << std::endl;
      //Loading chain info
      long long int nTot = (*iter_SampleInfos).chain->GetEntries();
      float WpT, Hmass, HpT, bbdRAve, bbdMMin, HHt, WHdR;
      (*iter_SampleInfos).chain->SetBranchAddress( "WpT", &WpT );
      (*iter_SampleInfos).chain->SetBranchAddress( "Hmass", &Hmass );
      (*iter_SampleInfos).chain->SetBranchAddress( "HpT", &HpT );
      (*iter_SampleInfos).chain->SetBranchAddress( "bbdRAve", &bbdRAve );
      (*iter_SampleInfos).chain->SetBranchAddress( "bbdMMin", &bbdMMin );
      (*iter_SampleInfos).chain->SetBranchAddress( "HHt", &HHt );
      (*iter_SampleInfos).chain->SetBranchAddress( "WHdR", &WHdR );
      float weight;
      (*iter_SampleInfos).chain->SetBranchAddress( "weight", &weight );

      for (long long int ievt = 0; ievt < nTot; ievt++) 
      {
        (*iter_SampleInfos).chain->GetEvent(ievt);
        float mvaout = myTMVAReader.GenReMVAReader
                       (
                        WpT,
                        Hmass, HpT, bbdRAve, bbdMMin, HHt,
                        WHdR,
                        "Haa4bSBClassification" + TrainMode
                       );
        (myMVACutFlowHist.h_b_WpT_Data)->Fill( WpT, weight );
        (myMVACutFlowHist.h_b_Hmass_Data)->Fill( Hmass, weight );
        (myMVACutFlowHist.h_b_HpT_Data)->Fill( HpT, weight );
        (myMVACutFlowHist.h_b_bbdRAve_Data)->Fill( bbdRAve, weight );
        (myMVACutFlowHist.h_b_bbdMMin_Data)->Fill( bbdMMin, weight );
        (myMVACutFlowHist.h_b_HHt_Data)->Fill( HHt, weight );
        (myMVACutFlowHist.h_b_WHdR_Data)->Fill( WHdR, weight );

        (myMVACutFlowHist.h_b_BDT_Data)->Fill( mvaout, weight );

        int lobin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).first, hibin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).second;
        if ( hibin >= 0 )
        {
          for ( int j = lobin; j <= hibin ; j++ )
          {
            (myMVACutFlowHist.h_b_n_Data)->Fill( j, weight );
            //(myMVACutFlowHist.h_b_n_Data)->Fill( j, 1 );
          }
        }
        else 
        { 
          (myMVACutFlowHist.h_b_n_Data)->Fill( 0.0, weight );
          //(myMVACutFlowHist.h_b_n_Data)->Fill( 0.0, 1 );
        }
        /*
        if ( ievt < 20 )
        {
          std::cout << "MVA output : " << mvaout << ", [" << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).first << ","  << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).second << "]" << std::endl;
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
