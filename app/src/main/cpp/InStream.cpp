#include "InStream.h"

InStream::InStream(int32_t deviceID) {
    infoLog("Creating inStream...");
    oboe::Result result;

    /*oboe::AudioStreamBuilder* streamBuilder;

    streamBuilder -> setSharingMode(oboe::SharingMode::Exclusive)
            -> setChannelCount(Stream::channelCount)
            -> setFormat(Stream::format)
            -> setSampleRate(Stream::samplingRate);*/

    streamBuilder->setDirection(oboe::Direction::Input)
            ->setCallback(nullptr);
    if (deviceID != INT32_MAX) {
        streamBuilder->setDeviceId(deviceID);
    }

    Loggable::infoLog("Opening inStream...");
    result = streamBuilder->openStream(&stream);
    if (result != oboe::Result::OK) {
        Loggable::errorLog("Error opening inStream: ", oboe::convertToText(result), "!");
    }
    Loggable::infoLog("Input stream created successfully.");
}

oboe::ResultWithValue<int32_t> InStream::read(void *audioData, int32_t numFrames) {
    return stream->read(audioData, numFrames, 0);
}