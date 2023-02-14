#ifndef _BEATMAP_H
#define _BEATMAP_H

#include "osufile.h"


namespace Osu
{
	struct Beatmap
	{
		char* artistName;
		char* artistNameUnicode;
		char* songTitle;
		char* songTitleUnicode;
		char* creatorName;
		char* difficultyName;
		char* audioFileName;
		char* md5Hash;
		char* osuFileName;
		byte_t rankedStatus;
		short_t numHitcircles;
		short_t numSliders;
		short_t numSpinners;
		long_t lastModificationTime;
		float_t approachRate;
		float_t circleSize;
		float_t hpDrain;
		float_t overallDifficulty;
		double_t sliderVelocity;
		int_double_t stdStarRatings;
		int_double_t taikoStarRatings;
		int_double_t ctbStarRatings;
		int_double_t maniaStarRatings;
		int_t drainTime;
		int_t totalLength;
		int_t previewTime;
		long_t* timingPoints;
		int_t difficultyID;
		int_t beatmapID;
		int_t threadID;
		byte_t stdGrade;
		byte_t taikoGrade;
		byte_t ctbGrade;
		byte_t maniaGrade;
		short_t localOffset;
		float_t stackLeniency;
		byte_t osuGameplayMode;
		char* songSource;
		char* songTags;
		short_t onlineOffset;
		char* fontUsed;
		byte_t isUnplayed;
		long_t lastTimePlayed;
		byte_t isOsz2;
		char* folderName;
		long_t lastChecked;
		byte_t ignoreBeatmapSound;
		byte_t ignoreBeatmapSkin;
		byte_t disableStoryboard;
		byte_t disableVideo;
		byte_t visualOverride;
		int_t lastModTime;
		byte_t maniaScrollSpeed;

		~Beatmap();
	};
}







#endif