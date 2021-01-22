#include <rack.hpp>
#include <common.hpp>

using namespace rack;

template <typename T>
static T clip(T x) {
	// return std::tanh(x);
	// Pade approximant of tanh
	x = simd::clamp(x, -3.f, 3.f);
	return x * (27 + x * x) / (27 + 9 * x * x);
}


template <typename T>
struct LadderFilter {
	T omega0;
	T resonance = 1;
	T state[4];
	T input;

	LadderFilter() {
		reset();
		setCutoff(0);
	}

	void reset() {
		for (int i = 0; i < 4; i++) {
			state[i] = 0;
		}
	}

	void setCutoff(T cutoff) {
		omega0 = 2 * T(M_PI) * cutoff;
	}

	void process(T input, T dt) {
		dsp::stepRK4(T(0), dt, state, 4, [&](T t, const T x[], T dxdt[]) {
			T inputt = crossfade(this->input, input, t / dt);
			T inputc = clip(inputt - resonance * x[3]);
			T yc0 = clip(x[0]);
			T yc1 = clip(x[1]);
			T yc2 = clip(x[2]);
			T yc3 = clip(x[3]);

			dxdt[0] = omega0 * (inputc - yc0);
			dxdt[1] = omega0 * (yc0 - yc1);
			dxdt[2] = omega0 * (yc1 - yc2);
			dxdt[3] = omega0 * (yc2 - yc3);
		});

		this->input = input;
	}

	T lowpass() {
		return state[3];
	}
	T highpass() {
		// TODO This is incorrect when `resonance > 0`. Is the math wrong?
		return clip((input - resonance * state[3]) - 4 * state[0] + 6 * state[1] - 4 * state[2] + state[3]);
	}
};