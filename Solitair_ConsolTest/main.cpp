#include <iostream>
#include "Card.h"
#include "Deck.h"
using namespace std;

int main(void)
{
	unsigned char test;
	unsigned int cnt;
	unsigned int pattern, number;
	CardStack stack = CardStack();
	DeckA deck = DeckA(stack);
	DeckB deck2[4] = { DeckB(), DeckB(), DeckB(), DeckB() };
	DeckC deck3[7] = {	DeckC(stack, 1), DeckC(stack, 2), DeckC(stack, 3), DeckC(stack, 4),
						DeckC(stack, 5), DeckC(stack, 6), DeckC(stack, 7) };
	Card * temp;
	CardDeque * BackDeck = NULL;
	bool result;

	cout << "deckA size : " << deck.GroupSize << endl;
	for (cnt = 0; cnt < 4; cnt++)
		cout << "deckB" << cnt << " size : " << deck2[cnt].GroupSize << endl;
	for (cnt = 0; cnt < 7; cnt++)
		cout << "deckC" << cnt << " size : " << deck3[cnt].GroupSize << endl;

	while (1)
	{
		deck.Console_Print();
		for (cnt = 0; cnt < 4; cnt++)
		{
			cout << cnt << " ";
			deck2[cnt].Console_Print();
		}
		for (cnt = 0; cnt < 7; cnt++)
		{
			cout << deck3[cnt].HiddenSize << " ";
			deck3[cnt].Console_Print();
		}
		cout << "카드 위치 입력(0~8) :";
		cin >> pattern;
		if (pattern > 8)  break;
		if (pattern == 7)
		{
			temp = deck.FlipCard();
			continue;
		}
		cout << "입력 덱 입력(0~3, 4~10) :";
		cin >> number;

		if (pattern < 7)
		{
			cout << "position? : ";
			cin >> cnt;
			temp = deck3[pattern].GetCard(cnt);
			BackDeck = &deck3[pattern];
		}
		if (pattern == 8)
		{
			temp = deck.GetCard();
			BackDeck = &deck;
		}

		if (number < 4)
		{
			result = deck2[number].PutCard(temp);
		}
		else
		{
			result = deck3[number-4].PutCard(temp);
		}
		if (result)
		{
			cout << "입력 성공 ";
			temp->Console_Print();
			cout << endl;
		}
		else
		{
			BackDeck->PushCard_Front(temp);
			cout << "입력 실패 ";
			if (temp == NULL)
				cout << "NULL ";
			else
				temp->Console_Print();
			cout << endl;
		}
	}

	cin >> test;
	

	return 0;
}