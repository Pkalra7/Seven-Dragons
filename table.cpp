#include "table.h"
#include "actionCard.h"

using namespace std;

Table::Table(Player o_players[5], int numPlayers) {
	int i = 0;
	while (i < numPlayers) {
		this->players[i] = o_players[i];
		i++;
	}
	
	std::fill((this->tracker)[0], (this->tracker)[102] + 103, -1);
	shared_ptr<AnimalCard> sS = shared_ptr<AnimalCard>(new StartStack()); 
	table[52][52] = sS;
	tracker[52][52] = 1;
	this->noPlayers = numPlayers;
}

int Table::addAt(std::shared_ptr<AnimalCard> o_animalCard, int row, int col) {
	//must check if insertion is valid

	bool neighbours = false;
	int matches = 0;

	if (tracker[row][col]<1) // checks if there isn't a card at Board[row][col] 
	{
		neighbours = checkForNeighbour(row, col);
		if (!neighbours)
		{
			cout << "invalid placement " << endl;
			return 0;
		}
		else
		{
			matches = nOfMatches(o_animalCard, row, col);

			if (matches > 0)
			{
				table[row][col] = o_animalCard;
				tracker[row][col] = 1;
				return matches;
			}
			else
			{
				return 0;
			}
		}
	}
	else //  there's already a card at given [row][col]
	{

		cout << "there's already a card at that position" << endl;
		return 0;
	}

}

bool Table::checkForNeighbour(int row, int col)
{
	bool correct;
	switch (row)
	{
	case 0:
		switch (col)
		{
		case 0:
			if (tracker[row + 1][col] > 0 || tracker[row][col + 1]  > 0)
			{
				correct = true;
			}
			break;
		case 102:
			if (tracker[row + 1][col] > 0 || tracker[row][col - 1] > 0)
			{
				correct = true;
			}
			break;
		default:
			if (tracker[row + 1][col] > 0 || tracker[row][col - 1] > 0 || tracker[row][col + 1] > 0)
			{
				correct = true;
			}
			break;
		}
		break;
	case 102:
		switch (col)
		{
		case 0:
			if (tracker[row - 1][col] > 0 || tracker[row][col + 1] > 0)
			{
				correct = true;
			}
			break;
		case 102:
			if (tracker[row - 1][col] > 0 || tracker[row][col - 1] > 0)
			{
				correct = true;
			}
			break;
		default:
			if (tracker[row - 1][col] > 0 || tracker[row][col - 1] > 0 || tracker[row][col + 1] > 0)
			{
				correct = true;
			}
			break;
		}
		break;
	default:
		switch (col)
		{
		case 0:
			if (tracker[row - 1][col] > 0 || tracker[row + 1][col] > 0 || tracker[row][col + 1] > 0)
			{
				correct = true;
			}
			break;
		case 102:
			if (tracker[row - 1][col] > 0 || tracker[row + 1][col] > 0 || tracker[row][col - 1] > 0)
			{
				correct = true;
			}
			break;
		default:
			if (tracker[row - 1][col] > 0 || tracker[row + 1][col] > 0 || tracker[row][col - 1] > 0 || tracker[row][col + 1] > 0)
			{
				correct = true;
			}
			break;

		}
	}
	return correct;
}

