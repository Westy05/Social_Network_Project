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