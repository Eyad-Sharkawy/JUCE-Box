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
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(playPauseButton);
    addAndMakeVisible(goToStartButton);
    addAndMakeVisible(goToEndButton);
    addAndMakeVisible(muteButton);
    addAndMakeVisible(loopButton);

    loadButton.addListener(this);
    volumeSlider.addListener(this);
    speedSlider.addListener(this);
    positionSlider.addListener(this);
    playPauseButton.addListener(this);
    goToStartButton.addListener(this);
    goToEndButton.addListener(this);
    muteButton.addListener(this);
    loopButton.addListener(this);
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.8);
    speedSlider.setRange(0.25, 2.0, 0.25);
    speedSlider.setSkewFactorFromMidPoint(1.0);
    speedSlider.setValue(1.0);
    speedSlider.setTextValueSuffix("x");
    
    // Position slider setup
    positionSlider.setRange(0.0, 1.0, 0.001);
    positionSlider.setValue(0.0);
    positionSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    positionSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    // Initialize metadata labels
    addAndMakeVisible(titleLabel);
    addAndMakeVisible(artistLabel);
    addAndMakeVisible(albumLabel);
    addAndMakeVisible(durationLabel);
    addAndMakeVisible(sampleRateLabel);
    addAndMakeVisible(channelsLabel);
    
    // Initialize position display labels
    addAndMakeVisible(currentTimeLabel);
    addAndMakeVisible(totalTimeLabel);

    // Style the labels
    titleLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    titleLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    artistLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    albumLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    durationLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    sampleRateLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    channelsLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    
    // Style position labels
    currentTimeLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    currentTimeLabel.setJustificationType(juce::Justification::centredLeft);
    totalTimeLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    totalTimeLabel.setJustificationType(juce::Justification::centredRight);
    
    // Start timer for position updates
    startTimer(50); // Update every 50ms
}

PlayerGUI::~PlayerGUI() {}

void PlayerGUI::resized() {
    auto area = getLocalBounds().reduced(10);

    // Metadata display area (top)
    auto metadataArea = area.removeFromTop(120);
    titleLabel.setBounds(metadataArea.removeFromTop(25));
    artistLabel.setBounds(metadataArea.removeFromTop(20));
    albumLabel.setBounds(metadataArea.removeFromTop(20));

    auto infoRow = metadataArea.removeFromTop(20);
    durationLabel.setBounds(infoRow.removeFromLeft(150));
    sampleRateLabel.setBounds(infoRow.removeFromLeft(100));
    channelsLabel.setBounds(infoRow.removeFromLeft(100));

    area.removeFromTop(10);

    // Control buttons (middle)
    auto top = area.removeFromTop(40);
    loadButton.setBounds(top.removeFromLeft(120));
    goToStartButton.setBounds(top.removeFromLeft(120));
    playPauseButton.setBounds(top.removeFromLeft(120));
    goToEndButton.setBounds(top.removeFromLeft(120));
    loopButton.setBounds(top.removeFromLeft(120));

    area.removeFromTop(10);

    // Position slider with time labels
    auto positionArea = area.removeFromTop(50);
    auto timeRow = positionArea.removeFromTop(20);
    currentTimeLabel.setBounds(timeRow.removeFromLeft(80));
    totalTimeLabel.setBounds(timeRow.removeFromRight(80));
    positionSlider.setBounds(positionArea);

    area.removeFromTop(10);

    // Volume + Speed controls (bottom)
    auto bottomRow = area.removeFromTop(30);
    volumeSlider.setBounds(bottomRow.removeFromLeft(200));
    speedSlider.setBounds(bottomRow.removeFromLeft(200));
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
                    if (playerAudio.loadFile(file)) {
                        playerAudio.play();
                        playPauseButton.setButtonText(playerAudio.isPlaying() ? "||" : "|>");
                        updateMetadataDisplay();
                    }
                }
                fileChooser.reset();
            });
    }
    else if (button == &playPauseButton)
    {
        playerAudio.togglePlayPause();
        playPauseButton.setButtonText(playerAudio.isPlaying() ? "||" : "|>");
    }
    else if (button == &goToStartButton)
    {
        playerAudio.goToStart();
		playerAudio.play();
		playPauseButton.setButtonText("||");
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
    else if (button == &loopButton)
    {
        playerAudio.toggleLoop();
        playerAudio.isLoopEnabled() ? loopButton.setButtonText("Disable Loop") : loopButton.setButtonText("Enable Loop");
    }
}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
    {
        playerAudio.setGain((float) volumeSlider.getValue());

        muteButton.setButtonText(playerAudio.isMuted() ? "Unmute" : "Mute");
    }
    else if (slider == &speedSlider)
    {
        playerAudio.setSpeed((float) speedSlider.getValue());
    }
    else if (slider == &positionSlider)
    {
        double length = playerAudio.getLength();
        if (length > 0.0)
        {
            double newPosition = positionSlider.getValue() * length;
            playerAudio.setPosition(newPosition);
        }
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

void PlayerGUI::updateMetadataDisplay()
{
    auto metadata = playerAudio.getCurrentMetadata();

    titleLabel.setText(metadata.title, juce::dontSendNotification);
    artistLabel.setText("Artist: " + metadata.artist, juce::dontSendNotification);
    albumLabel.setText("Album: " + metadata.album, juce::dontSendNotification);

    // Format duration as MM:SS
    int minutes = (int)(metadata.lengthInSeconds / 60);
    int seconds = (int)(metadata.lengthInSeconds) % 60;
    durationLabel.setText("Duration: " + juce::String::formatted("%02d:%02d", minutes, seconds), juce::dontSendNotification);

    sampleRateLabel.setText("Sample Rate: " + juce::String((int)metadata.sampleRate) + " Hz", juce::dontSendNotification);
    channelsLabel.setText("Channels: " + juce::String(metadata.numChannels), juce::dontSendNotification);

    // Update position display
    updatePositionDisplay();

    // Force repaint
    repaint();
}

void PlayerGUI::timerCallback()
{
    updatePositionDisplay();
}

juce::String PlayerGUI::formatTime(double timeInSeconds)
{
    int minutes = (int)(timeInSeconds / 60);
    int seconds = (int)(timeInSeconds) % 60;
    return juce::String::formatted("%02d:%02d", minutes, seconds);
}

void PlayerGUI::updatePositionDisplay()
{
    double currentPosition = playerAudio.getPosition();
    double totalLength = playerAudio.getLength();
    
    if (totalLength > 0.0)
    {
        // Update position slider (only if user isn't dragging it)
        if (!positionSlider.isMouseButtonDown())
        {
            positionSlider.setValue(currentPosition / totalLength, juce::dontSendNotification);
        }
        
        // Update time labels
        currentTimeLabel.setText(formatTime(currentPosition), juce::dontSendNotification);
        totalTimeLabel.setText(formatTime(totalLength), juce::dontSendNotification);
    }
    else
    {
        currentTimeLabel.setText("00:00", juce::dontSendNotification);
        totalTimeLabel.setText("00:00", juce::dontSendNotification);
        positionSlider.setValue(0.0, juce::dontSendNotification);
    }
}

//==============================================================================
// Keyboard control methods
void PlayerGUI::togglePlayPause()
{
    playerAudio.togglePlayPause();
    playPauseButton.setButtonText(playerAudio.isPlaying() ? "||" : "|>");
}

void PlayerGUI::goToStart()
{
    playerAudio.goToStart();
    playerAudio.play();
    playPauseButton.setButtonText("||");
}

void PlayerGUI::goToEnd()
{
    playerAudio.goToEnd();
}