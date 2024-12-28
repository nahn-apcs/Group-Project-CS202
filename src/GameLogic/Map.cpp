#include "Map.h"
#include "render.h"
#include <fstream>



Map::Map(const std::string& filePath, int tileSize, std::vector<sf::Texture>& mapTexture)
    : tileSize(tileSize)
{
    audioManager = new AudioManagement();
    //std::cout << "Map constructor called" << std::endl;
    coinsNumber = 0;
    monsterNumber = 0;
    score = 0;
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        //std::cout << line << std::endl;
        mapData.push_back(line);
    }

    //sf::Texture projectTile;
    if (mapTexture.size() > 2) {
        texture = mapTexture[0];
        Monstertexture = mapTexture[1];
        projectTile = mapTexture[2];
    }
    if (mapTexture.size() > 3) {
        enemyProjectTile = mapTexture[3];
    }
    tile.setTexture(texture);
    tile.setTextureRect(sf::IntRect(0, 0, constants::scene_width, constants::scene_height)); // Select first tile
    //sf::Sprite coinTexture = tile;
    //coinTexture.setTextureRect(sf::IntRect(9*32, 32, tileSize, tileSize)); 
    for (int i = 0; i < mapData.size(); ++i) {
        for (int j = 0; j < mapData[i].size(); ++j) {
            if (mapData[i][j] == 'C') {
                // Create a coin at the corresponding position
                Item* temp = ItemFactory::createItem("Coin", texture, { j * tileSize, i * tileSize });
                coins.push_back(temp);
            }

            else if (mapData[i][j] == '5') {
                Block* block = BlockFactory::createBlock("brick", texture, { j * tileSize, i * tileSize });
                blocks.push_back(block);
               
              
            }
            else if (mapData[i][j] == '7') {
                Block* block = BlockFactory::createBlock("question", texture, { j * tileSize, i * tileSize });
                blocks.push_back(block);
          
                block->setItem("coin");
              
            }
            else if (mapData[i][j] == '8') {
                Block* block = BlockFactory::createBlock("question", texture, { j * tileSize, i * tileSize });
                blocks.push_back(block);
       
                block->setItem("peach");
            }

            else if (mapData[i][j] == 'W') {
            
                Block* block = BlockFactory::createBlock(
                "water", texture, { j * tileSize, i * tileSize });
              blocks.push_back(block);
            }


            else if (mapData[i][j] == 'M') {
              Monster* monster = MonsterFactory::createMonster("Goomba", Monstertexture, { j * tileSize, i * tileSize });
              monsters.push_back(monster);
              mapData[i][j] = '0';
			  monsterNumber++;

            }
            else if (mapData[i][j] == 'B') {
              Monster* monster = MonsterFactory::createMonster("Bee", Monstertexture, { j * tileSize, i * tileSize });
              monsters.push_back(monster);
              mapData[i][j] = '0';
              monsterNumber++;

            }
            else if (mapData[i][j] == 'b') {
              Monster* monster = MonsterFactory::createMonster(
                "bee", Monstertexture, { j * tileSize, i * tileSize });
             
                monsters.push_back(monster);
                mapData[i][j] = '0';
                monsterNumber++;
            }
            else if (mapData[i][j] == 'F') {
			    	Block* block = BlockFactory::createBlock("flag", texture, { j * tileSize, i * tileSize });
				    blocks.push_back(block);
            }
        }
    }
   
}


