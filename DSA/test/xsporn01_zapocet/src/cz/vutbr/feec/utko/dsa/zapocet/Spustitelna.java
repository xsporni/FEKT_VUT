package cz.vutbr.feec.utko.dsa.zapocet;

import java.util.Date;

public class Spustitelna {

	public static void main(String[] args) {
		CovidCentrum c = new CovidCentrum();
		c.pridajOsobu("Alex Sporni", "Brno 521 00", "13123131", "xsporn01@vutbr.cz", 22, Pohlavie.MUZ);
		c.pridajOsobu("Sporak", "Brno 521 00", "13123131", "xsporn01@vutbr.cz", 22, Pohlavie.MUZ);
		c.pridajOsobu("Alex", "Brno 521 00", "13123131", "xsporn01@vutbr.cz", 22, Pohlavie.MUZ);
		c.pridajOsobu("Krcmery", "Brno 521 00", "13123131", "xsporn01@vutbr.cz", 22, Pohlavie.MUZ);
		c.pridajTest(new Date(Date.UTC(120, 10, 5, 12, 34, 67)), null, "Phieser", TypTestu.ANTIGEN, "Alex Sporni");
		c.pridajTest(new Date(Date.UTC(120, 10, 5, 12, 34, 67)), null, "Phieser", TypTestu.ANTIGEN, "Sporak");
		c.pridajTest(new Date(Date.UTC(120, 10, 5, 12, 34, 67)), null, "Phieser", TypTestu.PCR, "Alex");
		c.pridajTest(new Date(Date.UTC(120, 10, 5, 12, 34, 67)), null, "Phieser", TypTestu.PCR, "Krcmery");
		
		System.out.println("######################################################");
		c.vypisInfoOsoby();
		c.vypisInfoOsobyInfikovane();
		c.vyhodnotitTest();
		c.vyhodnotitTest();
		c.vyhodnotitTest();
		c.vyhodnotitTest();
		System.out.println("######################################################");
		c.vypisInfoOsoby();
		c.vypisInfoOsobyInfikovane();
		System.out.println("######################################################");
		c.vypisNaklady();
	}

}
