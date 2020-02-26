#include "ENGINE/Engine.h"
#include "SANDBOX/include/My_game.h"

#include <cstdio>

int main(int argc, char *args[]) {
    Engine::Application app("sq test", 800, 600, 0, "res/icon.png");
    app.Init();

    Mine_game::My_game *sq = new Mine_game::My_game(&app);

    app.Change_state(sq);

    app.Run();

    app.Close();

    return 0;
}
