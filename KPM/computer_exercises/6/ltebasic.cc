// necessary includes
#include <ns3/core-module.h>
#include <ns3/network-module.h>
#include <ns3/mobility-module.h>
#include <ns3/lte-module.h>
#include "ns3/config-store.h"

/**
 * @Author Alex Sporni
 * @Date 24.11.2020
 */

using namespace ns3; // ns3 namespace declaration
// main functuion
int main (int argc, char * argv [])
{
	// command line argument parsing
    CommandLine cmd;
    cmd. Parse (argc, argv);
    ConfigStore inputConfig;
    inputConfig.ConfigureDefaults();
    // parse again so you can override default values from the command line
    cmd.Parse(argc, argv);
    
    // this line of code displays the text "Simulation start" string to the standard output
    NS_LOG_UNCOND ("Simulation start.");

    // creating LTE helper object
    Ptr<LteHelper> lteHelper = CreateObject<LteHelper>();
    //This part of the code is necessary to run fading traces usage
    lteHelper->SetFadingModel("ns3::TraceFadingLossModel");
    
    lteHelper->SetFadingModelAttribute("TraceFilename", StringValue ("src/lte/model/fading-traces/fading_trace_EPA_3kmph.fad"));
    lteHelper->SetFadingModelAttribute("TraceLength", TimeValue(Seconds(10.0)));
    lteHelper->SetFadingModelAttribute("SamplesNum", UintegerValue(10000));
    lteHelper->SetFadingModelAttribute("WindowSize", TimeValue(Seconds(0.5)));
    lteHelper->SetFadingModelAttribute("RbNum", UintegerValue(100));
    
//	Creating Node objects for the eNB(s) and the UEs
//  these are empty nodes, the LTE protocol stack is not installed yed
    NodeContainer enbNodes; 
    enbNodes.Create(1);
    NodeContainer ueNodes;
    ueNodes.Create(2);

    // configuring the Mobility model for all the nodes
    //the code bellow will place all nodes at the coordinates (0,0,0).
    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(enbNodes);
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(ueNodes);

    // Installing the LTE protocol stack on the eNB(s)
    NetDeviceContainer enbDevs;
    enbDevs = lteHelper->InstallEnbDevice(enbNodes);

    // Installing the LTE protocol stack on the UEs
    NetDeviceContainer ueDevs;
    ueDevs = lteHelper->InstallUeDevice(ueNodes);

    // this line of code will attach the UEs to the eNB. This will configure each UE
    // according to the eNB configuration, and create an RRC connection between them
    lteHelper->Attach(ueDevs, enbDevs.Get(0));

    // Activating data radio bearer between each UE and the eNB it is attached to
    enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE; // define Qci type
    GbrQosInformation qos;
    qos.gbrDl = 1; // Downlink GBR
    qos.gbrUl = 1; // Uplink GBR
    qos.mbrDl = 1; // Downlink MBR
    qos.mbrUl = 1; // Uplink MBR
    EpsBearer bearer(q, qos);
    lteHelper->ActivateDataRadioBearer(ueDevs, bearer);
    //lteHelper->ActivateDedicatedEpsBearer(ueDevs ,bearer , EpcTft::Default());

    // Setting up the stop timer
    Simulator::Stop(Seconds(0.005));
    lteHelper->EnablePhyTraces();
    
    
    // enabling Tracing
    lteHelper->EnableMacTraces();
    lteHelper->EnableRlcTraces();
    lteHelper->EnablePdcpTraces();
    
    // running the simulation
    Simulator::Run();
    
    // terminating the simulation
    Simulator::Destroy();
    NS_LOG_UNCOND("Simulation stop.");
    return 0;
}