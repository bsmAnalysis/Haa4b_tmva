# Haa4bTools

This tool is based on stop analysis team alpha, where i am working on for 3 years, with great colleagues.

cmsrel CMSSW_9_2_14_patch1

sh cache_all.sh
tar --exclude-caches-all -zcf ${CMSSW_VERSION}.tar.gz -C ${CMSSW_BASE}/.. ${CMSSW_VERSION}

./MVAAna RunMode TrainMode
./MVAAna Train TribMVA
./MVAAna Train QuabMVA


python genList.py -d /eos/cms/store/user/georgia/results_2017_09_21 -l
