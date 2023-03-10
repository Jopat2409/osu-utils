/*
* Implementation of methods for reading .osr binary files.
* Based on the wiki page https://osu.ppy.sh/wiki/en/Client/File_formats/Osr_%28file_format%29
* Created by: Joe Paton
* Last Edited: 14/02/2023
*/

#include "..\include\replay.h"

Osu::Replay::Replay(const char* filePath)
{
	OsuFile readFile(filePath);

	readFile.ReadType<byte_t>(gameMode);
	readFile.ReadType<int_t>(gameVersion);
	readFile.ReadString(md5Hash_b);
	readFile.ReadString(playerName);
	readFile.ReadString(md5Hash_r);
	readFile.ReadType<short_t>(num300s);
	readFile.ReadType<short_t>(num100s);
	readFile.ReadType<short_t>(num50s);
	readFile.ReadType<short_t>(numGekis);
	readFile.ReadType<short_t>(numKatus);
	readFile.ReadType<short_t>(numMisses);
	readFile.ReadType<int_t>(totalScore);
	readFile.ReadType<short_t>(greatestCombo);
	readFile.ReadType<byte_t>(fullCombo);
	readFile.ReadType<int_t>(modsUsed);
	readFile.ReadString(lifeBar);
	readFile.ReadType<long_t>(timeStamp);
	readFile.ReadLzma(replayData);
	readFile.ReadType<long_t>(onlineScoreID);
	readFile.Close();

}

Osu::Replay::~Replay()
{
	delete[] this->md5Hash_b;
	delete[] this->md5Hash_r;
	delete[] this->playerName;
	delete[] this->lifeBar;
	delete[] this->replayData;
}

Osu::Replay* Osu::CreateReplayFromFile( const char* path)
{
	return new Replay(path);
}

void Osu::FreeReplay(Replay* ptr)
{
	delete ptr;
}
