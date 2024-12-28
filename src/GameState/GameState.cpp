#include <GameState.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>
#include "AudioManagement.h"
#include <LevelManager.hpp>
#include <fstream>

GameState::GameState(StateStack& stack, Context context) : boss(nullptr), State(stack, context) {
	monsterset = context.textures->get(Textures::Enemies);
	projectile = context.textures->get(Textures::Bullet);
	enemyProjectile = context.textures->get(Textures::BossBullet);
	camera = sf::View(sf::FloatRect(0.f, 0.f, constants::scene_width, constants::scene_height));
	drawEngine = new DrawEngine();
	PauseButton.setTexture(context.textures->get(Textures::PauseButton));
	PauseButton.setTextureRect(sf::IntRect(0, 0, 80, 50));
	PauseButton.setPosition(1230, 0);

	context.music->setVolume(30);
	context.music->play(Music::GameTheme);

	if (LevelManager::getInstance().getCurLevel() == LevelManager::None) {
		std::cout << "Load game\n";
		LevelManager& lm = LevelManager::getInstance();
		std::ifstream file;
		file.open("../resources/save.txt");
		if (!file) { std::cout << "File not found" << std::endl; 
		exit(1); 
		}
		int level, score, time, coins;
		int mapSize;
		std::vector<std::string> map;
		int monsterSize;
		std::vector<std::pair<float, float>> monsterPos;
		std::vector<char> monsterType;
		int playerProjectileSize;
		std::vector<std::pair<float, float>> playerProjectilePos;
		std::vector<int> playerProjectileDir;
		std::vector<std::pair<float, float>> playerProjectileVel;
		int monsterProjectileSize;
		std::vector<std::pair<float, float>> monsterProjectilePos;
		std::vector<int> monsterProjectileDir;
		std::vector<std::pair<float, float>> monsterProjectileVel;
		int itemSize;
		std::vector<std::pair<float, float>> itemPos;
		std::vector<int> itemType;
		int playerType;
		float playerX, playerY;
		int playerHP;
		int playerStatus;
		float playerVelX, playerVelY;
		bool hasBoss;
		float bossX, bossY;
		int bossHP;
		float bossVelX, bossVelY;
		int bossActive;
		if (file) {
			file >> level >> score >> time >> coins;
		
			file >> mapSize;
			for (int i = 0; i < mapSize; i++) {
				std::string line;
				file >> line;
				map.push_back(line);
			}
			file >> monsterSize;
			
			for (int i = 0; i < monsterSize; i++) {
				float x, y;
				file >> x >> y;
				monsterPos.push_back(std::make_pair(x, y));
			}
			for (int i = 0; i < monsterSize; i++) {
				char type;
				file >> type;
				monsterType.push_back(type);
				std::cout << type << "\n";
			}
			
			file >> playerProjectileSize;
			
			for (int i = 0; i < playerProjectileSize; i++) {
				float x, y;
				file >> x >> y;
				playerProjectilePos.push_back(std::make_pair(x, y));
			}
			for (int i = 0; i < playerProjectileSize; i++) {
				float x, y;
				file >> x >> y;
				monsterProjectilePos.push_back(std::make_pair(x, y));
			}

			for (int i = 0; i < playerProjectileSize; i++) {
				int dir;
				file >> dir;
				playerProjectileDir.push_back(dir);
			}

			for (int i = 0; i < playerProjectileSize; i++) {
				int dir;
				file >> dir;
				monsterProjectileDir.push_back(dir);
			}

			for (int i = 0; i < playerProjectileSize; i++) {
				float x, y;
				file >> x >> y;
				playerProjectileVel.push_back(std::make_pair(x, y));
			}

			for (int i = 0; i < playerProjectileSize; i++) {
				float x, y;
				file >> x >> y;
				monsterProjectileVel.push_back(std::make_pair(x, y));
			}


			/*file << lm.getSavePlayerProjectilePos().size() << std::endl;
			for (int i = 0; i < lm.getSavePlayerProjectilePos().size(); i++) {
				file << lm.getSavePlayerProjectilePos()[i].first << " " << lm.getSavePlayerProjectilePos()[i].second << std::endl;
			}
			for (int i = 0; i < lm.getSaveMonsterProjectilePos().size(); i++) {
				file << lm.getSaveMonsterProjectilePos()[i].first << " " << lm.getSaveMonsterProjectilePos()[i].second << std::endl;
			}
			for (int i = 0; i < lm.getSavePlayerProjectileDir().size(); i++) {
				file << lm.getSavePlayerProjectileDir()[i] << std::endl;
			}
			for (int i = 0; i < lm.getSaveMonsterProjectileDir().size(); i++) {
				file << lm.getSaveMonsterProjectileDir()[i] << std::endl;
			}
			for (int i = 0; i < lm.getSavePlayerProjectileVel().size(); i++) {
				file << lm.getSavePlayerProjectileVel()[i].first << " " << lm.getSavePlayerProjectileVel()[i].second << std::endl;
			}
			for (int i = 0; i < lm.getSaveMonsterProjectileVel().size(); i++) {
				file << lm.getSaveMonsterProjectileVel()[i].first << " " << lm.getSaveMonsterProjectileVel()[i].second << std::endl;
			}*/


			
			file >> itemSize;
			
			for (int i = 0; i < itemSize; i++) {
				float x, y;
				file >> x >> y;
				itemPos.push_back(std::make_pair(x, y));
			}
			for (int i = 0; i < itemSize; i++) {
				int type;
				file >> type;
				itemType.push_back(type);
				std::cout << type << "\n";
			}
			
			/*file << lm.getPlayerType() << std::endl;
			file << lm.getSavePlayerPosX() << " " << lm.getSavePlayerPosY() << std::endl;
			file << lm.getPlayerHP() << std::endl;
			file << lm.getPlayerStatus() << std::endl;
			file << lm.getPlayerVelX() << " " << lm.getPlayerVelY() << std::endl;
			file << "End." << std::endl;
			if (lm.hasBoss()) {
				file << 1 << std::endl;
				file << lm.getSaveBossPosX() << " " << lm.getSaveBossPosY() << std::endl;
				file << lm.getBossHP() << std::endl;
				file << lm.getBossVelX() << " " << lm.getBossVelY() << std::endl;
			}
			else {
				file << 0;
			}*/

			file >> playerType;
      if (playerType == 1) {
                          LevelManager::getInstance().setCurCharacter(
                            LevelManager::wukong);
                        }
      else {
                          LevelManager::getInstance().setCurCharacter(
                            LevelManager::pig);
      }
			file >> playerX >> playerY;
			file >> playerHP;
			file >> playerStatus;
			file >> playerVelX >> playerVelY;
			file >> hasBoss;
			if (hasBoss) {
				file >> bossX >> bossY;
				file >> bossHP;
				file >> bossVelX >> bossVelY;
				file >> bossActive;
			}
			std::cout << playerType << " " << playerX << " " << playerY << " " << playerHP << " " << playerStatus << " " << playerVelX << " " << playerVelY << "\n";
			for (auto i : monsterPos) {
				std::cout << i.first << " " << i.second << "\n";
			}
			elapsedTime = time;

			switch (playerType)
			{
			case 1:
				idleTextures.push_back(context.textures->get(Textures::WukongStand1));
				idleTextures.push_back(context.textures->get(Textures::WukongStand2));
				idleTextures.push_back(context.textures->get(Textures::WukongStand3));
				idleTextures.push_back(context.textures->get(Textures::WukongStand4));

				runTextures.push_back(context.textures->get(Textures::WukongRun1));
				runTextures.push_back(context.textures->get(Textures::WukongRun2));
				runTextures.push_back(context.textures->get(Textures::WukongRun3));
				runTextures.push_back(context.textures->get(Textures::WukongRun4));

				jumpTextures.push_back(context.textures->get(Textures::WukongJump1));
				jumpTextures.push_back(context.textures->get(Textures::WukongJump2));
				jumpTextures.push_back(context.textures->get(Textures::WukongJump3));
				jumpTextures.push_back(context.textures->get(Textures::WukongJump4));
				std::cout << "GameState 22" << "\n";

				attackTextures.push_back(context.textures->get(Textures::WukongAttack1));
				attackTextures.push_back(context.textures->get(Textures::WukongAttack2));

				sIdleTextures.push_back(context.textures->get(Textures::SmallWukongStand1));
				sIdleTextures.push_back(context.textures->get(Textures::SmallWukongStand2));
				sIdleTextures.push_back(context.textures->get(Textures::SmallWukongStand3));
				sIdleTextures.push_back(context.textures->get(Textures::SmallWukongStand4));
				std::cout << "GameState 33" << "\n";

				sRunTextures.push_back(context.textures->get(Textures::SmallWukongRun1));
				sRunTextures.push_back(context.textures->get(Textures::SmallWukongRun2));
				sRunTextures.push_back(context.textures->get(Textures::SmallWukongRun3));
				sRunTextures.push_back(context.textures->get(Textures::SmallWukongRun4));

				deadTextures.push_back(context.textures->get(Textures::DeadWukong1));
				deadTextures.push_back(context.textures->get(Textures::DeadWukong2));
				deadTextures.push_back(context.textures->get(Textures::DeadWukong3));
				deadTextures.push_back(context.textures->get(Textures::DeadWukong4));
				deadTextures.push_back(context.textures->get(Textures::DeadWukong5));
				deadTextures.push_back(context.textures->get(Textures::DeadWukong6));
				deadTextures.push_back(context.textures->get(Textures::DeadWukong7));
				deadTextures.push_back(context.textures->get(Textures::DeadWukong8));
				deadTextures.push_back(context.textures->get(Textures::DeadWukong9));

				hurtTextures.push_back(context.textures->get(Textures::WukongHurt1));
				hurtTextures.push_back(context.textures->get(Textures::WukongHurt2));
				hurtTextures.push_back(context.textures->get(Textures::WukongHurt3));

				sHurtTextures.push_back(context.textures->get(Textures::SmallWukongHurt1));
				sHurtTextures.push_back(context.textures->get(Textures::SmallWukongHurt2));
				sHurtTextures.push_back(context.textures->get(Textures::SmallWukongHurt3));
				player = new Character(idleTextures, runTextures, attackTextures, jumpTextures, hurtTextures, sIdleTextures, sRunTextures, sIdleTextures, sRunTextures, sHurtTextures, deadTextures, playerX, playerY, playerType, playerHP, playerVelX, playerVelY, playerStatus);
				break;
			case 2:
				idleTextures.push_back(context.textures->get(Textures::SecondWukongStand1));
				idleTextures.push_back(context.textures->get(Textures::SecondWukongStand2));
				idleTextures.push_back(context.textures->get(Textures::SecondWukongStand3));
				idleTextures.push_back(context.textures->get(Textures::SecondWukongStand4));
				idleTextures.push_back(context.textures->get(Textures::SecondWukongStand5));

				runTextures.push_back(context.textures->get(Textures::SecondWukongRun1));
				runTextures.push_back(context.textures->get(Textures::SecondWukongRun2));
				runTextures.push_back(context.textures->get(Textures::SecondWukongRun3));
				runTextures.push_back(context.textures->get(Textures::SecondWukongRun4));
				runTextures.push_back(context.textures->get(Textures::SecondWukongRun5));
				runTextures.push_back(context.textures->get(Textures::SecondWukongRun6));
				runTextures.push_back(context.textures->get(Textures::SecondWukongRun7));
				runTextures.push_back(context.textures->get(Textures::SecondWukongRun8));

				jumpTextures.push_back(context.textures->get(Textures::SecondWukongRun1));
				jumpTextures.push_back(context.textures->get(Textures::SecondWukongRun2));
				jumpTextures.push_back(context.textures->get(Textures::SecondWukongRun3));
				jumpTextures.push_back(context.textures->get(Textures::SecondWukongRun4));
				jumpTextures.push_back(context.textures->get(Textures::SecondWukongRun5));
				jumpTextures.push_back(context.textures->get(Textures::SecondWukongRun6));
				jumpTextures.push_back(context.textures->get(Textures::SecondWukongRun7));
				jumpTextures.push_back(context.textures->get(Textures::SecondWukongRun8));

				attackTextures.push_back(context.textures->get(Textures::SecondWukongAttack1));
				attackTextures.push_back(context.textures->get(Textures::SecondWukongAttack2));
				attackTextures.push_back(context.textures->get(Textures::SecondWukongAttack3));
				attackTextures.push_back(context.textures->get(Textures::SecondWukongAttack4));
				attackTextures.push_back(context.textures->get(Textures::SecondWukongAttack5));

				deadTextures.push_back(context.textures->get(Textures::SecondWukongDead1));
				deadTextures.push_back(context.textures->get(Textures::SecondWukongDead2));
				deadTextures.push_back(context.textures->get(Textures::SecondWukongDead3));
				deadTextures.push_back(context.textures->get(Textures::SecondWukongDead4));
				deadTextures.push_back(context.textures->get(Textures::SecondWukongDead5));
				deadTextures.push_back(context.textures->get(Textures::SecondWukongDead6));
				deadTextures.push_back(context.textures->get(Textures::SecondWukongDead7));

				hurtTextures.push_back(context.textures->get(Textures::SecondWukongHurt1));
				hurtTextures.push_back(context.textures->get(Textures::SecondWukongHurt2));
				hurtTextures.push_back(context.textures->get(Textures::SecondWukongHurt3));

				player = new SecondCharacter(idleTextures, runTextures, attackTextures, jumpTextures, hurtTextures, idleTextures, runTextures, idleTextures, runTextures, hurtTextures, deadTextures, playerX, playerY, 2, playerHP, playerVelX, playerVelY, playerStatus);

				break;

			default:
				break;
			}
			switch (level+1)
			{
			case 1:

				tileset = context.textures->get(Textures::Blocks);
				mapTextures.push_back(tileset);
				mapTextures.push_back(monsterset);
				mapTextures.push_back(projectile);
				mapTextures.push_back(enemyProjectile);
				/*audioManager = new AudioManagement();
				audioManager->playMainMusic();*/
				gameMap = new Map(map, 32,  mapTextures, score, monsterType, monsterPos, playerProjectilePos, monsterProjectilePos, playerProjectileDir, monsterProjectileDir, playerProjectileVel, monsterProjectileVel, itemPos, itemType);
				gameMap->level = 1;
				gameMap->setcoinsNumber(coins);
				backgroundTexture = context.textures->get(Textures::Bg1);
				backgroundSprite.setTexture(context.textures->get(Textures::Bg1));
				std::cout << gameMap->getMapData().size() << "\n";
				xRepeatCount = gameMap->getMapData()[0].size() * 32 / backgroundTexture.getSize().x + 1;  // Add 1 to ensure coverage
				yRepeatCount = gameMap->getMapData().size() * 32 / backgroundTexture.getSize().y + 1;
				LevelManager::getInstance().setCurLevel(LevelManager::Level1);
				break;
			case 2:
				tileset = context.textures->get(Textures::Blocks2);
				mapTextures.push_back(tileset);
				mapTextures.push_back(monsterset);
				mapTextures.push_back(projectile);
				mapTextures.push_back(enemyProjectile);

				gameMap = new Map(map,32, mapTextures, 
					score, 
					monsterType, 
					monsterPos, 
					playerProjectilePos, 
					monsterProjectilePos, 
					playerProjectileDir, 
					monsterProjectileDir, 
					playerProjectileVel, 
					monsterProjectileVel, 
					itemPos, 
					itemType);

				/*Map(std::vector<std::string>& map, int tileSize, std::vector<sf::Texture>& mapTexture,
					int sscore,
					std::vector<char>& saveMonsterType,
					std::vector<std::pair< float, float>>& saveMonsterPos,
					std::vector<std::pair<float, float>>& savePlayerProjectilePos,
					std::vector<std::pair<float, float>>& saveMonsterProjectilePos,
					std::vector<bool>& savePlayerProjectileDir,
					std::vector<bool>& saveMonsterProjectileDir,
					std::vector<std::pair<float, float>>& savePlayerProjectileVel,
					std::vector<std::pair<float, float>>& saveMonsterProjectileVel,

					std::vector<std::pair<float, float>>& saveItemPos,
					std::vector<int>& saveItemType);*/
				gameMap->level = 2;
				gameMap->setcoinsNumber(coins);

				backgroundTexture = context.textures->get(Textures::Bg2);
				backgroundSprite.setTexture(context.textures->get(Textures::Bg2));
				std::cout << gameMap->getMapData().size() << "\n";
				xRepeatCount = gameMap->getMapData()[0].size() * 32 / backgroundTexture.getSize().x + 1;  // Add 1 to ensure coverage
				yRepeatCount = gameMap->getMapData().size() * 32 / backgroundTexture.getSize().y + 1;
				LevelManager::getInstance().setCurLevel(LevelManager::Level2);

				break;
			case 3:
				tileset = context.textures->get(Textures::Blocks3);
				mapTextures.push_back(tileset);
				mapTextures.push_back(monsterset);
				mapTextures.push_back(projectile);
				mapTextures.push_back(enemyProjectile);

				gameMap = new Map(map, 32, mapTextures,
					score,
					monsterType,
					monsterPos,
					playerProjectilePos,
					monsterProjectilePos,
					playerProjectileDir,
					monsterProjectileDir,
					playerProjectileVel,
					monsterProjectileVel,
					itemPos,
					itemType);				
				gameMap->level = 3;
				gameMap->setcoinsNumber(coins);

				backgroundTexture = context.textures->get(Textures::Bg3);
				backgroundSprite.setTexture(context.textures->get(Textures::Bg3));
				std::cout << gameMap->getMapData().size() << "\n";
				xRepeatCount = gameMap->getMapData()[0].size() * 32 / backgroundTexture.getSize().x + 1;  // Add 1 to ensure coverage
				yRepeatCount = gameMap->getMapData().size() * 32 / backgroundTexture.getSize().y + 1;
				bossAttackTextures.push_back(context.textures->get(Textures::BossAttack1));
				bossAttackTextures.push_back(context.textures->get(Textures::BossAttack2));
				bossAttackTextures.push_back(context.textures->get(Textures::BossAttack3));

				bossDeadTextures.push_back(context.textures->get(Textures::BossDead1));
				bossDeadTextures.push_back(context.textures->get(Textures::BossDead2));
				bossDeadTextures.push_back(context.textures->get(Textures::BossDead3));
				bossDeadTextures.push_back(context.textures->get(Textures::BossDead4));
				bossDeadTextures.push_back(context.textures->get(Textures::BossDead5));
				bossDeadTextures.push_back(context.textures->get(Textures::BossDead6));
				bossDeadTextures.push_back(context.textures->get(Textures::BossDead7));

				bossExhaustedTextures.push_back(context.textures->get(Textures::BossExhausted1));
				bossExhaustedTextures.push_back(context.textures->get(Textures::BossExhausted2));

				bossFlyingTextures.push_back(context.textures->get(Textures::BossFly1));
				bossFlyingTextures.push_back(context.textures->get(Textures::BossFly2));
				bossFlyingTextures.push_back(context.textures->get(Textures::BossFly3));
				bossFlyingTextures.push_back(context.textures->get(Textures::BossFly4));

				bossShootTextures.push_back(context.textures->get(Textures::BossShoot1));
				bossShootTextures.push_back(context.textures->get(Textures::BossShoot2));

				boss = new Boss(bossFlyingTextures, bossAttackTextures, bossDeadTextures, bossExhaustedTextures, bossShootTextures, bossX, bossY, bossHP, bossVelX, bossVelY, bossActive);
				LevelManager::getInstance().setCurLevel(LevelManager::Level3);

				break;


			default:
				break;
			}
			
		}


		/*file << lm.getSaveLevel() << std::endl;
		file << lm.getSaveScore() << std::endl;
		file << lm.getSaveTime() << std::endl;

		file << lm.getSaveMap().size() << std::endl;
		for (int i = 0; i < lm.getSaveMap().size(); i++) {
			file << lm.getSaveMap()[i] << std::endl;
		}

		file << lm.getSaveMonsterPos().size() << std::endl;

		for (int i = 0; i < lm.getSaveMonsterPos().size(); i++) {
			file << lm.getSaveMonsterPos()[i].first << " " << lm.getSaveMonsterPos()[i].second << std::endl;
		}
		for (int i = 0; i < lm.getSaveMonsterType().size(); i++) {
			file << lm.getSaveMonsterType()[i] << std::endl;
		}

		file << lm.getSavePlayerProjectilePos().size() << std::endl;
		for (int i = 0; i < lm.getSavePlayerProjectilePos().size(); i++) {
			file << lm.getSavePlayerProjectilePos()[i].first << " " << lm.getSavePlayerProjectilePos()[i].second << std::endl;
		}
		for (int i = 0; i < lm.getSaveMonsterProjectilePos().size(); i++) {
			file << lm.getSaveMonsterProjectilePos()[i].first << " " << lm.getSaveMonsterProjectilePos()[i].second << std::endl;
		}
		for (int i = 0; i < lm.getSavePlayerProjectileDir().size(); i++) {
			file << lm.getSavePlayerProjectileDir()[i] << std::endl;
		}
		for (int i = 0; i < lm.getSaveMonsterProjectileDir().size(); i++) {
			file << lm.getSaveMonsterProjectileDir()[i] << std::endl;
		}
		for (int i = 0; i < lm.getSavePlayerProjectileVel().size(); i++) {
			file << lm.getSavePlayerProjectileVel()[i].first << " " << lm.getSavePlayerProjectileVel()[i].second << std::endl;
		}
		for (int i = 0; i < lm.getSaveMonsterProjectileVel().size(); i++) {
			file << lm.getSaveMonsterProjectileVel()[i].first << " " << lm.getSaveMonsterProjectileVel()[i].second << std::endl;
		}
		file << lm.getSaveItemPos().size() << std::endl;
		for (int i = 0; i < lm.getSaveItemPos().size(); i++) {
			file << lm.getSaveItemPos()[i].first << " " << lm.getSaveItemPos()[i].second << std::endl;
		}
		for (int i = 0; i < lm.getSaveItemType().size(); i++) {
			file << lm.getSaveItemType()[i] << std::endl;
		}

		file << lm.getPlayerType() << std::endl;
		file << lm.getSavePlayerPosX() << " " << lm.getSavePlayerPosY() << std::endl;
		file << lm.getPlayerHP() << std::endl;
		file << lm.getPlayerStatus() << std::endl;
		file << lm.getPlayerVelX() << " " << lm.getPlayerVelY() << std::endl;
		file << lm.getSaveBossPosX() << " " << lm.getSaveBossPosY() << std::endl;
		file << lm.getBossHP() << std::endl;
		file << lm.getBossVelX() << " " << lm.getBossVelY() << std::endl;*/
		for (int i = 0; i <= level; i++) {
			LevelManager::getInstance().setLevels(i, 1);
		}
		return;
	}

	
	switch (LevelManager::getInstance().getCurCharacter() + 1)
	{
	case 1:
		std::cout << "GameState 1" << "\n";

		idleTextures.push_back(context.textures->get(Textures::WukongStand1));
		idleTextures.push_back(context.textures->get(Textures::WukongStand2));
		idleTextures.push_back(context.textures->get(Textures::WukongStand3));
		idleTextures.push_back(context.textures->get(Textures::WukongStand4));
		
		runTextures.push_back(context.textures->get(Textures::WukongRun1));
		runTextures.push_back(context.textures->get(Textures::WukongRun2));
		runTextures.push_back(context.textures->get(Textures::WukongRun3));
		runTextures.push_back(context.textures->get(Textures::WukongRun4));

		jumpTextures.push_back(context.textures->get(Textures::WukongJump1));
		jumpTextures.push_back(context.textures->get(Textures::WukongJump2));
		jumpTextures.push_back(context.textures->get(Textures::WukongJump3));
		jumpTextures.push_back(context.textures->get(Textures::WukongJump4));
		std::cout << "GameState 22" << "\n";

		attackTextures.push_back(context.textures->get(Textures::WukongAttack1));
		attackTextures.push_back(context.textures->get(Textures::WukongAttack2));

		sIdleTextures.push_back(context.textures->get(Textures::SmallWukongStand1));
		sIdleTextures.push_back(context.textures->get(Textures::SmallWukongStand2));
		sIdleTextures.push_back(context.textures->get(Textures::SmallWukongStand3));
		sIdleTextures.push_back(context.textures->get(Textures::SmallWukongStand4));
		std::cout << "GameState 33" << "\n";

		sRunTextures.push_back(context.textures->get(Textures::SmallWukongRun1));
		sRunTextures.push_back(context.textures->get(Textures::SmallWukongRun2));
		sRunTextures.push_back(context.textures->get(Textures::SmallWukongRun3));
		sRunTextures.push_back(context.textures->get(Textures::SmallWukongRun4));

		deadTextures.push_back(context.textures->get(Textures::DeadWukong1));
		deadTextures.push_back(context.textures->get(Textures::DeadWukong2));
		deadTextures.push_back(context.textures->get(Textures::DeadWukong3));
		deadTextures.push_back(context.textures->get(Textures::DeadWukong4));
		deadTextures.push_back(context.textures->get(Textures::DeadWukong5));
		deadTextures.push_back(context.textures->get(Textures::DeadWukong6));
		deadTextures.push_back(context.textures->get(Textures::DeadWukong7));
		deadTextures.push_back(context.textures->get(Textures::DeadWukong8));
		deadTextures.push_back(context.textures->get(Textures::DeadWukong9));

		hurtTextures.push_back(context.textures->get(Textures::WukongHurt1));
		hurtTextures.push_back(context.textures->get(Textures::WukongHurt2));
		hurtTextures.push_back(context.textures->get(Textures::WukongHurt3));

		sHurtTextures.push_back(context.textures->get(Textures::SmallWukongHurt1));
		sHurtTextures.push_back(context.textures->get(Textures::SmallWukongHurt2));
		sHurtTextures.push_back(context.textures->get(Textures::SmallWukongHurt3));


		player = new FirstCharacter(idleTextures, runTextures, attackTextures, jumpTextures, hurtTextures, sIdleTextures, sRunTextures, sIdleTextures, sRunTextures,sHurtTextures , deadTextures, 100, 100, 1);
		std::cout << "GameState 1.1" << "\n";

		break;

	case 2:
		idleTextures.push_back(context.textures->get(Textures::SecondWukongStand1));
		idleTextures.push_back(context.textures->get(Textures::SecondWukongStand2));
		idleTextures.push_back(context.textures->get(Textures::SecondWukongStand3));
		idleTextures.push_back(context.textures->get(Textures::SecondWukongStand4));
		idleTextures.push_back(context.textures->get(Textures::SecondWukongStand5));

		runTextures.push_back(context.textures->get(Textures::SecondWukongRun1));
		runTextures.push_back(context.textures->get(Textures::SecondWukongRun2));
		runTextures.push_back(context.textures->get(Textures::SecondWukongRun3));
		runTextures.push_back(context.textures->get(Textures::SecondWukongRun4));
		runTextures.push_back(context.textures->get(Textures::SecondWukongRun5));
		runTextures.push_back(context.textures->get(Textures::SecondWukongRun6));
		runTextures.push_back(context.textures->get(Textures::SecondWukongRun7));
		runTextures.push_back(context.textures->get(Textures::SecondWukongRun8));

		jumpTextures.push_back(context.textures->get(Textures::SecondWukongRun1));
		jumpTextures.push_back(context.textures->get(Textures::SecondWukongRun2));
		jumpTextures.push_back(context.textures->get(Textures::SecondWukongRun3));
		jumpTextures.push_back(context.textures->get(Textures::SecondWukongRun4));
		jumpTextures.push_back(context.textures->get(Textures::SecondWukongRun5));
		jumpTextures.push_back(context.textures->get(Textures::SecondWukongRun6));
		jumpTextures.push_back(context.textures->get(Textures::SecondWukongRun7));
		jumpTextures.push_back(context.textures->get(Textures::SecondWukongRun8));

		attackTextures.push_back(context.textures->get(Textures::SecondWukongAttack1));
		attackTextures.push_back(context.textures->get(Textures::SecondWukongAttack2));
		attackTextures.push_back(context.textures->get(Textures::SecondWukongAttack3));
		attackTextures.push_back(context.textures->get(Textures::SecondWukongAttack4));
		attackTextures.push_back(context.textures->get(Textures::SecondWukongAttack5));

		deadTextures.push_back(context.textures->get(Textures::SecondWukongDead1));
		deadTextures.push_back(context.textures->get(Textures::SecondWukongDead2));
		deadTextures.push_back(context.textures->get(Textures::SecondWukongDead3));
		deadTextures.push_back(context.textures->get(Textures::SecondWukongDead4));
		deadTextures.push_back(context.textures->get(Textures::SecondWukongDead5));
		deadTextures.push_back(context.textures->get(Textures::SecondWukongDead6));
		deadTextures.push_back(context.textures->get(Textures::SecondWukongDead7));

		hurtTextures.push_back(context.textures->get(Textures::SecondWukongHurt1));
		hurtTextures.push_back(context.textures->get(Textures::SecondWukongHurt2));
		hurtTextures.push_back(context.textures->get(Textures::SecondWukongHurt3));

		player = new SecondCharacter(idleTextures, runTextures, attackTextures, jumpTextures, hurtTextures, idleTextures, runTextures, idleTextures, runTextures, hurtTextures, deadTextures, 200*32, 300, 2);

		break;

	default:
		break;
	}

	switch (LevelManager::getInstance().getCurLevel() + 1)
	{
		case 1:

			tileset = context.textures->get(Textures::Blocks);
			mapTextures.push_back(tileset);
			mapTextures.push_back(monsterset);
			mapTextures.push_back(projectile);
			mapTextures.push_back(enemyProjectile);
			/*audioManager = new AudioManagement();
			audioManager->playMainMusic();*/
			gameMap = new Map("../resources/Level1/level.txt", 32, mapTextures);
			gameMap->level = 1;
			backgroundTexture = context.textures->get(Textures::Bg1);
			backgroundSprite.setTexture(context.textures->get(Textures::Bg1));
			std::cout << gameMap->getMapData().size() << "\n";
			xRepeatCount = gameMap->getMapData()[0].size() * 32 / backgroundTexture.getSize().x + 1;  // Add 1 to ensure coverage
			yRepeatCount = gameMap->getMapData().size() * 32 / backgroundTexture.getSize().y + 1;
			break;
    case 2:
      tileset = context.textures->get(Textures::Blocks2);
      mapTextures.push_back(tileset);
      mapTextures.push_back(monsterset);
      mapTextures.push_back(projectile);
      mapTextures.push_back(enemyProjectile);

      gameMap = new Map("../resources/Level2/level.txt", 32, mapTextures);
	  gameMap->level = 2;
      backgroundTexture = context.textures->get(Textures::Bg2);
      backgroundSprite.setTexture(context.textures->get(Textures::Bg2));
      std::cout << gameMap->getMapData().size() << "\n";
      xRepeatCount = gameMap->getMapData()[0].size() * 32 / backgroundTexture.getSize().x + 1;  // Add 1 to ensure coverage
      yRepeatCount = gameMap->getMapData().size() * 32 / backgroundTexture.getSize().y + 1;

      break;
    case 3:
      tileset = context.textures->get(Textures::Blocks3);
      mapTextures.push_back(tileset);
      mapTextures.push_back(monsterset);
      mapTextures.push_back(projectile);
      mapTextures.push_back(enemyProjectile);

      gameMap = new Map("../resources/Level3/level.txt", 32, mapTextures);
	  gameMap->level = 3;
      backgroundTexture = context.textures->get(Textures::Bg3);
      backgroundSprite.setTexture(context.textures->get(Textures::Bg3));
      std::cout << gameMap->getMapData().size() << "\n";
      xRepeatCount = gameMap->getMapData()[0].size() * 32 / backgroundTexture.getSize().x + 1;  // Add 1 to ensure coverage
      yRepeatCount = gameMap->getMapData().size() * 32 / backgroundTexture.getSize().y + 1;
	  bossAttackTextures.push_back(context.textures->get(Textures::BossAttack1));
	  bossAttackTextures.push_back(context.textures->get(Textures::BossAttack2));
	  bossAttackTextures.push_back(context.textures->get(Textures::BossAttack3));

	  bossDeadTextures.push_back(context.textures->get(Textures::BossDead1));
	  bossDeadTextures.push_back(context.textures->get(Textures::BossDead2));
	  bossDeadTextures.push_back(context.textures->get(Textures::BossDead3));
	  bossDeadTextures.push_back(context.textures->get(Textures::BossDead4));
	  bossDeadTextures.push_back(context.textures->get(Textures::BossDead5));
	  bossDeadTextures.push_back(context.textures->get(Textures::BossDead6));
	  bossDeadTextures.push_back(context.textures->get(Textures::BossDead7));

	  bossExhaustedTextures.push_back(context.textures->get(Textures::BossExhausted1));
	  bossExhaustedTextures.push_back(context.textures->get(Textures::BossExhausted2));

	  bossFlyingTextures.push_back(context.textures->get(Textures::BossFly1));
	  bossFlyingTextures.push_back(context.textures->get(Textures::BossFly2));
	  bossFlyingTextures.push_back(context.textures->get(Textures::BossFly3));
	  bossFlyingTextures.push_back(context.textures->get(Textures::BossFly4));

	  bossShootTextures.push_back(context.textures->get(Textures::BossShoot1));
	  bossShootTextures.push_back(context.textures->get(Textures::BossShoot2));

	  boss = new Boss(bossFlyingTextures, bossAttackTextures, bossDeadTextures, bossExhaustedTextures, bossShootTextures, 325*32, 100);

      break;


	default:
		break;
	}
	std::cout << "GameState 2" << "\n";

}

