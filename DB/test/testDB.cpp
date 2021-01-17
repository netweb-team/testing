#include <gtest/gtest.h>
#include "gmock/gmock.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

#include "../include/AbstractDBController.h"
#include "../include/DocumentRepository.h"
#include "../include/UserRepository.h"
#include "../../ServerApplication/include/ServerApplication.h"

bool operator ==(const User &op1, const User &op2) { return true; }
bool operator ==(const Document &op1, const Document &op2) { return true; }

class MockDBController : public AbstractDBController
{
public:
    MOCK_METHOD2(runQuery, bool(const string&, vector<vector<string>>&));
};

class TestDBController : public ::testing::Test
{
protected: 
    void SetUp()
    {
        db_ctrl = make_shared<MockDBController>();
    }

    void TearDown() {}

    shared_ptr<MockDBController> db_ctrl;
    vector<vector<string>> result;
};

TEST_F(TestDBController, workWithDocument)
{
    EXPECT_CALL(*db_ctrl, runQuery("", result)).Times(AtLeast(5));
    DocumentRepository drep(db_ctrl);
    Document doc;
    User user;
    drep.createDoc(doc);
    drep.changeDoc(doc);
    drep.getById(doc.getId());
    drep.addUser(user, doc);
    drep.getByUser(user);
}

TEST_F(TestDBController, workWithUser)
{
    EXPECT_CALL(*db_ctrl, runQuery("", result)).Times(AtLeast(2));
    UserRepository urep(db_ctrl);
    User user;
    urep.createUser(user);
    urep.getById(user.getId());
}

class MockUserRepository : public UserRepositoryI
{
public:
    MOCK_METHOD1(createTest, void(User&));
    MOCK_METHOD1(getTest, User(int));
};

TEST(UserRepository, methodsCall)
{
    MockUserRepository murep;
    ServerApplication appServer;
    User user;
    EXPECT_CALL(murep, createTest(user)).Times(AtLeast(1));
    EXPECT_CALL(murep, getTest(user.getId())).Times(AtLeast(1));
    appServer.registerUser("");
    appServer.loginUser(); // ???
}

class MockDocumentRepository : public DocumentRepositoryI
{
public:
    MOCK_METHOD1(createTest, void(Document&));
    MOCK_METHOD1(changeTest, void(Document&));
    MOCK_METHOD1(deleteTest, void(Document&));
    MOCK_METHOD1(getIdTest, Document(int));
    MOCK_METHOD1(getUserTest, Document(User&));
    MOCK_METHOD2(addUserTest, void(User&, Document&));
};

TEST(DocumentRepository, methodsCall)
{
    MockDocumentRepository mdrep;
    ServerApplication appServer;
    Document doc;
    User user;
    EXPECT_CALL(mdrep, createTest(doc)).Times(AtLeast(1));
    EXPECT_CALL(mdrep, changeTest(doc)).Times(AtLeast(1));
    EXPECT_CALL(mdrep, getIdTest(doc.getId())).Times(AtLeast(1));
    EXPECT_CALL(mdrep, addUserTest(user, doc)).Times(AtLeast(1));
    EXPECT_CALL(mdrep, getUserTest(user)).Times(AtLeast(1));
    EXPECT_CALL(mdrep, deleteTest(doc)).Times(AtLeast(1));
    appServer.createDocument();
    Operation op;
    appServer.updateDocument(op);
    appServer.readDocument();
    appServer.connectDocument(user.getId(), doc.getId());
    appServer.connectDocument(user.getId(), doc.getId());
    appServer.deleteDocument();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
