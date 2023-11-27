#include<stdio.h>
#include<string.h>

void draw_sudo(int temp[16])
{
	for(int i = 0; i < 16; i++)
	{
		if(i % 4 == 3)
			printf("%d\n",temp[i]);
		else
			printf("%d ",temp[i]);
	}
	printf("-------------------------\n");
}

int check_has_zero(int temp[16])
{
	for(int i = 0; i < 16; i++)
	{
		if(temp[i] == 0)
			return 1;
	}
	return 0;
}

int check_valid(int temp[16])
{
	//printf("\nnow checking\n");
	int check[5];
	int cur = 0;
	int index_box[] = {0,1,4,5,2,3,6,7,8,9,12,13,10,11,14,15};
	for(int i = 0; i < 4; i++)
	{
		memset(&check, 0,5 * sizeof(int));
		for(int j = 0; j < 4; j++)//check row
		{
			cur = (i * 4) + j;
			if(check[temp[cur]] == 1 && temp[cur] != 0)
				return 0;
			if(check[temp[cur]] == 0)
				check[temp[cur]] = 1;
		}
		memset(&check, 0,5 * sizeof(int));
		for(int j = 0; j < 4; j++)//check col
		{
			cur = i + (j * 4);
			if(check[temp[cur]] == 1 && temp[cur] != 0)
				return 0;
			if(check[temp[cur]] == 0)
				check[temp[cur]] = 1;
		}
		memset(&check, 0,5 * sizeof(int));
		for(int j = 0; j < 4; j++)//check box
		{
			cur = index_box[(i * 4) + j];
			if(check[temp[cur]] == 1 && temp[cur] != 0)
				return 0;
			if(check[temp[cur]] == 0)
				check[temp[cur]] = 1;
		}
	}
	return 1;
}

int main()
{
	int inp[16];
	printf("input: ");
	for(int i = 0; i < 16; i++)
	{
		scanf("%d",&inp[i]);
		if (inp[i] < 0 || inp[i] > 4)
		{
			printf("***please input number 0-4 only***");
			return (1);
		}
	}
	int temp[16];
	memcpy(temp, inp, 64);
	if(check_valid(temp))
		printf("very thing ok\n");
	else
		printf("error\n");
	draw_sudo(temp);

	int ii = 0;
	while (check_has_zero(inp) && check_valid(inp))
	{
		if(ii > 15)
			ii = 0;
		if (inp[ii] == 0)
		{
			while((!check_valid(temp) || temp[ii] == 0) && temp[ii] <= 4)
			{
				temp[ii] += 1;
				if(check_valid(temp))
					printf("\nvery thing ok\n");
				else
					printf("\nerror\n");
				draw_sudo(temp);
			}
			if(temp[ii] == 5)
			{
				temp[ii] = 0;
				ii--;
				while(ii >= 0 && inp[ii] != 0)
				{
					ii--;
				}
				if (ii == -1)
				{
					printf("\nCant Slove sorry...\n");
					return 0;
				}
				else
				{
					temp[ii--] += 1;
				}
				draw_sudo(temp);
			}
		}
		if (!check_has_zero(temp) && check_valid(temp))
		{
			memcpy(inp, temp, 16*sizeof(int));
			printf("\ncomplete\n");
		}
		ii++;
	}
	if (!check_valid(inp))
		printf("it has sth wrong ...cant solve");
	else
		draw_sudo(inp);
	printf("\ncomplete");
	return 0;
}
