#include "NTupleReader.h"
#include "baselineDef.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <ctime>


int main()
{
  //char nBase[] = "../../huaTest/MC13TeV_Wh_amass20_0.root";
  //char nBase[] = "../../../../../MC13TeV_Wh_amass50_0.root";
  //char nBase[] = "root://eoscms.cern.ch//eos/cms/store/user/georgia/h-aa-Madgraph5/final/Wh_production_20/HIG-RunIISummer16MiniAODv2-01613_%i.root";
  char nBase[] = "root://eoscms.cern.ch//eos/cms/store/user/georgia/results_2017_09_21/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_MC13TeV_TTJets_2016_0/171005_184952/0000/analysis_94.root";
  //char nBase[] = "root://eoscms.cern.ch//eos/cms/store/user/georgia/results_2017_09_21/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/crab_MC13TeV_TTJets_2016_0/171005_184952/0000/analysis_49.root";

  TChain *ch = new TChain("mainNtuplizer/data");

  char chname[512];
  for (int i = 1; i <= 1; ++i)
  {
    sprintf(chname, nBase, i);
    ch->Add(chname);
  }

  int nTotal = ch->GetEntries();

  /*
  int nTotal = ch->GetEntries();

  for (int i = 0; i < nTotal; i++)
  {
    if( i < 600)
    {
      std::cout << "NEvent " << i << std::endl;
      int status = ch->GetEntry(i);
      std::cout << "status: " << status << std::endl;
    }
  }
  */
  
  try
  {
    NTupleReader *tr=0;
    tr = new NTupleReader(ch, AnaConsts::activatedBranchNames_Common);
    //const std::string spec = "test";
    //BaselineVessel *myBaselineVessel = 0;
    //myBaselineVessel = new BaselineVessel( *tr, spec);
    //tr->registerFunction(*myBaselineVessel);

    while (tr->getNextEvent())
    {
      if (tr->getEvtNum() == 1)
      //if (tr->getEvtNum() == 518)
      {
        tr->printTupleMembers();
        FILE * fout = fopen("NTupleTypes.txt", "w");
        tr->printTupleMembers(fout);
        fclose(fout);
      }
      std::cout << "NEvent " << tr->getEvtNum() << "/" << nTotal << std::endl;
      //int run = tr->getVar<int>("run");
      //std::cout << "NEvent " << tr->getEvtNum() << " " << run  << std::endl;
      //unsigned long event = tr->getVar<unsigned long>("event");
      
      //if ( tr->getEvtNum() < 20 )
      //{
        //int size = tr->getVar<int>("mn");
        //std::cout << "NMu " << tr->getVar<int>("mn") << std::endl;
        //const float * arr_head = & ( tr->getVar<float>("mn_px") );
        //std::cout << size << std::endl;
        //std::cout << arr_head << std::endl;
        //std::cout << *arr_head << std::endl;
        //if( size >= 2){ std::cout << *(arr_head+1) << std::endl; }
        //std::vector<float> vec ( arr_head, arr_head + size );
        //for (int i = 0; i < vec.size(); i++)
        //{
        //  std::cout << "num: " << vec.at(i) << std::endl;
        //}
      //}
      //std::cout << "NEvent " << tr->getEvtNum() << " " << tr->getVar<float>("bbdMMin_calcMVA")  << std::endl;
      //std::cout << "NEvent " << tr->getEvtNum() << " " << tr->getVar<int>("nHardBJets") << "," << tr->getVar<int>("nHardBJets_Test") << std::endl;
      //std::cout << "NEvent " << tr->getEvtNum() << " " << tr->getVar<int>("nSoftBJets")  << std::endl;
      //if ( tr->getVar<bool>("passSelPreMVA") )
      //if ( !tr->getVar<bool>("passLeptonSel") )
      //{
        //std::cout << "NEvent " << tr->getEvtNum() << " " << tr->getVar<float>("WpT_calcMVA")  << std::endl;
        //std::cout << "NEvent " << tr->getEvtNum() << " " << tr->getVar<float>("Hmass_calcMVA")  << std::endl;
        //std::cout << "NEvent " << tr->getEvtNum() << " " << tr->getVar<float>("HpT_calcMVA")  << std::endl;
        //std::cout << "NEvent " << tr->getEvtNum() << " " << tr->getVar<float>("bbdRAve_calcMVA")  << std::endl;
        //std::cout << "NEvent " << tr->getEvtNum() << " " << tr->getVar<float>("bbdMMin_calcMVA")  << std::endl;
        //std::cout << "NEvent " << tr->getEvtNum() << " " << tr->getVar<float>("HHt_calcMVA")  << std::endl;
        //std::cout << "NEvent " << tr->getEvtNum() << " " << tr->getVar<float>("WHdR_calcMVA")  << std::endl;
      //}
      //if ( tr->getVar<bool>("passHardBJets") )
      //{
        //std::cout << "NEvent " << tr->getEvtNum() << " " << tr->getVar<int>("nSoftBJets")  << std::endl;
        //std::cout << "NEvent " << tr->getEvtNum() << " " << tr->getVar<int>("nHardBJets")  << std::endl;
      //}
      //if ( tr->getVar<bool>("passMtW") )
      //{
        //std::cout << "NEvent " << tr->getEvtNum() << " " << tr->getVar<float>("mtw")  << std::endl;
      //}
      //if ( tr->getVar<bool>("passMET") )
      //{
        //std::cout << "NEvent " << tr->getEvtNum() << " " << tr->getVar<float>("met_pt")  << std::endl;
      //}
      //if ( tr->getVar<bool>("passLeptonSel") )
      //{
        //std::cout << "NEvent " << tr->getEvtNum() << " " << tr->getVar<int>("nmus_CUT") << " " << tr->getVar<int>("nels_CUT") << std::endl;
      //}
      //std::vector<TLorentzVector> jetLVec = tr->getVec<TLorentzVector>("jetLVec");
      //for (int i = 0; i < jetLVec.size(); i++)
      //{
        //float thispt = jetLVec.at(i).Pt();
        //std::cout << jetLVec.at(i).Pt() << ", " << jetLVec.at(i).Eta() << "; ";
        //if ( thispt < 20 ) std::cout << " Jet Pt smaller than 20 GeV: " << jetLVec.at(i).Pt() << ", ";
      //}
      //std::cout << std::endl;
      //std::vector<TLorentzVector> svLVec = tr->getVec<TLorentzVector>("svLVec"); 
      //for (int i = 0; i < svLVec.size(); i++)
      //{
        //float thispt = svLVec.at(i).Pt();
        //if ( thispt > 20 ) std::cout << " sv Pt greater than 20 GeV: " << svLVec.at(i).Pt() << ", ";
        //float thiseta = svLVec.at(i).Eta();
        //if ( std::abs(thiseta) > 2.4 ) std::cout << " sv Eta greater than 2.4: " << svLVec.at(i).Eta() << ", " << svLVec.at(i).Pt() << std::endl;
      //} 
      //std::cout << std::endl;
      //std::cout << "NEvent " << tr->getEvtNum() << std::endl;
      std::cout << "MET " << tr->getVar<float>("met_pt") << std::endl;
      //std::cout << " Njet " << tr->getVar<int>("jet") << std::endl;
    }
  }
  catch (const SATException& e)
  {
    e.print();
  }
  return 0;
}

