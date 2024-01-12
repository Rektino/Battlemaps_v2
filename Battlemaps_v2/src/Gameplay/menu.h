#pragma once
#include <SFML/Graphics.hpp>
#include "Events_mouse_key.h"
#include "button.h"
#include "Grid.h"

class Menu {
public : 
	Menu() = delete; 
	Menu(Grid& grid); 	
	void draw(sf::RenderWindow& window); 
	void toggle_state() { active = !active;  }
	inline bool is_active() { return active;  }
	friend void cursor_on_menu(sf::RenderWindow& window, Grid& grid, Menu& game_menu);
private : 	 	
	sf::Font btn_font; 
	Button rules_btn;
	Button sounds_btn;
	Button resume_btn;
	bool active{ false }; 
	bool buttons_created{ false }; 	
};

class Rulebook {
public : 
	Rulebook() = delete; 
	Rulebook(Grid& grid); 
	void draw(sf::RenderWindow& window); 
	void toggle_state() { active = !active;  }
	inline bool is_active(){return active;	} 
private :
	bool active{ false }; 
	sf::RectangleShape m_rectangle; 
	sf::Font m_font; 
	sf::Text m_text; 
	sf::Text title_goal; 
	sf::Text title_gameplay; 
	sf::Text title_piece_info; 
	const std::string goal_str = "How to win"; 
	const std::string gameplay_str = "How to play";
	const std::string piece_info_str = "Pieces"; 
	const std::string description = "Kill your opponent's commander, before they kill yours. Simple as that.\n\
Make sure to position your pieces wisely, and devise the perfect strategy for attack!\n\n\n\n\n\
First, both players position their pieces without viewing the opponent's pieces. When both players are finished, the game starts:\n\
The first player is chosen randomly.The board with all the pieces appear.\n\
In each turn, a player has 3 total MOVES.Each MOVE is associated with a PIECE.Therefore, in each turn, a player will touch pieces 3 times\n\
total.Each piece, can normally do up to 3 actions in one turn : move, attack and once per game, activate its ability.These\n\
can be done in any order.It is not however mandatory to do all these actions, with the selected piece.Note that even if a player chooses to use\n\
only one action of a certain piece, this will be counted as one move for this round.\n\
Exceptions occur when using a Piece's special ability, which may or may not allow for extra actions that round.\n\
In each turn, a player is allowed to activate one(1) Piece's unique ability. The ability may last for this turn or for others as well,\n\
depending on the specific piece.\
When a piece is attacked, if it survives the attack, it will fight back provided that its enemy is within range.\n\
For example, if an archer shoots a warrior from distance, the warrior will never be able to deal back damage,\n\
but if the warrior attacks the archer from close range, the archer will deal back damage. If the piece dies from the attack,\n\
no damage will be dealt back. Also, ranged attacks cannot reach pieces that are behind other pieces,\n\
unless a special ability allows it.\n\n\n\n\n\n\
Each piece has a unique ability, and some pieces may have passive effects as well.The passive effects are permanent, while the ability can be\n\
activated one time per game, for each piece.The abilities are the following:\n\
Warrior: (Berserk)Can attack up to 3 times and move up to 3 times for this round, in any order.It is not mandatory to complete all actions.\n\
Archer : (Heaven's shot) For this round, gain +1 range and you are able to attack a piece which stands behind another piece.\n\
Defender : (Wall)For this round and your opponent's round, become invulnerable to any damage.\n\
Assassin : (Invisibility Cloak) Become invisible to your opponent's pieces, for their next 2 rounds, or until it attacks. The next attack will\n\
be a critical hit(+50 % damage).\n\
Sniper : (Deadly bullet) Gain + 2 range.The next attack will be a critical hit(+50 % damage).\n\
Mage : (Hellfire)Select any 2x2 area on the map.The area becomes burning, causing pieces that stand there at the end of your turn to\n\
receive damage equal to 10 % of their maximum health.\
Healer : (Nature's touch) For this round only, it can heal 3 times.\n\
Commander : (War cry) Buff all adjacent pieces(distance 1), increasing their damage by 20 % for the rest of the game.\n";
		
};