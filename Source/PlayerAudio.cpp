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
    // Ensure normal speed initially
    resampler.setResamplingRatio(1.0);
}

void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampler.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerAudio::releaseResources()
{
    resampler.releaseResources();
    transportSource.releaseResources();
}

bool PlayerAudio::loadFile(const juce::File& audioFile)
{
    auto* reader = formatManager.createReaderFor(audioFile);

    if (reader != nullptr) {
        // Extract metadata using the same reader
        extractMetadataFromReader(reader, audioFile);
        
		auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);

        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
        playing = transportSource.isPlaying();
        return true;
    }
    else
    {
        // Reset metadata if file couldn't be read
        currentMetadata = AudioMetadata{};
        currentMetadata.filename = audioFile.getFileName();
        currentMetadata.title = currentMetadata.filename;
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

    resampler.getNextAudioBlock(bufferToFill);

    if (transportSource.hasStreamFinished()) {
        if (loopEnabled) {
            goToStart();
            play();
        } else {
            pause();
            playing = false;  // Update internal state when finished without loop
        }
    }
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

void PlayerAudio::toggleLoop()
{
    loopEnabled = !loopEnabled;
}

bool PlayerAudio::isLoopEnabled() const
{
    return loopEnabled;
}

void PlayerAudio::extractMetadataFromReader(juce::AudioFormatReader* reader, const juce::File& audioFile)
{
    // Reset metadata first
    currentMetadata = AudioMetadata{};
    
    if (reader != nullptr) {
        currentMetadata.lengthInSeconds = reader->lengthInSamples / reader->sampleRate;
		currentMetadata.sampleRate = reader->sampleRate;
		currentMetadata.numChannels = reader->numChannels;
		currentMetadata.filename = audioFile.getFileName();

        // Try to extract metadata tags
        auto metadata = reader->metadataValues;
        
        if (metadata.size() > 0) 
        {
            currentMetadata.title = metadata.getValue("Title", "");
            currentMetadata.artist = metadata.getValue("Artist", "");
            currentMetadata.album = metadata.getValue("Album", "");
            currentMetadata.genre = metadata.getValue("Genre", "");
        }

        // If no title found, use filename
        if (currentMetadata.title.isEmpty())
        {
            currentMetadata.title = currentMetadata.filename;
        }
    }
}

AudioMetadata PlayerAudio::getCurrentMetadata() const
{
    return currentMetadata;
}

void PlayerAudio::setSpeed(float ratio)
{
    ratio = juce::jlimit(0.25f, 4.0f, ratio);
    resampler.setResamplingRatio(ratio);
}

bool PlayerAudio::hasFinished() const
{
    return transportSource.hasStreamFinished() && !isPlaying();
}