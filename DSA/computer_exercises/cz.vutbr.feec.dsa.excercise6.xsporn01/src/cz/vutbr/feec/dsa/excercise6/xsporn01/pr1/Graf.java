package cz.vutbr.feec.dsa.excercise6.xsporn01.pr1;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 30.10.2020
 */

import java.util.HashMap;
import java.util.Map;

public class Graf 
{
	
	private Map<String, Vrchol> vrcholyGrafu = new HashMap<>();
	
	public void pridajVrcholy(String odkud, String kam, int cena)
	{
		Vrchol vrchol_odkial = pridajAleboVratExistujuciVrchol(odkud);
		Vrchol vrchol_kam = pridajAleboVratExistujuciVrchol(kam);
		
		// implementovat sposob pridania susedov a vytvorenie vazby
		vrchol_odkial.pridajSuseda(vrchol_kam, cena);
		vrchol_kam.pridajSuseda(vrchol_odkial, cena);
		
		
	}
	
	public Vrchol pridajAleboVratExistujuciVrchol(String nazovVrcholu)
	{
		Vrchol vrchol = vrcholyGrafu.get(nazovVrcholu);
		
		if(vrchol == null)
		{
			vrchol = new Vrchol();
			vrchol.setNazov(nazovVrcholu);
			vrcholyGrafu.put(nazovVrcholu, vrchol);
		}
		return vrchol;
	}
	
	public Vrchol vratVrchol(String nazov)
	{
		Vrchol vrchol = vrcholyGrafu.get(nazov);
		if (vrchol != null)
		{
			return vrchol;
		}
		else
		{
			return null;
		}
		
	}

}