bool GameState::update(sf::Time dt) {


	float deltaTime = dt.asSeconds();
	elapsedTime += deltaTime;
	sf::RenderWindow& window = *getContext().window;
	std::vector<std::string>& mapData = gameMap->getMapData();
				sf::FloatRect playerBounds = player->getBounds();
				std::vector<Monster*> monsters = gameMap->getMonsters();
				ProjectileManager& projectiles = gameMap->getProjectiles();
				AudioManagement* audioManager = gameMap->getAudioManager();
				int tileSize = gameMap->getTileSize();

				// Update camera position based on player position
				int mapWidth = gameMap->getMapData()[0].size() * gameMap->getTileSize();
				int mapHeight = gameMap->getMapData().size() * gameMap->getTileSize();

				// Make sure the camera stays within the bounds of the map
				float cameraX = std::max(constants::scene_width / 2.f, std::min(player->getBounds().left + player->getBounds().width / 2, mapWidth - constants::scene_width / 2.f));
				float cameraY = std::max(constants::scene_height / 2.f, std::min(player->getBounds().top + player->getBounds().height / 2, mapHeight - constants::scene_height / 2.f));

				camera.setCenter(cameraX, cameraY);
				window.setView(camera);


	// Update player and game state
	        player->interact(deltaTime, gameMap);
	        player->update(deltaTime, gameMap);

			//gameMap->updateBlocks(deltaTime,player->getBounds());
			std::vector<Block*> blocks = gameMap->getBlocks();
			for (auto it = blocks.begin(); it != blocks.end();) {
				auto& block = *it;
				block->update(deltaTime, mapData, tileSize);
				playerBounds.top -= 4.0f;
				if (block->isCollission(playerBounds) && !block->getIsDestroyed()) {
					//std::cout << "Collision detected" << std::endl;
					float playerTop = playerBounds.top;
					float blockBottom = block->getBounds().top + block->getBounds().height;
					float dy = blockBottom - playerTop;
					if (dy < 5.0f) {
						if (!block->getIsTouched()) {
							if (dynamic_cast<QuestionBlock*>(block)) {
								int tileX = (block->getBounds().left + 5.0f) / tileSize;
								int tileY = (block->getBounds().top + 5.0f) / tileSize;
								//std::cout << "QuestionBlock:" << tileY << " " << tileX << std::endl;
								//std::cout << mapData[tileY][tileX] << std::endl;
								block->setState(new ActiveState());
								block->onTouch2(mapData, tileSize, gameMap->getTexture());
								auto item = block->getItemObject();
								if (dynamic_cast<Coin*>(item)) {
									this->getContext().audio->playCoinSound();
									gameMap->increaseCoinsNumber();
								}
								else if (dynamic_cast<PowerUp*>(item)) {
									gameMap->addCoins(item);
								}
								mapData[tileY][tileX] = '9';
							}
							else if (dynamic_cast<BrickBlock*>(block) && player->isEvoled()) {
								block->setState(new DestroyedState());
								block->onTouch2(mapData, tileSize,
									gameMap->getTexture());
								block->setDestroyed(true);
								this->getContext().audio->playDestroyBlockSound();
							}
						}
					}

				}
				playerBounds.top += 4.0f;

				if (dynamic_cast<FlagBlock*>(block)) {
					if (playerBounds.left + playerBounds.width + 5 > block->getBounds().left && playerBounds.top + playerBounds.height > block->getBounds().top && playerBounds.left < block->getBounds().left) {
						if (!boss || boss->isDead()) win = true;
					}
				}
				//interact with water block --> die
				if (dynamic_cast<WaterBlock*>(block)) {
					if (playerBounds.intersects(block->getBounds())) {
						player->dead(gameMap);
					}
				}
				it++;
			}

			if (boss) {
				if (!boss->isActivated()) {
					sf::Vector2f playerPos = player->getBounds().getPosition();
					sf::Vector2f bossPos = boss->getPosition();
					if (abs(playerPos.x - bossPos.x) < 200) {
						boss->activate();
						this->getContext().music->play(Music::BossFightTheme);
						this->getContext().audio->playMonsterRoarSound();
					}
				}
				else {
					boss->interact(deltaTime, gameMap, player->getBounds().getPosition());
					boss->update(deltaTime, gameMap);
				}
			}

			
	        //gameMap->updateCoins(player->getBounds(), deltaTime);
			std::vector<Item*> coins = gameMap->getCoins();
			for (auto& coin : coins) {
				coin->update(deltaTime, mapData, 32);
				if (coin->getBounds().intersects(playerBounds) && !coin->isCollected()) {
					this->getContext().audio->playCoinSound();
					coin->collect(); // Collect the coin
					if (dynamic_cast<Coin*>(coin)) {
						gameMap->increaseCoinsNumber();
            int tileX = static_cast<int>(coin->getBounds().left / tileSize);
            int tileY = static_cast<int>(coin->getBounds().top /tileSize);
            mapData[tileY][tileX] = '0';
                                        
					}
					else if (dynamic_cast<PowerUp*>(coin)) {
						player->levelUp(gameMap);
					}

				}
			}

	        gameMap->updateScore();
	
	      
	        //gameMap->updateMonsters(deltaTime, player->getBounds(), camera);
			for (auto it = monsters.begin(); it != monsters.end();) {
				auto& monster = *it;  // Use reference for clarity and efficiency
				if (!gameMap->isVissible(monster->getSprite(), camera)) {
					++it;
					continue;
				}
				monster->update(deltaTime, mapData, tileSize);

				// Get player and monster positions
				sf::FloatRect monsterBounds = monster->getBounds();
				for (int i = 0; i < projectiles.getProjectiles().size(); ++i) {

					if (projectiles.getProjectiles()[i]->getBounds().intersects(monsterBounds)) {
						this->getContext().audio->playMonsterHitSound();
						projectiles.destroyProjectile(i);
						auto tileX = static_cast<int>(monsterBounds.left / tileSize);
						auto tileY = static_cast<int>(monsterBounds.top / tileSize);

						mapData[tileY][tileX] = '0';
						monster->kill(true, monster);
					}


				}

				// Check intersection
				if (monsterBounds.intersects(playerBounds) && !monster->getIsKilled()) {
					//std::cout<< "Monster collision detected" << std::endl;
					// Check if the player is above the monster
					float playerBottom =
						playerBounds.top + playerBounds.height;  // Bottom of the player
					float monsterTop = monsterBounds.top;      // Top of the monster


					if (playerBottom <= monsterTop + 5.0f) {  // Allow a small tolerance
						this->getContext().audio->playMonsterHitSound();
						// Monster is killed
						auto tileX = static_cast<int>(monsterBounds.left / tileSize);
						auto tileY = static_cast<int>(monsterBounds.top / tileSize);

						mapData[tileY][tileX] = '0';
						player->knockUp(gameMap);
						monster->kill(true, monster);  // Kill the monster

					}
					else {
						//std::cout<< "Player is killed" << std::endl;
						if (!monster->getIsKilled()) {
							player->damaged(gameMap);
						}
					}
				}

				++it;  // Increment the iterator if no monster was removed
			}
			
			ProjectileManager& enemyProjectiles = gameMap->getEnemyProjectiles();
			for (int j = 0; j < enemyProjectiles.getProjectiles().size(); j++) {
				Projectile* projectile = enemyProjectiles.getProjectiles()[j];
				projectile->update(deltaTime);
				if (projectile->getBounds().intersects(playerBounds) && !projectile->isDestroyed() ) {
					if (!player->isDead()) {
						player->damaged(gameMap);
					}
					enemyProjectiles.destroyProjectile(j);
				}
					
					for (int i = 0; i < projectiles.getProjectiles().size(); ++i) {
						if (projectiles.getProjectiles()[i]->getBounds().intersects(projectile->getBounds()) && !projectiles.getProjectiles()[i]->isDestroyed() && !projectile->isDestroyed() ) {
							projectiles.destroyProjectile(i);
							enemyProjectiles.destroyProjectile(j);
						}
					}
			}

			if (boss) {
				for (int i = 0; i < projectiles.getProjectiles().size(); ++i) {

					if (boss) {
						if (boss->getBounds().intersects(projectiles.getProjectiles()[i]->getBounds())) {
							boss->damaged(gameMap);
							projectiles.destroyProjectile(i);

						}
					}

				}
				if (boss->getBounds().intersects(playerBounds) && !boss->isDead()) {
					if (!player->isDead()) {
						player->damaged(gameMap);
					}
				}
			}



			
			

			for (auto it = projectiles.getProjectiles().begin(); it != projectiles.getProjectiles().end();) {
				auto& projectile = *it;
				if (projectile->isDestroyed()) {
					it = projectiles.getProjectiles().erase(it);
					//delete projectile;
					}
				else {
					++it;
					}
				}

			for (auto it = enemyProjectiles.getProjectiles().begin(); it != enemyProjectiles.getProjectiles().end();) {
				auto& projectile = *it;
				if (projectile->isDestroyed()) {
					it = enemyProjectiles.getProjectiles().erase(it);
					//delete projectile;
					}
				else {
					++it;
					}
				}

		
			

	        gameMap->updateProjectiles(deltaTime);
			gameMap->updateEnemyProjectiles(deltaTime);

		

			if (win) {
				win = 0;
				LevelManager::getInstance().setScore(gameMap->score);
				LevelManager::getInstance().setTime(elapsedTime);
				requestStackPush(States::LevelComplete);
			}

			else if (player->isDead()) {

				if (deadTime <= 0) requestStackPush(States::GameOver);
				else deadTime -= deltaTime;
			}

			if (boss) {
        if (!bossPoint && boss->isDead()) {
                            bossPoint = true;
          gameMap->addConstanScore(10000);
		  this->getContext().music->play(Music::GameTheme);
		  this->getContext().audio->playMonsterRoarSound();

                          }
      }
			

			return false;
}

