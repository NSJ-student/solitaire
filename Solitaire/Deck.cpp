#include "Deck.h"

using namespace std;


DeckA::DeckA()
{
	VisibleCard = NULL;
	FlipNumber = 0;
}

DeckA::DeckA(CardStack& stack)
{
	int i;
	Card * temp;

	FlipNumber = 0;
	for (i = 0; i < DECKA_SIZE_MAX; i++)
	{
		temp = stack.PopCard();
		if (temp == NULL)
		{
			cout << "DeckA initialize Error: Card Lack\n";
		}
		CardDeque::PushCard_Front(temp);
	}
}

DeckA::~DeckA()
{
	cout << "DeckA Over" << endl;
}

bool DeckA::PushStack(Card * card)
{
	return CardDeque::PushCard_Front(card);
}

Card * DeckA::FlipCard(void)
{
	if (FlipNumber < GroupSize)
	{
		VisibleCard = CardDeque::PopCard_Back();
		CardDeque::PushCard_Front(VisibleCard);
		FlipNumber++;
	}
	else
	{
		VisibleCard = NULL;
		FlipNumber = 0;
	}

	return VisibleCard;
}

Card * DeckA::GetCard(void)
{
	Card * temp;

	temp = CardDeque::PopCard_Front();
	if (temp != NULL)
	{
		FlipNumber--;
		VisibleCard = CardDeque::ShowCard_Front();
	}

	return temp;
}

DeckB::DeckB()
{
}

DeckB::~DeckB()
{
	cout << "DeckB Over" << endl;
}

bool DeckB::PutCard(Card * card)
{
	Card * CurrentTopCard;

	if (card == NULL)
	{
		cout << "입력 실패 / no card" << endl;
		return false;
	}
	if (IsEmpty() && (card->enNumber != CARD_ACE))
	{
		cout << "입력 실패 " << card->enPattern << " / " << card->enNumber << " not ace" << endl;
		return false;
	}
	if (!IsEmpty())
	{
		CurrentTopCard = ShowCard_Front();
		if (CurrentTopCard->enNumber == CARD_KING)
		{
			cout << "입력 실패 " << card->enPattern << " / " << card->enNumber << " deck full" << endl;
			return false;
		}
		if (CurrentTopCard->enPattern != card->enPattern)
		{
			cout << "입력 실패 " << card->enPattern << " / " << card->enNumber << " pattern error" << endl;
			return false;
		}
		if (CurrentTopCard->enNumber + 1 != card->enNumber)
		{
			cout << "입력 실패 " << card->enPattern << " / " << card->enNumber << " number order error" << endl;
			return false;
		}
	}

	return CardDeque::PushCard_Front(card);
}

Card * DeckB::GetCard(void)
{
	return CardDeque::PopCard_Front();
}


DeckC::DeckC(void)
{
	HiddenSize = -1;
}

DeckC::DeckC(CardStack& stack, unsigned char size)
{
	int i;
	Card * temp;

	for (i = 0; i < size; i++)
	{
		temp = stack.PopCard();
		if (temp == NULL)
		{
			cout << "DeckC initialize Error: Card Lack\n";
		}
		CardDeque::PushCard_Front(temp);
	}
	HiddenSize = size - 1;
}

DeckC::~DeckC(void)
{
	cout << "DeckC Over" << endl;
}

bool DeckC::PushStack(Card * card)
{
	bool rvalue;
	rvalue = CardDeque::PushCard_Front(card);
	HiddenSize = GroupSize - 1;

	return rvalue;
}

bool DeckC::PutCard(Card * card)
{
	Card * Tail = CardDeque::ShowCard_Front();

	if (card == NULL)
		return false;

	if (Tail == NULL)
	{
		cout << "deckC: push succeed\n";
		return CardDeque::PushCard_Front(card);
	}
	if ((Tail->enPattern + card->enPattern) & 0x01)		// 색이 다름
	{
		if (Tail->enNumber - 1 == card->enNumber)		// 카드 숫서가 맞음
		{
			cout << "deckC: push succeed\n";
			return CardDeque::PushCard_Front(card);
		}
	}
	cout << "deckC: push fail\n";

	return false;
}

Card * DeckC::GetCard(unsigned int position)
{
	Card * ret;
	if (position + 1 < HiddenSize)	// 선택 카드가 가려진 카드
	{
		cout << "deckC: Hidden\n";
		return NULL;
	}
	if (position + 1 > GroupSize)				// 선택 카드 없음
	{
		cout << "deckC: no select\n";
		return NULL;
	}

	ret = CardDeque::PopCards_Front(GroupSize - 1 - position);
	if (GroupSize == HiddenSize)
	{
		if (CardDeque::ShowCard_Front() != NULL)
		{
			HiddenSize--;
		}
	}

	return ret;
}
