/*
Developed from the Saleae Logic SampleAnalyzer by
Stephen L Reid, Reid Performance Designs
May 2020

Hexbus Analyzer - for TI CC-40/TI-74/TI-95 Hexbus/Dockbus logic analysis
*/
#include "HexBusAnalyzerResults.h"
#include <AnalyzerHelpers.h>
#include "HexBusAnalyzer.h"
#include "HexBusAnalyzerSettings.h"
#include <iostream>
#include <fstream>

HexBusAnalyzerResults::HexBusAnalyzerResults( HexBusAnalyzer* analyzer, HexBusAnalyzerSettings* settings )
:	AnalyzerResults(),
	mSettings( settings ),
	mAnalyzer( analyzer )
{
}

HexBusAnalyzerResults::~HexBusAnalyzerResults()
{
}

void HexBusAnalyzerResults::GenerateBubbleText( U64 frame_index, Channel& channel, DisplayBase display_base )
{
	ClearResultStrings();
	Frame frame = GetFrame( frame_index );

	char number_str[128];
	AnalyzerHelpers::GetNumberString( frame.mData1, display_base, 8, number_str, 128 );
    switch ( frame.mFlags )
    {
       case DEVCOD_POS:  strcat( number_str, " (Dev#)" );      break;
       case COMMAND_POS: strcat( number_str, " (Cmd)" );       break;
       case LUNO_POS:    strcat( number_str, " (LUNO)" );      break;
       case REC_LSB_POS: strcat( number_str, " (Rec-lsb)" );   break;
       case REC_MSB_POS: strcat( number_str, " (Rec-msb)" );   break;
       case BUF_LSB_POS: strcat( number_str, " (BufLen-lsb)"); break;
       case BUF_MSB_POS: strcat( number_str, " (BufLen-msb)"); break;
       case DAT_LSB_POS: strcat( number_str, " (DatLen-lsb)"); break;
       case DAT_MSB_POS: strcat( number_str, " (DatLen-msb)"); break;
       default: break;
    }
       
	AddResultString( number_str );  
}

void HexBusAnalyzerResults::GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id )
{
	std::ofstream file_stream( file, std::ios::out );

	U64 trigger_sample = mAnalyzer->GetTriggerSample();
	U32 sample_rate = mAnalyzer->GetSampleRate();

	file_stream << "Time [s],Value" << std::endl;

	U64 num_frames = GetNumFrames();
	for( U32 i=0; i < num_frames; i++ )
	{
		Frame frame = GetFrame( i );
		
		char time_str[128];
		AnalyzerHelpers::GetTimeString( frame.mStartingSampleInclusive, trigger_sample, sample_rate, time_str, 128 );

		char number_str[128];
		AnalyzerHelpers::GetNumberString( frame.mData1, display_base, 8, number_str, 128 );

		file_stream << time_str << "," << number_str << std::endl;

		if( UpdateExportProgressAndCheckForCancel( i, num_frames ) == true )
		{
			file_stream.close();
			return;
		}
	}

	file_stream.close();
}

void HexBusAnalyzerResults::GenerateFrameTabularText( U64 frame_index, DisplayBase display_base )
{
#ifdef SUPPORTS_PROTOCOL_SEARCH
	Frame frame = GetFrame( frame_index );
	ClearTabularText();

	char number_str[128];
	AnalyzerHelpers::GetNumberString( frame.mData1, display_base, 8, number_str, 128 );
	AddTabularText( number_str );
#endif
}

void HexBusAnalyzerResults::GeneratePacketTabularText( U64 packet_id, DisplayBase display_base )
{
	//not supported

}

void HexBusAnalyzerResults::GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base )
{
	//not supported
}
