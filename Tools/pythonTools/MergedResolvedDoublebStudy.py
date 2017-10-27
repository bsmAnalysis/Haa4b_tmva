import json
import ROOT
from ROOT import TCanvas, TH1
from ROOT import TH1D
from ROOT import TLegend
from ROOT import TStyle
from ROOT import TColor, TGaxis, TH1F, TPad, TNamed 
from ROOT import kBlack, kBlue, kRed
from pprint import pprint
from ROOT import TLorentzVector # triggers auto-load of libPhysics
import numpy as np
import math
import sys

def GetEtaPhi(px, py, pz, en):
  l = TLorentzVector()
  l.SetPxPyPzE(px,py,pz,en)
  #print( "sizeof4Floats: %d, sizeofTL: %d" % ( 4*sys.getsizeof(e), sys.getsizeof(l) ) )
  eta = l.Eta()
  phi = l.Phi()
  return eta, phi

def DeltaR(eta1, phi1, eta2, phi2):
  deta = eta1 - eta2
  resphi = phi1 - phi2
  while resphi > math.pi:
    resphi = resphi - 2 * math.pi
  while resphi < -math.pi:
    resphi = resphi + 2 * math.pi
  dphi = resphi
  dr = math.sqrt(deta*deta + dphi*dphi)
  return dr

class Abb:
  def __init__(self):
    self.a = TLorentzVector()
    self.lb = []

import collections
def ObtainAbb(mc_px, mc_py, mc_pz, mc_en, mc_id, mc_momidx):
  n = len(mc_px)
  genaobj = collections.namedtuple('GenAObj', 'aLVec aIdx')
  genbobj = collections.namedtuple('GenBObj', 'bLVec bMomId bMomIdx')
  lgenaobj = []
  lgenbobj = []
  for imc in range( 0, n):
    if abs(mc_id[imc]) == 5:
      thislb = TLorentzVector()
      thislb.SetPxPyPzE( mc_px[imc], mc_py[imc], mc_pz[imc], mc_en[imc] )
      lgenbobj.append( genbobj( bLVec = thislb, bMomId = mc_id[mc_momidx[imc]], bMomIdx = mc_momidx[imc] ) )
    if mc_id[imc] == 36:
      thisla = TLorentzVector()
      thisla.SetPxPyPzE( mc_px[imc], mc_py[imc], mc_pz[imc], mc_en[imc] )
      lgenaobj.append( genaobj( aLVec = thisla, aIdx = imc ) )
  
  lAbb = []
  for aobj in lgenaobj:
    this = Abb()
    this.a = aobj.aLVec
    for bobj in lgenbobj:
      if aobj.aIdx == bobj.bMomIdx and bobj.bMomId == 36:
        this.lb.append( bobj.bLVec )
    lAbb.append(this)
  return lAbb

def mcjetmatch(lmc, jet_px, jet_py, jet_pz, jet_en, drmax):
  #lmc = TLorentzVector()
  #lmc.SetPxPyPzE( amc_px, amc_py, amc_pz, amc_en )
  aeta = lmc.Eta()
  aphi = lmc.Phi()
  n = len(jet_px)
  for ijet in range(0, n):
    ljet = TLorentzVector()
    ljet.SetPxPyPzE( jet_px[ijet], jet_py[ijet], jet_pz[ijet], jet_en[ijet] )
    if DeltaR( aeta, aphi, ljet.Eta(), ljet.Phi() ) < drmax:
      return True
  return False

def doubleGenBFilter(thisabb):
  for blvec in thisabb.lb:
    if blvec.Pt() < 20:
      return False
  return True

def doubleBType(thisabb, jet_px, jet_py, jet_pz, jet_en, fjet_px, fjet_py, fjet_pz, fjet_en):
  amatch = mcjetmatch(thisabb.a, fjet_px, fjet_py, fjet_pz, fjet_en, 0.8)
  bmatch = True
  for blvec in thisabb.lb:
    bmatch = bmatch and mcjetmatch(blvec, jet_px, jet_py, jet_pz, jet_en, 0.4)
    #print("E of b: %f" % (blvec.E()) )
  return amatch, bmatch

if __name__ == '__main__':
  f = ROOT.TFile.Open("MC13TeV_Wh_amass50_0.root", "read")
  #f = ROOT.TFile.Open("root://cmseos.fnal.gov//store/group/lpcsusyhad/hua/Skimmed_2015Nov15/SignalStudy_Summer16_80X_Mar_2017_Ntp_v13p0_SMS-T5tttt_dM175_FastSim_scan_stopFlatNtuples_33.root", "read")
  t = f.Get("mainNtuplizer/data")
  i = 0 
  from BaselineDef import BaselineDef
  for ev in t:
    i = i+1
    myBaselineDef = BaselineDef(ev)
    if myBaselineDef.passBaseline:
      print( "MET: %f" % (ev.met_pt) )
    else:
      continue

    lmyabb = ObtainAbb(ev.mc_px, ev.mc_py, ev.mc_pz, ev.mc_en, ev.mc_id, ev.mc_momidx)
    for abb in lmyabb:
      if ( not doubleGenBFilter(abb) ):
        continue
 
      print ("%dth event" % (i))
      amatch, bmatch = doubleBType( abb, ev.jet_px, ev.jet_py, ev.jet_pz, ev.jet_en, ev.fjet_px, ev.fjet_py, ev.fjet_pz, ev.fjet_en )
      if amatch and bmatch:
        print ("Merged and Resolved")
      elif amatch and (not bmatch):
        print ("Merged and Not Resolved")
      elif (not amatch) and bmatch:
        print ("Not Merged and Resolved")
      else:
        print ("Not Merged and Not Resolved")
      #print ("E of A: %f" % (abb.a.E()) )
      print ("Pt of A: %f" % (abb.a.Pt()) )
      for blvec in abb.lb:
        #print ("E of b: %f" % (blvec.E()) )
        print ("Pt of b: %f" % (blvec.Pt()) )
      bbdr = DeltaR( abb.lb[0].Eta(), abb.lb[0].Phi(), abb.lb[1].Eta(), abb.lb[1].Phi() )
      print ("bb dR: %f" % (bbdr) )
    #nmc = ev.nmcparticles
    #for imc in range(0 , nmc):
      #if ev.mc_id[imc] == 36:
      #  afjetmatched = mcjetmatch( ev.mc_px[imc], ev.mc_py[imc], ev.mc_pz[imc], ev.mc_en[imc], ev.fjet_px, ev.fjet_py, ev.fjet_pz, ev.fjet_en, 0.8 )
      #  if afjetmatched: 
      #    print ("Gen a matched with a fat jet")
      #  else: 
      #    print ("Gen a not matched with a fat jet")
      #if abs(ev.mc_id[imc]) == 5:
      #  bjetmatched = mcjetmatch( ev.mc_px[imc], ev.mc_py[imc], ev.mc_pz[imc], ev.mc_en[imc], ev.jet_px, ev.jet_py, ev.jet_pz, ev.jet_en, 0.4 )
      #  if bjetmatched: 
      #    print ("Gen b matched with a jet")
      #  else: 
      #    print ("Gen b not matched with a jet")

    '''
    njet = ev.jet
    for ijet in range( 0, njet ):
      #print("length of jet vec: %d" % (len(ev.jet_en)))
      eta, phi = GetEtaPhi( ev.jet_px[ijet], ev.jet_py[ijet], ev.jet_pz[ijet], ev.jet_en[ijet] )
      #print("Eta: %f, Phi: %f" % (eta, phi))
    '''
    if i > 100:
      break
