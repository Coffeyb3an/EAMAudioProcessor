#include "PluginProcessor.h"
#include "PluginEditor.h"

EAMAudioProcessor::EAMAudioProcessor()
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo()).withOutput("Output", juce::AudioChannelSet::stereo()))
{
    addParameter(delayTimeParam = new juce::AudioParameterFloat("delayTime", "Delay Time", 0.1f, 2000.0f, 500.0f));  // Delay time in ms
    addParameter(feedbackParam = new juce::AudioParameterFloat("feedback", "Feedback", 0.0f, 0.9f, 0.5f)); // Feedback amount
    addParameter(reverbParam = new juce::AudioParameterFloat("wetDry", "Wet/Dry", 0.0f, 1.0f, 0.5f)); // Wet/Dry Reverb mix
    addParameter(masterGainParam = new juce::AudioParameterFloat("masterGain", "Master Gain", 0.0f, 1.0f, 0.8f)); // Master Output Gain
    addParameter(driveParam = new juce::AudioParameterFloat("drive", "Drive", 0.0f, 1.0f, 0.0f)); // Range 0.0 - 1.0 for intensity
}

EAMAudioProcessor::~EAMAudioProcessor() {}

void EAMAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getMainBusNumOutputChannels();
    delayLine.prepare(spec);
    delayLine.setDelay(static_cast<float>(delayTimeParam->get()));
}

void EAMAudioProcessor::releaseResources()
{
    delayLine.reset();
}

void EAMAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused(midiMessages);
    juce::ScopedNoDenormals noDenormals;

    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    delayLine.setDelay(static_cast<float>(delayTimeParam->get()));
    feedbackLevel = feedbackParam->get();
    delayWetLevel = reverbParam->get(); // reverb parameter for wet/dry (name changed)

    float driveAmount = driveParam->get();

    juce::AudioBuffer<float> originalInputBuffer;
    originalInputBuffer.makeCopyOf(buffer);

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        const float* inputChannelData = originalInputBuffer.getReadPointer(channel);
        float* outputChannelData = buffer.getWritePointer(channel);

        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            float currentSample = inputChannelData[i];
            float processedDrySample;

            if (juce::approximatelyEqual (driveAmount, 0.0f))
            {
                processedDrySample = currentSample;
            }
            else
            {
                float driveMultiplier = 1.0f + (driveAmount * 10.0f);
                processedDrySample = std::tanh(currentSample * driveMultiplier);
            }

            float delayedSample = delayLine.popSample(channel);
            float inputToDelay = processedDrySample + (delayedSample * feedbackLevel);
            delayLine.pushSample(channel, inputToDelay);

            outputChannelData[i] = processedDrySample * (1.0f - delayWetLevel) + delayedSample * delayWetLevel;
        }
    }

    buffer.applyGain(masterGainParam->get());
}

juce::AudioProcessorEditor* EAMAudioProcessor::createEditor()
{
    return new EAMAudioProcessorEditor (*this);
}

bool EAMAudioProcessor::hasEditor() const
{
    return true;
}

const juce::String EAMAudioProcessor::getName() const
{
    return "EAMAudioProcessor";
}

bool EAMAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo() && layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo();
}

void EAMAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    juce::ignoreUnused(destData);
}

void EAMAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    juce::ignoreUnused(data, sizeInBytes); 
}

bool EAMAudioProcessor::acceptsMidi() const
{
    return false;
}

bool EAMAudioProcessor::producesMidi() const
{
    return false;
}

double EAMAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EAMAudioProcessor::getNumPrograms()
{
    return 1;
}

int EAMAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EAMAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused(index);
}

const juce::String EAMAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused(index);
    return "Default";
}

void EAMAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused(index, newName);
}
