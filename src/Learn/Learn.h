#pragma once

#include "../Layer/Layer.h"
#include "../Network/Network.h"



namespace ela {
	struct UpdateNeuronData {
		float new_resistance = 0;
		float new_sensitivity = 0;
	};

	class Learn {
	public:
		std::vector<float> driver(
			std::vector<float>& inc_data,
			Network* __NETWORK__
		);
		std::vector<std::vector<ConfiguratorData>> layerLearn(
			std::vector<float> expected_value_s,
			std::vector<float>& inc_data,
			Network* __NETWORK__,
			float learn_balance
		);
		void fixingLearn(
			std::vector<std::vector<ConfiguratorData>> __ConfigurateData,
			Network* __NETWORK__
		);
		void learn(
			std::vector<float> expected_value_s,
			std::vector<float>& inc_data,
			Network* __NETWORK__,
			float learn_balance
		);
	};
}