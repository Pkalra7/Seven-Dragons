/*CSI2372 Assignment project: Animal Card Game
Professor:Jang Lochen
Due Date : Dec 9th, 11:00pm

SUMBMITTED BY 

Name: Jonathan Todd
Student # 7233629
Name: Pritish Kalra 
Student # 6425451
*/

#include <iostream>
#include "animalCardFactory.h"
#include "deck.h"
#include "player.h"
#include "table.h"
#include "actionCard.h"
using namespace std;

int main() {
	AnimalFactory* af = AnimalFactory::getFactory();

	Deck<AnimalCard> deck = af->getDeck();

	deck.shuffleDeck();

	int numOfPlayers = 0;

	cout << "How many players are playing this round?"
		"( 2-5 players are allowed to play at once.) " << endl;
	while (numOfPlayers == 0)
	{
		cin >> numOfPlayers;
		cout << endl;
	}

	Player* players = new Player[numOfPlayers];
	for (int pl = 0; pl < numOfPlayers; ++pl) {
		cout << "Name of player " << pl << "?" << endl;
		std::string name;
		cin >> name;
		players[pl].setName(name);
		for (int i = 0; i < 3; ++i) {
			players[pl].getHand() += deck.draw();
		}
	}


	Table Board = Table(players, numOfPlayers);

	bool playerWon = false;

	int drawsAllowed[5]{0, 0, 0, 0, 0 };

	while (!playerWon) {

		for (int j = 0; j != numOfPlayers; ++j) {

			cout << "Table: " << endl;

			Board.print();

			for (int n = 0; n != drawsAllowed[j]; n++)
			{
				players[j].getHand() += af->getDeck().draw();
			}

			cout << "Player: " << players[j].getName() << endl;


			int t;
			
			int row, col; // these are indexes the players will provide to insert their card into

			shared_ptr<AnimalCard> cardToBePlaced = nullptr;

			while (true) 
			{
				try 
				{
					t = -1;

					cout << "Which card would you like to place on the board? ";
					while (t < 0 || t > players[j].getHand().numCards())
					{

						cin >> t;

					}
					int orientation = -1;

					cout << "Should the card's orientation be reversed? Type 0 or 1 ";
					while (orientation != 0 && orientation != 1)
					{
						cin >> orientation;
					}

					cout << endl;

					cout << "Where do you want to play it? choose the row and  & col" << endl;

					cin >> row >> col;

					cout << endl;

					cardToBePlaced = players[j].getHand()[t];

					if (row == 52 && col == 52) 
					{
						if (shared_ptr<ActionCard> actionToPerform= dynamic_pointer_cast<ActionCard>(cardToBePlaced)) 
						{
							cout << "Do you want to place the Action card at the top of"
								"the stack or at the bottom? Type 1 to place on top and"
								"type 0  to place at the bottom.";

							bool Top;

							cin >> Top;

							if (Top) 
							{
								Board += actionToPerform;
							}
							else 
							{
								Board -= actionToPerform;
								
								QueryResult queryResult = actionToPerform->query();
								
								actionToPerform->perform(Board,players,queryResult);
							}
						}
						else
						{
							cout << "Only action cards are allowed to be placed on here ." << endl;
							//throw IllegalPlacement(x, y);
						}
					}
					else
					{
						cardToBePlaced->setOrientation((Orientation)orientation);

						drawsAllowed[j] = Board.addAt(cardToBePlaced, row, col);
					}

				}
				catch (...) 
				{
					cout << "Incorrect positioning of card. Make sure you place "
						"the card so that you have atleast one match "
						"with neighbouring cards" << endl;
					continue;
				}
				break;
			}

			players[j].getHand() -= cardToBePlaced;

			for (int o = 0; o!= numOfPlayers; ++o) {

				string name = players[o].getSecretAnimal();

				if (Board.win(name))
				{
					playerWon = true;
					cout << players[o].getName() << " has won the game" << endl;

				}
			}
		}
		return 0;
	}
}