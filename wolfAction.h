#pragma once
#include "actionCard.h"
#include "table.h"

class WolfAction : public ActionCard {
public:
	WolfAction();
	QueryResult query();
	void perform(Table&, Player*, QueryResult);
};
