package cz.vutbr.feec.utko.dsa.zapocet;

import java.util.Date;
import java.util.Random;

public class PCR extends Test{
	private int dobaVyhodnoteniaHod;
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
	public PCR(Date datum, VysledokTestu vysledok, String vyrobca, Osoba osoba) {
		super(datum, vysledok, vyrobca, osoba);
		// TODO Auto-generated constructor stub
		this.cena = 1700;
		Random random = new Random();
		this.dobaVyhodnoteniaHod = random.nextInt(96 - 12) + 12;
	}
	
	public void vypisINfo() {
		System.out.println("============================================");
		System.out.println("Datum: "+ this.datum);
		System.out.println("Vysledok: "+ this.vysledok);
		System.out.println("Vyrobca: "+ this.vyrobca);
		System.out.println("Cena: "+ this.cena);
		System.out.println("Doba Vyhodnotenia: "+ this.dobaVyhodnoteniaHod);
	}
	
}
