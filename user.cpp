#include "user.h"

// ---modifiers---

// pre: id must not be the user's own id or an id already present in friends_
// post: inserts the id into friends_ if preconditions are met, otherwise does nothing
void User::addFriend(int id) {
    if (id == id_) return;
    friends_.insert(id);
}

// pre: id is an id in friends_
// post: deletes the id from friends_ if it exists, otherwise nothing happens
void User::deleteFriend(int id) { friends_.erase(id); }

// pre: userPost actually points to a Post or IncomingPost object
// post: adds the new Post to the messages_ vector
void User::addPost(Post* userPost) { messages_.push_back(userPost); }

// ---accessors---

// pre: id_ has a value
// post: returns ID of user
int User::getId() { return id_; }

 // Start Generation Here
// pre: name_ has a string
// post: returns full name of user
std::string User::getName() { return name_; }

// pre: year_ has a value
// post: returns birth year of user
int User::getYear() { return year_; }

// pre: zip_ has a value
// post: returns zip code of user
int User::getZip() { return zip_; }

// pre: friends_ is constructed
// post: returns a set of IDs of the user's friends
std::set<int>& User::getFriends() { return friends_; }

// pre: messages_ is constructed
// post: returns a vector of Post pointers which are all posts on the User's "page"
std::vector<Post*> User::getPosts() { return messages_; }

// pre: both paramaters are valid and messages_ is constructed
// post: returns a (potentially large) string of all the most recent posts of the User or all posts if howMany meets or exceeds size of messages_
std::string User::getPostsString(int howMany, bool showOnlyPublic) {
    std::string postsString;
    
    // effectively the range is from n-1 to n-howMany (or 0 if howMany exceeds size) where n is the size of messages_
    int limit = (howMany >= messages_.size() ? 0 : messages_.size()-howMany);

    // for loop iterates through messages_ in reverse to easily grab most recent posts
    for (int index = messages_.size()-1; index >= limit; index--) {
        Post* currentPost = messages_[index];
        
        if (showOnlyPublic) { // checks if it should bother checking whether posts are public or not
            if (currentPost->getIsPublic()) postsString += currentPost->toString() + "\n\n";
        } else {
            postsString += currentPost->toString() + "\n\n";
        }
    }

    return postsString;
}