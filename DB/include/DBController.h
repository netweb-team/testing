#ifndef __DBCONTROLLER_H__
#define __DBCONTROLLER_H__

#include <mutex>
#include <condition_variable>
#include <queue>
#include <fstream>
#include <pqxx/pqxx>
#include "AbstractDBController.h"

#define DEFAULT_SIZE 10
#define CONFIG "../DB/db_config.txt"

using namespace std;

class DBController : public AbstractDBController
{
public:
    explicit DBController(int size = DEFAULT_SIZE);
    ~DBController();

    bool runQuery(const string& query,
                  vector<vector<string>>& result) override;

private:
    queue<shared_ptr<pqxx::connection>> connectionPool;
    mutex mtx;
    condition_variable cond;

    void createPool(int size);
    shared_ptr<pqxx::connection> getConnection(void);
    void freeConnection(shared_ptr<pqxx::connection> connection);
};

#endif
