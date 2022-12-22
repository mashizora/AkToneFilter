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

#include "ToneFilterFX.h"
#include "../ToneFilterConfig.h"

#include <AK/AkWwiseSDKVersion.h>

AK::IAkPlugin *CreateToneFilterFX(AK::IAkPluginMemAlloc *in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, ToneFilterFX());
}

AK::IAkPluginParam *CreateToneFilterFXParams(AK::IAkPluginMemAlloc *in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, ToneFilterFXParams());
}

AK_IMPLEMENT_PLUGIN_FACTORY(ToneFilterFX, AkPluginTypeEffect, ToneFilterConfig::CompanyID, ToneFilterConfig::PluginID)

ToneFilterFX::ToneFilterFX()
    : m_pParams(nullptr), m_pAllocator(nullptr), m_pContext(nullptr)
{
}

ToneFilterFX::~ToneFilterFX()
{
}

AKRESULT ToneFilterFX::Init(AK::IAkPluginMemAlloc *in_pAllocator, AK::IAkEffectPluginContext *in_pContext, AK::IAkPluginParam *in_pParams, AkAudioFormat &in_rFormat)
{
    m_pParams = (ToneFilterFXParams *)in_pParams;
    m_pAllocator = in_pAllocator;
    m_pContext = in_pContext;

    for (size_t i = 0; i < filterArray.size(); i++)
    {
        filterArray[i].coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(in_rFormat.uSampleRate, freqMap[i], 20);
    }

    return AK_Success;
}

AKRESULT ToneFilterFX::Term(AK::IAkPluginMemAlloc *in_pAllocator)
{
    AK_PLUGIN_DELETE(in_pAllocator, this);
    return AK_Success;
}

AKRESULT ToneFilterFX::Reset()
{
    return AK_Success;
}

AKRESULT ToneFilterFX::GetPluginInfo(AkPluginInfo &out_rPluginInfo)
{
    out_rPluginInfo.eType = AkPluginTypeEffect;
    out_rPluginInfo.bIsInPlace = true;
    out_rPluginInfo.bCanProcessObjects = false;
    out_rPluginInfo.uBuildVersion = AK_WWISESDK_VERSION_COMBINED;
    return AK_Success;
}

void ToneFilterFX::Execute(AkAudioBuffer *io_pBuffer)
{
    io_pBuffer->ZeroPadToMaxFrames();
    const auto uNumChannels = io_pBuffer->NumChannels();
    const auto uMaxFrames = io_pBuffer->MaxFrames();
    const auto mix = m_pParams->RTPC.fMix;

    for (AkUInt32 channel = 0; channel < io_pBuffer->NumChannels(); channel++)
    {
        AkSampleType *data = io_pBuffer->GetChannel(channel);
        AkSampleType *outData = static_cast<AkSampleType *>(AK_PLUGIN_ALLOC(m_pAllocator, sizeof(AkSampleType) * uMaxFrames));

        juce::dsp::AudioBlock<AkSampleType> block(&data, 1, uMaxFrames);
        for (auto &&filter : filterArray)
        {
            AkSampleType *tempData = static_cast<AkSampleType *>(AK_PLUGIN_ALLOC(m_pAllocator, sizeof(AkSampleType) * uMaxFrames));
            juce::dsp::AudioBlock<AkSampleType> tempBlock(&tempData, 1, uMaxFrames);
            juce::dsp::ProcessContextNonReplacing<AkSampleType> context(block, tempBlock);

            filter.process(context);

            AkSampleType avg = 0;
            for (size_t i = 0; i < uMaxFrames; ++i)
            {
                avg += abs(tempData[i]);
            }

            avg /= uMaxFrames;

            for (size_t i = 0; i < uMaxFrames; ++i)
            {
                tempData[i] = tempData[i] > 0.f ? avg : -avg;
            }

            for (size_t i = 0; i < uMaxFrames; ++i)
            {
                outData[i] += tempData[i];
            }
            AK_PLUGIN_FREE(m_pAllocator, tempData);
        }

        for (size_t i = 0; i < uMaxFrames; ++i)
        {
            data[i] = outData[i] * mix + data[i] * (1 - mix);
        }
        AK_PLUGIN_FREE(m_pAllocator, outData);
    }
}

AKRESULT ToneFilterFX::TimeSkip(AkUInt32 in_uFrames)
{
    return AK_DataReady;
}
