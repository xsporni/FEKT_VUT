package cz.vutbr.feec.dsa.excercise4.xsporn01.pr1;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 14.10.2020
 */

public class Polozka 
{
	private int data;
	private Polozka dalsiaPolozka;
	
	
	public int getData() {
		return data;
	}
	public void setData(int data) {
		this.data = data;
	}
	public Polozka getDalsiaPolozka() {
		return dalsiaPolozka;
	}
	public void setDalsiaPolozka(Polozka dalsiaPolozka) {
		this.dalsiaPolozka = dalsiaPolozka;
	}
}