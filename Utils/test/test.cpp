//#include <gtest/gtest.h>
//#include <vector>
//#include "gmock/gmock.h"
//
//using ::testing::AtLeast;
//using ::testing::DoAll;
//using ::testing::Return;
//using ::testing::SetArgReferee;
//
//#include "Change.h"
//#include "Document.h"
//#include "../../ServerApplication/include/Editor.h"
//#include "../../ServerApplication/include/EditorManager.h"
//#include "../../ServerApplication/include/ServerApplication.h"
//#include "../../ServerApplication/include/Session.h"
//#include "Operation.h"
//#include "User.h"
//
//bool operator ==(const Operation &op1, const Operation &op2) { return true; }
//
//class MockDocument : public Document {
// public:
//  MOCK_METHOD1(updateText, bool(Operation));
//  MOCK_METHOD1(addOwner, void(int));
//};
//
//TEST(Document, testUpdateText) {
//  MockDocument mockDocument;
//  Operation operation;
//  Editor editor;
//  EditorManager editorManager;
//  EXPECT_CALL(mockDocument, updateText(operation)).Times(AtLeast(2));
//  editor.changeDocument(operation);
//  editorManager.changeServerDocument(mockDocument);
//}
//
//class MockUser : public User {
// public:
//  MOCK_METHOD2(addDocument, void(int, std::string));
//};
//
//TEST(DocAndUser, testAddDocAndUser) {
//  MockDocument mockDocument;
//  MockUser mockUser;
//  int idUser;
//  int idDocument;
//  std::string passDocument;
//  ServerApplication serverApplication;
//  EXPECT_CALL(mockDocument, addOwner(idUser)).Times(AtLeast(1));
//  EXPECT_CALL(mockUser, addDocument(idDocument, passDocument)).Times(AtLeast(1));
//  serverApplication.createDocument();
//}
//
//class MockBaseChange : public BaseChange {
// public:
//  MOCK_METHOD0(applyChanges, void());
//};
//
//TEST(BaseChange, applyChanges) {
//  MockBaseChange *mockBaseChange = new MockBaseChange;
//  Document document;
//  Operation operation;
//  std::shared_ptr<BaseChange> ptr(mockBaseChange);
//  operation.addChange(ptr);
//  EXPECT_CALL(*mockBaseChange, applyChanges()).Times(AtLeast(1));
//  document.updateText(operation);
//}
//
//class MockOperation : public Operation {
// public:
//  MOCK_METHOD0(getRevision, int());
//  MOCK_METHOD0(getLengthBeforeOperation, int());
//  MOCK_METHOD0(getLengthAfterOperation, int());
//  MOCK_METHOD0(getIdEditor, int());
//  MOCK_METHOD0(getChanges, std::vector<std::shared_ptr<BaseChange>>());
//};
//
//TEST(Operation, getMethods) {
//  MockOperation mockOperation;
//  EXPECT_CALL(mockOperation, getRevision()).Times(AtLeast(2));
//  EXPECT_CALL(mockOperation, getLengthBeforeOperation()).Times(AtLeast(2));
//  EXPECT_CALL(mockOperation, getLengthAfterOperation()).Times(AtLeast(2));
//  EXPECT_CALL(mockOperation, getIdEditor()).Times(AtLeast(2));
//  EXPECT_CALL(mockOperation, getChanges()).Times(AtLeast(2));
//  Session session;
//  session.manageOperation(mockOperation);
//  EditorManager editorManager;
//  editorManager.changeOperationRelativelyOthers(mockOperation);
//}

#include "DocumentBuilder.h"
#include "OperationBuilder.h"
#include "UserBuilder.h"

int main(int argc, char** argv) {
  //::testing::InitGoogleMock(&argc, argv);
  //return RUN_ALL_TESTS();
  
}
