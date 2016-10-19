#ifndef _CSVPARSER_H
#define _CSVPARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>

using namespace std;

class CSVParser
{
public:
	CSVParser(std::string fileName)
		: _fileName(fileName)
	{
	}

	~CSVParser()
	{
		_csvContent.clear();
	}

	void parseCsv(char delimiter)
	{
		ifstream input(_fileName);
		if (input.fail())
			throw ("Impossible to open file " + _fileName);

		std::string line;
		while (getline(input, line) && input.good())
		{
			std::vector<std::string> row = csv_read_row(line, delimiter);
			if (row.size() > 0)
				_csvContent.push_back(row);
			else
				continue;
		}
		input.close();
	}

	std::vector<std::vector<std::string>>& getCsvContent() { return _csvContent; }

private:
	std::vector<std::string> csv_read_row(std::string &line, char delimiter)
	{
		std::stringstream ss(line);
		return csv_read_row(ss, delimiter);
	}

	std::vector<std::string> csv_read_row(std::istream &in, char delimiter)
	{
		std::stringstream ss;
		bool inquotes = false;
		std::vector<std::string> row;//relying on RVO
		while (in.good())
		{
			char c = in.get();
			if (!inquotes && c == '"') //beginquotechar
			{
				inquotes = true;
			}
			else if (inquotes && c == '"') //quotechar
			{
				if (in.peek() == '"')//2 consecutive quotes resolve to 1
				{
					ss << (char)in.get();
				}
				else //endquotechar
				{
					inquotes = false;
				}
			}
			else if (!inquotes && c == delimiter) //end of field
			{
				row.push_back(ss.str());
				ss.str("");
			}
			else if (!inquotes && (c == '\r' || c == '\n'))
			{
				if (in.peek() == '\n') { in.get(); }
				row.push_back(ss.str());
				return row;
			}
			else
			{
				ss << c;
			}
		}

		return row;
	}

private:
	std::string _fileName;
	std::vector<std::vector<std::string>> _csvContent;
};

#endif // !_CSVPARSER_H