Map::Map(std::vector<std::string>& map, int tileSize, std::vector<sf::Texture>& mapTexture,
    int sscore,
    std::vector<char>& saveMonsterType,
    std::vector<std::pair< float, float>>& saveMonsterPos,
    std::vector<std::pair<float, float>>& savePlayerProjectilePos,
    std::vector<std::pair<float, float>>& saveMonsterProjectilePos,
    std::vector<int>& savePlayerProjectileDir,
    std::vector<int>& saveMonsterProjectileDir,
    std::vector<std::pair<float, float>>& savePlayerProjectileVel,
    std::vector<std::pair<float, float>>& saveMonsterProjectileVel,

    std::vector<std::pair<float, float>>& saveItemPos,
    std::vector<int>& saveItemType)
    : tileSize(tileSize)
{
    audioManager = new AudioManagement();
    //std::cout << "Map constructor called" << std::endl;
    coinsNumber = 0;
    monsterNumber = 0;
    score = 0;

    for (int i = 0; i < map.size(); ++i) {
        mapData.push_back(map[i]);
    }

    //sf::Texture projectTile;
    if (mapTexture.size() > 2) {
        texture = mapTexture[0];
        Monstertexture = mapTexture[1];
        projectTile = mapTexture[2];
    }
    if (mapTexture.size() > 3) {
        enemyProjectTile = mapTexture[3];
    }
    tile.setTexture(texture);
    tile.setTextureRect(sf::IntRect(0, 0, constants::scene_width, constants::scene_height)); // Select first tile
    //sf::Sprite coinTexture = tile;
    //coinTexture.setTextureRect(sf::IntRect(9*32, 32, tileSize, tileSize)); 
    for (int i = 0; i < mapData.size(); ++i) {
        for (int j = 0; j < mapData[i].size(); ++j) {
            if (mapData[i][j] == 'C') {
                // Create a coin at the corresponding position
                Item* temp = ItemFactory::createItem("Coin", texture, { j * tileSize, i * tileSize });
                coins.push_back(temp);
                coinsNumber++;
            }

            else if (mapData[i][j] == '5') {
                Block* block = BlockFactory::createBlock("brick", texture, { j * tileSize, i * tileSize });
                blocks.push_back(block);


            }
            else if (mapData[i][j] == '7') {
                Block* block = BlockFactory::createBlock("question", texture, { j * tileSize, i * tileSize });
                blocks.push_back(block);

                block->setItem("coin");

            }
            else if (mapData[i][j] == '8') {
                Block* block = BlockFactory::createBlock("question", texture, { j * tileSize, i * tileSize });
                blocks.push_back(block);

                block->setItem("peach");
            }

            else if (mapData[i][j] == 'W') {

                Block* block = BlockFactory::createBlock(
                    "water", texture, { j * tileSize, i * tileSize });
                blocks.push_back(block);
            }


            else if (mapData[i][j] == 'M') {
                Monster* monster = MonsterFactory::createMonster("Goomba", Monstertexture, { j * tileSize, i * tileSize });
                monsters.push_back(monster);
                mapData[i][j] = '0';
                monsterNumber++;

            }
            else if (mapData[i][j] == 'B') {
                Monster* monster = MonsterFactory::createMonster("Bee", Monstertexture, { j * tileSize, i * tileSize });
                monsters.push_back(monster);
                mapData[i][j] = '0';
                monsterNumber++;

            }
            else if (mapData[i][j] == 'b') {
                Monster* monster = MonsterFactory::createMonster(
                    "bee", Monstertexture, { j * tileSize, i * tileSize });

                monsters.push_back(monster);
                mapData[i][j] = '0';
                monsterNumber++;
            }
            else if (mapData[i][j] == 'F') {
                Block* block = BlockFactory::createBlock("flag", texture, { j * tileSize, i * tileSize });
                blocks.push_back(block);
            }
        }
    }

    //int saveLevel;
    //int score = 0;
    //int time = 0;
    //std::vector<std::string> saveMap;
    //std::vector<std::pair< float, float>> saveMonsterPos;
    //std::vector<char> saveMonsterType;

    ////projectile
    //std::vector<std::pair<float, float>> savePlayerProjectilePos;
    //std::vector<std::pair<float, float>> saveMonsterProjectilePos;
    //std::vector<bool> savePlayerProjectileDir;
    //std::vector<bool> saveMonsterProjectileDir;
    //std::vector<std::pair<float, float>> savePlayerProjectileVel;
    //std::vector<std::pair<float, float>> saveMonsterProjectileVel;

    ////item
    //std::vector<std::pair<float, float>> saveItemPos;
    //std::vector<int> saveItemType;
    constantScore = sscore;
    std::cout << "Mster size: " << saveMonsterType.size() << std::endl;
    for (auto m : saveMonsterType) {
        std::cout << m << std::endl;
    }
   
    for (int i = 0; i < saveMonsterType.size(); i++) {
        if (saveMonsterType[i] == 'M') {
            Monster* monster = MonsterFactory::createMonster("Goomba", Monstertexture, {static_cast<int>(saveMonsterPos[i].first), static_cast<int>(saveMonsterPos[i].second) });
            monsters.push_back(monster);
            monsterNumber++;

        }
        else if (saveMonsterType[i] == 'B') {
            Monster* monster = MonsterFactory::createMonster("Bee", Monstertexture, { static_cast<int>(saveMonsterPos[i].first), static_cast<int>(saveMonsterPos[i].second) });
            monsters.push_back(monster);
            monsterNumber++;

        }
        else if (saveMonsterType[i] == 'b') {
            Monster* monster = MonsterFactory::createMonster("bee", Monstertexture, { static_cast<int>(saveMonsterPos[i].first), static_cast<int>(saveMonsterPos[i].second )});
            monsters.push_back(monster);
            monsterNumber++;
        }
    }
    for (int i = 0; i < saveItemType.size(); i++) {
        if (saveItemType[i] == 1) {
            Item* temp = ItemFactory::createItem("Coin", texture, { static_cast<int>(saveItemPos[i].first), static_cast<int>(saveItemPos[i].second) });
            coins.push_back(temp);
            coinsNumber++;
        }
        else if (saveItemType[i] == 2) {
            Item* temp = ItemFactory::createItem("Peach", texture, { static_cast<int>(saveItemPos[i].first), static_cast<int>(saveItemPos[i].second) });
            coins.push_back(temp);
            coinsNumber++;
        }
    }
    for (int i = 0; i < savePlayerProjectileVel.size(); i++) {
        projectiles.addProjectile(projectTile, savePlayerProjectileVel[i].first, savePlayerProjectileVel[i].second, savePlayerProjectilePos[i].first, savePlayerProjectilePos[i].second, savePlayerProjectileDir[i]);
    }
    for (int i = 0; i < saveMonsterProjectileVel.size(); i++) {
        enemyProjectiles.addProjectile(enemyProjectTile, saveMonsterProjectileVel[i].first, saveMonsterProjectileVel[i].second, saveMonsterProjectilePos[i].first, saveMonsterProjectilePos[i].second, saveMonsterProjectileDir[i]);
    }
}






