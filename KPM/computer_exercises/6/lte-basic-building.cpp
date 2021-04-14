/* -*- Mode : C++; c-file - style : "gnu "; indent -tabs - mode :nil ; -*- */
/*
* Copyright (c) 2011 -2018 Centre Tecnologic de Telecomunicacions de Catalunya ( CTTC )
*
* This program is free software ; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation;
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
*/

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/lte-module.h"
#include "ns3/config-store.h"
//# include "ns3 /gtk -config - store .h"
#include <ns3/mobility-building-info.h>
#include <ns3/buildings-propagation-loss-model.h>
#include <ns3/building.h>
#include <ns3/buildings-helper.h>
#include <ns3/buildings-module.h>
/*# include <ns3 / buildings - propagation -loss - model .h>
# include <ns3/ building .h>
# include <ns3/ buildings - helper .h>
# include <ns3/ buildings - module .h>
# include <ns3/hybrid - buildings - propagation -loss - model .h>
*/
using namespace ns3;

int main(int argc, char * argv [])
{
    Time simTime = MilliSeconds(1050);
    bool useCa = false ;

    CommandLine cmd;
    cmd.AddValue("simTime","Total duration of the simulation", simTime);
    cmd.AddValue("useCa","Whether to use carrier aggregation.", useCa);
    cmd.Parse(argc, argv);


    ConfigStore inputConfig;
    inputConfig.ConfigureDefaults();

    // Parse again so you can override default values from the command line
    cmd.Parse(argc, argv);

    Ptr<LteHelper>lteHelper = CreateObject<LteHelper>();
    lteHelper->SetAttribute("PathlossModel",StringValue("ns3::BuildingsPropagationLossModel"));

    // Uncomment to enable logging
    // lteHelper -> EnableLogComponents ();

    // Create Nodes : eNodeB and UE
    NodeContainer enbNodes;
    NodeContainer ueNodes;

    // Install Mobility Model
    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    double x_min = 0.0;
    double x_max = 10.0;
    double y_min = 0.0;
    double y_max = 20.0;
    double z_min = 0.0;
    double z_max = 10.0;
    Ptr<Building>b = CreateObject<Building>();
    b->SetBoundaries(Box (x_min , x_max , y_min , y_max , z_min , z_max));
    b->SetBuildingType(Building::Residential);
    b->SetExtWallsType(Building::ConcreteWithWindows);
    b->SetNFloors(3);
    b->SetNRoomsX(3);
    b->SetNRoomsY(2);

    enbNodes.Create(2);
    ueNodes.Create(2);
    mobility.Install(enbNodes);
    BuildingsHelper::Install(enbNodes);
    mobility.Install(ueNodes);
    BuildingsHelper::Install(ueNodes);

    // Create Devices and install them in the Nodes (eNB and UE)
    NetDeviceContainer enbDevs;
    NetDeviceContainer ueDevs;
    // Default scheduler is PF , uncomment to use RR
    // lteHelper -> SetSchedulerType (" ns3 :: RrFfMacScheduler ");

    enbDevs = lteHelper->InstallEnbDevice(enbNodes);
    ueDevs = lteHelper->InstallUeDevice(ueNodes);

    Ptr<ConstantPositionMobilityModel> mm0 = enbNodes.Get(0)->GetObject<ConstantPositionMobilityModel>();
    Ptr<ConstantPositionMobilityModel> mm1 = enbNodes.Get(1)->GetObject<ConstantPositionMobilityModel>();
    mm0->SetPosition(Vector (5.0 , 5.0 , 1.5));
    mm1->SetPosition(Vector (30.0 , 40.0 , 1.5));

    BuildingsHelper::MakeMobilityModelConsistent();

    // Attach a UE to a eNB
    lteHelper->Attach(ueDevs, enbDevs.Get(0));

    // Activate a data radio bearer
    enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
    EpsBearer bearer(q);
    lteHelper->ActivateDataRadioBearer(ueDevs, bearer );
    lteHelper->EnableTraces();

    Simulator::Stop(simTime);
    Simulator::Run();

    // GtkConfigStore config ;
    // config . ConfigureAttributes ();
    NS_LOG_UNCOND("Simulation stop.");
    Simulator::Destroy();
    return 0;
}