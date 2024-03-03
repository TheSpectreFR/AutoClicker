#include "autoclickerInclude.h"

int main(int argc, char *argv[])
{
    // asks which mode you want to run first.
    // this program sends right clicks, you can tweak it by changing in the functions the macro
    // please check the WinApi docs what needs to be stored in the structure.
    printf("Welcome to Autoclicker\nThis program sends left mouse clicks\n");
    Sleep(300);
    printf("What mode do you want to use today ?\n1.)Simple\n2.)Auto Click\nchose:");
    int mode;
    menue:
    scanf("%d", &mode);
    system("cls");

    if(mode == 1)
    {
        // send one input when pressing on the key binded
        printf("Bind a key to auto-click:\nEnter a microsoft virtual key value refered here: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes\nchose: ");
        scanf("%X", &CONST_AUTOCLICKER_TOUCHE);
        simpleClick();
    }else if(mode == 2)
    {
        printf("How much CPS do you want to send ?\nchose: ");
        scanf("%d", &CONST_AUTOCLICKER_CPS);
        printf("What key do you want to bind ?\nEnter a microsoft virtual key value refered here: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes\nchose: ");
        scanf("%X", &CONST_AUTOCLICKER_TOUCHE);
        autoClick();
    }else
    {
        printf("\nplease try again\n");
        goto menue;
    }
    return 0;
}