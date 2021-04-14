/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
/**
 * @Author Alex Sporni
 * @Date 23-24.10.2020
 */

// necessary includes
#include "ns3/core-module.h"			// core module loading
#include "ns3/network-module.h"			// network module loading
#include "ns3/internet-module.h"		// internet module loading
#include "ns3/point-to-point-module.h"	// p2p module loading
#include "ns3/applications-module.h"	// application module loading

using namespace ns3;													// ns3 namespace declaration

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");							// definition of log component wit the name "FirstScriptExample"

int main (int argc, char *argv[]) 										// the main function of the program, where argc is the number of input arguments, argv the input arguments
{
	uint32_t nPackets = 1;												// unsigned 32bit Integer with the name nPackets, initialized to 1
	CommandLine cmd;													// creating an instance of object cmd from the class CommandLine
	cmd.AddValue ("nPackets", "Number of packets to echo", nPackets);	// adding an option to load custom number of packets
	cmd.Parse (argc, argv);												// parameter parsing

	Time::SetResolution (Time::NS); // setting time to nanoseconds
	LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);	// turning on logging on a client, logging level is set to INFO
	LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);	// turning on logging on a server, logging level is set to INFO
	LogComponentEnable ("FirstScriptExample", LOG_LEVEL_ALL );			// turning on logging component with the name FirstScriptExample, level is set to ALL

	NS_LOG_INFO ("Creating Topology");	// printing LOG with a text "Creating Topology"

	NodeContainer nodes;	// creating an object instance nodes from class "NodeContainer"
	nodes.Create (2);		// passing integer value 2 to the method "create" of the object "nodes"

	PointToPointHelper pointToPoint; // creating an object instance "pointToPoint" from class "PointToPointHelper"
	pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));	// setting attribute "DataRate" to the value of 5Mbps
	pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));		// setting attribute "Delay" to the value of 2ms

	NetDeviceContainer devices;	// this line of code declares the device container
	devices = pointToPoint.Install (nodes);	// the install method of the PointToPointHelper takes a NodeContainer as a parameter

	InternetStackHelper stack; // creating an object instance "stack" from the class "InternetStackHelper"
	stack.Install (nodes); // installing p2p channel between nodes

	Ipv4AddressHelper address; // creating an object instance "address" from the class "Ipv4AddressHelper"
	address.SetBase ("10.1.1.0", "255.255.255.0"); // allocating an IP address and a subnet mask

	Ipv4InterfaceContainer interfaces = address.Assign (devices); // this command performs the actual address assignment to the object instance interfaces

	UdpEchoServerHelper echoServer (9); // creating an object instance "echoServer" from the class "UdpEchoServerHelper" and passing the parameter 9 (port number)

	ApplicationContainer serverApps = echoServer.Install (nodes.Get (1)); // creating an object instance "serverApps" from the class "ApplicationContainer" and passing the return value of method "Install" to it
	serverApps.Start (Seconds (1.0));	// start of the server app at the time t=1s
	serverApps.Stop (Seconds (10.0));	// termination of the server app at the time t=10s

	UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9); // the echo client application is set up in a method substantially similar to that for the server... we are creating the helper and telling it so set the remote address of the client to be the IP address assigned to the node on which the server resides
	echoClient.SetAttribute ("MaxPackets", UintegerValue (1)); // setting the attribute "MaxPackets"
	echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0))); // setting the attribute "Interval" to the initial value of 1s
	echoClient.SetAttribute ("PacketSize", UintegerValue (1024)); // setting the attribute "PacketSize" to the size of 1024
	echoClient.SetAttribute ("MaxPackets", UintegerValue (nPackets)); // overwriting the Integer value 1 by the value of nPackets which user can define

	ApplicationContainer clientApps = echoClient.Install (nodes.Get (0)); // same as line 66 but on client side...
	clientApps.Start (Seconds (2.0));	// client app will start at time t=2.s
	clientApps.Stop (Seconds (10.0));	// client app will terminate on time t=10s

	AsciiTraceHelper ascii; // creating an object instance "ascii" from the class "AsciiTraceHelper"
	pointToPoint.EnableAsciiAll(ascii.CreateFileStream("first.tr")); // creating a p2p output of a connection, to ascii chars to the file first.tr
	pointToPoint.EnablePcapAll("first"); // creating a p2p output to a .pcap file with the name "first" this file can be oppened and examined in wireshark...

	Simulator::Run (); // starting the simulation
	Simulator::Destroy (); // stopping the simulation
	return 0; // if is everything correct the function main returns an integer value 0 (OK)
}// end of the function Main body
