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
    mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass12"  , 1  , 1, 35.9, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass15"  , 1  , 1, 35.9, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass20"  , 1  , 1, 35.9, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass25"  , 1  , 1, 35.9, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass30"  , 1  , 1, 35.9, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass40"  , 1  , 1, 35.9, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass50"  , 1  , 1, 35.9, 1, "FileList/MVASGMCFileList.txt", TrainMode );
    mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass60"  , 1  , 1, 35.9, 1, "FileList/MVASGMCFileList.txt", TrainMode );

    std::cout << "Processing signal MC samples..." << std::endl;
    for(std::vector<QCDSampleInfo>::iterator iter_SampleInfos = mySGSampleWeight.QCDSampleInfos.begin(); iter_SampleInfos != mySGSampleWeight.QCDSampleInfos.end(); iter_SampleInfos++)
    { 
      //print out basic information 
      std::cout <<"Sample Type: "<< (*iter_SampleInfos).QCDTag << "; LUMI: " << (*iter_SampleInfos).weight << std::endl;
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
          (myMVACutFlowHist.h_b_WpT_SGMC[ih])->Fill( WpT, weight );
          (myMVACutFlowHist.h_b_Hmass_SGMC[ih])->Fill( Hmass, weight );
          (myMVACutFlowHist.h_b_HpT_SGMC[ih])->Fill( HpT, weight );
          (myMVACutFlowHist.h_b_bbdRAve_SGMC[ih])->Fill( bbdRAve, weight );
          (myMVACutFlowHist.h_b_bbdMMin_SGMC[ih])->Fill( bbdMMin, weight );
          (myMVACutFlowHist.h_b_HHt_SGMC[ih])->Fill( HHt, weight );
          (myMVACutFlowHist.h_b_WHdR_SGMC[ih])->Fill( WHdR, weight );

          (myMVACutFlowHist.h_b_BDT_SGMC[ih])->Fill( mvaout, weight );

          int lobin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).first, hibin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).second;
          if ( hibin > 0 )
          {
            for ( int j = lobin; j <= hibin ; j++ )
            {
              (myMVACutFlowHist.h_b_n_SGMC[ih])->Fill( j, weight );
            }
          }
        }
        /*
        if ( ievt < 200 )
        {
          std::cout << "MVA output : " << mvaout << ", [" << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).first << ","  << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).second << "]" << std::endl;
          //std::cout << "Weight: " << weight << std::endl;
          //std::cout << "MVA vars : " << WpT << "," << Hmass << std::endl;
          //std::cout << "MVA vars : " << myTMVAReader.WpT << "," << myTMVAReader.Hmass << std::endl;
        }
        */ 
      }
    }

    QCDSampleWeight myBGSampleWeight;
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_atW_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_at_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_s_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_tW_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_t_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_TTJets_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WJets"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_10to50_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_50toInf_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_TGJets_2016"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_TGJets_ext1_2016"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_TTGJets_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_TTWJetslnu_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_TTZJets2l2nu_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WW2l2nu_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WWlnu2q_2016"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WWlnu2q_ext1_2016"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WZ_2016"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WZ_ext1_2016"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_ZZ_2016"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_ZZ_ext1_2016"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WWW_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WWZ_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_WZZ_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_ZZZ_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt50To80_EMEnr_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt80To120_EMEnr_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt120To170_EMEnr_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt170To300_EMEnr_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300ToInf_EMEnr_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt20ToInf_MuEnr_"  , 1  , 1, 35.9, 1, "FileList/MVABGMCFileList.txt", TrainMode );
    std::cout << "Processing background MC samples..." << std::endl;
    for(std::vector<QCDSampleInfo>::iterator iter_SampleInfos = myBGSampleWeight.QCDSampleInfos.begin(); iter_SampleInfos != myBGSampleWeight.QCDSampleInfos.end(); iter_SampleInfos++)
    { 
      //print out basic information 
      std::cout <<"Sample Type: "<< (*iter_SampleInfos).QCDTag << "; LUMI: " << (*iter_SampleInfos).weight << std::endl;
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
                  (*iter_SampleInfos).QCDTag == "_TGJets_2016" 
               || (*iter_SampleInfos).QCDTag == "_TGJets_ext1_2016"
               || (*iter_SampleInfos).QCDTag == "_TTGJets_"
               || (*iter_SampleInfos).QCDTag == "_TTWJetslnu_"
               || (*iter_SampleInfos).QCDTag == "_TTZJets2l2nu_"
              ) ih = 4;
      else if ( 
                  (*iter_SampleInfos).QCDTag == "_WW2l2nu_" 
               || (*iter_SampleInfos).QCDTag == "_WWlnu2q_2016"
               || (*iter_SampleInfos).QCDTag == "_WWlnu2q_ext1_2016"
               || (*iter_SampleInfos).QCDTag == "_WZ_2016"
               || (*iter_SampleInfos).QCDTag == "_WZ_ext1_2016"
               || (*iter_SampleInfos).QCDTag == "_ZZ_2016"
               || (*iter_SampleInfos).QCDTag == "_ZZ_ext1_2016"
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
          (myMVACutFlowHist.h_b_WpT_BGMC[ih])->Fill( WpT, weight );
          (myMVACutFlowHist.h_b_Hmass_BGMC[ih])->Fill( Hmass, weight );
          (myMVACutFlowHist.h_b_HpT_BGMC[ih])->Fill( HpT, weight );
          (myMVACutFlowHist.h_b_bbdRAve_BGMC[ih])->Fill( bbdRAve, weight );
          (myMVACutFlowHist.h_b_bbdMMin_BGMC[ih])->Fill( bbdMMin, weight );
          (myMVACutFlowHist.h_b_HHt_BGMC[ih])->Fill( HHt, weight );
          (myMVACutFlowHist.h_b_WHdR_BGMC[ih])->Fill( WHdR, weight );

          (myMVACutFlowHist.h_b_BDT_BGMC[ih])->Fill( mvaout, weight );

          int lobin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).first, hibin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout ).second;
          if ( hibin > 0 )
          {
            for ( int j = lobin; j <= hibin ; j++ )
            {
              (myMVACutFlowHist.h_b_n_BGMC[ih])->Fill( j, weight );
            }
          }
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
