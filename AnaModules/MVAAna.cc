#include "MVAAna.h"


int main()
{
  /*
  TMVATrainer myTMVATrainer;
  
  myTMVATrainer.InitTMVAFactory("MVAOutTest.root", "Haa4bSBClassification");
  myTMVATrainer.SetupMVAFactory("TribMVA");
  //myTMVATrainer.SetupMVAFactory("QuabMVA");
  myTMVATrainer.TnTstMVAFactory();
  myTMVATrainer.CloseMVAFactory();
  */

  TMVAReader myTMVAReader;

  myTMVAReader.InitTMVAReader();
  myTMVAReader.SetupMVAReader( "BDT", "weights/Haa4bSBClassification_BDT.weights.xml" );
  /*
  myTMVAReader.GenReMVAReader(
                       float thisWpT,
                       float thisHmass, float thisHpT, float thisbbdRAve, float thisbbdMMin, float thisHHt,
                       float thisWHdR,
                       "BDT"
                      );
  */
  myTMVAReader.CloseMVAReader();

  return 0;
}
