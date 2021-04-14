package cz.vutbr.feec.dsa.excercise2.xsporn01.pr3;

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
		
		node1.setLeft(node4);
		node1.setRight(node2);
		
		node2.setLeft(node5);
		node2.setRight(node3);
		
		System.out.println("The name of the node is: "+ node1.getNodeName() + "\t the left node is: "+ node1.getLeft().getNodeName() + "\t the right node is: "+ node1.getRight().getNodeName());
		System.out.println("The name of the node is: "+ node2.getNodeName() + "\t the left node is: "+ node2.getLeft().getNodeName() + "\t the right node is: "+ node2.getRight().getNodeName());
		

	}

}
