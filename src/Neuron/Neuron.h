#pragma once

#include "DataStructures.h"
#include "NeuronConfigurator.h"
#include "NeuronActivators.h"


namespace ela {
	class Neuron {
	private:
		float _accumulator = 0;
		NeuronConfigurator _NeuronConfigurator;
	public:
		Neuron() = default;
		Neuron(
			float resistance,
			float sensitivity,
			uint mode
		);
		~Neuron() = default;

		void accumulate(
			float impulse
		);

		float activation();

		NeuronConfigurator& Configuration();

	};
}
