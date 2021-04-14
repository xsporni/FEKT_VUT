/* -*- Mode : C++; c-file - style : "gnu "; indent -tabs - mode :nil ; -*- */
/*
 * Copyright (c) 2019 Brno University of Technology , FEEC , Department of Telecommunications
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
 * Author : Pavel Masek < masekpavel@vutbr .cz >
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
#include "ns3/config-store.h"
#include "ns3/netanim-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/traffic-control-module.h"
#include "ns3/data-rate.h"
#include <fstream>
#include <string>
#include "ns3/gnuplot.h"


using namespace ns3; //ns3 namespace declaration

// definition of logging component with the name LTEFULL
NS_LOG_COMPONENT_DEFINE ("LTEFULL");

int main(int argc, char *argv[]) 
{
	// variable initialization
	uint16_t numberOfNodes = 4; 
	uint16_t numberOf_eNodeBs = 2;
	double simTime = 10; 
	double distance = 60.0; 
	double interPacketInterval = 100;
	bool useCa = false;

	// Command line arguments
	CommandLine cmd;
	// Command line argument parsing
	cmd.AddValue("numberOfNodes", "Number of eNodeBs + UE pairs",numberOfNodes);
	cmd.AddValue("simTime", "Total duration of the simulation [s])",simTime);
	cmd.AddValue("distance", "Distance between eNBs [m]", distance);
	cmd.AddValue("interPacketInterval", "Interpacket interval [ms])",interPacketInterval);
	cmd.AddValue("useCa", "Whether to use carrier aggregation .", useCa);
	cmd.Parse(argc, argv);

    // setting up carrier agregation
	if (useCa) 
    {
		Config::SetDefault("ns3::LteHelper::UseCa", BooleanValue(useCa));
		Config::SetDefault("ns3::LteHelper::NumberOfComponentCarriers",	UintegerValue(2));
		Config::SetDefault("ns3::LteHelper::EnbComponentCarrierManager", StringValue("ns3::RrComponentCarrierManager"));
	}
	// Creating the helper objects and initialize them
	Ptr<LteHelper> lteHelper = CreateObject<LteHelper>();
	Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper>();
	lteHelper->SetEpcHelper(epcHelper);

	ConfigStore inputConfig ; 
	inputConfig.ConfigureDefaults();

	// Parse again so you can override default values from the command line
	cmd.Parse(argc, argv);
	//vytvorenie packet gateway pomocou helperu
	Ptr<Node> pgw = epcHelper->GetPgwNode();

    // Creating a single RemoteHost and initializing the stack
	NodeContainer remoteHostContainer;
	remoteHostContainer.Create(1);
	Ptr<Node> remoteHost = remoteHostContainer.Get(0);
	InternetStackHelper internet;
	internet.Install(remoteHostContainer);

    // Creating the Internet 
	PointToPointHelper p2ph;
	p2ph.SetDeviceAttribute("DataRate", DataRateValue(DataRate("10Gb/s")));
	p2ph.SetDeviceAttribute("Mtu", UintegerValue(1500));
	p2ph.SetChannelAttribute("Delay", TimeValue(Seconds(0.100)));
	NetDeviceContainer internetDevices = p2ph.Install(pgw, remoteHost);
    // Assigning the connection on two nodes and setting up the IP addresses from the range
	Ipv4AddressHelper ipv4h;
	ipv4h.SetBase("1.0.0.0", "255.0.0.0");
	Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign(internetDevices);
	Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress(1);
	// Setting up the routing and assigning the IP adress
	Ipv4StaticRoutingHelper ipv4RoutingHelper;
	Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting(remoteHost->GetObject<Ipv4>());
	remoteHostStaticRouting->AddNetworkRouteTo(Ipv4Address("7.0.0.0"),Ipv4Mask(" 255.0.0.0 "), 1);
    // Creating ue and enb nodes
	NodeContainer ueNodes;
	NodeContainer enbNodes;
	enbNodes.Create(numberOf_eNodeBs);
	ueNodes.Create(numberOfNodes);

     // Install Mobility Model
	MobilityHelper mobility;
	mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	/*mobility.SetPositionAllocator("ns3::GridPositionAllocator",
	 " MinX ", DoubleValue (15.0) ,
	 " MinY ", DoubleValue (20.0) ,
	 " DeltaX ", DoubleValue (5.0) ,
	 " DeltaY ", DoubleValue (2.0) ,
	 " GridWidth ", UintegerValue (6) ,
	 " LayoutType ", StringValue (" RowFirst "));*/
    // setting up random position for each mobility model and their installation on nodes
	mobility.SetPositionAllocator("ns3::RandomBoxPositionAllocator", //Random Box position
			"X",StringValue("ns3::UniformRandomVariable[Min=20|Max=25]"),
			"Y",StringValue("ns3::UniformRandomVariable[Min=20|Max=25]"),
			"Z", StringValue("ns3::UniformRandomVariable[Min=0|Max=0]"));
    mobility.Install(enbNodes);
	mobility.Install(ueNodes);

	// Instalacia LTE na zariadenia
	NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice(enbNodes);
	NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice(ueNodes);

	// Installing LTe Devices to teh nodes
	internet.Install(ueNodes);
	Ipv4InterfaceContainer ueIpIface;
	ueIpIface = epcHelper->AssignUeIpv4Address(NetDeviceContainer(ueLteDevs));

    // Assigning IP addresses to the UEs, and installing applications
	for (uint32_t u = 0; u < ueNodes.GetN(); ++u) 
    {
		Ptr<Node> ueNode = ueNodes.Get(u);
		Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting(ueNode->GetObject<Ipv4>());
		ueStaticRouting->SetDefaultRoute(epcHelper->GetUeDefaultGatewayAddress(), 1);
	}

	// Attaching one UE per EnodeB 
	for (uint16_t i = 0; i < numberOfNodes; i++) 
    {
		if (i < 2) {
			lteHelper->Attach(ueLteDevs.Get(i), enbLteDevs.Get(0));
		} else {
			lteHelper->Attach(ueLteDevs.Get(i), enbLteDevs.Get(1));
		}
	}

    // Creating a BulkSendApplication and installing it on node 0
	uint16_t port = 9; // well - known echo port number
	uint16_t port2 = 33; // well - known echo port number

	BulkSendHelper source("ns3::TcpSocketFactory",InetSocketAddress(remoteHostAddr, port));
	BulkSendHelper source2("ns3::TcpSocketFactory",InetSocketAddress(remoteHostAddr, port2));

	// Setting up the amount of data to send in bytes, zero means it is not limited
	source.SetAttribute("MaxBytes", UintegerValue(0));
	source2.SetAttribute("MaxBytes", UintegerValue(0));
	ApplicationContainer sourceApps; 
	ApplicationContainer sourceApps2; 
	for (uint16_t i = 0; i < numberOfNodes; i++) {
		if (i < 2) {
			source.Install(ueNodes.Get(i));
		} else {
			source2.Install(ueNodes.Get(i));
		}
	}
	// start and stop timers for the application
	sourceApps.Start(Seconds(0.0));
	sourceApps.Stop(Seconds(10.0));

	sourceApps2.Start(Seconds(0.0));
	sourceApps2.Stop(Seconds(10.0));
	//vytvorenie packet sink aplikacie a priradenie na remote host, nasledne spustenie a zastavenie
	PacketSinkHelper sink("ns3::TcpSocketFactory",InetSocketAddress(Ipv4Address::GetAny(), port));
	ApplicationContainer sinkApps = sink.Install(remoteHost);
	sinkApps.Start(Seconds(0.0));
	sinkApps.Stop(Seconds(10.0));
    // Creating a PacketSinkApplication and installing it on node 1
	PacketSinkHelper sink2("ns3::TcpSocketFactory",InetSocketAddress(Ipv4Address::GetAny(), port2));
	ApplicationContainer sinkApps2 = sink2.Install(remoteHost);
	sinkApps2.Start(Seconds(0.0));
	sinkApps2.Stop(Seconds(10.0));
	lteHelper->EnableTraces();

	// Animation definition, creation of XML file, setting up the position remote host, 
	unsigned long long testValue = 0xFFFFFFFFFFFFFFFF;
	AnimationInterface::SetConstantPosition(remoteHost, 30, 50);
	AnimationInterface::SetConstantPosition(pgw, 30, 40);
	AnimationInterface anim("xsporn01.xml");
	anim.SetMobilityPollInterval(Seconds(1));
	anim.EnablePacketMetadata(true);

	anim.SetMaxPktsPerTraceFile(testValue);
	anim.UpdateNodeDescription(pgw, "PGW");
	anim.UpdateNodeDescription(remoteHost, "Remote_Host");
	anim.UpdateNodeDescription(5, "Access-point");
	anim.UpdateNodeDescription (ueNodes.Get (0),"Ue_Dev");
	anim.UpdateNodeDescription (enbNodes.Get (0),"eNodeB");

	for (uint32_t u = 0; u < ueNodes.GetN(); ++u) {
		anim.UpdateNodeDescription(ueNodes.Get(u), "Ue_" + std::to_string(u));
		AnimationInterface::SetConstantPosition(ueNodes.Get(u), 10 + 15 * u,20);
		anim.UpdateNodeColor(ueNodes.Get(u), 0, 0, 255);
	}

	for (uint32_t u = 0; u < enbNodes.GetN(); ++u) {
		anim.UpdateNodeDescription(enbNodes.Get(u),"eNodeB_" + std::to_string(u));
		anim.UpdateNodeColor(enbNodes.Get(u), 0, 255, 0);
		AnimationInterface::SetConstantPosition(enbNodes.Get(u), 10 + 40 * u,30);
	}

	// Enabling Pcap logging
	p2ph.EnablePcapAll("lte-full");
	// creating flowmonitor throughout helper object
	FlowMonitorHelper flowMonHelper;
	Ptr <FlowMonitor> monitor; 
	monitor = flowMonHelper.Install(enbNodes);
	monitor = flowMonHelper.Install(ueNodes);
	monitor = flowMonHelper.Install(remoteHost);
	// Starting the simulation
	Simulator::Stop(Seconds(simTime));
	Simulator::Run();

	// GnuPlot, creating the graph with the attributes bellow
	std::string jmenoSouboru = "delay";
	std::string graphicsFileName = jmenoSouboru + ".png";
	std::string plotFileName = jmenoSouboru + ".plt";
	std::string plotTitle = "Average delay";
	std::string dataTitle = "Delay [ms]";
	Gnuplot gnuplot(graphicsFileName);
	gnuplot.SetTitle(plotTitle);
	gnuplot.SetTerminal("png");
	gnuplot.SetLegend("IDs of data streams", "Delay [ms]");
	gnuplot.AppendExtra("set xrange [1:" + std::to_string(numberOfNodes * 2) + "]");
	gnuplot.AppendExtra("set yrange [0:100]");
	gnuplot.AppendExtra("set grid");
	Gnuplot2dDataset dataset;

	jmenoSouboru = "datarate";
	graphicsFileName = jmenoSouboru + ".png";
	std::string plotFileNameDR = jmenoSouboru + ".plt";
	plotTitle = "Data rate for IDs";
	dataTitle = "Data rate [ kbps ]";
	Gnuplot gnuplot_DR(graphicsFileName);
	gnuplot_DR.SetTitle(plotTitle);
	gnuplot_DR.SetTerminal("png");
	gnuplot_DR.SetLegend("IDs of all streams", "Data rate [ kbps ]");
	gnuplot_DR.AppendExtra ("set xrange [1:"+std :: to_string ( numberOfNodes *2)+"]");
	gnuplot_DR.AppendExtra ("set yrange [0:1000]");
	gnuplot_DR.AppendExtra("set grid");
	Gnuplot2dDataset dataset_rate;
	monitor->CheckForLostPackets();
	Ptr <Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowMonHelper.GetClassifier());
	std::map <FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats();
	monitor->SerializeToXmlFile(" manetrouting.flowmon", true, true);//vytvorenie xml suboru
	std::cout << std::endl << "*** Flow monitor statistic ***"<< std::endl;
	for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i =stats.begin(); i != stats.end(); ++i) {
		double Delay, DataRate;
		Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow(i->first);
		std::cout << " Flow ID:" << i->first << std::endl;
		std::cout << " Src add: " << t.sourceAddress << " -> Dst add: "<< t.destinationAddress << std::endl;
		std::cout << " Src port : " << t.sourcePort << " -> Dst port : "<< t.destinationPort << std::endl;
		std::cout << " Tx Packets / Bytes : " << i->second.txPackets<< " / " << i->second.txBytes << std::endl;
		std::cout << " Rx Packets / Bytes : " << i->second.rxPackets<< " /" << i-> second . rxBytes << std :: endl ;
		std::cout << " Throughput : "<< i->second.rxBytes * 8.0/ (i->second.timeLastRxPacket.GetSeconds()- i->second.timeFirstTxPacket.GetSeconds())/ 1024 << " kb/s" << std::endl;
		std::cout << " Delay sum: "<< i->second.delaySum.GetMilliSeconds() << " ms"<< std::endl;
		std::cout << " Mean delay : "<< (i->second.delaySum.GetSeconds()/ i->second.rxPackets) * 1000 << " ms"<< std::endl;

		// gnuplot Delay
		Delay = (i->second.delaySum.GetSeconds() / i->second.rxPackets)* 1000;
		DataRate = i->second.rxBytes * 8.0 / (i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds())/ 1024;

		dataset.Add((double)i->first,(double) Delay);
		dataset_rate.Add((double)i->first,(double) DataRate);
		std::cout << " Jitter sum: "<< i->second.jitterSum.GetMilliSeconds() << " ms"<< std::endl;
		std::cout << " Mean jitter : "<< (i->second.jitterSum.GetSeconds()/ (i->second.rxPackets - 1)) * 1000 << " ms"<< std::endl;
		std::cout << " Lost Packets : "<< i->second.txPackets - i->second.rxPackets<< std::endl;
		std::cout << " Packet loss : "<< (((i->second.txPackets - i->second.rxPackets) * 1.0)/ i->second.txPackets) * 100 << " %"<< std::endl;
		std::cout << " ------------------------------------------------"<< std::endl;
	}
	// Gnuplot - continuation
	gnuplot.AddDataset(dataset);
	std::ofstream plotFile(plotFileName.c_str());
	gnuplot.GenerateOutput(plotFile);
	plotFile.close();
	gnuplot_DR.AddDataset(dataset_rate);
	std::ofstream plotFileDR(plotFileNameDR.c_str());
	gnuplot_DR.GenerateOutput(plotFileDR);
	plotFileDR.close();
    // Simulation termination
	Simulator::Destroy();
	return 0;
}

