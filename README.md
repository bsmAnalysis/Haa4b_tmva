# Haa4bTools

This tool is based on stop analysis team alpha, where i am working on for 3 years, with great colleagues. <br />

### Set up BDT training framework
```bash
cmsrel CMSSW_9_2_14_patch1
cmsenv
mkdir UserCode
cd $CMSSW_BASE/src/UserCode
git clone git@github.com:weihuacern/Haa4bTools.git
```

### Compile Code
Note, make sure make clean before commit. <br />
```bash
cd $CMSSW_BASE/src/Haa4bTools/Tools
make
cd $CMSSW_BASE/src/Haa4bTools/AnaModules
make
```

```
sh cache_all.sh
tar --exclude-caches-all -zcf ${CMSSW_VERSION}.tar.gz -C ${CMSSW_BASE}/.. ${CMSSW_VERSION}
./MVAAna RunMode TrainMode
./MVAAna Train TribMVA
./MVAAna Train QuabMVA
python genList.py -d /eos/cms/store/user/georgia/results_2017_09_21 -l
```
