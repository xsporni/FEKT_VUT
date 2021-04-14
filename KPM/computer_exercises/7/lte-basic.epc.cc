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
* Authors : Jaume Nin <jaume . nin@cttc .cat >
* Manuel Requena <manuel . requena@cttc .es >
* Pavel Masek < masekpavel@vutbr .cz >
*/

/**
 * @Author Alex Sporni
 * @Date 29.11.2020
 */

// necessary includes
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store-module.h"
#include "ns3/lte-module.h"

using namespace ns3; //ns3 namespace declaration


/**
* Sample simulation script for LTE+EPC. It instantiates several eNodeBs ,
* attaches one UE per eNodeB starts a flow for each UE to and from a remote host .
* It also starts another flow between each UE pair .
*/
// definition of logging component with the name lte-basic-epc
NS_LOG_COMPONENT_DEFINE("lte-basic-epc");

// the main function of the program
int main (int argc, char *argv[])
{
    // variable initialization
	uint16_t numNodePairs = 2; 
	Time simTime = MilliSeconds(1100); 
	double distance = 60.0;
	Time interPacketInterval = MilliSeconds (100);
	bool useCa = false ;
	bool disableDl = false ;
	bool disableUl = false ;
	bool disablePl = false ;
	// Command line arguments
	CommandLine cmd;
	
    // command line argument parsing
	cmd.AddValue("numNodePairs", " Number of eNodeBs + UE pairs ", numNodePairs);
	cmd.AddValue(" simTime ", " Total duration of the simulation ", simTime);
	cmd.AddValue(" distance ", " Distance between eNBs [m]", distance);
	cmd.AddValue(" interPacketInterval ", " Inter packet interval ",interPacketInterval);
	cmd.AddValue(" useCa ", " Whether to use carrier aggregation .", useCa);
	cmd.AddValue(" disableDl ", " Disable downlink data flows ", disableDl);
	cmd.AddValue(" disableUl ", " Disable uplink data flows ", disableUl);
	cmd.AddValue(" disablePl ", " Disable data flows between peer UEs",disablePl);
	cmd.Parse(argc, argv);

	ConfigStore inputConfig ; 
	inputConfig.ConfigureDefaults(); 
	// parse again so you can override default values from the command line
	cmd.Parse(argc, argv);
    
    // this condition is used for carrier aggregation if the condition is true, then the default values of the object LteHelper will be used 
	if(useCa)
    {
		Config::SetDefault("ns3::LteHelper::UseCa", BooleanValue(useCa));
		Config::SetDefault("ns3::LteHelper::NumberOfComponentCarriers",UintegerValue(2));
		Config::SetDefault("ns3::LteHelper::EnbComponentCarrierManager",StringValue("ns3::RrComponentCarrierManager"));
	}
    // or the object ltehelper and point2point will be created and the variable ltehelper will be passed to them
	Ptr<LteHelper> lteHelper = CreateObject<LteHelper>();
	Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper>();
	lteHelper->SetEpcHelper(epcHelper);
	Ptr<Node> pgw = epcHelper->GetPgwNode();

    // Create a single RemoteHost and install the itnernet stack
	NodeContainer remoteHostContainer;
	remoteHostContainer.Create(1);
	Ptr<Node> remoteHost = remoteHostContainer.Get(0);
	InternetStackHelper internet;
	internet.Install(remoteHostContainer);

    // Create the p2p connection and setting up the link parameters
	PointToPointHelper p2ph;
	p2ph.SetDeviceAttribute("DataRate",DataRateValue(DataRate("100Gb/s")));
	p2ph.SetDeviceAttribute("Mtu", UintegerValue(1500));
	p2ph.SetChannelAttribute("Delay", TimeValue(MilliSeconds(10)));
	NetDeviceContainer internetDevices = p2ph.Install(pgw , remoteHost );
	Ipv4AddressHelper ipv4h;
	ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
	Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign(internetDevices);
	Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress(1);
	// setting up the routing and assigning the IP adress
	Ipv4StaticRoutingHelper ipv4RoutingHelper;
	Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4>());
	remoteHostStaticRouting->AddNetworkRouteTo(Ipv4Address("7.0.0.0"),Ipv4Mask("255.0.0.0"),1);
	
    // creating ue and enb nodes
	NodeContainer ueNodes;
	NodeContainer enbNodes;
	enbNodes.Create(numNodePairs);
	ueNodes.Create(numNodePairs);

	// Installing the mobility model
	Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator>();
	for (uint16_t i = 0; i < numNodePairs; i++)
    {
		positionAlloc->Add(Vector(distance*i, 0, 0));
	}

	MobilityHelper mobility;
	mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility.SetPositionAllocator(positionAlloc);
	mobility.Install(enbNodes);
	mobility.Install(ueNodes);

    // Installing LTEDevices to the nodes
	NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice(enbNodes);
	NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice(ueNodes);

	// Installing the IP stack on the UEs
	internet.Install(ueNodes);
	Ipv4InterfaceContainer ueIpIface;
	ueIpIface = epcHelper->AssignUeIpv4Address(NetDeviceContainer(ueLteDevs));

    // Assigning IP addresses to the UEs and installing application
	for (uint32_t u = 0; u < ueNodes.GetN(); ++u)
    {
		Ptr<Node> ueNode = ueNodes.Get(u);
		Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4>());
		ueStaticRouting->SetDefaultRoute(epcHelper->GetUeDefaultGatewayAddress(), 1);
	}
    // Attaching one UE per eNodeB
	for ( uint16_t i = 0; i < numNodePairs; i++){
		lteHelper->Attach(ueLteDevs.Get(i), enbLteDevs.Get(i));
	}
    // Installing and starting applications on the UEs and remote host
	uint16_t dlPort = 1100;
	uint16_t ulPort = 2000;
	uint16_t otherPort = 3000;
	ApplicationContainer clientApps;
	ApplicationContainer serverApps;

	for ( uint32_t u = 0; u < ueNodes.GetN(); ++u)
    {
		if (!disableDl)
        {
            PacketSinkHelper dlPacketSinkHelper("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny(),dlPort));
			serverApps.Add(dlPacketSinkHelper.Install (ueNodes.Get(u)));
			UdpClientHelper dlClient (ueIpIface.GetAddress(u), dlPort);
			dlClient.SetAttribute ("Interval", TimeValue (interPacketInterval));
			dlClient.SetAttribute ("MaxPackets", UintegerValue (1000000));
			clientApps.Add(dlClient.Install(remoteHost));
		}
		if (!disableUl)
        {
			++ulPort;
			PacketSinkHelper ulPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny(), ulPort ));
			serverApps.Add (ulPacketSinkHelper.Install(remoteHost));

			UdpClientHelper ulClient (remoteHostAddr, ulPort);
			ulClient.SetAttribute ("Interval", TimeValue (interPacketInterval));
			ulClient.SetAttribute ("MaxPackets", UintegerValue (1000000));
			clientApps.Add (ulClient.Install (ueNodes.Get(u)));
		}
		if (!disablePl && numNodePairs > 1)
        {
			++otherPort;
			PacketSinkHelper packetSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny(), otherPort));
			serverApps.Add (packetSinkHelper.Install (ueNodes.Get(u)));

			UdpClientHelper client (ueIpIface.GetAddress (u), otherPort);
			client.SetAttribute ("Interval", TimeValue (interPacketInterval));
			client.SetAttribute ("MaxPackets", UintegerValue (1000000));
			clientApps.Add (client.Install( ueNodes.Get ((u + 1) %	numNodePairs)));
		}
	}
	// starting the server and the client
	serverApps.Start(MilliSeconds(500));
	clientApps.Start(MilliSeconds(500));
	lteHelper->EnableTraces();

    // PCAP tracing enabled
	p2ph.EnablePcapAll ("lte-basic-epc");
	Simulator::Stop(simTime);
	Simulator::Run();

	Simulator::Destroy();
	return 0;
}
