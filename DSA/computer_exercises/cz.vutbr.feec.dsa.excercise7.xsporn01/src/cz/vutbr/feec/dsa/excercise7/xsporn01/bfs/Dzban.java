package cz.vutbr.feec.dsa.excercise7.xsporn01.bfs;

import java.util.ArrayList;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 6.11.2020
 */

public class Dzban 
{
	private int dzban4dc;
	private int dzban3dc;
	private int plnyDzban;
	private int riesenie = 2;
	private int prazdny = 0;
	
	private static int plnyDzban4dc = 4;
	private static int plnyDzban3dc = 3;
	
	private ArrayList<Integer> moznosti = new ArrayList<>();
	
	public Dzban klonujANapln(int moznost)
	{
		Dzban novyDzban = new Dzban();
		
		novyDzban.moznosti.addAll(this.moznosti);
		novyDzban.moznosti.add(moznost);
		
		novyDzban.dzban4dc = this.dzban4dc;
		novyDzban.dzban3dc = this.dzban3dc;
		
		boolean jeToMozne = novyDzban.vyberMoznost(moznost);
		
		if (jeToMozne)
		{
			return novyDzban;
		}
		else
		{
			return null;
		}
	}
	
	public boolean vyberMoznost(int moznost)
	{
		switch(moznost)
		{
		case 1:
			if (dzban4dc == plnyDzban4dc)
			{
				return false;
			}
			else
			{
				dzban4dc = plnyDzban4dc;
				return true;
			}
			
		case 2:
			if (dzban3dc == plnyDzban3dc)
			{
				return false;
			}
			else
			{
				dzban3dc = plnyDzban3dc;				
			}
		case 3:
			if (dzban4dc == prazdny)
			{
				return false;
			}
			else 
			{
				dzban4dc = prazdny;
				return true;
			}
			
		case 4:
			if (dzban3dc == prazdny)
			{
				return false;
			}
			else
			{
				dzban3dc = prazdny;
				return true;
			}
			
		case 5:
			int rozdiel = plnyDzban3dc - dzban3dc;
			if (dzban3dc == plnyDzban3dc || dzban4dc <= rozdiel)
			{
				if ((dzban3dc != plnyDzban3dc) && (dzban4dc != prazdny))
				{
					dzban3dc = dzban3dc + dzban4dc;
					dzban4dc = dzban4dc -dzban4dc;
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				dzban3dc = dzban3dc + rozdiel;
				dzban4dc = dzban4dc - rozdiel;
				return true;
			}
		case 6:
			int rozdiel2 = plnyDzban4dc - dzban4dc;
			if (dzban4dc == plnyDzban4dc || dzban3dc <= rozdiel2)
			{
				return false;
			}
			else
			{
				dzban4dc = dzban4dc + rozdiel2;
				dzban3dc = dzban3dc - rozdiel2;
				return true;
			}
			
		}
		return false;
		
	}

	public int getPlnyDzban() 
	{
		return plnyDzban;
	}

	public void setPlnyDzban(int plnyDzban) 
	{
		this.plnyDzban = plnyDzban;
	}
	
	public boolean jeRiesenie()
	{
		if (dzban4dc == riesenie && dzban3dc == prazdny)
		{
			plnyDzban = dzban4dc;
			return true;
		}
		else if (dzban3dc == riesenie && dzban4dc == prazdny)
		{
			plnyDzban = dzban3dc;
			return true;
		}
		else
		{
			return false;
		}
	}
	
	public int porovnaj(Dzban dzban)
	{
		if ((dzban4dc == dzban.dzban4dc) || (dzban3dc == dzban.dzban3dc))
		{
			return 0;
		}
		else if ((dzban4dc < dzban.dzban4dc) || (dzban3dc < dzban.dzban3dc))
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + dzban3dc;
		result = prime * result + dzban4dc;
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof Dzban))
			return false;
		Dzban other = (Dzban) obj;
		if (dzban3dc != other.dzban3dc)
			return false;
		if (dzban4dc != other.dzban4dc)
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "Dzban [dzban4dc=" + dzban4dc + ", dzban3dc=" + dzban3dc + ", moznosti=" + moznosti + "]";
	}
	
	
	
}
