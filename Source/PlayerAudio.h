/*
  ==============================================================================

    PlayerAudio.h
    Created: 20 Oct 2025 11:39:02am
    Author:  Eyad

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/

struct AudioMetadata
{
    juce::String title;
    juce::String artist;
    juce::String album;
    juce::String genre;
    double lengthInSeconds{ 0.0 };
    double sampleRate{ 0.0 };
	int numChannels{ 0 };
	juce::String filename; // Fallback when no metadata is available
};

//==============================================================================
/*
*/
class PlayerAudio
{
public:
    PlayerAudio();

    // Audio Handling

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

    // Transport controls

	bool loadFile(const juce::File& audioFile);
	void play();
    void pause();
    void goToStart();
    void goToEnd();

    // Parameters / state
    void setGain(float gain);
    void setPosition(double posInSeconds);
    double getPosition() const;
    double getLength() const;
    void toggleMute();
    bool isMuted() const;
    float getCurrentGain() const;
	void togglePlayPause();
	bool isPlaying() const;
	void toggleLoop();
	bool isLoopEnabled() const;

    // Metadata
	AudioMetadata getCurrentMetadata() const;
	void extractMetadataFromReader(juce::AudioFormatReader* reader, const juce::File& audioFile);
   
   // Speed control: 1.0 = normal, 2.0 = double-speed, 0.5 = half-speed
   void setSpeed(float ratio);
   
private:
	juce::AudioFormatManager formatManager;
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
	juce::AudioTransportSource transportSource;
    // Resampler wraps transportSource to change playback rate
    juce::ResamplingAudioSource resampler{ &transportSource, false, 2 };
	bool playing{ false };
    bool muted{ transportSource.isPlaying()};
    float lastNonMutedGain{ 0.8f };
    float currentGain{ 0.8f };
    bool loopEnabled{ false };
   AudioMetadata currentMetadata;
};
