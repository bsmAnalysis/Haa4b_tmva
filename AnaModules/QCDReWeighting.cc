#include "QCDReWeighting.h"

void QCDSampleWeight::QCDSampleInfo_push_back( std::string tag, double xsec, double nevents, double lumi, double kf, const TString &inputFileList, std::string TrainMode )
{
  QCDSampleInfo oneInfo;

  oneInfo.QCDTag = tag;
  oneInfo.xsec_in = xsec; 
  oneInfo.nevents_in = nevents;
  oneInfo.lumi_in = lumi; 
  oneInfo.kf_in =kf;

  oneInfo.weight = xsec*lumi*kf/nevents;
  oneInfo.chain = new TChain(TrainMode.c_str());
  
  if(!FillChain(oneInfo.chain, inputFileList, oneInfo.QCDTag))
  {
    std::cerr << "Cannot get the tree " << std::endl;
  }
  QCDSampleInfos.push_back(oneInfo);
  oneInfo = {};
}

void QCDSampleWeight::GenLatexTable()
{
  std::cout << "Start to generate Latex table for all background MC samples..." << std::endl;
  std::ofstream of("SampleTable.tex");
  of << "%This is a table of MC samples, includeing xsec, Nevt and weight" << std::endl;

  of << "\\documentclass{article}" << std::endl;
  of << "\\usepackage{table}" << std::endl;
  of << "\\usepackage{color}" << std::endl;
  of << "\\begin{document}" << std::endl;
  of << "\\begin{table}[htbp]" << std::endl;
  of << "\\caption{Background MC Summary}" << std::endl;
  of << "\\begin{tabular}{|c|c|c|c|c|c|}" << std::endl;
  of << "\\hline" << std::endl;
  of << "Sample Name & xSec(pb) & NEvt & Lumi($pb^{-1}$) & k Factor & Weight \\\\" << std::endl;
  of << "\\hline" << std::endl;
  char remove[] = "_";
  for (int i = 0; i < QCDSampleInfos.size(); i++)
  {
    std::string tmptag = QCDSampleInfos.at(i).QCDTag;
    removeCharsFromString( tmptag, remove );
    if ( QCDSampleInfos.at(i).weight < 10.0)
    {
      of << tmptag << " & " << QCDSampleInfos.at(i).xsec_in << " & " << QCDSampleInfos.at(i).nevents_in << " & " << QCDSampleInfos.at(i).lumi_in << " & " << QCDSampleInfos.at(i).kf_in << " & " << QCDSampleInfos.at(i).weight << " \\\\" << std::endl;
    }
    else
    {
      of << "\\textbf{" << tmptag << "} & \\textbf{" << QCDSampleInfos.at(i).xsec_in << "} & \\textbf{" << QCDSampleInfos.at(i).nevents_in << "} & \\textbf{" << QCDSampleInfos.at(i).lumi_in << "} & \\textbf{" << QCDSampleInfos.at(i).kf_in << "} & \\textbf{\\textcolor{red}{" << QCDSampleInfos.at(i).weight << "}} \\\\" << std::endl;
    }
    of << "\\hline" << std::endl;

  }
  of << "\\end{tabular}" << std::endl;
  of << "\\end{table}" << std::endl;
  of << "\\end{document}" << std::endl;

  of.close();
  return ;
}

