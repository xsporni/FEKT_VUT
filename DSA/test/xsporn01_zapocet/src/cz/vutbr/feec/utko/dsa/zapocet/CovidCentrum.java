package cz.vutbr.feec.utko.dsa.zapocet;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Random;

public class CovidCentrum {
	private Map<String, Osoba> osobyTestovane = new HashMap<>();
	private Map<String, Osoba> osobyInfikovane = new HashMap<>();
	private Queue<Test> testyNevyhodnotene = new LinkedList<Test>();
	
	public void pridajOsobu(String meno, String adresa, String tel, String mail, int vek, Pohlavie pohlavie)
	{
		Osoba osoba = new Osoba(meno, adresa, tel, mail, vek, pohlavie);
		osobyTestovane.put(meno, osoba);
	}
	
	public void pridajTest(Date datum, VysledokTestu vysledok, String vyrobca, TypTestu typ, String menoOsoby ) {
		
		Osoba osoba = osobyTestovane.get(menoOsoby);
		
		if(typ == TypTestu.ANTIGEN) {
			Antigen test = new Antigen(datum, vysledok, vyrobca, osoba);
			testyNevyhodnotene.add(test);
		} else if(typ == TypTestu.PCR) {
			PCR test = new PCR(datum, vysledok, vyrobca, osoba);
			testyNevyhodnotene.add(test);
		}

	}	
	
	public void vypisInfoOsoby() {
		System.out.println("=======================================");
		System.out.println("VSETKY TESTOVANE OSOBY:");
		for(Osoba osoba : osobyTestovane.values()) {
			osoba.vypisINfo();
		}
	}
	
	public void vypisInfoOsobyInfikovane() {
		System.out.println("=======================================");
		System.out.println("INFIKOVANE OSOBY:");
		for(Osoba osoba : osobyInfikovane.values()) {
			System.out.println("Meno: "+ osoba.getMeno());
		}
		System.out.println("=======================================");
	}
	
	public void vyhodnotitTest() {
		Test test = this.testyNevyhodnotene.poll();
		
		test.vysledok = VysledokTestu.randomVysledok();
		Osoba testovanaOsoba = test.osoba;
		testovanaOsoba.setVysledok(test.vysledok);
		testovanaOsoba.setPocetTestov(testovanaOsoba.getPocetTestov() + 1);
		if (test.vysledok == VysledokTestu.POZITIVNY) {
			osobyInfikovane.put(testovanaOsoba.getMeno(), testovanaOsoba);
		} else {
			if(osobyInfikovane.get(testovanaOsoba) == null) {
				osobyInfikovane.remove(testovanaOsoba);
			}
		}
		
		
	}
	
	public void vypisNaklady() {
		int suma = 0;
		for (Test test : testyNevyhodnotene) {
		    suma = suma + test.getCena();
		}
		System.out.println("Naklady na testovanie: " + suma);
	}
	
}
