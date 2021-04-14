package cz.vutbr.feec.dsa.excercise4.xsporn01.pr2;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 14.10.2020
 */

public class DvojcestneViazanyLinearnyZoznam 
{
	private Polozka prvaPolozka = null;
	private Polozka poslednaPolozka = null;
	
	public void pridajPrvokNaZaciatok(int data)
	{	
		// Pokial je zoznam prazdny, tak vytvorim novy prvok, ktory bude prvy a zaroven posledny
		if (prvaPolozka == null)
		{
			// Do konstruktora predam hodnotu prvej a poslednej premennej, ktore su null
			Polozka novaPolozka = new Polozka(prvaPolozka, poslednaPolozka, data);
			prvaPolozka = novaPolozka;
			poslednaPolozka = novaPolozka;
		}
		else
		{
			Polozka novaPolozka = new Polozka(prvaPolozka, null, data);
			prvaPolozka.setPredchadzajucaPolozka(novaPolozka);
			prvaPolozka = novaPolozka;
			
		}
	}
	
	public void odstranPrvokZoZaciatku()
	{
		// Pokial nie je zoznam prazdny tak...
		if (prvaPolozka != null)
		{
			// Ak sa jedna o zoznam jednej polozky tak...
			if (prvaPolozka.equals(poslednaPolozka))
			{
				// odstranime prvu polozku, ktora je zaroven posledna (zoznam ma 1 polozku)
				prvaPolozka = null;
				poslednaPolozka = null;
			}
			// Ak tych prvkov ma viac...
			else
			{
				// Nastavime premennu nasledujucaPolozka ako prvu
				Polozka nasledujucaPolozka = prvaPolozka.getNasledujucaPolozka();
				nasledujucaPolozka.setPredchadzajucaPolozka(null); 
				prvaPolozka = nasledujucaPolozka;
			}
		}
	}
	
	public void pridajPrvokNaKoniec(int data)
	{
		//zavolame metodu obsahujeNejakePolozky(), ktora nam zisti ci sa v zozname nieco nachadza...
		if (obsahujeNejakePolozky())
		{
			//Ak ano tak, vytvorime novu polozku "novaPolozka", ktorej ukazatel na dalsiu
			// polozku nastavime na null, a ukazatel na predoslu polozku nastavime
			// na doteraz poslednu polozku "psolednaPolozka"
			Polozka novaPolozka = new Polozka(null, poslednaPolozka, data);
			poslednaPolozka.setNasledujucaPolozka(novaPolozka);
			poslednaPolozka = novaPolozka;
		}
		// Ak neobsahuje ziadne polozky tak vytvorime polozku, ktora bude prva a zaroven posledna
		else
		{
			Polozka novaPolozka = new Polozka(prvaPolozka, poslednaPolozka, data);
			prvaPolozka = novaPolozka;
			poslednaPolozka = novaPolozka;
		}
	}
	// Pouzijem opacny princip ako pri odstranPrvokZoZaciatku()
	public void odstranPrvokZKonca()
	{
		if (poslednaPolozka != null)
		{
			// Ak sa v zozname nachadza len 1 polozka, ktora je zaroven prva aj posledna tak..
			if (prvaPolozka.equals(poslednaPolozka))
			{
				// odstrani sa polozka
				prvaPolozka = null;
				poslednaPolozka = null;
			}
			else
			{
				Polozka predchadzajucaPolozka = poslednaPolozka.getPredchadzajucaPolozka();
				predchadzajucaPolozka.setNasledujucaPolozka(null); 
				poslednaPolozka = predchadzajucaPolozka;
			}
		}
	}
	
	public boolean obsahujeNejakePolozky()
	{
		if (prvaPolozka == null)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	
	public boolean obsahujeKonkretnuHodnotu(int data)
	{
		Polozka temp = prvaPolozka;
		while (temp != null)
		{
			if (temp.getData() == data)
			{
				return true;
			}
			temp=temp.getNasledujucaPolozka();
		}
		return false;
		
	}
}