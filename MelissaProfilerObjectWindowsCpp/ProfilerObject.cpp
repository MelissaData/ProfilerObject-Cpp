#include "ProfilerObject.h"

ProfilerObject::ProfilerObject(string license, string dataPath)
{
	string prfFile = "testFile.prf";

	// Set license string and set path to datafiles (.dat, etc)
	mdProfilerObj->SetLicenseString(license.c_str());
	mdProfilerObj->SetFileName(prfFile.c_str());
	mdProfilerObj->SetAppendMode(mdProfiler::AppendMode::Overwrite);

	dataFilePath = dataPath;
	mdProfilerObj->SetPathToProfilerDataFiles(dataFilePath.c_str());

	mdProfilerObj->SetSortAnalysis(1); // the default is 1
	mdProfilerObj->SetMatchUpAnalysis(1); // the default is 1
	mdProfilerObj->SetRightFielderAnalysis(1); // the default is 1
	mdProfilerObj->SetDataAggregation(1); // the default is 1

	// If you see a different date than expected, check your license string and either download the new data files or use the Melissa Updater program to update your data files.  
	mdProfiler::ProgramStatus pStatus = mdProfilerObj->InitializeDataFiles();

	if (pStatus != mdProfiler::ProgramStatus::ErrorNone)
	{
		cout << "Failed to Initialize Object." << endl;
		cout << pStatus << endl;
		return;
	}

	cout << "                        DataBase Date: " + string(mdProfilerObj->GetDatabaseDate()) << endl;
	cout << "                      Expiration Date: " + string(mdProfilerObj->GetLicenseExpirationDate()) << endl;

	/**
	 * This number should match with the file properties of the Melissa Object binary file.
	 * If TEST appears with the build number, there may be a license key issue.
	 */
	cout << "                       Object Version: " + string(mdProfilerObj->GetBuildNumber()) << endl;
}

// This will call the Lookup function to process the input file as well as generate the result codes
void ProfilerObject::ExecuteObjectAndResultCodes(DataContainer& data)
{
	mdProfilerObj->AddColumn("first", mdProfiler::ProfilerColumnType::ColumnTypeVariableUnicodeString, mdProfiler::ProfilerDataType::DataTypeFirstName);
	mdProfilerObj->AddColumn("last", mdProfiler::ProfilerColumnType::ColumnTypeVariableUnicodeString, mdProfiler::ProfilerDataType::DataTypeLastName);
	mdProfilerObj->AddColumn("address", mdProfiler::ProfilerColumnType::ColumnTypeVariableUnicodeString, mdProfiler::ProfilerDataType::DataTypeAddress);
	mdProfilerObj->AddColumn("city", mdProfiler::ProfilerColumnType::ColumnTypeVariableUnicodeString, mdProfiler::ProfilerDataType::DataTypeCity);
	mdProfilerObj->AddColumn("state", mdProfiler::ProfilerColumnType::ColumnTypeVariableUnicodeString, mdProfiler::ProfilerDataType::DataTypeStateOrProvince);
	mdProfilerObj->AddColumn("zip", mdProfiler::ProfilerColumnType::ColumnTypeVariableUnicodeString, mdProfiler::ProfilerDataType::DataTypeZipOrPostalCode);

	vector<string> records;
	string line;

	ifstream inputFile(data.InputFile);
	if (!inputFile)
	{
		cerr << "Error: Unable to open the input file\n";
		exit(1);
	}

	try
	{
		while (getline(inputFile, line))
		{
			records.push_back(line);
		}
	}
	catch (exception ex)
	{
		cerr << "Error: problem encountered while reading the input file";
		exit(1);
	}

	mdProfilerObj->StartProfiling();

	// Inputting the records to the Profiler Object
	for (const auto& record : records)
	{
		istringstream iss(record);
		vector<string> fields;
		string field;

		while (getline(iss, field, ','))
		{
			fields.push_back(field);
		}

		mdProfilerObj->SetColumn("first", fields[0].c_str());
		mdProfilerObj->SetColumn("last", fields[1].c_str());
		mdProfilerObj->SetColumn("address", fields[2].c_str());
		mdProfilerObj->SetColumn("city", fields[3].c_str());
		mdProfilerObj->SetColumn("state", fields[4].c_str());
		mdProfilerObj->SetColumn("zip", fields[5].c_str());

		mdProfilerObj->AddRecord();
	}

	mdProfilerObj->ProfileData();

	// ResultsCodes explain any issues Profiler Object has with the object.
	// List of result codes for Profiler Object
	// https://wiki.melissadata.com/index.php?title=Result_Code_Details#Profiler_Object
}
