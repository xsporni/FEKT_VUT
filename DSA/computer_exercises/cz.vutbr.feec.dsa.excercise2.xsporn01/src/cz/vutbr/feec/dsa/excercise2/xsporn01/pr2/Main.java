package cz.vutbr.feec.dsa.excercise2.xsporn01.pr2;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 1.10.2020
 */

public class Main {

	public static void main(String[] args) {
		Packet packet_1 = new Packet(1, "firstPacket");
		Packet packet_2 = new Packet(2, "secondPacket");
		Packet packet_3 = new Packet(3, "thirdPacket");
		Packet packet_4 = new Packet(4, "fourthPacket");
		
		packet_1.setNextPacket(packet_2);
		packet_2.setNextPacket(packet_3);
		packet_3.setNextPacket(packet_4);
		// If we want to connect the last packet to the first we can set the next packet of packet_4 to packet_1
		packet_4.setNextPacket(packet_1);
		
		System.out.println("The ID of the first packet is: "+ packet_1.getPacketID() + "\t the name of the packet is: "+ packet_1.getPacketName() + "\t\t and the next packet is: "+ packet_1.getNextPacket().getPacketName());
		System.out.println("The ID of the second packet is: "+ packet_2.getPacketID() + "\t the name of the packet is: "+ packet_2.getPacketName() + "\t and the next packet is: "+ packet_2.getNextPacket().getPacketName());
		System.out.println("The ID of the third packet is: "+ packet_3.getPacketID() + "\t the name of the packet is: "+ packet_3.getPacketName() + "\t\t and the next packet is: "+ packet_3.getNextPacket().getPacketName());
		System.out.println("The ID of the fourth packet is: "+ packet_4.getPacketID() + "\t the name of the packet is: "+ packet_4.getPacketName() + "\t and the next packet is: "+ packet_4.getNextPacket().getPacketName());
		
		

	}

}
