/*
Developed from the Saleae Logic SampleAnalyzer by
Stephen L Reid, Reid Performance Designs
May 2020

Hexbus Analyzer - for TI CC-40/TI-74/TI-95 Hexbus/Dockbus logic analysis
*/
#include "HexBusAnalyzer.h"
#include "HexBusAnalyzerSettings.h"
#include <AnalyzerChannelData.h>

HexBusAnalyzer::HexBusAnalyzer()
:	Analyzer2(),  
	mSettings( new HexBusAnalyzerSettings() ),
	mSimulationInitilized( false )
{
	SetAnalyzerSettings( mSettings.get() );
}

HexBusAnalyzer::~HexBusAnalyzer()
{
	KillThread();
}

void HexBusAnalyzer::SetupResults()
{
	mResults.reset( new HexBusAnalyzerResults( this, mSettings.get() ) );
	SetAnalyzerResults( mResults.get() );
	mResults->AddChannelBubblesWillAppearOn( mSettings->mHSKChannel );
}

void HexBusAnalyzer::WorkerThread()
{
    U64 bav_falling;
    U64 bav_rising;
   
    mBAV = GetAnalyzerChannelData( mSettings->mBAVChannel );
	mHSK = GetAnalyzerChannelData( mSettings->mHSKChannel );
    mD0 = GetAnalyzerChannelData( mSettings->mD0Channel );
    mD1 = GetAnalyzerChannelData( mSettings->mD1Channel );
    mD2 = GetAnalyzerChannelData( mSettings->mD2Channel );
    mD3 = GetAnalyzerChannelData( mSettings->mD3Channel );
    
    U8 pabIndex = START_PAB;
    
	for( ; ; )
	{
		U8 data;
        
        data = 0;      
        
        if (mBAV->GetBitState() == BIT_HIGH)
        {
          mBAV->AdvanceToNextEdge();  // BAV falling
          bav_falling = mBAV->GetSampleNumber();
          bav_rising = mBAV->GetSampleOfNextEdge();
          pabIndex = START_PAB;
          mHSK->AdvanceToAbsPosition( bav_falling );
        }

        if ( mBAV->GetBitState() == BIT_LOW )
        {      
            U8 nibble = 0;
            U64  hsk_sample[2];
            
            while ( nibble != 2 )
            {
              mHSK->AdvanceToNextEdge(); // falling edge -- data valid
              data >>= 4;
              hsk_sample[nibble] = mHSK->GetSampleNumber();

              //let's put a dot exactly where we sample this bit:
              if (nibble)
              {
                mResults->AddMarker( hsk_sample[nibble], AnalyzerResults::Dot, mSettings->mHSKChannel );
              }
              
              if ( nibble == 0 )
              {
                if ( hsk_sample[nibble] > bav_rising )
                {
                   mBAV->AdvanceToAbsPosition( bav_rising );
                   pabIndex = START_PAB;
                   mBAV->AdvanceToNextEdge(); // falling edge of next
                   bav_falling = mBAV->GetSampleNumber();
                   bav_rising = mBAV->GetSampleOfNextEdge();
                }
              }

              mD0->AdvanceToAbsPosition( hsk_sample[nibble]+4 );
              mD1->AdvanceToAbsPosition( hsk_sample[nibble]+4 );
              mD2->AdvanceToAbsPosition( hsk_sample[nibble]+4 );
              mD3->AdvanceToAbsPosition( hsk_sample[nibble]+4 );
            
              if( mD0->GetBitState() == BIT_HIGH )
                data |= 16;
              if( mD1->GetBitState() == BIT_HIGH )
                data |= 32;
              if( mD2->GetBitState() == BIT_HIGH )
                data |= 64;
              if( mD3->GetBitState() == BIT_HIGH )
                data |= 128;

              mHSK->AdvanceToNextEdge(); // rising edge of hsk
              nibble++;
            }

            //we have a byte to save. 
            Frame frame;
            frame.mData1 = data;
            frame.mFlags = (pabIndex != OUTSIDE_PAB) ? (pabIndex | IN_PAB_FLAG) : 0;
            pabIndex++;
            if (pabIndex>8)
            {
              pabIndex = OUTSIDE_PAB;
            }
            frame.mStartingSampleInclusive = hsk_sample[0];
            frame.mEndingSampleInclusive = mHSK->GetSampleNumber();

            mResults->AddFrame( frame );
            mResults->CommitResults();
            ReportProgress( frame.mEndingSampleInclusive );
        }
        else
        {
            mBAV->AdvanceToNextEdge(); // next falling edge!
            bav_falling = mBAV->GetSampleNumber();
            bav_rising = mBAV->GetSampleOfNextEdge();
            mHSK->AdvanceToAbsPosition( bav_falling );
            pabIndex = START_PAB;
        }      
	}
}

bool HexBusAnalyzer::NeedsRerun()
{
	return false;
}

U32 HexBusAnalyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
{
	if( mSimulationInitilized == false )
	{
		mSimulationDataGenerator.Initialize( GetSimulationSampleRate(), mSettings.get() );
		mSimulationInitilized = true;
	}

	return mSimulationDataGenerator.GenerateSimulationData( minimum_sample_index, device_sample_rate, simulation_channels );
}

U32 HexBusAnalyzer::GetMinimumSampleRateHz()
{
	return 160000;
}

const char* HexBusAnalyzer::GetAnalyzerName() const
{
	return "HexBus";
}

const char* GetAnalyzerName()
{
	return "HexBus";
}

Analyzer* CreateAnalyzer()
{
	return new HexBusAnalyzer();
}

void DestroyAnalyzer( Analyzer* analyzer )
{
	delete analyzer;
}
