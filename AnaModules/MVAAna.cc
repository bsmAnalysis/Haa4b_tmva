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
  
  std::string channel = "Wh";
  unsigned short int yearBits = 4; // 1 for 2016, 2 for 2017 and 4 for 2018  
  
  bool is2016 = yearBits & 0x01;
  bool is2017 = (yearBits >> 1) & 0x01;
  bool is2018 = (yearBits >> 2) & 0x01;
  if(is2017) LumiScale = 41529.152;
  else if(is2018) LumiScale = 59740.565;
  std::string dir_out = "OutDir_2016";
  if(is2017) dir_out = "OutDir_2017";
  if(is2018) dir_out = "OutDir_2018";
  dir_out = dir_out + channel + "/";
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
    myMVACutFlowHist.BookHistgram( (dir_out + "MVACutFlow" + TrainMode + ".root").c_str() );
    
    TMVAReader myTMVAReader;
    myTMVAReader.InitTMVAReader();
    myTMVAReader.SetupMVAReader( "Haa4bSBClassification" + TrainMode, "dataset/weights/Haa4bSBClassification" + TrainMode + "_BDT.weights.xml" );
 
    QCDSampleWeight mySGSampleWeight;
    if(is2016){
      if(channel == "Wh"){
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass12"  , 1.37*0.61, 567134.0 - 0.0,  LumiScale, 1, "FileList/WH_2016_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass15"  , 1.37*0.61, 996279.0 - 0.0,  LumiScale, 1, "FileList/WH_2016_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass20"  , 1.37*0.61, 999279.0 - 0.0,  LumiScale, 1, "FileList/WH_2016_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass25"  , 1.37*0.61, 1010277.0 - 0.0, LumiScale, 1, "FileList/WH_2016_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass30"  , 1.37*0.61, 998095.0 - 0.0,  LumiScale, 1, "FileList/WH_2016_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass40"  , 1.37*0.61, 1010418.0 - 0.0, LumiScale, 1, "FileList/WH_2016_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass50"  , 1.37*0.61, 995119.0 - 0.0,  LumiScale, 1, "FileList/WH_2016_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass60"  , 1.37*0.61, 1008303.0 - 0.0, LumiScale, 1, "FileList/WH_2016_MVASGMCFileList.txt", TrainMode );
      }
      else if(channel == "Zh"){
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass12"  , 0.8549*0.7435, 965463.0 - 0.0, LumiScale, 1, "FileList/ZH_2016_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass15"  , 0.8549*0.7435, 990410.0 - 0.0, LumiScale, 1, "FileList/ZH_2016_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass20"  , 0.8549*0.7435, 965694.0 - 0.0, LumiScale, 1, "FileList/ZH_2016_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass25"  , 0.8549*0.7435, 985066.0 - 0.0, LumiScale, 1, "FileList/ZH_2016_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass30"  , 0.8549*0.7435, 994159.0 - 0.0, LumiScale, 1, "FileList/ZH_2016_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass40"  , 0.8549*0.7435, 986613.0 - 0.0, LumiScale, 1, "FileList/ZH_2016_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass50"  , 0.8549*0.7435, 993354.0 - 0.0, LumiScale, 1, "FileList/ZH_2016_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass60"  , 0.8549*0.7435, 974094.0 - 0.0, LumiScale, 1, "FileList/ZH_2016_MVASGMCFileList.txt", TrainMode );
      }
    }
    else if(is2017){
      if(channel == "Wh"){
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass12"  , 1.37*0.65, 954064.0 - 243.0, LumiScale, 1, "FileList/WH_2017_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass15"  , 1.37*0.65, 938279.0 - 194.0, LumiScale, 1, "FileList/WH_2017_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass20"  , 1.37*0.65, 958291.0 - 253.0, LumiScale, 1, "FileList/WH_2017_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass25"  , 1.37*0.65, 934752.0 - 245.0, LumiScale, 1, "FileList/WH_2017_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass30"  , 1.37*0.65, 934392.0 - 228.0, LumiScale, 1, "FileList/WH_2017_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass40"  , 1.37*0.65, 955312.0 - 232.0, LumiScale, 1, "FileList/WH_2017_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass50"  , 1.37*0.65, 938132.0 - 219.0, LumiScale, 1, "FileList/WH_2017_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass60"  , 1.37*0.65, 953671.0 - 238.0, LumiScale, 1, "FileList/WH_2017_MVASGMCFileList.txt", TrainMode );
      }
      else if(channel == "Zh"){
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass12"  , 0.8594*0.75, 494867.0 - 137.0, LumiScale, 1, "FileList/ZH_2017_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass15"  , 0.8594*0.75, 497352.0 - 146.0, LumiScale, 1, "FileList/ZH_2017_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass20"  , 0.8594*0.75, 496923.0 - 156.0, LumiScale, 1, "FileList/ZH_2017_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass25"  , 0.8594*0.75, 494046.0 - 113.0, LumiScale, 1, "FileList/ZH_2017_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass30"  , 0.8594*0.75, 494844.0 - 105.0, LumiScale, 1, "FileList/ZH_2017_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass40"  , 0.8594*0.75, 493834.0 - 130.0, LumiScale, 1, "FileList/ZH_2017_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass50"  , 0.8594*0.75, 496778.0 - 141.0, LumiScale, 1, "FileList/ZH_2017_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass60"  , 0.8594*0.75, 496260.0 - 155.0, LumiScale, 1, "FileList/ZH_2017_MVASGMCFileList.txt", TrainMode );
      }
    }
    else if(is2018){
      if(channel == "Wh"){
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass12"  , 1.37*0.61, 1020552.0 - 252.0, LumiScale, 1, "FileList/WH_2018_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass15"  , 1.37*0.61, 1022841.0 - 277.0, LumiScale, 1, "FileList/WH_2018_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass20"  , 1.37*0.61, 1020865.0 - 260.0, LumiScale, 1, "FileList/WH_2018_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass25"  , 1.37*0.61, 1021745.0 - 220.0, LumiScale, 1, "FileList/WH_2018_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass30"  , 1.37*0.61, 1011608.0 - 256.0, LumiScale, 1, "FileList/WH_2018_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass40"  , 1.37*0.61, 1019676.0 - 258.0, LumiScale, 1, "FileList/WH_2018_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass50"  , 1.37*0.61, 1015362.0 - 233.0, LumiScale, 1, "FileList/WH_2018_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Wh_amass60"  , 1.37*0.61, 1019268.0 - 221.0, LumiScale, 1, "FileList/WH_2018_MVASGMCFileList.txt", TrainMode );
      }
      else if(channel == "Zh"){
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass12"  , 0.8594*0.75, 496864.0 - 143.0, LumiScale, 1, "FileList/ZH_2018_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass15"  , 0.8594*0.75, 297591.0 - 90.0, LumiScale, 1, "FileList/ZH_2018_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass20"  , 0.8594*0.75, 494953.0 - 133.0, LumiScale, 1, "FileList/ZH_2018_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass25"  , 0.8594*0.75, 484526.0 - 63.0, LumiScale, 1, "FileList/ZH_2018_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass30"  , 0.8594*0.75, 132903.0 - 44.0, LumiScale, 1, "FileList/ZH_2018_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass40"  , 0.8594*0.75, 484354.0 - 40.0, LumiScale, 1, "FileList/ZH_2018_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass50"  , 0.8594*0.75, 472247.0 - 60.0, LumiScale, 1, "FileList/ZH_2018_MVASGMCFileList.txt", TrainMode );
        mySGSampleWeight.QCDSampleInfo_push_back( "_Zh_amass60"  , 0.8594*0.75, 495637.0 - 45.0, LumiScale, 1, "FileList/ZH_2018_MVASGMCFileList.txt", TrainMode );
      }
    }
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
      if      ( (*iter_SampleInfos).QCDTag == "_"+channel+"_amass12" ) ih = 0;
      else if ( (*iter_SampleInfos).QCDTag == "_"+channel+"_amass15" ) ih = 1;
      else if ( (*iter_SampleInfos).QCDTag == "_"+channel+"_amass20" ) ih = 2;
      else if ( (*iter_SampleInfos).QCDTag == "_"+channel+"_amass25" ) ih = 3;
      else if ( (*iter_SampleInfos).QCDTag == "_"+channel+"_amass30" ) ih = 4;
      else if ( (*iter_SampleInfos).QCDTag == "_"+channel+"_amass40" ) ih = 5;
      else if ( (*iter_SampleInfos).QCDTag == "_"+channel+"_amass50" ) ih = 6;
      else if ( (*iter_SampleInfos).QCDTag == "_"+channel+"_amass60" ) ih = 7;

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
    if(is2016){
      TString FilePath = "FileList/WH_2016_MVABGMCFileList.txt";
      if(channel.compare("Zh") == 0) FilePath = "FileList/ZH_2016_MVABGMCFileList.txt";
      //Single Top
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_s_"           ,             3.362,811495.0 - 188505.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_atW_"         ,              35.6,    6933094.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_tW_"          ,              35.6,    6952830.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_at_"          ,             80.95,   38811017.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_t_"           ,            136.02,   67240808.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      //TTJets
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTJets_"              ,            831.76, 77081156.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      //WJets
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_"                 ,           50690, 86731806.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode ); //be careful about kf, already NNLO
      myBGSampleWeight.QCDSampleInfo_push_back( "_W1Jets_"                ,              9493, 45367044.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_W2Jets_"                ,              3120, 60197766.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_W3Jets_"                ,             942.3, 58398439.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_W4Jets_"                ,             524.2, 29995313.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      //DY [10,50]
      myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_10to50_"    ,             18610, 62001124.0 - 4211038.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY1JetsToLL_10to50_"   ,               725,       39840774.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY2JetsToLL_10to50_"   ,             394.5,       19442927.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY3JetsToLL_10to50_"   ,             96.47,        4964197.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY4JetsToLL_10to50_"   ,             34.84,        2087849.0 - 0.0, LumiScale, 1.21, FilePath, TrainMode );
      // DY [50,Inf]
      myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_50toInf_"   ,              4895, 247721443.0 - 20137162.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY1JetsToLL_50toInf_"  ,              1016,         62627174.0 - 0.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY2JetsToLL_50toInf_"  ,             331.4,         19970551.0 - 0.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY3JetsToLL_50toInf_"  ,             96.36,          5856110.0 - 0.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY4JetsToLL_50toInf_"  ,              51.4,          4197868.0 - 0.0, LumiScale, 1.18, FilePath, TrainMode );
      //TG, TTG, TTW, TTZ
      myBGSampleWeight.QCDSampleInfo_push_back( "_TGJets_"              ,             2.967, 1109033.0 - 740471.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTGJets_"             ,             3.697, 3224372.0 - 1646539.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTWJetslnu_"          ,            0.2043, 2361962.0 - 758435.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTZJets2l2nu_"        ,            0.2529, 1460207.0 - 532231.0, LumiScale, 1, FilePath, TrainMode );
      //Di-boson
      myBGSampleWeight.QCDSampleInfo_push_back( "_WW2l2nu_"             ,            12.178,  1999000.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WWlnu2q_"             ,            49.997, 18973950.0 - 0.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_WW4q_"                ,            51.723,  1998400.0 - 0.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_WZ_"                  ,             47.13,  1000000.0 - 0.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_ZZ_"                  ,             17.72,  1988098.0 - 0.0, LumiScale, 1, FilePath, TrainMode ); //
      //Tri-boson
      myBGSampleWeight.QCDSampleInfo_push_back( "_WWW_"                 ,            0.2086, 225269.0 - 14731.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WWZ_"                 ,            0.1651, 235734.0 - 14266.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WZZ_"                 ,           0.05565, 231583.0 - 15217.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_ZZZ_"                 ,           0.01398, 231217.0 - 18020.0, LumiScale, 1, FilePath, TrainMode );
      //QCD
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt80To120_EMEnr_"     ,     2800000*0.125, 77695287.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt120To170_EMEnr_"    ,      477000*0.132, 77771316.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt170To300_EMEnr_"    ,      114000*0.165, 11540163.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300ToInf_EMEnr_"    ,         9000*0.15,  7373633.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt80to120_MuEnrPt5_"  ,       106033.6648, 23584215.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt120to170_MuEnrPt5_" ,       25190.51514,  8042721.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt170to300_MuEnrPt5_" ,        8654.49315, 17350231.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300to470_MuEnrPt5_" ,         797.35269, 48214485.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt470to600_MuEnrPt5_" ,       79.02553776, 19362943.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt600to800_MuEnrPt5_" ,       25.09505908,  9981311.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt800to1000_MuEnrPt5_",       4.707368272, 19767439.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt1000toInf_MuEnrPt5_",        1.62131692, 13599938.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt_80to170_bcToE_"    ,           3221000, 14976689.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt_170to250_bcToE_"   ,            105771,  9720760.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt_250toInf_bcToE_"   ,           21094.1,  9773617.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
    }
    else if(is2017){
      TString FilePath = "FileList/WH_2017_MVABGMCFileList.txt";
      if(channel.compare("Zh") == 0) FilePath = "FileList/ZH_2017_MVABGMCFileList.txt";
      //Single Top
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_s_"           ,             3.354,8050005.0 - 1864943.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_tW_antitop_"  ,              35.6,  7715654.0 - 29622.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_tW_top_"      ,              35.6,  7914815.0 - 30427.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_t_antitop_"   ,          26.30875,      3675910.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_t_top_"       ,           44.2065,      5982064.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      //TTJets
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTTo2L2Nu_"           ,             88.29, 68875708.0 - 280100.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTToHadronic_"        ,            377.96,129736822.0 - 525618.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTToSemiLeptonic_"    ,            365.34, 43555789.0 - 176656.0, LumiScale, 1, FilePath, TrainMode );
      //WJets
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_"                 ,           50690, 77665843.0 - 34663.0, LumiScale, 1.21, FilePath, TrainMode ); //be careful about kf, already NNLO
      myBGSampleWeight.QCDSampleInfo_push_back( "_W1Jets_"                ,              9493, 54127369.0 - 20443.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_W2Jets_"                ,              3120,   6573967.0 - 3525.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_W3Jets_"                ,             942.3, 19685035.0 - 15342.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_W4Jets_"                ,             524.2, 11088852.0 - 14833.0, LumiScale, 1.21, FilePath, TrainMode );
      //DY
      myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_10to50_"    ,             18610, 39837070.0 - 15903.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_M50_"	 ,              4895, 97757863.0 - 43076.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY1JetsToLL_M50_"	 ,              1016, 75971677.0 - 28745.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY2JetsToLL_M50_"	 ,             331.4,  10121430.0 - 5316.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY3JetsToLL_M50_"	 ,             96.36,   6892913.0 - 5020.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY4JetsToLL_M50_"	 ,              51.4,   4323202.0 - 5446.0, LumiScale, 1.18, FilePath, TrainMode );
      //TG, TTG, TTW, TTZ
      myBGSampleWeight.QCDSampleInfo_push_back( "_TGJets_"              ,             2.967,  1140561.0 - 768439.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTGJets_"             ,             3.697,21062657.0 - 9277474.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTWJetslnu_"          ,            0.2043, 3855275.0 - 1139268.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTZJets2l2nu_"        ,            0.2529, 5838974.0 - 2093676.0, LumiScale, 1, FilePath, TrainMode );
      //Di-boson
      myBGSampleWeight.QCDSampleInfo_push_back( "_WminusH_"             ,           0.03369, 2319634.0 - 62866.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_WplusH_"              ,             0.053, 2412283.0 - 68917.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_ZH_"			,           0.04865,4034880.0 - 122194.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_WW_"			,             118.7,     7765828.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WZ_"                  ,             47.13,     3928630.0 - 0.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_ZZ_"                  ,            16.523,     1925931.0 - 0.0, LumiScale, 1, FilePath, TrainMode ); //
      //Tri-boson
      myBGSampleWeight.QCDSampleInfo_push_back( "_WWW_"                 ,            0.2086, 217773.0 - 14527.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WWZ_"                 ,            0.1651, 234982.0 - 15018.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WZZ_"                 ,           0.05565, 234830.0 - 15170.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_ZZZ_"                 ,           0.01398, 232159.0 - 17841.0, LumiScale, 1, FilePath, TrainMode );
      //QCD
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt80To120_EMEnr_"	    ,     2800000*0.125, 9104852.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt120To170_EMEnr_"    ,      477000*0.132, 8515107.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300ToInf_EMEnr_"    ,              1350, 2874295.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt80to120_MuEnrPt5_"  ,       106033.6648,23248995.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt120to170_MuEnrPt5_" ,       25190.51514,20774848.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt170to300_MuEnrPt5_" ,        8654.49315,46170668.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300to470_MuEnrPt5_" ,         797.35269,17744779.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt470to600_MuEnrPt5_" ,       79.02553776,24243589.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt_80to170_bcToE_"    ,           3221000,15999466.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt_170to250_bcToE_"   ,            105771, 9847660.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt_250toInf_bcToE_"   ,           21094.1, 9996886.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
    }
    else if(is2018){
      TString FilePath = "FileList/WH_2018_MVABGMCFileList.txt";
      if(channel.compare("Zh") == 0) FilePath = "FileList/ZH_2018_MVABGMCFileList.txt";
      //Single Top
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_s_"           ,             3.354,16211819.0 - 3753181.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_tW_antitop_"  ,              35.6,  7605590.0 - 17410.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_tW_top_"      ,              35.6,  9575956.0 - 22044.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_t_antitop_"   ,          26.30875,76658965.0 - 2431835.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_SingleT_t_top_"       ,           44.2065,149201191.0 - 5106409.0, LumiScale, 1, FilePath, TrainMode );
      //TTJets
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTTo2L2Nu_"           ,             88.29, 64050742.0 - 259258.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTToHadronic_"        ,            377.96,133266791.0 - 541209.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTToSemiLeptonic_"    ,            365.34,101139378.0 - 410622.0, LumiScale, 1, FilePath, TrainMode );
      //WJets
      myBGSampleWeight.QCDSampleInfo_push_back( "_WJets_"                 ,             50690, 70996650.0 - 30211.0, LumiScale, 1.21, FilePath, TrainMode ); //be careful about kf, already NNLO
      myBGSampleWeight.QCDSampleInfo_push_back( "_W1Jets_"                ,              9493, 51065321.0 - 17455.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_W2Jets_"                ,              3120,  23281764.0 - 8946.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_W3Jets_"                ,             942.3,  14500689.0 - 7792.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_W4Jets_"                ,             524.2, 10072540.0 - 10207.0, LumiScale, 1.21, FilePath, TrainMode );
      //DY
      myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_10to50_"    ,             18610, 39376427.0 - 15635.0, LumiScale, 1.21, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DYJetsToLL_M50_"	 ,              4895,100154500.0 - 40097.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY1JetsToLL_M50_"	 ,              1016,106839361.0 - 35389.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY2JetsToLL_M50_"	 ,             331.4,  20448554.0 - 7483.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY3JetsToLL_M50_"	 ,             96.36,   5649476.0 - 2881.0, LumiScale, 1.18, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_DY4JetsToLL_M50_"	 ,              51.4,  2815147.0 - 2665.0, LumiScale, 1.18, FilePath, TrainMode );
      //TG, TTG, TTW, TTZ
      myBGSampleWeight.QCDSampleInfo_push_back( "_TGJets_"              ,             2.967,  1152139.0 - 777861.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTGJets_"             ,             3.697, 3267151.0 - 1424764.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTWJetslnu_"          ,            0.2043, 3799018.0 - 1112923.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_TTZJets2l2nu_"        ,            0.2529, 9777023.0 - 3502977.0, LumiScale, 1, FilePath, TrainMode );
      //Di-boson
      myBGSampleWeight.QCDSampleInfo_push_back( "_WminusH_"             ,           0.03369, 1926589.0 - 52030.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_WplusH_"              ,             0.053, 1892215.0 - 53980.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_ZH_"			,           0.04865,6830527.0 - 206173.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_WW_"			,             118.7,     7850000.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WZ_"                  ,             47.13,     3885000.0 - 0.0, LumiScale, 1, FilePath, TrainMode ); //
      myBGSampleWeight.QCDSampleInfo_push_back( "_ZZ_"                  ,            16.523,     1979000.0 - 0.0, LumiScale, 1, FilePath, TrainMode ); //
      //Tri-boson
      myBGSampleWeight.QCDSampleInfo_push_back( "_WWW_"                 ,            0.2086, 225050.0 - 14950.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WWZ_"                 ,            0.1651, 234955.0 - 15045.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_WZZ_"                 ,           0.05565, 234625.0 - 15375.0, LumiScale, 1, FilePath, TrainMode );
      myBGSampleWeight.QCDSampleInfo_push_back( "_ZZZ_"                 ,           0.01398, 232141.0 - 17859.0, LumiScale, 1, FilePath, TrainMode );
      //QCD
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt80To120_EMEnr_"	    ,     2800000*0.125, 9648791.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt120To170_EMEnr_"    ,      477000*0.132, 9964143.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt170To300_EMEnr_"    ,             18810, 3712174.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300ToInf_EMEnr_"    ,              1350, 2901355.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt80to120_MuEnrPt5_"  ,       106033.6648,25652280.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt120to170_MuEnrPt5_" ,       25190.51514,  633668.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt170to300_MuEnrPt5_" ,        8654.49315,35978539.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt300to470_MuEnrPt5_" ,         797.35269,  492418.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt470to600_MuEnrPt5_" ,       79.02553776,  492716.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt600to800_MuEnrPt5_" ,       25.09505908,16618977.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt800to1000_ext3_MuEnrPt5_",  4.707368272,23123897.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
//      myBGSampleWeight.QCDSampleInfo_push_back( "_QCD_Pt1000toInf_MuEnrPt5_",        1.62131692,10719790.0 - 0.0, LumiScale, 1, FilePath, TrainMode );
    }
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
	       || (*iter_SampleInfos).QCDTag == "_TTToSemiLeptonic_"
	       || (*iter_SampleInfos).QCDTag == "_TTToHadronic_"
	       || (*iter_SampleInfos).QCDTag == "_TTTo2L2Nu_"
              ) ih = 1;
      else if ( isWJets )
      {
        ih = 2;
        std::cout << "W0Jets: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(0, 0, yearBits) << std::endl;
        std::cout << "W1Jets: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(0, 1, yearBits) << std::endl;
        std::cout << "W2Jets: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(0, 2, yearBits) << std::endl;
        std::cout << "W3Jets: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(0, 3, yearBits) << std::endl;
        std::cout << "W4Jets: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(0, 4, yearBits) << std::endl;
      }
      else if ( isDYJets )
      {
        ih = 3;
        if( (*iter_SampleInfos).QCDTag.find("_10to50") != std::string::npos )
        {
          std::cout << "DY0Jets_10to50: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(1, 0, yearBits) << std::endl;
          std::cout << "DY1Jets_10to50: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(1, 1, yearBits) << std::endl;
          std::cout << "DY2Jets_10to50: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(1, 2, yearBits) << std::endl;
          std::cout << "DY3Jets_10to50: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(1, 3, yearBits) << std::endl;
          std::cout << "DY4Jets_10to50: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(1, 4, yearBits) << std::endl;
        }
        else
        {
          std::cout << "DY0Jets_50toInf: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(2, 0, yearBits) << std::endl;
          std::cout << "DY1Jets_50toInf: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(2, 1, yearBits) << std::endl;
          std::cout << "DY2Jets_50toInf: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(2, 2, yearBits) << std::endl;
          std::cout << "DY3Jets_50toInf: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(2, 3, yearBits) << std::endl;
          std::cout << "DY4Jets_50toInf: " << LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(2, 4, yearBits) << std::endl;
        }
      }
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
               || (*iter_SampleInfos).QCDTag == "_WW4q_"
               || (*iter_SampleInfos).QCDTag == "_WW_"
               || (*iter_SampleInfos).QCDTag == "_WZ_"
               || (*iter_SampleInfos).QCDTag == "_ZZ_"
               || (*iter_SampleInfos).QCDTag == "_WplusH_"
               || (*iter_SampleInfos).QCDTag == "_WminusH_"
               || (*iter_SampleInfos).QCDTag == "_ZH_"
              ) ih = 5;
      else if ( 
                  (*iter_SampleInfos).QCDTag == "_WWW_" 
               || (*iter_SampleInfos).QCDTag == "_WWZ_" 
               || (*iter_SampleInfos).QCDTag == "_WZZ_" 
               || (*iter_SampleInfos).QCDTag == "_ZZZ_" 
              ) ih = 6;
      else if ( (*iter_SampleInfos).QCDTag.find("_QCD_Pt") != std::string::npos ) ih = 7;
      else 
      {
        std::cout << "Em... Unclassified sample. Tag: " << (*iter_SampleInfos).QCDTag << std::endl;
      }
      for (long long int ievt = 0; ievt < nTot; ievt++) 
      {
        if ( isWJets ){ ls = LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(0, lheNJets, yearBits); }
        if ( isDYJets ){ (*iter_SampleInfos).QCDTag.find("_10to50_") != std::string::npos ? ls = LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(1, lheNJets, yearBits) : ls = LumiScale * myBGSampleWeight.xsecWeightCalcLHEJets(2, lheNJets, yearBits); }

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

//    QCDSampleWeight myDataSampleWeight;
//    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016B_ver2"  , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
//    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016C"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
//    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016D"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
//    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016E"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
//    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016F"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
//    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016G"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
//    //myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016G"       , 1  , 1, LumiScale/7544.01559, 1, "FileList/MVADataFileList.txt", TrainMode );
//    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016H_ver2"  , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
//    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleElectron2016H_ver3"  , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
//    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016B_ver2"  , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
//    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016C"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
//    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016D"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
//    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016E"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
//    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016F"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
//    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016G"       , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
//    //myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016G"       , 1  , 1, LumiScale/7544.01559, 1, "FileList/MVADataFileList.txt", TrainMode );
//    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016H_ver2"  , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
//    myDataSampleWeight.QCDSampleInfo_push_back( "_SingleMuon2016H_ver3"  , 1  , 1, 1, 1, "FileList/MVADataFileList.txt", TrainMode );
//    std::cout << "Processing data samples..." << std::endl;
//    for(std::vector<QCDSampleInfo>::iterator iter_SampleInfos = myDataSampleWeight.QCDSampleInfos.begin(); iter_SampleInfos != myDataSampleWeight.QCDSampleInfos.end(); iter_SampleInfos++)
//    {
//      float ls = (*iter_SampleInfos).weight;
//      //print out basic information 
//      std::cout <<"Sample Type: "<< (*iter_SampleInfos).QCDTag << "; Lumi Scale: " << ls << std::endl;
//      //Loading chain info
//      long long int nTot = (*iter_SampleInfos).chain->GetEntries();
//      float WpT, Hmass, HpT, bbdRAve, bbdMMin, HHt, WHdR;
//      float lepPt, pfMET, MTw, ljDR;
//      (*iter_SampleInfos).chain->SetBranchAddress( "WpT", &WpT );
//      (*iter_SampleInfos).chain->SetBranchAddress( "Hmass", &Hmass );
//      (*iter_SampleInfos).chain->SetBranchAddress( "HpT", &HpT );
//      (*iter_SampleInfos).chain->SetBranchAddress( "bbdRAve", &bbdRAve );
//      (*iter_SampleInfos).chain->SetBranchAddress( "bbdMMin", &bbdMMin );
//      (*iter_SampleInfos).chain->SetBranchAddress( "HHt", &HHt );
//      (*iter_SampleInfos).chain->SetBranchAddress( "WHdR", &WHdR );
//      (*iter_SampleInfos).chain->SetBranchAddress( "lepPt", &lepPt );
//      (*iter_SampleInfos).chain->SetBranchAddress( "pfMET", &pfMET ); 
//      (*iter_SampleInfos).chain->SetBranchAddress( "MTw", &MTw ); 
//      (*iter_SampleInfos).chain->SetBranchAddress( "ljDR", &ljDR );      
//      float weight;
//      (*iter_SampleInfos).chain->SetBranchAddress( "weight", &weight );
//
//      for (long long int ievt = 0; ievt < nTot; ievt++) 
//      {
//        (*iter_SampleInfos).chain->GetEvent(ievt);
//        float mvaout = myTMVAReader.GenReMVAReader
//                       (
//                        WpT,
//                        Hmass, HpT, bbdRAve, bbdMMin, HHt,
//                        WHdR, lepPt, pfMET, MTw, ljDR,
//                        "Haa4bSBClassification" + TrainMode
//			);
//        (myMVACutFlowHist.h_b_WpT_Data)->Fill( WpT, weight * ls );
//        (myMVACutFlowHist.h_b_Hmass_Data)->Fill( Hmass, weight * ls );
//        (myMVACutFlowHist.h_b_HpT_Data)->Fill( HpT, weight * ls );
//        (myMVACutFlowHist.h_b_bbdRAve_Data)->Fill( bbdRAve, weight * ls );
//        (myMVACutFlowHist.h_b_bbdMMin_Data)->Fill( bbdMMin, weight * ls );
//        (myMVACutFlowHist.h_b_HHt_Data)->Fill( HHt, weight * ls );
//        (myMVACutFlowHist.h_b_WHdR_Data)->Fill( WHdR, weight * ls );
//	(myMVACutFlowHist.h_b_lepPt_Data)->Fill( lepPt, weight * ls );                                                                                                                                                                 
//	(myMVACutFlowHist.h_b_pfMET_Data)->Fill( pfMET, weight * ls ); 
//	(myMVACutFlowHist.h_b_MTw_Data)->Fill( MTw, weight * ls ); 
//	(myMVACutFlowHist.h_b_ljDR_Data)->Fill( ljDR, weight * ls ); 
//        (myMVACutFlowHist.h_b_BDT_Data)->Fill( mvaout, weight * ls );
//
//        int lobin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout, TrainMode ).first, hibin = myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout, TrainMode ).second;
//        if ( hibin >= 0 )
//        {
//          for ( int j = lobin; j <= hibin ; j++ )
//          {
//            (myMVACutFlowHist.h_b_n_Data)->Fill( j, weight * ls );
//            //(myMVACutFlowHist.h_b_n_Data)->Fill( j, 1 );
//          }
//        }
//        //else 
//        //{ 
//          //(myMVACutFlowHist.h_b_n_Data)->Fill( 0.0, weight * ls );
//          //(myMVACutFlowHist.h_b_n_Data)->Fill( 0.0, 1 );
//        //}
//        /*
//        if ( ievt < 20 )
//        {
//          std::cout << "MVA output : " << mvaout << ", [" << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout, TrainMode ).first << ","  << myMVACutFlowHist.getHistoBinEdgeFromMVA( mvaout, TrainMode ).second << "]" << std::endl;
//          std::cout << "Weight: " << weight << std::endl;
//          //std::cout << "MVA vars : " << WpT << "," << Hmass << std::endl;
//          //std::cout << "MVA vars : " << myTMVAReader.WpT << "," << myTMVAReader.Hmass << std::endl;
//        }
//        */
//      }
//    }

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
