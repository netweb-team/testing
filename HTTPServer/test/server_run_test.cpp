#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <memory>

#include "server/Server.h"

using namespace std;
using namespace http;

class ServerTest : public ::testing::Test {
protected:
  void SetUp() override {
    mainServer = make_shared<server::Server>("localhost", 5555);
  }
  void TearDown() override {
  }

  shared_ptr<server::Server> mainServer;
};

TEST_F(ServerTest, testRun) {
//  mainServer->run();
}
