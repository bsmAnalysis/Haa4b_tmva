#!/bin/bash

export PATH=${PATH}:/cvmfs/cms.cern.ch/common
export CMS_PATH=/cvmfs/cms.cern.ch

tar -xzf $1.tar.gz

cd $1
source /cvmfs/cms.cern.ch/cmsset_default.sh
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${_CONDOR_SCRATCH_DIR}/$1/src/UserCode/Haa4bTools/Tools/obj:${_CONDOR_SCRATCH_DIR}/$1/lib/$2
# cmsenv
eval `scramv1 runtime -sh`

cd ${_CONDOR_SCRATCH_DIR}
./ReFormat $3
