#include "network.h"
#include <sstream>
#include <fstream>
#include <queue>
#include <utility>
#include <stack>
#include <algorithm>
#include <cctype>

// pre: both paramaters are valid
// post: returns true if p1's messageId is less than p2's, false otherwise
bool postComp(Post* p1, Post* p2) {
    return p1->getMessageId() < p2->getMessageId();
}

// ---private helpers---

// pre: name is a valid string
// post: returns a trimmed version of the string
// note: primarily for getting the name from txt files
std::string Network::trimName(const std::string &name) {
    std::stringstream ss(name);
    std::string word;
    std::string result;
    bool first = true;
    while (ss >> word) {
        if (!first) {
            result += " ";
        }
        result += word;
        first = false;
    }
    return result;
}

// pre: source is an actual user id in users_ and group and visited exist beyond the scope of the function with visited being the size of users_
// post: returns nothing. only modifies 2nd and 3rd paramaters where the group paramater should be somewhat populated.
void Network::groupsHelper(int source, std::vector<int>& group, std::vector<bool>& visited) {
    for (int i : users_[source]->getFriends()) {
        if (!visited[i]) {
            visited[i] = true;
            group.push_back(i);
            groupsHelper(i, group, visited); // recursive call to go further into the depth of the network
        }
    }
}

// ---modifiers---

// pre: user parameter has all fields filled out
// post: adds the new user at the end of the vector of users
void Network::addUser(User* newUser) {
    users_.push_back(newUser);
}

// pre: both strings are formatted "FirstName LastName" and are both already in users_
// post: returns -1 if either of the names is not in users_ or returns 0 if the operation was successful
int Network::addConnection(std::string s1, std::string s2) {
    User* user1 = nullptr;
    User* user2 = nullptr;

    // iterates through vector and tries to find corresponding users
    for (User* user : users_) {
        if (user->getName() == s1) {
            user1 = user;
        } else if (user->getName() == s2) {
            user2 = user;
        }
    }

    // checks whether both users were found
    if (user1 == nullptr || user2 == nullptr) {
        return -1;
    } else { // both corresponding user objects add each other as friends
        user1->addFriend(user2->getId());
        user2->addFriend(user1->getId());

        return 0;
    }
}

// pre: both strings are formatted "FirstName LastName", both are already in users_, and both already have a connection
// post: returns -1 if either of the names is not in users_ or returns 0 if the operation was successful
int Network::deleteConnection(std::string s1, std::string s2) {
    User* user1 = nullptr;
    User* user2 = nullptr;

    // iterates through vector and tries to find corresponding users
    for (User* user : users_) {
        if (user->getName() == s1) {
            user1 = user;
        } else if (user->getName() == s2) {
            user2 = user;
        }
    }

    // checks whether both users were found
    if (user1 == nullptr || user2 == nullptr) {
        return -1;
    } else { // both corresponding user objects remove each other from their friends lists
        user1->deleteFriend(user2->getId());
        user2->deleteFriend(user1->getId());

        return 0;
    }
}

