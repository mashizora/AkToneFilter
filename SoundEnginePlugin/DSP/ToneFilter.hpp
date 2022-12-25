// https://www.w3.org/TR/audio-eq-cookbook/

#pragma once
#include <array>
#include <cmath>
#include <memory>
#include <memory>
#include <numbers>
#include <utility>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

#include <AK/SoundEngine/Common/AkCommonDefs.h>
#include <AK/Tools/Common/AkAssert.h>

namespace DSP
{
    /** Tone filter is a narrow band-pass filter with high Q-factor. */
    class ToneFilter
    {
    public:
        ToneFilter() : b0(1.0f), b1(0.0f), b2(0.0f), a1(0.0f), a2(0.0f), state({0, 0}) {}

        void setCoefficients(AkUInt32 sampleRate, AkReal32 frequency, AkReal32 Q)
        {
            const auto omega = 2 * (AkReal32)M_PI * (frequency / sampleRate);
            const auto sin_omega = std::sin(omega);
            const auto cos_omega = std::cos(omega);
            const auto alpha = sin_omega / (2 * Q);

            const auto scale = 1 / (1 + alpha);

            b0 = alpha * scale;
            b1 = 0;
            b2 = -alpha * scale;
            a1 = -2 * cos_omega * scale;
            a2 = (1 - alpha) * scale;
        }

        void process(AkSampleType *src, AkSampleType *dst, AkUInt16 numSamples)
        {
            for (size_t pass = 0; pass < 4; pass++)
            {
                auto lv1 = state[pass][0];
                auto lv2 = state[pass][1];
                for (size_t i = 0; i < numSamples; ++i)
                {
                    const auto input = src[i];
                    const auto output = (b0 * input) + lv1;
                    dst[i] = output;

                    lv1 = (b1 * input) - (a1 * output) + lv2;
                    lv2 = (b2 * input) - (a2 * output);
                }
                state[pass][0] = lv1;
                state[pass][1] = lv2;
            }
        }

    private:
        /** Filter coefficients. */
        AkReal32 b0, b1, b2, a1, a2;
        /** Filter state between audio buffer. */
        std::array<std::array<AkSampleType, 2>, 4> state;
    };

}
