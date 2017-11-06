#!/bin/bash

shopt -s expand_aliases
alias cachedir='echo "Signature: 8a477f597d28d172789f06886806bc55\n# This file is a cache directory tag.\n# For information about cache directory tags, see:\n#       http://www.brynosaurus.com/cachedir/" > CACHEDIR.TAG'

current=`pwd`

cd $CMSSW_BASE/tmp
cachedir
cd $CMSSW_BASE/src/.git
cachedir
cd $CMSSW_BASE/src/EgammaAnalysis
cachedir
cd $CMSSW_BASE/src/PhysicsTools
cachedir
cd $CMSSW_BASE/src/RecoBTag
cachedir
cd $CMSSW_BASE/src/TauAnalysis
cachedir
cd $CMSSW_BASE/src/TopQuarkAnalysis
cachedir
cd $CMSSW_BASE/src/UserCode/bsmhiggs_fwk
cachedir
cd $CMSSW_BASE/src/UserCode/Haa4bTools/.git
cachedir

cd $current
