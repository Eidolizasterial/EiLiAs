#include "Layer/Layer.h"
#include "Learn/Learn.h"

#include <iostream>
#include <ctime>


static void init(ela::Network& __Network) {
	std::vector<ela::Layer> Layer_s;
	ela::uint inc_n = 0;
	ela::uint h_layer = 0;
	ela::uint h_layer_neuron = 0;
	ela::uint out_n = 0;

	ela::uint screen_f = 0;

	std::cout << "Start Config -- " << std::endl;

	std::cout << "Incoming neuron <-- ";
	std::cin >> inc_n;
	std::cout << std::endl;

	std::cout << "Count hiden layers <-- ";
	std::cin >> h_layer;
	std::cout << std::endl;

	Layer_s.resize(2 + h_layer);
	Layer_s[0].get__Neuron_s().resize(inc_n);
	
	for (ela::uint i{ 0 }; i < h_layer; i++) {
		std::cout << "Count hiden layers " << i << " <-- ";
		std::cin >> h_layer_neuron;
		std::cout << std::endl;
		Layer_s[1 + i].get__Neuron_s().resize(h_layer_neuron);
	}

	std::cout << "Outgoing neuron <-- ";
	std::cin >> out_n;
	std::cout << std::endl;
	Layer_s[Layer_s.size() - 1].get__Neuron_s().resize(out_n);

	std::cout << "Neuron config" << std::endl;
	std::cout << "1.Manual" << std::endl;
	std::cout << "2.Random" << std::endl;
	std::cin >> screen_f;

	if (screen_f == 1) {
		float val = 0;

		std::cout << "Incoming Neuron config" << std::endl;
		for (ela::uint i{ 0 }; i < inc_n; i++) {
			std::cout << "Neuron " << i << std::endl;

			std::cout << "Set resistance <-- ";
			std::cin >> val;
			Layer_s[0].get__Neuron_s()[i].Configuration().set__resistance(val);

			std::cout << "Set sensitivity <-- ";
			std::cin >> val;
			Layer_s[0].get__Neuron_s()[i].Configuration().set__sensitivity(val);
		}
		std::cout << "Hiden Neuron config" << std::endl;
		for (ela::uint i{ 0 }; i < h_layer; i++) {
			for (ela::uint j{ 0 }; j < Layer_s[1 + i].get__Neuron_s().size(); j++) {
				std::cout << "Layer " << i << std::endl;
				std::cout << "Neuron " << j << std::endl;

				std::cout << "Set resistance <-- ";
				std::cin >> val;
				Layer_s[1 + i].get__Neuron_s()[j].Configuration().set__resistance(val);

				std::cout << "Set sensitivity <-- ";
				std::cin >> val;
				Layer_s[1 + i].get__Neuron_s()[j].Configuration().set__sensitivity(val);
			}

		}
		std::cout << "Outgoing Neuron config" << std::endl;
		for (ela::uint i{ 0 }; i < out_n; i++) {
			std::cout << "Neuron " << i << std::endl;

			std::cout << "Set resistance <-- ";
			std::cin >> val;
			Layer_s[Layer_s.size() - 1].get__Neuron_s()[i].Configuration().set__resistance(val);

			std::cout << "Set sensitivity <-- ";
			std::cin >> val;
			Layer_s[Layer_s.size() - 1].get__Neuron_s()[i].Configuration().set__sensitivity(val);
		}
	}
	else if (screen_f == 2) {
		srand(time(NULL));

		for (ela::uint i{ 0 }; i < inc_n; i++) {
			Layer_s[0].get__Neuron_s()[i].Configuration().set__resistance(rand() % 10);
			Layer_s[0].get__Neuron_s()[i].Configuration().set__sensitivity(rand() % 10);
		}
		for (ela::uint i{ 0 }; i < h_layer; i++) {
			for (ela::uint j{ 0 }; j < Layer_s[1 + i].get__Neuron_s().size(); j++) {
				Layer_s[1 + i].get__Neuron_s()[j].Configuration().set__resistance(rand() % 10);
				Layer_s[1 + i].get__Neuron_s()[j].Configuration().set__sensitivity(rand() % 10);
			}
			
		}
		for (ela::uint i{ 0 }; i < out_n; i++) {
			Layer_s[Layer_s.size() - 1].get__Neuron_s()[i].Configuration().set__resistance(rand() % 10);
			Layer_s[Layer_s.size() - 1].get__Neuron_s()[i].Configuration().set__sensitivity(rand() % 10);
		}
	}
	__Network = ela::Network(Layer_s);
}

int main() {
	ela::Network __Network__;
	ela::Learn __Learn__;
	float learn_balance = 0;
	ela::uint learn_step = 0;
	bool run = true;

	std::vector<float> incoming_data;
	std::vector<float> expected_data;

	ela::uint screen_f = 0;
	while (run) {

		if (screen_f == 0) {
			std::cout << "1.Set config" << std::endl;
			std::cout << "2.Learn" << std::endl;
			std::cout << "3.Test" << std::endl;
			std::cout << "4.Info" << std::endl;
			std::cout << "1000. Exit" << std::endl;

			std::cin >> screen_f;
		}
		else if (screen_f == 1) {
			init(__Network__);
			screen_f = 0;
		}
		else if (screen_f == 2) {
			std::cout << "Set learn balance <-- ";
			std::cin >> learn_balance;
			std::cout << std::endl;

			std::cout << "Set learn step <-- ";
			std::cin >> learn_step;
			std::cout << std::endl;

			std::cout << "Set incoming data" << std::endl;
			for (ela::uint i{ 0 }; i < __Network__.get__Network()[0].get__Neuron_s().size(); i++) {
				incoming_data.resize(__Network__.get__Network()[0].get__Neuron_s().size());
				std::cin >> incoming_data[i];
			}

			std::cout << "Set expected data" << std::endl;
			for (ela::uint i{ 0 }; i < __Network__.get__Network()[__Network__.get__Network().size() - 1].get__Neuron_s().size(); i++) {
				expected_data.resize(__Network__.get__Network()[__Network__.get__Network().size() - 1].get__Neuron_s().size());
				std::cin >> expected_data[i];
			}
			for (ela::uint i{ 0 }; i < learn_step; i++) {
				__Learn__.learn(
					expected_data,
					incoming_data,
					&__Network__,
					learn_balance
				);
			}

			screen_f = 0;
		}
		else if (screen_f == 3) {
			std::cout << "Set incoming data" << std::endl;
			for (ela::uint i{ 0 }; i < __Network__.get__Network()[0].get__Neuron_s().size(); i++) {
				incoming_data.resize(__Network__.get__Network()[0].get__Neuron_s().size());
				std::cin >> incoming_data[i];
			}

			std::vector<float> out = __Learn__.driver(
				incoming_data,
				&__Network__
			);
			std::cout << "Result" << std::endl;
			for (ela::uint i{ 0 }; i < out.size(); i++) {
				std::cout << out[i] << std::endl;
			}

			screen_f = 0;
		}
		else if (screen_f == 4) {
			for (ela::uint i{ 0 }; i < __Network__.get__Network().size(); i++) {
				for (ela::uint j{ 0 }; j < __Network__.get__Network()[i].get__Neuron_s().size(); j++) {
					__Network__.get__Network()[i].get__Neuron_s()[j].Configuration().info();
				}
			}
			screen_f = 0;
		}
		else if (screen_f == 1000) {
			run = false;
		}
		else {
			std::cin >> screen_f;
		}

		std::cout << "==============================" << std::endl;
	}

	return 0;
}