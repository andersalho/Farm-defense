#include "state.hpp"
#include "../state_stack.hpp"
#include <SFML/Graphics/RenderWindow.hpp>


State::Context::Context(sf::RenderWindow& window, TextureHolder& textures,
                        FontHolder& fonts, Player& player, sf::Vector2f viewOffset,
                        GUI::Container& GUIContainer, GUI::Controller& GUIController) 
        : window_(&window),
        textures_(&textures),
        fonts_(&fonts),
        player_(&player),
        viewOffset_(viewOffset),
        GUIContainer_(&GUIContainer),
        GUIController_(&GUIController) 
        { 
        }

State::State(StateStack &stateStack, Context context)
        : context_(context), stateStack_(&stateStack) { }

void State::RequestStackPop() {
        stateStack_->PopState();
}

void State::RequestStackPush(States::ID stateID) {
        stateStack_->PushState(stateID);
}

void State::RequestStateClear() {
        stateStack_->ClearStates();
}

State::Context State::GetContext() const {    
        return context_;
}



