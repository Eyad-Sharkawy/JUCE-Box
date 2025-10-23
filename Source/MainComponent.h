#pragma once

#include <JuceHeader.h>
#include "PlayerAudio.h"
#include "PlayerGUI.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent,
                       public juce::KeyListener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
	// AudioAppComponent overrides
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;

    void resized() override;
    
    // KeyListener overrides
    bool keyPressed(const juce::KeyPress& key, juce::Component* originatingComponent) override;

private:
    //==============================================================================
    // Your private member variables go here...
    PlayerGUI  player1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
