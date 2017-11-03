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
  char nBase[] = "../../../../../MC13TeV_Wh_amass50_0.root";
  //char nBase[] = "root://eoscms.cern.ch//eos/cms/store/user/georgia/h-aa-Madgraph5/final/Wh_production_20/HIG-RunIISummer16MiniAODv2-01613_%i.root";
  //char nBase[] = "root://eoscms.cern.ch//eos/cms/store/user/georgia/h-aa-Madgraph5/final/Wh_production_50/HIG-RunIISummer16MiniAODv2-01613_%i.root";
  TChain *ch = new TChain("mainNtuplizer/data");

  char chname[512];
  for (int i = 1; i <= 1; ++i)
  {
    sprintf(chname, nBase, i);
    ch->Add(chname);
  }

  try
  {
    NTupleReader *tr=0;
    tr = new NTupleReader(ch);
    //BaselineVessel blv(tr);
    //tr.registerFunction(blv);
    const std::string spec = "test";
    BaselineVessel *myBaselineVessel = 0;
    myBaselineVessel = new BaselineVessel( *tr, spec);
    tr->registerFunction(*myBaselineVessel);

    while (tr->getNextEvent())
    {
      if (tr->getEvtNum() == 1)
      {
        tr->printTupleMembers();
        FILE * fout = fopen("NTupleTypes.txt", "w");
        tr->printTupleMembers(fout);
        fclose(fout);
      }
      if ( tr->getEvtNum() < 20 )
      {
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
      }
     
      std::cout << "NEvent " << tr->getEvtNum() << " " << tr->getVar<int>("sv") << ", " << tr->getVar<int>("jet") << std::endl;
      std::vector<TLorentzVector> jetLVec = tr->getVec<TLorentzVector>("jetLVec");
      for (int i = 0; i < jetLVec.size(); i++)
      {
        float thispt = jetLVec.at(i).Pt();
        if ( thispt < 20 ) std::cout << " Jet Pt smaller than 20 GeV: " << jetLVec.at(i).Pt() << ", ";
      }
      std::cout << std::endl;

      std::vector<TLorentzVector> svLVec = tr->getVec<TLorentzVector>("svLVec"); 
      for (int i = 0; i < svLVec.size(); i++)
      {
        float thispt = svLVec.at(i).Pt();
        if ( thispt > 20 ) std::cout << " sv Pt greater than 20 GeV: " << svLVec.at(i).Pt() << ", ";
      } 
      std::cout << std::endl;
      //std::cout << "NEvent " << tr->getEvtNum() << std::endl;
      //std::cout << "MET " << tr->getVar<float>("met_pt");
      //std::cout << "MET " << tr->getVar<float>("met_pt") << std::endl;
      //std::cout << " Njet " << tr->getVar<int>("jet") << std::endl;
    }
  }
  catch (const SATException& e)
  {
    e.print();
  }

  return 0;
}

