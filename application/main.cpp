#include <mnemos.hpp>
#include "game.hpp"

int main(int argc, char** argv)
{
    mnm::Run(std::make_unique<game::Game>());

    return 0;
}
