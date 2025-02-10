
#pragma once

#include "Application.h"

// Entry point
int main() 
{
    Application app;
    if (!app.Initialize())
    {
        return -1;
    }

    app.Run();
    app.Shutdown();
    return 0;
}
