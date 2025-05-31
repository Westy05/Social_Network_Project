#ifndef USER_H
#define USER_H

#include <string>
#include <set>
#include <vector>
#include "post.h"

class User {
private:
    // user fields
    int id_; // user's ID number
    std::string name_; // user's full name
    int year_; // user's birth year
    int zip_; // user's zip code
    std::set<int> friends_; // set of user's friends' IDs
    std::vector<Post*> messages_; // vector of posts from the user
    int friendListPrivacy_; // privacy level of user (0 = private, 1 = public, and 2 = semi-private)
public:
    User() : id_(0), name_(std::string()), year_(0), zip_(0), friends_(std::set<int>()), messages_(std::vector<Post*>()), friendListPrivacy_(1) {}
    User(int id, std::string name, int year, int zip, std::set<int> friends, int privacy = 1) : id_(id), name_(name), year_(year), zip_(zip), friends_(friends), messages_(std::vector<Post*>()), friendListPrivacy_(privacy) {}

    // ---modifiers---

    // pre: id must not be the user's own id or an id already present in friends_
    // post: inserts the id into friends_ if preconditions are met, otherwise does nothing
    void addFriend(int id);
    
    // pre: id is an id in friends_
    // post: deletes the id from friends_ if it exists, otherwise nothing happens
    void deleteFriend(int id);

    // pre: userPost actually points to a Post or IncomingPost object
    // post: adds the new Post to the messages_ vector
    void addPost(Post* userPost);

    // pre: object is constructed
    // post: sets the privacy level of the user's friend list to newPrivacy if it is between 1 and 3, otherwise does nothing
    void setFriendListPrivacy(int newPrivacy);

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

    // pre: messages_ is constructed
    // post: returns a vector of Post pointers which are all posts on the User's "page"
    std::vector<Post*> getPosts();

    // pre: both paramaters are valid and messages_ is constructed
    // post: returns a (potentially large) string of all the most recent posts of the User or all posts if howMany meets or exceeds size of messages_
    std::string getPostsString(int howMany, int privacyLevel);

    // pre: friendListPrivacy_ has a value
    // post: returns the privacy level of the user's friend list
    int getFriendListPrivacy();
};

#endif