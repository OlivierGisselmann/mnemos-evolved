#include "game.hpp"

#include <iostream>

using namespace mnm;

namespace game
{
    void Game::OnInit()
    {
        debug::Log("Game Init()");
    }

    void Game::OnUpdate(float delta)
    {
        if(input::IsKeyPressed(input::Key::Escape))
        {
            Stop();
        }
    }

    void Game::OnFixedUpdate()
    {
        
    }

    void Game::OnShutdown()
    {
        debug::Log("Game Shutdown()");
    }
}
