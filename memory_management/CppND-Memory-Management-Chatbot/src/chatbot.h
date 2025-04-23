#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <string>
#include <iostream>
#include <vector>
#include <memory>


class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot
{
private:
    // data handles (owned)
    wxBitmap *_image; // avatar image

    // data handles (not owned)
    GraphNode *_currentNode;
    GraphNode *_rootNode;
    ChatLogic *_chatLogic;

    // proprietary functions
    int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
    // constructors / destructors
    ChatBot();                     // constructor WITHOUT memory allocation
    ChatBot(std::string filename); // constructor WITH memory allocation
    ~ChatBot();

    ////  CODE
    ////

    //Copy Constructor; initiliaze -> ChatBot chatbot(ChatBot other);
    ChatBot(const ChatBot& other);

    // Copy Assigment; initiliaze -> ChatBot chatbot = other;
    ChatBot& operator=(const ChatBot& other);
    

    //Move Constructor; initiliaze -> ChatBot chatbot(std::move(other)) ;
    ChatBot(ChatBot&& other);

    //Move Assignment; initiliaze -> ChatBot chatbot = std::move(other);
    ChatBot& operator=(ChatBot&& other);


    ////
    //// EOF  CODE

    // getters / setters
    void SetCurrentNode(GraphNode *node);
    void SetRootNode(GraphNode *rootNode) { _rootNode = rootNode; }
    void SetChatLogicHandle(ChatLogic *chatLogic) { _chatLogic = chatLogic; }
    ChatLogic* GetChatLogicHandle() { return _chatLogic; }
    wxBitmap *GetImageHandle() { return _image; }

    // communication
    void ReceiveMessageFromUser(std::string message);
};

#endif /* CHATBOT_H_ */