// pre: fname (the file name of the txt file) must be present in the same directory as the program
// post: returns 0 if the file was successfully read into the network object, returns -1 if it fails at any point
int Network::readUsers(char* fname) {
    std::string myLine;
    std::ifstream myFile(fname);
    
    if (!myFile.is_open()) return -1;

    // gets the first line which should be the total num of users
    std::getline(myFile, myLine);
    int totalUsers = std::stoi(myLine);
    users_.reserve(totalUsers); // resizes vector's capacity so it allocates the necessary space all at once
    
    // each if statement below calls the getline function and will return -1 if it fails
    for (int i = 0; i < totalUsers; i++) {
        if (!std::getline(myFile, myLine)) return -1; // read user's ID
        int id = std::stoi(myLine);

        if (!std::getline(myFile, myLine)) return -1; // read user's name (or privacy level depending on version)
        std::string secondElement = trimName(myLine); // trims whitespaces off string
        
        std::string fullName;
        int privacyLvl = 1; // public by default

        // checks whether string is actually an integer for privacy level
        if (secondElement == "0" || secondElement == "1" || secondElement == "2") {
            privacyLvl = std::stoi(secondElement); // privacy is set

            if (!std::getline(myFile, myLine)) return -1; // reads user's name now, shifts all following readings by a line
            fullName = trimName(myLine);
        } else { // otherwise it is treated like the old format
            fullName = secondElement;
        }

        if (!std::getline(myFile, myLine)) return -1; // read user's birth year
        int birthYear = std::stoi(myLine);

        if (!std::getline(myFile, myLine)) return -1; // read user's zip code
        int zipCode = std::stoi(myLine);

        if (!std::getline(myFile, myLine)) return -1; // read user's list of friends' ids
        std::set<int> friends;
        std::stringstream friendStream(myLine); // creates string stream to iterate through each id
        int friendId;
        while (friendStream >> friendId) { // inserts each unique friend id into the set
            friends.insert(friendId);
        }

        User* newUser = new User(id, fullName, birthYear, zipCode, friends, privacyLvl); // done for readability

        addUser(newUser);
    }

    myFile.close();
    return 0; // function successful!
}

// pre: name must be a valid file name to write to
// post: returns 0 if the file was successfully written to, returns -1 if it fails at any point; supposed to save all users in network object
int Network::writeUsers(char* fname) {
    std::ofstream saveFile(fname);

    if (!saveFile.is_open()) return -1;

    // writes the total number of users
    saveFile << users_.size() << std::endl;

    // iterates over each user and writes their fields into the file with proper formatting
    for (User* user : users_) {
        saveFile << user->getId() << std::endl;
        saveFile << "\t" << user->getFriendListPrivacy() << std::endl;
        saveFile << "\t" << user->getName() << std::endl;
        saveFile << "\t" << user->getYear() << std::endl;
        saveFile << "\t" << user->getZip() << std::endl;
        std::set<int> friends = user->getFriends();
        saveFile << "\t";
        for (int friendId : friends) {
            saveFile << friendId << " ";
        }
        saveFile << std::endl;
    }

    saveFile.close();
    return 0;
}

// pre: paramaters must be valid and ownerId must be an already existing user ID
// post: adds a new post entry in the user's messages_ vector
void Network::addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, int privacyLevel) {    
    int messageId = numOfPosts_;
    if (isIncoming) { // determines whether to add new post as IncomingPost or Post
        users_[ownerId]->addPost(new IncomingPost(messageId, ownerId, message, likes, privacyLevel, authorName));
    } else {
        users_[ownerId]->addPost(new Post(messageId, ownerId, message, likes, privacyLevel));
    }
    numOfPosts_++;
}

// pre: fname (the file name of the txt file) must be present in the same directory as the program and have correct format
// post: returns 0 if the file was successfully read into the network object, returns -1 if it fails at any point
int Network::readPosts(char* fname) {
    std::string myLine;
    std::ifstream myFile(fname);
    
    if (!myFile.is_open()) return -1;

    // gets the first line which should be the total num of posts
    std::getline(myFile, myLine);
    int totalPosts = std::stoi(myLine);
    
    // each if statement below calls the getline function and will return -1 if it fails
    for (int i = 0; i < totalPosts; i++) {
        if (!std::getline(myFile, myLine)) return -1; // read post's ID
        int messageId = std::stoi(myLine);

        if (!std::getline(myFile, myLine)) return -1; // read post's message
        std::string messageContent = trimName(myLine);

        if (!std::getline(myFile, myLine)) return -1; // read post's owner ID (user's ID)
        int ownerId = std::stoi(myLine);

        if (!std::getline(myFile, myLine)) return -1; // read post's number of likes
        int likes = std::stoi(myLine);

        if (!std::getline(myFile, myLine)) return -1; // read incoming post's privacy
        std::string postPrivacyLvl = trimName(myLine);

        if (!std::getline(myFile, myLine)) return -1; // read incoming post's author
        std::string authorName = trimName(myLine);

        // initializes privacyLvl as 1 by default and changes to a valid value depending the string
        int privacyLvl = 1;
        if (postPrivacyLvl == "private") {
            privacyLvl = 0;
        } else if (postPrivacyLvl == "public") {
            privacyLvl = 1;
        } else if (postPrivacyLvl == "semi-private") {
            privacyLvl = 2;
        }


        addPost(ownerId, messageContent, likes, !authorName.empty(), authorName, privacyLvl);
    }

    myFile.close();
    return 0;
}

