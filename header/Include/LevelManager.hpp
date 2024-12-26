#ifndef LEVEL_MANAGER_HPP
#define LEVEL_MANAGER_HPP

#include <vector>
#include <iostream>
#include <string.h>
#include <Map.h>
#include <Character.h>
#include <Boss.h>

class LevelManager {
public:

    enum Level {
        Level1,
        Level2,
        Level3,
        Level4,
        Level5,
        None,
    };

    enum Character_1 {
        wukong,
        pig
    };

    static LevelManager& getInstance();
    void setLevels(int pos, int val);
    void setSaveLevel(int saveLevel) {this->saveLevel = saveLevel;}
    int getSaveLevel() const {return saveLevel;}
    const int getLevels(int pos) const;
    void resetLevels();
    void setCurLevel(Level level);
    int getSaveScore() const {return score;}
    int getSaveTime() const {return time;}

    Level getCurLevel() const;
    void setCurCharacter(Character_1 character);
    Character_1 getCurCharacter() const;
    void setScore(int score){this->score = score;}
    int getScore() const {return score;}
    void setTime(int time) {this->time = time;}
    int getTime() const {return time;}
    void setSaveMap(std::vector<std::string> saveMap) {this->saveMap = saveMap;}
    std::vector<std::string> getSaveMap() const {return saveMap;}
    void setSaveMonsterPos(std::vector<std::pair<float, float>> saveMonsterPos) {this->saveMonsterPos = saveMonsterPos;}
    std::vector<std::pair<float, float>> getSaveMonsterPos() const {return saveMonsterPos;}
    void setSaveMonsterType(std::vector<char> saveMonsterType) {this->saveMonsterType = saveMonsterType;}
    std::vector<char> getSaveMonsterType() const {return saveMonsterType;}
    void setSavePlayerProjectilePos(std::vector<std::pair<float, float>> savePlayerProjectilePos) {this->savePlayerProjectilePos = savePlayerProjectilePos;}
    std::vector<std::pair<float, float>> getSavePlayerProjectilePos() const {return savePlayerProjectilePos;}
    void setSaveMonsterProjectilePos(std::vector<std::pair<float, float>> saveMonsterProjectilePos) {this->saveMonsterProjectilePos = saveMonsterProjectilePos;}
    std::vector<std::pair<float, float>> getSaveMonsterProjectilePos() const {return saveMonsterProjectilePos;}
    void setSavePlayerProjectileDir(std::vector<bool> savePlayerProjectileDir) {this->savePlayerProjectileDir = savePlayerProjectileDir;}
    std::vector<bool> getSavePlayerProjectileDir() const {return savePlayerProjectileDir;}
    void setSaveMonsterProjectileDir(std::vector<bool> saveMonsterProjectileDir) {this->saveMonsterProjectileDir = saveMonsterProjectileDir;}
    std::vector<bool> getSaveMonsterProjectileDir() const {return saveMonsterProjectileDir;}
    void setSavePlayerProjectileVel(std::vector<std::pair<float, float>> savePlayerProjectileVel) {this->savePlayerProjectileVel = savePlayerProjectileVel;}
    std::vector<std::pair<float, float>> getSavePlayerProjectileVel() const {return savePlayerProjectileVel;}
    void setSaveMonsterProjectileVel(std::vector<std::pair<float, float>> saveMonsterProjectileVel) {this->saveMonsterProjectileVel = saveMonsterProjectileVel;}
    std::vector<std::pair<float, float>> getSaveMonsterProjectileVel() const {return saveMonsterProjectileVel;}
    void setSaveItemPos(std::vector<std::pair<float, float>> saveItemPos) {this->saveItemPos = saveItemPos;}
    std::vector<std::pair<float, float>> getSaveItemPos() const {return saveItemPos;}
    void setSaveItemType(std::vector<int> saveItemType) {this->saveItemType = saveItemType;}
    std::vector<int> getSaveItemType() const {return saveItemType;}
    void setSavePlayerPosX(float savePlayerPosX) {this->savePlayerPosX = savePlayerPosX;}
    float getSavePlayerPosX() const {return savePlayerPosX;}
    void setSavePlayerPosY(float savePlayerPosY) {this->savePlayerPosY = savePlayerPosY;}
    float getSavePlayerPosY() const {return savePlayerPosY;}
    void setPlayerHP(int playerHP) {this->playerHP = playerHP;}
    int getPlayerHP() const {return playerHP;}
    void setPlayerStatus(int playerStatus) {this->playerStatus = playerStatus;}
    int getPlayerStatus() const {return playerStatus;}
    void setPlayerVelX(float playerVelX) {this->playerVelX = playerVelX;}
    float getPlayerVelX() const {return playerVelX;}
    void setPlayerVelY(float playerVelY) {this->playerVelY = playerVelY;}
    float getPlayerVelY() const {return playerVelY;}
    void setSaveBossPosX(float saveBossPosX) {this->saveBossPosX = saveBossPosX;}
    float getSaveBossPosX() const {return saveBossPosX;}
    void setSaveBossPosY(float saveBossPosY) {this->saveBossPosY = saveBossPosY;}
    float getSaveBossPosY() const {return saveBossPosY;}
    void setBossHP(int bossHP) {this->bossHP = bossHP;}
    int getBossHP() const {return bossHP;}
    void setBossVelX(float bossVelX) {this->bossVelX = bossVelX;}
    float getBossVelX() const {return bossVelX;}
    void setBossVelY(float bossVelY) {this->bossVelY = bossVelY;}
    float getBossVelY() const {return bossVelY;}
    void addItems(Item* i){
        if (Item* ni = dynamic_cast<Coin*>(i)){
			saveItemType.push_back(1);
            saveItemPos.push_back(std::make_pair(ni->getPosition().x, ni->getPosition().y));
		}
		else if (Item* ni = dynamic_cast<PowerUp*>(i)){
			saveItemType.push_back(2);
            saveItemPos.push_back(std::make_pair(ni->getPosition().x, ni->getPosition().y));
		}
    }

