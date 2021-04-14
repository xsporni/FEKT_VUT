package cz.vutbr.feec.dsa.excercise2.xsporn01.pr1;

public class Car {
	
	private String name;
	private int x_cord;
	private int y_cord;
	
	public Car() {
	}
	
	public Car(String name, int x_cord, int y_cord) {
		super();
		this.name = name;
		this.x_cord = x_cord;
		this.y_cord = y_cord;
	}
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public int getX_cord() {
		return x_cord;
	}
	public void setX_cord(int x_cord) {
		this.x_cord = x_cord;
	}
	public int getY_cord() {
		return y_cord;
	}
	public void setY_cord(int y_cord) {
		this.y_cord = y_cord;
	}
	

}