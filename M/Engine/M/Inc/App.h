#pragma once

namespace M
{
    class AppState;

    class App final
    {
    public:
        template <class StateType>
        void AddState(size_t stateId)
        {
            static_assert(std::is_base_of_v<AppState, StateType>, "AddState must be of type AppState");

            auto [iter, success] = mAppStates.try_emplace(stateId, nullptr);
            if (success)
            {
                auto& ptr = iter->second;
                ptr = std::make_unique<StateType>();
                if(mCurrentState == nullptr)
                {
                    LOG("App -- Current state: %d", iter->first);
                    mCurrentState = ptr.get();
                }
            }
        }

        void ChangeState(size_t stateId);

        void Run();
        void Quit();

    private:
        using AppStateMap = std::map<size_t, std::unique_ptr<AppState>>;

        AppStateMap mAppStates;
        AppState* mCurrentState = nullptr;
        AppState* mNextState = nullptr;
        bool mRunning = false;
    };
}