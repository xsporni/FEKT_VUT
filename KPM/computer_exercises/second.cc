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
 * @Date 30.10.2020
 */

// necessary includes
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"

// Default Network Topology
//
//       10.1.1.0
// n0 -------------- n1   n2   n3   n4
//    point-to-point  |    |    |    |
//                    ================
//                      LAN 10.1.2.0


using namespace ns3;	// ns3 namespace declaration

NS_LOG_COMPONENT_DEFINE ("SecondScriptExample");	// definition of log component wit the name "SecondScriptExample"

int main (int argc, char *argv[])	// the main function of the program, where argc is the number of input arguments, argv the input arguments
{
	  bool verbose = true;			// creating a boolean variable and assigning a true value to it, it is used for enabling UDP logging
	  uint32_t nCsma = 3;			// creating an unsigned Integer variable with a value of 3, it creates 3 nodes in the CSMA part of the topology

	  CommandLine cmd;				// creating an instance of object cmd from the class CommandLine
	  cmd.AddValue ("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);		// adding the option of own number of nodes to the topology
	  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose); 	// adding the option of turning on/off UDP logging for application

	  cmd.Parse (argc,argv); // argument parsing

	  if (verbose) // just a condition if the value of the verbose variable is true, if yes enable UDP logging on level INFO
		{
		  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO); 	// client side logging
		  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);	// server side logging
		}

	  nCsma = nCsma == 0 ? 1 : nCsma;	//ternary operator, if nCsma == 0 then it changes to 1, else value > 0 will stay

	  NodeContainer p2pNodes;		// creating an object instance nodes from class "NodeContainer"
	  p2pNodes.Create (2);			// passing integer value 2 to the method "create" of the object "nodes"

	  NodeContainer csmaNodes;		// creating an object instance "csmaNodes" from class NodeContainer
	  csmaNodes.Add (p2pNodes.Get (1)); // adding a value of p2pNodes on a position of index 1 to the variable csmaNodes
	  csmaNodes.Create (nCsma);			// creating multiple csmaNodes based on the integer value of the variable nCsma

	  PointToPointHelper pointToPoint;	// creating an object instance "pointToPoint" from class "PointToPointHelper"
	  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));		// setting attribute "DataRate" to the value of 5Mbps
	  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));			// setting attribute "Delay" to the value of 2ms

	  NetDeviceContainer p2pDevices; // creating an object instance "p2pDevices" from class "NetDeviceContainer"
	  p2pDevices = pointToPoint.Install (p2pNodes); //creating a simple p2p connection between two "p2pNodes"

	  CsmaHelper csma;	// creating an object instance "csma" from class CsmaHelper
	  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));	// setting attribute "DataRate" to the value of 100Mbps
	  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560))); // setting attribute "Delay" to the value of 6560ns

//	  csma.SetDeviceAttribute("Mtu", StringValue("1500")); // setting the attribute Mtu to string value 1500
//	  csma.SetDeviceAttribute("EncapsulationMode", StringValue("Llc")); // setting the attribute EncapsulationMode to the string value "Llc"

	  NetDeviceContainer csmaDevices; // creating an object instance "csmaDevices" from the class "NetDeviceContainer"
	  csmaDevices = csma.Install (csmaNodes); // creating a simple  csma bus connection between "csmaNodes"

	  InternetStackHelper stack;	// creating an object instance "stack" from the class "InternetStackHelper"
	  stack.Install (p2pNodes.Get (0)); // communication protocol installation on p2pNodes
	  stack.Install (csmaNodes);		// communication protocol installation on csmaNodes

	  Ipv4AddressHelper address; // creating an object instance from the class "Ipv4AddressHelper"
	  address.SetBase ("10.1.1.0", "255.255.255.0"); // setting the address space to 10.1.1.0/24
	  Ipv4InterfaceContainer p2pInterfaces; // creating an object instance p2pInterfaces from the class "Ipv4InterfaceContainer"
	  p2pInterfaces = address.Assign (p2pDevices); // assigning the IP addresses to the p2pInterfaces

	  address.SetBase ("10.1.2.0", "255.255.255.0"); // setting the address space to 10.1.2.0/24
	  Ipv4InterfaceContainer csmaInterfaces;		 //creating an object instance csmaInterfaces from the class "Ipv4InterfaceContainer"
	  csmaInterfaces = address.Assign (csmaDevices); // assigning the IP addresses to the csmaInterfaces

	  UdpEchoServerHelper echoServer (9); // creating an object instance "echoServer" from the class "UdpEchoServerHelper" and assigning the port number --> server side
	  ApplicationContainer serverApps = echoServer.Install (csmaNodes.Get (nCsma)); //installing the server app to the created instance "ServerApps" from the class "ApplicationContainer"
	  serverApps.Start (Seconds (1.0)); // start of the server app at the time t=1s
	  serverApps.Stop (Seconds (10.0)); // termination of the server app at the time t=10s

	  UdpEchoClientHelper echoClient (csmaInterfaces.GetAddress (nCsma), 9); // same as on the server side...
	  echoClient.SetAttribute ("MaxPackets", UintegerValue (1)); // setting the attribute "MaxPackets" to 1
	  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0))); // setting the attribute "Interval" to the initial value of 1s
	  echoClient.SetAttribute ("PacketSize", UintegerValue (1024)); // setting the attribute "PacketSize" to the size of 1024

	  ApplicationContainer clientApps = echoClient.Install (p2pNodes.Get (0)); //installing the client app on the first interface to the created  instance "ClientApps" from the class "ApplicationContainer"
	  clientApps.Start (Seconds (2.0));	// start of the client app at the time t=1s
	  clientApps.Stop (Seconds (10.0)); // termination of the client app at the time t=10s

	  Ipv4GlobalRoutingHelper::PopulateRoutingTables (); //assembling the routing tables for the topology

//	  pointToPoint.EnablePcapAll ("second");
//	  csma.EnablePcap ("second", csmaDevices.Get (1), true);

	  pointToPoint.EnablePcap("second",p2pNodes.Get(0)->GetId(),0); 		// creating an output of the p2p connection to the pcap file with the name second
	  csma.EnablePcap("second",csmaNodes.Get(nCsma)->GetId(), 0, false);	// creating an output of the csma connection on the last node - server  to the pcap file with the name second
	  csma.EnablePcap("second",csmaNodes.Get(nCsma-1)->GetId(), 0, false); // creating an output of the csma connection on the previes from the last node - server  to the pcap file with the name second

	  Simulator::Run (); // simulation start
	  Simulator::Destroy (); // simulation end

	  /*
	   * In the case of turning on the promiscuous mode on one of the csma nodes, the whole communication of the topology is stored, not just the single node
	   */

	  return 0; // if is everything correct the function main returns an integer value 0 (OK)
}
