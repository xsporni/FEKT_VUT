package cz.vutbr.feec.dsa.excercise3.xsporn01.pr1;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 8.10.2020
 */

public abstract class GrObjekt {
	
	protected int x_cord;
	protected int y_cord;
	
	
	public GrObjekt(int x_cord, int y_cord) {
		super();
		this.x_cord = x_cord;
		this.y_cord = y_cord;
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


	public abstract void vykresli();

}