void GameState::draw() {
	sf::RenderWindow& window = *getContext().window;
	window.setView(camera);
	for (int i = 0; i < xRepeatCount; ++i) {
		            for (int j = 0; j < yRepeatCount; ++j) {
		                backgroundSprite.setPosition(i * backgroundTexture.getSize().x, j * backgroundTexture.getSize().y);
		                window.draw(backgroundSprite); 
		            }
		        }
	gameMap->draw(window);
	player->draw(window);
	//player->drawBounds(window);
	if (boss) {
		boss->draw(window);
		//boss->drawBounds(window);
	}
	/*for (auto& monster : gameMap->getMonsters()) {
		monster->drawBounds(window);
	}*/
	if (boss && boss->isActivated() && !boss->isDead()) {
		drawEngine->displayBossHealth(window, elapsedTime, gameMap, player, boss);
	}
	else drawEngine->displayGameInfo(window, elapsedTime, gameMap, player);
	
	window.draw(PauseButton);
}

bool GameState::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (PauseButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    LevelManager::getInstance().resetSave();
        saveGame();

				requestStackPush(States::Pause);
			}
		}
	}
	else if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			saveGame();
			
			requestStackPush(States::Pause);
		}
		else if (event.key.code == sf::Keyboard::W) {
			LevelManager::getInstance().setScore(gameMap->score);
			LevelManager::getInstance().setTime(elapsedTime);
			requestStackPush(States::LevelComplete);
		}
		else if (event.key.code == sf::Keyboard::L) {
			requestStackPush(States::GameOver);
		}
	}

	return false;
}


