package cz.vutbr.feec.dsa.excercise2.xsporn01.pr1;

import java.util.Vector;

public class Map {
	
	private Vector<Car> vector_of_cars = new Vector<>();
	
	public void addCar(Car auto) {
		vector_of_cars.add(auto);
	}
	public Car getCar(int index) {
		return vector_of_cars.elementAt(index);
	}
	public void removeCar(int index) {
		vector_of_cars.remove(index);
	}

	public int getNumberOfCars() {
		return vector_of_cars.size();
	}
	
	

}
