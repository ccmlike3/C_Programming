#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int	phase;

int	check(int sum)
{
	if (sum == 21)
		return (1);
	else if (sum < 21)
	{
		return (0);
	}
	else
		return (-1);
}

int	draw(void) //ī�� �̱� ���� (1 ~ 13 �� ���� ����)
{
	return (1 + rand() % 13);
}

void	print_hand(int hand)
{
	char	trump_card[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'K', 'Q', 'J' }; //ȭ�鿡 ǥ�õ� ���

	if (hand == 10)
		printf("%d: 10 ", hand);
	else
		printf("%d: %c ", hand, trump_card[hand - 1]);
	return ;
}

int	game(void) //���� �¸� �� 0 ��ȯ, �й� �� 1 ��ȯ
{
	int	sum[2];
	int	max[2]; // ��ǻ��[0]�� �÷��̾�[1]�� ī�� ��
	int	my_hand[21] = { 0 }; //�÷��̾��� ��
	int	cpu_hand[21] = { 0 }; //��ǻ���� ��
	int	trump_value[13] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 }; //Ʈ���� ī�尡 ���� ��

	/*
	* �÷��̾�� PC�� ī�� 2���� �̰� ������.
	*/
	for (int i = 0; i < 2; i++)
	{
		my_hand[i] = draw();
		cpu_hand[i] = draw();
	}

	max[0] = 2;
	max[1] = 2;

	/*
	* PC�� ī�� 1���� �����ϰ�, ������ ī�带 Ȯ����. 
	*/
	
	print_hand(cpu_hand[0]);
	printf("?(%d)\n", cpu_hand[1]);

	for (int i = 0; i < 2; i++)
		print_hand(my_hand[i]);
	printf("\n");

	sum[0] = 0;
	sum[1] = 0;

	for (int i = 0; cpu_hand[i]; i++)
	{
		sum[0] += trump_value[cpu_hand[i] - 1];
	}
	for (int i = 0; my_hand[i]; i++)
	{
		sum[1] += trump_value[my_hand[i] - 1];
	}
	
	/*
	phase = 0;
	while (1)
	{
		if (!(phase % 2))
		{
			if (check(sum[1]))
			{

			}
		}
		else
		{

		}
			
	}
	*/
	
	printf("��: %d %d\n", sum[0], sum[1]);
}

int	main(void)
{
	unsigned int	seed;

	/*
	*  ���� �� ���� �� �õ� �� ����
	*/
	seed = time(NULL);
	srand(seed);

	game();
	return (0);
}