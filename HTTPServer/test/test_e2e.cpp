#include "../include/client.h"
#include <ctime>
#include <cstdlib>

using namespace std;

string random_str(int len) 
{
    string result = "";
    int curr_len = rand() % len + 1;
    for (size_t i = 0; i < curr_len; ++i) 
    {
        int randomChar = rand() % (26 + 26 + 10);
        if (randomChar < 26)
            result += ('a' + randomChar);
        else if (randomChar < 26+26)
            result += ('A' + randomChar - 26);
        else
            result += ('0' + randomChar - 26 - 26);
    }
    return result;
}

void test(void)
{
    client::Client client("127.0.0.1", "5555");
    string test_username = random_str(10);
    string test_password = random_str(10);

    auto result = client.signup(test_username, test_password);

    if (result.first != client::ClientErrors::success)
        throw runtime_error("user signup");
    int editor_id = stoi(result.second);
    if (editor_id <= 0)
        throw runtime_error("user signup");

    string test_docname = random_str(30);

    result = client.create(editor_id, test_docname);

    if (result.first != client::ClientErrors::success)
        throw runtime_error("document create");
    int doc_id = stoi(result.second);
    if (doc_id <= 0)
        throw runtime_error("document create");

    string test_document_text = "";

    result = client.connect(editor_id, doc_id);

    if (result.first != client::ClientErrors::success || result.second != test_document_text)
        throw runtime_error("document connect");

    int cursor_pos = 0;
    string operation = "0,hello";

    result = client.update(editor_id, doc_id, cursor_pos, operation);

    if (result.first != client::ClientErrors::success)
        throw runtime_error("document edit");

    string result_text = "hello";

    result = client.getTextDocument(doc_id);

    if (result.first != client::ClientErrors::success || result.second != result_text)
        throw runtime_error("document get text");

    cursor_pos = 4;
    operation = "2,-1,2";

    result = client.update(editor_id, doc_id, cursor_pos, operation);

    if (result.first != client::ClientErrors::success)
        throw runtime_error("document edit");

    result_text = "helo";

    result = client.getTextDocument(doc_id);

    if (result.first != client::ClientErrors::success || result.second != result_text)
        throw runtime_error("document get text");

    result = client.disconnect(editor_id, doc_id);

    if (result.first != client::ClientErrors::success)
        throw runtime_error("document disconnect");

    result = client.logout(editor_id);

    if (result.first != client::ClientErrors::success)
        throw runtime_error("user logout");
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    if (argc != 2)
    {
        cout << "Usage: test.out <N> (N - number of test launch)" << endl;
        return -1;
    }
    int n = stoi(argv[1]);
    int success_count = 0;
    for (int i = 0; i < n; i++)
    {
        try 
        {
            test();
            success_count++;
        }
        catch (std::exception& e)
        {
            cout << e.what() << endl;
        }
    }
    cout << "Result: " << success_count << "/" << n << endl;
    cout << "Percentage of success: " << ((float) success_count / n * 100) << endl;
    return 0;
}