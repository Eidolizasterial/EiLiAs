#include "NeuronActivators.h"

bool ela::act::default(
	float accumulate,
	float resistance
) {
	if (accumulate >= resistance) {
		return true;
	}
	else {
		return false;
	}
}

bool ela::activator(
	float accumulate,
	float resistance,
	uint mode
) {
	if (mode == 0) {
		return act::default(
			accumulate,
			resistance
			);
	}
}
