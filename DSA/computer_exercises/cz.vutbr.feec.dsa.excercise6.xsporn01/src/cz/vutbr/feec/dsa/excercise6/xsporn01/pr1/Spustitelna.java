package cz.vutbr.feec.dsa.excercise6.xsporn01.pr1;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 30.10.2020
 */

public class Spustitelna 
{

	public static void main(String[] args) 
	{
		Graf g = new Graf();
		Cesta c = new Cesta(g);
		// vrchol 1
		g.pridajVrcholy("1", "2", 4);
		g.pridajVrcholy("1", "6", 6);
		g.pridajVrcholy("1", "7", 16);
		// vrchol 2
		g.pridajVrcholy("2", "3", 24);
		g.pridajVrcholy("2", "3", 24);
		// vrchol 6 
		g.pridajVrcholy("6", "3", 23);
		g.pridajVrcholy("6", "5", 5);
		g.pridajVrcholy("6", "1", 6);
		g.pridajVrcholy("6", "7", 8);
		// vrchol 7
		g.pridajVrcholy("7", "8", 21);
		g.pridajVrcholy("7", "1", 16);
		g.pridajVrcholy("7", "6", 8);
		g.pridajVrcholy("7", "5", 10);
		// vrchol 3
		g.pridajVrcholy("3", "4", 9);
		g.pridajVrcholy("3", "5", 18);
	    g.pridajVrcholy("3", "6", 23);
	    g.pridajVrcholy("3", "2", 24);
		// vrchol 5
		g.pridajVrcholy("5", "4", 11);
		g.pridajVrcholy("5", "8", 14);
		g.pridajVrcholy("5", "3", 18);
		g.pridajVrcholy("5", "6", 5);
        g.pridajVrcholy("5", "7", 10);
		// vrchol 4
		g.pridajVrcholy("4", "8", 7);
		g.pridajVrcholy("4", "3", 9);
        g.pridajVrcholy("4", "5", 11);
        // vrchol 8 
        g.pridajVrcholy("8", "4", 7);
        g.pridajVrcholy("8", "7", 21);
        g.pridajVrcholy("8", "5", 14);
		
        // najvyhodnejsia cesta z bodu 1 do bodu 3
		c.pridajDielciVrchol("1");
		c.pridajDielciVrchol("6");
		c.pridajDielciVrchol("5");
		c.pridajDielciVrchol("4");
		c.pridajDielciVrchol("3");
		
		c.vypisInformaceOCeste();
	}
}