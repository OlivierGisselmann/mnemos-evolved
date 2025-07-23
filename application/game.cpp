#include "game.hpp"

namespace game
{
    void Game::OnInit()
    {
        mnm::debug::Log("Game Init()");
    }

    void Game::OnUpdate()
    {
        // mnm::debug::Log("Game OnUpdate()");
    }

    void Game::OnFixedUpdate()
    {
        
    }

    void Game::OnShutdown()
    {
        mnm::debug::Log("Game Shutdown()");
    }
}
