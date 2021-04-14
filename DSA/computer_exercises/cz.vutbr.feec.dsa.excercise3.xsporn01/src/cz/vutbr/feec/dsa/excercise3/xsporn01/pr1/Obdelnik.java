package cz.vutbr.feec.dsa.excercise3.xsporn01.pr1;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 8.10.2020
 */

public class Obdelnik extends GrObjekt{

	private int vyska;
	private int sirka;
	
	public Obdelnik(int x_cord, int y_cord, int vyska, int sirka) {
		super(x_cord, y_cord);
		this.vyska = vyska;
		this.sirka = sirka;
	}
	
	@Override
	public void vykresli() {
		System.out.println("Tento objekt je obdelnik s vyskou : " + vyska + " a sirkou: "+ sirka +" a lezi na suradniciach x: " + getX_cord() + " a y: " + getY_cord());
		
	}
}
