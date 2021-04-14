package cz.vutbr.feec.dsa.excercise2.xsporn01.pr4;

import java.util.Vector;


public class Node {
	
	private String nodeName; 
	private Vector<Node> neighbour = new Vector<>();
	
	public void AddNeighbour(Node new_neighbour)
	{
		neighbour.add(new_neighbour);
	}
	
	public Node(String name)
	{
		super();
		this.nodeName = name;
	}
	
	public void printNeighbours()
	{
		for (Node node: neighbour)
		{
			System.out.println(node.nodeName);
		}
	}

}
