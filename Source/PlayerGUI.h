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
                   public juce::Slider::Listener,
                   public juce::Timer
{
public:
    PlayerGUI();
    ~PlayerGUI() override;

    void resized() override;

    // audio delegation called by MainComponent
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();
    void updateMetadataDisplay();

private:
    PlayerAudio playerAudio;


    // UI Elements

	juce::TextButton loadButton{ "Load File" };
    juce::TextButton playPauseButton{ "|>" };
    juce::TextButton goToStartButton{ "|<" };
	juce::TextButton goToEndButton{ ">|" };
	juce::TextButton muteButton{ "Mute" };
	juce::TextButton loopButton{ "Enable Loop" };
   
    juce::Slider volumeSlider;
    juce::Slider speedSlider;
    juce::Slider positionSlider;
    std::unique_ptr<juce::FileChooser> fileChooser;

    // listeners
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void timerCallback() override;

    // Metadata
    juce::Label titleLabel;
    juce::Label artistLabel;
    juce::Label albumLabel;
    juce::Label durationLabel;
    juce::Label sampleRateLabel;
    juce::Label channelsLabel;
    
    // Position display
    juce::Label currentTimeLabel;
    juce::Label totalTimeLabel;
    
    // Helper methods
    juce::String formatTime(double timeInSeconds);
    void updatePositionDisplay();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI);
};
