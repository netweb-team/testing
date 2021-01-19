#ifndef __DOCUMENTREPOSITORY_H__
#define __DOCUMENTREPOSITORY_H__

#include <boost/format.hpp>
#include <memory>
#include "AbstractDBController.h"
#include "../../Utils/include/User.h"
#include "../../Utils/include/Document.h"

using namespace std;

class DocumentRepositoryI
{
public:
    DocumentRepositoryI() = default;
    virtual ~DocumentRepositoryI() = default;
    virtual void createTest(Document& d) = 0;
    virtual void changeTest(Document& d) = 0;
    virtual void deleteTest(Document& d) = 0;
    virtual shared_ptr<Document> getIdTest(int id) = 0;
    virtual vector<shared_ptr<Document>> getUserTest(User& u) = 0;
    virtual void addUserTest(User& u, Document& d) = 0;
};

class DocumentRepository : public DocumentRepositoryI
{
public:
    DocumentRepository() = default;
    DocumentRepository(shared_ptr<AbstractDBController> ctrl);
    ~DocumentRepository();

    void createDoc(Document& d);
    void changeDoc(Document& d);
    void deleteDoc(Document& d);
    shared_ptr<Document> getById(int id);
    vector<shared_ptr<Document>> getByUser(User& u);
    void addUser(User& u, Document& d);

    virtual void createTest(Document& d) { createDoc(d); }
    virtual void changeTest(Document& d) { changeDoc(d); }
    virtual void deleteTest(Document& d) { deleteDoc(d); }
    virtual shared_ptr<Document> getIdTest(int id) { return getById(id); }
    virtual vector<shared_ptr<Document>> getUserTest(User& u) { return getByUser(u); }
    virtual void addUserTest(User& u, Document& d) { addUser(u, d); }

private:
    shared_ptr<AbstractDBController> db;
};

#endif
