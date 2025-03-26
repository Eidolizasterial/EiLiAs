#include "NeuronConfigurator.h"

ela::NeuronConfigurator::NeuronConfigurator(
	float resistance,
	float sensitivity,
	ela::uint mode
) {
	this->_resistance = resistance;
	this->_sensitivity = sensitivity;
	this->_mode = mode;
}

float ela::NeuronConfigurator::get__resistance() const {
	return this->_resistance;
}

float ela::NeuronConfigurator::get__sensitivity() const {
	return this->_sensitivity;
}

ela::uint ela::NeuronConfigurator::get__mode() const {
	return this->_mode;
}

void ela::NeuronConfigurator::set__resistance(
	float resistance
) {
	this->_resistance = resistance;
}

void ela::NeuronConfigurator::set__sensitivity(
	float sensitivity
) {
	this->_sensitivity = sensitivity;
}

void ela::NeuronConfigurator::set__mode(
	uint mode
) {
	this->_mode = mode;
}

void ela::NeuronConfigurator::info(
) const {
	std::cout << "R: " << this->_resistance
		<< " S:" << this->_sensitivity
		<< std::endl;
}
