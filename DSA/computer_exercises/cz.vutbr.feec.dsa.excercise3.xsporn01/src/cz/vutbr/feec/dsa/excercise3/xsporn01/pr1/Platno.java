package cz.vutbr.feec.dsa.excercise3.xsporn01.pr1;

import java.util.Vector;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 8.10.2020
 */

public class Platno {
	
	Vector<GrObjekt> vektor_grafic_objektov = new Vector<>();
	
	
	public void pridaj_graficky_obejekt(GrObjekt novy_objekt)
	{
		vektor_grafic_objektov.add(novy_objekt);
	}
	
	public void vykresli() {
		for(GrObjekt graf_obj: vektor_grafic_objektov)
		{
			graf_obj.vykresli();
		}
	}

}
