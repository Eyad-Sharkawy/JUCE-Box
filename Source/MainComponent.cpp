#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : playerGUI(playerAudio)
{
	addAndMakeVisible(playerGUI);
    setSize (600, 400);

    // Open audio device: 0 inputs, 2 outputs
    setAudioChannels(0, 2);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================
// AudioAppComponent overrides
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
	playerAudio.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
    playerAudio.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources() {
    playerAudio.releaseResources();
}

//==============================================================================
// Component overrides
void MainComponent::paint (juce::Graphics& g) { juce::ignoreUnused(g); }

void MainComponent::resized()
{
    playerGUI.setBounds(getLocalBounds());
}
