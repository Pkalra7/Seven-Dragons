#pragma once
#include "actionCard.h"
#include "table.h"

class MooseAction : public ActionCard {
public:
	MooseAction();
	QueryResult query();
	void perform(Table&, Player*, QueryResult);
};
