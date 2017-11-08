#include "MVAAna.h"


int main()
{
  TMVATrainer myTMVATrainer;
  
  myTMVATrainer.InitTMVAFactory("MVAOutTest.root", "Haa4bSBClassification");
  myTMVATrainer.SetupMVAFactory("TribMVA");
  //myTMVATrainer.SetupMVAFactory("QuabMVA");
  myTMVATrainer.TnTstMVAFactory();
  myTMVATrainer.CloseMVAFactory();
  return 0;
}
