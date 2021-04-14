package cz.vutbr.feec.dsa.excercise2.xsporn01.pr3;

public class Node {
	private Node left;
	private Node right;
	private String nodeName;
	
	
	public Node(String nodeName) {
		super();
		this.nodeName = nodeName;
	}
	
	public Node getLeft() {
		return left;
	}
	public void setLeft(Node left) {
		this.left = left;
	}
	public Node getRight() {
		return right;
	}
	public void setRight(Node right) {
		this.right = right;
	}
	public String getNodeName() {
		return nodeName;
	}
	public void setNodeName(String nodeName) {
		this.nodeName = nodeName;
	}
	
	
	
	
	

}
