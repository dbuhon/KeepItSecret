#ifndef USER_H
#define USER_H


class user
{
public:
    user();
    user(const char*& _login, const char*& _password1, const char*& _password2);
    bool save();
    ~user();

private:
    char* login;
    char* password;
};

#endif // USER_H