float QCDSampleWeight::xsecWeightCalcLHEJets(int bit, int lheNJets)
{
  //bit == 0 for WJets/WXJets, bit == 1 for low mass DY, bit == 2 for high mass DY
  float this_kf = 1;
  int this_events[5] = {1, 1, 1, 1, 1};
  float this_xsec[5] = {1, 1, 1, 1, 1};

  if (bit == 0)//WJets
  {
    this_kf = 1.233848684;
    this_events[0] = (mStat.find("MC13TeV_WJets_2016")->second).first; this_xsec[0] = (mStat.find("MC13TeV_WJets_2016")->second).second/this_kf;
    this_events[1] = (mStat.find("MC13TeV_W1Jets_2016")->second).first; this_xsec[1] = (mStat.find("MC13TeV_W1Jets_2016")->second).second;
    this_events[2] = (mStat.find("MC13TeV_W2Jets_2016")->second).first; this_xsec[2] = (mStat.find("MC13TeV_W2Jets_2016")->second).second;
    this_events[3] = (mStat.find("MC13TeV_W3Jets_2016")->second).first; this_xsec[3] = (mStat.find("MC13TeV_W3Jets_2016")->second).second;
    this_events[4] = (mStat.find("MC13TeV_W4Jets_2016")->second).first; this_xsec[4] = (mStat.find("MC13TeV_W4Jets_2016")->second).second;
  }
  else if( bit == 1)//low mass DY
  {
    this_kf = 1.33;
    this_events[0] = (mStat.find("MC13TeV_DYJetsToLL_10to50_2016")->second).first; this_xsec[0] = (mStat.find("MC13TeV_DYJetsToLL_10to50_2016")->second).second/this_kf;
    this_events[1] = (mStat.find("MC13TeV_DY1JetsToLL_10to50_2016")->second).first; this_xsec[1] = (mStat.find("MC13TeV_DY1JetsToLL_10to50_2016")->second).second;
    this_events[2] = (mStat.find("MC13TeV_DY2JetsToLL_10to50_2016")->second).first; this_xsec[2] = (mStat.find("MC13TeV_DY2JetsToLL_10to50_2016")->second).second;
    this_events[3] = (mStat.find("MC13TeV_DY3JetsToLL_10to50_2016")->second).first; this_xsec[3] = (mStat.find("MC13TeV_DY3JetsToLL_10to50_2016")->second).second;
    this_events[4] = (mStat.find("MC13TeV_DY4JetsToLL_10to50_2016")->second).first; this_xsec[4] = (mStat.find("MC13TeV_DY4JetsToLL_10to50_2016")->second).second;
  }
  else if( bit == 2)//high mass DY
  {
    this_kf = 1.187694915;
    this_events[0] = (mStat.find("MC13TeV_DYJetsToLL_50toInf_ext1_2016")->second).first; this_xsec[0] = (mStat.find("MC13TeV_DYJetsToLL_50toInf_ext1_2016")->second).second/this_kf;
    this_events[1] = (mStat.find("MC13TeV_DY1JetsToLL_50toInf_2016")->second).first; this_xsec[1] = (mStat.find("MC13TeV_DY1JetsToLL_50toInf_2016")->second).second;
    this_events[2] = (mStat.find("MC13TeV_DY2JetsToLL_50toInf_2016")->second).first; this_xsec[2] = (mStat.find("MC13TeV_DY2JetsToLL_50toInf_2016")->second).second;
    this_events[3] = (mStat.find("MC13TeV_DY3JetsToLL_50toInf_2016")->second).first; this_xsec[3] = (mStat.find("MC13TeV_DY3JetsToLL_50toInf_2016")->second).second;
    this_events[4] = (mStat.find("MC13TeV_DY4JetsToLL_50toInf_2016")->second).first; this_xsec[4] = (mStat.find("MC13TeV_DY4JetsToLL_50toInf_2016")->second).second;
  }
  else
  {
    std::cout << "### There is a problem here! Bit: " << bit << std::endl;
    return 0;
  }

  if      (lheNJets == 0) return this_kf / (this_events[0] / this_xsec[0]);
  else if (lheNJets == 1) return this_kf / (this_events[1] / this_xsec[1] + this_events[0] / this_xsec[0]);
  else if (lheNJets == 2) return this_kf / (this_events[2] / this_xsec[2] + this_events[0] / this_xsec[0]);
  else if (lheNJets == 3) return this_kf / (this_events[3] / this_xsec[3] + this_events[0] / this_xsec[0]);
  else if (lheNJets == 4) return this_kf / (this_events[4] / this_xsec[4] + this_events[0] / this_xsec[0]);
  else { std::cout << "### There is a problem here! lheNJets: " << lheNJets << std::endl; return 0; }
  return 0;
}

//Fill chain from txt file
bool QCDSampleWeight::FillChain(TChain *chain, const TString &inputFileList, std::string tag)
{
  std::ifstream infile( inputFileList, std::ifstream::in );
  std::string buffer;

  if(!infile.is_open())
  {
    std::cerr << "** ERROR: Can't open '" << inputFileList << "' for input" << std::endl;
    return false;
  }

  std::cout << "TreeUtilities : FillChain " << tag << std::endl;
  while(1)
  {
    buffer.clear();
    infile >> buffer;

    if(!infile.good()) break;
    //std::cout << "Adding tree from " << buffer.c_str() << std::endl;
    //std::cout << (buffer.find(tag) != std::string::npos) << std::endl;
    if (buffer.find(tag) != std::string::npos)
    {
      //std::cout << tag << " found!" << std::endl;
      chain->Add(buffer.c_str());
    }
  }
  std::cout << "No. of Entries in this tree : " << chain->GetEntries() << std::endl;
  return true;
}

void QCDSampleWeight::removeCharsFromString( std::string &str, char* charsToRemove ) 
{
  for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) 
  {
    str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
  }
}
