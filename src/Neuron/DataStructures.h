#pragma once


namespace ela {

	typedef unsigned int uint;

	struct IncomingData {
		uint incoming_index = 0;
		float data = 0;
	};
	struct ConfiguratorData {
		float s = 0;
		float r = 0;
	};
}
