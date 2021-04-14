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
 * @Date 10.11.2020
 */

// necessary includes
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/yans-wifi-phy.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ssid.h"
#include "ns3/traffic-control-helper.h"
#include "ns3/wifi-net-device.h"
#include "ns3/config-store.h"

// Default Network Topology
//
//   Wifi 10.1.3.0
//                 AP
//  *    *    *    *
//  |    |    |    |    10.1.1.0
// n5   n6   n7   n0 -------------- n1   n2   n3   n4
//                   point-to-point  |    |    |    |
//                                   ================
//                                     LAN 10.1.2.0

using namespace ns3; // ns3 namespace declaration

NS_LOG_COMPONENT_DEFINE ("ThirdScriptExample"); // definition of log component wit the name "ThirdScriptExample"

/*
* This function pulls the position infromation from the mobility model and unconditionally logs the x and y position of the node
*/
void CourseChange (std::string context , Ptr<const MobilityModel> model ){
	Vector position = model->GetPosition();
	NS_LOG_UNCOND ( context <<" x = " << position.x << ", y = " << position.y);
}


/*
* Function which is used to change object parameters of WIFI PHY
*/
Ptr<YansWifiPhy> GetYansWifiPhyPtr (const NetDeviceContainer &nc){
   Ptr<WifiNetDevice> wnd = nc.Get (0)->GetObject<WifiNetDevice> ();
   Ptr<WifiPhy> wp;
   wp = wnd->GetPhy();
   return wp->GetObject<YansWifiPhy> ();
}

