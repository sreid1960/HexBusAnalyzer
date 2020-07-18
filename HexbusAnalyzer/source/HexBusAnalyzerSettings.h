/*
Developed from the Saleae Logic SampleAnalyzer by
Stephen L Reid, Reid Performance Designs
May 2020

Hexbus Analyzer - for TI CC-40/TI-74/TI-95 Hexbus/Dockbus logic analysis
*/
#ifndef HEXBUS_ANALYZER_SETTINGS
#define HEXBUS_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

#define IN_PAB_FLAG   128

#define START_PAB     0
#define DEVCOD_POS    (IN_PAB_FLAG+0)
#define COMMAND_POS   (IN_PAB_FLAG+1)
#define LUNO_POS      (IN_PAB_FLAG+2)
#define REC_LSB_POS   (IN_PAB_FLAG+3)
#define REC_MSB_POS   (IN_PAB_FLAG+4)
#define BUF_LSB_POS   (IN_PAB_FLAG+5)
#define BUF_MSB_POS   (IN_PAB_FLAG+6)
#define DAT_LSB_POS   (IN_PAB_FLAG+7)
#define DAT_MSB_POS   (IN_PAB_FLAG+8)

#define OUTSIDE_PAB 254
class HexBusAnalyzerSettings : public AnalyzerSettings
{
public:
	HexBusAnalyzerSettings();
	virtual ~HexBusAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();

	
	Channel mBAVChannel;
    Channel mHSKChannel;
    Channel mD0Channel;
    Channel mD1Channel;
    Channel mD2Channel;
    Channel mD3Channel;   

protected:
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mBAVChannelInterface;
    std::auto_ptr< AnalyzerSettingInterfaceChannel 
        >   mHSKChannelInterface;
    std::auto_ptr< AnalyzerSettingInterfaceChannel 
        >   mD0ChannelInterface;
    std::auto_ptr< AnalyzerSettingInterfaceChannel 
        >   mD1ChannelInterface;
    std::auto_ptr< AnalyzerSettingInterfaceChannel 
        >   mD2ChannelInterface;
    std::auto_ptr< AnalyzerSettingInterfaceChannel 
        >   mD3ChannelInterface;
};

#endif //HEXBUS_ANALYZER_SETTINGS
