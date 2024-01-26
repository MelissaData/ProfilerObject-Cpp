# Melissa Profiler Object Windows C++

CXX=cl
CXXFLAGS=-Zi -EHsc
LDLIBS=mdProfiler.lib
RM=del /q /f

all: MelissaProfilerObjectWindowsCpp.exe clean

MelissaProfilerObjectWindowsCpp.exe:	Main.cpp mdProfiler.h mdProfilerEnums.h
	$(CXX) $(CXXFLAGS) Main.cpp ProfilerObject.cpp $(LDLIBS) /Fe:.\Build\MelissaProfilerObjectWindowsCpp.exe

clean:
	$(RM) *.obj *.ilk *.pdb *.h.hash *.lib.hash 
