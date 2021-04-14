package cz.vutbr.feec.dsa.excercise4.xsporn01.pr2;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 14.10.2020
 */

public class Polozka 
{
	private Polozka nasledujucaPolozka;
	private Polozka predchadzajucaPolozka;
	private int data;
	
	public Polozka(Polozka nasledujucaPolozka, Polozka predchadzajucaPolozka, int data) {
		super();
		this.nasledujucaPolozka = nasledujucaPolozka;
		this.predchadzajucaPolozka = predchadzajucaPolozka;
		this.data = data;
	}
	public Polozka getNasledujucaPolozka() {
		return nasledujucaPolozka;
	}
	public void setNasledujucaPolozka(Polozka nasledujucaPolozka) {
		this.nasledujucaPolozka = nasledujucaPolozka;
	}
	public Polozka getPredchadzajucaPolozka() {
		return predchadzajucaPolozka;
	}
	public void setPredchadzajucaPolozka(Polozka predchadzajucaPolozka) {
		this.predchadzajucaPolozka = predchadzajucaPolozka;
	}
	public int getData() {
		return data;
	}
	public void setData(int data) {
		this.data = data;
	}
	
	
	
}
