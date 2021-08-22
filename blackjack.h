#ifndef BLACKJACK_H
#define BLACKJACK_H

class Blackjack {
	std::string name;
	unsigned int number;
	unsigned int budget;
	unsigned int bet;
	std::vector<int> deck;
	bool done;
	
	const unsigned int cap = 21;
	
	public:
	// Constructor
	Blackjack(std::string name);
	// Starters
	void Player_start();
	void Casino_start();
	// Commands
	void Add_credit(int amount);
	void Hit();
	void Hit(std::vector<int> split_deck);
	std::vector<int> Split();
	void Split_start(std::vector<int> split_deck, unsigned int player_budget); 
	bool Double();
	bool Bet(unsigned int amount);
	// Fetch or set info
	unsigned int Get_budget();
	unsigned int Get_number();
	unsigned int Get_bet();
	std::string Get_name();
	bool Get_done();
	std::vector<int> Get_deck();

	void Set_done(bool value);
	void Set_bet(unsigned int amount);

	void Casino_play(std::vector<int> player_deck); // Casino autoplay 
	void Casino_play(std::vector<int> player_deck, std::vector<int> split_deck);

	void Test(); // Prints players' info

	const unsigned int Limit(); // returns the constant 21 limit in blackjack
	//test methods
	void Player_start_split();
};

#endif


