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
class PlayerGUI  : public juce::Component
{
public:
    PlayerGUI(PlayerAudio& audio);
    ~PlayerGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    PlayerAudio& playerAudio;


    // UI Elements

	juce::TextButton loadButton;
    juce::TextButton playButton;
    juce::TextButton stopButton;
    juce::TextButton startButton;
    juce::TextButton endButton;
	std::unique_ptr<juce::FileChooser> fileChooser;

    void setupButton();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI);
};
