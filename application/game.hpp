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
        void OnUpdate(float delta) override;
        void OnFixedUpdate() override;
        void OnShutdown() override;
    };
}

#endif
