#pragma once
#include "actionCard.h"
#include "table.h"

class DeerAction : public ActionCard {
public:
	DeerAction();
	QueryResult query();
	void perform(Table&, Player*, QueryResult);
};
