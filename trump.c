#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int		hand[2][21] = { 0 }; // ��(������ 0, �÷��̾�� 1) (�ε����� ��� �� -1 �ʿ�)
int		hand_index[2] = { 2, 2 };
int		sum[2] = { 0 };
int		trump_value[13] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 }; // ī�尡 ���� ����
char	trump_card[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'K', 'Q', 'J' }; // ī�尡 ǥ�õ� ���

int	check(int sum, int index)
{
	if (sum == 21 && !(hand[index][2])) // ����(ù �� 21)�� ���
		return (2);
	if (sum == 21) // ���� 21�� ���
		return (1);
	else if (sum < 21) // ���� 21 �̸�
		return (0);
	else // ���� 21 �ʰ�
		return (-1);
}

void	print_result(void)
{
	printf("\n[���]\n");
	printf("���� ����: %d\n", sum[0]);
	printf("�÷��̾� ����: %d\n", sum[1]);
	if ((check(sum[1], 1) == 2) && (check(sum[0], 0) != 2))
		printf("����� ����\n");
	else if (check(sum[0], 0) == 2 && check(sum[1], 1) != 2)
		printf("������ ����\n");
	else if (check(sum[1], 1) == -1) // �÷��̾ ����Ʈ�� ���
		printf("����� �й�\n");
	else if (check(sum[0], 0) == -1) // ������ ����Ʈ�� ���
		printf("����� �¸�\n");
	else if (sum[1] == 21 && sum[0] != 21)
		printf("����� �¸�\n");
	else if (sum[1] > sum[0])
		printf("����� �¸�\n");
	else if (sum[1] < sum[0])
		printf("������ �¸�\n");
	else // ������ ����
		printf("���º�\n");
}

int	draw(void) // ī�� �̱� ���� (1 ~ 13 �� ���� ����)
{
	return (1 + rand() % 13);
}

void	print_hand(int hand)
{
	if (hand == 10)
		printf("10 ");
	else
		printf("%c ", trump_card[hand - 1]);
	return ;
}

int	sum_hand(int index)
{
	int	number = 0;

	for (int i = 0; i < hand_index[index]; i++)
		number += trump_value[hand[index][i] - 1];
	return (number);
}

int	player_turn(void)
{
	char	choice;

	while (1)
	{
		sum[1] = sum_hand(1);
		if (check(sum[1], 1) != 0)
			return (sum[1]);
		printf("\nī�带 �� �����ðڽ��ϱ�? (y/n): ");
		scanf(" %c", &choice);
		if (choice == 'y' || choice == 'Y')
		{
			hand[1][hand_index[1]] = draw();
			hand_index[1]++;
			printf("����� ī��: ");
			for (int i = 0; i < hand_index[1]; i++)
				print_hand(hand[1][i]);
			printf("\n");
		}
		else
			break;
	}
	return (sum_hand(1));
}

int	cpu_turn(void)
{
	while (1)
	{
		sum[0] = sum_hand(0);
		if (sum[0] >= 17 || check(sum[0], 0) != 0)
			return (sum[0]);
		hand[0][hand_index[0]] = draw();
		hand_index[0]++;
	}
}


int	game(void) // ���� �¸� �� 0 ��ȯ, �й� �� 1 ��ȯ
{
	/*
	* �÷��̾�� PC�� ī�� 2���� �̰� ������.
	*/
	for (int i = 0; i < 2; i++)
	{
		hand[0][i] = draw();
		hand[1][i] = draw();
	}

	/*
	* PC�� ī�� 1���� �����ϰ�, ������ ī�带 Ȯ����. 
	*/
	
	print_hand(hand[0][0]);
	printf("?(%d)\n", hand[0][1]);

	for (int i = 0; i < 2; i++)
		print_hand(hand[1][i]);
	printf("\n");

	sum[0] = 0;
	sum[1] = 0;

	for (int i = 0; hand[0][i]; i++)
	{
		sum[0] += trump_value[hand[0][i] - 1];
	}
	for (int i = 0; hand[1][i]; i++)
	{
		sum[1] += trump_value[hand[1][i] - 1];
	}
	
	player_turn();
	cpu_turn();
	
	printf("��ǻ���� ��ü ī��: ");
	for (int i = 0; i < hand_index[0]; i++)
		print_hand(hand[0][i]);
	printf("\n");

	print_result();
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