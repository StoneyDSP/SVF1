/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

//#include <JuceHeader.h>
#include "SVF.h"

//==============================================================================
/**
*/
class SVF1AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    

    //==============================================================================
    SVF1AudioProcessor();
    ~SVF1AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    using APVTS = juce::AudioProcessorValueTreeState;
    static APVTS::ParameterLayout createParameterLayout();
    APVTS apvts{ *this, nullptr, "Parameters", createParameterLayout() };

    //==============================================================================
    /** Initialises the processor. */
    void prepare();

    /** Resets the internal state variables of the processor. */
    void reset();

private:
    //==============================================================================
    /** Updates the internal state variables of the processor. */
    void update();

    //==============================================================================
    juce::dsp::ProcessSpec spec;
    //juce::dsp::StateVariableTPTFilter<float> filter;
    juce::dsp::DryWetMixer<float> mixer;
    StateVariableTPTFilter<float> filter;

    juce::AudioParameterFloat* cutoff { nullptr };
    juce::AudioParameterFloat* resonance { nullptr };
    juce::AudioParameterChoice* type { nullptr };
    juce::AudioParameterFloat* mix { nullptr };
    juce::AudioParameterBool* bypass { nullptr };
    //juce::UndoManager undoManager;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SVF1AudioProcessor)
};
