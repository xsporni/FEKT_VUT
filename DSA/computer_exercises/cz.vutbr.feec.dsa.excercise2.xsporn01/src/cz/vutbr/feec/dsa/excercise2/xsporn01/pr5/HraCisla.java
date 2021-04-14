package cz.vutbr.feec.dsa.excercise2.xsporn01.pr5;

public class HraCisla {
	
	public static final int HORE = 0;
	public static final int DOLE = 1;
	public static final int DOLAVA = 2;
	public static final int DOPRAVA = 3;
	public int step_counter = 0;
	
	private int pozicia_prazdne_X = 1;
	private int pozicia_prazdne_Y = 1;
	private int[][] matrix = new int[][] {{7,2,4}, {5,0,6}, {8,3,1}};
	

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
	
	public void show_matrix() 
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
