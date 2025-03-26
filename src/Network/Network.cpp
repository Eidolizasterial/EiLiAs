#include "Network.h"

ela::Network::Network(
	std::vector<Layer> __Layer_s
) {
	this->_Network = __Layer_s;
}

std::vector<ela::Layer>& ela::Network::get__Network()
{
	return this->_Network;
}


