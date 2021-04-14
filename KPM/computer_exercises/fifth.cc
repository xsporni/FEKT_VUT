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

// necessary includes
#include <fstream>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3; // ns3 namespace declaration

NS_LOG_COMPONENT_DEFINE ("FifthScriptExample"); // definition of log component wit the name "FifthScriptExample"

// ===========================================================================
//
//         node 0                 node 1
//   +----------------+    +----------------+
//   |    ns-3 TCP    |    |    ns-3 TCP    |
//   +----------------+    +----------------+
//   |    10.1.1.1    |    |    10.1.1.2    |
//   +----------------+    +----------------+
//   | point-to-point |    | point-to-point |
//   +----------------+    +----------------+
//           |                     |
//           +---------------------+
//                5 Mbps, 2 ms
//
//
// We want to look at changes in the ns-3 TCP congestion window.  We need
// to crank up a flow and hook the CongestionWindow attribute on the socket
// of the sender.  Normally one would use an on-off application to generate a
// flow, but this has a couple of problems.  First, the socket of the on-off 
// application is not created until Application Start time, so we wouldn't be 
// able to hook the socket (now) at configuration time.  Second, even if we 
// could arrange a call after start time, the socket is not public so we 
// couldn't get at it.
//
// So, we can cook up a simple version of the on-off application that does what
// we want.  On the plus side we don't need all of the complexity of the on-off
// application.  On the minus side, we don't have a helper, so we have to get
// a little more involved in the details, but this is trivial.
//
// So first, we create a socket and do the trace connect on it; then we pass 
// this socket into the constructor of our simple application which we then 
// install in the source node.
// ===========================================================================
//

/**
 * @Author Alex Sporni
 * @Date 15.11.2020
 */

// Public class MyApp
class MyApp : public Application 
{
public:

  MyApp ();
  virtual ~MyApp();

  void Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate);
// private methods with private variables
private:
  virtual void StartApplication (void);
  virtual void StopApplication (void);

  void ScheduleTx (void);
  void SendPacket (void);

  Ptr<Socket>     m_socket;
  Address         m_peer;
  uint32_t        m_packetSize;
  uint32_t        m_nPackets;
  DataRate        m_dataRate;
  EventId         m_sendEvent;
  bool            m_running;
  uint32_t        m_packetsSent;
};
// constructor
MyApp::MyApp ()
  : m_socket (0), 
    m_peer (), 
    m_packetSize (0), 
    m_nPackets (0), 
    m_dataRate (0), 
    m_sendEvent (), 
    m_running (false), 
    m_packetsSent (0)
{
}
// destructor
MyApp::~MyApp()
{
  m_socket = 0;
}

// function Setup which sets the values of attributes according to the passed attributes
void MyApp::Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate)
{
  m_socket = socket;
  m_peer = address;
  m_packetSize = packetSize;
  m_nPackets = nPackets;
  m_dataRate = dataRate;
}

// function StartApplication, the purpose of this function is to set initial values and start the simulation
void MyApp::StartApplication (void)
{
  m_running = true;
  m_packetsSent = 0;
  m_socket->Bind ();
  m_socket->Connect (m_peer);
  SendPacket ();
}

// function StopApplication, the purpose of this function is to stop the simulation
void MyApp::StopApplication (void)
{
  m_running = false;

  if (m_sendEvent.IsRunning ())
    {
      Simulator::Cancel (m_sendEvent);
    }

  if (m_socket)
    {
      m_socket->Close ();
    }
}

// function SendPacket, the purpose of this function is to send a packet
void MyApp::SendPacket (void)
{
  Ptr<Packet> packet = Create<Packet> (m_packetSize);
  m_socket->Send (packet);

  if (++m_packetsSent < m_nPackets)
    {
      ScheduleTx ();
    }
}

// function ScheduleTx, the purpose of this function is to schedule packet sending in specific time intervals with specific bitrate
void MyApp::ScheduleTx (void)
{
  if (m_running)
    {
      Time tNext (Seconds (m_packetSize * 8 / static_cast<double> (m_dataRate.GetBitRate ())));
      m_sendEvent = Simulator::Schedule (tNext, &MyApp::SendPacket, this);
    }
}

