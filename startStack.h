#pragma once
#include "startCard.h"
#include <memory>
#include <deque>

class ActionCard;

class StartStack : public AnimalCard {
	std::deque<std::shared_ptr<ActionCard>> stack;
	std::shared_ptr<StartCard> start;
	int stackSize;
public:
	StartStack();
	StartStack& operator+=(std::shared_ptr<ActionCard>);
	StartStack& operator-=(std::shared_ptr<ActionCard>);
	std::shared_ptr<StartCard> getStartCard();
	void printRow(EvenOdd);
};