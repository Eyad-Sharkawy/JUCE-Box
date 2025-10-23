#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(player1);
    setSize (600, 400);

    // Enable keyboard focus and add key listener
    setWantsKeyboardFocus(true);
    addKeyListener(this);

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

//==============================================================================
// KeyListener overrides
bool MainComponent::keyPressed(const juce::KeyPress& key, juce::Component* originatingComponent)
{
    // Space bar - Play/Pause
    if (key.getKeyCode() == juce::KeyPress::spaceKey)
    {
        player1.togglePlayPause();
        return true;
    }
    
    // Play key - Play/Pause
    if (key.getKeyCode() == juce::KeyPress::playKey)
    {
        player1.togglePlayPause();
        return true;
    }
    
    // Stop key - Stop (go to start)
    if (key.getKeyCode() == juce::KeyPress::stopKey)
    {
        player1.goToStart();
        return true;
    }
    
    // Fast Forward key - Next track (go to end)
    if (key.getKeyCode() == juce::KeyPress::fastForwardKey)
    {
        player1.goToEnd();
        return true;
    }
    
    // Rewind key - Previous track (go to start)
    if (key.getKeyCode() == juce::KeyPress::rewindKey)
    {
        player1.goToStart();
        return true;
    }
    
    // New keybinds with Ctrl modifier
    if (key.getModifiers().isCtrlDown())
    {
        // Ctrl + Right Arrow - Next (go to end)
        if (key.getKeyCode() == juce::KeyPress::rightKey)
        {
            player1.goToEnd();
            return true;
        }
        
        // Ctrl + Left Arrow - Previous (go to start)
        if (key.getKeyCode() == juce::KeyPress::leftKey)
        {
            player1.goToStart();
            return true;
        }
        
        // Ctrl + R - Toggle Loop
        if (key.getKeyCode() == 'R')
        {
            player1.toggleLoop();
            return true;
        }
        
        // Ctrl + Up Arrow - Volume Up
        if (key.getKeyCode() == juce::KeyPress::upKey)
        {
            player1.volumeUp();
            return true;
        }
        
        // Ctrl + Down Arrow - Volume Down
        if (key.getKeyCode() == juce::KeyPress::downKey)
        {
            player1.volumeDown();
            return true;
        }
    }
    
    return false;
}
