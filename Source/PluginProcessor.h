#pragma once

#include <JuceHeader.h>

class EAMAudioProcessor  : public juce::AudioProcessor
{
public:
    EAMAudioProcessor();
    ~EAMAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    // Declare audio parameters
    juce::AudioParameterFloat* delayTimeParam;
    juce::AudioParameterFloat* feedbackParam;
    juce::AudioParameterFloat* reverbParam; // Wet/Dry Mix
    juce::AudioParameterFloat* masterGainParam;
    juce::AudioParameterFloat* driveParam;

    juce::dsp::DelayLine<float> delayLine;
    float feedbackLevel = 0.5f;
    float delayWetLevel = 0.5f; // wet/dry mix

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EAMAudioProcessor)
};
