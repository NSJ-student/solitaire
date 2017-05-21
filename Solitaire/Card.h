#ifndef __CARD_H__
#define __CARD_H__

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
using namespace std;

#define NUMBER_OF_CARD		(4*13)

#define CARD_HEIGHT			96
#define CARD_WIDTH			71
#define HIDDEN_CARD_GAP		5
#define EXPOSED_CARD_GAP	25
#define SIDE_CARD_GAP_W		20
#define SIDE_CARD_GAP_H		10

#define WINDOW_WIDTH		(7*CARD_WIDTH + 8*SIDE_CARD_GAP_W)
#define WINDOW_HEIGHT		(SIDE_CARD_GAP_H*2 + CARD_HEIGHT*5)



typedef enum card_pattern {
	CARD_DIAMOND,
	CARD_SPADE,
	CARD_HEART,
	CARD_CLOVER
} CardPattern;

typedef enum card_number {
	CARD_ACE,
	CARD_TWO,
	CARD_THREE,
	CARD_FOUR,
	CARD_FIVE,
	CARD_SIX,
	CARD_SEVEN,
	CARD_EIGHT,
	CARD_NINE,
	CARD_TEN,
	CARD_JACK,
	CARD_QUEEN,
	CARD_KING
} CardNumber;

class Card
{
public:
	CardPattern enPattern;
	CardNumber enNumber;
	Card * nextCard;
	Card * prevCard;

	Card(CardPattern pattern, CardNumber number);
	Card(unsigned int index);
	~Card();
	unsigned int GetIndex(void);
	string GetPattern(void);
	void Console_Print(void);
};

class CardStack
{
private:
	Card * csCardStack;
public:
	unsigned char remain;
	CardStack();
	~CardStack();
	bool IsEmpty(void);
	Card * PopCard(void);
};

class CardDeque
{
private:
	Card * CardBack;		// 바닥의 카드	-> 바닥 쪽 카드
	Card * CardFront;		// 맨 윗 카드	-> 유저가 카드는 빼는 쪽

public:
	unsigned int GroupSize;

	CardDeque();
	~CardDeque();
	virtual bool IsEmpty(void);

	virtual bool PushCard_Front(Card * card);
	virtual Card * PopCard_Front(void);
	//virtual Card * PopCard_Front(unsigned char order);
	virtual Card * PopCards_Front(unsigned char order);	// 0이 첫번째, Front으로 뺌
	virtual Card * ShowCard_Front(void);

	virtual bool PushCard_Back(Card * card);
	virtual Card * PopCard_Back(void);
	//virtual Card * PopCard_Back(unsigned char order);
	virtual Card * PopCards_Back(unsigned char order);	// 0이 첫번째, Back으로 뺌
	virtual Card * ShowCard_Back(void);

	Card * GetCard(unsigned char position);

	virtual void Console_Print(void);
};

#endif		// __CARD_H__