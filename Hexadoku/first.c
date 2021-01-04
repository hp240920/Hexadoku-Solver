#include <stdio.h>
#include <stdlib.h>
#define total 930
int count = 0;
int empty_check[16][16];
int uni_row = 0;
int uni_column = 0;
int hexa_check[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
char hexa_array[16]={'0', '1', '2', '3', '4', '5',  '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

int row_column_grid_check(char** arr, int row, int column, int num) //check
{
	//printf("Hello\n");
	for(int i = 0; i < 16; i++)
  {
	if(arr[row][i] == num)
	{
		return 0;
	}
  }

	for(int i=0; i<16; i++)
{
	if(arr[i][column] == num)
	{
		return 0;
	}
  }

	//int check_grid[4][4];
	int grid_row = row - (row % 4); // we want the lowest and nearest multiple of four
	int grid_column = column - (column % 4);
	for(int i = grid_row; i < (grid_row + 4); i++)

{
	for(int j = grid_column; j < (grid_column + 4); j++)
	{
		if(arr[i][j] == num)
		{
			return 0;
		}
	}
}
return 1;

}

void set_it_to_zero()

{
	for(int i = 0; i < 16; i++)
	{
		hexa_check[i] = 0;
	}
}

void empty_zero()
{

	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			empty_check[i][j] = 0;
		}
	}
}

int oneOrMore(int arr[16])

{
	int count = 0;
	for(int i = 0; i < 16; i++)

	{
		if(arr[i] == 1)
		
		{
			count++;
		}

	}

	if(count == 1) {
	return 1;

	}

	return 0;
}

int indexFinder(int arr[16])
{
	for(int i = 0; i < 16; i++)
	{
		if(arr[i] == 1) {
		return i;
	}
}

return 0;
}

void check_hexa_array(char** arr, int row, int column)
{
	for(int i= 0; i < 16; i++)
	{

	//printf("RC: %d %d\n", row, column);
	if(row_column_grid_check(arr, row, column, hexa_array[i])) {
		hexa_check[i] = 1;
		//printf("%d\n", i);
		}else{
			hexa_check[i] = 0;
		}

	}

}

void set_empty_array(char** arr)

{
	empty_zero(empty_check);
	for(int i = 0; i < 16; i++)

{
	for(int j = 0; j < 16; j++)
	{
		if(arr[i][j] == '-')
		{
			empty_check[i][j] = 1;
		}
	}
}
}

void find_next_empty(int row, int column)

{
	if(row == 0 && column == 0) {
		column = -1;
	}
for(int i = column + 1; i < 16; i++)
	{
	//printf("First\n");
	if(empty_check[row][i] == 1)
		{
			uni_row = row;
			uni_column = i;
			return;
		}
}

for(int i = row + 1; i < 16; i++)
{
	//printf("Second\n");
	for(int j = 0; j < 16; j++)
	{
		if(empty_check[i][j] == 1)
		{
			uni_row = i;
			uni_column = j;
			return;
			}
		}
	}
	//printf("At the end\n");
	uni_row = -1;
	uni_column = -1;
	return;
}

void recursive_call(char** solve_sudo, int row, int column)
{
	//printf("Work\n");
	//printf("Row: %d Column: %d\n", row, column);
	find_next_empty(row, column);
	if(uni_row == -1 || uni_column == -1)
	{
		//printf("I am here\n);
		return;
	}
	
	//printf("Row: %d Column: %d\n", uni_row, uni_column);
	if(solve_sudo[uni_row][uni_column] == '-')
	{

	//printf("Hey\n");
	check_hexa_array(solve_sudo, uni_row, uni_column);
	if(oneOrMore(hexa_check) == 1)
	{

	//printf("Why?\n");
	count++;
	//printf("heyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy\n");
	solve_sudo[uni_row][uni_column] = hexa_array[indexFinder(hexa_check)];

/*

	printf("\n\n");
	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			printf("%c", solve_sudo[i][j]);

		}
		printf("\n");
	}
	
	printf("\n\n");

*/

	set_it_to_zero(hexa_check);
	empty_check[uni_row][uni_column] = 0;
	recursive_call(solve_sudo, 0, 0);
}else{
	//printf("Hello %d %d\n", uni_row, uni_column);
	set_it_to_zero(hexa_check);
	recursive_call(solve_sudo, uni_row, uni_column);
	}
}
}

int check_total(char** arr)
{

	int sum = 0;
	for(int i = 0; i < 16; i++)
	{
		sum = 0;
		for(int j = 0; j < 16; j++)
		{
			sum += arr[i][j];
		}
		if(sum != total) {
		return 0;
		}
	}
	for(int i = 0; i < 16; i++)
	{
		sum = 0;
		for(int j = 0; j < 16; j++)
		{
			sum += arr[j][i];
		}
		if(sum != total) {
		return 0; 
		}
	}
	return 1;
}

void solution_print(char** arr)

{
	/*
	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			if(arr[i][j] == '-')
			{
				printf("no-solution");
				return 0;
			}
		}
	}
	*/

	for(int i = 0; i < 16 ; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			printf("%c\t", arr[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char* argv[])
{

	FILE* f = fopen(argv[1],"r");
	//int check [16];
	for(int i = 0; i < 16; i++)
	{
		//check[i] = 0;
	}
	if(f == NULL)
	{
		return 0;
	}
	char** arr = (char **)malloc(16 * sizeof(char*));
	for(int i = 0; i < 16; i++)
	{
		arr[i] = (char *)malloc(16 * sizeof(char));
	}
	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			char c = '\0';
			fscanf(f, "%c\t", &c);
			arr[i][j] = c;
		}
	}
/*	
	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			printf("%c", arr[i][j]);
		}
		printf("\n");
	}
*/
// starting here
	set_empty_array(arr);
	recursive_call(arr, 0, 0);
	//printf("%d\n\n\n", check_total(arr));
	if(check_total(arr) == 1) {
		solution_print(arr);
	}else{
		printf("no-solution");
	}
	for(int i = 0; i < 16; i++)
	{
		free(arr[i]);
	}

	free(arr);
	fclose(f);
	return 0;
	
 	// TOTAL is always 120
}
	
 
