#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include "user_management.h"

using namespace std;

string Apollo_User::generateUserId()
{
    // Gets the current time in milliseconds
    auto now = chrono::system_clock::now();
    auto now_ms = chrono::time_point_cast<chrono::milliseconds>(now);
    auto value = now_ms.time_since_epoch().count();

    // Generates a random string to append to the timestamp
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 25);
    string randomStr;
    for (int i = 0; i < 6; i++)
    {
        randomStr += ('a' + dis(gen));
    }

    // Concatenates the timestamp and the random string to form the user ID
    return to_string(value) + randomStr;
}

bool Apollo_User::password_validator(string passkey)
{

    bool hasChar = false;
    bool hasInt = false;
    bool hasPunct = false;

    for (char c : passkey)
    {
        if (std::isalpha(c))
        {
            hasChar = true;
        }
        else if (std::isdigit(c))
        {
            hasInt = true;
        }
        else if (std::ispunct(c))
        {
            hasPunct = true;
        }
    }

    return hasChar && hasInt && hasPunct;
}

bool Apollo_User::user_exists(string username)
{
    ifstream file("__users.csv");
    string line;
    while (getline(file, line))
    {
        size_t pos = line.find(",");
        if (pos != string::npos)
        {
            string current_username = line.substr(0, pos);
            if (current_username == username)
            {
                return true;
                break;
            }
        }
    }
    return false;
}

bool Apollo_User::prem_user_exists(string username)
{
    ifstream file("__prem_users.csv");
    string line;
    while (getline(file, line))
    {
        size_t pos = line.find(",");
        if (pos != string::npos)
        {
            string current_username = line.substr(0, pos);
            if (current_username == username)
            {
                return true;
                break;
            }
        }
    }
    return false;
}

