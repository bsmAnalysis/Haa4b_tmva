#include "LHESplit.h"

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr <<"Please give 2 arguments " << "inputFileName " << "LHENJets " << std::endl;
    std::cerr <<"Valid configurations are: " << std::endl;
    std::cerr <<"./LHESplit .root 0" << std::endl;
    return -1;
  }
  std::string input_str(argv[1]);
  std::string sellheNJets(argv[2]);

  std::string output_str = "mva_LHE" + sellheNJets + "Jets_" + input_str;

  std::cout << "Output File Name: " << output_str << std::endl;

  TChain *in3b = new TChain("TribMVA");
  in3b->Add(input_str.c_str());
  in3b->SetBranchStatus("*", 1);
  TChain *in4b = new TChain("QuabMVA");
  in4b->Add(input_str.c_str());
  in4b->SetBranchStatus("*", 1);

  int lheNJets3b;
  in3b->SetBranchAddress( "lheNJets", &lheNJets3b );  
  int lheNJets4b;
  in4b->SetBranchAddress( "lheNJets", &lheNJets4b );

  TFile* output = new TFile((output_str).c_str(), "RECREATE");
  TTree* out3b = in3b->CloneTree(0);
  TTree* out4b = in4b->CloneTree(0);
 
  for (long long int ievt = 0; ievt < in3b->GetEntries(); ievt++) 
  {

    in3b->GetEvent(ievt); 
    if( lheNJets3b == std::atoi(argv[2]) ) out3b->Fill();
    else continue;
  }

  out3b->Write();

  for (long long int ievt = 0; ievt < in4b->GetEntries(); ievt++) 
  {

    in4b->GetEvent(ievt); 
    if( lheNJets4b == std::atoi(argv[2]) ) out4b->Fill();                                                                                                                                               
    else continue;
  }
  out4b->Write();

  output->Write(); 
  output->Close();

  if (in3b) delete in3b;
  if (in4b) delete in4b;

  //std::string d = "root://cmseos.fnal.gov//store/group/lpcsusyhad/hua/Skimmed_2015Nov15";
  //std::system(("xrdcp " + output_str + " " + d).c_str());
  //std::system(("rm " + output_str).c_str());

  return 0;
}
