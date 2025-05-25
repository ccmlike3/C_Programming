#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
/*
* �⺻������ 0���� �ʱ�ȭ�ǰ� ī�带 ���� �� 1 ~ 13 �� ���� ���� ����.
*/
int		hand[2][21] = { 0 }; // ��(������ 0, �÷��̾�� 1) (�ε����� ��� �� -1 �ʿ�)
int		hand_index[2] = { 2, 2 }; // ���� ��
int		sum[2] = { 0 }; // ���� ���� ��
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

int	print_result(void) //int������ ���� �ʿ�
{
	printf("\n[���]\n");
	printf("���� ����: %d\n", sum[0]);
	printf("�÷��̾� ����: %d\n", sum[1]);
	if ((check(sum[1], 1) == 2) && (check(sum[0], 0) != 2)) //�÷��̾ ������ ���
	{
		printf("����� ����\n");
		return (2);
	}
	else if (check(sum[0], 0) == 2 && check(sum[1], 1) != 2) //������ ������ ���
	{
		printf("������ ����\n");
		return (-2);
	}
	else if (check(sum[1], 1) == -1) // �÷��̾ ����Ʈ�� ���
	{
		printf("����� �й�\n");
		return (-1);
	}
	else if (check(sum[0], 0) == -1) // ������ ����Ʈ�� ���
	{
		printf("����� �¸�\n");
		return (1);
	}
	else if (sum[1] == 21 && sum[0] != 21) // �÷��̾��� �ո� 21�� ���
	{
		printf("����� �¸�\n");
		return (1);
	}
	else if (sum[1] > sum[0]) // �÷��̾��� ���� �� 21�� ����� ���
	{
		printf("����� �¸�\n");
		return (1);
	}	
	else if (sum[1] < sum[0]) // ������ ���� 21�� �� ����� ���
	{
		printf("������ �¸�\n");
		return (-1);
	}
	else // ������ ���� �Ǵ� �÷��̾ ����Ʈ�� �ƴ� ��Ȳ���� ���� ���� ��� 
	{
		printf("���º�\n");
		return (0);
	}
}

int	draw(void) // ī�� �̱� ���� (1 ~ 13 �� ���� ����)
{
	return (1 + rand() % 13);
}

/*
* 2���� �迭�� ����ϴ� ���� ��ȿ�����̶�� �Ǵ��Ͽ� T�� �ӽ� �����ϰ�, ����� ���� 10���� ���� ����
*/

void	print_hand(int hand) //���� �и� ����ϴ� �Լ�.
{
	if (hand == 10)
		printf("10 ");
	else
		printf("%c ", trump_card[hand - 1]);
	return ;
}

int	sum_hand(int index) //���� ���� ���� ���ϴ� �Լ�.
{
	int	number = 0;
	int	count_a = 0;

	for (int i = 0; i < hand_index[index]; i++) // �п��� 0�� ���� ������ ����
	{
		int card = hand[index][i];
		number += trump_value[card - 1];
		if (card == 1) // A�� ������ ī��Ʈ ����
			count_a++;
	}
	while (number > 21 && count_a > 0) //���� A�� �ִµ�, 21�� �ʰ��� ��, A�� 1�� �ڵ� ġȯ
	{
		number -= 10;
		count_a--;
	}
	return (number);
}


int	player_turn(void) // �÷��̾��� ��
{
	char	choice;

	while (1)
	{
		sum[1] = sum_hand(1);
		if (check(sum[1], 1) != 0) //���� 21���� ���� ��Ȳ�� �ƴ� �� ������.
			return (sum[1]);
		printf("\nī�带 �� �����ðڽ��ϱ�? (y/n): ");
		scanf(" %c", &choice);
		if (choice == 'y' || choice == 'Y') // y�� �Է��ϸ� ī�带 �߰��� ����.
		{
			hand[1][hand_index[1]] = draw();
			hand_index[1]++;
			printf("����� ī��: ");
			for (int i = 0; i < hand_index[1]; i++)
				print_hand(hand[1][i]);
			printf("\n");
		}
		else // �ƴ� ��� ����
			break;
	}
	return (sum_hand(1));
}

/*
* ��ǻ���� �� (��ǻ�ʹ� 17 �̸��� ��� �ݵ�� �̰�, 17 �̻��̸� �ݵ�� ���� �ʴ´�.)
*/

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
	
	printf("������ ī��: ");
	print_hand(hand[0][0]);
	printf("?(%d)\n", hand[0][1]);

	printf("����� ī��: ");
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
	
	player_turn(); //�÷��̾��� ���� ������.
	cpu_turn(); //cpu�� ���� ������.
	
	printf("��ǻ���� ��ü ī��: ");
	for (int i = 0; i < hand_index[0]; i++)
		print_hand(hand[0][i]);
	printf("\n");

	return (print_result());
}

int	main(void)
{
	int				money;
	int				result;
	unsigned int	seed;

	/*
	*  ���� �� ���� �� �õ� �� ����
	*/
	seed = time(NULL);
	srand(seed);

	//printf("�õ�: %d\n", seed); //����׿� �ڵ�

	money = 1000;
	printf("���� �ڱ�: %d\n", money);

	result = game();
	if (result == 0) // ���º� �� ���� ��ȯ
		money *= 1;
	else if (result == 1) // �Ϲ� �¸� �� 2�� ����
		money *= 2;
	else if (result == 2) // ���� �¸� �� 2.5�� ����
		money *= 2.5;
	else // �й� �� �ڱ� ����
		money *= 0; 
	printf("���� �ڱ�: %d\n", money);

	return (0);
}