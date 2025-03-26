#pragma once

#include "../Layer/Layer.h"

namespace ela {
	class Network {
	private:
		std::vector<Layer> _Network;
	public:
		Network() = default;
		Network(std::vector<Layer> __Layer_s);
		~Network() = default;

		std::vector<Layer>& get__Network();
	};
}