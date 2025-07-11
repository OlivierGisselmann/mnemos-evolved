#ifndef GAME_HPP
#define GAME_HPP

#include <mnemos.hpp>

#include <memory>

namespace game
{
    class Game : public mnm::MnemosApplication
    {
    public:
        void OnInit() override;
        void OnUpdate() override;
        void OnFixedUpdate() override;
        void OnShutdown() override;
    };
}

#endif
