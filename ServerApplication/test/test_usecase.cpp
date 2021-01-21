#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "../include/ServerApplication.h"
#include "../include/DocumentParBuilder.h"
#include "../include/UserParBuilder.h"
#include "../include/MockUserRepository.h"
#include "../include/MockDocumentRepository.h"
#include "../include/MockDBController.h"
#include "../../Utils/include/DocumentBuilder.h"
#include "../../Utils/include/UserBuilder.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

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
    struct DocumentParams data = prm->build();

    auto result = server.connectDocument(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(ConnectDocument, error_doc_id)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Document was not created"));
    TestServerApplication server;
    DocumentParBuilder *prm = (new DocumentParBuilder)->setP1N(1)->setP2S("str");
    struct DocumentParams data = prm->build();

    auto result = server.connectDocument(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(ConnectDocument, good_doc_id)
{
    auto expected = make_pair(ApplicationErrors::success, string(""));
    TestServerApplication server;
    DocumentParBuilder *prm = (new DocumentParBuilder)->setP1N(1)->setP2N(3);
    struct DocumentParams data = prm->build();

    auto result = server.connectDocument(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(ConnectDocument, already_connected)
{
    auto expected = make_pair(ApplicationErrors::success, string(""));
    TestServerApplication server;
    DocumentParBuilder *prm = (new DocumentParBuilder)->setP1N(1)->setP2N(3);
    struct DocumentParams data = prm->build();
    server.connectDocument(data);

    auto result = server.connectDocument(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(DisconnectDocument, not_connected_doc)
{
    auto expected = make_pair(ApplicationErrors::failure, string("This session does not exist"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1);
    TestServerApplication server;
    struct DocumentParams data = prm->build();

    auto result = server.disconnectDocument(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(DisconnectDocument, connected_doc)
{
    auto expected = make_pair(ApplicationErrors::success, string("Editor was successfully disconnected"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1);
    TestServerApplication server;
    struct DocumentParams data = prm->build();
    server.connectDocument(data);
    

    auto result = server.disconnectDocument(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(GetDocument, not_existed_doc_id)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Document is not open"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(0);
    TestServerApplication server;
    struct DocumentParams data = prm->build();

    auto result = server.getTextDocument(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(GetDocument, not_connected_doc)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Document is not open"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1);
    TestServerApplication server;
    struct DocumentParams data = prm->build();

    auto result = server.getTextDocument(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(GetDocument, good_doc_id)
{
    auto expected = make_pair(ApplicationErrors::success, string(""));
    TestServerApplication server; 
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1)->setP2N(2);
    struct DocumentParams data = prm->build();
    server.connectDocument(data);
    prm->setP1N(prm->params.p2.num);
    data = prm->build();

    auto result = server.getTextDocument(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(DeleteDocument, not_connected_doc)
{
    auto expected = make_pair(ApplicationErrors::failure, string("This document does not exist"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1);
    TestServerApplication server;
    struct DocumentParams data = prm->build();

    auto result = server.deleteDocument(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(DeleteDocument, not_existed_doc_id)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Error with document delete"));
    TestServerApplication server; 
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1)->setP2N(8);
    struct DocumentParams data = prm->build();
    server.connectDocument(data);
    prm->setP1N(prm->params.p2.num);
    data = prm->build();

    auto result = server.deleteDocument(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(DeleteDocument, good_doc_id)
{
    auto expected = make_pair(ApplicationErrors::success, string("Document was successfully deleted"));
    TestServerApplication server; 
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1)->setP2N(2);
    struct DocumentParams data = prm->build();
    server.connectDocument(data);
    prm->setP1N(prm->params.p2.num);
    data = prm->build();

    auto result = server.deleteDocument(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(SaveDocument, not_connected_doc)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Document does not exist"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1);
    struct DocumentParams data = prm->build();
    TestServerApplication server; 

    auto result = server.saveDocument(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(SaveDocument, not_existed_doc_id)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Error with document save"));
    TestServerApplication server; 
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1)->setP2N(8);
    struct DocumentParams data = prm->build();
    server.connectDocument(data);
    prm->setP1N(prm->params.p2.num);
    data = prm->build();

    auto result = server.saveDocument(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(SaveDocument, good_doc_id)
{
    auto expected = make_pair(ApplicationErrors::success, string("Document has been saved"));
    TestServerApplication server; 
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1)->setP2N(2);
    struct DocumentParams data = prm->build();
    server.connectDocument(data);
    prm->setP1N(prm->params.p2.num);
    data = prm->build();

    auto result = server.saveDocument(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(UpdateDocument, not_connected_doc)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Document is not open"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1)->setP2N(1)->setP3S("");
    TestServerApplication server;
    struct DocumentParams data = prm->build();

    auto result = server.updateDocument(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(UpdateDocument, empty_operation)
{
    auto expected = make_pair(ApplicationErrors::success, string("Change sent successfully"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1)->setP2N(1)->setP3S(" ");
    TestServerApplication server;
    struct DocumentParams data = prm->build();
    server.connectDocument(data);
    data = prm->build();

    auto result = server.updateDocument(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(UpdateDocument, one_operation)
{
    auto expected = make_pair(ApplicationErrors::success, string("Change sent successfully"));
    DocumentParBuilder *prm = (new DocumentParBuilder())->setP1N(1)->setP2N(1)->setP3S("0,a");
    TestServerApplication server;
    struct DocumentParams data = prm->build();
    server.connectDocument(data);
    data = prm->build();

    auto result = server.updateDocument(data);

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
    struct DocumentParams data = dmother->three()->build();
    
    auto res = server.createDocument(data);
    

    EXPECT_EQ(expected, res);
}

TEST_F(TestCreateDocument, good_doc)
{
    auto expected = make_pair(ApplicationErrors::success, to_string(0));
    struct DocumentParams data = dmother->four()->build();

    auto res = server.createDocument(data);

    EXPECT_EQ(expected, res);
}

TEST_F(TestCreateDocument, existed_doc)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Error with creating document"));
    struct DocumentParams data = dmother->five()->build();
    auto res = server.createDocument(data);

    EXPECT_EQ(expected, res);
}


class TestRegisterUser : public ::testing::Test
{
protected: 
    void SetUp()
    {
        umother = new UserParMother;
    }

    void TearDown() 
    {
        delete umother;
    }

    UserParMother *umother;
    TestServerApplication server;
};

TEST_F(TestRegisterUser, empty_user)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Error with user"));
    struct UserParams data = umother->one()->build();
    
    auto result = server.registerUser(data);

    EXPECT_EQ(expected, result);
}

TEST_F(TestRegisterUser, good_user)
{
    auto expected = make_pair(ApplicationErrors::success, to_string(0));
    struct UserParams data = umother->two()->build();
    
    auto result = server.registerUser(data);

    EXPECT_EQ(expected, result);
}

TEST_F(TestRegisterUser, already_exist)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Error with creating user"));
    struct UserParams data = umother->three()->build();

    auto result = server.registerUser(data);

    EXPECT_EQ(expected, result);
}

TEST(UpdateUser, empty_user)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Error with user"));
    TestServerApplication server;
    UserParBuilder *prm = (new UserParBuilder)->setP1N(1)->setP2S("");
    struct UserParams data = prm->build();

    auto result = server.updateUser(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(UpdateUser, not_exist_user)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Error with user"));
    TestServerApplication server;
    UserParBuilder *prm = (new UserParBuilder)->setP1N(0)->setP2S("name pass");
    struct UserParams data = prm->build();

    auto result = server.updateUser(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(UpdateUser, good_user)
{
    auto expected = make_pair(ApplicationErrors::success, string("User was successfully updated"));
    TestServerApplication server;
    UserParBuilder *prm = (new UserParBuilder)->setP1N(1)->setP2S("name pass");
    struct UserParams data = prm->build();

    auto result = server.updateUser(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(LoginUser, not_exist_user)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Error with user"));
    TestServerApplication server;
    UserParBuilder *prm = (new UserParBuilder)->setP1S("username")->setP2S("password");
    struct UserParams data = prm->build();
    
    auto result = server.loginUser(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(LoginUser, exist_user)
{
    auto expected = make_pair(ApplicationErrors::success, to_string(0));
    TestServerApplication server;
    UserParBuilder *prm = (new UserParBuilder)->setP1S("name")->setP2S("pass");
    struct UserParams data = prm->build();

    auto result = server.loginUser(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(LogoutUser, not_exist_user_id)
{
    auto expected = make_pair(ApplicationErrors::failure, string("Error with user"));
    TestServerApplication server;
    UserParBuilder *prm = (new UserParBuilder)->setP1N(0);
    struct UserParams data = prm->build();

    auto result = server.logoutUser(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(LogoutUser, unlogged_user)
{
    auto expected = make_pair(ApplicationErrors::success, string("User was successfully logouted"));
    TestServerApplication server;
    UserParBuilder *prm = (new UserParBuilder)->setP1N(1);
    struct UserParams data = prm->build();

    auto result = server.logoutUser(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

TEST(LogoutUser, good_user)
{
    auto expected = make_pair(ApplicationErrors::success, string("User was successfully logouted"));
    TestServerApplication server;
    UserParBuilder *prm = (new UserParBuilder)->setP1N(2);
    struct UserParams data = prm->build();

    auto result = server.logoutUser(data);

    EXPECT_EQ(expected, result);
    delete prm;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
