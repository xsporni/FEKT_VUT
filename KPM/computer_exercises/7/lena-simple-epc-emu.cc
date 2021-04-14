/* -*- Mode : C++; c-file - style : "gnu "; indent -tabs - mode :nil ; -*- */
/*
* Copyright (c) 2011 , 2013 Centre Tecnologic de Telecomunicacions de Catalunya ( CTTC )
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
* Author : Jaume Nin <jaume . nin@cttc .cat >
* Nicola Baldo <nbaldo@cttc .cat >
* Pavel Masek < masekpavel@vutbr .cz >
*/

/**
 * @Author Alex Sporni
 * @Date 29.11.2020
 */

// necessary includes
#include "ns3/lte-helper.h"
#include "ns3/epc-helper.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/lte-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-helper.h"
#include <ns3/config-store-module.h>


using namespace ns3; //ns3 namespace declaration

/* Simple simulation program using the emulated EPC . For the LTE radio part ,
it simulates a simple linear topology with a fixed number of eNBs spaced
at equal distance , and a fixed number of UEs per each eNB , located at
the same position of the eNB. For the EPC , it uses EmuEpcHelper to
realize the S1 -U connection via a real link .
*/

// definition of logging component with the name EPC-EMU
NS_LOG_COMPONENT_DEFINE ("EPC-EMU");

