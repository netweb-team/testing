#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "../include/ServerApplication.h"
#include "../../Utils/include/DocumentBuilder.h"

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

class MockDocumentRepository : public DocumentRepository 
{
public:
    MockDocumentRepository() {}
    ~MockDocumentRepository() = default;

    void createDoc(Document& d)
    {
        DocumentBuilder dbuilder;
        d = *dbuilder.build();
    }
    void changeDoc(Document& d)
    {
        DocumentBuilder dbuilder;
        d = *dbuilder.build();
    }
    void deleteDoc(Document& d)
    {
        return;
    }
    shared_ptr<Document> getById(int id)
    {
        DocumentBuilder dbuilder;
        Document *doc = dbuilder.build();
        return make_shared<Document>(doc->getId(), doc->getName(), doc->getText());
    }
    vector<shared_ptr<Document>> getByUser(User& u)
    {
        DocumentBuilder dbuilder;
        Document *doc = dbuilder.build();
        vector<shared_ptr<Document>> result;
        result.push_back(make_shared<Document>(doc->getId(), doc->getName(), doc->getText()));
        return result;
    }
    void addUser(User& u, Document& d) 
    {
        return;
    }
};

class MockUserRepository : public UserRepository 
{
public:
    MockUserRepository() {}
    ~MockUserRepository() = default;

    void createUser(User& u)
    {
        UserBuilder ubuilder;
        u = *ubuilder.build();
    }
    void updateUser(User& u)
    {
        UserBuilder ubuilder;
        u = *ubuilder.build();
    }
    shared_ptr<User> getById(int id)
    {
        UserBuilder ubuilder;
        User *u = ubuilder.build();
        auto user = make_shared<User>();
        user->setId(u->getId());
        user->setName(u->getName());
        user->setPassword(u->getPassword());
        user->setIsLogin(u->getIsLogin());
        return user;
    }
    void checkUser(User& u) 
    {
        return;
    }
};

class TestServerApplication: public ServerApplication
{
public:
    TestServerApplication()
    {
        //auto ctrl = make_shared<MockDBController>();
        this->docRepository = make_shared<MockDocumentRepository>();
        this->userRepository = make_shared<MockUserRepository>();
    }
    ~TestServerApplication() = default;
};

TEST(GetDocument, not_existed_doc_id)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Document is not open"));
    DocumentParams prm = { 0 };
    auto server = ServerApplication::get_instance();

    auto result = server->getTextDocument(prm);

    EXPECT_EQ(expected, result);
}

TEST(GetDocument, error_doc_id)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Document is not open"));
    DocumentParams prm = { 0 };
    prm.p1.str = (char *) "some string";
    auto server = ServerApplication::get_instance();

    auto result = server->getTextDocument(prm);

    EXPECT_EQ(expected, result);
}

TEST(GetDocument, good_doc_id)
{
    auto expected = make_pair(ApplicationErrors::success, string(""));
    DocumentParams prm = { 1, 1 };
    auto server = ServerApplication::get_instance();
    server->connectDocument(prm);

    auto result = server->getTextDocument(prm);

    EXPECT_EQ(expected, result);
}

TEST(CreateDocument, empty_doc_name)
{
    DocumentParams prm = { 1, 1 };
    TestServerApplication tsa;
    tsa.connectDocument(prm);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}