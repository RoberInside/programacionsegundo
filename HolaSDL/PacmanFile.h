#ifndef _H_PACMAN_FILE_H_
#define _H_PACMAN_FILE_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class PacmanFile
{
public:
	struct Par {
		int x, y;
	};
	struct GameData
	{
		int level, score;
	};
	struct MapData
	{
		int rows, cols;
		vector<int> map;
	};
	struct GhostData
	{
		int type, age;
		Par pos, posini, dir;
	};
	struct GhostsData {
		int numGhosts;
		vector<GhostData> ghosts;
	};
	struct PacmanData
	{
		int energy, lifes;
		Par pos, posini, dir;
	};
public:

	PacmanFile(string fileName);
	~PacmanFile();

	bool save();

	inline GameData*	getGameData()		 { return &gameData;				};
	inline MapData*		getMapData()		 { return &mapData;					};
	inline GhostsData*	getGhostsData()		 { return &ghostsData;				};
	inline PacmanData*	getPacmanData()		 { return &pacmanData;				};
	inline GhostData*	getGhostData(int id) { return &ghostsData.ghosts[id];	};


private:
	GameData gameData;
	MapData mapData;
	GhostsData ghostsData;
	PacmanData pacmanData;

	string _fileName;


};
#endif // !_H_PACMAN_FILE_H_

