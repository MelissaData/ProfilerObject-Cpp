#include<iostream>
#include<sstream>
#include<vector>

using namespace std;

#ifndef DATACONTAINER_H
#define DATACONTAINER_H

class DataContainer
{
public:
	string InputFile;

	DataContainer() {};

	vector<string> GetWrapped(string& path, int maxLineLength)
	{
		string filePath = path;

		vector<string> lines;
		istringstream f(filePath);
		string s;

		while (getline(f, s, '\\'))
		{
			lines.push_back(s);
		}

		string currentLine;
		vector<string> wrappedString;

		for (const string& section : lines)
		{
			if ((currentLine + section).length() > maxLineLength)
			{
				wrappedString.push_back(currentLine);
				currentLine.clear();
			}

			if (section.find(path) != string::npos)
			{
				currentLine += section;
			}
			else
			{
				currentLine += section + "\\";
			}
		}

		if (!currentLine.empty())
		{
			wrappedString.push_back(currentLine);
		}

		return wrappedString;
	}
};

#endif
