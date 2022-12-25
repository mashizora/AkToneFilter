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

#include "ToneFilterFXParams.h"
#include "DSP/ToneFilter.hpp"
#include "DSP/Utils.hpp"
#include <vector>

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

    using FilterArray = std::array<DSP::ToneFilter, 48>;
    std::vector<FilterArray> filterMatrix;
    std::array<AkReal32, 48> freqList{
        185.00f,
        196.00f,
        207.65f,
        220.00f,
        233.08f,
        246.94f,
        261.63f,
        277.18f,
        293.66f,
        311.13f,
        329.63f,
        349.23f,
        369.99f,
        392.00f,
        415.30f,
        440.00f,
        466.16f,
        493.88f,
        523.25f,
        554.37f,
        587.33f,
        622.25f,
        659.25f,
        698.46f,
        739.99f,
        783.99f,
        830.61f,
        880.00f,
        932.33f,
        987.77f,
        1046.50f,
        1108.73f,
        1174.66f,
        1244.51f,
        1318.51f,
        1396.91f,
        1479.98f,
        1567.98f,
        1661.22f,
        1760.00f,
        1864.66f,
        1975.53f,
        2093.00f,
        2217.46f,
        2349.32f,
        2489.02f,
        2637.02f,
        2793.83f,
    };
};
#endif // ToneFilterFX_H
