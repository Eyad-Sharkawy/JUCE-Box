#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(player1);
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
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
    player1.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources() {
    player1.releaseResources();
}

//==============================================================================
// Component overrides
void MainComponent::resized()
{
    player1.setBounds(getLocalBounds());
}
