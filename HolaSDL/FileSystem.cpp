#include "FileSystem.h"



FileSystem::FileSystem(string fileName):_fileName(fileName)
{
	bool isASavedFile = false;
	int buffer;
	GhostData gBuffer;

	fstream s(_fileName);
	int levelPos = fileName.find("level");
	if ( levelPos != std::string::npos) 
	{//Is a source file
		//Set game data to default values
		isASavedFile = true;
		levelPos += 5;
		string level;
		for (int i = levelPos; fileName[i] != '.'; i++) {
			level += fileName[i];
		}
		gameData.level = stoi(level);
		gameData.score = 0;
	}
	else 
	{//Is a saved file;
		//Read game data
		s >> gameData.level >> gameData.score;
	}
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
			>> gBuffer.pos.x	>> gBuffer.pos.y
			>> gBuffer.posini.x >> gBuffer.posini.y
			>> gBuffer.dir.x	>> gBuffer.dir.y;
		if (gBuffer.type) s//if is a smartghost there's age, if not don't
			>> gBuffer.age;

		ghostsData.ghosts.push_back(gBuffer);
	}
	//Read PacmanData
	s	>> pacmanData.pos.x		>> pacmanData.pos.y
		>> pacmanData.posini.x	>> pacmanData.posini.y
		>> pacmanData.dir.x		>> pacmanData.dir.y;
	if (isASavedFile)
	{	//Read energy and lifes
		s >> pacmanData.energy	>> pacmanData.lifes;
	}
	else
	{	//Set to default values
		pacmanData.energy = 0;
		pacmanData.lifes = 3;
	}
	//Close File
	s.close();
}

//Every variable are in static memory, so don't need to delete anything
FileSystem::~FileSystem(){}

bool FileSystem::save(string code)
{//TODO: Control de fallos y excepciones
	fstream s(code + ".pac");
	//Read game Data
	s << gameData.level <<" "<< gameData.score << endl;
	//Read MapData
	s << mapData.rows <<" "<< mapData.cols<< endl;
	for (int i = 0; i < mapData.rows; i++) {
		for (size_t j = 0; j < mapData.cols; j++){
			s << mapData.map[i*mapData.cols + j];
		}
	}
	//Read GhostData
	s << ghostsData.numGhosts << endl;
	for (size_t i = 0; i < ghostsData.numGhosts; i++)
	{
		s	<< ghostsData.ghosts[i].type	 <<" "
			<< ghostsData.ghosts[i].pos.x	 <<" "<< ghostsData.ghosts[i].pos.y		<<" "
			<< ghostsData.ghosts[i].posini.x <<" "<< ghostsData.ghosts[i].posini.y	<<" "
			<< ghostsData.ghosts[i].dir.x	 <<" "<< ghostsData.ghosts[i].dir.y		<<" "
			<< ghostsData.ghosts[i].age		 << endl;
	}
	//Read PacmanData
	s	<< pacmanData.pos.x		<<" "<< pacmanData.pos.y	<<" "
		<< pacmanData.posini.x	<<" "<< pacmanData.posini.y	<<" "
		<< pacmanData.dir.x		<<" "<< pacmanData.dir.y	<<" "
		<< pacmanData.energy	<<" "<< pacmanData.lifes	<< endl;
	
	//Close File
	s.close();
	return true;
}
