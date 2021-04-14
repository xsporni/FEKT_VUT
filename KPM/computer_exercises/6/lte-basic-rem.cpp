/* -*- Mode : C++; c-file - style : "gnu "; indent -tabs - mode :nil ; -*- */
/*
* Copyright (c) 2011 -2018 Centre Tecnologic de Telecomunicacions de Catalunya ( CTTC )
*
* This program is free software ; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation ;
*
* This program is distributed in the hope that it will be useful ,
* but WITHOUT ANY WARRANTY ; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE . See the
* GNU General Public License for more details .
*
* You should have received a copy of the GNU General Public License
* along with this program ; if not , write to the Free Software
* Foundation , Inc., 59 Temple Place , Suite 330 , Boston , MA 02111 -1307 USA
*
* Author : Manuel Requena <manuel . requena@cttc .es >
* Author : Pavel Masek < masekpavel@vutbr .cz >
*/

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/lte-module.h"
#include "ns3/config-store.h"
#include <ns3/buildings-helper.h>
//#include "ns3/gtk-config-store.h"

using namespace ns3;

int main (int argc , char * argv [])
{
    Time simTime = MilliSeconds(1050);
    bool config = false;

    CommandLine cmd;
    cmd.Parse(argc, argv);

    NS_LOG_UNCOND("Simulation start.");

    ConfigStore inputConfig;
    inputConfig.ConfigureDefaults();

    // Parse again so you can override default values from the command line
    cmd.Parse(argc, argv );

    Ptr<LteHelper>lteHelper = CreateObject<LteHelper>();

    lteHelper->SetAttribute("PathlossModel", StringValue("ns3::LogDistancePropagationLossModel"));
    lteHelper->SetSchedulerType("ns3::PssFfMacScheduler");
    if (config)
    {
        Config::SetDefault("ns3::LteSpectrumPhy::CtrlErrorModelEnabled", BooleanValue(false));
        Config::SetDefault("ns3::LteSpectrumPhy::DataErrorModelEnabled", BooleanValue(false));
    }

    // Config the MIMO parameters
    // Config :: SetDefault (" ns3 :: LteEnbRrc :: DefaultTransmissionMode ", UintegerValue(0)); // SISO
    // Config :: SetDefault (" ns3 :: LteEnbRrc :: DefaultTransmissionMode ", UintegerValue(1)); // MIMO Tx diversity (1 layer )
    // Config :: SetDefault (" ns3 :: LteEnbRrc :: DefaultTransmissionMode ", UintegerValue(2)); // MIMO Spatial Multiplexity (2 layers )

    // Uncomment to enable logging
    // lteHelper -> EnableLogComponents ();

    // Create Nodes : eNodeB and UE
    NodeContainer enbNodes;
    NodeContainer ueNodes;
    enbNodes.Create(1);
    ueNodes.Create(1);

    // Install Mobility Model
    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(enbNodes);
    BuildingsHelper::Install(enbNodes);
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(ueNodes);

    BuildingsHelper::Install(ueNodes);

    // Create Devices and install them in the Nodes (eNB and UE)
    NetDeviceContainer enbDevs;
    NetDeviceContainer ueDevs;

    // Default scheduler is PF , uncomment to use RR
    // lteHelper -> SetSchedulerType (" ns3 :: RrFfMacScheduler ");

    enbDevs = lteHelper->InstallEnbDevice(enbNodes);
    ueDevs = lteHelper->InstallUeDevice(ueNodes);

    // Attach a UE to a eNB
    lteHelper->Attach(ueDevs, enbDevs.Get(0));

    // Activate a data radio bearer
    enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
    EpsBearer bearer(q);
    lteHelper-> ActivateDataRadioBearer(ueDevs, bearer);
    lteHelper-> EnableTraces();

    lteHelper->SetEnbAntennaModelType("ns3::CosineAntennaModel");
    lteHelper->SetEnbAntennaModelAttribute("Orientation", DoubleValue(0));
    lteHelper->SetEnbAntennaModelAttribute("Beamwidth", DoubleValue(60));
    lteHelper->SetEnbAntennaModelAttribute("MaxGain", DoubleValue(0.0));

    NS_LOG_UNCOND ("Simulation temp 1.");
    uint8_t rnti = 1;
    Ptr<LteEnbNetDevice> enbNetDev = enbDevs.Get(0)->GetObject<LteEnbNetDevice>();
    PointerValue ptrval;
    enbNetDev->GetCcMap()[0]->GetAttribute("FfMacScheduler", ptrval);
    NS_LOG_UNCOND("Simulation temp 2.");
    Ptr<RrFfMacScheduler> rrsched = ptrval.Get<RrFfMacScheduler>();
    Simulator::Schedule(Seconds(0.2), &RrFfMacScheduler::TransmissionModeConfigurationUpdate, rrsched, rnti, 1);

    Ptr<RadioEnvironmentMapHelper> remHelper = CreateObject <RadioEnvironmentMapHelper>();
    remHelper->SetAttribute(" ChannelPath ", StringValue("/ ChannelList /0"));
    remHelper->SetAttribute(" OutputFile ", StringValue("rem.out"));
    remHelper->SetAttribute(" XMin ", DoubleValue(-400.0));
    remHelper->SetAttribute(" XMax ", DoubleValue(400.0));
    remHelper->SetAttribute(" XRes ", UintegerValue(100));
    remHelper->SetAttribute(" YMin ", DoubleValue(-300.0));
    remHelper->SetAttribute(" YMax ", DoubleValue (300.0));
    remHelper->SetAttribute(" YRes ", UintegerValue (75));
    remHelper->SetAttribute("Z", DoubleValue(0.0));
    remHelper->SetAttribute("UseDataChannel ", BooleanValue(true));
    remHelper->SetAttribute("RbId ", IntegerValue(10));
    remHelper->Install();
    

    NS_LOG_UNCOND ("Simulation stop.");
    Simulator::Stop(simTime);
    Simulator::Run();

    // GtkConfigStore config ;
    // config . ConfigureAttributes ();

    Simulator::Destroy();
    return 0;
}