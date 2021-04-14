package cz.vutbr.feec.dsa.excercise4.xsporn01.pr1;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 14.10.2020
 */

public class LinearnyZoznam 
{
	private Polozka prvaPolozka;
	
	public void pridajPrvokNaZaciatok(int data)
	{
		Polozka novaPolozka = new Polozka();
		novaPolozka.setData(data);
		novaPolozka.setDalsiaPolozka(prvaPolozka);
		prvaPolozka = novaPolozka;
	}
	
	public void odstranPrvokZoZaciatku()
	{
		// Pokial zoznam nie je prazdny tak...
		if (prvaPolozka != null )
		{
			// Pokial sa v zozname nachadzaju aspon 2 polozky...
			if (prvaPolozka.getDalsiaPolozka() != null)
			{
				// Nacitam si do premennej 'nasledujucaPolozka' 2. polozku v poradi
				Polozka nasledujucaPolozka = prvaPolozka.getDalsiaPolozka();
				// Aktualizujem premennu 'prvaPolozka' tak, aby ukazovala na druhu
				prvaPolozka = nasledujucaPolozka;
			}
			else // Ak sa mi v zozname nachadza len jedna polozka, mozem ju hned odstranit...
			{
				prvaPolozka = null;
			}
		}
		return;
	}
	
	public boolean obsahujeNejakePolozky()
	{
		// Ak nic neobsahuje vrat false, inak true
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
		// Prehladavame pokial je co prehladavat (kym nenarazime na ukazatel na null)
		while (temp != null) 
		{
			// ak najdeme hladane data vratime true, inak do pomocnej premennej nacitame dalsiu polozku, ktoru znovu overime v cykle atd...
			if(temp.getData() == data)
			{
				return true;
			}
			temp = temp.getDalsiaPolozka();
		}
		// Ak sa nam nepodari najst hladane data, vratime false...
		return false;
		
	}
	
}
