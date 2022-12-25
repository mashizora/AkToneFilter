// https://www.w3.org/TR/audio-eq-cookbook/

#pragma once
#include <array>
#include <cmath>
#include <memory>
#include <memory>
#include <numbers>
#include <utility>

#include <AK/SoundEngine/Common/AkCommonDefs.h>
#include <AK/SoundEngine/Common/AkSimd.h>
#include <AK/Tools/Common/AkAssert.h>
#include <AK/DSP/AkApplyGain.h>

namespace DSP
{
    namespace Utils
    {
        AkSampleType calculateRMS(const AkSampleType *data, AkUInt16 numSamples)
        {
            if (numSamples <= 0)
            {
                return 0;
            }

            double sum = 0.0;
            for (size_t i = 0; i < numSamples; i++)
            {
                auto sample = data[i];
                sum += sample * sample;
            }

            return static_cast<AkSampleType>(std::sqrt(sum / numSamples));
        }
    }
}
