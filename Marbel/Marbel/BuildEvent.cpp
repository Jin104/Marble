#include "player.h"
#include "buildEvent.h"
#include "start.h"
#include "draw.h"

extern LinkedList *list1, *list2;   //플레이어1,2의 보유지역 연결리스트
extern Player player[2];
extern Local local[32];

void buildBuilding(int turn, int board) {

	//turn=> 플레이어번호 0:player1  1:player2
	//borad=> 플레이어가있는 지역번호
	//state=> 지역의 구매상태 -1: 비어있음 0:player1의 호텔 1:player2의 호텔 2:player1의 랜드마크 3:player2의 랜드마크 4:player1의 관광지 5:player2의 관광지
	//board=> 지역의 특수성   0시작 2보너스게임 4,9,14,18,25관광지 8무인도 12,20,28포츈카드 16올림픽 24세계여행 30국세청
	int answer, answer2;
	int state = local[board].state;
	switch (board)
	{
	case 0:
		break;
	case 2:
		bonusEvent(turn);
		PlayerState();
		break;
	case 8:
		//player[turn].state = 2;
		gotoxytext(34, 30, "무인도 당첨");
		Sleep(500);
		gotoxytext(34, 30, "           ");
		break;
	case 12: case 20: case 28:
		break;
	case 16:
		//OlympicEvent(turn);
		PlayerState();
		break;
	case 24:
		printf("세계여행~~ 다음턴에 원하는곳으로 이동할수있어요.");
		player[turn].state = 3;
		break;
	case 30:
		break;
	default:

		switch (state)
		{
		case -1:   //지역이 비어있을때
			gotoxytext(34, 30, "비어있는 지역입니다. 구매하시겠습니까?");
			gotoxy(48, 31);
			printf("1) YES  2) NO  (선택) ▶ ");
			answer = _getch() - 48;
			gotoxy(80, 31); printf("%d", answer);
			if (answer == 1) {
				if (board != 4 && board != 9 && board != 14 && board != 18 && board != 25) {   //관광지는 제외
					gotoxytext(48, 32, "호텔을 건설했습니다.");
					local[board].state = turn;   //지역의 상태를 바꿔줌
				}
				else {
					gotoxytext(48, 32, "관광지를 구매했습니다.");
					local[board].state = turn + 4;   //지역의 상태를 바꿔줌
				}

				player[turn].marble -= localPrice[board][0];   //보유 마블 감소

				Node *node = NewNode(local[board].name, local[board].price, player[turn].board);   //새로운 지역노드생성
				if (turn == 0) {
					gotoxytext(local[board].x, local[board].y - 2, "△△△");   //건물그림 출력
					HangNode(list1, node);   //플레이어의 리스트에 지역노드를 연결해줌
				}
				else {
					gotoxytext(local[board].x, local[board].y - 2, "▲▲▲");
					HangNode(list2, node);
				}
			}
			break;
		case 0:   //호텔이 지어져있는경우
			if (turn == 0) {
				BuildRandmark(turn, board);
			}
			if (turn == 1) {
				if (local[board].state == 0) {
					gotoxy(34, 30);
					printf("통행료는 %d마블 입니다.", localPrice[board][2]);

					if (player[turn].marble < localPrice[board][2]) {
						Bankrupt(turn, localPrice[board][2]);
					}
					else {
						player[turn].marble -= localPrice[board][2];
					}
					Takeover(turn, board);

					Sleep(300);

				}
				if (local[board].state == 2) {   //랜드마크일때는 인수가 불가능
					gotoxy(34, 30);
					printf("통행료는 %d마블 입니다.", localPrice[board][3]);
					player[turn].marble -= localPrice[board][3];
					Sleep(300);
				}
			}
			break;
		case 1:
			if (turn == 1) {
				BuildRandmark(turn, board);
			}
			if (turn == 0) {
				if (local[board].state == 1) {
					gotoxy(34, 30);
					printf("통행료는 %d마블 입니다.", localPrice[board][2]);
					player[turn].marble -= localPrice[board][2];

					Takeover(turn, board);

					Sleep(300);

				}
				if (local[board].state == 3) {
					gotoxy(34, 30);
					printf("통행료는 %d마블 입니다.", localPrice[board][3]);
					player[turn].marble -= localPrice[board][3];
					Sleep(300);
				}
			}
			break;
		case 2:

			break;
		case 3:

			break;
		case 4:
			if (turn == 1) {
				gotoxy(34, 30);
				printf("통행료는 %d마블 입니다.", localPrice[board][0]);
				player[turn].marble -= localPrice[board][0];
				Sleep(300);
			}
			break;
		case 5:
			if (turn == 0) {
				gotoxy(34, 30);
				printf("통행료는 %d마블 입니다.", localPrice[board][0]);
				player[turn].marble -= localPrice[board][0];
				Sleep(300);
			}
			break;
		default:
			break;
		}

		Sleep(500);
		PlayerState();
		PrintList(list1);
		//clrList();
		PrintList2(list2);
		clrText();

		break;
	}
}

