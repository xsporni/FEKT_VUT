package cz.vutbr.feec.dsa.excercise6.xsporn01.pr1;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 30.10.2020
 */

import java.util.HashMap;
import java.util.Map;

public class Vrchol 
{
	private String nazov;
	private Map<Vrchol, Integer> sousede = new HashMap<>();
	
	public String getNazov() 
	{
		return nazov;
	}

	public void setNazov(String nazov) 
	{
		this.nazov = nazov;
	}
	
	
	public void pridajSuseda(Vrchol sused, int cena)
	{
		sousede.put(sused, cena);
	}
	
	public int vratSusedovuCenu(Vrchol vrchol)
	{
		return sousede.get(vrchol);
	}
	
}
