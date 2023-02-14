# Osu Utils
Osu-Utils is a c++ library containing many useful utilities for reading and editing binary files related to the game osu!.

# Use

### Loading Replays from file

In order to load replays from a file, use CreateReplayFromFile
```
Osu::Replay* replay = Osu::CreateReplayFromPath("yourreplay.osr");
```

### Loading Replays from lzma stream (COMING SOON)

In order to load a replay from a pure lzma stream, use CreateReplayFromLZMA
```
Osu::Replay* replay = Osu::CreateReplayFromLZMA("lzma-stream");
```

### Loading Replays from the osu! API endpoint (COMING SOON)

In order to load a replay from a get_replay endpoint, use CreateReplayFromEndpoint
```
Osu::Replay* replay = Osu::CreateReplayFromEndpoint("your-api-endpoint")
```

### Freeing replay objects

Replay objects must be freed using FreeReplay
```
Osu::FreeReplay(replay_ptr);
```
