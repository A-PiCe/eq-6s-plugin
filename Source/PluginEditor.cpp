#include "PluginProcessor.h"
#include "PluginEditor.h"

EQ6SAudioProcessorEditor::EQ6SAudioProcessorEditor (EQ6SAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (900, 500);

    setupKnobStyle(band1GainSlider, true);
    setupKnobStyle(band1FreqSlider);
    addAndMakeVisible(band1GainSlider);
    addAndMakeVisible(band1FreqSlider);
    
    band1Label.setText("30Hz", juce::dontSendNotification);
    band1Label.setJustificationType(juce::Justification::centred);
    band1Label.setColour(juce::Label::textColourId, juce::Colour(0xFFF5F5DC));
    addAndMakeVisible(band1Label);

    setupKnobStyle(band2GainSlider, true);
    setupKnobStyle(band2FreqSlider);
    setupKnobStyle(band2QSlider);
    addAndMakeVisible(band2GainSlider);
    addAndMakeVisible(band2FreqSlider);
    addAndMakeVisible(band2QSlider);
    
    band2Label.setText("110Hz", juce::dontSendNotification);
    band2Label.setJustificationType(juce::Justification::centred);
    band2Label.setColour(juce::Label::textColourId, juce::Colour(0xFFF5F5DC));
    addAndMakeVisible(band2Label);

    setupKnobStyle(band3GainSlider, true);
    setupKnobStyle(band3FreqSlider);
    setupKnobStyle(band3QSlider);
    addAndMakeVisible(band3GainSlider);
    addAndMakeVisible(band3FreqSlider);
    addAndMakeVisible(band3QSlider);
    
    band3Label.setText("500Hz", juce::dontSendNotification);
    band3Label.setJustificationType(juce::Justification::centred);
    band3Label.setColour(juce::Label::textColourId, juce::Colour(0xFFF5F5DC));
    addAndMakeVisible(band3Label);

    setupKnobStyle(band4GainSlider, true);
    setupKnobStyle(band4FreqSlider);
    setupKnobStyle(band4QSlider);
    addAndMakeVisible(band4GainSlider);
    addAndMakeVisible(band4FreqSlider);
    addAndMakeVisible(band4QSlider);
    
    band4Label.setText("1.2kHz", juce::dontSendNotification);
    band4Label.setJustificationType(juce::Justification::centred);
    band4Label.setColour(juce::Label::textColourId, juce::Colour(0xFFF5F5DC));
    addAndMakeVisible(band4Label);

    setupKnobStyle(band5GainSlider, true);
    setupKnobStyle(band5FreqSlider);
    setupKnobStyle(band5QSlider);
    addAndMakeVisible(band5GainSlider);
    addAndMakeVisible(band5FreqSlider);
    addAndMakeVisible(band5QSlider);
    
    band5Label.setText("5.0kHz", juce::dontSendNotification);
    band5Label.setJustificationType(juce::Justification::centred);
    band5Label.setColour(juce::Label::textColourId, juce::Colour(0xFFF5F5DC));
    addAndMakeVisible(band5Label);

    setupKnobStyle(band6GainSlider, true);
    setupKnobStyle(band6FreqSlider);
    addAndMakeVisible(band6GainSlider);
    addAndMakeVisible(band6FreqSlider);
    
    band6Label.setText("12kHz", juce::dontSendNotification);
    band6Label.setJustificationType(juce::Justification::centred);
    band6Label.setColour(juce::Label::textColourId, juce::Colour(0xFFF5F5DC));
    addAndMakeVisible(band6Label);

    setupComboBoxStyle(hpfSelector);
    setupComboBoxStyle(lpfSelector);
    hpfSelector.addItem("15 Hz", 1);
    hpfSelector.addItem("20 Hz", 2);
    hpfSelector.addItem("30 Hz", 3);
    lpfSelector.addItem("16 kHz", 1);
    lpfSelector.addItem("17 kHz", 2);
    lpfSelector.addItem("18 kHz", 3);
    addAndMakeVisible(hpfSelector);
    addAndMakeVisible(lpfSelector);

    hpfLabel.setText("HPF", juce::dontSendNotification);
    hpfLabel.setJustificationType(juce::Justification::centred);
    hpfLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFF5F5DC));
    addAndMakeVisible(hpfLabel);

    lpfLabel.setText("LPF", juce::dontSendNotification);
    lpfLabel.setJustificationType(juce::Justification::centred);
    lpfLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFF5F5DC));
    addAndMakeVisible(lpfLabel);

    auto& params = audioProcessor.getValueTreeState();
    
    band1FreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "band1_freq", band1FreqSlider);
    band1GainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "band1_gain", band1GainSlider);
    
    band2FreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "band2_freq", band2FreqSlider);
    band2GainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "band2_gain", band2GainSlider);
    band2QAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "band2_q", band2QSlider);
    
    band3FreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "band3_freq", band3FreqSlider);
    band3GainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "band3_gain", band3GainSlider);
    band3QAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "band3_q", band3QSlider);
    
    band4FreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "band4_freq", band4FreqSlider);
    band4GainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "band4_gain", band4GainSlider);
    band4QAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "band4_q", band4QSlider);
    
    band5FreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "band5_freq", band5FreqSlider);
    band5GainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "band5_gain", band5GainSlider);
    band5QAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "band5_q", band5QSlider);
    
    band6FreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "band6_freq", band6FreqSlider);
    band6GainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(params, "band6_gain", band6GainSlider);
    
    hpfAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(params, "hpf_freq", hpfSelector);
    lpfAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(params, "lpf_freq", lpfSelector);
}

EQ6SAudioProcessorEditor::~EQ6SAudioProcessorEditor()
{
}

