#include <exception>
#include <random>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>


class Apollo_User
{
    private:

        std::string password;
        bool is_deleted;

        void set_password(std::string);
        void set_name(std::string, std::string);
        void set_gender(char);
        void set_age(int);

        std::string get_password();


    protected:
        std::string first_name;
        std::string last_name;
        char gender;
        int age;

    public:
        std::string username;

        Apollo_User();
        Apollo_User(std::string, std::string, std::string, std::string, char, int);

        void set_username(std::string);
        std::string get_username();
        bool sign_up(std::string, std::string, std::string, std::string, char, int);
        bool sign_up_user(std::string, std::string, std::string, std::string, char, int);
        bool sign_up_prem(std::string, std::string, std::string, std::string, char, int);
        bool sign_in(std::string, std::string);
        bool delete_acc(std::string, std::string);

        static std::string generateUserId();
        static bool password_validator(std::string passkey);
        static bool user_exists(std::string username);
        static bool prem_user_exists(std::string username);
        static bool verify_prem_user();
        static int authenticate_user(std::string username, std::string password);
        static int authenticate_prem_user(std::string username, std::string password);
};


class Std_User : public Apollo_User
{
    public:
        void playmusic(std::string);
        Std_User(std::string, std::string, std::string, std::string, char, int);
        Std_User();
    
};


class Prem_User : public Apollo_User
{
	private:
		bool isPrem;
	public:
        Prem_User();
        Prem_User(std::string, std::string, std::string, std::string, char, int);
        bool get_Prem(std::string username);
        void set_Prem();
        void access_gui();
};


class invalid : public std::exception
{
    public:
        invalid(const std::string &message) : message(message) {}

        const char *what() const noexcept override
        {
            return message.c_str();
        }

    private:
        std::string message;
};

