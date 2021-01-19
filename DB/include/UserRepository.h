#ifndef __USERREPOSITORY_H__
#define __USERREPOSITORY_H__

#include <boost/format.hpp>
#include <memory>
#include "AbstractDBController.h"
#include "../../Utils/include/User.h"

using namespace std;

class UserRepositoryI
{
public:
    UserRepositoryI() = default;
    virtual ~UserRepositoryI() = default;
    virtual void create(User& u) = 0;
    virtual void update(User& u) = 0;
    virtual shared_ptr<User> get(int id) = 0;
    virtual void check(User& u) = 0;
};

class UserRepository : public UserRepositoryI
{
public:
    UserRepository() = default;
    UserRepository(shared_ptr<AbstractDBController> ctrl);
    ~UserRepository();

    void createUser(User& u);
    void updateUser(User& u);
    shared_ptr<User> getById(int id);
    void checkUser(User& u);

    virtual void create(User& u) { createUser(u); }
    virtual void update(User& u) { updateUser(u); }
    virtual shared_ptr<User> get(int id) { return getById(id); }
    virtual void check(User& u) { checkUser(u); }

private:
    shared_ptr<AbstractDBController> db;
};

#endif
