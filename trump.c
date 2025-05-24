#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int		hand[2][21] = { 0 }; // 패(딜러는 0, 플레이어는 1) (인덱스로 사용 시 -1 필요)
int		hand_index[2] = { 2, 2 };
int		sum[2] = { 0 };
int		trump_value[13] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 }; // 카드가 가진 점수
char	trump_card[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'K', 'Q', 'J' }; // 카드가 표시될 모습

int	check(int sum, int index)
{
	if (sum == 21 && !(hand[index][2])) // 블랙잭(첫 턴 21)인 경우
		return (2);
	if (sum == 21) // 합이 21인 경우
		return (1);
	else if (sum < 21) // 합이 21 미만
		return (0);
	else // 합이 21 초과
		return (-1);
}

void	print_result(void)
{
	printf("\n[결과]\n");
	printf("딜러 점수: %d\n", sum[0]);
	printf("플레이어 점수: %d\n", sum[1]);
	if ((check(sum[1], 1) == 2) && (check(sum[0], 0) != 2))
		printf("당신의 블랙잭\n");
	else if (check(sum[0], 0) == 2 && check(sum[1], 1) != 2)
		printf("딜러의 블랙잭\n");
	else if (check(sum[1], 1) == -1) // 플레이어가 버스트인 경우
		printf("당신의 패배\n");
	else if (check(sum[0], 0) == -1) // 딜러가 버스트인 경우
		printf("당신의 승리\n");
	else if (sum[1] == 21 && sum[0] != 21)
		printf("당신의 승리\n");
	else if (sum[1] > sum[0])
		printf("당신의 승리\n");
	else if (sum[1] < sum[0])
		printf("딜러의 승리\n");
	else // 양쪽이 같음
		printf("무승부\n");
}

int	draw(void) // 카드 뽑기 로직 (1 ~ 13 중 값을 뽑음)
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
		printf("\n카드를 더 뽑으시겠습니까? (y/n): ");
		scanf(" %c", &choice);
		if (choice == 'y' || choice == 'Y')
		{
			hand[1][hand_index[1]] = draw();
			hand_index[1]++;
			printf("당신의 카드: ");
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


int	game(void) // 게임 승리 시 0 반환, 패배 시 1 반환
{
	/*
	* 플레이어와 PC가 카드 2장을 뽑고 시작함.
	*/
	for (int i = 0; i < 2; i++)
	{
		hand[0][i] = draw();
		hand[1][i] = draw();
	}

	/*
	* PC는 카드 1장을 공개하고, 본인의 카드를 확인함. 
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
	
	printf("컴퓨터의 전체 카드: ");
	for (int i = 0; i < hand_index[0]; i++)
		print_hand(hand[0][i]);
	printf("\n");

	print_result();
}

int	main(void)
{
	unsigned int	seed;

	/*
	*  랜덤 값 설정 및 시드 값 저장
	*/
	seed = time(NULL);
	srand(seed);

	game();
	return (0);
}