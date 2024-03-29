﻿# Blackjack

A simple blackjack game where you play against the house.
Rules:

-The player and the house both start with 2 cards but the house will only show one card until the end;  
-The player can choose to stand, hit or double unless he gets to 21 or higher;  
-The house will play until it hits 17 or higher;  
-If the player starts with a pair he can choose to split his cards into 2 decks. Each deck can hit, double or stand and have the potential to quadruple the initial bet;  
-Any card above 10 equals 10 and aces are worth 11 unless it causes the player or house to go over 21. In that case they are worth 1;  

The cards are represented on a frequency array where every cell index represents a card value, and the value of the cell is the number of times that card was played. At the end of the game that value cannot exceed 4 counting all the played decks up to 3 (player, player split, house);

After username, credits and bet are made there will be a prompt ("8=>") where the following commands can be used to play the game:

- "hit" - add another card
- "stand" - end current player/split turn
- "double" - doubles current bet, hits then stand
- "split" - if the player has a pair or enough budget to double his bet he can split. That means he can play 2 decks at the same time (player and player split). He can play the split deck using the split variant of the above commands
- "hit split" - add another card on the split deck
- "double split" - doubles the split deck
- "split stand" - stops split's turn
- "view" - shows current status of the player house and split if available 
- "help" - lists all commands
- "exit" - exits game


