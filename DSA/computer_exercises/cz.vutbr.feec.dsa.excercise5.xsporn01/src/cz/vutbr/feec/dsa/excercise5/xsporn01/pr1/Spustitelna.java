package cz.vutbr.feec.dsa.excercise5.xsporn01.pr1;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 22.10.2020
 */

public class Spustitelna {

	public static void main(String[] args) 
	{
		BinarnyStrom binStrom = new BinarnyStrom();
		binStrom.pridajHodnotu(10);
		binStrom.pridajHodnotu(4);
		binStrom.pridajHodnotu(7);
		binStrom.pridajHodnotu(13);
		binStrom.pridajHodnotu(11);
		binStrom.pridajHodnotu(15);
		binStrom.pridajHodnotu(2);
		
		binStrom.obsahujeHodnotu(4);
		binStrom.obsahujeHodnotu(13);
		binStrom.obsahujeHodnotu(2);
		
		binStrom.obsahujeHodnotu(55);
		binStrom.obsahujeHodnotu(99);
		binStrom.obsahujeHodnotu(44);
		
		
		

	}

}
