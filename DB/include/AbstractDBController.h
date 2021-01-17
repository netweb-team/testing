#ifndef __ABSTRACTDBCONTROLLER_H__
#define __ABSTRACTDBCONTROLLER_H__

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class AbstractDBController
{
public:
    AbstractDBController() = default;
    virtual ~AbstractDBController() = default;

    virtual bool runQuery(const string& query,
                          vector<vector<string>>& result) = 0;
};

#endif
