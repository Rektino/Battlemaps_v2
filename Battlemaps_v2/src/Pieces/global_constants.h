#ifndef GLOBAL_CONSTANTS_H
#define GLOBAL_CONSTANTS_H
#include <cstdint>
#include <string>
constexpr int PLAYER_ACTIONS = 3;
constexpr int MAPSIZE = 10;
constexpr short int CIRCLE_RADIUS = 25;
constexpr float OUTLINE_THICKNESS = 0.0f;
constexpr float SPACING = 25.0f;
constexpr size_t POINTS_COUNT = 80;
// Number of sprites for each type
constexpr int numWarriors = 3;
constexpr int numArchers = 3;
constexpr int numDefenders = 2;
constexpr int numAssassins = 2;
constexpr int numMages = 1;
constexpr int numHealers = 1;
constexpr int numSnipers = 1;
constexpr int numCommanders = 1;
constexpr int numPieceTypes = 8; 
constexpr int numPieces = numWarriors + numDefenders + numArchers + numMages + numAssassins + numSnipers + numHealers + numCommanders;
constexpr int numPieces_array[] = { numWarriors , numDefenders ,numArchers , numMages , numAssassins , numSnipers , numHealers , numCommanders };


//Grid : 
constexpr int GRID_SIZE_X = 18; // Number of columns
constexpr int GRID_SIZE_Y = 10; // Number of rows
//Hp bars : 
constexpr float HP_BAR_OFFSET = 18.0f; //offset from the piece's sprite
constexpr float HP_BAR_SIZE_X = 5.0f;
constexpr float HP_BAR_SIZE_Y = 30.0f;

constexpr unsigned DEFAULT_CHAR_SIZE = 15; 
constexpr unsigned MENU_BTN_TEXT_SIZE = 45U;


//File paths for fonts :

const std::string font_paths[2] = {
    "fonts/JosefinSans-SemiBold.ttf" ,
    "fonts/JosefinSans-Bold.ttf"
};

const std::string icons_texture_paths[2] = {
    "icons/menu_40.png" ,
    "icons/help_40.png"
}; 

// File paths for the texture files
const std::string p1_texturePaths[8] = {
    "icons/helmet_red.png",
    //"C:/Users/geode/Documents/VS projects GEO/SFML test/Project1/icons/helmet_red.png",     // Warrior
    "icons/shield_red.png",     // defender
    "icons/archer_red.png",       // archer
    "icons/mage_red.png",     // mage
    "icons/dagger_red.png",     // Assassin
    "icons/rifle_red.png",    //sniper
    "icons/healer_red.png" ,  //healer
    "icons/commander_red.png" //commander
    // Add paths for the remaining piece types here
};

const std::string p2_texturePaths[8] = {
    "icons/helmet_blue.png",     // Warrior
    "icons/shield_blue.png",     // defender
    "icons/archer_blue.png",       // archer
    "icons/mage_blue.png",     // mage
    "icons/dagger_blue.png",     // Assassin
    "icons/rifle_blue.png",    //sniper
    "icons/healer_blue.png" ,  //healer
    "icons/commander_blue.png" //commander
    // Add paths for the remaining piece types here
};

const std::string soundPaths[11] = {
    //"C:/Users/geode/Documents/VS projects GEO/SFML test/Project1/sounds/clickButton_sound.wav" ,  //selection
    "sounds/clickButton_sound.wav" ,  //selection
    "sounds/sword-hit.mp3" ,  // warrior
    "sounds/arrow-shot.mp3" , // archer
    "sounds/knife-slice.mp3" , //assassin
    "sounds/magic-spell.mp3" , //mage
    "sounds/health-pickup.mp3" , //healer
    "sounds/pistol-shot.mp3" , //sniper
    "sounds/shield.mp3" ,      //defender 
    "sounds/commander.mp3", //commander
    "sounds/success-sound.mp3" , //victory
    "sounds/placement_sound.mp3" // placement

};

enum Event_states {
    neutral , 
    selected_piece,
    hold_selection , 
    moving_piece  
};

enum Game_states {
    placement,
    action,
    evaluation
};

/**********************************/
/****  PIECE CHARACTERISTICS******/
/*********************************/
constexpr int WARRIOR_DMG = 35;
constexpr int WARRIOR_HP = 250;
constexpr int WARRIOR_RANGE = 1;
//---
constexpr int DEFENDER_DMG = 35;
constexpr int DEFENDER_HP = 250;
constexpr int DEFENDER_RANGE = 1;
//--
constexpr int ARCHER_DMG = 35;
constexpr int ARCHER_HP = 250;
constexpr int ARCHER_RANGE = 2;
//--
constexpr int MAGE_DMG = 35;
constexpr int MAGE_HP = 250;
constexpr int MAGE_RANGE = 2;
//--
constexpr int ASSASSIN_DMG = 35;
constexpr int ASSASSIN_HP = 250;
constexpr int ASSASSIN_RANGE = 1;
//--
constexpr int SNIPER_DMG = 35;
constexpr int SNIPER_HP = 250;
constexpr int SNIPER_RANGE = 2;
//--
constexpr int HEALER_DMG = 10;
constexpr int HEALER_HP = 200;
constexpr int HEALER_RANGE = 2;
//--
constexpr int COMMANDER_DMG = 50;
constexpr int COMMANDER_HP = 400;
constexpr int COMMANDER_RANGE = 1;

constexpr int AVERAGE_HP_START = numWarriors * WARRIOR_HP + numArchers * ARCHER_HP + numDefenders * DEFENDER_HP +
numAssassins * ASSASSIN_HP + numSnipers * SNIPER_HP + numHealers * HEALER_HP + numCommanders * COMMANDER_HP;

constexpr int PIECE_INFO_CELLX = 11;




#endif