// pre: fname must be a valid file name to write to
// post: returns 0 if the file was successfully written to, returns -1 if it fails at any point; supposed to save all posts in network object
int Network::writePosts(char* fname) {
    std::ofstream saveFile(fname);

    if (!saveFile.is_open()) return -1;

    // creates vector to store all posts in the network and uses for loop to insert all posts found
    std::vector<Post*> allPosts;
    for (User* user : users_) {
        std::vector<Post*> currentPosts = user->getPosts();
        allPosts.insert(allPosts.end(), currentPosts.begin(), currentPosts.end());
    }

    // sorts vector so that it's ordered by messageId in ascending order (smallest to largest)
    std::sort(allPosts.begin(), allPosts.end(), postComp);

    // writes the total number of posts
    saveFile << allPosts.size() << std::endl;

    // iterates over each post and writes their fields into the file with proper formatting
    for (Post* post : allPosts) {
        saveFile << post->getMessageId() << std::endl;
        saveFile << "\t" << post->getMessage() << std::endl;
        saveFile << "\t" << post->getOwnerId() << std::endl;
        saveFile << "\t" << post->getLikes() << std::endl;

        // checks if the author field is empty or not
        if (!post->getAuthor().empty()) {
            
            // if statements that figure out which privacy to save in file
            if (post->getPostPrivacy() == 0) {
                saveFile << "\t" << "private" << std::endl;
            } else if (post->getPostPrivacy() == 1) {
                saveFile << "\t" << "public" << std::endl;
            } else if (post->getPostPrivacy() == 2) {
                saveFile << "\t" << "semi-private" << std::endl;
            }
            
            saveFile << "\t" << post->getAuthor() << std::endl;
        } else {
            saveFile << "\t" << std::endl;
            saveFile << "\t" << std::endl;
        }
    }

    saveFile.close();
    return 0;
}

// ---accessors---

// pre: name must be a name belonging to a user object in users_
// post: returns the user's id if successful or -1 if not
int Network::getId(std::string name) {
    for (User* user : users_) {
        if (user->getName() == name) {
            return user->getId();
        }
    }

    return -1; // only returns this if cannot be found in linear search
}

// pre: users_ vector is constructed
// post: returns number of users in network object's users_ vector
int Network::numUsers() { return users_.size(); }

// pre: id must be within users_
// post: returns a pointer to the user with the corresponding id, otherwise returns nullptr
User* Network::getUser(int id) {
    for (User* user : users_) {
        if (user->getId() == id) {
            return user;
        }
    }

    return nullptr;
}

