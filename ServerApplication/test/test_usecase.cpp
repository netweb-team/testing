#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "../include/ServerApplication.h"
#include "../include/DocumentParBuilder.h"
#include "../include/UserParBuilder.h"
#include "../../Utils/include/DocumentBuilder.h"
#include "../../Utils/include/UserBuilder.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

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
        else if (d.getId() > 10)
            throw runtime_error("error id");
        DocumentBuilder dbuilder;
        d = *dbuilder.build();
    }
    void deleteD(Document& d)
    {
        if (d.getId() < 1)
            throw runtime_error("not exist");
        else if (d.getId() > 10)
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
        if (u.getId() < 1)
            throw runtime_error("not exist");
        else if (u.getId() > 10)
            throw runtime_error("error id");
        DocumentBuilder dbuilder;
        Document *doc = dbuilder.build();
        vector<shared_ptr<Document>> result;
        result.push_back(make_shared<Document>(doc->getId(), doc->getName(), doc->getText()));
        return result;
    }
    void addUserToDoc(User& u, Document& d) 
    {
        if (u.getId() < 1 || d.getId() < 1)
            throw runtime_error("not exist");
        return;
    }
};

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
        user->setId(u->getId());
        user->setName(u->getName());
        user->setPassword(u->getPassword());
        user->setIsLogin(u->getIsLogin());
        return user;
    }
    void check(User& u) 
    {
        if (u.getName() != "name" && u.getPassword() != "pass")
            throw runtime_error("not exist");
        return;
    }
};

class TestServerApplication: public ServerApplication
{
public:
    TestServerApplication()
    {
        this->docRepository = make_shared<MockDocumentRepository>();
        this->userRepository = make_shared<MockUserRepository>();
    }
    ~TestServerApplication() = default;
};

TEST(ConnectDocument, not_existed_doc_id)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Document was not created"));
    TestServerApplication server;
    DocumentParBuilder *prm = (new DocumentParBuilder)->setP1N(1)->setP2N(0);

    auto result = server.connectDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(ConnectDocument, error_doc_id)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Document was not created"));
    TestServerApplication server;
    DocumentParBuilder *prm = (new DocumentParBuilder)->setP1N(1)->setP2S("str");

    auto result = server.connectDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(ConnectDocument, good_doc_id)
{
    auto expected = make_pair(ApplicationErrors::success, string(""));
    TestServerApplication server;
    DocumentParBuilder *prm = (new DocumentParBuilder)->setP1N(1)->setP2N(3);

    auto result = server.connectDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(ConnectDocument, already_connected)
{
    auto expected = make_pair(ApplicationErrors::success, string(""));
    TestServerApplication server;
    DocumentParBuilder *prm = (new DocumentParBuilder)->setP1N(1)->setP2N(3);
    server.connectDocument(prm->build());

    auto result = server.connectDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(DisconnectDocument, not_connected_doc)
{
    auto expected = make_pair(ApplicationErrors::failure, string("This session does not exist"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1);
    TestServerApplication server; 

    auto result = server.disconnectDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(DisconnectDocument, connected_doc)
{
    auto expected = make_pair(ApplicationErrors::success, string("Editor was successfully disconnected"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1);
    TestServerApplication server; 
    server.connectDocument(prm->build());

    auto result = server.disconnectDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(GetDocument, not_existed_doc_id)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Document is not open"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(0);
    TestServerApplication server; 

    auto result = server.getTextDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(GetDocument, not_connected_doc)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Document is not open"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1);
    TestServerApplication server; 

    auto result = server.getTextDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(GetDocument, good_doc_id)
{
    auto expected = make_pair(ApplicationErrors::success, string(""));
    TestServerApplication server; 
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1)->setP2N(2);
    server.connectDocument(prm->build());
    prm->setP1N(prm->params.p2.num);

    auto result = server.getTextDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

/*TEST(CreateDocument, empty_doc_name)
{
    DocumentParams prm = { 1, 1 };
    TestServerApplication tsa;
    tsa.connectDocument(prm);
}*/

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}