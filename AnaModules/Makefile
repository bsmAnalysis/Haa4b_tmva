IDIR       = .
ODIR       = obj
SDIR       = ../Tools

CXX        = g++

CXXFLAGS += -I. -std=c++0x -I$(CMSSW_BASE)/src/ -I$(LHAPDF_DATA_PATH)/../../include -I$(CMSSW_RELEASE_BASE)/src
CXXFLAGS += -I$(shell scram tool info fastjet | grep '^INCLUDE' | sed 's/INCLUDE=//')
CXXFLAGS += -I$(shell scram tool info boost | grep '^INCLUDE' | sed 's/INCLUDE=//')
## Optimization flag
CXXFLAGS += -g -fPIC
## Enable the maximun warning
#CXXFLAGS += -Wall -Wextra -Weffc++ -g

## Include ROOT
CXXFLAGS  += $(shell root-config --cflags)

CXXDEPFLAGS = -MMD -MP

LD         = g++
LDFLAGS    =

OPENCV_DIRECTORY=$(CMSSW_BASE)/src/opencv
LIBS       = $(shell root-config --glibs)
#LIBS      += -Lobj -lAnaTools
LHAPDFLIB  = -L$(LHAPDF_DATA_PATH)/../../lib -lLHAPDF
FILES = $(wildcard $(SDIR)/*.cc)
OBJS  := $(FILES:$(SDIR)/%.cc=$(ODIR)/%.o)

PROGRAMS = ReFormat MVATreeMaker

all: mkobj $(OBJS) AnaTools $(PROGRAMS)

mkobj:
	@mkdir -p obj

#code to compile shared library to link samples to python
AnaTools : $(OBJS)
	ar rcs lib$@.a $^
	gcc -shared -o $(ODIR)/lib$@.so $^

$(ODIR)/%.o : $(SDIR)/%.C
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(SDIR)/%.cc
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(SDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(IDIR)/%.C
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(IDIR)/%.cc
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(IDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

ReFormat: $(ODIR)/ReFormat.o $(ODIR)/EvtHandler.o
	$(LD) $^ $(LIBS) $(LHAPDFLIB) -o $@

MVATreeMaker: $(ODIR)/MVATreeMaker.o $(ODIR)/baselineDef.o $(ODIR)/NTupleReader.o $(ODIR)/SATException.o $(ODIR)/customize.o
	$(LD) $^ $(LIBS) $(LHAPDFLIB) -o $@

clean:
	rm -f $(IDIR)/*.a $(ODIR)/*.o $(ODIR)/*.d $(ODIR)/*.so $(PROGRAMS) core 

-include $(ODIR)/*.d
