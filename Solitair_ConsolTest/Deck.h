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
	bool PushStack(Card * card);	// ���ÿ� ī�带 �ִ´�(�ʱ�ȭ)
	bool BackCard(Card * card);		// ������ ī�带 �ǵ����ִ´�
	Card * FlipCard(void);			// Deck���� ī�带 ���� �����´�
	Card * GetCard(void);			// ������ ī�带 �̵���Ű�����ؼ� �̴´�
};

class DeckB : public CardDeque
{
private:
public:
	DeckB();
	~DeckB();
	bool PutCard(Card * card);		// Deck�� ī�带 �ִ´�
	Card * GetCard(void);			// Deck���� ī�带 �� �� ����
};

class DeckC : public CardDeque
{
private:
public:
	unsigned int HiddenSize;
	DeckC();
	DeckC(CardStack& stack, unsigned char size);
	~DeckC();
	bool PushStack(Card * card);				// �ʱ�ȭ�� ���� ī�� ����
	bool PutCard(Card * card);					// ī�� ����
	Card * GetCard(unsigned int position);	// ī�带 ��
};


#endif  // __DECKA_H__