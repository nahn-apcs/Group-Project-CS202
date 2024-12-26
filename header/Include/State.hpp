#ifndef STATE_HPP
#define STATE_HPP

#include <StateID.hpp>
#include <ResourceID.hpp>
#include <MusicPlayer.hpp>
#include <SoundPlayer.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace sf {
	class RenderWindow;
}

class StateStack;

class State {

public:
	typedef std::unique_ptr<State> Ptr;

	struct Context {
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, MusicPlayer& music, SoundPlayer& sounds);

		sf::RenderWindow* window;
		TextureHolder* textures;
		FontHolder* fonts;
		MusicPlayer* music;
		SoundPlayer* sounds;
		int currentScore = 0;
		int currentTime = 0;
	};

public:
	State(StateStack& stack, Context context);
	virtual                         ~State();
	virtual void		            draw() = 0;
	virtual bool		            update(sf::Time dt) = 0;
	virtual bool		            handleEvent(const sf::Event& event) = 0;

	virtual void		            onActivate();
	virtual void		            onDestroy();

protected:
	void			                requestStackPush(States::ID stateID);
	void				            requestStackPop();
	void				            requestStateClear();

	Context				            getContext() const;


private:
	StateStack* mStack;
	Context				        mContext;



};

#endif // STATE_HPP