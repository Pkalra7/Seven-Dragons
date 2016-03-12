#include "player.h"

Player::Player() {
    
}

Player::Player(int number, std::string name, std::string secret, Hand hand) {
	this->playerNumber = number;
	this->playerName = name;
	this->secretAnimal = secret;
	this->hand = hand;
}

std::string Player::swapSecretAnimal(std::string & newSecret) {
	std::string temp = this->getSecretAnimal();
	this->secretAnimal = newSecret;
	return temp;
}

void Player::setName(const std::string& p_name) {
	this->name = p_name;
}

const std::string& Player::getName() const {
	return  (this->name);
}

std::string& Player::getSecretAnimal() {
	return this->secretAnimal;
}

void Player::swapHand(Hand o_hand) {
	this->hand = o_hand;
}

Hand Player::getHand() {
	return this->hand;
}

void Player::print() {
	std::cout << "Player " << this->playerNumber << std::endl;
	std::cout << "Name: " << this->playerName << std::endl;
	std::cout << "Secret Animal: " << this->getSecretAnimal() << std::endl;
	std::cout << "Hand: " << std::endl;
	(this->hand).print();
}
