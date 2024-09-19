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
			"|..!!.!.!......!.!|",
			"_.@.!.S.....!....._",
			"|.....!.!..!.!=!..|",
			"+-----------------+"
		},
		{ // Level 2
			"XXXXXXXX",
			"X....F._",
			"X.#####X",
			"X......X",
			"X#####.X",
			"X.=.!..X",
			"X#####.X",
			"X......X",
			"X...S..X",
			"X.S....X",
			"X......X",
			"X#G####X",
			"X.....=X",
			"X###.##X",
			"_.@..!.X",
			"XXXXXXXX"
		},
		{ // Level 3
			"XXXXXXXXXXXXXXXXXXX",
			"X.................X",
			"X.................X",
			"X..#############..X",
			"X..#=....=..F.=#..X",
			"X..#=..F......=#..X",
			"X..#=.........=#..X",
			"X..######G######..X",
			"X.................X",
			"X....S............X",
			"X.................X",
			"X.................X",
			"_...S........S....X",
			"X.................X",
			"XXXXXXXXXXXXXXXXXXX",
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
			/* Random Traps : */ 10
		},
		{ // Level 3
			/* Random Obstacles : */ 10,
			/* Random Chests : */ 0,
			/* Random Traps : */ 20,
		},
	};
};