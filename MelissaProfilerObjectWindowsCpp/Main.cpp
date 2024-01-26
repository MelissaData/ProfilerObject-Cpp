#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include<iomanip>

#include "mdProfiler.h"
#include "ProfilerObject.h"
#include "DataContainer.h"

using namespace std;

// function declarations
void ParseArguments(string& license, string& testFile, string& dataPath, int argc, char* argv[]);
void RunAsConsole(string license, string testFile, string dataPath);

int main(int argc, char* argv[])
{
	// Variables
	string license = "";
	string testFile = "";
	string dataPath = "";

	ParseArguments(license, testFile, dataPath, argc, argv);
	RunAsConsole(license, testFile, dataPath);

	return 0;
}

void ParseArguments(string& license, string& testFile, string& dataPath, int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (string(argv[i]) == "--license" || string(argv[i]) == "-l")
		{
			if (argv[i + 1] != NULL)
			{
				license = argv[i + 1];
			}
		}
		if (string(argv[i]) == "--file" || string(argv[i]) == "-f")
		{
			if (argv[i + 1] != NULL)
			{
				testFile = argv[i + 1];
			}
		}
		if (string(argv[i]) == "--dataPath" || string(argv[i]) == "-d")
		{
			if (argv[i + 1] != NULL)
			{
				dataPath = argv[i + 1];
			}
		}
	}
}

void RunAsConsole(string license, string testFile, string dataPath)
{
	cout << "\n\n=============== WELCOME TO MELISSA PROFILER OBJECT WINDOWS C++ ================\n" << endl;

	ProfilerObject* profilerObject = new ProfilerObject(license, dataPath);

	bool shouldContinueRunning = true;

	while (shouldContinueRunning)
	{
		DataContainer dataContainer = DataContainer();

		if (testFile.empty())
		{
			string inputFile;

			cout << "\nFill in each value to see the Profiler Object results" << endl;

			cout << "File Path: ";
			getline(cin, inputFile);
			dataContainer.InputFile = inputFile;
		}
		else
		{
			dataContainer.InputFile = testFile;
		}

		// Print user input
		cout << "\n==================================== INPUTS ===================================\n" << endl;

		vector<string> sections = dataContainer.GetWrapped(dataContainer.InputFile, 50);

		cout << "                        Input File: " + sections[0] << endl;

		for (int i = 1; i < sections.size(); i++)
		{
			if ((i == sections.size() - 1) && sections[i].back() == '\\');
			{
				sections[i] = sections[i].substr(0, sections[i].size() - 1);
			}
			cout << "                              " + sections[i] << endl;
		}

		// Execute Profiler Object
		profilerObject->ExecuteObjectAndResultCodes(dataContainer);

		// Print output
		cout << "\n==================================== OUTPUT ===================================\n";
		cout << "\n\tProfiler Object Information:\n";
		cout << "\n\t        TABLE STATISTICS\n\n";
		cout << "\t         TableRecordCount           :  " << profilerObject->mdProfilerObj->GetTableRecordCount()                     << "\n";
		cout << "\t         ColumnCount                :  " << profilerObject->mdProfilerObj->GetColumnCount()                          << "\n";
		cout << "\n";
		cout << "\t         ExactMatchDistinctCount    :  " << profilerObject->mdProfilerObj->GetTableExactMatchDistinctCount()         << "\n";
		cout << "\t         ExactMatchDupesCount       :  " << profilerObject->mdProfilerObj->GetTableExactMatchDupesCount()            << "\n";
		cout << "\t         ExactMatchLargestGroup     :  " << profilerObject->mdProfilerObj->GetTableExactMatchLargestGroup()          << "\n";
		cout << "\n";
		cout << "\t         ContactMatchDistinctCount  :  " << profilerObject->mdProfilerObj->GetTableContactMatchDistinctCount()       << "\n";
		cout << "\t         ContactMatchDupesCount     :  " << profilerObject->mdProfilerObj->GetTableContactMatchDupesCount()          << "\n";
		cout << "\t         ContactMatchLargestGroup   :  " << profilerObject->mdProfilerObj->GetTableContactMatchLargestGroup()        << "\n";
		cout << "\n";
		cout << "\t         HouseholdMatchDistinctCount:  " << profilerObject->mdProfilerObj->GetTableHouseholdMatchDistinctCount()     << "\n";
		cout << "\t         HouseholdMatchDupesCount   :  " << profilerObject->mdProfilerObj->GetTableHouseholdMatchDupesCount()        << "\n";
		cout << "\t         HouseholdMatchLargestGroup :  " << profilerObject->mdProfilerObj->GetTableHouseholdMatchLargestGroup()      << "\n";
		cout << "\n";
		cout << "\t         AddressMatchDistinctCount  :  " << profilerObject->mdProfilerObj->GetTableAddressMatchDistinctCount()       << "\n";
		cout << "\t         AddressMatchDupesCount     :  " << profilerObject->mdProfilerObj->GetTableAddressMatchDupesCount()          << "\n";
		cout << "\t         AddressMatchLargestGroup   :  " << profilerObject->mdProfilerObj->GetTableAddressMatchLargestGroup()        << "\n";

		cout << "\n\n\t        COLUMN STATISTICS\n\n";

		// STATE Iterator Example
		cout << "\t         STATE Value        Count\n";
		profilerObject->mdProfilerObj->StartDataFrequency("state", mdProfiler::Order::OrderCountAscending);
		do {
			cout << "\t              " << setw(16) << left << profilerObject->mdProfilerObj->GetDataFrequencyValue("state")
			<< setw(10) << left << profilerObject->mdProfilerObj->GetDataFrequencyCount("state") << "\n";

		} while (profilerObject->mdProfilerObj->GetNextDataFrequency("state") == 1);
		cout << "\n";


		// POSTAL Iterator Example
		cout << "\t         POSTAL Pattern     Count\n";
		profilerObject->mdProfilerObj->StartPatternFrequency("zip", mdProfiler::Order::OrderCountAscending);
		do {
			cout << "\t              " << setw(16) << left << profilerObject->mdProfilerObj->GetPatternFrequencyValue("zip")
				<< setw(10) << left << profilerObject->mdProfilerObj->GetPatternFrequencyCount("zip") << "\n";

		} while (profilerObject->mdProfilerObj->GetNextPatternFrequency("zip") == 1);

		bool isValid = false;
		if (!testFile.empty())
		{
			isValid = true;
			shouldContinueRunning = false;
		}
		while (!isValid)
		{
			string testAnotherResponse;

			cout << "\nTest another file? (Y/N)" << endl;
			getline(cin, testAnotherResponse);

			if (!testAnotherResponse.empty())
			{
				if (testAnotherResponse == "y" || testAnotherResponse == "Y")
				{
					isValid = true;
				}
				else if (testAnotherResponse == "n" || testAnotherResponse == "N")
				{
					isValid = true;
					shouldContinueRunning = false;
				}
				else
				{
					cout << "Invalid Response, please respond 'Y' or 'N'" << endl;
				}
			}
		}
	}
	delete profilerObject->mdProfilerObj;

	cout << "\n==================== THANK YOU FOR USING MELISSA C++ OBJECT ===================\n" << endl;
}

