#pragma once
#include <string>
#include "hand.h"

class Player {
	int playerNumber;
	std::string playerName;
	std::string secretAnimal;
	std::string name;
	Hand hand;
public:
	Player();
	Player(int, std::string, std::string, Hand);
	std::string swapSecretAnimal(std::string&);
	std::string& getSecretAnimal();
	void setName(const std::string& p_name);
	const std::string& getName() const;
	void swapHand(Hand);
	Hand getHand();
	void print();
};
