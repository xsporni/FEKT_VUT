package cz.vutbr.feec.dsa.excercise2.xsporn01.pr5;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 1.10.2020
 */

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		HraCisla hra = new HraCisla();
		
		System.out.println("Pociatocny stav herneho pola:");
		hra.show_matrix();
		
		System.out.println("Posun vlavo:");
		hra.posun(HraCisla.DOLAVA);
		hra.show_matrix();
		
		System.out.println("Posun hore:");
		hra.posun(HraCisla.HORE);
		hra.show_matrix();
		
		System.out.println("Posun vpravo:");
		hra.posun(HraCisla.DOPRAVA);
		hra.show_matrix();
		
		System.out.println("Posun dole:");
		hra.posun(HraCisla.DOLE);
		hra.show_matrix();
		
		System.out.println("Posun dole:");
		hra.posun(HraCisla.DOLE);
		hra.show_matrix();
		
		System.out.println("Posun vlavo:");
		hra.posun(HraCisla.DOLAVA);
		hra.show_matrix();
		
		System.out.println("Posun hore:");
		hra.posun(HraCisla.HORE);
		hra.show_matrix();
		
		System.out.println("Posun vpravo:");
		hra.posun(HraCisla.DOPRAVA);
		hra.show_matrix();
		
		System.out.println("Posun vpravo:");
		hra.posun(HraCisla.DOPRAVA);
		hra.show_matrix();
		
		System.out.println("Posun hore:");
		hra.posun(HraCisla.HORE);
		hra.show_matrix();
		
		System.out.println("Posun vlavo:");
		hra.posun(HraCisla.DOLAVA);
		hra.show_matrix();
		
		System.out.println("Posun vlavo:");
		hra.posun(HraCisla.DOLAVA);
		hra.show_matrix();
		
		System.out.println("Posun dole:");
		hra.posun(HraCisla.DOLE);
		hra.show_matrix();
		
		System.out.println("Posun vpravo:");
		hra.posun(HraCisla.DOPRAVA);
		hra.show_matrix();
		
		System.out.println("Posun vpravo:");
		hra.posun(HraCisla.DOPRAVA);
		hra.show_matrix();
		
		System.out.println("Posun dole:");
		hra.posun(HraCisla.DOLE);
		hra.show_matrix();
		
		System.out.println("Posun vlavo:");
		hra.posun(HraCisla.DOLAVA);
		hra.show_matrix();
		
		System.out.println("Posun vlavo:");
		hra.posun(HraCisla.DOLAVA);
		hra.show_matrix();
		
		System.out.println("Posun hore:");
		hra.posun(HraCisla.HORE);
		hra.show_matrix();
		
		System.out.println("Posun vpravo:");
		hra.posun(HraCisla.DOPRAVA);
		hra.show_matrix();
		
		System.out.println("Posun vpravo:");
		hra.posun(HraCisla.DOPRAVA);
		hra.show_matrix();
		
		System.out.println("Posun hore:");
		hra.posun(HraCisla.HORE);
		hra.show_matrix();
		
		System.out.println("Posun vlavo:");
		hra.posun(HraCisla.DOLAVA);
		hra.show_matrix();
		
		System.out.println("Posun dole:");
		hra.posun(HraCisla.DOLE);
		hra.show_matrix();
		
		System.out.println("Posun vlavo:");
		hra.posun(HraCisla.DOLAVA);
		hra.show_matrix();
		
		System.out.println("Posun hore:");
		hra.posun(HraCisla.HORE);
		hra.show_matrix();
		
		System.out.println("Pocet krokov k spravnemu rieseniu: "+ hra.step_counter);


	}

}
