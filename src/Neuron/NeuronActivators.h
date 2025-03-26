#pragma once

#include "NeuronConfigurator.h"
#include "DataStructures.h"
#include <cmath>


namespace ela {
	namespace act {
		bool default(
			float accumulate,
			float resistance
		);
	}
	bool activator(
		float accumulate,
		float resistance,
		uint mode
	);
}