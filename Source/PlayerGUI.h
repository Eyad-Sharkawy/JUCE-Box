/*
  ==============================================================================

    PlayerGUI.h
    Created: 20 Oct 2025 11:52:36am
    Author:  Eyad

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PlayerAudio.h"

//==============================================================================
/*
*/
class PlayerGUI  : public juce::Component,
                   public juce::Button::Listener,
                   public juce::Slider::Listener
{
public:
    PlayerGUI();
    ~PlayerGUI() override;

    void resized() override;

    // audio delegation called by MainComponent
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

private:
    PlayerAudio playerAudio;


    // UI Elements

	juce::TextButton loadButton{ "Load File" };
    juce::TextButton playPauseButton{ "Play" };
    juce::TextButton goToStartButton{ "Go to Start" };
	juce::TextButton goToEndButton{ "Go to End" };
	juce::TextButton muteButton{ "Mute" };

    juce::Slider volumeSlider;
	std::unique_ptr<juce::FileChooser> fileChooser;

    // listeners
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI);
};
