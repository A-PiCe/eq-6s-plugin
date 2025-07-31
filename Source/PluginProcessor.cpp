#include "PluginProcessor.h"
#include "PluginEditor.h"

EQ6SAudioProcessor::EQ6SAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
       valueTreeState (*this, nullptr, "Parameters", createParameterLayout())
#endif
{
}

EQ6SAudioProcessor::~EQ6SAudioProcessor()
{
}

const juce::String EQ6SAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EQ6SAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EQ6SAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EQ6SAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EQ6SAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EQ6SAudioProcessor::getNumPrograms()
{
    return 1;
}

int EQ6SAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EQ6SAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EQ6SAudioProcessor::getProgramName (int index)
{
    return {};
}

void EQ6SAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

juce::AudioProcessorValueTreeState::ParameterLayout EQ6SAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("band1_freq", "Band 1 Freq", 20.0f, 55.0f, 30.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("band1_gain", "Band 1 Gain", -8.0f, 8.0f, 0.0f));
    
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("band2_freq", "Band 2 Freq", 80.0f, 150.0f, 110.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("band2_gain", "Band 2 Gain", -8.0f, 8.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("band2_q", "Band 2 Q", 0.3f, 3.0f, 1.0f));
    
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("band3_freq", "Band 3 Freq", 350.0f, 700.0f, 500.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("band3_gain", "Band 3 Gain", -8.0f, 8.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("band3_q", "Band 3 Q", 0.3f, 3.0f, 1.0f));
    
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("band4_freq", "Band 4 Freq", 800.0f, 2000.0f, 1200.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("band4_gain", "Band 4 Gain", -8.0f, 8.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("band4_q", "Band 4 Q", 0.3f, 3.0f, 1.0f));
    
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("band5_freq", "Band 5 Freq", 3000.0f, 8000.0f, 5000.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("band5_gain", "Band 5 Gain", -8.0f, 8.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("band5_q", "Band 5 Q", 0.3f, 3.0f, 1.0f));
    
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("band6_freq", "Band 6 Freq", 8000.0f, 16000.0f, 12000.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("band6_gain", "Band 6 Gain", -8.0f, 8.0f, 0.0f));
    
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>("hpf_freq", "HPF Freq", juce::StringArray{"15 Hz", "20 Hz", "30 Hz"}, 1));
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>("lpf_freq", "LPF Freq", juce::StringArray{"16 kHz", "17 kHz", "18 kHz"}, 1));

    return { parameters.begin(), parameters.end() };
}

float EQ6SAudioProcessor::applySaturation(float inputSample, float intensity)
{
    if (intensity <= 0.0f)
        return inputSample;
    
    float normalizedInput = juce::jlimit(-1.0f, 1.0f, inputSample);
    
    float drive = 1.0f + intensity * 2.0f; // Scale intensity
    
    float output;
    if (normalizedInput >= 0.0f)
    {
        float x = normalizedInput * drive;
        output = x - (x * x * x) / 3.0f + (x * x * x * x * x) / 5.0f - (x * x * x * x * x * x * x) / 7.0f;
    }
    else
    {
        float x = normalizedInput * drive;
        output = x + (x * x * x) / 4.0f - (x * x * x * x * x) / 6.0f + (x * x * x * x * x * x * x) / 8.0f;
    }
    
    output = std::tanh(output * 0.7f);
    
    return normalizedInput + (output - normalizedInput) * intensity;
}

void EQ6SAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    currentSampleRate = sampleRate;
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    lowShelfFilter.prepare(spec);
    bellFilter1.prepare(spec);
    bellFilter2.prepare(spec);
    bellFilter3.prepare(spec);
    bellFilter4.prepare(spec);
    highShelfFilter.prepare(spec);
    highPassFilter1.prepare(spec);
    highPassFilter2.prepare(spec);
    lowPassFilter1.prepare(spec);
    lowPassFilter2.prepare(spec);
    
    updateFilters();
}

