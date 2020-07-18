/*
Developed from the Saleae Logic SampleAnalyzer by
Stephen L Reid, Reid Performance Designs
May 2020

Hexbus Analyzer - for TI CC-40/TI-74/TI-95 Hexbus/Dockbus logic analysis
*/
#include "HexBusAnalyzerSettings.h"
#include <AnalyzerHelpers.h>


HexBusAnalyzerSettings::HexBusAnalyzerSettings()
:	mBAVChannel( UNDEFINED_CHANNEL ),
	mHSKChannel( UNDEFINED_CHANNEL ),
    mD0Channel( UNDEFINED_CHANNEL ),
    mD1Channel( UNDEFINED_CHANNEL ),
    mD2Channel( UNDEFINED_CHANNEL ),
    mD3Channel( UNDEFINED_CHANNEL )   
{
	mBAVChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	mBAVChannelInterface->SetTitleAndTooltip( "BAV", "" );
	mBAVChannelInterface->SetChannel( mBAVChannel );

    mHSKChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
    mHSKChannelInterface->SetTitleAndTooltip( "HSK", "" );
    mHSKChannelInterface->SetChannel( mHSKChannel );

    mD0ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
    mD0ChannelInterface->SetTitleAndTooltip( "D0", "" );
    mD0ChannelInterface->SetChannel( mD0Channel );
    mD0ChannelInterface->SetSelectionOfNoneIsAllowed( true );

    mD1ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
    mD1ChannelInterface->SetTitleAndTooltip( "D1", "" );
    mD1ChannelInterface->SetChannel( mD1Channel );
    mD1ChannelInterface->SetSelectionOfNoneIsAllowed( true );

    mD2ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
    mD2ChannelInterface->SetTitleAndTooltip( "D2", "" );
    mD2ChannelInterface->SetChannel( mD2Channel );
    mD2ChannelInterface->SetSelectionOfNoneIsAllowed( true );

    mD3ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
    mD3ChannelInterface->SetTitleAndTooltip( "D3", "" );
    mD3ChannelInterface->SetChannel( mD3Channel );
    mD3ChannelInterface->SetSelectionOfNoneIsAllowed( true );

	AddInterface( mBAVChannelInterface.get() );
	AddInterface( mHSKChannelInterface.get() );
    AddInterface( mD0ChannelInterface.get() );
    AddInterface( mD1ChannelInterface.get() );
    AddInterface( mD2ChannelInterface.get() );
    AddInterface( mD3ChannelInterface.get() );

	AddExportOption( 0, "Export as text/csv file" );
	AddExportExtension( 0, "text", "txt" );
	AddExportExtension( 0, "csv", "csv" );

	ClearChannels();
	AddChannel( mBAVChannel, "BAV", false );
    AddChannel( mHSKChannel, "HSK", false );
    AddChannel( mD0Channel, "D0", false );
    AddChannel( mD1Channel, "D1", false );
    AddChannel( mD2Channel, "D2", false );
    AddChannel( mD3Channel, "D3", false );
}

HexBusAnalyzerSettings::~HexBusAnalyzerSettings()
{
}

bool HexBusAnalyzerSettings::SetSettingsFromInterfaces()
{
	mBAVChannel = mBAVChannelInterface->GetChannel();
    mHSKChannel = mHSKChannelInterface->GetChannel();
    mD0Channel = mD0ChannelInterface->GetChannel();
    mD1Channel = mD1ChannelInterface->GetChannel();
    mD2Channel = mD2ChannelInterface->GetChannel();
    mD3Channel = mD3ChannelInterface->GetChannel();

	ClearChannels();
	AddChannel( mBAVChannel, "BAV", true );
    AddChannel( mHSKChannel, "HSK", true );
    AddChannel( mD0Channel, "D0", true );
    AddChannel( mD1Channel, "D1", true );
    AddChannel( mD2Channel, "D2", true );
    AddChannel( mD3Channel, "D3", true );

	return true;
}

void HexBusAnalyzerSettings::UpdateInterfacesFromSettings()
{
	mBAVChannelInterface->SetChannel( mBAVChannel );
    mHSKChannelInterface->SetChannel( mHSKChannel );
    mD0ChannelInterface->SetChannel( mD0Channel );
    mD1ChannelInterface->SetChannel( mD1Channel );
    mD2ChannelInterface->SetChannel( mD2Channel );
    mD3ChannelInterface->SetChannel( mD3Channel );
}

void HexBusAnalyzerSettings::LoadSettings( const char* settings )
{
	SimpleArchive text_archive;
	text_archive.SetString( settings );

	text_archive >> mBAVChannel;
	text_archive >> mHSKChannel;
    text_archive >> mD0Channel;
    text_archive >> mD1Channel;
    text_archive >> mD2Channel;
    text_archive >> mD3Channel;

	ClearChannels();
    AddChannel( mBAVChannel, "BAV", true );
    AddChannel( mHSKChannel, "HSK", true );
    AddChannel( mD0Channel, "D0", true );
    AddChannel( mD1Channel, "D1", true );
    AddChannel( mD2Channel, "D2", true );
    AddChannel( mD3Channel, "D3", true );

	UpdateInterfacesFromSettings();
}

const char* HexBusAnalyzerSettings::SaveSettings()
{
	SimpleArchive text_archive;

	text_archive << mBAVChannel;
	text_archive << mHSKChannel;
    text_archive << mD0Channel;
    text_archive << mD1Channel;
    text_archive << mD2Channel;
    text_archive << mD3Channel;

	return SetReturnString( text_archive.GetString() );
}
