#ifndef OBOERECORD_AUDIOENGINE_H
#define OBOERECORD_AUDIOENGINE_H

#include "AudioRecord.h"
#include "InStream.h"
#include "OutStream.h"
#include "FilterAdapter.h"
#include <jni.h>
#include "AudioRecord.h"
#include "Loggable.h"

enum class EngineState {Idle, Recording, Playing};

class AudioEngine : Loggable, oboe::AudioStreamCallback {
private:
    AudioRecord* record;
    EngineState state;
    int ampliFactor = 1;
    bool cacheData = false;
    uint64_t processedFrameCount = 0;

    InStream* inStream;
    OutStream* outStream;
    FilterAdapter* filter;

    oboe::DataCallbackResult outputCallback(void* audioData, int32_t numFrames);
    oboe::DataCallbackResult inputCallback(void* audioData, int32_t numFrames);
    void startThroughput();
    void stopThroughput();

public:
    AudioEngine();
    void startRecording();
    void stopRecording();
    void startListening();
    void stopListening();
    void startPlaying();
    void stopPlaying();
    void setAmplificationFactor(int factor) {ampliFactor = factor; };
    bool storeRecord(std::string filepath) const;

    oboe::DataCallbackResult
    onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32_t numFrames) override;
    void onErrorBeforeClose(oboe::AudioStream *oboeStream, oboe::Result error) override;
    void onErrorAfterClose(oboe::AudioStream *oboeStream, oboe::Result error) override;
};

#endif //OBOERECORD_AUDIOENGINE_H
