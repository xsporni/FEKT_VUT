package cz.vutbr.feec.dsa.excercise2.xsporn01.pr1;

import java.util.Vector;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 1.10.2020
 */
public class Main {

	public static void main(String[] args) {
	
	Map new_map = new Map();
	
	Car first_car = new Car("BMW", 10, 20);
	Car second_car = new Car("Peugeot", 30, 40);
	Car third_car = new Car("Mercedes", 50, 60);
	Car fourth_car = new Car("Volkswagen", 70, 80);
	
	new_map.addCar(first_car);
	new_map.addCar(second_car);
	new_map.addCar(third_car);
	new_map.addCar(fourth_car);
	
	System.out.println("Name of the 1st car is: "+ first_car.getName() + "\t\t The X-coordinate is: " + first_car.getX_cord() + "\t The Y-coordinate is: " + first_car.getY_cord());
	System.out.println("Name of the 2st car is: "+ second_car.getName() + "\t\t The X-coordinate is: " + second_car.getX_cord() + "\t The Y-coordinate is: " + second_car.getY_cord());
	System.out.println("Name of the 3st car is: "+ third_car.getName() + "\t The X-coordinate is: " + third_car.getX_cord() + "\t The Y-coordinate is: " + third_car.getY_cord());
	System.out.println("Name of the 4st car is: "+ fourth_car.getName() + "\t The X-coordinate is: " + fourth_car.getX_cord() + "\t The Y-coordinate is: " + fourth_car.getY_cord());
	
	// Via vector
	Vector<Car> vector_of_cars = new Vector<>();
	vector_of_cars.add(new Car("Lada", 90, 100));
	vector_of_cars.add(new Car("Saab", 110, 120));
	vector_of_cars.add(new Car("Kia", 130, 140));
	vector_of_cars.add(new Car("Lotus", 150, 160));
	System.out.println("\nVector implementation");
	System.out.println("Name of the 1st car is: "+ vector_of_cars.get(0).getName() + "\t\t The X-coordinate is: " + vector_of_cars.get(0).getX_cord() + "\t The Y-coordinate is: " + vector_of_cars.get(0).getY_cord());
	System.out.println("Name of the 2nd car is: "+ vector_of_cars.get(1).getName() + "\t\t The X-coordinate is: " + vector_of_cars.get(1).getX_cord() + "\t The Y-coordinate is: " + vector_of_cars.get(1).getY_cord());
	System.out.println("Name of the 3rd car is: "+ vector_of_cars.get(2).getName() + "\t\t The X-coordinate is: " + vector_of_cars.get(2).getX_cord() + "\t The Y-coordinate is: " + vector_of_cars.get(2).getY_cord());
	System.out.println("Name of the 4th car is: "+ vector_of_cars.get(3).getName() + "\t\t The X-coordinate is: " + vector_of_cars.get(3).getX_cord() + "\t The Y-coordinate is: " + vector_of_cars.get(3).getY_cord());
	System.out.println("The total number of cars is: " + vector_of_cars.size());
	
	
	
	
	}

}
