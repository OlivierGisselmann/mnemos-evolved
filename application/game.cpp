#include "game.hpp"

#include <iostream>

namespace game
{
    void Game::OnInit()
    {
        mnm::debug::Log("Game Init()");
    }

    void Game::OnUpdate()
    {
        if(mnm::input::IsKeyPressed(mnm::input::Key::Escape))
        {
            mnm::Stop();
        }
    }

    void Game::OnFixedUpdate()
    {
        
    }

    void Game::OnShutdown()
    {
        mnm::debug::Log("Game Shutdown()");
    }
}
