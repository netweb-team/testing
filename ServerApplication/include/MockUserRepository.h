#ifndef MOCKUSER_REPOSITORY_H
#define MOCKUSER_REPOSITORY_H

#include "../../Utils/include/UserBuilder.h"

class MockUserRepository : public UserRepositoryI
{
public:
    MockUserRepository() {}
    ~MockUserRepository() = default;

    void create(User& u)
    {
        if (u.getName() == "name" && u.getPassword() == "pass")
            throw runtime_error("already exist");
        UserBuilder ubuilder;
        u = *ubuilder.build();
    }
    void update(User& u)
    {
        if (u.getId() < 1)
            throw runtime_error("not exist");
        else if (u.getId() > 10)
            throw runtime_error("error id");
        UserBuilder ubuilder;
        u = *ubuilder.build();
    }
    shared_ptr<User> get(int id)
    {
        if (id < 1)
            throw runtime_error("not exist");
        else if (id > 10)
            throw runtime_error("error id");
        UserBuilder ubuilder;
        User *u = ubuilder.build();
        auto user = make_shared<User>();
        user->setId(id);
        user->setName(u->getName());
        user->setPassword(u->getPassword());
        user->setIsLogin(u->getIsLogin());
        return user;
    }
    void check(User& u)
    {
        if (u.getName() != "name" && u.getPassword() != "pass")
            throw runtime_error("not exist");
        UserBuilder *ubuilder = (new UserBuilder)->setId(1);
        u = *ubuilder->build();
        delete ubuilder;
    }
};
#endif //MOCKUSER_REPOSITORY_H
