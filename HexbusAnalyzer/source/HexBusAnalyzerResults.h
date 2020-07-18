/*
 Developed from the Saleae Logic SampleAnalyzer by
 Stephen L Reid, Reid Performance Designs
 May 2020

 Hexbus Analyzer - for TI CC-40/TI-74/TI-95 Hexbus/Dockbus logic analysis
 */
#ifndef HEXBUS_ANALYZER_RESULTS
#define HEXBUS_ANALYZER_RESULTS

#include <AnalyzerResults.h>

class HexBusAnalyzer;
class HexBusAnalyzerSettings;

class HexBusAnalyzerResults : public AnalyzerResults
{
public:
	HexBusAnalyzerResults( HexBusAnalyzer* analyzer, HexBusAnalyzerSettings* settings );
	virtual ~HexBusAnalyzerResults();

	virtual void GenerateBubbleText( U64 frame_index, Channel& channel, DisplayBase display_base );
	virtual void GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id );

	virtual void GenerateFrameTabularText(U64 frame_index, DisplayBase display_base );
	virtual void GeneratePacketTabularText( U64 packet_id, DisplayBase display_base );
	virtual void GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base );

protected: //functions

protected:  //vars
	HexBusAnalyzerSettings* mSettings;
	HexBusAnalyzer* mAnalyzer;
};

#endif //HEXBUS_ANALYZER_RESULTS