bool Apollo_User::verify_prem_user()
{
    cout << "Are you a Premium User.";
    char ch;
    cout << "Have you planted a tree for this(Y or N)? ";
    cin >> ch;
    if (ch == 'Y')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Apollo_User::authenticate_user(string username, string password)
{
    ifstream file1("__users.csv");
    string line1;

    while (getline(file1, line1))
    {
        string uname1, pass1 ;
        int delimiter_pos1 = line1.find(",");
        uname1 = line1.substr(0, delimiter_pos1);
        pass1 = line1.substr(delimiter_pos1 + 1);

        if (username == uname1)
        {
            if (password == pass1)
            {
                return true;
            }
            else
            {
                int tries = 3;
                while (tries--)
                {
                    cout << "Password is incorrect. Please try again: ";
                    cin >> password;
                    if (password == pass1)
                    {
                        return true;
                    }
                }
                cout << "Incorrect password entered 3 times. Exiting program.\n";
                exit(0);
            }
        }
    }

        
    file1.close();

    return false;
}

int Apollo_User::authenticate_prem_user(string username, string password)
{
    ifstream file2("__prem_users.csv");
    string line2;

    while (getline(file2,line2))
    {
        string uname2, pass2;
        int delimiter_pos2 = line2.find(",");
        uname2 = line2.substr(0, delimiter_pos2);
        pass2 = line2.substr(delimiter_pos2 + 1);

        if (username == uname2)
        {
            if (password == pass2)
            {
                return true;
            }
            else
            {
                int tries = 3;
                while (tries--)
                {
                    cout << "Password is incorrect. Please try again: ";
                    cin >> password;
                    if (password == pass2)
                    {
                        return true;
                    }
                }
                cout << "Incorrect password entered 3 times. Exiting program.\n";
                exit(0);
            }
        }
    }

    file2.close();

    return false;
}

Apollo_User::Apollo_User() {}

Apollo_User::Apollo_User(string p_uname, string p_fname, string p_lname, string p_password, char p_gender, int p_age)
{
    bool opt2;
    cout << setfill('-') << setw(20) << "SIGN UP" << setw(20) << endl;
    do
    {
        int opt;

        cout << "Enter 1 to Sign Up & 0 to Escape";
        cin >> opt;

        if (opt)
        {
            opt2 = sign_up(p_uname, p_fname, p_lname, p_password, p_gender, p_age);
            if (opt2) break;
            else
            {
                cout << "Invalid Credentials. Press 1 to enter again or 0 to quit." << endl;
                cin >> opt2;
            }
        }
        else
        {
            exit(0);
        }
    }
    while (opt2);

    cout << setfill('-') << setw(20) << "SIGN UP SUCCESSFUL" << setw(20) << endl;
}

void Apollo_User::set_username(string u_name)
{
    username = u_name;
    return;
}

void Apollo_User::set_password(string pwd)
{
    password = pwd;
    return;
}

void Apollo_User::set_name(string f_name, string l_name)
{
    first_name = f_name, last_name = l_name;
    return; 
}

void Apollo_User::set_gender(char gen)
{
    gender = gen;
    return;
}

void Apollo_User::set_age(int Age)
{
    age = Age;
    return;
}

string Apollo_User::get_username()
{
    return username;
}

string Apollo_User::get_password()
{
    return password;
}

bool Apollo_User::sign_up(string u_name, string f_name, string l_name, string passkey, char gender_char, int age_num)
{

    if (u_name.length() < 3) 
    {
        throw invalid("Length of the username must be greater than 3 characters.");
        return false;
    }
    else if(user_exists(u_name))
    {
        throw invalid("Username already exists.");
        return false;
    }
    else if (f_name.length() < 3)
    {
        throw invalid("Length of the First name must be greater than 3 characters.");
        return false;
    }
    else if (!password_validator(passkey))
    {
        throw invalid("The password must contain characters, numbers and special characters.");
        return false;
    }
    else if (gender_char != 'M' && gender_char != 'F' && gender_char != 'N' && gender_char != 'O')
    {
        throw invalid("The gender character must be valid.");
        return false;
    }
    else if (age_num < 14)
    {
        throw invalid("You must be above 14 years to use Apollo.");
        return false;
    }
    else
    {
        set_username(u_name);
        set_password(passkey);
        set_name(f_name, l_name);
        set_age(age_num);
        set_gender(gender_char);
        ofstream file;
        file.open("__users.csv", ios::app);
        if (file.is_open())
        {
            file << username << "," << password << endl;
            file.close();
            cout << "New user added successfully!" << endl;
        }
        else
        {
            cout << "Error opening file!" << endl;
        }

        return true;
    }
}

bool Apollo_User::sign_up_user(string u_name, string f_name, string l_name, string passkey, char gender_char, int age_num)
{

    if (u_name.length() < 3) 
    {
        throw invalid("Length of the username must be greater than 3 characters.");
        return false;
    }
    else if(user_exists(u_name))
    {
        throw invalid("Username already exists.");
        return false;
    }
    else if (f_name.length() < 3)
    {
        throw invalid("Length of the First name must be greater than 3 characters.");
        return false;
    }
    else if (!password_validator(passkey))
    {
        throw invalid("The password must contain characters, numbers and special characters.");
        return false;
    }
    else if (gender_char != 'M' && gender_char != 'F' && gender_char != 'N' && gender_char != 'O')
    {
        throw invalid("The gender character must be valid.");
        return false;
    }
    else if (age_num < 14)
    {
        throw invalid("You must be above 14 years to use Apollo.");
        return false;
    }
    else
    {
        set_username(u_name);
        set_password(passkey);
        set_name(f_name, l_name);
        set_age(age_num);
        set_gender(gender_char);
        ofstream file;
        file.open("__users.csv", ios::app);
        if (file.is_open())
        {
            file << username << "," << password << endl;
            file.close();
            cout << "New user added successfully!" << endl;
        }
        else
        {
            cout << "Error opening file!" << endl;
        }

        return true;
    }
}

bool Apollo_User::sign_up_prem(string u_name, string f_name, string l_name, string passkey, char gender_char, int age_num)
{

    if (u_name.length() < 3) 
    {
        throw invalid("Length of the username must be greater than 3 characters.");
        return false;
    }
    else if(user_exists(u_name))
    {
        throw invalid("Username already exists.");
        return false;
    }
    else if (f_name.length() < 3)
    {
        throw invalid("Length of the First name must be greater than 3 characters.");
        return false;
    }
    else if (!password_validator(passkey))
    {
        throw invalid("The password must contain characters, numbers and special characters.");
        return false;
    }
    else if (gender_char != 'M' && gender_char != 'F' && gender_char != 'N' && gender_char != 'O')
    {
        throw invalid("The gender character must be valid.");
        return false;
    }
    else if (age_num < 14)
    {
        throw invalid("You must be above 14 years to use Apollo.");
        return false;
    }
    else
    {
        set_username(u_name);
        set_password(passkey);
        set_name(f_name, l_name);
        set_age(age_num);
        set_gender(gender_char);
        ofstream file;
        file.open("__prem_users.csv", ios::app);
        if (file.is_open())
        {
            file << username << "," << password << endl;
            file.close();
            cout << "New user added successfully!" << endl;
        }
        else
        {
            cout << "Error opening file!" << endl;
        }

        return true;
    }
}

bool Apollo_User::sign_in(string username, string passkey)
{

    if (!user_exists(username))
    {
        bool opt;
        throw invalid("Username doesnt exist. Press 1 to sign up or 0 to exit: ");
        cin >> opt;
        if(opt)
        {
            //opt = sign_up(); 
        }
        else
        {
            exit(0);
        }
    }
    else
    {
        return true;
    }

}

bool Apollo_User::delete_acc(string, string)
{
    if (authenticate_user(username, password))
    {
        ifstream infile("__users.csv");
        ofstream outfile("__users_temp.csv");
        string line;
        bool found = false;
        while (getline(infile, line))
        {
            size_t pos = line.find(",");
            string user = line.substr(0, pos);
            if (user == username)
            {
                found = true;
            }
            else
            {
                outfile << line << endl;
            }
        }
        infile.close();
        outfile.close();
        if (remove("__users.csv") != 0)
        {
            perror("Error deleting file");
        }
        if (rename("__users_temp.csv", "__users.csv") != 0)
        {
            perror("Error renaming file");
        }
        cout << "User removed successfully." << endl;
    }
    else
    {
        cout << "User doesn't exist" << endl;
        return false;

    }

    return false;
}


//------------------------------------------------------------------------------------------------------------

Prem_User::Prem_User() {};

Prem_User::Prem_User(string us_name, string fr_name, string ls_name, string passkeyy, char gend, int agee):Apollo_User(us_name, fr_name, ls_name, passkeyy, gend, agee)
{
    set_Prem();
    ofstream file;
    file.open("__prem_users.csv", ios::app);

    if (file.is_open())
    {
        file << username << "," << passkeyy << endl;
        file.close();
        cout << "New user added successfully!" << endl;
    }
    else
    {
        cout << "Error opening file!" << endl;
    }
}

bool Prem_User::get_Prem(string username)
{
    return isPrem;
}

void Prem_User::set_Prem()
{
    cin >> username;
}

void Std_User::playmusic(string songname)
{
    string command = "start  D:/20XW27_Package/Apollo/Songs/" + songname;
    system(command.c_str());
    return;
}

Std_User::Std_User(string us_name, string fr_name, string ls_name, string passkeyy, char gend, int agee) : Apollo_User(us_name, fr_name, ls_name, passkeyy, gend, agee)
{

}

Std_User::Std_User(){}