#include <M/Inc/M.h>

enum class states : size_t
{
    GameState = 0
};
class GameState : public M::AppState
{
public:
    virtual ~GameState() = default;
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    M::App& mainApp = M::MainApp();

    mainApp.AddState<GameState>((size_t)states::GameState);
    mainApp.Run();

    return 0;
}