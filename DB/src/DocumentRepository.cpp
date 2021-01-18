#include "../include/DocumentRepository.h"

DocumentRepository::DocumentRepository(shared_ptr<AbstractDBController> ctrl) :
        db(ctrl) {}

DocumentRepository::~DocumentRepository() {}

void DocumentRepository::createDoc(Document& d)
{
    vector<vector<string>> query_result = {};
    string query1 =
            (boost::format(
                    "INSERT INTO document VALUES(%1%, '%2%', '%3%');")
             % "default"
             % d.getText()
             % d.getName()
            ).str();
    string query2 =
            (boost::format(
                    "SELECT max(id) FROM document;")
            ).str();
    if (db)
    {
        if (db->runQuery(query1, query_result) != true)
            throw runtime_error("cannot create document.");
        if (db->runQuery(query2, query_result) != true)
            throw runtime_error("cannot get id of document.");
        d.setId(stoi(query_result[0][0]));
    }
    else
        throw runtime_error("no db controller.");
}

void DocumentRepository::changeDoc(Document& d)
{
    vector<vector<string>> query_result = {};
    string query =
            (boost::format(
                    "UPDATE document SET dtext = '%1%', name = '%2%' WHERE id = %3%;")
             % d.getText()
             % d.getName()
             % d.getId()
            ).str();
    if (db)
    {
        if (db->runQuery(query, query_result) != true)
            throw runtime_error("cannot update document.");
    }
    else
        throw runtime_error("no db controller.");
}

void DocumentRepository::deleteDoc(Document& d)
{
    vector<vector<string>> query_result = {};
    string query =
            (boost::format(
                    "DELETE FROM document WHERE id = %1%;")
             % d.getId()
            ).str();
    if (db)
    {
        if (db->runQuery(query, query_result) != true)
            throw runtime_error("cannot delete document.");
    }
    else
        throw runtime_error("no db controller.");
}

shared_ptr<Document> DocumentRepository::getById(int id)
{
    vector<vector<string>> query_result = {};
    string query =
            (boost::format(
                    "SELECT d.id, d.dtext FROM document AS d WHERE d.id = %1%;")
             % id
            ).str();
    if (db)
    {
        if (db->runQuery(query, query_result) != true)
            throw runtime_error("cannot get document.");
    }
    else
        throw runtime_error("no db controller.");

    shared_ptr<Document> doc = make_shared<Document>(stoi(query_result[0][0]),
                                                     query_result[0][1]);
//    for (auto row: query_result) {
//        doc->addOwner(stoi(row[2]));
//    }
    return doc;
}

vector<shared_ptr<Document>> DocumentRepository::getByUser(User& u)
{
    vector<vector<string>> query_result = {};
    string query =
            (boost::format(
                    "SELECT d.id, d.dtext FROM document AS d JOIN ownership AS ow ON d.id = ow.doc_id WHERE ow.user_id = %1%;")
             % u.getId()
            ).str();

    vector<shared_ptr<Document>> result = {};
    if (db)
    {
        if (db->runQuery(query, query_result) != true)
            throw runtime_error("cannot get document.");
        for (auto row: query_result)
        {
            result.emplace_back(make_shared<Document>(stoi(row[0]), row[1]));
            result.back()->addOwner(u.getId());
        }
    }
    else
        throw runtime_error("no db controller.");
    return result;
}

void DocumentRepository::addUser(User& u, Document& d)
{
    vector<vector<string>> query_result = {};
    string query =
            (boost::format(
                    "INSERT INTO ownership VALUES(%1%, %2%, %3%);")
             % "default"
             % u.getId()
             % d.getId()
            ).str();
    if (db)
    {
        if (db->runQuery(query, query_result) != true)
            throw runtime_error("cannot add ownership of document.");
    }
    else
        throw runtime_error("no db controller.");
}
