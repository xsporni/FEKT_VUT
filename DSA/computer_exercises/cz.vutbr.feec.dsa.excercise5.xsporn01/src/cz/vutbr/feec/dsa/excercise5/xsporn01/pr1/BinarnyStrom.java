package cz.vutbr.feec.dsa.excercise5.xsporn01.pr1;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 22.10.2020
 */

public class BinarnyStrom {
	
	private Uzol koren;
	
	public void pridajHodnotu(int data)
	{
		if (koren == null)
		{
			Uzol uzol = new Uzol();
			uzol.setData(data);
			koren = uzol;
			return;
		}
			Uzol pomocnaPremenna = koren;
			while (true)
			{
				if (data <= pomocnaPremenna.getData())
				{
					if (pomocnaPremenna.getVlavo() == null)
					{
						Uzol uzol = new Uzol();
						uzol.setData(data);
						pomocnaPremenna.setVlavo(uzol);
						return;
					}
					else
					{
						pomocnaPremenna = pomocnaPremenna.getVlavo();
					}
				}
				else if (data > pomocnaPremenna.getData())
				{
					if (pomocnaPremenna.getVpravo() == null)
					{
						Uzol uzol = new Uzol();
						uzol.setData(data);
						pomocnaPremenna.setVpravo(uzol);
						return;
					}
					else
					{
						pomocnaPremenna = pomocnaPremenna.getVpravo();
					}
				}
				else
				{
					return;
				}
			}
	}
	
	public boolean obsahujeHodnotu(int data)
	{
		if (koren == null)
		{
			System.out.println("Hladana premenna: "+data+" --> nebola najdena !");
			return false;
		}
		Uzol pomocnaPremenna = koren;
		while(true)
		{
			if (pomocnaPremenna == null)
			{
				System.out.println("Hladana premenna: "+data+" --> nebola najdena !");
				return false;
			}
			else if (data > pomocnaPremenna.getData()) //pravo cesta
			{
				pomocnaPremenna = pomocnaPremenna.getVpravo();
			}
			else if (data < pomocnaPremenna.getData())
			{
				pomocnaPremenna = pomocnaPremenna.getVlavo();
			}
			else
			{
				System.out.println("Hladana premenna: "+data+" --> bola najdena !");
				return true;
			}
		}
	}
	

}