void EQ6SAudioProcessorEditor::setupKnobStyle(juce::Slider& slider, bool isLarge)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(0xFF8B4513));
    slider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(0xFF654321));
    slider.setColour(juce::Slider::thumbColourId, juce::Colour(0xFFD2691E));
    slider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFF5F5DC));
    slider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    
    if (isLarge)
    {
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 25);
    }
}

void EQ6SAudioProcessorEditor::setupComboBoxStyle(juce::ComboBox& comboBox)
{
    comboBox.setColour(juce::ComboBox::backgroundColourId, juce::Colour(0xFF654321));
    comboBox.setColour(juce::ComboBox::textColourId, juce::Colour(0xFFF5F5DC));
    comboBox.setColour(juce::ComboBox::outlineColourId, juce::Colour(0xFF8B4513));
    comboBox.setColour(juce::ComboBox::buttonColourId, juce::Colour(0xFF8B4513));
    comboBox.setColour(juce::ComboBox::arrowColourId, juce::Colour(0xFFF5F5DC));
}

void EQ6SAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::ColourGradient woodGradient(juce::Colour(0xFF2F1B14), 0, 0, 
                                      juce::Colour(0xFF1A0F0A), getWidth(), getHeight(), false);
    woodGradient.addColour(0.3, juce::Colour(0xFF3D2317));
    woodGradient.addColour(0.7, juce::Colour(0xFF2A1611));
    g.setGradientFill(woodGradient);
    g.fillAll();

    g.setColour(juce::Colour(0x20000000));
    for (int i = 0; i < getHeight(); i += 3)
    {
        g.drawHorizontalLine(i, 0, getWidth());
    }

    g.setColour(juce::Colour(0xFFF5F5DC));
    g.setFont(juce::Font("Arial", 28.0f, juce::Font::bold));
    g.drawText("EQ-6S", 20, 20, 200, 40, juce::Justification::left);

    g.setFont(juce::Font("Arial", 14.0f, juce::Font::italic));
    g.drawText("6-Band Harmonic Equalizer", 20, 55, 250, 20, juce::Justification::left);

    g.setColour(juce::Colour(0x40F5F5DC));
    for (int i = 1; i < 6; ++i)
    {
        int x = 120 + i * 120;
        g.drawVerticalLine(x, 100, getHeight() - 50);
    }
}

void EQ6SAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    int bandWidth = 120;
    int startX = 140;
    int centerY = getHeight() / 2;
    int largeKnobSize = 80;
    int smallKnobSize = 50;
    int spacing = 10;

    int band1X = startX;
    band1GainSlider.setBounds(band1X, centerY - 20, largeKnobSize, largeKnobSize);
    band1FreqSlider.setBounds(band1X + 15, centerY + largeKnobSize + spacing, smallKnobSize, smallKnobSize);
    band1Label.setBounds(band1X, centerY - 50, largeKnobSize, 20);

    int band2X = startX + bandWidth;
    band2GainSlider.setBounds(band2X, centerY - 20, largeKnobSize, largeKnobSize);
    band2FreqSlider.setBounds(band2X + 15, centerY + largeKnobSize + spacing, smallKnobSize, smallKnobSize);
    band2QSlider.setBounds(band2X - 15, centerY + largeKnobSize + spacing, smallKnobSize, smallKnobSize);
    band2Label.setBounds(band2X, centerY - 50, largeKnobSize, 20);

    int band3X = startX + bandWidth * 2;
    band3GainSlider.setBounds(band3X, centerY - 20, largeKnobSize, largeKnobSize);
    band3FreqSlider.setBounds(band3X + 15, centerY - largeKnobSize - spacing - smallKnobSize, smallKnobSize, smallKnobSize);
    band3QSlider.setBounds(band3X - 15, centerY - largeKnobSize - spacing - smallKnobSize, smallKnobSize, smallKnobSize);
    band3Label.setBounds(band3X, centerY - 50, largeKnobSize, 20);

    int band4X = startX + bandWidth * 3;
    band4GainSlider.setBounds(band4X, centerY - 20, largeKnobSize, largeKnobSize);
    band4FreqSlider.setBounds(band4X + 15, centerY + largeKnobSize + spacing, smallKnobSize, smallKnobSize);
    band4QSlider.setBounds(band4X - 15, centerY + largeKnobSize + spacing, smallKnobSize, smallKnobSize);
    band4Label.setBounds(band4X, centerY - 50, largeKnobSize, 20);

    int band5X = startX + bandWidth * 4;
    band5GainSlider.setBounds(band5X, centerY - 20, largeKnobSize, largeKnobSize);
    band5FreqSlider.setBounds(band5X + 15, centerY - largeKnobSize - spacing - smallKnobSize, smallKnobSize, smallKnobSize);
    band5QSlider.setBounds(band5X - 15, centerY - largeKnobSize - spacing - smallKnobSize, smallKnobSize, smallKnobSize);
    band5Label.setBounds(band5X, centerY - 50, largeKnobSize, 20);

    int band6X = startX + bandWidth * 5;
    band6GainSlider.setBounds(band6X, centerY - 20, largeKnobSize, largeKnobSize);
    band6FreqSlider.setBounds(band6X + 15, centerY + largeKnobSize + spacing, smallKnobSize, smallKnobSize);
    band6Label.setBounds(band6X, centerY - 50, largeKnobSize, 20);

    int filterX = 20;
    hpfSelector.setBounds(filterX, 120, 80, 30);
    hpfLabel.setBounds(filterX, 100, 80, 20);
    
    lpfSelector.setBounds(filterX, 180, 80, 30);
    lpfLabel.setBounds(filterX, 160, 80, 20);
}
