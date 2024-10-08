#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

struct LevelData
{
	int m_randomObstacles;
	int m_randomChests;
	int m_randomTraps;
};

class LevelEditor
{
public:
	vector<string>& GetLevel(int level) { return m_levels[level]; }
	LevelData GetLevelData(int level) const { return m_levelsData[level]; }
	int GetLevelNumber() const { return m_levels.size(); }

private:
	vector<vector<string>> m_levels
	{
		{ // Level 1
			"+-----------------+",
			"|..!!.!.!....M.!.!|",
			"_@.!.S.....!......_",
			"|.....!.!..!.!=!..|",
			"+-----------------+"
		},
		{ // Level 2
			"+-------+",
			"|....F.._",
			"|.......|",
			"|..#####|",
			"|.......|",
			"|.......|",
			"|#####..|",
			"|.=.!..M|",
			"|#####..|",
			"|.......|",
			"|....E..|",
			"|.S.....|",
			"|.......|",
			"|#G#####|",
			"|......=|",
			"|###.###|",
			"_@...!..|",
			"+-------+"
		},
		{ // Level 3
			"+-----------------+",
			"|.................|",
			"|.................|",
			"|..#############..|",
			"|..#=....=....=#..|",
			"|..#=....T....=#..|",
			"|..#=.........=#..|",
			"|..######G######..|",
			"|.................|",
			"|.................|",
			"|.............E...|",
			"|.................|",
			"_@..S.............|",
			"|.................|",
			"+-----------------+",
		},
	};

	vector<LevelData> m_levelsData
	{
		{ // Level 1
			/* Random Obstacles : */ 0,
			/* Random Chests : */ 0,
			/* Random Traps : */ 0
		},
		{ // Level 2
			/* Random Obstacles : */ 0,
			/* Random Chests : */ 2,
			/* Random Traps : */ 5
		},
		{ // Level 3
			/* Random Obstacles : */ 5,
			/* Random Chests : */ 0,
			/* Random Traps : */ 20
		},
	};
};