IDIR       = .
ODIR       = obj
SDIR       = .
#SDIR       = $(CMSSW_BASE)/src/SusyAnaTools/Tools/

CXX        = g++

CXXFLAGS += -I. -std=c++0x -I$(CMSSW_BASE)/src/ -isystem$(LHAPDF_DATA_PATH)/../../include -I$(CMSSW_RELEASE_BASE)/src 
#CXXFLAGS += -I$(shell scram tool info fastjet | grep '^INCLUDE' | sed 's/INCLUDE=//')
#CXXFLAGS += -I$(shell scram tool info boost | grep '^INCLUDE' | sed 's/INCLUDE=//')
## Optimization flag
CXXFLAGS += -g -fPIC
## Enable the maximun warning
#CXXFLAGS += -Wall -Wextra -Weffc++ -g

## Include ROOT
CXXFLAGS  += $(shell root-config --cflags)

CXXDEPFLAGS = -MMD -MP

LD         = g++
LDFLAGS    =

#OPENCV_DIRECTORY = $(CMSSW_BASE)/src/opencv
LIBS       = $(shell root-config --glibs)
#LIBS      += -L$(CMSSW_BASE)/lib/${SCRAM_ARCH}/ -lTopTaggerTopTagger -lTopTaggerCfgParser
#LIBS      += -L$(OPENCV_DIRECTORY)/lib/ -lopencv_ml -lopencv_core

LHAPDFLIB  = -L$(LHAPDF_DATA_PATH)/../../lib -lLHAPDF

FILES = $(wildcard $(SDIR)/*.cc)
OBJS := $(FILES:$(SDIR)/%.cc=$(ODIR)/%.o)

PROGRAMS = tupleTest MVATreeMaker

all: mkobj AnaTools sampPyWrap $(PROGRAMS)

mkobj:
	@mkdir -p obj

AnaTools : $(OBJS)
	ar rcs $(ODIR)/lib$@.a $^
	gcc -shared -o $(ODIR)/lib$@.so $^

#code to compile shared library to link samples to python
sampPyWrap: $(ODIR)/samplesModule.so

$(ODIR)/samplesModule.so: $(ODIR)/samplesPyWrap.o $(ODIR)/samplesModulePyWrap.o
	$(CXX) -shared -o $@ $^

$(ODIR)/samplesPyWrap.o: $(SDIR)/samples.cc $(SDIR)/samples.h 
	$(CXX) --std=c++11 -c -fPIC -o $@ $<

$(ODIR)/samplesModulePyWrap.o: $(SDIR)/samplesModule.cc
	$(CXX) --std=c++11 -c -fPIC -o $@ $<

$(ODIR)/%.o : $(SDIR)/%.C
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(SDIR)/%.cc
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(SDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

tupleTest: $(ODIR)/baselineDef.o $(ODIR)/NTupleReader.o $(ODIR)/SATException.o $(ODIR)/customize.o $(ODIR)/tupleReadTest.o
	$(LD) $^ $(LIBS) $(LHAPDFLIB) -o $@

MVATreeMaker: $(ODIR)/baselineDef.o $(ODIR)/NTupleReader.o $(ODIR)/SATException.o $(ODIR)/customize.o $(ODIR)/MVATreeMaker.o
	$(LD) $^ $(LIBS) $(LHAPDFLIB) -o $@

clean:
	rm -f $(ODIR)/*.a $(ODIR)/*.so $(ODIR)/*.o $(ODIR)/*.d $(PROGRAMS) core 

-include $(ODIR)/*.d
