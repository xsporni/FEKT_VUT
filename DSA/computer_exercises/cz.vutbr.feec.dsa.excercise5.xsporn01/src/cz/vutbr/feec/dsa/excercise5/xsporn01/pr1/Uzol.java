package cz.vutbr.feec.dsa.excercise5.xsporn01.pr1;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 22.10.2020
 */

public class Uzol {
	
	private int data;
	private Uzol vpravo;
	private Uzol vlavo;
	
	
	public int getData() {
		return data;
	}
	public void setData(int data) {
		this.data = data;
	}
	public Uzol getVpravo() {
		return vpravo;
	}
	public void setVpravo(Uzol vpravo) {
		this.vpravo = vpravo;
	}
	public Uzol getVlavo() {
		return vlavo;
	}
	public void setVlavo(Uzol vlavo) {
		this.vlavo = vlavo;
	}

}
