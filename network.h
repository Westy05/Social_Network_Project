#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
#include <vector>

class Network {
private:
    std::vector<User*> users_; // vector of dynamically allocated users
    int numOfPosts_; // total number of posts in network, useful for figuring out the next message id

    // pre: name is a valid string
    // post: returns a trimmed version of the name
    // note: primarily for getting the name from txt files
    std::string trimName(const std::string &name);

    // pre: source is an actual user id in users_ and group and visited exist beyond the scope of the function with visited being the size of users_
    // post: returns nothing. only modifies 2nd and 3rd paramaters where the group paramater should be somewhat populated if it finds anything.
    void groupsHelper(int source, std::vector<int>& group, std::vector<bool>& visited);
public:
    Network() : users_(std::vector<User*>()) {}

    // ---modifiers---
    
    // pre: user parameter has all fields filled out
    // post: adds the new user at the end of the vector of users
    void addUser(User* newUser);
    
    // pre: both strings are formatted "FirstName LastName" and are both already in users_
    // post: returns -1 if either of the names is not in users_ or returns 0 if the operation was successful
    int addConnection(std::string s1, std::string s2);
    
    // pre: both strings are formatted "FirstName LastName", both are already in users_, and both already have a connection
    // post: returns -1 if either of the names is not in users_ or returns 0 if the operation was successful
    int deleteConnection(std::string s1, std::string s2);
    
    // pre: fname (the file name of the txt file) must be present in the same directory as the program
    // post: returns 0 if the file was successfully read into the network object, returns -1 if it fails at any point
    int readUsers(char* fname);
    
    // pre: name must be a valid file name to write to
    // post: returns 0 if the file was successfully written to, returns -1 if it fails at any point
    int writeUsers(char* fname);

    // pre: paramaters must be valid and ownerId must be an already existing user ID
    // post: adds a new post entry in the user's messages_ vector
    void addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, int privacyLevel);

    // pre: fname (the file name of the txt file) must be present in the same directory as the program and have correct format
    // post: returns 0 if the file was successfully read into the network object, returns -1 if it fails at any point
    int readPosts(char* fname);

    // pre: fname must be a valid file name to write to
    // post: returns 0 if the file was successfully written to, returns -1 if it fails at any point; supposed to save all posts in network object
    int writePosts(char* fname);
    
    // ---accessors---
    
    // pre: name must be a name belonging to a user object in users_
    // post: returns the user's id if successful or -1 if not
    int getId(std::string name);
    
    // pre: users_ vector is constructed
    // post: returns number of users in network object's users_ vector
    int numUsers();
    
    // pre: id must be within users_
    // post: returns a pointer to the user with the corresponding id, otherwise returns nullptr
    User* getUser(int id);

    // pre: users_ has both users and they are connected to some degree
    // post: returns a vector of the shortest path starting from and ending to
    std::vector<int> shortestPath(int from, int to);

    // pre: users_ has a user with an id == from and has at least one user that has distance amount of edges between them
    // post: changes the to paramater to match a user with the same distance and returns a vector of the shortest path starting at from and ending at to
    std::vector<int> distanceUser(int from, int& to, int distance);

    // pre: a user in users_ has the id matching who
    // post: returns a vector of user ids who have the highest amount of friends in common with user who
    // and sets score paramater to these users' score
    std::vector<int> suggestFriends(int who, int& score);

    // pre: network object has been properly initialized
    // post: returns a vector of vectors of integers with each vector within it representing a connected component
    // and each of these components contain the user ids of users connected to each other.
    std::vector<std::vector<int>> groups();

    // pre: ownerId is a valid user ID (in the range of users_)
    // post: returns a string containing the most recent [howMany] posts (or all if howMany >= the number of posts from user) of the specified user
    std::string getPostsString(int ownerId, int howMany, int privacyLevel);

    // pre: who is a valid user ID
    // post: returns a sorted vector of ALL friends of friends
    std::vector<int> getFriendsOfFriends(int who);

    int getAccessLevel(int user1, int user2);
};

#endif