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

    while (tr->getNextEvent())
    {
      if (tr->getEvtNum() == 1)
      {
        tr->printTupleMembers();
        FILE * fout = fopen("NTupleTypes.txt", "w");
        tr->printTupleMembers(fout);
        fclose(fout);
      }
      //std::cout << "NEvent " << tr->getEvtNum() << std::endl;
      //std::cout << "MET " << tr->getVar<float>("met_pt");
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

