#ifndef MOCKDOCUMENT_REPOSITORY_H
#define MOCKDOCUMENT_REPOSITORY_H

#include "../../Utils/include/DocumentBuilder.h"

class MockDocumentRepository : public DocumentRepositoryI
{
public:
    MockDocumentRepository() {}
    ~MockDocumentRepository() = default;

    void create(Document& d)
    {
        if (d.getName() == "name")
            throw runtime_error("already exist");
        DocumentBuilder dbuilder;
        d = *dbuilder.build();
    }
    void change(Document& d)
    {
        if (d.getId() < 1)
            throw runtime_error("not exist");
        else if (d.getId() > 5)
            throw runtime_error("error id");
        DocumentBuilder dbuilder;
        d = *dbuilder.build();
    }
    void deleteD(Document& d)
    {
        if (d.getId() < 1)
            throw runtime_error("not exist");
        else if (d.getId() > 5)
            throw runtime_error("error id");
        return;
    }
    shared_ptr<Document> getId(int id)
    {
        //cout << "here" << endl;
        if (id < 1)
            throw runtime_error("not exist");
        else if (id > 10)
            throw runtime_error("error id");
        DocumentBuilder *dbuilder = (new DocumentBuilder)->setId(id);
        Document *doc = dbuilder->build();
        delete dbuilder;
        return make_shared<Document>(doc->getId(), doc->getName(), doc->getText());
    }
    vector<shared_ptr<Document>> getUserDocs(User& u)
    {
        DocumentBuilder dbuilder;
        Document *doc = dbuilder.build();
        vector<shared_ptr<Document>> result;
        result.push_back(make_shared<Document>(doc->getId(), doc->getName(), doc->getText()));
        return result;
    }
    void addUserToDoc(User& u, Document& d)
    {
        return;
    }
};

#endif //MOCKDOCUMENT_REPOSITORY_H
