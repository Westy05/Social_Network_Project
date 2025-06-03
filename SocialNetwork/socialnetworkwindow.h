#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H

#include <QMainWindow>
#include "../network.h"
#include "../user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SocialNetworkWindow; }
QT_END_NAMESPACE

class SocialNetworkWindow : public QMainWindow
{
    Q_OBJECT

public:
    SocialNetworkWindow(QWidget *parent = nullptr);
    ~SocialNetworkWindow();

    // pre: none
    // post: updates the UI to show/hide certain widgets
    void updateDisplay();

    // pre: none
    // post: logs user into the network
    void logIn();

    // pre: both currentUser and displayedUser are not null
    // post: loads the correct profile
    void loadProfile();

    // pre: cell at (column, row) in table of profile's friends contains the name of a valid user
    // post: changes profile to said user
    void goToProfile(int row, int column);

    // pre: currentUser is not null
    // post: loads the profile of the user logged in
    void goHome();

    // pre: cell at (column, row) in table of suggested friends contains the name of a valid user
    // post: changes profile to said user
    void goToSuggested(int row, int column);

    // pre: both currentUser and displayedUser are not null AND users.txt exists at specified path below
    // post: creates a new connection between the profile being displayed and the logged in user. also updates users.txt to include the new connection
    void addFriendToUser();

    // pre: both currentUser and displayedUser are not null AND posts.txt exists at the specified path below
    // post: creates a new post if done on own profile or incoming post if on someone else's profile. also updates posts.txt to include the new post
    void createAPost();

    void changeFriendListPrivacy();
private:
    Ui::SocialNetworkWindow *ui;
    Network socialNet;
    User* currentUser;
    User* displayedUser;
};
#endif // SOCIALNETWORKWINDOW_H
