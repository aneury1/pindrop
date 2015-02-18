// Copyright 2014 Google Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef PINDROP_AUDIO_ENGINE_H_
#define PINDROP_AUDIO_ENGINE_H_

#include <string>

#define PINDROP_VERSION_MAJOR 1
#define PINDROP_VERSION_MINOR 0
#define PINDROP_VERSION_REVISION 0
#define PINDROP_STRING_EXPAND(X) #X
#define PINDROP_STRING(X) PINDROP_STRING_EXPAND(X)

namespace pindrop {

struct AudioConfig;
struct AudioEngineInternalState;
class SoundCollection;

class AudioEngine {
 public:
  typedef int ChannelId;

  static const ChannelId kInvalidChannel;

  typedef SoundCollection* SoundHandle;

  AudioEngine() : state_(nullptr) {}
  ~AudioEngine();

  bool Initialize(const AudioConfig* config);

  // Update audio volume per channel each frame.
  void AdvanceFrame(float delta_time);

  // Load a sound bank from a file.
  // Returns true on success.
  bool LoadSoundBank(const std::string& filename);

  // Unload a sound bank.
  void UnloadSoundBank(const std::string& filename);

  // Get a SoundHandle given its sound_id as defined in its flatbuffer.
  SoundHandle GetSoundHandle(const std::string& sound_id) const;

  // Get a SoundHandle given its filename.
  SoundHandle GetSoundHandleFromFile(const std::string& filename) const;

  // Play a sound associated with the given sound_handle.
  // Returns the channel the sound is played on.
  // Playing a SoundHandle is faster while passing the sound by sound_id incurs
  // a map lookup.
  ChannelId PlaySound(SoundHandle sound_handle);
  ChannelId PlaySound(const std::string& sound_id);

  // Checks if the sound playing on a given channel is playing
  static bool Playing(ChannelId channel_id);

  // Stop a channel.
  void Stop(ChannelId channel_id);

  // Adjusts the gain on the master bus.
  void set_master_gain(float master_gain);
  float master_gain();

  // Mutes the audio engine completely.
  void set_mute(bool mute);
  bool mute();

  // Pauses all playing sounds and streams.
  void Pause(bool pause);

  AudioEngineInternalState* state() { return state_; }

 private:
  AudioEngineInternalState* state_;
};

// Weak linkage is culled by VS & doesn't work on cygwin.
#if !defined(_WIN32) && !defined(__CYGWIN__)

extern volatile __attribute__((weak)) const char *pindrop_version_string;
volatile __attribute__((weak)) const char *pindrop_version_string =
  "pindrop "
  PINDROP_STRING(PINDROP_VERSION_MAJOR) "."
  PINDROP_STRING(PINDROP_VERSION_MINOR) "."
  PINDROP_STRING(PINDROP_VERSION_REVISION);

#endif  // !defined(_WIN32) && !defined(__CYGWIN__)

}  // namespace pindrop

#endif  // PINDROP_AUDIO_ENGINE_H_

