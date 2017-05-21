#include "Card.h"

using namespace std;
//////////////////////////  각 카드에 대한 클래스

Card::Card(CardPattern pattern, CardNumber number)
{
	enPattern = pattern;
	enNumber = number;
	nextCard = NULL;
	prevCard = NULL;
}

Card::Card(unsigned int index)
{
	enPattern = (CardPattern)(index / 13);
	enNumber = (CardNumber)(index % 13);
	nextCard = NULL;
	prevCard = NULL;
}

Card::~Card()
{
}

unsigned int Card::GetIndex(void)
{
	return (enPattern * 13) + enNumber;
}

string Card::GetPattern(void)
{
	switch (enPattern)
	{
	case CARD_SPADE:	return "!";
	case CARD_CLOVER:	return "/";
	case CARD_DIAMOND:	return "#";
	case CARD_HEART:	return "@";
	default: return NULL;
	}
}

void Card::Console_Print(void)
{
	cout << GetPattern() << enNumber + 1 << " ";
}

//////////////////////////  카드 스택

CardStack::CardStack()
{
	unsigned int stack_cnt, temp;
	Card * Header;

	remain = 0;
	srand((unsigned int)time(NULL));
	temp = rand() % NUMBER_OF_CARD;
	csCardStack = new Card(temp);
	cout << "스택: 카드 생성 -> ";
	cout << temp << endl;

	for (stack_cnt = 0; stack_cnt < NUMBER_OF_CARD - 1; stack_cnt++)
	{
		do
		{
			temp = rand() % NUMBER_OF_CARD;
			Header = csCardStack;
			while (Header != NULL)
			{
				if (Header->GetIndex() == temp)
				{
					temp = NUMBER_OF_CARD;
					break;
				}
				if (Header->nextCard == NULL)
				{
					Header->nextCard = new Card(temp);
					break;
				}
				Header = Header->nextCard;
			}
		} while (temp == NUMBER_OF_CARD);

		cout << stack_cnt;
		cout << " 스택: 카드 생성 -> ";
		cout << temp << endl;
		remain++;
	}
}

CardStack::~CardStack()
{
	Card * Header;

	while (!IsEmpty())
	{
		Header = csCardStack;
		cout << "스택: 카드 소멸 -> ";
		cout << Header->GetIndex() << endl;
		csCardStack = csCardStack->nextCard;
		delete Header;
	}
}

bool CardStack::IsEmpty(void)
{
	return (csCardStack == NULL);
}

Card * CardStack::PopCard(void)
{
	Card * RetCard;

	RetCard = csCardStack;
	csCardStack = csCardStack->nextCard;
	RetCard->prevCard = NULL;
	RetCard->nextCard = NULL;
	remain--;

	return RetCard;
}

//////////////////////////  카드그룹을 관리

CardDeque::CardDeque()
{
	CardBack = NULL;
	CardFront = NULL;
	GroupSize = 0;
	cout << "deck created" << endl;
}

CardDeque::~CardDeque()
{
	Card * temp;

	while (!IsEmpty())
	{
		temp = CardBack;
		cout << "deck card deleted -> ";
		cout << temp->GetIndex() << endl;
		CardBack = CardBack->nextCard;
		delete temp;
	}
}

bool CardDeque::IsEmpty(void)
{
	return (CardBack == NULL);
}

bool CardDeque::PushCard_Front(Card * card)
{
	if (card == NULL)
	{
		return false;
	}
	if (IsEmpty())
	{
		CardBack = card;
		while (card->nextCard != NULL)
		{
			GroupSize++;
			card = card->nextCard;
		}
		CardFront = card;
	}
	else
	{
		CardFront->nextCard = card;
		card->prevCard = CardFront;
		while (card->nextCard != NULL)
		{
			GroupSize++;
			card = card->nextCard;
		}
		CardFront = card;
	}

	GroupSize++;

	return true;
}