void Map::draw(sf::RenderWindow& window) {
    for (auto& monster : monsters) {
        monster->draw(window);
    }
    for (int i = 0; i < mapData.size(); ++i) {
        for (int j = 0; j < mapData[i].size(); ++j) {
            char tileType = mapData[i][j];

            // Define tile texture regions based on tile type
            if (tileType == '1') { // Solid block
                tile.setTextureRect(sf::IntRect(32*3, 0, tileSize, tileSize));  // Assuming the first tile is a solid block
            }
            else if (tileType == '6') {
                tile.setTextureRect(sf::IntRect(32 * 4, 0, tileSize, tileSize)); 
              
            }
            else if (tileType == '2') {
                // Solid block
				tile.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));  // Assuming the first tile is a solid block
            }
            else if (tileType == '9') {
                tile.setTextureRect(sf::IntRect(32 * 5, 0, tileSize, tileSize));

            }
            //else if (tileType == '5')
            //{
            //    tile.setTextureRect(sf::IntRect(32, 0, tileSize, tileSize));  // Assuming the first tile is a solid bloc
            //}
            //else if (tileType == '7' || tileType == '8') {
            //    tile.setTextureRect(sf::IntRect(32*6, 32, tileSize, tileSize));  // Assuming the first tile is a solid block
            //}
            else if (tileType == 'P')
            {
                tile.setTextureRect(sf::IntRect(16*32, 32, tileSize, tileSize-1));  // Assuming the first tile is a solid bloc
            }
            else if (tileType == 'p') {
                tile.setTextureRect(sf::IntRect(17*32, 32, tileSize, tileSize-1));  // Assuming the first tile is a solid bloc
            }
            else if (tileType == 'H') {
                tile.setTextureRect(sf::IntRect(16*32, 0, tileSize, tileSize-1));  // Assuming the first tile is a solid bloc
            }
            else if (tileType == 'h')
            {
                tile.setTextureRect(sf::IntRect(17*32, 0, tileSize, tileSize-1));  // Assuming the first tile is a solid block

            }
            else if (tileType == 'X') {
              tile.setTextureRect(sf::IntRect(18 * 32, 0, tileSize, tileSize));
            }
            else if (tileType =='Y') {
              tile.setTextureRect(sf::IntRect(19 * 32, 0, tileSize, tileSize));
            }
            else if (tileType == 'Z') {
              tile.setTextureRect(sf::IntRect(20 * 32, 0, tileSize, tileSize));
            }
            else if (tileType == 'L') {
              tile.setTextureRect(sf::IntRect(18 * 32,  32, tileSize, tileSize));
            }
            else if (tileType == 'Q') {
              tile.setTextureRect(sf::IntRect(19 * 32, 32, tileSize, tileSize));
            }
            else if (tileType == 'R') {
              tile.setTextureRect(sf::IntRect(20 * 32, 32, tileSize, tileSize));
            }
            else if (tileType == 'x') {
              tile.setTextureRect(sf::IntRect(18 * 32, 2*32, tileSize, tileSize));
            }
            else if (tileType == 'y') {
              tile.setTextureRect(sf::IntRect(19 * 32,2*32, tileSize, tileSize));
            }
            else if (tileType == 'z') {
              tile.setTextureRect(sf::IntRect(20 * 32, 2*32, tileSize, tileSize));
            }
            else if (tileType == 'c') {
              tile.setTextureRect(sf::IntRect(23 * 32, 0, tileSize, tileSize));
            }
            else if (tileType == 'a') {
              tile.setTextureRect(sf::IntRect(23 * 32, 2*32, tileSize, tileSize));
            }
            else if (tileType == 'd') {
              tile.setTextureRect(
                sf::IntRect(21 * 32, 0, tileSize, tileSize));
            }
            else if (tileType == 'q') {
              tile.setTextureRect(sf::IntRect(21 * 32, 2 * 32, tileSize, tileSize));
            }
            else{
                continue;
            }
            tile.setPosition(j * tileSize, i * tileSize);
            window.draw(tile);
        }
    }

    for (auto& coin : coins) {
        coin->draw(window);
    }

    for (auto& block : blocks) {
        block->draw(window);
    }

    projectiles.draw(window);
    enemyProjectiles.draw(window);

	//sf::Font font;
	//font.loadFromFile("../resources/font/Pixel_NES.otf");
	//sf::Text text;
	//text.setFont(font);
	//text.setString("Coins: " + std::to_string(coinCount));
	//text.setCharacterSize(24);
	//text.setFillColor(sf::Color::Black);
	//text.setPosition(10, 10);
}

