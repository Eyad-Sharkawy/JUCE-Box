# JUCEBox - Audio Player

A modern, feature-rich audio player built with the JUCE framework. JUCEBox provides an intuitive interface for playing audio files with advanced controls and keyboard shortcuts.

## Features

### 🎵 Audio Playback
- Support for multiple audio formats (WAV, AIFF, MP3)
- High-quality audio processing with resampling
- Real-time audio visualization
- Precise position control with scrubbing

### 🎛️ Advanced Controls
- **Playback Controls**: Play, Pause, Stop, Go to Start/End
- **Volume Control**: Slider with mute functionality
- **Speed Control**: Variable playback speed (0.25x to 2.0x)
- **Loop Mode**: Seamless looping capability
- **Position Scrubbing**: Click and drag to seek through audio

### ⌨️ Keyboard Shortcuts
- **Space** - Play/Pause
- **Play Key** - Play/Pause
- **Stop Key** - Stop and go to start
- **Fast Forward Key** - Go to end
- **Rewind Key** - Go to start
- **Ctrl + Right Arrow** - Next (go to end)
- **Ctrl + Left Arrow** - Previous (go to start)
- **Ctrl + R** - Toggle Loop
- **Ctrl + Up Arrow** - Volume Up
- **Ctrl + Down Arrow** - Volume Down

### 📊 Audio Information
- **Metadata Display**: Title, Artist, Album, Duration
- **Technical Details**: Sample Rate, Channel Count
- **Time Display**: Current position and total duration
- **Visual Feedback**: Real-time position updates

## Screenshots

The player features a clean, modern interface with:
- Metadata display at the top
- Control buttons in the center
- Position slider with time labels
- Volume and speed controls at the bottom

## Technical Details

### Built With
- **JUCE Framework** - Cross-platform C++ audio framework
- **Visual Studio 2022** - Development environment
- **C++17** - Modern C++ features

### Architecture
- **PlayerAudio**: Core audio processing and transport
- **PlayerGUI**: User interface and controls
- **MainComponent**: Application entry point and keyboard handling

### Audio Processing
- Multi-format audio file support
- Real-time resampling for speed control
- High-quality audio transport
- Efficient memory management

## Installation

### Prerequisites
- Visual Studio 2022 or later
- JUCE framework (included in project)
- Windows 10/11 (primary target platform)

### Building
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/JUCEBox.git
   cd JUCEBox
   ```

2. Open `Builds/VisualStudio2022/JUCEBox.sln` in Visual Studio

3. Build the solution (Ctrl+Shift+B)

4. Run the application (F5)

## Usage

### Loading Audio Files
1. Click the "Load File" button
2. Select an audio file (WAV, AIFF, or MP3)
3. The file will automatically start playing

### Playback Controls
- Use the play/pause button or press Space
- Drag the position slider to scrub through the audio
- Adjust volume with the volume slider or keyboard shortcuts
- Change playback speed with the speed slider
- Enable/disable loop mode with the loop button

### Keyboard Shortcuts
The player supports extensive keyboard control:
- **Space**: Toggle play/pause
- **Ctrl + Arrow Keys**: Navigate and control volume
- **Ctrl + R**: Toggle loop mode

## File Structure

```
JUCEBox/
├── Source/
│   ├── Main.cpp              # Application entry point
│   ├── MainComponent.cpp     # Main application component
│   ├── MainComponent.h       # Main component header
│   ├── PlayerAudio.cpp       # Audio processing logic
│   ├── PlayerAudio.h         # Audio component header
│   ├── PlayerGUI.cpp         # User interface logic
│   └── PlayerGUI.h           # GUI component header
├── Builds/
│   └── VisualStudio2022/     # Visual Studio project files
├── JuceLibraryCode/          # JUCE framework code
└── JUCEBox.jucer            # JUCE project file
```

## Development

### Adding New Features
1. Audio processing: Modify `PlayerAudio.cpp`
2. User interface: Modify `PlayerGUI.cpp`
3. Keyboard shortcuts: Modify `MainComponent.cpp`

### Code Style
- Follow JUCE naming conventions
- Use RAII principles
- Prefer composition over inheritance
- Document public interfaces

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Built with the [JUCE Framework](https://juce.com/)
- Inspired by modern audio player interfaces
- Created for CS 213 Assignment 2

## Future Enhancements

- [ ] Playlist support
- [ ] Audio effects (EQ, reverb)
- [ ] Visual waveform display
- [ ] Cross-platform builds (macOS, Linux)
- [ ] Plugin support
- [ ] Recording capabilities

---

**JUCEBox** - A modern audio player built with JUCE
