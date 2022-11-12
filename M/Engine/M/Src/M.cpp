#include "Precompiled.h"
#include "M.h"

M::App& M::MainApp()
{
    static App sApp;
    return sApp;
}