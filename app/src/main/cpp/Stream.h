#ifndef OBOERECORD_STREAM_H
#define OBOERECORD_STREAM_H


#include <oboe/Oboe.h>
#include "Loggable.h"

class Stream : public Loggable {
public:
    static uint32_t const maxRecordSize = 5 /* min's */ * 60 /* sec's per min */ * 88200 /* bytes per sec */ ;
    //static uint32_t const maxRecordSize = 5 /* sec's */ * 88200 /* bytes per sec */ ;
    static oboe::AudioFormat const format = oboe::AudioFormat::I16;
    static oboe::ChannelCount const channelCount = oboe::ChannelCount::Mono;
    static oboe::PerformanceMode const performanceMode = oboe::PerformanceMode::PowerSaving;
    static oboe::SharingMode const sharingMode = oboe::SharingMode::Exclusive;
    static uint32_t const samplingRate = 44100;
    static uint8_t const bytesPerSample = 2;
    static uint16_t const warmupFrames = samplingRate/2;

    void start();
    void stop();

protected:
    oboe::AudioStreamBuilder* streamBuilder = new oboe::AudioStreamBuilder();
    oboe::AudioStream* stream = nullptr;

    Stream();
};


#endif //OBOERECORD_STREAM_H
