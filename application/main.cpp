#include <mnemos.hpp>
#include "game.hpp"

int main(int argc, char** argv)
{
    game::Game gameApp;

    mnm::Run(&gameApp);

    return 0;
}
