#include "CppUnitTest.h"
#include "replay.h"
#include "db.h"
#include <string>

#define STR(x) std::string(x)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OsuUtilsUnitTests
{
	TEST_CLASS(OsuUtilsUnitTests)
	{
	public:
		
		TEST_METHOD(TestReplayLoad)
		{
			Osu::Replay* test = Osu::CreateReplayFromFile("C:\\Users\\Joe\\AppData\\Local\\osu!\\Replays\\Jopat2409 - Chroma - sink to the deep sea world [AR10] (2021-10-18) Osu.osr");
			
			Assert::IsNotNull(test);
			Assert::AreEqual(0, int(test->gameMode));
			Assert::AreEqual(127, int(test->num100s));
			Assert::AreEqual(STR("Jopat2409"), STR(test->playerName));
			
			Osu::FreeReplay(test);
		}
		TEST_METHOD(TestDbLoadHeader)
		{
			Osu::BeatmapDB* test = Osu::CreateDbFromFile("D:\\osu!.db");

			Assert::IsNotNull(test);
			Assert::AreEqual(test->header.osuVersion, 20220829);
			Assert::AreEqual(test->header.folderCount, 4085);
			Assert::IsTrue(test->header.isAccountUnlocked);
			Assert::AreEqual(STR("Jopat2409"), STR(test->header.playerName));
			Assert::AreEqual(test->header.numBeatmaps, 16934);
			Osu::FreeDB(test);
		}
		TEST_METHOD(TestDbLoadBeatmaps)
		{
			Osu::BeatmapDB* test = Osu::CreateDbFromFile("D:\\osu!.db");
			Assert::IsNotNull();
			Osu::FreeDB(test);
		}
	};
}
