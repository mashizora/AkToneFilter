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

    std::array<juce::dsp::IIR::Filter<AkSampleType>, 48> filterArray;
    std::array<std::tuple<float, float>, 48> filterParams{
        std::tuple(19.5f, 10.0f),
        std::tuple(21.8f, 10.0f),
        std::tuple(24.5f, 10.0f),
        std::tuple(27.5f, 10.0f),
        std::tuple(30.9f, 10.0f),
        std::tuple(34.7f, 10.0f),
        std::tuple(38.9f, 10.0f),
        std::tuple(49.0f, 10.0f),
        std::tuple(55.0f, 10.0f),
        std::tuple(61.7f, 10.0f),
        std::tuple(69.3f, 10.0f),
        std::tuple(77.8f, 10.0f),
        std::tuple(87.3f, 10.0f),
        std::tuple(98.0f, 10.0f),
        std::tuple(110.0f, 10.0f),
        std::tuple(123.5f, 10.0f),
        std::tuple(138.6f, 10.0f),
        std::tuple(155.6f, 10.0f),
        std::tuple(174.6f, 10.0f),
        std::tuple(196.0f, 10.0f),
        std::tuple(220.0f, 10.0f),
        std::tuple(245.0f, 10.0f),
        std::tuple(277.2f, 10.0f),
        std::tuple(311.1f, 10.0f),
        std::tuple(349.2f, 10.0f),
        std::tuple(392.0f, 10.0f),
        std::tuple(440.0f, 10.0f),
        std::tuple(493.9f, 10.0f),
        std::tuple(554.4f, 10.0f),
        std::tuple(662.3f, 10.0f),
        std::tuple(698.5f, 10.0f),
        std::tuple(784.0f, 10.0f),
        std::tuple(880.0f, 10.0f),
        std::tuple(987.8f, 10.0f),
        std::tuple(1108.7f, 10.0f),
        std::tuple(1244.5f, 10.0f),
        std::tuple(1396.9f, 10.0f),
        std::tuple(1568.0f, 10.0f),
        std::tuple(1760.0f, 10.0f),
        std::tuple(1975.5f, 10.0f),
        std::tuple(2217.5f, 10.0f),
        std::tuple(2489.0f, 5.0f),
        std::tuple(2793.8f, 5.0f),
        std::tuple(3136.0f, 5.0f),
        std::tuple(3520.0f, 5.0f),
        std::tuple(3951.0f, 5.0f),
        std::tuple(4434.9f, 5.0f),
        std::tuple(4978.0f, 5.0f),

    };
};
#endif // ToneFilterFX_H
