package cz.vutbr.feec.dsa.excercise3.xsporn01.pr2;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 9.10.2020
 */

public class Main {

	public static void main(String[] args) {
		HraCisla hra = new HraCisla();
		HraCisla hra2 = new HraCisla();
		
		System.out.println("Pociatocny stav herneho pola:");
		hra.show_matrix();
		
		System.out.println("Posun vlavo:");
		hra.posun(HraCisla.DOLAVA);
		hra.show_matrix();

		System.out.println("Posun hore:");
		hra.posun(HraCisla.HORE);
		hra.show_matrix();
		
		System.out.println("Posun dole:");
		hra.posun(HraCisla.DOLE);
		hra.show_matrix();
		
		hra.hash_mnoz.add(hra);
		hra.hash_mnoz.add(hra); //nic sa nestale lebo sa jedna o rovnaky prvok
		hra.hash_mnoz.add(hra2);
		
		System.out.println("Pocet prvkov v mnozine: " + hra.hash_mnoz.size());
		
	}

}
