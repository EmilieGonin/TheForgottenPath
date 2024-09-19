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
	vector<string> GetLevel(int level) const { return m_levels[level]; }
	LevelData GetLevelData(int level) const { return m_levelsData[level]; }

private:
	vector<vector<string>> m_levels
	{
		{ // Level 1
			"X.................X",
			"X-----------------X"
		},
		{ // Level 2
			"-------------------"
		},
		{ // Level 3
			"-------------------"
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
			/* Random Chests : */ 0,
			/* Random Traps : */ 0
		},
		{ // Level 3
			/* Random Obstacles : */ 0,
			/* Random Chests : */ 0,
			/* Random Traps : */ 0
		},
	};
};