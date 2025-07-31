#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class EQ6SAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    EQ6SAudioProcessorEditor (EQ6SAudioProcessor&);
    ~EQ6SAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    EQ6SAudioProcessor& audioProcessor;

    // EQ Band Controls (6 bands)
    juce::Slider band1FreqSlider, band1GainSlider;
    juce::Slider band2FreqSlider, band2GainSlider, band2QSlider;
    juce::Slider band3FreqSlider, band3GainSlider, band3QSlider;
    juce::Slider band4FreqSlider, band4GainSlider, band4QSlider;
    juce::Slider band5FreqSlider, band5GainSlider, band5QSlider;
    juce::Slider band6FreqSlider, band6GainSlider;

    // Cut Filter Controls
    juce::ComboBox hpfSelector, lpfSelector;

    // Attachments for parameter binding
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band1FreqAttachment, band1GainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band2FreqAttachment, band2GainAttachment, band2QAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band3FreqAttachment, band3GainAttachment, band3QAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band4FreqAttachment, band4GainAttachment, band4QAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band5FreqAttachment, band5GainAttachment, band5QAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band6FreqAttachment, band6GainAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> hpfAttachment, lpfAttachment;

    // Labels
    juce::Label band1Label, band2Label, band3Label, band4Label, band5Label, band6Label;
    juce::Label hpfLabel, lpfLabel;

    void setupKnobStyle(juce::Slider& slider, bool isLarge = false);
    void setupComboBoxStyle(juce::ComboBox& comboBox);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQ6SAudioProcessorEditor)
};
