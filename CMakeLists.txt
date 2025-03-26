cmake_minimum_required(VERSION 4.0.0)

project(EiLiAs)

add_executable(${PROJECT_NAME} src/main.cpp

src/Neuron/Neuron.h src/Neuron/Neuron.cpp 
src/Neuron/NeuronConfigurator.h src/Neuron/NeuronConfigurator.cpp
src/Neuron/NeuronActivators.h src/Neuron/NeuronActivators.cpp  
src/Neuron/DataStructures.h

src/Layer/Layer.h src/Layer/Layer.cpp 

src/Network/Network.h src/Network/Network.cpp 

src/Learn/Learn.h src/Learn/Learn.cpp 
)