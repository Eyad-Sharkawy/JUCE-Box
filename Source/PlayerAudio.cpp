/*
  ==============================================================================

    PlayerAudio.cpp
    Created: 20 Oct 2025 11:39:02am
    Author:  Eyad

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayerAudio.h"

//==============================================================================

PlayerAudio::PlayerAudio()
{
	// Register the basic audio formats (WAV, AIFF, etc.)
    formatManager.registerBasicFormats();
}

void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerAudio::releaseResources()
{
    transportSource.releaseResources();
}

bool PlayerAudio::loadFile(const juce::File& audioFile)
{
    auto* reader = formatManager.createReaderFor(audioFile);

    if (reader != nullptr) {
		auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);

        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
        return true;
    }
    return false;
}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    transportSource.getNextAudioBlock(bufferToFill);
}

void PlayerAudio::play() {
    transportSource.start();
}

void PlayerAudio::stop() {
	transportSource.stop();
}

void PlayerAudio::goToStart()
{
    transportSource.setPosition(0.0);
}

void PlayerAudio::goToEnd()
{
    if (readerSource != nullptr)
    {
        transportSource.setPosition(transportSource.getLengthInSeconds());
    }
}

void PlayerAudio::setGain(float gain)
{
    transportSource.setGain(gain);
}

void PlayerAudio::setPosition(double posInSeconds)
{
    transportSource.setPosition(posInSeconds);
}

double PlayerAudio::getPosition() const
{
    return transportSource.getCurrentPosition();
}

double PlayerAudio::getLength() const
{
    return transportSource.getLengthInSeconds();
}