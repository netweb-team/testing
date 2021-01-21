#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "../include/DBController.h"
#include "../include/DocumentRepository.h"
#include "../include/UserRepository.h"
#include "../../ServerApplication/include/DocumentParBuilder.h"
#include "../../ServerApplication/include/UserParBuilder.h"
#include "../../Utils/include/DocumentBuilder.h"
#include "../../Utils/include/UserBuilder.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;

class TestCreateDocument : public ::testing::Test
{
protected: 
    void SetUp()
    {
        docMother = new DocumentMother;
        auto db = make_shared<DBController>();
        docRepo = new DocumentRepository(db);
    }

    void TearDown() 
    {
        delete docMother;
        delete docRepo;
    }

    DocumentMother *docMother;
    DocumentRepository *docRepo;
};

TEST_F(TestCreateDocument, empty_doc_name)
{
    DocumentBuilder *dbuilder = docMother->three();
    Document *doc = dbuilder->setId(0)->build();

    docRepo->createDoc(*doc);

    EXPECT_NE(0, doc->getId());
    delete doc;
    delete dbuilder;
}

TEST_F(TestCreateDocument, good_doc)
{
    DocumentBuilder *dbuilder = docMother->two();
    Document *doc = dbuilder->setId(0)->build();

    docRepo->createDoc(*doc);

    EXPECT_NE(0, doc->getId());
    delete doc;
    delete dbuilder;
}

TEST_F(TestCreateDocument, already_exist_doc)
{
    DocumentBuilder *dbuilder = docMother->one();
    Document *doc = dbuilder->build();

    docRepo->createDoc(*doc);

    EXPECT_THROW(docRepo->createDoc(*doc), runtime_error);
    delete doc;
    delete dbuilder;
}

class TestDocumentRepo : public ::testing::Test
{
protected:
    void SetUp()
    {
        auto db = make_shared<DBController>();
        docRepo = new DocumentRepository(db);
        DocumentMother docMother;
        dbuilder = docMother.one();
    }
    void TearDown()
    {
        delete docRepo;
        delete dbuilder;
    }

    DocumentBuilder *dbuilder;
    DocumentRepository *docRepo;
};

bool cmpDocument(Document& l, Document& r)
{
    cout << l.getId() << " " << r.getId() << endl;
    cout << l.getName() << endl << r.getName() << endl;
    cout << l.getText() << endl << r.getText() << endl;
    if (l.getId() == r.getId() && l.getName() == r.getName()
        && l.getText() == r.getText())
        return true;
    return false;
}

TEST_F(TestDocumentRepo, get_not_exist_document)
{
    int doc_id = 0;

    EXPECT_THROW(docRepo->getById(doc_id), runtime_error);
}

TEST_F(TestDocumentRepo, get_exist_document)
{
    Document *doc = dbuilder->setName("get_doc")->build();
    auto expected = make_shared<Document>(doc->getId(), doc->getName(), doc->getText());
    docRepo->createDoc(*expected);

    auto result = docRepo->getById(expected->getId());

    EXPECT_TRUE(cmpDocument(*expected, *result));
    delete doc;
}

TEST_F(TestDocumentRepo, update_not_exist_document)
{
    Document *not_exist = dbuilder->setName("update_doc")->build();

    EXPECT_THROW(docRepo->changeDoc(*not_exist), runtime_error);
    delete not_exist;
}

TEST_F(TestDocumentRepo, update_exist_document)
{
    Document *doc = dbuilder->setName("update_doc")->build();
    docRepo->createDoc(*doc);

    EXPECT_NO_THROW(docRepo->changeDoc(*doc));
    delete doc;
}

TEST_F(TestDocumentRepo, delete_not_exist_document)
{
    Document *not_exist = dbuilder->setName("delete_doc")->build();

    EXPECT_THROW(docRepo->deleteDoc(*not_exist), runtime_error);
    delete not_exist;
}

TEST_F(TestDocumentRepo, delete_exist_document)
{
    Document *doc = dbuilder->setName("delete_doc")->build();
    docRepo->createDoc(*doc);

    EXPECT_NO_THROW(docRepo->deleteDoc(*doc));
    delete doc;
}

class TestUserDocs : public ::testing::Test
{
protected:
    void SetUp()
    {
        auto db = make_shared<DBController>();
        docRepo = new DocumentRepository(db);
        userRepo = new UserRepository(db);

        DocumentMother docMother;
        dbuilder = docMother.one();
        UserMother userMother;
        ubuilder = userMother.two();
    }
    void TearDown()
    {
        delete docRepo;
        delete userRepo;
        delete dbuilder;
        delete ubuilder;
    }

    DocumentRepository *docRepo;
    UserRepository *userRepo;
    DocumentBuilder *dbuilder;
    UserBuilder *ubuilder;
};

bool cmpDocs(vector<shared_ptr<Document>>& l, vector<shared_ptr<Document>>& r)
{
    if (l.size() != r.size())
        return false;

    for (int i = 0; i < l.size(); i++)
    {
        if (!cmpDocument(*l[i], *r[i]))
            return false;
    }
    return true;
}

TEST_F(TestUserDocs, get_not_exist_user_docs)
{
    User user;

    EXPECT_THROW(docRepo->getByUser(user), runtime_error);
}

