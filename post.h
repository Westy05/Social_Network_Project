#ifndef POST_H
#define POST_H
#include <string>

class Post {
private:
    int messageId_; // id of post's message
    int ownerId_; // id of author/owner of post
    std::string message_; // contents of post's message
    int likes_; // number of likes on post
    int postPrivacy_; // privacy level of post (0 = private, 1 = public, and 2 = semi-private)
public:
    Post() : messageId_(0), ownerId_(0), message_(""), likes_(0), postPrivacy_(1) {}
    Post(int messageId, int ownerId, std::string message, int likes, int privacy = 1) : messageId_(messageId), ownerId_(ownerId), message_(message), likes_(likes), postPrivacy_(privacy) {}

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
    // post: returns post's privacy level (0 = private, 1 = public, and 2 = semi-private)
    int getPostPrivacy();

    // pre: post object is constructed
    // post: returns empty string
    virtual std::string getAuthor();
};

class IncomingPost : public Post {
private:
    std::string author_; // name of the author of the incoming post
public:
    IncomingPost() : author_(std::string()) {}
    IncomingPost(int messageId, int ownerId, std::string message, int likes, int privacy, std::string author) 
    : Post(messageId, ownerId, message, likes, privacy), author_(author) {}

    // accessors

    // pre: post object is constructed
    // post: returns string containing author's name, indicates whether the post is public, and everything from Post::toString()
    std::string toString();

    // pre: post object is constructed
    // post: returns author of incoming post's name
    std::string getAuthor();
};

#endif