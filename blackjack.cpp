#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include "blackjack.h"

Blackjack::Blackjack(std::string name) {
	this -> name = name;
	this -> number = 0;
	this -> budget = 0;
	this -> done = 0;
}

void Blackjack::Player_start() {

	unsigned int sum, aux;
	
  	do {
		deck.clear();
		for(int i = 1; i <= 13; i++)
			deck[i] = 0;

		srand(time(0));

		sum = 0;	
		for(int i = 0; i < 13; i++) {
			aux = rand() % 13 + 1;
			this -> deck[aux-1]++;
			if(aux > 10)
				aux = 10;

			else	if(aux == 1 && sum + 11 <= this -> cap)
				aux = 11;				
			
			sum+=aux;
		}
	}while(sum >= this -> cap);

	this -> number = sum;
	this -> done = 0;
}

void Blackjack::Casino_start() {
	unsigned int sum, aux;

	this -> budget -= 1; // initial budget must be 0

  	do {
		deck.clear();
		for(int i = 1; i <= 13; i++)
			deck.push_back(0);

		srand(time(0) + 1);

		sum = 0;	
		for(int i = 0; i < 1; i++) {
			aux = rand() % 13 + 1;
			this -> deck[aux - 1]++;
			if(aux > 10)
				aux = 10;

			else	if(aux == 1 && sum + 11 <= this -> cap)
				aux = 11;				

			sum += aux;
		}

	}while(sum >= this -> cap);

	this -> number = sum;
}	

void Blackjack::Add_credit(int amount) {
	this -> budget += amount; 
}

bool Blackjack::Bet(unsigned int amount) {
	if(this -> budget < amount) 
		return 0;
	else
	{
		this -> bet = amount;	
		return 1;
	}
}

void Blackjack::Hit() {
	unsigned int aux;
	srand(time(0) + 2);
	aux = rand() % 13 + 1;
	this -> deck[aux - 1]++;
	while(this -> deck[aux - 1] > 4) {
		this -> deck[aux - 1]--;
		aux = rand() % 13 + 1;
		this -> deck[aux - 1]++;
		
	}
	if(aux > 10)
		aux = 10;

	else	if(aux == 1 && this -> number + 11 <= this -> cap)
		aux = 11;				
	this -> number += aux;
}

void Blackjack::Hit(std::vector<int> deck2) {
	unsigned int aux;
	srand(time(0) + 2);
	aux = rand() % 13 + 1;
	this -> deck[aux - 1]++;
	while(this -> deck[aux - 1] + deck2[aux - 1] > 4) {
		this -> deck[aux - 1]--;
		aux = rand() % 13 + 1;
		this -> deck[aux - 1]++;
	}

	if(aux > 10)
		aux = 10;

	else	if(aux == 1 && this -> number + 11 <= this -> cap)
		aux = 11;

	this -> number += aux;
}


bool Blackjack::Double() {
	if(this -> budget < this -> bet)
		return 0;

       	return 1;	
}

std::vector<int> Blackjack::Split() {
	std::vector<int> split_deck(13,0);
	std::vector<int>::iterator i;
	unsigned int pos;
	bool ok = 0; 

	for(i = this -> deck.begin(); i != this -> deck.end(); i++)
		if(*i == 2) {
			ok = 1;
			pos = i - this -> deck.begin();
		       	//incepe splituirea
			this -> deck[pos]--;
			split_deck[pos]++;
			this -> number -= pos + 1;
			break;
		}

	if(!ok) {
		split_deck.clear();
		return split_deck;
	}
	
	return split_deck; 
}

void Blackjack::Split_start(std::vector<int> split_deck, unsigned int player_budget) {
	this -> deck = split_deck;
	for(std::vector<int>::iterator i = deck.begin(); i != deck.end(); i++) {
		if(*i) { 
			this -> number = i - deck.begin() + 1;
			break;
		}
	}
	
	this -> budget = player_budget;
	this -> done = 0;

}

unsigned int Blackjack::Get_budget() {
	return this -> budget;
}

unsigned int Blackjack::Get_number() {
	return this -> number;
}

std::string Blackjack::Get_name() {
	return this -> name;
}

bool Blackjack::Get_done() {
	return this -> done;
}

void Blackjack::Set_done(bool value) {
	this -> done = value;
}

unsigned int Blackjack::Get_bet() {
	return this -> bet;
}

void Blackjack::Set_bet(unsigned int amount) {
	this -> bet = amount;
}

std::vector<int> Blackjack::Get_deck() {
	return this -> deck;
}

void Blackjack::Casino_play(std::vector<int> player_deck) {
	unsigned int aux;

	srand(time(0));
	aux = rand() % 13 + 1;

	while(this -> number < 17) {
		while((this -> deck[aux - 1]) + (player_deck[aux - 1]) + 1 > 4) {
			aux = rand() % 13 + 1;
		}
		this -> deck[aux - 1]++;
		this -> number += aux;
	}
	this -> done = 1;
}

void Blackjack::Casino_play(std::vector<int> player_deck, std::vector<int> split_deck) {
	unsigned int aux;

	srand(time(0));
	aux = rand() % 13 + 1;

	while(this -> number < 17) {
		while((this -> deck[aux - 1]) + (player_deck[aux - 1]) + (split_deck[aux - 1]) + 1 > 4) {
			aux = rand() % 13 + 1;
		}
		this -> deck[aux - 1]++;
		this -> number += aux;
	}
	this -> done = 1;
}

void Blackjack::Test() {
	std::vector<int>::iterator i;

	std::cout << this -> name << ": ";  
	std::cout << this -> number << std::endl;
	std::cout << "play state: ";
	if(this -> done == 1)
		std::cout << "done";
	else
		std::cout << "playing";
	std::cout << std::endl;
	for(int j = 0; j < 13; j++) {
		if(j + 1 < 10)
			std::cout << j + 1 << "  ";
		else

			std::cout << j + 1 << " ";
	}
	std::cout<<std::endl;
	for(i = this -> deck.begin(); i != this -> deck.end(); i++) 
	      std::cout << *i << "  "; 	
	std::cout << std::endl << std::endl;

	for(int i = 0; i < 39; i++)
		std::cout << "#";
	std::cout << std::endl;

}

const unsigned int Blackjack::Limit() {
	return this -> cap;
}
// Test methods
void Blackjack::Player_start_split() {

	unsigned int sum, aux;
	
	deck.clear();
	for(int i = 0; i < 13; i++)
		deck.push_back(0);

	srand(time(0));

	sum = 0;	
	aux = rand()%10+1;
	sum += 2 * aux;
	this -> deck[aux-1]++;
	this -> deck[aux-1]++;

	this -> number = sum;
	this -> done = 0;

}
