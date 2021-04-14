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

/**
 * @Author Alex Sporni
 * @Date 29.11.2020
 */

// necessary includes
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/lte-module.h"
#include "ns3/config-store.h"
#include <ns3/buildings-helper.h>


using namespace ns3;
/*
 * This example show how to configure and how Uplink Power Control works .
 */
int main(int argc, char *argv[]) {
	
	Time simTime = MilliSeconds(1050);
	uint8_t bandwidth = 75;
	double d1 = 0;
	double eNbTxPower = 30;
	/*
		I have trippled the TxPower and the bandwidth but I have not spotted any significant changes
	*/
	NS_LOG_UNCOND("Simulation start."); // simulation start will be printed in the console
    // setting up the default values for LTE power controll
	Config::SetDefault("ns3::LteHelper::UseIdealRrc", BooleanValue(false));
	Config::SetDefault("ns3::LteEnbPhy::TxPower", DoubleValue(eNbTxPower));
	Config::SetDefault("ns3::LteUePhy::TxPower", DoubleValue(90.0));
	Config::SetDefault("ns3::LteUePhy::EnableUplinkPowerControl",BooleanValue(true));
	Config::SetDefault("ns3::LteUePowerControl::ClosedLoop",BooleanValue(true));
	Config::SetDefault("ns3::LteUePowerControl::AccumulationEnabled",BooleanValue(true));
	Config::SetDefault("ns3::LteUePowerControl::Alpha", DoubleValue(1.0));
    // command line parsing
	CommandLine cmd;
	cmd.Parse(argc, argv);
	Ptr<LteHelper> lteHelper = CreateObject<LteHelper>();
	lteHelper->SetAttribute("PathlossModel", StringValue("ns3::LogDistancePropagationLossModel"));
	lteHelper->SetEnbDeviceAttribute("DlBandwidth", UintegerValue(bandwidth));
	lteHelper->SetEnbDeviceAttribute("UlBandwidth", UintegerValue(bandwidth));
	
    // Creating nodes = eNodeB and UE
    NodeContainer enbNodes;
	NodeContainer ueNodes;
	enbNodes.Create(1);
	ueNodes.Create(1);
	NodeContainer allNodes = NodeContainer(enbNodes, ueNodes);

	/* the topology is the following :
	 *
	 * eNB1 -------------------------UE
	 *                d1
	 */


    // Mobility model installation
	Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator>();
	positionAlloc->Add(Vector(0.0, 0.0, 0.0)); // eNB1
	positionAlloc->Add(Vector(d1, 0.0, 0.0)); // UE1

	MobilityHelper mobility;
	mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility.SetPositionAllocator(positionAlloc);
	mobility.Install(allNodes);

    // Creating Devices and installing them in the Nodes (eNB and UE)
	NetDeviceContainer enbDevs;
	NetDeviceContainer ueDevs;
	lteHelper->SetSchedulerType("ns3::RrFfMacScheduler");
	enbDevs = lteHelper->InstallEnbDevice(enbNodes);
	ueDevs = lteHelper->InstallUeDevice(ueNodes);
	// Attaching a UE to a eNB
    lteHelper->Attach(ueDevs, enbDevs.Get(0));

    // Activating a data radio bearer
	enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
	EpsBearer bearer(q);
	lteHelper->ActivateDataRadioBearer(ueDevs, bearer);
	lteHelper->EnableTraces();

	Ptr<RadioEnvironmentMapHelper> remHelper = CreateObject <RadioEnvironmentMapHelper > ();
	
	//remHelper->SetAttribute ("OutputFile", StringValue ("rem.out"));
	remHelper->SetAttribute ("OutputFile", StringValue ("rem2.out"));
	remHelper->SetAttribute ("XMin", DoubleValue (-400.0) );
	remHelper->SetAttribute ("XMax", DoubleValue (400.0) );
	remHelper->SetAttribute ("XRes", UintegerValue (100) );
	remHelper->SetAttribute ("YMin", DoubleValue (-300.0) );
	remHelper->SetAttribute ("YMax", DoubleValue (300.0) );
	remHelper->SetAttribute ("YRes", UintegerValue (75) );
	remHelper->SetAttribute ("Z", DoubleValue (0.0) );
	remHelper->SetAttribute ("UseDataChannel", BooleanValue ( true ));
	remHelper->SetAttribute ("RbId", IntegerValue (10));
	remHelper->Install();

	NS_LOG_UNCOND("Simulation stop.");
	Simulator::Stop(simTime);
	Simulator::Run();

	Simulator::Destroy();
	return 0;
}