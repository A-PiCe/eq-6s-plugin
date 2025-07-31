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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQ6SAudioProcessorEditor)
};
