#ifndef POST_H
#define POST_H
#include <string>

class Post {
private:
    int messageId_; // id of post's message
    int ownerId_; // id of author/owner of post
    std::string message_; // contents of post's message
    int likes_; // number of likes on post
public:
    Post() : messageId_(-1), ownerId_(-1), message_(std::string()), likes_(0) {}
    Post(int messageId, int ownerId, std::string message, int likes) : messageId_(messageId), ownerId_(ownerId), message_(message), likes_(likes) {}

    // accessors

    // pre: post object is constructed
    // post: returns string that contains the message and number of likes
    virtual std::string toString();

    // pre: post object is constructed
    // post: returns post's message ID
    int getMessageId();
    
    // pre: post object is constructed
    // post: returns post's owner ID
    int getOwnerId();

    // pre: post object is constructed
    // post: returns post's message
    std::string getMessage();

    // pre: post object is constructed
    // post: returns post's number of likes
    int getLikes();

    // pre: post object is constructed
    // post: returns empty string
    virtual std::string getAuthor();

    // pre: post object is constructed
    // post: returns true
    virtual bool getIsPublic();
};

class IncomingPost : public Post {
private:
    std::string author_; // name of the author of the incoming post
    bool isPublic_; // true if incoming post is public, false if private
public:
    IncomingPost() : isPublic_(true), author_(std::string()) {}
    IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author) 
    : Post(messageId, ownerId, message, likes), isPublic_(isPublic), author_(author) {}

    // accessors

    // pre: post object is constructed
    // post: returns string containing author's name, indicates whether the post is public, and everything from Post::toString()
    std::string toString();

    // pre: post object is constructed
    // post: returns author of incoming post's name
    std::string getAuthor();

    // pre: post object is constructed
    // post: returns a boolean that indicates whether the incoming post is public or private
    bool getIsPublic();
};

#endif