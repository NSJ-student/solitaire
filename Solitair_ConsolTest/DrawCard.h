#pragma once
#include "Card.h"

#define CARD_HEIGHT			96
#define CARD_WIDTH			71
#define HIDDEN_CARD_GAP		5
#define EXPOSED_CARD_GAP	25
#define SIDE_CARD_GAP_W		20
#define SIDE_CARD_GAP_H		10

#define WINDOW_WIDTH		(7*CARD_WIDTH + 8*SIDE_CARD_GAP_W)
#define WINDOW_HEIGHT		(SIDE_CARD_GAP_H*2 + CARD_HEIGHT*5)


class DrawCard
{
public:
	DrawCard();
	~DrawCard();
	void DrawOneCard(Card * card);
	void DrawCards(Card * card);
};

