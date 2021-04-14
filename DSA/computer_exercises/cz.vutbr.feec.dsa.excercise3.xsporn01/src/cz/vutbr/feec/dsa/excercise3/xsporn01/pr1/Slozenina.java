package cz.vutbr.feec.dsa.excercise3.xsporn01.pr1;

import java.util.Vector;


/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 8.10.2020
 */

public class Slozenina extends GrObjekt {
	
	Vector<GrObjekt> vektor_grafic_objektov = new Vector<>();

	public Slozenina(int x_cord, int y_cord, Vector<GrObjekt> vektor_grafic_objektov) {
		super(x_cord, y_cord);
		this.vektor_grafic_objektov = vektor_grafic_objektov;
	}

	@Override
	public void vykresli() {
		System.out.println("Vykresluje sa slozenina na suradnice x: " + x_cord + " a y:"+ y_cord);
		for(GrObjekt graf_obj : vektor_grafic_objektov)
		{
			System.out.println("V slozenine sa nachadzaju objekty: ");
			graf_obj.vykresli();
		}
		
	}
	

}
