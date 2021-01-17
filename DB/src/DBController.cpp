#include "../include/DBController.h"

DBController::DBController(int size)
{
    createPool(size);
}

DBController::~DBController()
{

}

bool DBController::runQuery(const string& query,
                            vector<vector<string>>& result)
{
    auto connect = getConnection();
    pqxx::work worker(*connect.get());
    bool flag = true;
    try
    {
        pqxx::result r = worker.exec(query);
        worker.commit();
        result.clear();

        if (r.empty() && r.affected_rows() == 0) {
            flag = false;
        }

        for (auto row: r)
        {
            result.push_back(vector<string>());
            for (int i = 0; i < row.size(); i++)
                result.back().push_back(row[i].as<string>());
        }
    }
    catch(const std::exception& e)
    {
        cerr << e.what() << endl;
        cerr << "Query: " << query << endl;
        flag = false;
    }
    freeConnection(connect);
    return flag;
}

void DBController::createPool(int size)
{
    string connectString = "";
    ifstream fin(CONFIG, ios_base::in);
    if (fin.is_open())
    {
        string param = "";
        while (fin >> param)
            connectString += param + " ";
        fin.close();
    }
    try
    {
        for (int i = 0; i < size; ++i)
            connectionPool.push(make_shared<pqxx::connection>(connectString));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
    }
}

shared_ptr<pqxx::connection> DBController::getConnection(void)
{
    unique_lock<mutex> lock(mtx);
    while (connectionPool.empty())
    {
        cond.wait(lock);
    }

    auto connect = connectionPool.front();
    connectionPool.pop();
    return connect;
}

void DBController::freeConnection(shared_ptr<pqxx::connection> connection)
{
    unique_lock<mutex> lock(mtx);
    connectionPool.push(connection);
    lock.unlock();
    cond.notify_one();
}
