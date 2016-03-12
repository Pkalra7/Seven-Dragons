#pragma once
#include "animalCard.h"
#include "deck.h"

class AnimalFactory {
private:
	AnimalFactory();
	~AnimalFactory();
	static int count;
	static AnimalFactory *obj;
	std::shared_ptr<AnimalCard> newDeck[51];
public:
	static AnimalFactory* getFactory();
	Deck<AnimalCard>& getDeck();

};