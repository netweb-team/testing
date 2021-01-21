#ifndef MOCKDB_CONTROLLER_H
#define MOCKDB_CONTROLLER_H

class MockDBController : public DBController
{
public:
    MockDBController() = default;
    ~MockDBController() = default;

    bool runQuery(const string& query, vector<vector<string>>& result) override
    {
        result.push_back(vector<string>());
        result.back().push_back("1");
        result.back().push_back("");
        result.back().push_back("docname");
        return true;
    }
};

#endif //MOCKDB_CONTROLLER_H
