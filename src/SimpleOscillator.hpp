inline float sin2pi_pade_05_7_6(float x)
{
    x -= 0.5f;
    return (-6.28319*x + 35.353*std::pow(x, 3) - 44.9043*std::pow(x, 5) + 16.0951*std::pow(x, 7))
	       / (1 + 0.953136*std::pow(x, 2) + 0.430238*std::pow(x, 4) + 0.0981408*std::pow(x, 6));
}

class SimpleOscillator {
    public:
        SimpleOscillator() {
            frequency = 0;
            magnitude = 1;
            phase = 0;
        }
        SimpleOscillator(float freq) : SimpleOscillator {} {
            frequency = freq;
        }
        void setFrequency(float freq)
        {
            frequency = freq;
        }
        void setMagnitude(float mag)
        {
            magnitude = mag;
        }
        void process(float sampleRate, float sampleTime)
        {
            phase += frequency * sampleTime;
            if (phase >= 1.f)
            {
                phase -= 1.f;
            }
        }
        float getReal();
        float getImaginary()
        {
            return sin2pi_pade_05_7_6(phase);
        }
        void reset() {
            phase = 0.f;
        }
    private:
        float frequency;
        float magnitude;
        float phase;
};

// template <typename T>
// T sin2pi_pade_05_7_6(T x) {
// 	x -= 0.5f;
// 	return (T(-6.28319) * x + T(35.353) * simd::pow(x, 3) - T(44.9043) * simd::pow(x, 5) + T(16.0951) * simd::pow(x, 7))
// 	       / (1 + T(0.953136) * simd::pow(x, 2) + T(0.430238) * simd::pow(x, 4) + T(0.0981408) * simd::pow(x, 6));
// }

