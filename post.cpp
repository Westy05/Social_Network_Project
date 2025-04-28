#include "post.h"

// modifiers

std::string Post::toString() {

}

// accessors

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


std::string Post::getAuthor() {}


bool Post::getIsPublic() {}