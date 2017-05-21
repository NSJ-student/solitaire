#ifndef __DECKA_H__
#define __DECKA_H__

#include "Card.h"

#define DECKA_SIZE_MAX	24

class DeckA : public CardDeque
{
private:
	Card * VisibleCard;
	unsigned char FlipNumber;
public:
	DeckA();
	DeckA(CardStack& stack);
	~DeckA();
	bool PushStack(Card * card);	// 스택에 카드를 넣는다(초기화)
	bool BackCard(Card * card);		// 선택한 카드를 되돌려넣는다
	Card * FlipCard(void);			// Deck에서 카드를 한장 뒤집는다
	Card * GetCard(void);			// 뒤집은 카드를 이동시키기위해서 뽑는다
};

class DeckB : public CardDeque
{
private:
public:
	DeckB();
	~DeckB();
	bool PutCard(Card * card);		// Deck에 카드를 넣는다
	Card * GetCard(void);			// Deck에서 카드를 한 장 뺀다
};

class DeckC : public CardDeque
{
private:
public:
	unsigned int HiddenSize;
	DeckC();
	DeckC(CardStack& stack, unsigned char size);
	~DeckC();
	bool PushStack(Card * card);				// 초기화를 위해 카드 넣음
	bool PutCard(Card * card);					// 카드 넣음
	Card * GetCard(unsigned int position);	// 카드를 뺌
};


#endif  // __DECKA_H__