int main (int argc , char * argv [])
{
	// variable initialization
	uint16_t nEnbs = 1;
	uint16_t nUesPerEnb = 1;
	double simTime = 10.1;
	double distance = 1000.0;
	double interPacketInterval = 1000;

	// Command line arguments
	CommandLine cmd;

     // Command line argument parsing
	cmd.AddValue ("nEnbs", " Number of eNBs ", nEnbs);
	cmd.AddValue ("nUesPerEnb", " Number of UEs per eNB", nUesPerEnb);
	cmd.AddValue ("simTime", " Total duration of the simulation [s])", simTime);
	cmd.AddValue ("distance", " Distance between eNBs [m]", distance);
	cmd.AddValue ("interPacketInterval", " Inter packet interval [ms])",interPacketInterval);
	cmd.Parse(argc , argv );// parsovanie parametrov z cmd


	Config::SetDefault("ns3::LteSpectrumPhy::CtrlErrorModelEnabled",BooleanValue (false));
	Config::SetDefault("ns3::LteSpectrumPhy::DataErrorModelEnabled",BooleanValue (false));
	GlobalValue::Bind("ChecksumEnabled", BooleanValue (true));

	ConfigStore inputConfig;
	inputConfig.ConfigureDefaults();

	// Parse again so you can override default values from the command line
	cmd.Parse(argc, argv );

    // Creating the helper objects and initialize them
	Ptr<LteHelper> lteHelper = CreateObject<LteHelper>();
	Ptr<EmuEpcHelper> epcHelper = CreateObject<EmuEpcHelper>();
	lteHelper->SetEpcHelper( epcHelper );
	epcHelper->Initialize();
    // Creating the packet gatewey with the helper object
	Ptr<Node> pgw = epcHelper->GetPgwNode();

    // Creating a single RemoteHost and initialization of IP stack
	NodeContainer remoteHostContainer;
	remoteHostContainer.Create(1);
	Ptr<Node> remoteHost = remoteHostContainer.Get(0);
	InternetStackHelper internet;
	internet.Install(remoteHostContainer);

    // Create the p2p connection and setting up the link parameters
	PointToPointHelper p2ph;
	p2ph.SetDeviceAttribute ("DataRate", DataRateValue ( DataRate ("100Gb/s")));
	p2ph.SetDeviceAttribute ("Mtu", UintegerValue (1500));
	p2ph.SetChannelAttribute ("Delay", TimeValue ( Seconds (0.010) ));
	NetDeviceContainer internetDevices = p2ph.Install (pgw , remoteHost);
	Ipv4AddressHelper ipv4h;
	ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
	Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign( internetDevices );
	Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress(1);
    // setting up the routing and assigning the IP adress
	Ipv4StaticRoutingHelper ipv4RoutingHelper;
	Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting ( remoteHost->GetObject<Ipv4>());
	remoteHostStaticRouting->AddNetworkRouteTo(Ipv4Address ("7.0.0.0"),Ipv4Mask("255.0.0.0"), 1);

     // creating ue and enb nodes
	NodeContainer ueNodes;
	NodeContainer enbNodes;
	enbNodes.Create(nEnbs);
	ueNodes.Create(nEnbs * nUesPerEnb);

    // Install Mobility Model
	Ptr<ListPositionAllocator> positionAlloc = CreateObject <ListPositionAllocator>();
	for ( uint16_t i = 0; i < nEnbs; i++){
		positionAlloc->Add ( Vector (distance * i, 0, 0));
	}

	MobilityHelper mobility;
	mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
	mobility.SetPositionAllocator (positionAlloc);
	mobility.Install (enbNodes);
	mobility.Install (ueNodes);

    // Installing the LTE Devices to the nodes
	NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice (enbNodes);
	NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice (ueNodes);

    // Installing the IP stack on the UEs
	internet.Install(ueNodes);
	Ipv4InterfaceContainer ueIpIface ;
	ueIpIface = epcHelper->AssignUeIpv4Address (NetDeviceContainer(ueLteDevs));

    // Assigning IP adresses to the UEs and installing applications
	for ( uint32_t u = 0; u < ueNodes.GetN(); ++u)
    {
		Ptr<Node> ueNode = ueNodes.Get(u);
        // Setting up the default gateway for the UE
		Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4>());
		ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress(), 1);
	}

	lteHelper->Attach(ueLteDevs);
	// side effects : 1) use idle mode cell selection , 2) activate default EPSbearer
	// randomize a bit start times to avoid simulation artifacts
	// (e.g., buffer overflows due to packet transmissions happening
	// exactly at the same time )
	Ptr<UniformRandomVariable> startTimeSeconds = CreateObject <UniformRandomVariable> ();
	startTimeSeconds->SetAttribute ("Min", DoubleValue (0));
	startTimeSeconds->SetAttribute ("Max", DoubleValue (interPacketInterval/1000.0) );

	// Installing and starting the applications on UEs and remote host
	uint16_t dlPort = 1234;
	uint16_t ulPort = 2000;
	for ( uint32_t u = 0; u < ueNodes . GetN (); ++u)
    {
		++ulPort ;
		// Creating the application
		ApplicationContainer clientApps;
		ApplicationContainer serverApps;
		// Creating UDP communication and installation on helpers on each node
		PacketSinkHelper dlPacketSinkHelper ("ns3::UdpSocketFactory",InetSocketAddress ( Ipv4Address::GetAny(), dlPort ));
		PacketSinkHelper ulPacketSinkHelper ("ns3::UdpSocketFactory",InetSocketAddress ( Ipv4Address::GetAny(), ulPort ));
		serverApps.Add(dlPacketSinkHelper.Install(ueNodes.Get(u)));
		serverApps.Add(ulPacketSinkHelper.Install(remoteHost));
		// Setting up the IP addresses, ports, sending the packets in intervals etc...
		UdpClientHelper dlClient (ueIpIface.GetAddress (u), dlPort );
		dlClient.SetAttribute ("Interval", TimeValue ( MilliSeconds (interPacketInterval )));
		dlClient.SetAttribute ("MaxPackets", UintegerValue (1000000) );
		UdpClientHelper ulClient (remoteHostAddr, ulPort );
		ulClient.SetAttribute ("Interval", TimeValue ( MilliSeconds (interPacketInterval )));
		ulClient.SetAttribute ("MaxPackets", UintegerValue (1000000) );
		// Installation of the client side
		clientApps.Add ( dlClient.Install ( remoteHost ));
		clientApps.Add ( ulClient.Install ( ueNodes.Get(u)));
		// Application start
		serverApps.Start (Seconds ( startTimeSeconds->GetValue ()));
		clientApps.Start (Seconds ( startTimeSeconds->GetValue ()));
	}
	// Simulation start
	Simulator::Stop(Seconds(simTime));
	Simulator::Run();
	Simulator::Destroy();
	return 0;
}
