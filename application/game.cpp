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
        if(mnm::input::IsKeyPressed(mnm::input::Key::Escape))
            mnm::debug::Log("Escape pressed!");

        if(mnm::input::IsKeyReleased(mnm::input::Key::F1))
            mnm::debug::Log("F1 pressed!");

        if(mnm::input::IsKeyPressed(mnm::input::Key::Numpad3))
            mnm::debug::Log("3 pressed!");

        if(mnm::input::IsKeyDown(mnm::input::Key::Return))
            mnm::debug::Log("Return pressed!");
        //mnm::debug::Log("Game OnFixedUpdate()");
    }

    void Game::OnShutdown()
    {
        mnm::debug::Log("Game Shutdown()");
    }
}
