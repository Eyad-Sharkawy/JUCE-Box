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
class PlayerAudio  : public juce::ChangeBroadcaster
{
public:
    PlayerAudio();

    // Audio Handling

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

    // Transport controls

    void loadFile(const juce::File& audioFile);
	void play();
    void stop();
    void goToStart();
    void goToEnd();
private:
	juce::AudioFormatManager formatManager;
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
	juce::AudioTransportSource transportSource;
};
