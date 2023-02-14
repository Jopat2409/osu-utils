#include "..\include\beatmap.h"


Osu::Beatmap::~Beatmap()
{
	delete[] this->artistName;
	delete[] this->artistNameUnicode;
	delete[] this->songTitle;
	delete[] this->songTitleUnicode;
	delete[] this->creatorName;
	delete[] this->difficultyName;
	delete[] this->audioFileName;
	delete[] this->md5Hash;
	delete[] this->osuFileName;
	delete[] this->songSource;
	delete[] this->songTags;
	delete[] this->folderName;
}