// Main function
int main (int argc, char *argv[])
{
    // Variable declaration and definition, tracing is set to true so we can generate .tr output
	bool verbose = true;
	uint32_t nCsma = 3;
	uint32_t nWifi = 3;
	bool tracing = true;

    // Command line argument parsing
	CommandLine cmd;
	cmd.AddValue ("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);
	cmd.AddValue ("nWifi", "Number of wifi STA devices", nWifi);
	cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);
	cmd.AddValue ("tracing", "Enable pcap tracing", tracing);
	cmd.Parse (argc,argv);

	// The underlying restriction of 18 is due to the grid position
	// allocator's configuration; the grid layout will exceed the
	// bounding box if more than 18 nodes are provided.
	if (nWifi > 18) // nWifi parameter checking
	{
	  std::cout << "nWifi should be 18 or less; otherwise grid layout exceeds the bounding box" << std::endl;
	  return 1;
	}
    // if verbose is enabled then logging will happen
	if (verbose)
	{
	  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
	  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
	}

	NodeContainer p2pNodes; // creating an object instance nodes from class "NodeContainer"
	p2pNodes.Create (2); // passing integer value 2 to the method "create" of the object "nodes"

	PointToPointHelper pointToPoint;    // creating an object instance "pointToPoint" from class "PointToPointHelper"
	pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps")); // setting attribute "DataRate" to the value of 5Mbps
	pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));    // setting attribute "Delay" to the value of 2ms

	NetDeviceContainer p2pDevices; // creating an object instance "p2pDevices" from class "NetDeviceContainer"
	p2pDevices = pointToPoint.Install (p2pNodes); //creating a simple p2p connection between two "p2pNodes"

	NodeContainer csmaNodes;    // creating an object instance "csmaNodes" from the class "NodeContainer"
	csmaNodes.Add (p2pNodes.Get (1)); //passing the value p2pNodes on the first index position
	csmaNodes.Create (nCsma);   // creating multiple nodes, based on the value in the nCsma variable

	CsmaHelper csma; // creating an object instance "csma" from the class "CsmaHelper"
	// same as previous, setting attribute values...
    csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
	csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

	NetDeviceContainer csmaDevices; // creating an object instance "csmaDevices" from the class "NetDeviceContainer"
	csmaDevices = csma.Install (csmaNodes);  // creating a simple  csma bus connection between "csmaNodes"

	NodeContainer wifiStaNodes;  // creating an object instance "wifiStaNodes" from the class "NodeContainer"
	wifiStaNodes.Create (nWifi); // creating multiple wifiStaNodes based on the value in the variable nWifi
	NodeContainer wifiApNode = p2pNodes.Get (0); // setting up the first node in the variable p2pNodes as the WIFI AP

	YansWifiChannelHelper channel = YansWifiChannelHelper::Default (); // creating WIFI channel with YansWifiChannelHelper and setting up as default value...
	YansWifiPhyHelper phy = YansWifiPhyHelper::Default (); // creating Wifi phy with YansWifiPhyHelper and setting up as default value
	phy.SetChannel (channel.Create ()); // creating the channel

	WifiHelper wifi; // creating an object instance "wifi" from the class "WifiHelper"
	wifi.SetStandard (WIFI_PHY_STANDARD_80211ax_5GHZ); // setting up the WIFI standard as 80211ax_5GHZ
    std::string dataRate = "HeMcs0"; // setting up the datarate value of the 80211ax_5GHZ standard
	wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager", "DataMode", StringValue(dataRate), "ControlMode", StringValue(dataRate)); // setting up remote manager attribute

	WifiMacHelper mac; //creating an object instance "mac" from the class "WifiMacHelper"
	Ssid ssid = Ssid ("ns-3-ssid"); // creating the variable ssid and naming it "ns-3-ssid"
	mac.SetType ("ns3::StaWifiMac",
			   "Ssid", SsidValue (ssid),
			   "ActiveProbing", BooleanValue (false)); // active probing is turned off

	NetDeviceContainer staDevices; //creating an object instance "staDevices" from the class "NetDeviceContainer"
	staDevices = wifi.Install (phy, mac, wifiStaNodes); // installing wifi funkcionality...

    Ptr<YansWifiPhy> phySta; //creating an object instance "phySta" from the class "YansWifiPhy"

    int freq = 5210; // frequency
    int bw = 80; // bandwidth
    int ch = 42; // channel number

    // assigning the values from above
    phySta = GetYansWifiPhyPtr(staDevices);
    NS_ASSERT (phySta->GetChannelNumber () == ch);
    NS_ASSERT (phySta->GetChannelWidth () == bw);
    NS_ASSERT (phySta->GetFrequency () == freq);


	mac.SetType ("ns3::ApWifiMac",
			   "Ssid", SsidValue (ssid));

	NetDeviceContainer apDevices;  //creating an object instance "apDevices" from the class "NetDeviceContainer"
	apDevices = wifi.Install (phy, mac, wifiApNode); // installing wifi funkcionality on all nodes in the variable apDevices

	MobilityHelper mobility; //creating an object instance "mobility" from the class "MobilityHelper"

	mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
								 "MinX", DoubleValue (0.0),
								 "MinY", DoubleValue (0.0),
								 "DeltaX", DoubleValue (5.0),
								 "DeltaY", DoubleValue (10.0),
								 "GridWidth", UintegerValue (3),
								 "LayoutType", StringValue ("RowFirst")); // creating a 2D grid, setting up X and Y MIN and MAX values

	mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
							 "Bounds", RectangleValue (Rectangle (-50, 50, -50, 50))); // random jumping in the boundariues of X and Y rectange
	mobility.Install (wifiStaNodes); // installing random movement funckionality

	mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel"); // setting up static position
	mobility.Install (wifiApNode); // installing static position on nodes in the variable wifiApNode

	InternetStackHelper stack; //creating an object instance "stack" from the class "InternetStackHelper"
	// installing necessary communication protocols on stack
    stack.Install (csmaNodes);
	stack.Install (wifiApNode);
	stack.Install (wifiStaNodes);

    //creating an object instance "address" from the class "Ipv4AddressHelper"
	Ipv4AddressHelper address;

    // setting up IP adresses for the network nodes
	address.SetBase ("10.1.1.0", "255.255.255.0"); // setting the address space to 10.1.1.0/24
	Ipv4InterfaceContainer p2pInterfaces; // creating an object instance p2pInterfaces from the class "Ipv4InterfaceContainer"
	p2pInterfaces = address.Assign (p2pDevices); // assigning the IP addresses to the p2pInterfaces

    // same operations as above just with the csmaInterfaces
	address.SetBase ("10.1.2.0", "255.255.255.0");
	Ipv4InterfaceContainer csmaInterfaces;
	csmaInterfaces = address.Assign (csmaDevices);

	address.SetBase ("10.1.3.0", "255.255.255.0"); // setting the address space to 10.1.3.0/24
	address.Assign (staDevices);
	address.Assign (apDevices);

	UdpEchoServerHelper echoServer (9); // creating an object instance "echoServer" from the class "UdpEchoServerHelper" and assigning the port number

	ApplicationContainer serverApps = echoServer.Install (csmaNodes.Get (nCsma)); //installing the server app to the created instance "ServerApps" from the class "ApplicationContainer"
	serverApps.Start (Seconds (1.0)); // start of the server app at the time t=1s
	serverApps.Stop (Seconds (10.0)); // termination of the server app at the time t=10s

	UdpEchoClientHelper echoClient (csmaInterfaces.GetAddress (nCsma), 9); // same as on the server side...
	echoClient.SetAttribute ("MaxPackets", UintegerValue (1)); // setting the attribute "MaxPackets" to 1
	echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0))); // setting the attribute "Interval" to the initial value of 1s
	echoClient.SetAttribute ("PacketSize", UintegerValue (1024)); // setting the attribute "PacketSize" to the size of 1024

	ApplicationContainer clientApps = echoClient.Install (wifiStaNodes.Get (nWifi - 1));
	clientApps.Start (Seconds (2.0)); // start of the client app at the time t=2s
	clientApps.Stop (Seconds (10.0)); // termination of the client app at the time t=10s

	Ipv4GlobalRoutingHelper::PopulateRoutingTables (); //assembling the routing tables for the topology

	Simulator::Stop (Seconds (10.0)); // terminating the simulation after 10s

	if (tracing == true) // checking if tracing is enabled
	{
	  pointToPoint.EnablePcapAll ("third"); // creating an output of the p2p connection to the pcap file with the name third
	  phy.EnablePcap ("third", apDevices.Get (0));
	  csma.EnablePcap ("third", csmaDevices.Get (0), true);

      AsciiTraceHelper ascii; //creating an object instance "ascii" from the class "AsciiTraceHelper"
      pointToPoint.EnableAsciiAll (ascii.CreateFileStream("third.tr"));
	}

	std::ostringstream oss; // string stream to console
	oss << "/NodeList/" << wifiStaNodes.Get (nWifi-1)->GetId () <<
		  "/$ns3::MobilityModel/CourseChange";
	Config::Connect(oss.str () , MakeCallback (&CourseChange)); // funckion call

	Simulator::Run (); // simulation start
	Simulator::Destroy (); // simulation end
	return 0;
}
