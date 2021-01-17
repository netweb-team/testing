#ifndef UNTITLED_EDITORLISTENER_H
#define UNTITLED_EDITORLISTENER_H

class EditorListener {
public:
    virtual void hearChangesFromServer() = 0;
    virtual void hearSubmitFromServer() = 0;
};

#endif //UNTITLED_EDITORLISTENER_H
