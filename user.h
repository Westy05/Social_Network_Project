#ifndef USER_H
#define USER_H

#include <string>
#include <set>

class User {
private:
    // user fields
    int id_; // user's ID number
    std::string name_; // user's full name
    int year_; // user's birth year
    int zip_; // user's zip code
    std::set<int> friends_; // set of user's friends' IDs
public:
    User() : id_(0), name_(std::string()), year_(0), zip_(0), friends_(std::set<int>()) {}
    User(int id, std::string name, int year, int zip, std::set<int> friends) : id_(id), name_(name), year_(year), zip_(zip), friends_(friends) {}

    // ---modifiers---

    // pre: id must not be the user's own id or an id already present in friends_
    // post: inserts the id into friends_ if preconditions are met, otherwise does nothing
    void addFriend(int id);
    
    // pre: id is an id in friends_
    // post: deletes the id from friends_ if it exists, otherwise nothing happens
    void deleteFriend(int id);

    // ---accessors---

    // pre: id_ has a value
    // post: returns ID of user
    int getId();
    
    // pre: name_ has a string
    // post: returns full name of user
    std::string getName();
    
    // pre: year_ has a value
    // post: returns birth year of user
    int getYear();
    
    // pre: zip_ has a value
    // post: returns zip code of user
    int getZip();
    
    // pre: friends_ is constructed
    // post: returns a set of IDs of the user's friends
    std::set<int>& getFriends();
};

#endif