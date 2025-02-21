#include <iostream>
#include <string>
#include "user_management.h"

using namespace std;

int main()
{
    cout << "WELCOME TO APOLLO MUSIC ENGINE" << endl
         << endl;

    int ch;
    do
    {
        cout << "Menu\n1.Sign In\n2.Sign Up\n3.Create Playlist\n4.Exit" << endl;
        cout << "Enter your choice: ";
        cin >> ch;

        try
        {
            if (ch < 1 || ch > 3)
            {
                throw invalid_argument("Invalid choice. Please enter a valid option.");
            }

            string uname, pwd, fname, lname;
            char gen;
            int age;
            bool flag, verify;
            Apollo_User ap_user;
            Std_User user;
            Prem_User users;

            switch (ch)
            {
            case 1:
                cout << "Enter your username: ";
                cin >> uname;
                cout << "Enter your password: ";
                cin >> pwd;

                if (Apollo_User::prem_user_exists(uname))
                {
                    flag = Apollo_User::authenticate_prem_user(uname, pwd);
                    if (flag)
                    {
                        system("python apollo_Prem_player.py");
                    }
                }
                else if (Apollo_User::user_exists(uname))
                {
                    flag = Apollo_User::authenticate_user(uname, pwd);
                    if (flag)
                    {
                        user.playmusic("Katthu-Adikkuthu-Katthu.mp3");
                    }
                }
                else
                {
                    cout << "User doesn't exist. Please Sign Up." << endl;
                }
                break;

            case 2:
                cout << "Enter your Username: ";
                cin >> uname;
                cout << "Enter your first name: ";
                cin >> fname;
                cout << "Enter your last name: ";
                cin >> lname;
                cout << "Enter your gender (M/F): ";
                cin >> gen;
                cout << "Enter your age: ";
                cin >> age;
                cout << "Enter the password (must contain char, spl char, digits): ";
                cin >> pwd;

                verify = Apollo_User::verify_prem_user();
                if (verify == 1)
                {
                    users.sign_up_prem(uname, fname, lname, pwd, gen, age);
                    flag = Apollo_User::authenticate_prem_user(uname, pwd);
                    if (flag)
                    {
                        system("python apollo_Prem_player.py");
                    }
                    users.sign_in(uname, pwd);
                }
                else
                {
                    user.sign_up_user(uname, fname, lname, pwd, gen, age);
                    flag = Apollo_User::authenticate_user(uname, pwd);
                    if (flag)
                    {
                        user.playmusic("Katthu-Adikkuthu-Katthu.mp3");
                    }
                    user.sign_in(uname, pwd);
                }
                break;

            default:
                break;
            }
        }
        catch (const exception &e)
        {
            cerr << "Error: " << e.what() << endl;
        }

        if (ch == 3)
        {
            system("g++ playlist.cpp -o create");
            system("create.exe");
        }
    } while (ch != 4);

    return 0;
}

