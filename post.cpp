#include "post.h"

// ----Post----

// accessors

// pre: post object is constructed
// post: returns string that contains the message and number of likes
std::string Post::toString() {
    return (message_ + " Liked by " + std::to_string(likes_) + " people");
}

// pre: post object is constructed
// post: returns post's message ID
int Post::getMessageId() { return messageId_; }


// pre: post object is constructed
// post: returns post's owner ID
int Post::getOwnerId() { return ownerId_; }


// pre: post object is constructed
// post: returns post's message
std::string Post::getMessage() { return message_; }


// pre: post object is constructed
// post: returns post's number of likes
int Post::getLikes() { return likes_; }


// pre: post object is constructed
// post: returns empty string
std::string Post::getAuthor() { return ""; }


// pre: post object is constructed
// post: returns true
bool Post::getIsPublic() { return true; }


// ----IncomingPost----

// accessors

// pre: post object is constructed
// post: returns string containing author's name, indicates whether the post is public, and everything from Post::toString()
std::string IncomingPost::toString() {
    std::string result = author_ + " wrote";
    if (!isPublic_) result += " (private)";
    result += ": " + Post::toString();

    return result;
}

// pre: post object is constructed
// post: returns author of incoming post's name
std::string IncomingPost::getAuthor() { return author_; }

// pre: post object is constructed
// post: returns a boolean that indicates whether the incoming post is public or private
bool IncomingPost::getIsPublic() { return isPublic_; }