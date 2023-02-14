#include "..\include\db.h"

Osu::BeatmapDB::BeatmapDB(const char* filePath)
{
	OsuFile readFile(filePath);
	// -------- DATABASE HEADER -------------
	readFile.ReadType<int_t>(this->header.osuVersion);
	readFile.ReadType<int_t>(this->header.folderCount);
	readFile.ReadType<byte_t>(this->header.isAccountUnlocked);
	readFile.ReadType<long_t>(this->header.dateAccountUnlocked);
	readFile.ReadString(this->header.playerName);
	readFile.ReadType<int_t>(this->header.numBeatmaps);
	this->beatmaps = new Beatmap[this->header.numBeatmaps]();
	for (int i = 0; i < this->header.numBeatmaps; i++)
	{
	}
	readFile.Close();
}

Osu::BeatmapDB::~BeatmapDB()
{
	// free memory
	delete this->header.playerName;
	delete[] this->beatmaps;
}


Osu::BeatmapDB* Osu::CreateDbFromFile(const char* path)
{
	return new BeatmapDB(path);
}

void Osu::FreeDB(Osu::BeatmapDB* ptr)
{
	delete ptr;
}
