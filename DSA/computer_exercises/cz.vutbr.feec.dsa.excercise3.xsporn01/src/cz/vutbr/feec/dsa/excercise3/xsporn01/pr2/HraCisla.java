package cz.vutbr.feec.dsa.excercise3.xsporn01.pr2;

/**
 * 
 * @author Alex Sporni | xsporn01@stud.feec.vutbr.cz
 * @date 9.10.2020
 */

import java.util.Arrays;
import java.util.HashSet;

public class HraCisla {
	
	public static final int HORE = 0;
	public static final int DOLE = 1;
	public static final int DOLAVA = 2;
	public static final int DOPRAVA = 3;
	public int step_counter = 0;
	
	private int pozicia_prazdne_X = 1;
	private int pozicia_prazdne_Y = 1;
	private int[][] matrix = new int[][] {{7,2,4}, {5,0,6}, {8,3,1}};
	
	HashSet<HraCisla> hash_mnoz = new HashSet<HraCisla>();
	

	public void posun(int smer) {
		if(smer == HORE) 
		{
			matrix[pozicia_prazdne_Y][pozicia_prazdne_X] = matrix[pozicia_prazdne_Y - 1][pozicia_prazdne_X]; 
			matrix[pozicia_prazdne_Y - 1][pozicia_prazdne_X] = 0; 
			pozicia_prazdne_Y--;
			step_counter++;
		}
		else if (smer == DOLE)
		{
			matrix[pozicia_prazdne_Y][pozicia_prazdne_X] = matrix[pozicia_prazdne_Y + 1][pozicia_prazdne_X]; 
			matrix[pozicia_prazdne_Y + 1][pozicia_prazdne_X] = 0; 
			pozicia_prazdne_Y++;
			step_counter++;
		}
		else if (smer == DOLAVA)
		{
			matrix[pozicia_prazdne_Y][pozicia_prazdne_X] = matrix[pozicia_prazdne_Y][pozicia_prazdne_X - 1]; 
			matrix[pozicia_prazdne_Y][pozicia_prazdne_X - 1] = 0; 
			pozicia_prazdne_X--;
			step_counter++;
		}
		else if (smer == DOPRAVA)
		{
			matrix[pozicia_prazdne_Y][pozicia_prazdne_X] = matrix[pozicia_prazdne_Y][pozicia_prazdne_X + 1]; 
			matrix[pozicia_prazdne_Y][pozicia_prazdne_X + 1] = 0; 
			pozicia_prazdne_X++;
			step_counter++;
		}
				
				
	}
	
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + Arrays.deepHashCode(matrix);
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		HraCisla other = (HraCisla) obj;
		if (!Arrays.deepEquals(matrix, other.matrix))
			return false;
		return true;
	}

 void show_matrix() 
	{
		for (int i = 0; i < 3; i++) 
		{
			for (int j = 0; j < 3; j++) 
			{
				System.out.print(matrix[i][j]);
				System.out.print(" ");
			}
			System.out.println();
		}
		
		System.out.println();
	}
	
}
