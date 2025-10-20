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
        playing = transportSource.isPlaying();
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
    playing = transportSource.isPlaying();
}

void PlayerAudio::pause() {
	transportSource.stop();
    playing = transportSource.isPlaying();
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
	currentGain = gain;
    transportSource.setGain(gain);

    if (gain > 0.0f)
    {
        lastNonMutedGain = gain;
        muted = false;
    }
    else
    {
        muted = true;
	}
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

void PlayerAudio::toggleMute()
{
    if (muted)
    {
        setGain(lastNonMutedGain);
    }
    else
    {
        setGain(0.0f);
    }
}

bool PlayerAudio::isMuted() const
{
    return muted;
}

float PlayerAudio::getCurrentGain() const
{
    return currentGain;
}

void PlayerAudio::togglePlayPause()
{
    if (transportSource.isPlaying())
    {
        pause();
    }
    else
    {
        play();
    }
	playing = transportSource.isPlaying();
}

bool PlayerAudio::isPlaying() const {
    return playing;
}