// pre: users_ has a user with id from and a user with id to, and they are connected to some degree
// post: returns a vector of the shortest path starting at from and ending at to
std::vector<int> Network::shortestPath(int from, int to) {
    if (to >= numUsers() || from >= numUsers()) return std::vector<int>(); // precondition check
    
    std::queue<int> q;
    std::vector<bool> visited(numUsers(), false);
    std::vector<int> previous(numUsers(), -1);

    q.push(from);
    visited[from] = true;

    // performs a breadth first search on users_
    while (!q.empty() && !visited[to]) {
        int currUserId = q.front();
        q.pop();

        for (int friendId : users_[currUserId]->getFriends()) {
            if (!visited[friendId]) {
                visited[friendId] = true;
                q.push(friendId);
                previous[friendId] = currUserId;
            }
        }
    }

    if (!visited[to]) return std::vector<int>();

    std::vector<int> shortestPath;
    int currUserId = to;

    // builds up final vector by following shortest path in previous
    while (currUserId != -1) {
        shortestPath.push_back(currUserId);
        currUserId = previous[currUserId];
    }
    std::reverse(shortestPath.rbegin(), shortestPath.rend());

    return shortestPath;
}

// pre: users_ has a user with an id == from and has at least one user that has distance amount of edges between them
// post: changes the to paramater to match a user with the same distance and returns a vector of the shortest path starting at from and ending at to
std::vector<int> Network::distanceUser(int from, int& to, int distance) {
    // precondition check
    if (from >= numUsers()) {
        to = -1;
        return std::vector<int>();
    }
    
    // disclaimer: from my understanding of the instructions, i believe you wanted me to basically find the shortest path with distance length but i am slightly unsure.
    std::queue<int> q;
    std::vector<bool> visited(numUsers(), false);

    // each pair in the vector holds the preceding friend's id of a user (first value) and the current distance from the source (second value)
    std::vector<std::pair<int, int>> previous(numUsers(), std::make_pair(-1, 0));

    q.push(from);
    visited[from] = true;
    bool foundTarget = false;

    // performs a breadth first search on users_
    while (!q.empty() && !foundTarget) {
        int currUserId = q.front();
        q.pop();

        for (int friendId : users_[currUserId]->getFriends()) {
            if (!visited[friendId]) {
                visited[friendId] = true;
                q.push(friendId);
                previous[friendId].first = currUserId;
                previous[friendId].second = previous[currUserId].second + 1;

                // this if statement should only run ONCE it has found the first user at set distance
                if (previous[friendId].second == distance && !foundTarget) {
                    to = friendId;
                    foundTarget = true;
                }
            }
        }
    }

    // checks if user with correct distance was ever found
    // usually distance is out of bounds of the network if false
    if (!foundTarget) {
        to = -1;
        return std::vector<int>();
    }

    std::vector<int> shortestPath;
    int currUserId = to;

    // builds up final vector by following shortest path in previous
    while (currUserId != -1) {
        shortestPath.push_back(currUserId);
        currUserId = previous[currUserId].first;
    }
    std::reverse(shortestPath.rbegin(), shortestPath.rend());

    return shortestPath;
}

// pre: a user in users_ has the id matching who
// post: returns a vector of user ids who have the highest amount of friends in common with user who
// and sets score paramater to these users' score
std::vector<int> Network::suggestFriends(int who, int& score) {
    score = 0;
    if (who >= numUsers()) return std::vector<int>();

    std::queue<int> q;
    std::vector<bool> visited(numUsers(), false);
    std::vector<bool> isFriendOfUser(numUsers(), false);

    int targetDistance = 2;
    std::vector<int> potentialFriends(numUsers(), 0); // each index represents id and each int represents score
    std::vector<int> distance(numUsers(), -1);
    
    visited[who] = true;
    distance[who] = 0;
    q.push(who);

    // sets up quick way to check whether a user is a friend of who
    for (int friendId : users_[who]->getFriends()) {
        isFriendOfUser[friendId] = true;
    }

    // does a breadth first search on users_
    while (!q.empty()) {
        int currUserId = q.front();
        q.pop();

        for (int friendId : users_[currUserId]->getFriends()) {
            if (!visited[friendId] && distance[currUserId] < targetDistance) {
                q.push(friendId);
                visited[friendId] = true;
                distance[friendId] = distance[currUserId] + 1;
            }
            
            // checks whether to count towards being a potential friend
            if (distance[currUserId] == targetDistance && isFriendOfUser[friendId]) {
                potentialFriends[currUserId]++;
                if (potentialFriends[currUserId] > score) score = potentialFriends[currUserId];
            }
        }
    }

    // if score is still 0 at this point, there are NO friends of friends relative to user who
    if (score == 0) return std::vector<int>();

    // creates and fills out a vector containing all users that have the same score as the paramater score
    std::vector<int> recommendedFriends;
    for (int friendId = 0; friendId < potentialFriends.size(); friendId++) {
        if (potentialFriends[friendId] == score && visited[friendId]) {
            recommendedFriends.push_back(friendId);
        }
    }

    return recommendedFriends;
}

