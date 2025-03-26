#include "Learn.h"

std::vector<float> ela::Learn::driver(
	std::vector<float>& inc_data,
	Network* __NETWORK__
) {
	__NETWORK__->get__Network()[0].takeIncomingData(inc_data);

	uint l_size = __NETWORK__->get__Network().size();
	for (uint i{ 1 }; i < l_size; i++) {
		__NETWORK__->get__Network()[i].takeData(__NETWORK__->get__Network()[i - 1].returnOutgoingData());
	}

	return __NETWORK__->get__Network()[l_size - 1].returnOutgoingData();
}

std::vector<std::vector<ela::ConfiguratorData>> ela::Learn::layerLearn(
	std::vector<float> expected_value_s,
	std::vector<float>& inc_data,
	Network* __NETWORK__,
	float learn_balance
) {
	uint l_size = __NETWORK__->get__Network().size();
	uint v_size = expected_value_s.size();

	std::vector<float> current_value_s;	current_value_s.resize(v_size);
	current_value_s = this->driver(
		inc_data,
		__NETWORK__
	);
	std::vector<float> diference_value_s;	diference_value_s.resize(v_size);
	for (uint i{ 0 }; i < v_size; i++) {
		diference_value_s[i] = std::abs(expected_value_s[i] - current_value_s[i]);
	}
	std::vector<std::vector<ConfiguratorData>> LearnStack;	LearnStack.resize(l_size);

	for (uint i{ 0 }; i < l_size; i++) {
		uint n_size = __NETWORK__->get__Network()[i].get__Neuron_s().size();
		LearnStack[i].resize(n_size);
		for (uint j{ 0 }; j < n_size; j++) {
			float stability_configuration_s = __NETWORK__->get__Network()[i].get__Neuron_s()[j].Configuration().get__sensitivity();
			float stability_configuration_r = __NETWORK__->get__Network()[i].get__Neuron_s()[j].Configuration().get__resistance();

			/// 0 - +, +
			/// 1 - -, -
			/// 2 - +, -
			/// 3 - -, +
			std::vector<std::vector<float>> result_difference_stack;	result_difference_stack.resize(4);
			for (uint z{ 0 }; z < 4; z++) {
				result_difference_stack[z].resize(v_size);

				if (z == 0) {
					__NETWORK__->get__Network()[i].get__Neuron_s()[j].Configuration().set__sensitivity(stability_configuration_s + learn_balance);
					__NETWORK__->get__Network()[i].get__Neuron_s()[j].Configuration().set__resistance(stability_configuration_r + learn_balance);
				}
				else if (z == 1) {
					__NETWORK__->get__Network()[i].get__Neuron_s()[j].Configuration().set__sensitivity(stability_configuration_s - learn_balance);
					__NETWORK__->get__Network()[i].get__Neuron_s()[j].Configuration().set__resistance(stability_configuration_r - learn_balance);
				}
				else if (z == 2) {
					__NETWORK__->get__Network()[i].get__Neuron_s()[j].Configuration().set__sensitivity(stability_configuration_s + learn_balance);
					__NETWORK__->get__Network()[i].get__Neuron_s()[j].Configuration().set__resistance(stability_configuration_r - learn_balance);
				}
				else if (z == 3) {
					__NETWORK__->get__Network()[i].get__Neuron_s()[j].Configuration().set__sensitivity(stability_configuration_s - learn_balance);
					__NETWORK__->get__Network()[i].get__Neuron_s()[j].Configuration().set__resistance(stability_configuration_r + learn_balance);
				}
				std::vector<float> new_current = this->driver(
					inc_data,
					__NETWORK__
				);
				for (uint zz{ 0 }; zz < v_size; zz++) {
					result_difference_stack[z][zz] = std::abs(expected_value_s[zz] - new_current[zz]);
				}
			}

			uint counter = 0;
			uint res_index = 4;
			std::vector <float> main_diference_value = diference_value_s;
			for (uint z{ 0 }; z < 4; z++) {
				for (uint zz{ 0 }; zz < v_size; zz++) {
					if (main_diference_value[zz] > result_difference_stack[z][zz]) {
						counter++;
					}
				}

				if (counter == v_size) {
					main_diference_value = result_difference_stack[z];
					res_index = z;
				}

				counter = 0;
			}

			if (res_index != 4) {
				if (res_index == 0) {
					LearnStack[i][j].s = stability_configuration_s + learn_balance;
					LearnStack[i][j].r = stability_configuration_r + learn_balance;
				}
				else if (res_index == 1) {
					LearnStack[i][j].s = stability_configuration_s - learn_balance;
					LearnStack[i][j].r = stability_configuration_r - learn_balance;
				}
				else if (res_index == 2) {
					LearnStack[i][j].s = stability_configuration_s + learn_balance;
					LearnStack[i][j].r = stability_configuration_r - learn_balance;
				}
				else if (res_index == 3) {
					LearnStack[i][j].s = stability_configuration_s - learn_balance;
					LearnStack[i][j].r = stability_configuration_r + learn_balance;
				}
			}
			else {
				LearnStack[i][j].s = stability_configuration_s;
				LearnStack[i][j].r = stability_configuration_r;
			}

			__NETWORK__->get__Network()[i].get__Neuron_s()[j].Configuration().set__sensitivity(stability_configuration_s);
			__NETWORK__->get__Network()[i].get__Neuron_s()[j].Configuration().set__resistance(stability_configuration_r);
		}
	}

	return LearnStack;
}

void ela::Learn::fixingLearn(
	std::vector<std::vector<ConfiguratorData>> __ConfigurateData,
	Network* __NETWORK__
) {
	uint l_size = __NETWORK__->get__Network().size();
	for (uint i{ 0 }; i < l_size; i++) {
		uint n_size = __NETWORK__->get__Network()[i].get__Neuron_s().size();
		for (uint j{ 0 }; j < n_size; j++) {
			__NETWORK__->get__Network()[i].get__Neuron_s()[j].Configuration().set__sensitivity(__ConfigurateData[i][j].s);
			__NETWORK__->get__Network()[i].get__Neuron_s()[j].Configuration().set__resistance(__ConfigurateData[i][j].r);
		}
	}
}

void ela::Learn::learn(
	std::vector<float> expected_value_s,
	std::vector<float>& inc_data,
	Network* __NETWORK__,
	float learn_balance
) {
	uint l_size = __NETWORK__->get__Network().size();

	std::vector<std::vector<UpdateNeuronData>> UpdateNeuronDataStack;	UpdateNeuronDataStack.resize(l_size);

	this->fixingLearn(
		this->layerLearn(
			expected_value_s,
			inc_data,
			__NETWORK__,
			learn_balance
		),
		__NETWORK__
	);
}

