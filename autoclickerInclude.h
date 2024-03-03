/*
    This program was made for people who just want a simple and working autoclicker
    and also for devs who need to simulate inputs.

    REMINDER:
    This is a 1.0 version,
    for now if you want to chose which inputs you want to "simulate",
    please check the WinApi docs to find the macros that needs to be used in the structures.
*/
#ifndef _STDIO_H
#include <stdio.h>
#endif
#ifndef _WINDOWS_
#include <windows.h>
#endif

int CONST_AUTOCLICKER_AUTOMODE = 0;
int CONST_AUTOCLICKER_TOUCHE = 0;
int CONST_AUTOCLICKER_CPS;
unsigned int CONST_AUTOCLICKER_RUN = 1;

DWORD WINAPI isActive(void *parameters)
{
    printf("Press the key %X if you want to turn on/off the autoclicker\nAlso press CTRL+ALT+UP/DOWN-ARROW to tweak the speed...\n", CONST_AUTOCLICKER_TOUCHE);
    CONST_AUTOCLICKER_AUTOMODE = 0;
    while(CONST_AUTOCLICKER_RUN = 1)
    {
        if(GetAsyncKeyState(CONST_AUTOCLICKER_TOUCHE)&0x0001) // checks if binded key is pressed
        {
            // checks if the auto clicker is already enabled
            if(CONST_AUTOCLICKER_AUTOMODE != 0)
            {
                printf("Autoclicker turned off\n");
                CONST_AUTOCLICKER_AUTOMODE = 0;
            }else
            {
                printf("Autoclicker turned on\n");
                CONST_AUTOCLICKER_AUTOMODE = 1;
            }
        }else if(GetKeyState(0x11)&0x1000) // if CTRL key pressed
        {
            if(GetKeyState(0x12)&0x1000) // if ALT key pressed
            {
                if(GetAsyncKeyState(0x26)&0x0001) // if UP-ARROW key pressed
                {
                    CONST_AUTOCLICKER_CPS += 5;
                    printf("Increased CONST_AUTOCLICKER_CPS to %d\n", CONST_AUTOCLICKER_CPS);
                }else if(GetAsyncKeyState(0x28)&0x0001) // if DOWN-ARROW key pressed
                {
                    if(CONST_AUTOCLICKER_CPS <= 5)
                    {
                        CONST_AUTOCLICKER_CPS = 1;
                    }else
                    {
                        CONST_AUTOCLICKER_CPS -= 5;
                    }
                    printf("Decreased CONST_AUTOCLICKER_CPS to %d\n", CONST_AUTOCLICKER_CPS);
                }
            }
        }
    }
}
int simpleClick(void)
{
    system("cls");
    printf("the key is: %X", CONST_AUTOCLICKER_TOUCHE);
    printf("Press the key\n");
    unsigned int CONST_AUTOCLICKER_RUN = 1;
    while(CONST_AUTOCLICKER_RUN == 1)
    {
        if(GetAsyncKeyState(CONST_AUTOCLICKER_TOUCHE)&0x0001) // test si la touche assignee est pressee
        {
            // simulate the click
            // defines when pressing down the key
            INPUT click[2] = {0};
            click[0].type = INPUT_MOUSE;
            click[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

            // defines when you release it
            click[1].type = INPUT_MOUSE;
            click[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

            // sends the "virtual" click
            UINT ret = SendInput(2, click, sizeof(INPUT));

            if(ret != 2)
            {
                CONST_AUTOCLICKER_RUN = 0;
                printf("%d\n", ret);
                printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
            }
        }
    }
    return 0;
}
int autoClick(void)
{
    // tests if the autoclicker is already active... -> creating the thread defined to set the flag
    DWORD ThreadID;
    HANDLE Thread = CreateThread(0, 0, isActive, NULL, 0, &ThreadID);

    // body of the autoClick function.
    while(CONST_AUTOCLICKER_RUN == 1)
    {
        Sleep(10);
        while(CONST_AUTOCLICKER_AUTOMODE == 1)
        {
            // simulates the click
            // defines the pressing action
            INPUT click[2] = {0};
            click[0].type = INPUT_MOUSE;
            click[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

            // defines the release of the key
            click[1].type = INPUT_MOUSE;
            click[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

            // sends the click.
            UINT ret = SendInput(2, click, sizeof(INPUT));
            if(ret != 2)
            {
                CONST_AUTOCLICKER_RUN = 0;
                printf("%d\n", ret);
                printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
            }
            Sleep(1000/CONST_AUTOCLICKER_CPS);
        }
    }
    return 0;
}