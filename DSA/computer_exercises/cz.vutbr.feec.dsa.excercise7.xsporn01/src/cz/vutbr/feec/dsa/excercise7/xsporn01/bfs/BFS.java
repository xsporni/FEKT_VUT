package cz.vutbr.feec.dsa.excercise7.xsporn01.bfs;

import java.util.HashSet;
import java.util.LinkedList;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 6.11.2020
 */

public class BFS 
{
	public void najdiRiesenie(Dzban dzban)
	{
		LinkedList<Dzban> open = new LinkedList<>();
		HashSet<Dzban> closed = new HashSet<>();
		
		open.addFirst(dzban);
		while (!open.isEmpty())
		{
			Dzban tmp = open.removeLast();
			if (tmp.jeRiesenie())
			{
				System.out.println("Riesenie sa naslo: " + tmp);
				return;
			}
			for (int i = 1; i <= 6; i++)
			{
				Dzban novyDzban = tmp.klonujANapln(i);
				if (novyDzban != null && !closed.contains(novyDzban))
				{
					open.addFirst(novyDzban);
					closed.add(novyDzban);
				}
			}
		}
		System.out.println("Riesenie neexistuje !");
	}
}
