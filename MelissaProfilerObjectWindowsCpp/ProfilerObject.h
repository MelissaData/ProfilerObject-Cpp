#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

#include "mdProfiler.h"
#include "DataContainer.h"

using namespace std;

#ifndef PROFILEROBJECT_H
#define PROFILEROBJECT_H

class ProfilerObject
{
public:
	// Path to Profiler Object data files (.dat, etc)
	string dataFilePath;

	// Create instance of Melissa Profiler Object
	mdProfiler* mdProfilerObj = new mdProfiler;

	ProfilerObject(string license, string dataPath);

	// This will call the Lookup function to process the input file as well as generate the result codes
	void ExecuteObjectAndResultCodes(DataContainer& data);
};

#endif

