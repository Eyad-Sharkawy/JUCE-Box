/*
  ==============================================================================

    PlayerGUI.cpp
    Created: 20 Oct 2025 11:52:37am
    Author:  Eyad

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayerGUI.h"

//==============================================================================
PlayerGUI::PlayerGUI()
{
    addAndMakeVisible(loadButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(playButton);
    addAndMakeVisible(goToStartButton);
	addAndMakeVisible(goToEndButton);
	addAndMakeVisible(muteButton);

    loadButton.addListener(this);
    stopButton.addListener(this);
    volumeSlider.addListener(this);
	playButton.addListener(this);
    goToStartButton.addListener(this);
	goToEndButton.addListener(this);
    muteButton.addListener(this);
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.8);
}

PlayerGUI::~PlayerGUI() {}

void PlayerGUI::resized() {
    auto area = getLocalBounds().reduced(10);
    auto top = area.removeFromTop(40);
    loadButton.setBounds(top.removeFromLeft(120));
    playButton.setBounds(top.removeFromLeft(120));
    stopButton.setBounds(top.removeFromLeft(120));
    goToStartButton.setBounds(top.removeFromLeft(120));
    goToEndButton.setBounds(top.removeFromLeft(120));

    area.removeFromTop(10);
    auto bottomRow = area.removeFromTop(30);
    volumeSlider.setBounds(bottomRow.removeFromLeft(200));
    muteButton.setBounds(bottomRow.removeFromLeft(120));

}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(juce::String("Select an audio file..."), juce::File(), juce::String("*.wav;*.aiff;*.mp3"));
        fileChooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file.existsAsFile())
                {
                    if (playerAudio.loadFile(file))
                        playerAudio.play();
                }
                fileChooser.reset();
            });
    }
    else if (button == &playButton)
    {
        playerAudio.play();
    }
    else if (button == &stopButton)
    {
        playerAudio.stop();
    }
    
    else if (button == &goToStartButton)
    {
        playerAudio.goToStart();
        playerAudio.play();
    }
    else if (button == &goToEndButton)
    {
		playerAudio.goToEnd();
    }
    else if (button == &muteButton)
    {
        playerAudio.toggleMute();
		muteButton.setButtonText(playerAudio.isMuted() ? "Unmute" : "Mute");

        if (playerAudio.isMuted())
        {
            volumeSlider.setValue(0.0);
        }
        else
        {
            volumeSlider.setValue(playerAudio.getCurrentGain());
		}
	}
}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
    {
        playerAudio.setGain((float) volumeSlider.getValue());

		muteButton.setButtonText(playerAudio.isMuted() ? "Unmute" : "Mute");
    }
}

void PlayerGUI::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playerAudio.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerGUI::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    playerAudio.getNextAudioBlock(bufferToFill);
}

void PlayerGUI::releaseResources()
{
    playerAudio.releaseResources();
}