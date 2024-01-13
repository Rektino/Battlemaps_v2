#include "Player.h"

Player::Player(int id, sf::RenderWindow& window, Grid& grid)
	: m_id(id), m_dashboard(3, numPieces, 100)
{
	const std::string(&texture_paths)[8] { id == 1 ? p1_texturePaths : p2_texturePaths };
	std::cout << "PLayer constructor has been called\n";
	cumulative_piece_sum[0] = numWarriors;
	for (int i = 1; i < numPieceTypes; i++) {
		cumulative_piece_sum[i] = cumulative_piece_sum[i - 1] + numPieces_array[i];
	}
	for (int i = 0; i < numPieces; i++) {
		auto index = std::lower_bound(cumulative_piece_sum.begin(), cumulative_piece_sum.end(), i) - cumulative_piece_sum.begin();
		if (cumulative_piece_sum[index] == i) index++;
		m_textures.push_back(assign_texture(texture_paths, index));			
	}
	for (int i = 0; i < numPieces; i++) {
		m_sprites.push_back(create_sprite(m_textures[i]));
	}
	create_pieces(); 
	std::cout << "pieces vector size is = " << m_pieces.size() << "\n"; 
	std::cout << "sprites vector size is = " << m_sprites.size() << "\n"; 
	std::cout << "textures vector size is = " << m_textures.size() << "\n"; 
	int j = 0; 
	for (auto& piece : m_pieces) {
		piece->setSprite(m_sprites[j]); 
		j++; 
	}
}

void Player::draw(sf::RenderTarget& window, Grid& grid)
{
	for (auto& piece_ptr : m_pieces) {
		piece_ptr->draw(window);
	}
}

sf::Texture Player::assign_texture(const std::string* paths, ptrdiff_t i) {
	sf::Texture texture;
	try {
		if (!texture.loadFromFile(paths[i])) {
			throw std::runtime_error("Failed to load image"); // Throw an exception if loading fails
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return texture; 
}

std::shared_ptr<sf::Sprite> Player::create_sprite(sf::Texture& texture)
{
	std::shared_ptr<sf::Sprite> my_sprite_ptr = std::make_shared<sf::Sprite>() ; 
	try {
		my_sprite_ptr->setTexture(texture);
		std::cout << "Set the texture : " << my_sprite_ptr->getTexture() << "\n" ;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return my_sprite_ptr;
}

void Player::create_pieces()
{
	for (int i{}; i < numWarriors; i++) {
		m_pieces.push_back(std::make_shared<Warrior>(m_id));
	}
	for (int i{}; i < numDefenders; i++) {
		m_pieces.push_back(std::make_shared<Defender>(m_id));
	}
	for (int i{}; i < numArchers; i++) {
		m_pieces.push_back(std::make_shared<Archer>(m_id));
	}
	for (int i{}; i < numMages; i++) {
		m_pieces.push_back(std::make_shared<Mage>(m_id));
	}
	for (int i{}; i < numAssassins; i++) {
		m_pieces.push_back(std::make_shared<Assassin>(m_id));
	}
	for (int i{}; i < numSnipers; i++) {
		m_pieces.push_back(std::make_shared<Sniper>(m_id));
	}
	for (int i{}; i < numHealers; i++) {
		m_pieces.push_back(std::make_shared<Healer>(m_id));
	}
	for (int i{}; i < numCommanders; i++) {
		m_pieces.push_back(std::make_shared<Commander>(m_id));
	}
}

void Player::place_sprites(Grid& grid)
{
	int i = 0; 
	int y_offset = (m_id == 1 ? 1 : 7); 
	const int piecesPerRow = numPieces / 2;
	for (auto& piece_ptr : m_pieces) {
		int posX = 11 + (i % piecesPerRow);
		int posY = y_offset + (i / piecesPerRow);
		sf::Vector2f pos_float = { grid.getCellPositionX(posX, posY) , grid.getCellPositionY(posX, posY) };
		piece_ptr->move(pos_float, posX, posY);
		i++;
	}
}
