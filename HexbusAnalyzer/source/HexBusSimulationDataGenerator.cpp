/*
Developed from the Saleae Logic SampleAnalyzer by
Stephen L Reid, Reid Performance Designs
May 2020

Hexbus Analyzer - for TI CC-40/TI-74/TI-95 Hexbus/Dockbus logic analysis
*/
#include "HexBusSimulationDataGenerator.h"
#include "HexBusAnalyzerSettings.h"

#include <AnalyzerHelpers.h>

HexBusSimulationDataGenerator::HexBusSimulationDataGenerator()
:	mHexBusText( "Hexbus Analyzer" ),
	mStringIndex( 0 )
{
}

HexBusSimulationDataGenerator::~HexBusSimulationDataGenerator()
{
}

void HexBusSimulationDataGenerator::Initialize( U32 simulation_sample_rate, HexBusAnalyzerSettings* settings )
{
	mSettings = settings;

	mHexBusSimulationData.SetChannel( mSettings->mBAVChannel );
	mHexBusSimulationData.SetInitialBitState( BIT_HIGH );
}

U32 HexBusSimulationDataGenerator::GenerateSimulationData( U64 largest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel )
{
	U64 adjusted_largest_sample_requested = AnalyzerHelpers::AdjustSimulationTargetSample( largest_sample_requested, sample_rate, 1000 );

	while( mHexBusSimulationData.GetCurrentSampleNumber() < adjusted_largest_sample_requested )
	{
		CreateHexBusByte();
	}

	*simulation_channel = &mHexBusSimulationData;
	return 1;
}

void HexBusSimulationDataGenerator::CreateHexBusByte()
{
	U32 samples_per_bit = 8;

	U8 byte = mHexBusText[ mStringIndex ];
	mStringIndex++;
	if( mStringIndex == mHexBusText.size() )
		mStringIndex = 0;

	//we're currenty high
	//let's move forward a little
	mHexBusSimulationData.Advance( samples_per_bit * 10 );

	mHexBusSimulationData.Transition();  //low-going edge for start bit
	mHexBusSimulationData.Advance( samples_per_bit );  //add start bit time

	U8 mask = 0x1 << 7;
	for( U32 i=0; i<8; i++ )
	{
		if( ( byte & mask ) != 0 )
			mHexBusSimulationData.TransitionIfNeeded( BIT_HIGH );
		else
			mHexBusSimulationData.TransitionIfNeeded( BIT_LOW );

		mHexBusSimulationData.Advance( samples_per_bit );
		mask = mask >> 1;
	}

	mHexBusSimulationData.TransitionIfNeeded( BIT_HIGH ); //we need to end high

	//lets pad the end a bit for the stop bit:
	mHexBusSimulationData.Advance( samples_per_bit );
}
