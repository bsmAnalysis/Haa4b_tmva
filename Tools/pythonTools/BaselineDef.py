import ROOT

class BaselineDef:

  def __init__(self, event):
    self.passMET = self.__passMET(event)
    self.passElectron = self.__passElectron(event)
    self.passMuon = self.__passMuon(event)
    self.passLepton = self.__passLepton(event)
    self.passBaseline = self.passMET and self.passLepton

  def __passMET(self, event):
    if event.met_pt < 25:
      return False
    else:
      return True

  def __passElectron(self, event):
    return True

  def __passMuon(self, event):
    return True

  def __passLepton(self, event):
    return (self.passElectron or self.passMuon)

if __name__ == '__main__':
  f = ROOT.TFile.Open("MC13TeV_Wh_amass50_0.root", "read")
  #f = ROOT.TFile.Open("root://cmseos.fnal.gov//store/group/lpcsusyhad/hua/Skimmed_2015Nov15/SignalStudy_Summer16_80X_Mar_2017_Ntp_v13p0_SMS-T5tttt_dM175_FastSim_scan_stopFlatNtuples_33.root", "read")
  t = f.Get("mainNtuplizer/data")
  i = 0
  for ev in t:
    i = i + 1
    #print ("%dth event" % (i))
    myBaselineDef = BaselineDef(ev)
    #print( myBaselineDef.passMET )
    #myBaselineDef.passBaseline()
    if myBaselineDef.passBaseline:
      print( "MET: %f" % (ev.met_pt) )
