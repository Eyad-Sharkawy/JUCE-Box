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
   
private:
	juce::AudioFormatManager formatManager;
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
	juce::AudioTransportSource transportSource;
	bool playing{ false };
    bool muted{ transportSource.isPlaying()};
    float lastNonMutedGain{ 0.8f };
    float currentGain{ 0.8f };
    bool loopEnabled{ false };
};