// pre: network object has been properly initialized
// post: returns a vector of vectors of integers with each vector within it representing a connected component
// and each of these components contain the user ids of users connected to each other.
std::vector<std::vector<int>> Network::groups() {
    std::vector<bool> visited(numUsers(), false);
    std::vector<std::vector<int>> connectedComponents;
    std::vector<int> currentGroup;

    // iterates through all of the user ids but only does something if the user has not yet been visited
    // this loop ensures ALL users are visited, isolated or not
    for (int userID = 0; userID < numUsers(); userID++) {
        if (!visited[userID]) {
            visited[userID] = true;
            currentGroup.push_back(userID);

            groupsHelper(userID, currentGroup, visited); // after this is done execution, that means it has completed one whole group
            connectedComponents.push_back(currentGroup);
            currentGroup.clear(); // resets vector's content to hold the next group (ALLOCATION IS UNCHANGED)
        }
    }

    return connectedComponents;
}

// pre: ownerId is a valid user ID (in the range of users_)
// post: returns a string containing the most recent [howMany] posts (or all if howMany >= the number of posts from user) of the specified user
std::string Network::getPostsString(int ownerId, int howMany, int privacyLevel) {
    return users_[ownerId]->getPostsString(howMany, privacyLevel);
}

// pre: who is a valid user ID
// post: returns a sorted vector of ALL friends of friends
std::vector<int> Network::getFriendsOfFriends(int who) {
    if (who >= numUsers()) return std::vector<int>();

    std::set<int> FOFTemp;
    std::vector<bool> isFriendOfUser(numUsers(), false);
    
    // mark all users who are friends as friends of the user who. will be used to prevent shared friends from being added as friends of friends.
    for (int friendId : users_[who]->getFriends()) {
        isFriendOfUser[friendId] = true;
    }
    
    // loop through who's list of friends to find friends of friends
    for (int friendId : users_[who]->getFriends()) {
        for (int friendOfFriendId : users_[friendId]->getFriends()) {
            if (!isFriendOfUser[friendOfFriendId]) { // prevents direct friends from being included
                FOFTemp.insert(friendOfFriendId);
            }
        }
    }
    
    // converts the set into a vector to return
    std::vector<int> friendsOfFriends(FOFTemp.begin(), FOFTemp.end());

    return friendsOfFriends;
}

// pre: both parameters are valid user IDs within the network
// post: returns an integer that corresponds with the access level that the accessingUser should have with the targetUser.
// 0 = private access (can see all), 1 = public access (can only see public things), 2 = semi-private access (can only see semi-private things)
int Network::getAccessLevel(int accessingUser, int targetUser) {
    if (accessingUser >= numUsers() || targetUser >= numUsers()) return -1;

    std::vector<int> friendsOfFriends = getFriendsOfFriends(targetUser);
    std::set<int> friendsOfUser = users_[targetUser]->getFriends();

    // checks if user has private access (0)
    for (int ID : friendsOfUser) {
        if (ID == accessingUser) return 0;
    }

    // checks if user has semi-private access (2)
    for (int ID : friendsOfFriends) {
        if (ID == accessingUser) return 2;
    }

    // otherwise user has public access (1)
    return 1;
}