# Osu Utils
Osu-Utils is a c++ library containing many useful utilities for reading and editing binary files related to the game osu!.

# Use
## Replays

### Loading Replays from file

In order to load replays from a file, use the exported function CreateReplayFromFile as shown below
```
Osu::Replay* replay = Osu::CreateReplayFromPath("yourreplay.osr");
```
