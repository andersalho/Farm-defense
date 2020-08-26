#include "game_state.hpp"
#include "../node_component.hpp"
#include "../resource_identifiers.hpp"
#include <memory>
#include "../data_tables.hpp"

namespace {
	const std::vector<GUIData> table = InitializeGUIData();
}

GameState::GameState(StateStack& stack, Context context) :
    State(stack, context),
    gameField_(*context.window_, context.viewOffset_),
    player_(*context.player_),
    GUIContainer_(),
    GUIController_(*context.GUIController_)
    { 
        player_.SetGameStatus(Player::GameRunning);
        
        auto pauseButton = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_, table[GUIitems::ID::PauseButton].normalTexture, table[GUIitems::ID::PauseButton].selectedTexture);
        pauseButton->setPosition(10, 10);
        pauseButton->SetCallback([this] ()
	{
		RequestStackPush(States::ID::Pause);
	});
        GUIContainer_.Pack(pauseButton);

        //GetContext().textures_->Load(Textures::ID::FireTower, "../media/textures/tower.png");

    }

void GameState::Draw() {
    gameField_.Draw(); // calls the gamefield to draw everything
    sf::RenderWindow& window = *GetContext().window_;
    window.draw(GUIContainer_);
}

bool GameState::Update(sf::Time dt) {
    gameField_.Update(dt); // updates the gamefield on each tick
    ModifyPlayerScore(gameField_.GetRoundScore());
    
    for (int i = 0; i < gameField_.NewEnemiesReachedEnd(); i++)
    {
        player_.ReduceLife();
    }
    if (player_.GetLives() <= 0) 
    {
        player_.SetGameStatus(Player::GameLost);
        RequestStackPush(States::ID::GameOver);
        return false;
    }
    if (gameField_.IsEndOfGame())
    {
        player_.SetGameStatus(Player::GameWon);
        RequestStackPush(States::ID::GameOver);
        return false;
    }
    if (gameField_.EndOfLevel())
    {
        // when level ends open side bar 
        //RequestStackPush(States::ID::Sidebar);
        //return false;
    }


    CommandQueue& commands = gameField_.GetCommandQueue();
	player_.HandleRealtimeInput(commands);

    

	return true;
}

bool GameState::HandleEvent(const sf::Event& event) {
    CommandQueue& commands = gameField_.GetCommandQueue();
    player_.HandleEvent(event, commands);
    GUIController_.FetchInput(commands);
    if (event.type == sf::Event::MouseButtonReleased)
    {
        std::cout << "Inforequested: " << player_.InfoRequested() << std::endl;
        std::cout << "InfoPOPrequested: " << player_.InfoPopRequested() << std::endl;
        if (player_.InfoRequested() && !(player_.InfoPopRequested()))
            {
                std::cout << "Hello from here rewuested infooooo" << std::endl;
                RequestStackPush(States::ID::GameUpgradeTowerSideBar);
                player_.ResetInfoRequestStatus();
                
            }
        if (player_.InfoPopRequested() && !(player_.InfoRequested()))
            {
                RequestStackPop();
                std::cout << "Stack pop requested" << std::endl;
                player_.ResetInfoPopStatus();
            }
        
    }
    
    

    if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P))
		RequestStackPush(States::ID::Pause);

    /*if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::U))
    {
        std::cout << "Requested upgrade " << std::endl;
        RequestStackPush(States::ID::Sidebar);
		RequestStackPush(States::ID::GameUpgradeTowerSideBar);
    }*/
    if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I))
    {
        std::cout << "Requested info " << std::endl;
        RequestStackPush(States::ID::Sidebar);
    }
        
    GUIContainer_.HandleEvent(event);
    return true;
}


void GameState::ModifyPlayerScore(int score)
{
    player_.SetScore(score);
    //std::cout << "current score: " << player_.GetScore() << std::endl;
}

