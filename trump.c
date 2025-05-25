#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
/*
* 기본적으로 0으로 초기화되고 카드를 받을 시 1 ~ 13 중 값의 값을 취함.
*/
int		hand[2][21] = { 0 }; // 패(딜러는 0, 플레이어는 1) (인덱스로 사용 시 -1 필요)
int		hand_index[2] = { 2, 2 }; // 패의 수
int		sum[2] = { 0 }; // 패의 점수 합
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

int	print_result(void) //int형으로 수정 필요
{
	printf("\n[결과]\n");
	printf("딜러 점수: %d\n", sum[0]);
	printf("플레이어 점수: %d\n", sum[1]);
	if ((check(sum[1], 1) == 2) && (check(sum[0], 0) != 2)) //플레이어가 블랙잭인 경우
	{
		printf("당신의 블랙잭\n");
		return (2);
	}
	else if (check(sum[0], 0) == 2 && check(sum[1], 1) != 2) //딜러가 블랙잭인 경우
	{
		printf("딜러의 블랙잭\n");
		return (-2);
	}
	else if (check(sum[1], 1) == -1) // 플레이어가 버스트인 경우
	{
		printf("당신의 패배\n");
		return (-1);
	}
	else if (check(sum[0], 0) == -1) // 딜러만 버스트인 경우
	{
		printf("당신의 승리\n");
		return (1);
	}
	else if (sum[1] == 21 && sum[0] != 21) // 플레이어의 합만 21인 경우
	{
		printf("당신의 승리\n");
		return (1);
	}
	else if (sum[1] > sum[0]) // 플레이어의 합이 더 21에 가까운 경우
	{
		printf("당신의 승리\n");
		return (1);
	}	
	else if (sum[1] < sum[0]) // 딜러의 합이 21에 더 가까운 경우
	{
		printf("딜러의 승리\n");
		return (-1);
	}
	else // 양쪽이 블랙잭 또는 플레이어가 버스트가 아닌 상황에서 합이 같은 경우 
	{
		printf("무승부\n");
		return (0);
	}
}

int	draw(void) // 카드 뽑기 로직 (1 ~ 13 중 값을 뽑음)
{
	return (1 + rand() % 13);
}

/*
* 2차원 배열을 사용하는 것은 비효울적이라고 판단하여 T로 임시 저장하고, 출력할 때는 10으로 별도 조정
*/

void	print_hand(int hand) //가진 패를 출력하는 함수.
{
	if (hand == 10)
		printf("10 ");
	else
		printf("%c ", trump_card[hand - 1]);
	return ;
}

int	sum_hand(int index) //가진 패의 값을 더하는 함수.
{
	int	number = 0;
	int	count_a = 0;

	for (int i = 0; i < hand_index[index]; i++) // 패에서 0이 나올 때까지 돌림
	{
		int card = hand[index][i];
		number += trump_value[card - 1];
		if (card == 1) // A가 있으면 카운트 증가
			count_a++;
	}
	while (number > 21 && count_a > 0) //만약 A가 있는데, 21을 초과할 시, A를 1로 자동 치환
	{
		number -= 10;
		count_a--;
	}
	return (number);
}


int	player_turn(void) // 플레이어의 턴
{
	char	choice;

	while (1)
	{
		sum[1] = sum_hand(1);
		if (check(sum[1], 1) != 0) //합이 21보다 적은 상황이 아닐 때 종료함.
			return (sum[1]);
		printf("\n카드를 더 뽑으시겠습니까? (y/n): ");
		scanf(" %c", &choice);
		if (choice == 'y' || choice == 'Y') // y를 입력하면 카드를 추가로 뽑음.
		{
			hand[1][hand_index[1]] = draw();
			hand_index[1]++;
			printf("당신의 카드: ");
			for (int i = 0; i < hand_index[1]; i++)
				print_hand(hand[1][i]);
			printf("\n");
		}
		else // 아닐 경우 종료
			break;
	}
	return (sum_hand(1));
}

/*
* 컴퓨터의 턴 (컴퓨터는 17 미만일 경우 반드시 뽑고, 17 이상이면 반드시 뽑지 않는다.)
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
	
	printf("딜러의 카드: ");
	print_hand(hand[0][0]);
	printf("?(%d)\n", hand[0][1]);

	printf("당신의 카드: ");
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
	
	player_turn(); //플레이어의 턴을 수행함.
	cpu_turn(); //cpu의 턴을 수행함.
	
	printf("컴퓨터의 전체 카드: ");
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
	*  랜덤 값 설정 및 시드 값 저장
	*/
	seed = time(NULL);
	srand(seed);

	//printf("시드: %d\n", seed); //디버그용 코드

	money = 1000;
	printf("시작 자금: %d\n", money);

	result = game();
	if (result == 0) // 무승부 시 원금 반환
		money *= 1;
	else if (result == 1) // 일반 승리 시 2배 지급
		money *= 2;
	else if (result == 2) // 블랙잭 승리 시 2.5배 지급
		money *= 2.5;
	else // 패배 시 자금 증발
		money *= 0; 
	printf("최종 자금: %d\n", money);

	return (0);
}