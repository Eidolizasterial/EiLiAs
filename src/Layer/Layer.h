#pragma once

#include "../Neuron/Neuron.h"

#include <vector>

namespace ela {
	class Layer {
	private:
		std::vector<Neuron> _Neuron_s;
	public:
		Layer() = default;
		Layer(
			uint neuron_count
		);
		~Layer() = default;

		std::vector<Neuron>& get__Neuron_s();

		void takeIncomingData(
			std::vector<float>& incoming_data_s
		);

		void takeData(
			std::vector<float>& data_s
		);

		std::vector<float> returnOutgoingData();
	};
}