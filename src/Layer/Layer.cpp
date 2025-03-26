#include "Layer.h"

ela::Layer::Layer(
	ela::uint neuron_count
) {
	this->_Neuron_s.resize(neuron_count);
}

std::vector<ela::Neuron>& ela::Layer::get__Neuron_s() {
	return this->_Neuron_s;
}

void ela::Layer::takeIncomingData(
	std::vector<float>& incoming_data_s
) {
	uint n_size = this->_Neuron_s.size();
	for (uint i{ 0 }; i < n_size; i++) {
		this->_Neuron_s[i].accumulate(incoming_data_s[i]);
	}
}

void ela::Layer::takeData(
	std::vector<float>& data_s
) {
	uint n_size = this->_Neuron_s.size();
	uint d_size = data_s.size();
	for (uint i{ 0 }; i < n_size; i++) {
		for (uint j{ 0 }; j < d_size; j++) {
			this->_Neuron_s[i].accumulate(data_s[j]);
		}
	}
}

std::vector<float> ela::Layer::returnOutgoingData()
{
	uint n_size = this->_Neuron_s.size();
	std::vector<float> out_data;	out_data.resize(n_size);
	for (uint i{ 0 }; i < n_size; i++) {
		out_data[i] = this->_Neuron_s[i].activation();
	}
	return out_data;
}
