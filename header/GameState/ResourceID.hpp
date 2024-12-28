#ifndef RESOURCE_ID_HPP
#define RESOURCE_ID_HPP

#include <ResourceHolder.hpp>

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

namespace Textures
{
    enum ID
    {
	
		//WukongAsset1
		WukongStand1,
		WukongStand2,
		WukongStand3,
		WukongStand4,
		WukongJump1,
		WukongJump2,
		WukongJump3,
		WukongJump4,
		WukongRun1,
		WukongRun2,
		WukongRun3,
		WukongRun4,
		WukongAttack1,
		WukongAttack2,

		WukongHurt1,
		WukongHurt2,
		WukongHurt3,


		SmallWukongStand1,
		SmallWukongStand2,
		SmallWukongStand3,
		SmallWukongStand4,

		SmallWukongRun1,
		SmallWukongRun2,
		SmallWukongRun3,
		SmallWukongRun4,

		SmallWukongHurt1,
		SmallWukongHurt2,
		SmallWukongHurt3,

		DeadWukong1,
		DeadWukong2,
		DeadWukong3,
		DeadWukong4,
		DeadWukong5,
		DeadWukong6,
		DeadWukong7,
		DeadWukong8,
		DeadWukong9,

		SecondWukongStand1,
		SecondWukongStand2,
		SecondWukongStand3,
		SecondWukongStand4,
		SecondWukongStand5,

		SecondWukongRun1,
		SecondWukongRun2,
		SecondWukongRun3,
		SecondWukongRun4,
		SecondWukongRun5,
		SecondWukongRun6,
		SecondWukongRun7,
		SecondWukongRun8,

		SecondWukongHurt1,
		SecondWukongHurt2,
		SecondWukongHurt3,

		SecondWukongAttack1,
		SecondWukongAttack2,
		SecondWukongAttack3,
		SecondWukongAttack4,
		SecondWukongAttack5,
		

		SecondWukongDead1,
		SecondWukongDead2,
		SecondWukongDead3,
		SecondWukongDead4,
		SecondWukongDead5,
		SecondWukongDead6,
		SecondWukongDead7,
		
		BossFly1,
		BossFly2,
		BossFly3,
		BossFly4,

		BossAttack1,
		BossAttack2,
		BossAttack3,

		BossDead1,
		BossDead2,
		BossDead3,
		BossDead4,
		BossDead5,
		BossDead6,
		BossDead7,

		BossExhausted1,
		BossExhausted2,

		BossShoot1,
		BossShoot2,

		BossBullet,

		Bullet,
		Enemies,
		Bg1,
		Blocks,
        Bg2,
        Blocks2,
		Bg3,
        Blocks3,

		//Menu
			button,
			MainMenuBG,
			MainMenuBG_1,
			MainMenuBG_2,
			MainMenuBG_3,
			MainMenuClound_1,
			MainMenuClound_2,
			MainMenuClound_3,
			MainMenuClound_4,
			MainMenuClound_5,
			MainMenuClound_6,
			MainMenuClound_7,
			MainMenuClound_8,
			MainMenuClound_9,
			MainMenuPig,
			MainMenuWukong,
			MainMenuPointer,

			//Guide
			GuideBG,
			CloseGuide,

			//Level
			LevelBG,
			LevelBackButton,
			LevelLock,
			LevelMap_1,
			LevelMap_2,
			LevelMap_3,
			LevelMap_4,
			LevelMap_5,
			LevelPointer1,
			LevelPointer2,
			LevelPointer3,
			LevelPointer4,
			LevelPointer5,

			//Pause
			PauseBG,
			PauseContinueButton,
			PauseRestartButton,
			PauseMenuButton,
			PauseSaveButton,
			PauseSoundButton,
			PauseMusicButton,

			//Game
			PauseButton,

			// LevelComplete
			LevelCompleteBG,
			LevelCompleteNextButton,
			LevelCompleteBackButton,

			//Winning
			WinningBG,
			WinningBoard,
			WinningRestartButton,

			//GameOver
			GameOverBoard,
			GameOverRestartButton,
			GameOverMenuButton,

			//Setiting
			SettingBoard,
			SettingMusicButton,
			SettingSoundButton,
			SettingCloseButton,





    };
}

namespace Fonts
{
	enum ID
	{
		Main,
		NameGame,
		PixelNes,
	};
}

namespace SoundEffect
{
	enum ID
	{

	};
}

namespace Music
{
	enum ID
	{
		MenuTheme,
		GameTheme,
		WinningTheme,
		LevelCompleteTheme,
		GameOverTheme,
		BossFightTheme,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>			TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>					FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;




#endif // RESOURCE_ID_HPP