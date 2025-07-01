#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class EAMAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                 public juce::Slider::Listener
{
public:
    EAMAudioProcessorEditor (EAMAudioProcessor&);
    ~EAMAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;


    void sliderValueChanged (juce::Slider* slider) override;

private:
    EAMAudioProcessor& processor;

    // Declared sliders as member var
    juce::Slider driveSlider;
    juce::Slider delayTimeSlider;
    juce::Slider feedbackSlider;
    juce::Slider reverbSlider;     // Wet/Dry
    juce::Slider masterGainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EAMAudioProcessorEditor)
};
