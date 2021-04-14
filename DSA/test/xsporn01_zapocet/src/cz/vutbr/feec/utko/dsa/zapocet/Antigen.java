package cz.vutbr.feec.utko.dsa.zapocet;

import java.util.Date;
import java.util.Random;

public class Antigen extends Test {
	private int cena;

	public int getCena() {
		return cena;
	}

	public void setCena(int cena) {
		this.cena = cena;
	}

	/**
	 * @param datum
	 * @param vysledok
	 * @param vyrobca
	 */
	public Antigen(Date datum, VysledokTestu vysledok, String vyrobca, Osoba osoba) {
		super(datum, vysledok, vyrobca, osoba);
		// TODO Auto-generated constructor stub
		Random random = new Random();
		this.cena = random.nextInt(700 - 300) + 300;
	}
	
	public void vypisINfo() {
		System.out.println("============================================");
		System.out.println("Datum: "+ this.datum);
		System.out.println("Vysledok: "+ this.vysledok);
		System.out.println("Vyrobca: "+ this.vyrobca);
		System.out.println("Cena: "+ this.cena);
	}
	
	
}
