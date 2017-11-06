import glob, os, sys

def GenCondorTxt( fname, tag ):
  f = open('condorThis.txt', 'w')
  
  f.write('universe = vanilla\n')
  #f.write('request_disk   = 50 GB\n')
  #f.write('request_memory = 1.5 GB\n')
  f.write('executable = $ENV(CMSSW_BASE)/src/UserCode/Haa4bTools/AnaModules/goRF.sh\n')
  f.write('should_transfer_files = YES\n')

  f.write('\n')  

  f.write('transfer_input_files = $ENV(CMSSW_BASE)/src/UserCode/Haa4bTools/AnaModules/condor/$ENV(CMSSW_VERSION).tar.gz, $ENV(CMSSW_BASE)/src/UserCode/Haa4bTools/AnaModules/ReFormat, $ENV(CMSSW_BASE)/src/UserCode/Haa4bTools/AnaModules/goRF.sh\n') 

  f.write('\n')

  f.write('Output = $ENV(CMSSW_BASE)/src/UserCode/Haa4bTools/AnaModules/condor/res/RF_'+ tag + '_$(Process).stdout\n')
  f.write('Error = $ENV(CMSSW_BASE)/src/UserCode/Haa4bTools/AnaModules/condor/res/RF_'+ tag + '_$(Process).stderr\n')
  f.write('Log = $ENV(CMSSW_BASE)/src/UserCode/Haa4bTools/AnaModules/condor/res/RF_'+ tag + '_$(Process).log\n')
  f.write('notify_user = hua.wei@cern.ch\n')


  with open(fname) as thisf:
    for line in thisf:
      f.write('\n')
      f.write('arguments = $ENV(CMSSW_VERSION) $ENV(SCRAM_ARCH) ' + line + '\n')
      f.write('Queue\n')

  f.close()

file_name = sys.argv[1]
tag = sys.argv[2]

GenCondorTxt( file_name, tag ) 
cmd = 'condor_submit condorThis.txt' 
#cmd = './EventPick ' + line
print(cmd) 
os.system(cmd)
os.system ( 'rm condorThis.txt')
