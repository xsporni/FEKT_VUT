package cz.vutbr.feec.dsa.excercise3.xsporn01.pr1;

import java.util.Vector;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 8.10.2020
 */

public class Main {

	public static void main(String[] args) {
		
		Platno obj_platno = new Platno();
		Slozenina obj_slozenina = new Slozenina(20, 20, new Vector<>());
		
		
		obj_platno.pridaj_graficky_obejekt(new Obdelnik(420, 690, 140, 90));
		obj_platno.pridaj_graficky_obejekt(new Obdelnik(200, 300, 100, 50));
		obj_platno.pridaj_graficky_obejekt(new Obdelnik(500, 200, 200, 150));
		obj_platno.pridaj_graficky_obejekt(new Kruh(100, 150, 20));
		obj_platno.pridaj_graficky_obejekt(new Kruh(150, 200, 30));
		
		obj_slozenina.vektor_grafic_objektov.add(new Kruh(5, 5, 5));
		obj_slozenina.vektor_grafic_objektov.add(new Kruh(10, 10, 10));
		obj_slozenina.vektor_grafic_objektov.add(new Obdelnik(40, 50, 900, 600));
		
		
		obj_platno.vykresli();
		System.out.println("\n");
		obj_slozenina.vykresli();
		
		
		

	}

}