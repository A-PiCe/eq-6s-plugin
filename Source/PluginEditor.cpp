#include "PluginProcessor.h"
#include "PluginEditor.h"

EQ6SAudioProcessorEditor::EQ6SAudioProcessorEditor (EQ6SAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (800, 400);
}

EQ6SAudioProcessorEditor::~EQ6SAudioProcessorEditor()
{
}

void EQ6SAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("EQ-6S Audio Plugin", getLocalBounds(), juce::Justification::centred, 1);
}

void EQ6SAudioProcessorEditor::resized()
{
}