void BuildRandmark(int turn, int board) {
	int answer;
	gotoxytext(34, 30, "랜드마크를 건설하시겠습니까?");
	gotoxy(48, 31);
	printf("1) YES  2) NO  (선택) ▶ ");
	answer = _getch() - 48;
	gotoxy(80, 31); printf("%d", answer);
	if (answer == 1) {
		gotoxytext(48, 32, "랜드마크를 건설했습니다.");
		local[board].state = turn + 1;      //지역의 상태변경
		local[board].price = localPrice[board][3];   //지역의 가격변경
		if (turn == 0) {
			gotoxytext(local[board].x, local[board].y - 2, "♧♧♧");   //랜드마크 모양으로 변경
			player[turn].marble -= localPrice[board][1];   //보유마블 감소
			modifiNode(list1, local[board].name, localPrice[board][3]);
		}
		else {
			gotoxytext(local[board].x, local[board].y - 2, "♣♣♣");
			player[turn].marble -= localPrice[board][1];
			modifiNode(list2, local[board].name, localPrice[board][3]);
		}
	}
}

void Takeover(int turn, int board) {
	int answer;
	if (player[turn].marble > localPrice[board][0]) {   //인수할 돈이 있을때
		gotoxy(34, 31);
		printf("인수하시겠습니까? 인수료는 %d입니다.\n", localPrice[board][0]);
		gotoxy(34, 32);
		printf("1) YES  2) NO  (선택) ▶ ");
		answer = _getch() - 48;
		gotoxy(80, 32); printf("%d", answer);
		if (answer == 1) {
			gotoxytext(34, 33, "인수를 완료했습니다.\n");
			player[turn].marble -= localPrice[board][0];   //보유마블 감소
			player[1 - turn].marble += localPrice[board][0];
			local[board].state = turn;   //지역의 상태 변경
			Node *node = NewNode(local[board].name, local[board].price, player[turn].board);   //지역노드 생성
			if (turn == 0) {
				deletNode(list2, local[board].name);   //상대방의 연결리스트에서 지역노드 삭제
				HangNode(list1, node);   //자신의 연결리스트에 지역노드 연결
				gotoxytext(local[board].x, local[board].y - 2, "▲▲▲");   //건물그림 변경
			}
			else {
				deletNode(list1, local[board].name);
				HangNode(list2, node);
				gotoxytext(local[board].x, local[board].y - 2, "△△△");
			}
			return;
		}
	}
	else {
		gotoxy(34, 31);
		printf("인수할 돈이 부족합니다.\n");
	}
}

//void PayMarble(int turn, int price) {
//
//	int answer,answer2;
//	char name[10];
//
//	gotoxytext(34, 30, "통행료가 부족합니다.\n");
//	gotoxy(70, 30); printf("부족한 마블: %d", price - player[turn].marble);
//	gotoxy(48, 31);
//	printf("1) 매각  2) 파산  (선택) ▶ ");
//	answer = _getch() - 48;
//	gotoxy(80, 31); printf("%d", answer);
//	clrText();
//	if (answer == 1) {
//		gotoxytext(48, 30, "보유한 지역 리스트 입니다.\n");
//		if (turn == 0) {
//			PrintList(list1);
//			while (1) {
//				clrText();
//				gotoxytext(48, 31, "매각할 지역의 이름을 입력하세요: ");
//				gotoxy(48, 32); scanf("%s", name);
//				if (FindNode == NULL) {
//					gotoxy(48, 33);  printf("존재하지 않는 지역입니다.");
//				}
//				else {
//					int marble = deletNode(list1, name);
//					player[turn].marble += marble;
//					gotoxy(70, 30); printf("부족한 마블: %d", price - player[turn].marble);
//					if (list1->size < 1) {
//						gotoxytext(34, 33, "더이상 매각할 지역이 없습니다.");
//						Sleep(500);
//						clrText();
//						return;
//					}
//					gotoxytext(34, 33, "더 매각하시겠습니까?");
//					gotoxy(34, 34);
//					printf("1) YES  2) NO  (선택) ▶ ");
//					answer = _getch() - 48;
//					gotoxy(80, 34); printf("%d", answer);
//					if (answer == 2) {
//						break;
//					}
//				}
//				gotoxytext(34, 33, "파산!!!");
//				Sleep(500);
//				clrText();
//				return;
//			}
//		}
//	}
//	else if(answer == 2) {
//	
//	}
//}