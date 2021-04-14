package cz.vutbr.feec.dsa.excercise2.xsporn01.pr2;

public class Packet {
	private int packetID;
	private String packetName;
	
	
	public Packet(int packetID, String packetName) {
		super();
		this.packetID = packetID;
		this.packetName = packetName;
	}
	public int getPacketID() {
		return packetID;
	}
	public void setPacketID(int packetID) {
		this.packetID = packetID;
	}
	public String getPacketName() {
		return packetName;
	}
	public void setPacketName(String packetName) {
		this.packetName = packetName;
	}
	public Packet getNextPacket() {
		return nextPacket;
	}
	public void setNextPacket(Packet nextPacket) {
		this.nextPacket = nextPacket;
	}
	private Packet nextPacket; 

}
