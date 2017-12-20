#include "FileSystem.h"



FileSystem::FileSystem(string fileName):_fileName(fileName)
{
	int buffer;
	GhostData gBuffer;

	fstream s(_fileName);
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


FileSystem::~FileSystem()
{
}

bool FileSystem::save()
{//TODO: Control de fallos y excepciones
	int buffer;
	fstream s(_fileName);
	//Read game Data
	s << gameData.level << gameData.score;
	//Read MapData
	s << mapData.rows << mapData.cols;
	for (int i = 0; i < (mapData.rows * mapData.cols); i++) {

		s << mapData.map[i];
	}
	//Read GhostData
	s << ghostsData.numGhosts;
	for (size_t i = 0; i < ghostsData.numGhosts; i++)
	{
		s << ghostsData.ghosts[i].type
			<< ghostsData.ghosts[i].pos.x	 << ghostsData.ghosts[i].pos.y
			<< ghostsData.ghosts[i].posini.x << ghostsData.ghosts[i].posini.y
			<< ghostsData.ghosts[i].dir.x, ghostsData.ghosts[i].dir.y
			<< ghostsData.ghosts[i].age;
	}
	//Read PacmanData
	s << pacmanData.pos.x << pacmanData.pos.y
		<< pacmanData.posini.x << pacmanData.posini.y
		<< pacmanData.dir.x << pacmanData.dir.y
		<< pacmanData.energy << pacmanData.lifes;
	//Close File
	s.close();
	return true;
}