Map::~Map() {
   // std::cout << "Map destructor called" << std::endl;
    for (auto& coin : coins) {
        delete coin;
    }
    for (auto& monster : monsters) {
        delete monster;
    }
    for (auto& block : blocks) {
        delete block;
    }
}

void Map::updateCoins(const sf::FloatRect& playerBounds, float deltatime) {
    // Check for coin collection
    
    for (auto& coin : coins) {
        coin->update(deltatime, mapData, 32);
        if (coin->getBounds().intersects(playerBounds) && !coin->isCollected()) {
            audioManager->playCoinSound();
            coin->collect(); // Collect the coin
          if (dynamic_cast<Coin*>(coin)) {
            coinsNumber++;
          }
          else if (dynamic_cast<PowerUp*>(coin)) {
            //implement power up
          }
			      
        }
    }
}

std::vector<std::string>& Map::getMapData(){
	return mapData;
}

void Map::updateMonsters(float deltatime, const sf::FloatRect& playerBounds, const sf::View& camera)
{
  for (auto it = monsters.begin(); it != monsters.end();) {
    auto& monster = *it;  // Use reference for clarity and efficiency
    if (!isVissible(monster->getSprite(), camera)) {
      ++it;
      continue;
    }
    monster->update(deltatime, mapData, tileSize);

    // Get player and monster positions
    sf::FloatRect monsterBounds = monster->getSprite().getGlobalBounds();
    for (int i = 0; i < projectiles.getProjectiles().size(); ++i) {
       
            if (projectiles.getProjectiles()[i]->getBounds().intersects(monsterBounds) && !monster->getIsKilled()) {
                projectiles.destroyProjectile(i);
                auto tileX = static_cast<int>(monsterBounds.left / tileSize);
                auto tileY = static_cast<int>(monsterBounds.top / tileSize);

                mapData[tileY][tileX] = '0';
                monster->kill(true, monster);  
            }
        
    }

    // Check intersection
    if (monsterBounds.intersects(playerBounds)) {
      //std::cout<< "Monster collision detected" << std::endl;
      // Check if the player is above the monster
      float playerBottom =
        playerBounds.top + playerBounds.height;  // Bottom of the player
      float monsterTop = monsterBounds.top;      // Top of the monster


      if (playerBottom <= monsterTop + 5.0f) {  // Allow a small tolerance
        // Monster is killed
        auto tileX = static_cast<int>(monsterBounds.left / tileSize);
        auto tileY = static_cast<int>(monsterBounds.top / tileSize);
       
        mapData[tileY][tileX] = '0';
        monster->kill(true, monster);  // Kill the monster

      }  
      else {
          //std::cout<< "Player is killed" << std::endl;
          if (!monster->getIsKilled()) {
              // Player is killed
              std::cout << "Player is killed" << std::endl;
              // Implement player death here
          }   
      }
    }

    ++it;  // Increment the iterator if no monster was removed
  }
}

