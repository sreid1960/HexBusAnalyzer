#ifndef HEXBUS_SIMULATION_DATA_GENERATOR
#define HEXBUS_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>
class HexBusAnalyzerSettings;

class HexBusSimulationDataGenerator
{
public:
	HexBusSimulationDataGenerator();
	~HexBusSimulationDataGenerator();

	void Initialize( U32 simulation_sample_rate, HexBusAnalyzerSettings* settings );
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
	HexBusAnalyzerSettings* mSettings;

protected:
	void CreateHexBusByte();
	std::string mHexBusText;
	U32 mStringIndex;

	SimulationChannelDescriptor mHexBusSimulationData;

};
#endif //HEXBUS_SIMULATION_DATA_GENERATOR