Card * CardDeque::PopCard_Front(void)
{
	Card * return_value;

	if (IsEmpty())
	{
		return NULL;
	}
	else
	{
		return_value = CardFront;
		CardFront = CardFront->prevCard;
		return_value->prevCard = NULL;
		if (CardFront == NULL)
		{
			CardBack = NULL;
		}
		else
		{
			CardFront->nextCard = NULL;
		}
		GroupSize--;
		return return_value;
	}
}
/*
Card * CardDeque::PopCard_Front(unsigned char order)
{
Card * return_value;

return_value = CardFront;

while ((return_value != NULL) && (order > 0))
{
return_value = return_value->prevCard;
order--;
}

if (return_value != NULL)
{
GroupSize--;
if (return_value->prevCard != NULL)
{
return_value->prevCard->nextCard = return_value->nextCard;
}
else
{
CardFront = return_value->nextCard;
}
if (return_value->nextCard != NULL)
{
return_value->nextCard->prevCard = return_value->prevCard;
}
else
{
CardBack = return_value->prevCard;
}
return_value->prevCard = NULL;
return_value->nextCard = NULL;
}

return return_value;
}
*/
Card * CardDeque::PopCards_Front(unsigned char order)
{
	Card * return_value;

	return_value = CardFront;

	while ((return_value != NULL) && (order > 0))
	{
		return_value = return_value->prevCard;
		order--;
		GroupSize--;
	}

	if (return_value != NULL)
	{
		GroupSize--;
		CardFront = return_value->prevCard;
		if (CardFront != NULL)	CardFront->nextCard = NULL;
		else					CardBack = CardFront;
		return_value->prevCard = NULL;
	}

	return return_value;
}

Card * CardDeque::ShowCard_Front(void)
{
	return CardFront;
}


bool CardDeque::PushCard_Back(Card * card)
{
	if (card == NULL)
	{
		return false;
	}
	if (IsEmpty())
	{
		CardFront = card;
		while (card->prevCard != NULL)
		{
			GroupSize++;
			card = card->prevCard;
		}
		CardBack = card;
	}
	else
	{
		CardBack->prevCard = card;
		card->nextCard = CardBack;
		while (card->prevCard != NULL)
		{
			GroupSize++;
			card = card->prevCard;
		}
		CardBack = card;
	}

	GroupSize++;

	return true;
}

Card * CardDeque::PopCard_Back(void)
{
	Card * return_value;

	if (IsEmpty())
	{
		return NULL;
	}
	else
	{
		return_value = CardBack;
		CardBack = CardBack->nextCard;
		return_value->nextCard = NULL;
		if (CardBack == NULL)
		{
			CardFront = NULL;
		}
		else
		{
			CardBack->prevCard = NULL;
		}
		GroupSize--;
		return return_value;
	}
}
/*
Card * CardDeque::PopCard_Back(unsigned char order)
{
Card * return_value;

return_value = CardBack;

while ((return_value != NULL) && (order > 0))
{
return_value = return_value->nextCard;
order--;
GroupSize--;
}

if (return_value != NULL)
{
GroupSize--;
if (return_value->prevCard != NULL)
{
return_value->prevCard->nextCard = return_value->nextCard;
}
else
{
CardFront = return_value->nextCard;
}
if (return_value->nextCard != NULL)
{
return_value->nextCard->prevCard = return_value->prevCard;
}
else
{
CardBack = return_value->prevCard;
}
return_value->prevCard = NULL;
return_value->nextCard = NULL;
}

return return_value;
}
*/
Card * CardDeque::PopCards_Back(unsigned char order)
{
	Card * return_value;

	return_value = CardBack;

	while ((return_value != NULL) && (order > 0))
	{
		return_value = return_value->nextCard;
		order--;
		GroupSize--;
	}

	if (return_value != NULL)
	{
		GroupSize--;
		CardBack = return_value->nextCard;
		if (CardBack != NULL)	CardBack->prevCard = NULL;
		else					CardFront = CardBack;
		return_value->nextCard = NULL;
	}

	return return_value;
}

Card * CardDeque::ShowCard_Back(void)
{
	return CardBack;
}

Card * CardDeque::GetCard(unsigned char position)
{
	int i;
	Card * temp = CardBack;

	if (temp == NULL)
		return NULL;

	for (i = 0; (i < position) && (temp != NULL); i++)
	{
		temp = temp->nextCard;
	}
	return temp;
}

void CardDeque::Console_Print(void)
{
	unsigned int i;
	Card * card;
	cout << "[0x" << hex << this << "] ";

	if (GroupSize > 0)
	{
		for (i = 0; i < GroupSize; i++)
		{
			card = CardDeque::GetCard(i);
			cout << card->GetPattern() << card->enNumber + 1 << " ";
			if (i % 10 == 9)
				cout << endl;
		}
	}
	else
	{
		cout << dec << "NULL";
	}
	cout << dec << endl;
}
