/*
Developed from the Saleae Logic SampleAnalyzer by
Stephen L Reid, Reid Performance Designs
May 2020

Hexbus Analyzer - for TI CC-40/TI-74/TI-95 Hexbus/Dockbus logic analysis
*/
#ifndef HEXBUS_ANALYZER_H
#define HEXBUS_ANALYZER_H

#include <Analyzer.h>
#include "HexBusAnalyzerResults.h"
#include "HexBusSimulationDataGenerator.h"

class HexBusAnalyzerSettings;
class ANALYZER_EXPORT HexBusAnalyzer : public Analyzer2
{
public:
	HexBusAnalyzer();
	virtual ~HexBusAnalyzer();

	virtual void SetupResults();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

protected: //vars
	std::auto_ptr< HexBusAnalyzerSettings > mSettings;
	std::auto_ptr< HexBusAnalyzerResults > mResults;
	AnalyzerChannelData* mBAV;
    AnalyzerChannelData* mHSK;
    AnalyzerChannelData* mD0;
    AnalyzerChannelData* mD1;
    AnalyzerChannelData* mD2;
    AnalyzerChannelData* mD3;

	HexBusSimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//HexBusanalysis vars:

};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //HEXBUS_ANALYZER_H
