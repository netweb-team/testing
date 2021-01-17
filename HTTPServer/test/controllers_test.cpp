#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "controller/controllers.h"

#include "requests/Request.h"
#include "requests/Reply.h"

#include "client/Client.h"

/*
Добрый день!
В данный момент этот класс должен находиться в папке ServerApplication,
но, к сожалению, возникла некоторая неопределнность, так как этот
класс является связующим между http-сервером и логикой приложения.
В ближайшее время это недарозумение будет приведено к порядочному виду.
 */

class BaseServerApplication {
public:
  BaseServerApplication() = default;
  virtual ~BaseServerApplication() = default;

  virtual int createDocument(std::string userData, std::string documentName) = 0;

  virtual std::vector<std::string> updateDocument(std::string userData,
                                                  int docId,
                                                  std::vector<std::string> operations) = 0;

  virtual void deleteDocument(std::string userData, int docId) = 0;

  virtual std::string readDocument(std::string userData, int docId) = 0;

  virtual std::string connectDocument(std::string userData, int docId) = 0;

  virtual std::string loginUser(std::string userData) = 0;

  virtual std::string registerUser(std::string userData) = 0;

  virtual std::string logoutUser(std::string userData) = 0;
};

using namespace std;

class MockServerApplication {
public:
  MockServerApplication() = default;

  virtual ~MockServerApplication() = default;

  MOCK_METHOD2(createDocument, int(string userData, string documentName));

  MOCK_METHOD3(updateDocument, vector<string>(string userData, int docId, vector<string> operations));

  MOCK_METHOD2(deleteDocument, void(string userData, int docId));

  MOCK_METHOD2(readDocument, string(string userData, int docId));

  MOCK_METHOD2(connectDocument, std::string(string userData, int docId));

  MOCK_METHOD1(loginUser, string(string userData));

  MOCK_METHOD1(registerUser, string(string userData));

  MOCK_METHOD1(logoutUser, string(string userData));

};

using namespace http;

//
//class MockClient : public Client {
//public:
//  MockClient() = default;
//  MOCK_METHOD0(run, void());
//};
//
//class MockConnectController : public server::ConnectController {
//public:
//  MockConnectController() = default;
//  MOCK_METHOD1(handleRequest, Reply(const Request &Request));
//};
//
//class MockCreateController : public server::CreateController {
//public:
//  MockCreateController() = default;
//  MOCK_METHOD1(handleRequest, Reply(const Request &Request));
//};
//
//class MockDeleteController : public server::DeleteController {
//public:
//  MockDeleteController() = default;
//  MOCK_METHOD1(handleRequest, Reply(const Request &Request));
//};
//
//class MockEditController : public server::EditController {
//public:
//  MockEditController() = default;
//  MOCK_METHOD1(handleRequest, Reply(const Request &Request));
//};
//
//class MockLoginController : public server::LoginController {
//public:
//  MockLoginController() = default;
//  MOCK_METHOD1(handleRequest, Reply(const Request &Request));
//};
//
//class MockLogoutController : public server::LogoutController {
//public:
//  MockLogoutController() = default;
//  MOCK_METHOD1(handleRequest, Reply(const Request &Request));
//};
//
//class MockRegistrationController : public server::RegistrationController {
//public:
//  MockRegistrationController() = default;
//  MOCK_METHOD1(handleRequest, Reply(const Request &Request));
//};
//

using ::testing::_;

class ConnectControllerTest : public ::testing::Test {
protected:
  void SetUp() override {
    controller = c.createController();
    application = make_shared<MockServerApplication>();
  }

  shared_ptr<server::Controller> controller;
  shared_ptr<MockServerApplication> application;

  server::ConnectControllerCreator c;
};

TEST_F(ConnectControllerTest, test1) {
  EXPECT_CALL(*application, connectDocument(_, _)).Times(1);

  Request q;
  q.headers["type"] = "connect";
  Reply r = controller->handleRequest(q);
  ASSERT_EQ(r.headers["type"], "connect");
}

class CreateControllerTest : public ::testing::Test {
protected:
  void SetUp() override {
    controller = c.createController();
    application = make_shared<MockServerApplication>();
  }

  shared_ptr<server::Controller> controller;
  shared_ptr<MockServerApplication> application;

  server::CreateControllerCreator c;
};

TEST_F(CreateControllerTest, test1) {
  EXPECT_CALL(*application, createDocument(_, _)).Times(1);

  Request q;
  q.headers["type"] = "create";
  Reply r = controller->handleRequest(q);
  ASSERT_EQ(r.headers["type"], "create");
}

class DeleteControllerTest : public ::testing::Test {
protected:
  void SetUp() override {
    controller = c.createController();
    application = make_shared<MockServerApplication>();
  }

  shared_ptr<server::Controller> controller;
  shared_ptr<MockServerApplication> application;

  server::DeleteControllerCreator c;
};

TEST_F(DeleteControllerTest, test1) {
  EXPECT_CALL(*application, deleteDocument(_, _)).Times(1);

  Request q;
  q.headers["type"] = "delete";
  Reply r = controller->handleRequest(q);
  ASSERT_EQ(r.headers["type"], "delete");
}

class EditControllerTest : public ::testing::Test {
protected:
  void SetUp() override {
    controller = c.createController();
    application = make_shared<MockServerApplication>();
  }

  shared_ptr<server::Controller> controller;
  shared_ptr<MockServerApplication> application;

  server::EditControllerCreator c;
};

TEST_F(EditControllerTest, test1) {
  EXPECT_CALL(*application, updateDocument(_, _, _)).Times(0);

  Request q;
  q.headers["type"] = "edit";
  Reply r = controller->handleRequest(q);

  ASSERT_EQ(r.headers["type"], "edit");
}

class LoginControllerTest : public ::testing::Test {
protected:
  void SetUp() override {
    controller = c.createController();
    application = make_shared<MockServerApplication>();
  }

  shared_ptr<server::Controller> controller;
  shared_ptr<MockServerApplication> application;

  server::EditControllerCreator c;
};

TEST_F(LoginControllerTest, test1) {
  EXPECT_CALL(*application, loginUser(_)).Times(0);

  Request q;
  q.headers["type"] = "login";
  Reply r = controller->handleRequest(q);
  ASSERT_EQ(r.headers["type"], "login");
}

class LogoutControllerTest : public ::testing::Test {
protected:
  void SetUp() override {
    controller = c.createController();
    application = make_shared<MockServerApplication>();
  }

  shared_ptr<server::Controller> controller;
  shared_ptr<MockServerApplication> application;

  server::LogoutControllerCreator c;
};

TEST_F(LogoutControllerTest, test1) {
  EXPECT_CALL(*application, logoutUser(_)).Times(0);

  Request q;
  q.headers["type"] = "logout";
  Reply r = controller->handleRequest(q);
  ASSERT_EQ(r.headers["type"], "logout");
}

class RegistrationController : public ::testing::Test {
protected:
  void SetUp() override {
    controller = c.createController();
    application = make_shared<MockServerApplication>();
  }

  shared_ptr<server::Controller> controller;
  shared_ptr<MockServerApplication> application;

  server::RegistrationControllerCreator c;
};

TEST_F(RegistrationController, test1) {
  EXPECT_CALL(*application, registerUser(_)).Times(1);

  Request q;
  q.headers["type"] = "register";
  Reply r = controller->handleRequest(q);
  ASSERT_EQ(r.headers["type"], "register");
}

//int main(int argc, char **argv) {
//  ::testing::InitGoogleTest(&argc, argv);
//  return RUN_ALL_TESTS();
//}
