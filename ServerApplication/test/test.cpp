#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "../include/ServerApplication.h"
#include "../../Utils/include/Document.h"
#include "../../Utils/include/Operation.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

bool operator ==(const Operation &op1, const Operation &op2) { return true; }
bool operator ==(const Document &doc1, const Document &doc2) { return true; }

class MockServerApplication: public BaseServerApplication {
public:
    MockServerApplication() = default;
    ~MockServerApplication() {}
    MOCK_METHOD2(createDocument, int(std::string, std::string));
    MOCK_METHOD3(updateDocument, std::vector<std::string>(std::string, int, std::vector<std::string>));
    MOCK_METHOD2(deleteDocument, void(std::string, int));
    MOCK_METHOD2(readDocument, std::string(std::string, int));
    MOCK_METHOD2(connectDocument, std::string(std::string, int));
    MOCK_METHOD1(loginUser, std::string(std::string));
    MOCK_METHOD1(registerUser, std::string(std::string));
    MOCK_METHOD1(logoutUser, std::string(std::string));
    MOCK_METHOD2(updateUser, std::string(std::string, std::string));
};

class MockEditorManager: public BaseEditorManager, public EditorManagerDelegate {
public:
    MockEditorManager() = default;
    MOCK_METHOD1(changeOperationRelativelyOthers, Operation(Operation));
    MOCK_METHOD1(addOperationToLog, void(Operation));
    MOCK_METHOD1(changeServerDocument, void(Document));
    MOCK_METHOD1(sendOperationToClient, void(Operation));
    MOCK_METHOD1(sendAnswerToOriginalClient, void(Operation));

    // Delegate Method
    MOCK_METHOD1(addOperationToQueue, void(Operation));

private:
};

class MockEditor: public BaseEditor, public EditorListener {
public:
    MockEditor() = default;
    MOCK_METHOD1(submitToServer, Operation(Operation));
    MOCK_METHOD0(makeNewOperation, Operation());
    MOCK_METHOD1(changeDocument, void(Operation));

    // Observers Methods
    MOCK_METHOD0(hearChangesFromServer, void());
    MOCK_METHOD0(hearSubmitFromServer, void());

private:
};

class MockSession: public BaseSession {
public:
    MockSession() = default;
    MOCK_METHOD1(manageOperation, void(Operation));
    MOCK_METHOD0(sendToServerBufOfhanger, std::vector<Operation>());

private:
};

TEST(ApplicationServer, readDocument) {
    MockServerApplication *mockServerApplication = new MockServerApplication();
    Document document;

    EXPECT_CALL(*mockServerApplication, readDocument(std::string(), 0)).Times(AtLeast(1));
    mockServerApplication->readDocument(std::string(), 0);
    delete mockServerApplication;
}

TEST(EditorManager, changeServerDocument) {
    MockEditorManager *mockEditorManager = new MockEditorManager;
    Document document;
    EXPECT_CALL(*mockEditorManager, changeServerDocument(document)).Times(AtLeast(1));
    mockEditorManager->changeServerDocument(document);
    delete mockEditorManager;
}

TEST(MockEditor, changeServerDocument) {
    MockEditor *mockEditor = new MockEditor;
    Document document;
    EXPECT_CALL(*mockEditor, hearChangesFromServer()).Times(AtLeast(1));
    mockEditor->hearChangesFromServer();
    delete mockEditor;
}

int main(int argc, char** argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}