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

// pre: object is constructed
// post: sets the privacy level of the user's friend list to newPrivacy if it is between 1 and 3, otherwise does nothing
void User::setFriendListPrivacy(int newPrivacy) {
    if (newPrivacy >= 1 && newPrivacy <= 3) {
        friendListPrivacy_ = newPrivacy;
    }
}

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
std::string User::getPostsString(int howMany, int privacyLevel) {
    std::string postsString;
    
    // effectively the range is from n-1 to n-howMany (or 0 if howMany exceeds size) where n is the size of messages_
    int limit = (howMany >= messages_.size() ? 0 : messages_.size()-howMany);

    // for loop iterates through messages_ in reverse to easily grab most recent posts
    // this loop is now a work in progress to implement privacy levels, will need to check each post's privacy level which hasn't been implemented yet
    for (int index = messages_.size()-1; index >= limit; index--) {
        Post* currentPost = messages_[index];
        
        if (privacyLevel == 0) { // checks if it should only show public posts
            if (currentPost->getIsPublic()) postsString += currentPost->toString() + "\n\n";
        } else if (privacyLevel == 2) { // checks if it should only show semi-private posts

        } else { // shows all posts
            postsString += currentPost->toString() + "\n\n";
        }
    }

    return postsString;
}

// pre: friendListPrivacy_ has a value
// post: returns the privacy level of the user's friend list
int User::getFriendListPrivacy() {
    return friendListPrivacy_;
}