void Map::printMapData() const
{
	for (int i = 0; i < mapData.size(); ++i) {
		for (int j = 0; j < mapData[i].size(); ++j) {
			std::cout << mapData[i][j];
		}
		std::cout << std::endl;
	}
}

void Map::saveMapData(const std::string& filePath) {
    // Print debug information
    std::cout << "Saving map data to: " << filePath << std::endl;

    // Open the file
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file: " << filePath << std::endl;
        return;
    }

    // Check mapData size
    if (mapData.empty()) {
        std::cerr << "Warning: mapData is empty. No data will be written." << std::endl;
    }

    // Write data
    for (const auto& data : mapData) {
        file << data << '\n';
    }

    // Optional flush
    file.flush();
    std::cout << "Map data saved successfully." << std::endl;
}


bool Map::isVissible(const sf::Sprite& sprite, const sf::View& camera)
{
  sf::FloatRect monsterBounds = sprite.getGlobalBounds();
  sf::FloatRect viewBounds(camera.getCenter() - camera.getSize() / 2.1f,
                           camera.getSize());
  return monsterBounds.intersects(viewBounds);
}


bool Map::colliable(int x, int y) const
{
    if (x < 0 || y < 0 || x >= mapData[0].size() || y >= mapData.size())
    {
        return false;
    }
    // X,Y,Z,L,R, x,y,z,q, a, b, c, d
    if (mapData[y][x] == '1' || mapData[y][x] == '2' || mapData[y][x] == '5' || mapData[y][x] == '7' || mapData[y][x] == '8' || mapData[y][x] == '9' || mapData[y][x] == 'P' || mapData[y][x] == 'p' || mapData[y][x] == 'H' || mapData[y][x] == 'h'
      ||
        mapData[y][x] == 'X' || mapData[y][x] == 'Y' || mapData[y][x] == 'Z' ||
        mapData[y][x] == 'L' || mapData[y][x] == 'Q' || mapData[y][x] == 'R' ||
        mapData[y][x] == 'x' || mapData[y][x] == 'y' || mapData[y][x] == 'z' ||
        mapData[y][x] == 'q' || mapData[y][x] == 'a' || mapData[y][x] == 'b' ||
        mapData[y][x] == 'c' || mapData[y][x] == 'd'
      )
    {
        return false;
    }
    return true;
}

bool Map::colliableChar(const char& c) const
{
    if (c == '1' || c == '2' || c == '5' || c == '7' || c == '8' || c == '9' || c == 'P' || c == 'p' || c == 'H' || c == 'h' || c == 'X' || c == 'Y' || c == 'Z' ||
      c == 'L' || c == 'Q' || c == 'R' || c == 'x' || c == 'y' || c == 'z' ||
      c == 'q' || c == 'a' || c == 'b' || c == 'c' || c == 'd')
    {
        return false;
    }
    return true;
}

void Map::updateScore()
{   
	int coi = 0;
	for (auto& coin : coins) {
		if (coin->isCollected()) {
			coi++;
		}
	}
	int mons = 0;
	for (auto& monster : monsters) {
		if (monster->getIsKilled()) {
			mons++;
		}
	}
   for (auto& block : blocks) {
          auto item = block->getItemObject();
          if (dynamic_cast<Coin*>(item)) {
            if (item->isCollected()) {
              coi++;
       }
     }
   }

	score = constantScore + coi * 100 + mons * 200;
}

