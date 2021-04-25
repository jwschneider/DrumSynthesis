#include <cmath>

inline float sin2pi_pade_05_7_6(float x)
{
    x -= 0.5f;
    return (-6.28319*x + 35.353*std::pow(x, 3) - 44.9043*std::pow(x, 5) + 16.0951*std::pow(x, 7))
	       / (1 + 0.953136*std::pow(x, 2) + 0.430238*std::pow(x, 4) + 0.0981408*std::pow(x, 6));
}

// These functions are only accurate on the interval (0,1)
class Oscillator {
    public:
    static float sin(float p)
    {
        return sin2pi_pade_05_7_6(p);
    }
    static float cos(float p)
    {
        return sin(p + 0.25);
    }
    static float tri(float p)
    {
        return 4 * abs(fmod(p - 0.25, 1.f) - 0.5) - 1;
    }
    static float hilbert_tri(float p)
    {
        return -(1.f/M_PI)
            *(log(abs((p-0.5)/(p+0.5))) + 2*p*log(abs(std::pow(p, 2.f)/(std::pow(p, 2.f) - 0.25))));
    }

};