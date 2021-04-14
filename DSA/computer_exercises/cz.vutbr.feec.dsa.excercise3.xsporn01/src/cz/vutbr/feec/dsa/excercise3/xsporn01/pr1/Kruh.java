package cz.vutbr.feec.dsa.excercise3.xsporn01.pr1;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 8.10.2020
 */

public class Kruh extends GrObjekt {
	
	private int polomer;
	
	public Kruh(int x_cord, int y_cord, int polomer) {
		super(x_cord, y_cord);
		this.polomer = polomer;
	}


	@Override
	public void vykresli() {
		System.out.println("Tento objekt je kruh s polomerom: " + polomer + " a lezi na suradniciach x: " + getX_cord() + " a y: " + getY_cord());
		
	}

}
