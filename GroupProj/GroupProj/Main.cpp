// Include important C++ libraries here
#include <SFML/Graphics.hpp>

// Make code easier to type with "using namespace"
using namespace sf;

int main()
{
	enum class State { PAUSED, GAME_OVER, PLAYING };

	State state = State::GAME_OVER;

	//gets resolution
	Vector2f resolution;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y), "Chicken Hunt (Working Title)", Style::Fullscreen);

	//creates a view
	//View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	View mainView = View(window.getDefaultView());

	FloatRect fBounds(0.f, 0.f, (resolution.x * 2), (resolution.y));

	//clock for timing things
	Clock clock;

	//total game time - could be used for high score
	Time totalGameTime;

	//both mouse position vectors required
	Vector2f mouseWorldPosition;
	Vector2i mouseScreenPosition;

	//background texture
	Texture backgroundTexture;

	backgroundTexture.loadFromFile("graphics/back.jpg");

	backgroundTexture.setRepeated(true);

	IntRect iBounds(fBounds);

	//sprite for background

	sf::Sprite backgroundSprite(backgroundTexture, iBounds);

	const sf::Vector2f viewStart(fBounds.left + (fBounds.width / 2), fBounds.top + (fBounds.height / 2));
	const sf::Vector2f spriteStart(fBounds.left, fBounds.top);

	while (window.isOpen())
	{


		Event event;
		while (window.pollEvent(event))
		{

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Return && state == State::PLAYING)
				{
					state = State::PAUSED;
				}
				else if (event.key.code == Keyboard::Return && state == State::PAUSED)
				{
					state = State::PLAYING;
					// Reset the clock so there isn't a frame jump
					clock.restart();
				}
				// Start a new game while in GAME_OVER state
				else if (event.key.code == Keyboard::Return && state == State::GAME_OVER)
				{
					state = State::PLAYING;
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (state == State::PLAYING)
		{
			//all used for scrolling background
			//moves the x value of the view by 0.2f (value may be changed to suit the game)
			mainView.move(0.2f, 0.0f);
			//sets the offset of the view
			const sf::Vector2f viewOffset(viewStart - mainView.getCenter());
			//creates the sprite offset
			sf::Vector2f spriteOffset;
			//sets the x and y offsets so both can be moved
			spriteOffset.x = floor(viewOffset.x / backgroundTexture.getSize().x) * backgroundTexture.getSize().x;
			spriteOffset.y = floor(viewOffset.y / backgroundTexture.getSize().y) * backgroundTexture.getSize().y;
			//sets the background position
			backgroundSprite.setPosition(spriteStart - spriteOffset);


			//basic function to clear and draw scene
			window.clear();
			window.setView(mainView);
			window.draw(backgroundSprite);
			window.display();
			 
		}
	}
}

