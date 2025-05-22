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

int	draw(void) //카드 뽑기 로직 (1 ~ 13 중 값을 뽑음)
{
	return (1 + rand() % 13);
}

void	print_hand(int hand)
{
	char	trump_card[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'K', 'Q', 'J' }; //화면에 표시될 모습

	if (hand == 10)
		printf("%d: 10 ", hand);
	else
		printf("%d: %c ", hand, trump_card[hand - 1]);
	return ;
}

int	game(void) //게임 승리 시 0 반환, 패배 시 1 반환
{
	int	sum[2];
	int	max[2]; // 컴퓨터[0]와 플레이어[1]의 카드 수
	int	my_hand[21] = { 0 }; //플레이어의 패
	int	cpu_hand[21] = { 0 }; //컴퓨터의 패
	int	trump_value[13] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 }; //트럼프 카드가 가진 값

	/*
	* 플레이어와 PC가 카드 2장을 뽑고 시작함.
	*/
	for (int i = 0; i < 2; i++)
	{
		my_hand[i] = draw();
		cpu_hand[i] = draw();
	}

	max[0] = 2;
	max[1] = 2;

	/*
	* PC는 카드 1장을 공개하고, 본인의 카드를 확인함. 
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
	
	printf("합: %d %d\n", sum[0], sum[1]);
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