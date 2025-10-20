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
PlayerGUI::PlayerGUI(PlayerAudio& audio) : playerAudio(audio)
{
	addAndMakeVisible(&loadButton);
    addAndMakeVisible(&playButton);
    addAndMakeVisible(&stopButton);
    addAndMakeVisible(&startButton);
    addAndMakeVisible(&endButton);

    setupButton();

    setSize(600, 400);
}

PlayerGUI::~PlayerGUI() {}

void PlayerGUI::paint(juce::Graphics& g) {
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void PlayerGUI::resized() {

    loadButton.setBounds(10, 10, 100, 40);
    playButton.setBounds(120, 10, 100, 40);
    stopButton.setBounds(230, 10, 100, 40);
    startButton.setBounds(340, 10, 120, 40);
    endButton.setBounds(470, 10, 120, 40);
}

void PlayerGUI::setupButton() {
    loadButton.setButtonText("Load");
	playButton.setButtonText("Play");
	stopButton.setButtonText("Stop");
    startButton.setButtonText("Go to start");
    endButton.setButtonText("Go to end");

	// Lambda functions for button actions

    loadButton.onClick = [this]() {
        fileChooser = std::make_unique<juce::FileChooser>(juce::String("Select an audio file..."), juce::File(), juce::String("*.wav;*.aiff;*.mp3"));
        fileChooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file.existsAsFile())
                    playerAudio.loadFile(file);
                fileChooser.reset();
            });
        };

    playButton.onClick = [this]() {
        playerAudio.play();
        };

    stopButton.onClick = [this]() {
        playerAudio.stop();
        };

    startButton.onClick = [this]() {
        playerAudio.goToStart();
        };

    endButton.onClick = [this]() {
        playerAudio.goToEnd();
        };
}