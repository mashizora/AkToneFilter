/*******************************************************************************
The content of this file includes portions of the AUDIOKINETIC Wwise Technology
released in source code form as part of the SDK installer package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use this file in accordance with the end user license agreement provided
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

Apache License Usage

Alternatively, this file may be used under the Apache License, Version 2.0 (the
"Apache License"); you may not use this file except in compliance with the
Apache License. You may obtain a copy of the Apache License at
http://www.apache.org/licenses/LICENSE-2.0.

Unless required by applicable law or agreed to in writing, software distributed
under the Apache License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
OR CONDITIONS OF ANY KIND, either express or implied. See the Apache License for
the specific language governing permissions and limitations under the License.

  Copyright (c) 2022 Audiokinetic Inc.
*******************************************************************************/

#ifndef ToneFilterFX_H
#define ToneFilterFX_H

#include "../JuceModules/JuceHeader.h"
#include "ToneFilterFXParams.h"

/// See https://www.audiokinetic.com/library/edge/?source=SDK&id=soundengine__plugins__effects.html
/// for the documentation about effect plug-ins
class ToneFilterFX
    : public AK::IAkInPlaceEffectPlugin
{
public:
    ToneFilterFX();
    ~ToneFilterFX();

    /// Plug-in initialization.
    /// Prepares the plug-in for data processing, allocates memory and sets up the initial conditions.
    AKRESULT Init(AK::IAkPluginMemAlloc *in_pAllocator, AK::IAkEffectPluginContext *in_pContext, AK::IAkPluginParam *in_pParams, AkAudioFormat &in_rFormat) override;

    /// Release the resources upon termination of the plug-in.
    AKRESULT Term(AK::IAkPluginMemAlloc *in_pAllocator) override;

    /// The reset action should perform any actions required to reinitialize the
    /// state of the plug-in to its original state (e.g. after Init() or on effect bypass).
    AKRESULT Reset() override;

    /// Plug-in information query mechanism used when the sound engine requires
    /// information about the plug-in to determine its behavior.
    AKRESULT GetPluginInfo(AkPluginInfo &out_rPluginInfo) override;

    /// Effect plug-in DSP execution.
    void Execute(AkAudioBuffer *io_pBuffer) override;

    /// Skips execution of some frames, when the voice is virtual playing from elapsed time.
    /// This can be used to simulate processing that would have taken place (e.g. update internal state).
    /// Return AK_DataReady or AK_NoMoreData, depending if there would be audio output or not at that point.
    AKRESULT TimeSkip(AkUInt32 in_uFrames) override;

private:
    ToneFilterFXParams *m_pParams;
    AK::IAkPluginMemAlloc *m_pAllocator;
    AK::IAkEffectPluginContext *m_pContext;

    using Filter = juce::dsp::IIR::Filter<AkSampleType>;
    std::array<juce::dsp::ProcessorChain<Filter, Filter, Filter, Filter>, 48> filterArray;
    std::array<std::tuple<float, float>, 48> filterParams{
        // std::tuple(110.00f, 80.f),
        // std::tuple(116.54f, 80.f),
        // std::tuple(123.47f, 80.f),
        // std::tuple(130.81f, 80.f),
        // std::tuple(138.59f, 80.f),
        // std::tuple(146.83f, 80.f),
        // std::tuple(155.56f, 80.f),
        // std::tuple(164.81f, 80.f),
        // std::tuple(174.61f, 80.f),
        // std::tuple(185.00f, 80.f),
        // std::tuple(196.00f, 80.f),
        // std::tuple(207.65f, 80.f),
        std::tuple(220.00f, 60.f),
        std::tuple(233.08f, 60.f),
        std::tuple(246.94f, 60.f),
        std::tuple(261.63f, 60.f),
        std::tuple(277.18f, 60.f),
        std::tuple(293.66f, 60.f),
        std::tuple(311.13f, 60.f),
        std::tuple(329.63f, 60.f),
        std::tuple(349.23f, 60.f),
        std::tuple(369.99f, 60.f),
        std::tuple(392.00f, 60.f),
        std::tuple(415.30f, 60.f),
        std::tuple(440.00f, 50.f),
        std::tuple(466.16f, 50.f),
        std::tuple(493.88f, 50.f),
        std::tuple(523.25f, 50.f),
        std::tuple(554.37f, 50.f),
        std::tuple(587.33f, 50.f),
        std::tuple(622.25f, 50.f),
        std::tuple(659.25f, 50.f),
        std::tuple(698.46f, 50.f),
        std::tuple(739.99f, 50.f),
        std::tuple(783.99f, 50.f),
        std::tuple(830.61f, 50.f),
        std::tuple(880.00f, 40.f),
        std::tuple(932.33f, 40.f),
        std::tuple(987.77f, 40.f),
        std::tuple(1046.50f, 40.f),
        std::tuple(1108.73f, 40.f),
        std::tuple(1174.66f, 40.f),
        std::tuple(1244.51f, 40.f),
        std::tuple(1318.51f, 40.f),
        std::tuple(1396.91f, 40.f),
        std::tuple(1479.98f, 40.f),
        std::tuple(1567.98f, 40.f),
        std::tuple(1661.22f, 40.f),
        std::tuple(1760.00f, 30.f),
        std::tuple(1864.66f, 30.f),
        std::tuple(1975.53f, 30.f),
        std::tuple(2093.00f, 30.f),
        std::tuple(2217.46f, 30.f),
        std::tuple(2349.32f, 30.f),
        std::tuple(2489.02f, 30.f),
        std::tuple(2637.02f, 30.f),
        std::tuple(2793.83f, 30.f),
        std::tuple(2959.96f, 30.f),
        std::tuple(3135.96f, 30.f),
        std::tuple(3322.44f, 30.f),
        // std::tuple(3520.00f, 20.f),
        // std::tuple(3729.31f, 20.f),
        // std::tuple(3951.07f, 20.f),
        // std::tuple(4186.01f, 20.f),
        // std::tuple(4434.92f, 20.f),
        // std::tuple(4698.63f, 20.f),
        // std::tuple(4978.03f, 20.f),
        // std::tuple(5274.04f, 20.f),
        // std::tuple(5587.65f, 20.f),
        // std::tuple(5919.91f, 20.f),
        // std::tuple(6271.93f, 20.f),
        // std::tuple(6644.88f, 20.f),
    };
};
#endif // ToneFilterFX_H
