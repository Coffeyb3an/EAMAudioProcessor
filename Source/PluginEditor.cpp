#include "PluginEditor.h"
#include "PluginProcessor.h"

EAMAudioProcessorEditor::EAMAudioProcessorEditor (EAMAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    //window size
    setSize (450, 280);

    // --- Slider Setup
    auto setupVerticalSlider = [this](juce::Slider& slider, juce::AudioParameterFloat* param)
    {
        slider.setSliderStyle(juce::Slider::LinearVertical);
        slider.setRange(param->range.start, param->range.end);
        slider.setValue(param->get());
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20); // Wider textbox below
        slider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
        slider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::grey);
        slider.setColour(juce::Slider::thumbColourId, juce::Colours::lightgrey);
        slider.setColour(juce::Slider::trackColourId, juce::Colours::darkgrey);
        slider.addListener(this); // Editor will listen for value changes
        slider.setNumDecimalPlacesToDisplay(1); // Limit decimal places to 1
        addAndMakeVisible(slider);
    };

    // Setup Drive Slider
    setupVerticalSlider(driveSlider, processor.driveParam);
    // Setup Delay Time Slider
    setupVerticalSlider(delayTimeSlider, processor.delayTimeParam);
    // Setup Feedback Slider
    setupVerticalSlider(feedbackSlider, processor.feedbackParam);
    // Setup Wet/Dry Slider (using reverbParam for this)
    setupVerticalSlider(reverbSlider, processor.reverbParam);

    // Master Gain Slider - Horizontal
    masterGainSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    masterGainSlider.setRange(processor.masterGainParam->range.start, processor.masterGainParam->range.end);
    masterGainSlider.setValue(processor.masterGainParam->get());
    masterGainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 60, 20); // Text box to the right
    masterGainSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    masterGainSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::grey);
    masterGainSlider.setColour(juce::Slider::thumbColourId, juce::Colours::lightgrey);
    masterGainSlider.setColour(juce::Slider::trackColourId, juce::Colours::darkgrey);
    masterGainSlider.addListener(this); // Editor will listen for value changes
    masterGainSlider.setNumDecimalPlacesToDisplay(1); // Limit decimal places to 1
    addAndMakeVisible(masterGainSlider);
}


EAMAudioProcessorEditor::~EAMAudioProcessorEditor()
{
    driveSlider.removeListener(this);
    delayTimeSlider.removeListener(this);
    feedbackSlider.removeListener(this);
    reverbSlider.removeListener(this);
    masterGainSlider.removeListener(this);
}

void EAMAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black); // background colour
    g.setColour(juce::Colours::white); // font colour
    g.setFont(14.0f); // font size

    // vertical slider labels
    g.drawText("Drive", driveSlider.getX(), driveSlider.getY() - 20, driveSlider.getWidth(), 20, juce::Justification::centred, true);
    g.drawText("Delay", delayTimeSlider.getX(), delayTimeSlider.getY() - 20, delayTimeSlider.getWidth(), 20, juce::Justification::centred, true);
    g.drawText("Feedback", feedbackSlider.getX(), feedbackSlider.getY() - 20, feedbackSlider.getWidth(), 20, juce::Justification::centred, true);
    g.drawText("Wet/Dry", reverbSlider.getX(), reverbSlider.getY() - 20, reverbSlider.getWidth(), 20, juce::Justification::centred, true);

    // Master Gain label (above slider)
    g.drawText("Master Gain", masterGainSlider.getX(), masterGainSlider.getY() - 20, masterGainSlider.getWidth(), 20, juce::Justification::centred, true);
}

void EAMAudioProcessorEditor::resized()
{
    // Sliders layout 
    int numVerticalSliders = 4;
    int sliderMargin = 25;
    int sliderSpacing = 15;
    int totalSliderWidth = getWidth() - (2 * sliderMargin);
    int individualSliderWidth = (totalSliderWidth - (numVerticalSliders - 1) * sliderSpacing) / numVerticalSliders;
    int sliderHeight = round(getHeight() * 0.55);
    int sliderY = 40;

    // Set bounds for vertical sliders
    driveSlider.setBounds(sliderMargin, sliderY, individualSliderWidth, sliderHeight);
    delayTimeSlider.setBounds(sliderMargin + individualSliderWidth + sliderSpacing, sliderY, individualSliderWidth, sliderHeight);
    feedbackSlider.setBounds(sliderMargin + (individualSliderWidth + sliderSpacing) * 2, sliderY, individualSliderWidth, sliderHeight);
    reverbSlider.setBounds(sliderMargin + (individualSliderWidth + sliderSpacing) * 3, sliderY, individualSliderWidth, sliderHeight);

    // Master Gain slider (horizontal) - at bottom
    masterGainSlider.setBounds(sliderMargin, getHeight() - 50, getWidth() - (2 * sliderMargin), 25);
}

void EAMAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &driveSlider)
    {
        processor.driveParam->setValueNotifyingHost(slider->getValue());
    }
    else if (slider == &delayTimeSlider)
    {
        processor.delayTimeParam->setValueNotifyingHost(slider->getValue());
    }
    else if (slider == &feedbackSlider)
    {
        processor.feedbackParam->setValueNotifyingHost(slider->getValue());
    }
    else if (slider == &reverbSlider) // (WET/DRY - name change)
    {
        processor.reverbParam->setValueNotifyingHost(slider->getValue());
    }
    else if (slider == &masterGainSlider)
    {
        processor.masterGainParam->setValueNotifyingHost(slider->getValue());
    }
}
