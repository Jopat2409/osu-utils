#ifndef _REPLAY_H
#define _REPLAY_H

#include "dlldef.h"
#include "osufile.h"

namespace Osu 
{
	/**
	* Class encapsulating a replay object
	*
	*/
	class Replay
	{
	public:
		/**
		* Creates replay from path
		*
		* @param replayFile - path to the replay
		*/
		Replay(const char* replayFile);

		/**
		* Frees memory allocated in Replay()
		*/
		OSU_API ~Replay();

		byte_t gameMode;
		int_t gameVersion;
		char* md5Hash_b;
		char* playerName;
		char* md5Hash_r;
		short_t num300s;
		short_t num100s;
		short_t num50s;
		short_t numGekis;
		short_t numKatus;
		short_t numMisses;
		int_t totalScore;
		short_t greatestCombo;
		byte_t fullCombo;
		int_t modsUsed;
		char* lifeBar;
		long_t timeStamp;
		char* replayData;
		long_t onlineScoreID;
	};

	extern "C" OSU_API Replay * CreateReplayFromFile(const char* path);
	extern "C" OSU_API void FreeReplay(Replay * ptr);

}


#endif