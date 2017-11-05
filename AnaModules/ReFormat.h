#ifndef _ReFormat_H_
#define _ReFormat_H_

#include <string>
#include <iostream>
#include <vector>

#include "EvtHandler.h"

const double trigger_turn_on_met = 200;
const double cut_mtwmu = 100;
const double cut_mtwel = 100;
const int nth_slash_nametag_MC = 10;
const int nth_slash_nametag_Data = 10;

inline size_t find_Nth
(
  const std::string & str ,   // where to work
  unsigned            N ,     // N'th ocurrence
  const std::string & find    // what to 'find'
)
{
  if ( 0==N ) { return std::string::npos; }
  size_t pos,from=0;
  unsigned i=0;
  while ( i<N )
  {
    pos=str.find(find,from);
    if ( std::string::npos == pos ) { break; }
    from = pos + 1; // from = pos + find.size();
    ++i;
  }
  return pos;
}
/*
std::string OutputFileNameGenerator(std::string input_str, bool isData)
{
  //here is a little bit tricky when dealing with the slash... need to improve
  std::string tag = "";
  if(isData) tag = input_str.substr(find_Nth(input_str,nth_slash_nametag_Data,"/") + 1,find_Nth(input_str,nth_slash_nametag_Data+1,"/")-find_Nth(input_str,nth_slash_nametag_Data,"/")-1);
  else tag = input_str.substr(find_Nth(input_str,nth_slash_nametag_MC,"/") + 1,find_Nth(input_str,nth_slash_nametag_MC+1,"/")-find_Nth(input_str,nth_slash_nametag_MC,"/")-1);
  std::size_t idpos = input_str.find("stopFlatNtuples");
  std::string fileid = input_str.substr (idpos);
  std::string output_str = "MVATree_" + tag + "_" + fileid;
  std::cout << "Output File Name: " << output_str << std::endl;
  return output_str;
}
*/
#endif
