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

/*
* 게임을 시작할 경우에 이전 게임에서 수정된 사항들을 초기화하는 함수
*/
void init_game()
{
	int	i;
	int	j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (hand[i][j])
		{
			hand[i][j] = 0;
			j++;
		}
		i++;
	}
	
	i = 0;
	while (i < 2)
	{
		hand_index[i] = 2;
		sum[i] = 0;
		i++;
	}
}

/*
* 카드의 값이 유효한지 확인하는 함수.
*/

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

/*
* 게임의 결과를 출력하는 함수
*/

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


/*
* 카드를 뽑는 로직을 가진 함수
*/

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

/*
* 가진 패의 값을 더하는 함수.
*/

int	sum_hand(int index)
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

/*
* 플레이어의 턴을 진행하는 함수
*/
int	player_turn(void)
{
	char	choice; //플레이어의 응답을 저장하는 변수

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
		else if (choice == 'n' || choice == 'N') //n을 입력하면 카드를 추가로 뽑지 않음.
		{
			printf("\n");
			break;
		}
		else //잘못된 값을 처리함.
		{
			printf("잘못된 값입니다.\n\n");
			continue;
		}
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


/*
* 게임을 진행하는 함수 (게임 승리 시 양수 반환, 패배 시 음수 반환, 무승부 시 0 반환)
*/
int	game(void)
{
	init_game(); //전역 변수 초기화 기능
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

	/*
	* 플레이어의 카드 확인
	*/

	printf("당신의 카드: ");
	for (int i = 0; i < 2; i++)
		print_hand(hand[1][i]);
	printf("\n");

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

	return (print_result()); //결과를 출력하고 game 함수 종료
}

int	main(void)
{
	int				result;
	char			choice;
	int				wallet;
	int				money;
	unsigned int	seed;

	/*
	*  랜덤 값 설정 및 시드 값 저장
	*/
	seed = time(NULL);
	srand(seed);

	//printf("시드: %d\n", seed); //디버그용 코드

	wallet = 1000;
	money = 0;
	printf("시작 자금: %u\n", wallet);
	while (1)
	{
		if (wallet == 0) //자금 고갈 시 종료
			break;
		printf("배팅 금액: ");
		scanf("%u", &money);
		if (money <= 0)
		{
			printf("0보다 큰 값을 넣어야 합니다.\n");
			money = 0;
			continue;
		}
		else if (money > wallet)
		{
			printf("소지한 자금보다 큰 금액입니다.\n");
			money = 0;
			continue;
		}
		
		wallet -= money;
		result = game();
		if (result == 0) // 무승부 시 원금 반환
			money *= 1;
		else if (result == 1) // 일반 승리 시 2배 지급
			money *= 2;
		else if (result == 2) // 블랙잭 승리 시 2.5배 지급
			money *= 2.5;
		else // 패배 시 자금 증발
			money *= 0;
		wallet += money;

		if (wallet == 0) // 소지금이 0일 경우 자동 종료
		{
			printf("자금을 소진하여 게임을 종료합니다.\n");
			return (0);
		}

		while (1) // 계속 진행할지 물어봄.
		{
			printf("(현재 자금: %u)\n", wallet);
			printf("게임을 계속 진행하시겠습니까? (y/n)");
			scanf(" %c", &choice);
			if (choice == 'y' || choice == 'Y')
				break;
			else if (choice == 'n' || choice == 'N')
			{
				printf("최종 자금: %u\n", wallet);
				return (0);
			}
			else
			{
				printf("잘못된 값입니다.\n\n");
			}
		}
	}
	printf("최종 자금: %u\n", wallet);

	return (0);
}