    void addMonster(Monster* m){
		saveMonsterPos.push_back(std::make_pair(m->getPosition().x, m->getPosition().y));
		if (Monster* nm = dynamic_cast<Goomba*>(m))
            saveMonsterType.push_back('M');
		else if (Monster* nm = dynamic_cast<Bee*>(m))
			saveMonsterType.push_back('B');
		else if (Monster* nm = dynamic_cast<bee*>(m))
			saveMonsterType.push_back('b');
		
	}

    void addPlayerProjectile(Projectile* p){
        savePlayerProjectilePos.push_back(std::make_pair(p->getPosition().x, p->getPosition().y));
        savePlayerProjectileDir.push_back(p->getDirection());
        savePlayerProjectileVel.push_back(std::make_pair(p->getVelocity().x, p->getVelocity().y));
     }
    void addMonsterProjectile(Projectile* p){
		saveMonsterProjectilePos.push_back(std::make_pair(p->getPosition().x, p->getPosition().y));
		saveMonsterProjectileDir.push_back(p->getDirection());
		saveMonsterProjectileVel.push_back(std::make_pair(p->getVelocity().x, p->getVelocity().y));
	}

    void saveFromMap(Map* map, float t){
		saveMap = map->getMapData();
		score = map->score;
        time = t;
	}

    void saveFromCharacter(Character* character){
        savePlayerPosX = character->getPosition().x;
        savePlayerPosY = character->getPosition().y;
        playerHP = character->getHP();
        playerStatus = character->getStatus();
        playerVelX = character->getVelocity().x;
        playerVelY = character->getVelocity().y;
    }
    
    void saveFromBoss(Boss* boss){
		saveBossPosX = boss->getPosition().x;
		saveBossPosY = boss->getPosition().y;
		bossHP = boss->getHP();
		bossVelX = boss->getVelocity().x;
		bossVelY = boss->getVelocity().y;
	}

    void setSaveCharacter(int saveCharacter) {this->saveCharacter = saveCharacter;}
    int getSaveCharacter() const {return saveCharacter;}
private:
    LevelManager();
    ~LevelManager() = default;

    LevelManager(const LevelManager&) = delete;
    LevelManager& operator=(const LevelManager&) = delete;

    std::vector<int> mLevels;
    Level curLevel;
    int saveLevel;
    Character_1 curCharacter;
    static LevelManager* sInstance;
    int saveCharacter;
    
    int score = 0;
    int time = 0;
    std::vector<std::string> saveMap;
    std::vector<std::pair< float, float>> saveMonsterPos;
    std::vector<char> saveMonsterType;

    //projectile
    std::vector<std::pair<float, float>> savePlayerProjectilePos;
    std::vector<std::pair<float, float>> saveMonsterProjectilePos;
    std::vector<bool> savePlayerProjectileDir;
    std::vector<bool> saveMonsterProjectileDir;
    std::vector<std::pair<float, float>> savePlayerProjectileVel;
    std::vector<std::pair<float, float>> saveMonsterProjectileVel;

    //item
    std::vector<std::pair<float, float>> saveItemPos;
    std::vector<int> saveItemType;
    //coin = 1
    //powerup = 2

    float savePlayerPosX;
    float savePlayerPosY;
    int playerHP;
    int playerStatus;
    float playerVelX;
    float playerVelY;

    //boss
    float saveBossPosX;
    float saveBossPosY;
    int bossHP;
    float bossVelX;
    float bossVelY;


    
};


#endif // LEVEL_MANAGER_HPP