#include "PacmanFile.h"



PacmanFile::PacmanFile(string fileName)
{
	int buffer;
	GhostData gBuffer;

	fstream s(fileName);
	//Read game Data
	s >> gameData.level >> gameData.score;
	//Read MapData
	s >> mapData.rows >> mapData.cols;
	for (int i = 0; i < (mapData.rows * mapData.cols); i++) {
		s >> buffer;
		mapData.map.push_back(buffer);
	}
	//Read GhostData
	s >> ghostsData.numGhosts;
	for (size_t i = 0; i < ghostsData.numGhosts; i++)
	{
		s	>> gBuffer.type 
			>> gBuffer.pos.x >> gBuffer.pos.y 
			>> gBuffer.posini.x >> gBuffer.posini.y 
			>> gBuffer.dir.x, gBuffer.dir.y 
			>> gBuffer.age;
		ghostsData.ghosts.push_back(gBuffer);
	}
	//Read PacmanData
	s	>> pacmanData.pos.x		>> pacmanData.pos.y
		>> pacmanData.posini.x	>> pacmanData.posini.y
		>> pacmanData.dir.x		>> pacmanData.dir.y
		>> pacmanData.energy	>> pacmanData.lifes;
	//Close File
	s.close();
}


PacmanFile::~PacmanFile()
{
}
