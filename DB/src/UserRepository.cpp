#include "../include/UserRepository.h"

UserRepository::UserRepository(shared_ptr<AbstractDBController> ctrl) :
        db(ctrl) {}

UserRepository::~UserRepository() {}

void UserRepository::createUser(User& u)
{
    vector<vector<string>> query_result = {};
    string query1 =
            (boost::format(
                    "INSERT INTO users VALUES(%1%, '%2%', '%3');")
             % "default"
             % u.getName()
             % u.getPassword()
            ).str();
    string query2 =
            (boost::format(
                    "SELECT max(id) FROM users;")
            ).str();
    if (db)
    {
        if (db->runQuery(query1, query_result) != true)
            throw runtime_error("cannot create user.");
        if (db->runQuery(query2, query_result) != true)
            throw runtime_error("cannot get id of user.");
        u.setId(stoi(query_result[0][0]));
    }
    else
        throw runtime_error("no db controller.");
}

shared_ptr<User> UserRepository::getById(int id)
{
    vector<vector<string>> query_result = {};
    string query =
            (boost::format(
                    "SELECT * FROM users WHERE id = %1%;")
             % id
            ).str();
    if (db)
    {
        if (db->runQuery(query, query_result) != true)
            throw runtime_error("cannot get user.");
    }
    else
        throw runtime_error("no db controller.");

    shared_ptr<User> user = make_shared<User>();
    user->setId(stoi(query_result[0][0]));
    user->setName(query_result[0][1]);
    user->setPassword(query_result[0][2]);
    return user;
}

void UserRepository::updateUser(User& u)
{
    vector<vector<string>> query_result = {};
    string query =
            (boost::format(
                    "UPDATE users SET username = '%1%', password = '%2%' WHERE id = %3%;")
             % u.getName()
             % u.getPassword()
             % u.getId()
            ).str();
    if (db)
    {
        if (db->runQuery(query, query_result) != true)
            throw runtime_error("cannot update document.");
    }
    else
        throw runtime_error("no db controller.");
}
