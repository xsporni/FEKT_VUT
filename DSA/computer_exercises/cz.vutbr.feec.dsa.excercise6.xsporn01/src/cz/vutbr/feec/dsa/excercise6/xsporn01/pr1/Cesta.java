package cz.vutbr.feec.dsa.excercise6.xsporn01.pr1;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 30.10.2020
 */

import java.util.ArrayList;

public class Cesta
{
	// ADT uchovajuci poradie prvkov
	ArrayList<Vrchol> zoznam = new ArrayList<>();
	private int celkovaCenaCesty = 0;
	private Graf graf;
	
	public Cesta(Graf g) 
	{
		super();
		this.graf = g;
	}
	
	public void pridajDielciVrchol(String vrchol)
	{
		 Vrchol temp_vrchol = graf.pridajAleboVratExistujuciVrchol(vrchol);
		 if (temp_vrchol == null)
		 {
			 System.err.println("ERROR, hladany vrchol nie je v grafe !");
		 }
		 else
		 {
			 if (zoznam.isEmpty())
			 {
				 zoznam.add(graf.vratVrchol(vrchol));
				 return;
			 }
			 else
			 {
				 zoznam.add(graf.vratVrchol(vrchol));
				 celkovaCenaCesty += temp_vrchol.vratSusedovuCenu(zoznam.get(zoznam.size()-2));
			 }
		 }
	}
	
	private void iterujCezVrcholy()
	{
		for(Vrchol tempVrchol : this.zoznam)
		{
			System.out.println(" " + tempVrchol.getNazov());
		}
	}
	
	public void vypisInformaceOCeste()
	{
		System.out.println("Celkova cena cesty je: " + celkovaCenaCesty);
		System.out.println("iteruje sa cez vrcholy: ");
		iterujCezVrcholy();
	}
}