void GameState::saveGame() {
	LevelManager& lm = LevelManager::getInstance();
	lm.setScore(gameMap->score);
	lm.setTime(elapsedTime);
	lm.setSaveLevel(static_cast<int>(lm.getCurLevel()));
	lm.setSaveCharacter(static_cast<int>(lm.getCurCharacter()));
	std::vector<Item*> coins = gameMap->getCoins();
	for (auto& coin : coins) {
		if (!coin->isCollected()) {
			lm.addItems(coin);
		}
	}
	std::vector<Monster*> monsters = gameMap->getMonsters();
        std::cout << "Monster size: " << monsters.size() << std::endl;
	for (auto& monster : monsters) {
		if (!monster->getIsKilled()) {
			lm.addMonster(monster);
		}
	}

	if (boss) lm.saveFromBoss(boss);
	lm.saveFromCharacter(player);
	lm.saveFromMap(gameMap, elapsedTime);

}

void GameState::loadGame() {
	
	LevelManager& lm = LevelManager::getInstance();
	std::ifstream file;
	file.open("../resources/save.txt");
	if (file) {
		int level, score, time;
		file >> level >> score >> time;
		std::vector<std::string> map;
		int mapSize;
		file >> mapSize;
		for (int i = 0; i < mapSize; i++) {
			std::string line;
			file >> line;
			map.push_back(line);
		}
		int monsterSize;
		file >> monsterSize;
		std::vector<std::pair<float, float>> monsterPos;
		std::vector<char> monsterType;
		for (int i = 0; i < monsterSize; i++) {
			float x, y;
			file >> x >> y;
			monsterPos.push_back(std::make_pair(x, y));
		}
		for (int i = 0; i < monsterSize; i++) {
			int type;
			file >> type;
			monsterType.push_back(type);
		}
		int playerProjectileSize;
		file >> playerProjectileSize;
		std::vector<std::pair<float, float>> playerProjectilePos;
		std::vector<int> playerProjectileDir;
		std::vector<std::pair<float, float>> playerProjectileVel;
		for (int i = 0; i < playerProjectileSize; i++) {
			float x, y;
			file >> x >> y;
			playerProjectilePos.push_back(std::make_pair(x, y));
		}
		for (int i = 0; i < playerProjectileSize; i++) {
			int dir;
			file >> dir;
			playerProjectileDir.push_back(dir);
		}
		for (int i = 0; i < playerProjectileSize; i++) {
			float x, y;
			file >> x >> y;
			playerProjectileVel.push_back(std::make_pair(x, y));
		}
		int monsterProjectileSize;
		file >> monsterProjectileSize;
		std::vector<std::pair<float, float>> monsterProjectilePos;
		std::vector<int> monsterProjectileDir;
		std::vector<std::pair<float, float>> monsterProjectileVel;
		for (int i = 0; i < monsterProjectileSize; i++) {
			float x, y;
			file >> x >> y;
			monsterProjectilePos.push_back(std::make_pair(x, y));
		}
		for (int i = 0; i < monsterProjectileSize; i++) {
			int dir;
			file >> dir;
			monsterProjectileDir.push_back(dir);
		}
		for (int i = 0; i < monsterProjectileSize; i++) {
			float x, y;
			file >> x >> y;
			monsterProjectileVel.push_back(std::make_pair(x, y));
		}
		int itemSize;
		file >> itemSize;
		std::vector<std::pair<float, float>> itemPos;
		std::vector<int> itemType;
		for (int i = 0; i < itemSize; i++) {
			float x, y;
			file >> x >> y;
			itemPos.push_back(std::make_pair(x, y));
		}
		for (int i = 0; i < itemSize; i++) {
			int type;
			file >> type;
			itemType.push_back(type);
		}
		int playerType;
		file >> playerType;
    if (playerType == 1) {
                  LevelManager::getInstance().setCurCharacter(LevelManager::wukong);
                }
    else {
                  LevelManager::getInstance().setCurCharacter(
                    LevelManager::pig);
    }
		float playerX, playerY;
		file >> playerX >> playerY;
		int playerHP;
		file >> playerHP;
		int playerStatus;
		file >> playerStatus;
		float playerVelX, playerVelY;
		file >> playerVelX >> playerVelY;
		int hasBoss;
		file >> hasBoss;
		if (hasBoss) {
			float bossX, bossY;
			file >> bossX >> bossY;
			int bossHP;
			file >> bossHP;
			float bossVelX, bossVelY;
			file >> bossVelX >> bossVelY;
		}

		switch (playerType)
		{
		case 1:

			player = new Character(idleTextures, runTextures, attackTextures, jumpTextures, hurtTextures, sIdleTextures, sRunTextures, sIdleTextures, sRunTextures, sHurtTextures, deadTextures, playerX, playerY, playerType, playerHP,playerVelX, playerVelY, playerStatus);
			break;
		default:
			break;
		}
	}


	/*file << lm.getSaveLevel() << std::endl;
	file << lm.getSaveScore() << std::endl;
	file << lm.getSaveTime() << std::endl;

	file << lm.getSaveMap().size() << std::endl;
	for (int i = 0; i < lm.getSaveMap().size(); i++) {
		file << lm.getSaveMap()[i] << std::endl;
	}

	file << lm.getSaveMonsterPos().size() << std::endl;

	for (int i = 0; i < lm.getSaveMonsterPos().size(); i++) {
		file << lm.getSaveMonsterPos()[i].first << " " << lm.getSaveMonsterPos()[i].second << std::endl;
	}
	for (int i = 0; i < lm.getSaveMonsterType().size(); i++) {
		file << lm.getSaveMonsterType()[i] << std::endl;
	}

	file << lm.getSavePlayerProjectilePos().size() << std::endl;
	for (int i = 0; i < lm.getSavePlayerProjectilePos().size(); i++) {
		file << lm.getSavePlayerProjectilePos()[i].first << " " << lm.getSavePlayerProjectilePos()[i].second << std::endl;
	}
	for (int i = 0; i < lm.getSaveMonsterProjectilePos().size(); i++) {
		file << lm.getSaveMonsterProjectilePos()[i].first << " " << lm.getSaveMonsterProjectilePos()[i].second << std::endl;
	}
	for (int i = 0; i < lm.getSavePlayerProjectileDir().size(); i++) {
		file << lm.getSavePlayerProjectileDir()[i] << std::endl;
	}
	for (int i = 0; i < lm.getSaveMonsterProjectileDir().size(); i++) {
		file << lm.getSaveMonsterProjectileDir()[i] << std::endl;
	}
	for (int i = 0; i < lm.getSavePlayerProjectileVel().size(); i++) {
		file << lm.getSavePlayerProjectileVel()[i].first << " " << lm.getSavePlayerProjectileVel()[i].second << std::endl;
	}
	for (int i = 0; i < lm.getSaveMonsterProjectileVel().size(); i++) {
		file << lm.getSaveMonsterProjectileVel()[i].first << " " << lm.getSaveMonsterProjectileVel()[i].second << std::endl;
	}
	file << lm.getSaveItemPos().size() << std::endl;
	for (int i = 0; i < lm.getSaveItemPos().size(); i++) {
		file << lm.getSaveItemPos()[i].first << " " << lm.getSaveItemPos()[i].second << std::endl;
	}
	for (int i = 0; i < lm.getSaveItemType().size(); i++) {
		file << lm.getSaveItemType()[i] << std::endl;
	}

	file << lm.getPlayerType() << std::endl;
	file << lm.getSavePlayerPosX() << " " << lm.getSavePlayerPosY() << std::endl;
	file << lm.getPlayerHP() << std::endl;
	file << lm.getPlayerStatus() << std::endl;
	file << lm.getPlayerVelX() << " " << lm.getPlayerVelY() << std::endl;
	file << lm.getSaveBossPosX() << " " << lm.getSaveBossPosY() << std::endl;
	file << lm.getBossHP() << std::endl;
	file << lm.getBossVelX() << " " << lm.getBossVelY() << std::endl;*/

}

