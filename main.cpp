#include <iostream>
#include <vector>
#include <string>
#include "blackjack.h"

void Banner() {
	unsigned int i;
        for(i = 0; i < 30; i++)
	  	std::cout << "#";
	std::cout << std::endl << "#";
	for(i = 0; i < 10; i++)
		std::cout << " ";
	std::cout << "blackjack";
	for(i = 0; i < 9; i++)
		std::cout << " ";
	std::cout << "#\n";
	for(i = 0; i < 29; i++)	
		std::cout << "#";						std::cout << "#\n";
}


int main()
{
	int profit;
	unsigned int bet_amount, bet_amount_split = 0, credit_amount;
	bool bet_ok, split, doubled, readEmptyLine, verify_blackjack; 
	std::string command, player_name;	
	std::vector<int> split_deck;
	
	Banner();
	
	std::cout << "player name: ";
	std::getline(std::cin,player_name);
	Blackjack player(player_name), house("house");
	Blackjack player_split(player_name + " 2");
	
	while(1) {
	split = 0;
	readEmptyLine = 1;
	verify_blackjack = 1;
	player.Player_start();
	//player.Player_start_split();          //  split test
	house.Casino_start();
	std::cout << std::endl;
	if(player.Get_budget() <= 0) {
		std::cout << "insufficient budget\nadd credit: ";
		std::cin >> credit_amount;
		player.Add_credit(credit_amount);
	}
	
	profit = player.Get_budget();

	do {
	std::cout << "bet amount: ";
	std::cin >> bet_amount;
	bet_ok = player.Bet(bet_amount);
	if(!bet_ok)
	std::cout << " is too high\n";
	}while(!bet_ok);
	
	for(int i = 0; i < 30; i++)
		std::cout << "#";
	std::cout << std::endl; 

	
	player.Test(); house.Test(); 
	while((split == 0 && player.Get_done() == 0 ) || (split == 1 && (player.Get_done() == 0 || player_split.Get_done() == 0)) ) {

		//empty read line 
		
		if(readEmptyLine == 1) {
			std::string nimic;
			std::getline(std::cin, nimic);
		}
	        //	
		if(verify_blackjack == 1) {
			if(player.Get_number() == house.Limit()) {
				std::cout << "\n**Blackjack**\n";
				player.Set_done(1);
				break;
			}
			else
				verify_blackjack = 0;
		}

		std::cout << std::endl << "8=> ";
		std::getline(std::cin, command);
		
		readEmptyLine = 0;

		if(command == "hit" && player.Get_done() == 0) {
			if(split == 0) 
				player.Hit();
			else
				player.Hit(player_split.Get_deck());

			player.Test(); house.Test();
			if(player.Get_number() >= house.Limit())
				player.Set_done(1);
			
			
		} else

		if(command == "hit split" && split == 1 && player_split.Get_done() == 0) {

			player_split.Hit(player.Get_deck());
			player_split.Test(); house.Test();
			if(player_split.Get_number() >= house.Limit())
				player_split.Set_done(1);
		} else

		if(command == "double" && player.Get_done() == 0) {
			if(!player.Double()) {
				std::cout << "insufficient budget\n";
			}
			else
			{
				if(split == 0)
					player.Hit();
				else
					player.Hit(player_split.Get_deck());

				player.Set_bet(2 * player.Get_bet());
				player.Test();
				player.Set_done(1);
			}
		}

		if(command == "double split" && split == 1 && player_split.Get_done() == 0) {
			if(!player_split.Double()) {
				std::cout << "insufficient budget\n";
			}
			else
			{
				player_split.Set_bet(2 * player_split.Get_bet());
				
				player_split.Hit(player.Get_deck());

				player.Test();
				player_split.Test();
				player_split.Set_done(1);
			}
		}

		if(command == "split" && split == 0 && player.Get_done() == 0) {
			split_deck = player.Split();
			if(!split_deck.size()) 
				std::cout << "you need 2 cards of the same value in order to split\n";
			
			else if(player.Get_budget() < 2 * player.Get_bet())
				std::cout << "Insufficient budget to split\n";

			else {
				player_split.Split_start(split_deck, credit_amount);
				split = 1;
				player_split.Set_bet(player.Get_bet());
			}

			player.Test();
			if(split == 1)
				player_split.Test();
			house.Test();

		}
		  else

		if(command == "stand" && split == 0) {
			player.Set_done(1);
			break;
		} else
		
		if(command == "stand" && split == 1 && player.Get_done() == 0) {
			player.Set_done(1);
		} else

		if(command == "stand split" && split == 1 && player_split.Get_done() == 0) {
			player_split.Set_done(1);
			std::cout << player_split.Get_name() << " stand\n";
		} else

		if(command == "exit")
			exit(0);
		  else

		if(command == "view" && split == 0) {
			player.Test();
			house.Test();
		}

		  else
			  
		if(command == "view" && split == 1) {
			player.Test(); player_split.Test();
			house.Test();
		}

		  else

		if(command == "help")
			std::cout << "Command list:\nhit\nstand\ndouble\nview\nexit\nhelp\nsplit // si comenzile care necesita split inainte\nhit split\ndouble split\nstand split\n\n";

		if(player.Get_done() == 1)
			std::cout << player.Get_name() << " done\n"; 
		if(split == 1)
			if(player_split.Get_done() == 1)
				std::cout << player_split.Get_name() << " done\n";
	}	
		// house autoplay
		
		if(split == 0)
			house.Casino_play(player.Get_deck());
		else
			house.Casino_play(player.Get_deck(), player_split.Get_deck());

		//arbitrare
		std::cout << "**results**" << std::endl;
		if(split == 0) {
			if(player.Get_number() > house.Limit()) {
				player.Add_credit(-player.Get_bet());
				std::cout << "you lost\n";
			}
			else if(player.Get_number() <= house.Limit() && house.Get_number() > house.Limit()) {
				player.Test();house.Test();
				player.Add_credit(player.Get_bet());
				std::cout << "you won\n";
			}

			else if(player.Get_number() > house.Get_number()) {
				player.Test();house.Test();
				player.Add_credit(player.Get_bet());
				std::cout << "you won\n";
			}	

			else if(player.Get_number() < house.Get_number()) {
				player.Test();house.Test();
				player.Add_credit(-player.Get_bet());
				std::cout << "you lost\n";
			}

			else if(player.Get_number() == house.Get_number()) {
				player.Test();house.Test();
				std::cout << "draw\n";
			}
		}

		else
		{	
			//arbitrare player si split
			bool finished_player = 0, finished_split = 0;
			if(player.Get_number() > house.Limit() || player_split.Get_number() > house.Limit()) {
				if(player.Get_number() > house.Limit()) {
					std::cout << player.Get_name() <<" lost\n";
					player.Add_credit(-player.Get_bet()); 
					finished_player = 1;
				}
				
				if(player_split.Get_number() > house.Limit()) {
					std::cout << player_split.Get_name() << " lost\n";
					player.Add_credit(-player_split.Get_bet()); 
					finished_split = 1;
				}
			}

			if(finished_player == 0 || finished_split == 0) {
				if(finished_player == 0) {
					if(player.Get_number() <= house.Limit() && house.Get_number() > house.Limit()) {
						std::cout << player.Get_name() << " won\n";
						player.Add_credit(player.Get_bet()); 
					}
					else if(player.Get_number() > house.Get_number()) {
						std::cout << player.Get_name() << " won\n";
						player.Add_credit(player.Get_bet()); 
					}	
					else if(player.Get_number() < house.Get_number()) {
						std::cout << player.Get_name() << " lost\n";
						player.Add_credit(-player.Get_bet()); 
					}
					else if(player.Get_number() == house.Get_number()) {
						std::cout << player.Get_name() << " draw\n";
					}
				}
				if(finished_split == 0) {
					if(player_split.Get_number() <= house.Limit() && house.Get_number() > house.Limit()) {
						std::cout << player_split.Get_name() << " won\n";
						player.Add_credit(player_split.Get_bet()); 
					}
					else if(player_split.Get_number() > house.Get_number()) {
						std::cout << player_split.Get_name() << " won\n";
						player.Add_credit(player_split.Get_bet()); 
					}	
					else if(player_split.Get_number() < house.Get_number()) {
						std::cout << player_split.Get_name() << " lost\n";
						player.Add_credit(-player_split.Get_bet()); 
					}
					else if(player_split.Get_number() == house.Get_number()) {
						std::cout << player_split.Get_name() << " draw\n";
					}
				}
			}
		
			std::cout << std::endl;
			player.Test(); player_split.Test(); house.Test();	
		}

	

		std::cout << "current budget: " << player.Get_budget() << std::endl;
		profit =  player.Get_budget() - profit;
		if(profit > 0)
			std::cout << "\nprofit: +" << profit << std::endl;
		else
			std::cout << "\nprofit: " << profit << std::endl;

	}
	return 0;
}
