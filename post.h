#ifndef POST_H
#define POST_H
#include <string>

class Post {
private:
    int messageId_;
    int ownerId_;
    std::string message_;
    int likes_;
public:
    Post() : messageId_(-1), ownerId_(-1), message_(std::string()), likes_(0) {}
    Post(int messageId, int ownerId, std::string message, int likes) : messageId_(messageId), ownerId_(ownerId), message_(message), likes_(likes) {}

    // modifiers

    std::string toString();

    // accessors

    int getMessageId();
    int getOwnerId();
    std::string getMessage();
    int getLikes();
    std::string getAuthor();
    bool getIsPublic();
};



#endif