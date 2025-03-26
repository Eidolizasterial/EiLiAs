#pragma once

#include "DataStructures.h"

#include <iostream>

namespace ela {
	class NeuronConfigurator {
	private:
		float _resistance = 0;
		float _sensitivity = 0;
		uint _mode = 0;
	public:
		NeuronConfigurator() = default;
		NeuronConfigurator(
			float resistance,
			float sensitivity,
			uint mode
		);
		~NeuronConfigurator() = default;

		float get__resistance() const;
		float get__sensitivity() const;
		uint get__mode() const;

		void set__resistance(
			float resistance
		);
		void set__sensitivity(
			float sensitivity
		);
		void set__mode(
			uint mode
		);
		void info() const;
	};
}