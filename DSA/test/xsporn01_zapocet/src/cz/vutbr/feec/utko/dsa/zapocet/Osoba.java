package cz.vutbr.feec.utko.dsa.zapocet;

public class Osoba {
	private String meno;
	private String adresa;
	private String tel;
	private String mail;
	private int vek;
	private Pohlavie pohlavie;
	private int pocetTestov;
	private VysledokTestu vysledok;

	public int getPocetTestov() {
		return pocetTestov;
	}


	public void setPocetTestov(int pocetTestov) {
		this.pocetTestov = pocetTestov;
	}


	public void setMeno(String meno) {
		this.meno = meno;
	}


	public VysledokTestu getVysledok() {
		return vysledok;
	}


	public void setVysledok(VysledokTestu vysledok) {
		this.vysledok = vysledok;
	}


	public String getMeno() {
		return meno;
	}

	
	/**
	 * @param meno
	 * @param adresa
	 * @param tel
	 * @param mail
	 * @param vek
	 * @param pohlavie
	 */
	public Osoba(String meno, String adresa, String tel, String mail, int vek, Pohlavie pohlavie) {
		super();
		this.meno = meno;
		this.adresa = adresa;
		this.tel = tel;
		this.mail = mail;
		this.vek = vek;
		this.pohlavie = pohlavie;
		this.pocetTestov = 0;
	}
	
	public void vypisINfo() {
		System.out.println("============================================");
		System.out.println("Meno: "+ this.meno);
		System.out.println("Adresa: "+ this.adresa);
		System.out.println("Tel: "+ this.tel);
		System.out.println("Tel: "+ this.tel);
		System.out.println("Main: "+ this.mail);
		System.out.println("Vek: "+ this.vek);
		System.out.println("Pohlavie: "+ this.pohlavie);
		System.out.println("PocetTestov: "+ this.pocetTestov);
		System.out.println("VysledokPoslednehoTestu: "+ this.vysledok);
	}
}
