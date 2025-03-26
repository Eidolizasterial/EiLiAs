#include "Neuron.h"

ela::Neuron::Neuron(
	float resistance,
	float sensitivity,
	uint mode
) {
	this->_NeuronConfigurator = NeuronConfigurator(
		resistance,
		sensitivity,
		mode
	);
}

void ela::Neuron::accumulate(
	float impulse
) {
	this->_accumulator += impulse * this->_NeuronConfigurator.get__sensitivity();
}

float ela::Neuron::activation() {
	if (activator(
		this->_accumulator,
		this->_NeuronConfigurator.get__resistance(),
		this->_NeuronConfigurator.get__mode()
		)
	) {
		float impulse = this->_accumulator; this->_accumulator = 0;
		return impulse;
	}
	else {
		this->_accumulator = 0;
		return 0;
	}
}

ela::NeuronConfigurator& ela::Neuron::Configuration() {
	return this->_NeuronConfigurator;
}