void Map::updateBlocks(float deltatime, sf::FloatRect& playerBounds)
{
 // std::cout << playerBounds.top << std::endl;
  for (auto it = blocks.begin(); it != blocks.end();) {
    auto& block = *it;
    block->update(deltatime, mapData, tileSize);
   // playerBounds.left += 2.0f;
    if (block->isCollission(playerBounds)) {
     
      float playerTop = playerBounds.top;
      float blockBottom = block->getBounds().top + block->getBounds().height;
      float dy = blockBottom - playerTop;
      if (dy < 5.0f) {
        if (!block->getIsTouched()) {
          if (dynamic_cast<QuestionBlock*>(block)) {
            block->setState(new ActiveState());
            block->onTouch2(mapData, tileSize, texture);
            auto item = block->getItemObject();
            if (dynamic_cast<Coin*>(item)) {
                audioManager->playCoinSound();
              coinsNumber++;
            }
            else if (dynamic_cast<PowerUp*>(item)) {
              coins.push_back(item);
            }
          }
          else if (dynamic_cast<BrickBlock*>(block)) {
            block->setState(new DestroyedState());
            block->onTouch2(mapData, tileSize, texture);
            auto item = block->getItemObject();
          }
          
        }
      }
    }
   

    it++;
  }

}
void Map::updateProjectiles(float deltatime)
{
   
    for (int i = 0; i < projectiles.getProjectiles().size(); ++i) {
		int LeftX = projectiles.getProjectiles()[i]->getBounds().left/tileSize;
        int RightX = (projectiles.getProjectiles()[i]->getBounds().left + projectiles.getProjectiles()[i]->getBounds().width) / tileSize;
        int TopY = projectiles.getProjectiles()[i]->getBounds().top / tileSize;
        int BottomY = (projectiles.getProjectiles()[i]->getBounds().top + projectiles.getProjectiles()[i]->getBounds().height) / tileSize;
        int midY = (TopY + BottomY) / 2;
        if (RightX >= mapData[0].size()-1) {
			projectiles.destroyProjectile(i);
		}
        if (LeftX <= 0) {  
            projectiles.destroyProjectile(i);
        }
        if (!colliable(LeftX, midY) || !colliable(RightX, midY)) {
            projectiles.destroyProjectile(i);
        }
	}

  projectiles.update(deltatime);
}

void Map::updateEnemyProjectiles(float deltatime) {
    for (int i = 0; i < enemyProjectiles.getProjectiles().size(); ++i) {
        int LeftX = enemyProjectiles.getProjectiles()[i]->getBounds().left / tileSize;
        int RightX = (enemyProjectiles.getProjectiles()[i]->getBounds().left + enemyProjectiles.getProjectiles()[i]->getBounds().width) / tileSize;
        int TopY = enemyProjectiles.getProjectiles()[i]->getBounds().top / tileSize;
        int BottomY = (enemyProjectiles.getProjectiles()[i]->getBounds().top + enemyProjectiles.getProjectiles()[i]->getBounds().height) / tileSize;
        int midY = (TopY + BottomY) / 2;
        if (RightX >= mapData[0].size() - 1) {
            enemyProjectiles.destroyProjectile(i);
        }
        if (LeftX <= 0) {
            enemyProjectiles.destroyProjectile(i);
        }
        if (!colliable(LeftX, midY) || !colliable(RightX, midY)) {
            enemyProjectiles.destroyProjectile(i);
        }
    }

    enemyProjectiles.update(deltatime);
}

Map Map::operator&=(const Map& other)
{
	mapData = other.mapData;
	tileSize = other.tileSize;
	texture = other.texture;
	Monstertexture = other.Monstertexture;
	projectTile = other.projectTile;
	tile = other.tile;
	coins = other.coins;
	monsters = other.monsters;
	blocks = other.blocks;
	score = other.score;
    coinsNumber = other.coinsNumber;
    monsterNumber = other.monsterNumber;
    projectiles = other.projectiles;
    audioManager = other.audioManager;
	return *this;
}