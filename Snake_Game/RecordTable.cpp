#include "RecordTable.h"
#include <fstream>
#include <sstream>

#include "Settings.h"

namespace SnakeGame
{
	RecordTable::RecordTable(const Settings& currentSettings) : settings(currentSettings)
	{
	}

	void RecordTable::AddRecord(std::wstring name, int score)
	{
		recordTable.insert({ name, score });
	}

	std::vector<std::wstring> RecordTable::GetRecords(int count) const
	{
		std::vector<std::wstring> records;
		records.reserve(count);
		const std::multimap<int, std::wstring> orderedTable = GetOrderedTable();
		int index = 1;
		std::multimap<int, std::wstring>::const_iterator current = orderedTable.begin();
		
		while (current != orderedTable.end() && index <= settings.bigRecordsSize)
		{
			std::wostringstream currentString;
			currentString << index << L". " << current->second << L" ";
			records.push_back(currentString.str());
		}
		return records;
	}

	bool RecordTable::Serialize() const
	{
		std::wofstream output(settings.recordsFileName);
		if (output.is_open())
		{
			const std::multimap<int, std::wstring> orderedTable = GetOrderedTable();
			int index = 0;
			std::multimap<int, std::wstring>::const_iterator current = orderedTable.begin();
			while (current != orderedTable.end() && index < settings.bigRecordsSize)
			{
				output << current->second << L" " << current->first;
				++index;
				++current;
			}
			output.close();
			return true;
		}
		else
		{
			return false;
		}
	}

	void RecordTable::Deserialize()
	{
		recordTable.clear();
		recordTable.reserve(settings.bigRecordsSize);
		std::wifstream input(settings.recordsFileName);
		if (input.is_open())
		{
			std::wstring name;
			int score = 0;
			while (input >> name >> score)
			{
				recordTable.insert({ name, score });
			}
			input.close();
		}
		else
		{
			for (int i = 1; i <= settings.bigRecordsSize; ++i)
			{
				recordTable.insert({ L"XYZ", i * settings.difficultyToScore.at(settings.difficultyLevelCount - 1) });
			}
		}
	}

	std::multimap<int, std::wstring> RecordTable::GetOrderedTable() const
	{
		std::multimap<int, std::wstring> orderedTable;
		for (auto& current : recordTable)
		{
			orderedTable.insert({ current.second, current.first });
		}
		return orderedTable;
	}
}