GameState::~GameState() {
	delete player;
	delete gameMap;
	delete drawEngine;
	if (boss) {
		delete boss;
	}
}















//MenuState::MenuState(StateStack& stack, Context context) : State(stack, context), mBackgroundSprite(), mGUIContainer(GUI::Container::TopDown) {
//    sf::Texture& texture = context.textures->get(Textures::MainMenuBG_1);
//    mBackgroundSprite.push_back(sf::Sprite(texture));
//
//    sf::Texture& texture_1 = context.textures->get(Textures::MainMenuBG_2);
//    mBackgroundSprite.push_back(sf::Sprite(texture_1));
//
//    sf::Texture& texture_2 = context.textures->get(Textures::MainMenuBG_3);
//    mBackgroundSprite.push_back(sf::Sprite(texture_2));
//
//    sf::Sprite tmp;
//
//    sf::Texture& texture_3 = context.textures->get(Textures::MainMenuClound_1);
//    tmp = sf::Sprite(texture_3);
//    tmp.setPosition(0, 37);
//    mCloundSprite.push_back(tmp);
//
//    sf::Texture& texture_4 = context.textures->get(Textures::MainMenuClound_2);
//    tmp = sf::Sprite(texture_4);
//    tmp.setPosition(475, 48);
//    mCloundSprite.push_back(tmp);
//
//    sf::Texture& texture_5 = context.textures->get(Textures::MainMenuClound_3);
//    tmp = sf::Sprite(texture_5);
//    tmp.setPosition(950, 37);
//    mCloundSprite.push_back(tmp);
//
//    sf::Texture& texture_6 = context.textures->get(Textures::MainMenuClound_4);
//    tmp = sf::Sprite(texture_6);
//    tmp.setPosition(0, 10);
//    mCloundSprite.push_back(tmp);
//
//    sf::Texture& texture_7 = context.textures->get(Textures::MainMenuClound_5);
//    tmp = sf::Sprite(texture_7);
//    tmp.setPosition(449, 3);
//    mCloundSprite.push_back(tmp);
//
//    sf::Texture& texture_8 = context.textures->get(Textures::MainMenuClound_6);
//    tmp = sf::Sprite(texture_8);
//    tmp.setPosition(897, 0);
//    mCloundSprite.push_back(tmp);
//
//    sf::Texture& texture_9 = context.textures->get(Textures::MainMenuClound_7);
//    tmp = sf::Sprite(texture_9);
//    tmp.setPosition(345, -9);
//    mCloundSprite.push_back(tmp);
//
//    sf::Texture& texture_10 = context.textures->get(Textures::MainMenuClound_8);
//    tmp = sf::Sprite(texture_10);
//    tmp.setPosition(759, -9);
//    mCloundSprite.push_back(tmp);
//
//
//    auto playButton = std::make_shared<GUI::Button>(context, Textures::button, 150, 45);
//    playButton->setPosition(565, 380);
//    playButton->setText("Play");
//    playButton->setCallback([this]() {
//        //requestStackPop();
//        requestStackPush(States::Level);
//        std::cout << "Play button pressed" << std::endl;
//        });
//
//    auto guideButton = std::make_shared<GUI::Button>(context, Textures::button, 150, 45);
//    guideButton->setPosition(565, 440);
//    guideButton->setText("Guide");
//    guideButton->setCallback([this]() {
//        //requestStackPop();
//        requestStackPush(States::Guide);
//        std::cout << "Guide button pressed" << std::endl;
//        });
//
//
//    auto settingButton = std::make_shared<GUI::Button>(context, Textures::button, 150, 45);
//    settingButton->setPosition(565, 500);
//    settingButton->setText("Setting");
//    settingButton->setCallback([this]() {
//        //requestStackPop();
//        //requestStackPush(States::Game);
//        std::cout << "Setting button pressed" << std::endl;
//        });
//
//    auto exitButton = std::make_shared<GUI::Button>(context, Textures::button, 150, 45);
//    exitButton->setPosition(565, 560);
//    exitButton->setText("Quit");
//    exitButton->setCallback([this]() {
//        requestStackPop();
//        });
//
//    mGUIContainer.pack(playButton);
//    mGUIContainer.pack(guideButton);
//    mGUIContainer.pack(settingButton);
//    mGUIContainer.pack(exitButton);
//
//    sf::Font& font = context.fonts->get(Fonts::NameGame);
//
//    wukongText.setFont(font);
//    wukongText.setString("Journey to the West");
//    wukongText.setCharacterSize(120);
//    wukongText.setFillColor(sf::Color(0, 0, 0, 255));
//    wukongText.setOrigin(wukongText.getLocalBounds().width / 2.0f, wukongText.getLocalBounds().height / 2.0f);
//    wukongText.setPosition(640, 150);
//    wukongText.setScale(mScale, mScale);
//
//    // Khởi tạo bóng của chữ
//    shadowText = wukongText; // Copy toàn bộ thuộc tính từ chữ chính
//    shadowText.setFillColor(sf::Color(0, 0, 0, 128)); // Màu đen mờ hơn
//    shadowText.setPosition(wukongText.getPosition().x + 5, wukongText.getPosition().y + 5); // Lệch vị trí
//
//}
//
//void MenuState::draw() {
//    sf::RenderWindow& window = *getContext().window;
//    window.setView(window.getDefaultView());
//
//    for (const sf::Sprite& sprite : mBackgroundSprite) {
//        window.draw(sprite);
//    }
//
//    for (int i = mCloundSprite.size() - 1; i >= 0; i--) {
//        sf::Sprite& sprite = mCloundSprite[i];
//        window.draw(sprite);
//    }
//
//    window.draw(mGUIContainer);
//
//
//
//    window.draw(shadowText);
//    window.draw(wukongText);
//}
//
//bool MenuState::update(sf::Time deltatime)
//{
//
//
//    if (mTextState == ScalingUp) {
//        float scaleSpeed = 0.5f * deltatime.asSeconds();
//        mScale += scaleSpeed;
//        if (mScale >= 1.0f) {
//            mScale = 1.0f;
//            mTextState = None;
//        }
//        wukongText.setScale(mScale, mScale);
//        shadowText.setScale(mScale, mScale);
//
//    }
//
//
//
//    for (int i = 0; i < mCloundSprite.size(); i++) {
//        sf::Sprite& sprite = mCloundSprite[i];
//        sprite.move(-speed[i] * deltatime.asSeconds(), 0);
//        if (sprite.getPosition().x < -sprite.getLocalBounds().width) {
//            sprite.setPosition(1280, sprite.getPosition().y);
//        }
//    }
//
//
//
//    return false;
//}
//
//bool MenuState::handleEvent(const sf::Event& event)
//{
//    mGUIContainer.handleEvent(event);
//    return false;}
