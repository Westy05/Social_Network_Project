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

int Post::getPostPrivacy() { return postPrivacy_; }

// pre: post object is constructed
// post: returns empty string
std::string Post::getAuthor() { return ""; }

// ----IncomingPost----

// accessors

// pre: post object is constructed
// post: returns string containing author's name, indicates whether the post is public, and everything from Post::toString()
std::string IncomingPost::toString() {
    std::string result = author_ + " wrote";
    if (getPostPrivacy() == 0) result += " (private)"; // includes private keyword if post is not public
    else if (getPostPrivacy() == 2) result += " (semi-private)"; // includes semi-private keyword if post is semi-private
    result += ": " + Post::toString();

    return result;
}

// pre: post object is constructed
// post: returns author of incoming post's name
std::string IncomingPost::getAuthor() { return author_; }