int Table::nOfMatches(std::shared_ptr<AnimalCard> o_actionCard, int row, int col)
{
	bool TL = false;
	bool TR = false;
	bool BL = false;
	bool BR = false;
	bool  matches[4] = { TL, TR, BL, BR };
	int count = 0;

	//CHECKING FOR MATCHES WITH CARD ABOVE
	if (row - 1 >= 0 && tracker[row - 1][col] == 1)
	{
		if (table[row - 1][col]->getBL() == "S" || table[row - 1][col]->getBL() == o_actionCard->getTL() || table[row - 1][col]->getBL() == "J")
		{
			TL = true;
		}

		if (table[row - 1][col]->getBR() == "S" || table[row - 1][col]->getBR() == o_actionCard->getTR() || table[row - 1][col]->getBR() == "J")
		{
			TR = true;
		}
	}

	//CHECKING FOR MATCHES WITH CARD ON THE LEFT
	if (((col - 1) >= 0) && tracker[row][col - 1] == 1)
	{
		if (table[row][col - 1]->getTR() == "S" || table[row][col - 1]->getTR() == o_actionCard->getTL() || table[row][col - 1]->getTR() == "J")
		{
			TL = true;
		}
		if (table[row][col - 1]->getBR() == "S" || table[row][col - 1]->getBR() == o_actionCard->getBL() || table[row][col - 1]->getBR() == "J")
		{
			BL = true;
		}
	}

	//CHECKING FOR MATCHES WITH CARD BELOW
	if (((row + 1) >= 0) && tracker[row + 1][col] == 1)
	{
		if (table[row + 1][col]->getTL() == "S" || table[row + 1][col]->getTL() == o_actionCard->getBL() || table[row + 1][col]->getTL() == "J")
		{
			BL = true;
		}
		if (table[row + 1][col]->getTR() == "S" || table[row + 1][col]->getTR() == o_actionCard->getBR() || table[row + 1][col]->getTR() == "J")
		{
			BR = true;
		}
	}

	//CHECKING FOR MATCHES WITH CARD ON THE RIGHT
	if (((col + 1) >= 0) && tracker[row][col + 1] == 1)
	{
		if (table[row][col + 1]->getTL() == "S" || table[row][col + 1]->getTL() == o_actionCard->getTR() || table[row][col + 1]->getTL() == "J")
		{
			TR = true;
		}
		if (table[row][col + 1]->getBL() == "S" || table[row][col + 1]->getBL() == o_actionCard->getBR() || table[row][col + 1]->getBL() == "J")
		{
			BR = true;
		}
	}

	//computes total matches for the card that is being added
	for (int i = 0; i < 4; ++i)
	{
		if (matches[i] == true)
		{
			count++;
		}
	}

	return count++;
	
}


Table & Table::operator+=(std::shared_ptr<ActionCard> o_actionCard) {
	shared_ptr<StartStack> startS= dynamic_pointer_cast<StartStack>(table[52][52]);
	
	*startS+=(o_actionCard);
	
	return *this;
}

Table & Table::operator-=(std::shared_ptr<ActionCard> o_actionCard) {
	shared_ptr<StartStack> sStack = dynamic_pointer_cast<StartStack>(table[52][52]);
	
	*sStack-=(o_actionCard);
	
	return *this;
}

//removes and returns card at given [row][col] 
std::shared_ptr<AnimalCard> Table::pickAt(int row, int col) {
	bool isIllegal;
	try {
		if (tracker[row][col] != 1 || (row == 52 && col == 52)) {
			isIllegal = true;
		}
		else {
			shared_ptr<AnimalCard> temp = (this->table)[row][col];
			(this->table)[row][col] = nullptr;
			(this->tracker)[row][col] = -1;
			return temp;
		}
	}
	catch (bool b) {
		std::cout << "Illegal pick" << std::endl;
	}
}

Player Table::getPlayer(int playerNumber) {
	return (this->players)[playerNumber];
}

int Table::numPlayers() {
	return this->noPlayers;
}


bool Table::win(std::string & animal) {

	bool exists = false;
	int numOfAnimals = 0;

	for (int i = 0; i < 103; ++i)
	{
		for (int j = 0; j < 103; ++j)
		{
			if (tracker[i][j] == 1)
			{
				if (table[i][j]->getTL() == animal || table[i][j]->getTR() == animal || table[i][j]->getBL() == animal || table[i][j]->getBR() == animal)
				{
					numOfAnimals++;
				}
			}
		}
	}

	return numOfAnimals >= 12;

}

void Table::print()
{
	for (int i = 0; i < 103; ++i)
	{
		for (int j = 0; j < 103; ++j)
		{
			if (tracker[i][j] == 1)
			{
				cout << (this->table)[i][j]->getTL() << (this->table)[i][j]->getTR() << " ";

			}
			else
			{
				cout << "empty ";
			}
		}

		cout << endl;

		for (int n = 0; n < 103; ++n)
		{
			if (tracker[i][n] == 1)
			{
				cout << (this->table)[i][n]->getBL() << (this->table)[i][n]->getBR() << " ";
			}
			else
			{
				cout << "empty ";
			}

		}

		cout << endl;
		cout << endl;

	}
}