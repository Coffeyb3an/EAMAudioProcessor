# EAMAudioProcessor
Effects and Manipulation Audio Processor - Effects Plugin for DAW


A custom audio plugin developed using JUCE for MSP. This plugin features a set of effects including Overdrive, Delay, Feedback, and Wet/Dry mix, along with a Master Gain control.

## Features

* **Overdrive:** Add warmth and distortion to your audio.
* **Delay:** Control delay time and feedback for rhythmic or atmospheric effects.
* **Wet/Dry Mix:** Adjust the balance between the original (dry) and processed (wet) signal for the delay effect.
* **Master Gain:** Control the overall output volume of the plugin.
* **Intuitive GUI:** Custom-designed interface with vertical sliders for effects and a horizontal slider for master gain, featuring real-time numerical feedback.

## System Requirements

* macOS (Intel or Apple Silicon)
* [Minimum macOS version, e.g., macOS 10.13 High Sierra or later]
* An Audio Unit (AU) compatible Digital Audio Workstation (DAW) such as Logic Pro, GarageBand, Ableton Live, Cubase, etc.
* (Optional, for building from source): Xcode [Minimum Xcode version, e.g., Xcode 12 or later]

## Building from Source (for Developers)

This project is built using the JUCE framework.

1.  **Clone the repository:**
2.  **Install JUCE:** If you don't have JUCE installed, download it from [juce.com](https://juce.com/).
3.  **Open in Projucer:** Open the 'EffectsPlugin,jucer` file with the JUCE Projucer application.
4.  **Export to Xcode:** In Projucer, go to the "Exporters" section, select "Xcode (macOS)", and click "Save and Open IDE..."
5.  **Build in Xcode:**
    * In Xcode, go to 'Product > Scheme > Edit Scheme'.
    * Click 'Run' on the left.
    * Set 'Build Configuration' to 'Release'.
    * Click 'Close'.
    * Go to 'Product > Build' (or 'Cmd+B' ).

The compiled '.component' file will be located in 'YourProjectFolder/Builds/MacOSX/build/Release/YourPluginName.component'.

## Installation (for Users)

1.  **Download the plugin:** [If you plan to provide a direct download link for the .zip, put it here, otherwise, instruct them to build from source or simply clarify that this is for the built .component file].
2.  **Unzip** the downloaded file.
3.  **Copy** the 'EffectsPlugin,component` file.
4.  **Navigate to the Audio Unit plugins folder:**
    * Open Finder.
    * Go to 'Go' (menu bar) > 'Go to Folder' (or 'Shift + Cmd + G').
    * Enter: '/Library/Audio/Plug-Ins/Components/'
    * Press 'Go'.
5.  **Paste** the 'EffectsPlugin,component` file into this folder. You may be prompted for your administrator password.
6.  **Restart your DAW.** Your plugin should now appear in your DAW's plugin list (usually under "Audio Units" or "Effects"). You might need to perform a "Rescan Plugins" within your DAW's settings if it doesn't appear immediately.

## Usage

* Insert 'EffectsPlugin` onto an audio track in your DAW.
* Adjust the "Drive" slider for varying levels of harmonic distortion.
* Use the "Delay Time" and "Feedback" sliders to dial in your desired delay effect.
* The "Wet/Dry" slider controls the blend of the delayed signal with the original audio.
* Adjust the "Master Gain" for overall output volume.

## Acknowledgments

* Built with the **JUCE Framework** ([juce.com](https://juce.com/)).
