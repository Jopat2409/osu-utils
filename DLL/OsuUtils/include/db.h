#ifndef _BEATMAPDB_H
#define _BEATMAPDB_H

#include "dlldef.h"
#include "osufile.h"
#include "beatmap.h"

namespace Osu
{

	struct dbheader_t
	{
		int_t osuVersion;
		int_t folderCount;
		byte_t isAccountUnlocked;
		datetime_t dateAccountUnlocked;
		char* playerName;
		int_t numBeatmaps;
		int_t userPerms;
	};

	class BeatmapDB
	{
	public:
		BeatmapDB(const char* path);
		~BeatmapDB();
		dbheader_t header;
		Beatmap* beatmaps;
		inline Beatmap& operator[](int index) {
			return this->beatmaps[index];
		}
	};
	extern "C" OSU_API BeatmapDB* CreateDbFromFile(const char* dbPath);
	extern "C" OSU_API void FreeDB(BeatmapDB * ptr);
}
#endif