void EQ6SAudioProcessor::updateFilters()
{
    auto band1Freq = valueTreeState.getRawParameterValue("band1_freq")->load();
    auto band1Gain = juce::Decibels::decibelsToGain(valueTreeState.getRawParameterValue("band1_gain")->load());
    auto lowShelfCoeffs = juce::dsp::IIR::Coefficients<float>::makeLowShelf(currentSampleRate, band1Freq, 0.707f, band1Gain);
    lowShelfFilter.coefficients = lowShelfCoeffs;
    
    auto band2Freq = valueTreeState.getRawParameterValue("band2_freq")->load();
    auto band2Gain = juce::Decibels::decibelsToGain(valueTreeState.getRawParameterValue("band2_gain")->load());
    auto band2Q = valueTreeState.getRawParameterValue("band2_q")->load();
    auto bell1Coeffs = juce::dsp::IIR::Coefficients<float>::makePeakFilter(currentSampleRate, band2Freq, band2Q, band2Gain);
    bellFilter1.coefficients = bell1Coeffs;
    
    auto band3Freq = valueTreeState.getRawParameterValue("band3_freq")->load();
    auto band3Gain = juce::Decibels::decibelsToGain(valueTreeState.getRawParameterValue("band3_gain")->load());
    auto band3Q = valueTreeState.getRawParameterValue("band3_q")->load();
    auto bell2Coeffs = juce::dsp::IIR::Coefficients<float>::makePeakFilter(currentSampleRate, band3Freq, band3Q, band3Gain);
    bellFilter2.coefficients = bell2Coeffs;
    
    auto band4Freq = valueTreeState.getRawParameterValue("band4_freq")->load();
    auto band4Gain = juce::Decibels::decibelsToGain(valueTreeState.getRawParameterValue("band4_gain")->load());
    auto band4Q = valueTreeState.getRawParameterValue("band4_q")->load();
    auto bell3Coeffs = juce::dsp::IIR::Coefficients<float>::makePeakFilter(currentSampleRate, band4Freq, band4Q, band4Gain);
    bellFilter3.coefficients = bell3Coeffs;
    
    auto band5Freq = valueTreeState.getRawParameterValue("band5_freq")->load();
    auto band5Gain = juce::Decibels::decibelsToGain(valueTreeState.getRawParameterValue("band5_gain")->load());
    auto band5Q = valueTreeState.getRawParameterValue("band5_q")->load();
    auto bell4Coeffs = juce::dsp::IIR::Coefficients<float>::makePeakFilter(currentSampleRate, band5Freq, band5Q, band5Gain);
    bellFilter4.coefficients = bell4Coeffs;
    
    auto band6Freq = valueTreeState.getRawParameterValue("band6_freq")->load();
    auto band6Gain = juce::Decibels::decibelsToGain(valueTreeState.getRawParameterValue("band6_gain")->load());
    auto highShelfCoeffs = juce::dsp::IIR::Coefficients<float>::makeHighShelf(currentSampleRate, band6Freq, 0.707f, band6Gain);
    highShelfFilter.coefficients = highShelfCoeffs;
    
    auto hpfChoice = static_cast<int>(valueTreeState.getRawParameterValue("hpf_freq")->load());
    float hpfFreqs[] = {15.0f, 20.0f, 30.0f};
    auto hpfCoeffs = juce::dsp::IIR::Coefficients<float>::makeHighPass(currentSampleRate, hpfFreqs[hpfChoice], 0.707f);
    highPassFilter1.coefficients = hpfCoeffs;
    highPassFilter2.coefficients = hpfCoeffs;
    
    auto lpfChoice = static_cast<int>(valueTreeState.getRawParameterValue("lpf_freq")->load());
    float lpfFreqs[] = {16000.0f, 17000.0f, 18000.0f};
    auto lpfCoeffs = juce::dsp::IIR::Coefficients<float>::makeLowPass(currentSampleRate, lpfFreqs[lpfChoice], 0.707f);
    lowPassFilter1.coefficients = lpfCoeffs;
    lowPassFilter2.coefficients = lpfCoeffs;
}

void EQ6SAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EQ6SAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EQ6SAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    updateFilters();

    float saturationIntensity = 0.0f;
    for (int band = 1; band <= 6; ++band)
    {
        auto gainParam = valueTreeState.getRawParameterValue("band" + juce::String(band) + "_gain");
        if (gainParam != nullptr)
        {
            float gainValue = std::abs(*gainParam);
            saturationIntensity += gainValue / 48.0f; // Normalize (6 bands * 8dB max = 48dB)
        }
    }
    saturationIntensity = juce::jlimit(0.0f, 0.3f, saturationIntensity); // Limit max saturation

    if (saturationIntensity > 0.001f)
    {
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            auto* channelData = buffer.getWritePointer(channel);
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                channelData[sample] = applySaturation(channelData[sample], saturationIntensity);
            }
        }
    }

    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::ProcessContextReplacing<float> context (block);

    highPassFilter1.process(context);
    highPassFilter2.process(context);
    lowShelfFilter.process(context);
    bellFilter1.process(context);
    bellFilter2.process(context);
    bellFilter3.process(context);
    bellFilter4.process(context);
    highShelfFilter.process(context);
    lowPassFilter1.process(context);
    lowPassFilter2.process(context);
}

bool EQ6SAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* EQ6SAudioProcessor::createEditor()
{
    return new EQ6SAudioProcessorEditor (*this);
}

void EQ6SAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
}

void EQ6SAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EQ6SAudioProcessor();
}
