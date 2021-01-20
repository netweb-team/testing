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

TEST(DeleteDocument, not_connected_doc)
{
    auto expected = make_pair(ApplicationErrors::failure, string("This document does not exist"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1);
    TestServerApplication server; 

    auto result = server.deleteDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(DeleteDocument, not_existed_doc_id)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Error with document delete"));
    TestServerApplication server; 
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1)->setP2N(8);
    server.connectDocument(prm->build());
    prm->setP1N(prm->params.p2.num);

    auto result = server.deleteDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(DeleteDocument, good_doc_id)
{
    auto expected = make_pair(ApplicationErrors::success, string("Document was successfully deleted"));
    TestServerApplication server; 
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1)->setP2N(2);
    server.connectDocument(prm->build());
    prm->setP1N(prm->params.p2.num);

    auto result = server.deleteDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(SaveDocument, not_connected_doc)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Document does not exist"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1);
    TestServerApplication server; 

    auto result = server.saveDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(SaveDocument, not_existed_doc_id)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Error with document save"));
    TestServerApplication server; 
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1)->setP2N(8);
    server.connectDocument(prm->build());
    prm->setP1N(prm->params.p2.num);

    auto result = server.saveDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(SaveDocument, good_doc_id)
{
    auto expected = make_pair(ApplicationErrors::success, string("Document has been saved"));
    TestServerApplication server; 
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1)->setP2N(2);
    server.connectDocument(prm->build());
    prm->setP1N(prm->params.p2.num);

    auto result = server.saveDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(UpdateDocument, not_connected_doc)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Document is not open"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1)->setP2N(1)->setP3S("");
    TestServerApplication server; 

    auto result = server.updateDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(UpdateDocument, empty_operation)
{
    auto expected = make_pair(ApplicationErrors::success, string("Change sent successfully"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1)->setP2N(1)->setP3S(" ");
    TestServerApplication server; 
    server.connectDocument(prm->build());

    auto result = server.updateDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(UpdateDocument, one_operation)
{
    auto expected = make_pair(ApplicationErrors::success, string("Change sent successfully"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1)->setP2N(1)->setP3S("0,a");
    TestServerApplication server; 
    server.connectDocument(prm->build());

    auto result = server.updateDocument(prm->build());

    EXPECT_EQ(expected, result);
    delete prm;
}

class TestCreateDocument : public ::testing::Test
{
protected: 
    void SetUp()
    {
        dmother = new DocumentParMother;
    }

    void TearDown() 
    {
        delete dmother;
    }

    DocumentParMother *dmother;
    TestServerApplication server;
};

TEST_F(TestCreateDocument, empty_doc_name)
{
    auto expected = make_pair(ApplicationErrors::success, to_string(0));

    auto res = server.createDocument(dmother->three()->build());

    EXPECT_EQ(expected, res);
}

TEST_F(TestCreateDocument, good_doc)
{
    auto expected = make_pair(ApplicationErrors::success, to_string(0));

    auto res = server.createDocument(dmother->four()->build());

    EXPECT_EQ(expected, res);
}

TEST_F(TestCreateDocument, existed_doc)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Error with creating document"));

    auto res = server.createDocument(dmother->five()->build());

    EXPECT_EQ(expected, res);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}