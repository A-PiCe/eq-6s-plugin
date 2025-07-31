#pragma once

#include <JuceHeader.h>

class EQ6SAudioProcessor : public juce::AudioProcessor
{
public:
    EQ6SAudioProcessor();
    ~EQ6SAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState& getValueTreeState() { return valueTreeState; }

private:
    void updateFilters();
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    float applySaturation(float inputSample, float intensity);

    juce::dsp::IIR::Filter<float> lowShelfFilter;      // Band 1: 20-55Hz Low-Shelf
    juce::dsp::IIR::Filter<float> bellFilter1;        // Band 2: 80-150Hz Bell
    juce::dsp::IIR::Filter<float> bellFilter2;        // Band 3: 350-700Hz Bell  
    juce::dsp::IIR::Filter<float> bellFilter3;        // Band 4: 800-2000Hz Bell
    juce::dsp::IIR::Filter<float> bellFilter4;        // Band 5: 3000-8000Hz Bell
    juce::dsp::IIR::Filter<float> highShelfFilter;    // Band 6: 8-16kHz High-Shelf
    
    juce::dsp::IIR::Filter<float> highPassFilter1;    // HPF Stage 1: 15/20/30 Hz (24 dB/octave)
    juce::dsp::IIR::Filter<float> highPassFilter2;    // HPF Stage 2: 15/20/30 Hz (24 dB/octave)
    juce::dsp::IIR::Filter<float> lowPassFilter1;     // LPF Stage 1: 16/17/18 kHz (24 dB/octave)
    juce::dsp::IIR::Filter<float> lowPassFilter2;     // LPF Stage 2: 16/17/18 kHz (24 dB/octave)
    
    double currentSampleRate = 44100.0;

    juce::AudioProcessorValueTreeState valueTreeState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQ6SAudioProcessor)
};
