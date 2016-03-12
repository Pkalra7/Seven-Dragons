#pragma once
#include "actionCard.h"
#include "table.h"

class HareAction : public ActionCard {
public:
	HareAction();
	QueryResult query();
	void perform(Table&, Player*, QueryResult);
};