// function CwndChange, the purpose of this function is to implement the corresponding trace sink
// this function logs the current simulation time and the new value of the congestuion window every time it is changed
static void CwndChange (uint32_t oldCwnd, uint32_t newCwnd)
{
  NS_LOG_UNCOND (Simulator::Now ().GetSeconds () << "\t" << newCwnd);
}
// logging function, we do not need that se we just dissable it
// static void RxDrop (Ptr<const Packet> p)
// {
//   NS_LOG_UNCOND ("RxDrop at " << Simulator::Now ().GetSeconds ());
// }

// The main function
int main (int argc, char *argv[])
{
        // command line parsing
    CommandLine cmd;
    cmd.Parse (argc, argv);

    NodeContainer nodes; // creating an object instance nodes from class "NodeContainer"
    nodes.Create (2); // passing integer value 2 to the method "Create" of the object "nodes"

    PointToPointHelper pointToPoint; // creating an object instance "pointToPoint" from class "PointToPointHelper"
    pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps")); // setting attribute "DataRate" to the value of 5Mbps
    pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms")); // setting attribute "Delay" to the value of 2ms

    NetDeviceContainer devices; // creating an object instance "p2pDevices" from class "NetDeviceContainer"
    devices = pointToPoint.Install (nodes); //creating a simple p2p connection between two "p2pNodes"

    Ptr<RateErrorModel> em = CreateObject<RateErrorModel> (); // creating an object instance "em" from class "RateErrorModel"
    em->SetAttribute ("ErrorRate", DoubleValue (0.00001)); // creating a error with the current value
    devices.Get (1)->SetAttribute ("ReceiveErrorModel", PointerValue (em));

    InternetStackHelper stack; // creating an object instance "stack" from class "InternetStackHelper"
    stack.Install (nodes); // installing communication protocols on nodes

    Ipv4AddressHelper address;  //creating an object instance "address" from the class "Ipv4AddressHelper"
    address.SetBase ("10.1.1.0", "255.255.255.252"); // setting the address space to 10.1.1.0/30
    Ipv4InterfaceContainer interfaces = address.Assign (devices); // assigning the addresses

    uint16_t sinkPort = 8080; // creating a sinkPort variable and assigning the integer value 8080 to it
    Address sinkAddress (InetSocketAddress (interfaces.GetAddress (1), sinkPort));
    /*
        This code instantiates a PacketSinkHelper and tells it to create sockets using the class called
        ns3::TcpSocketFactory. This class implements a design pattern called \object factory" which is
        a commonly used mechanism for specifying a class used to create objects in an abstract way.
    */
    PacketSinkHelper packetSinkHelper ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort));
    ApplicationContainer sinkApps = packetSinkHelper.Install (nodes.Get (1));
    sinkApps.Start (Seconds (0.)); // Application start at time t = 0 s
    sinkApps.Stop (Seconds (20.)); // Application termination at time t = 20 s
    // The purpose of the next two lines of code is to create the socket and connect the trace sorce
    // tge first statement calls the static member function Socekt::CreateSocket and provides a Node and explicit
    // TypeID for the object factory used to create tFhe socket
    Ptr<Socket> ns3TcpSocket = Socket::CreateSocket (nodes.Get (0), TcpSocketFactory::GetTypeId ());
    ns3TcpSocket->TraceConnectWithoutContext ("CongestionWindow", MakeCallback (&CwndChange));

    Ptr<MyApp> app = CreateObject<MyApp> (); // this line of code creates an Object of type MyApp
    app->Setup (ns3TcpSocket, sinkAddress, 1040, 1000, DataRate ("1Mbps")); // this line of code tells the Applicatio nwhat Socket to use, what adress to connect to, how much data to send at each send event...
    nodes.Get (0)->AddApplication (app); // this line of code manually adds the MyApp Application to the source Node and explicitly call the Start and Stop methods
    app->SetStartTime (Seconds (1.)); // when to start
    app->SetStopTime (Seconds (20.)); // when to stop

    //devices.Get (1)->TraceConnectWithoutContext ("PhyRxDrop", MakeCallback (&RxDrop)); //assigning the socet to the device

    Simulator::Stop (Seconds (20)); // stopping the simulation after 20s
    Simulator::Run ();
    Simulator::Destroy ();

    return 0;
}
