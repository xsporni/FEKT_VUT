package cz.vutbr.feec.utko.dsa.zapocet;

import java.util.Date;

public abstract class Test {
	protected Date datum;
	protected VysledokTestu vysledok;
	protected String vyrobca;
	protected Osoba osoba;

	protected abstract int getCena();

	/**
	 * @param datum
	 * @param vysledok
	 * @param vyrobca
	 */
	public Test(Date datum, VysledokTestu vysledok, String vyrobca, Osoba osoba) {
		super();
		this.datum = datum;
		this.vysledok = vysledok;
		this.vyrobca = vyrobca;
		this.osoba = osoba;
	}
	
}
