package cz.vutbr.feec.dsa.excercise2.xsporn01.pr4;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 1.10.2020
 */

public class Main {

	public static void main(String[] args) {
		
		Node node1 = new Node("node_one");
		Node node2 = new Node("node_two");
		Node node3 = new Node("node_three");
		Node node4 = new Node("node_four");
		Node node5 = new Node("node_five");
		Node node6 = new Node("node_six");
		
		node1.AddNeighbour(node2);
		node1.AddNeighbour(node4);
		node1.AddNeighbour(node6);
		
		
		node2.AddNeighbour(node1);
		node2.AddNeighbour(node3);
		node2.AddNeighbour(node5);
		
		node5.AddNeighbour(node4);
		
		
		
		System.out.println("Neighbours of node1 are: ");
		node1.printNeighbours();
		
		System.out.println("\nNeighbours of node2 are: ");
		node2.printNeighbours();
		
		System.out.println("\nNeighbours of node5 are: ");
		node5.printNeighbours();
		

		
	}

}