TEST_F(TestUserDocs, get_exist_user_docs)
{
    User *user = ubuilder->setName("admin2")->build();
    userRepo->createUser(*user);
    Document *doc = dbuilder->setName("old")->build();
    docRepo->createDoc(*doc);
    user->addDocument(doc->getId());
    docRepo->addUser(*user, *doc);
    vector<shared_ptr<Document>> expected;
    expected.push_back(make_shared<Document>());
    expected.back()->setId(doc->getId());
    expected.back()->setName(doc->getName());

    auto result = docRepo->getByUser(*user);

    EXPECT_TRUE(cmpDocs(expected, result));
    delete user;
    delete doc;
}

TEST_F(TestUserDocs, add_not_exist_doc)
{
    User *user = ubuilder->setName("user1")->build();
    userRepo->createUser(*user);
    Document *doc = dbuilder->setId(0)->build();

    EXPECT_THROW(docRepo->addUser(*user, *doc), runtime_error);
    delete user;
    delete doc;
}

TEST_F(TestUserDocs, add_not_exist_user)
{
    User *user = ubuilder->setId(0)->build();
    Document *doc = dbuilder->setName("existed")->build();
    docRepo->createDoc(*doc);

    EXPECT_THROW(docRepo->addUser(*user, *doc), runtime_error);
    delete user;
    delete doc;
}

TEST_F(TestUserDocs, add_good_user_doc)
{
    User *user = ubuilder->setName("user2")->build();
    userRepo->createUser(*user);
    Document *doc = dbuilder->setName("good_doc")->build();
    docRepo->createDoc(*doc);

    EXPECT_NO_THROW(docRepo->addUser(*user, *doc));
    delete user;
    delete doc;
}

class TestCreateUser : public ::testing::Test
{
protected:
    void SetUp()
    {
        userMother = new UserMother;
        auto db = make_shared<DBController>();
        userRepo  = new UserRepository(db);
    }
    void TearDown()
    {
        delete userMother;
        delete userRepo;
    }

    UserMother *userMother;
    UserRepository *userRepo;
};

TEST_F(TestCreateUser, empty_user)
{
    UserBuilder *ubuilder = userMother->three();
    User *user = ubuilder->setId(0)->build();

    userRepo->createUser(*user);

    EXPECT_NE(0, user->getId());
    delete user;
    delete ubuilder;
}

TEST_F(TestCreateUser, good_user)
{
    UserBuilder *ubuilder = userMother->two();
    User *user = ubuilder->setId(0)->build();

    userRepo->createUser(*user);

    EXPECT_NE(0, user->getId());
    delete user;
    delete ubuilder;
}

TEST_F(TestCreateUser, already_exist_user)
{
    UserBuilder *ubuilder = userMother->one();
    User *user = ubuilder->setId(0)->build();

    userRepo->createUser(*user);

    EXPECT_THROW(userRepo->createUser(*user), runtime_error);
    delete user;
    delete ubuilder;
}

class TestUserRepo : public ::testing::Test
{
protected:
    void SetUp()
    {
        auto db = make_shared<DBController>();
        userRepo = new UserRepository(db);
        UserMother userMother;
        ubuilder = userMother.three();
    }
    void TearDown()
    {
        delete userRepo;
        delete ubuilder;
    }

    UserBuilder *ubuilder;
    UserRepository *userRepo;
};

bool cmpUser(User& l, User& r)
{
    if (l.getId() == r.getId() && l.getName() == r.getName()
        && l.getPassword() == r.getPassword())
        return true;
    return false;
}

TEST_F(TestUserRepo, get_not_exist_user)
{
    int user_id = 0;

    EXPECT_THROW(userRepo->getById(user_id), runtime_error);
}

TEST_F(TestUserRepo, get_exist_user)
{
    User *user = ubuilder->setName("get_user")->build();
    auto expected = make_shared<User>();
    expected->setId(user->getId());
    expected->setName(user->getName());
    expected->setPassword(user->getPassword());
    expected->setIsLogin(user->getIsLogin());
    userRepo->createUser(*expected);

    auto result = userRepo->getById(expected->getId());

    EXPECT_TRUE(cmpUser(*expected, *result));
    delete user;
}

TEST_F(TestUserRepo, update_not_exist_user)
{
    User *not_exist = ubuilder->setName("update_user")->build();

    EXPECT_THROW(userRepo->updateUser(*not_exist), runtime_error);
    delete not_exist;
}

TEST_F(TestUserRepo, update_exist_user)
{
    User *user = ubuilder->setName("update_user")->build();
    userRepo->createUser(*user);

    EXPECT_NO_THROW(userRepo->updateUser(*user));
    delete user;
}

TEST_F(TestUserRepo, check_not_exist_user)
{
    User *user = ubuilder->setName("not_exist_user")->build();

    EXPECT_THROW(userRepo->checkUser(*user), runtime_error);
    delete user;
}

TEST_F(TestUserRepo, check_exist_user)
{
    User *user = ubuilder->setName("exist_user")->setPassword("pass")->build();
    userRepo->createUser(*user);

    EXPECT_NO_THROW(userRepo->checkUser(*user));
    delete user;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}