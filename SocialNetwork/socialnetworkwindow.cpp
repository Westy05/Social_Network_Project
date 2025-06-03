#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"

SocialNetworkWindow::SocialNetworkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkWindow)
{
    ui->setupUi(this);

    // it took me almost 2 hours to figure out that i had to use absolute path instead of relative path
    socialNet.readUsers(const_cast<char*>("C:/cygwin64/home/heron/CS62Project/SocialNetwork/users.txt"));
    socialNet.readPosts(const_cast<char*>("C:/cygwin64/home/heron/CS62Project/SocialNetwork/posts.txt"));
    currentUser = nullptr;
    displayedUser = nullptr;
    ui->listOfFriends->setHorizontalHeaderLabels({"Friends"});
    ui->suggestedFriends->setHorizontalHeaderLabels({"Suggested Friends"});

    connect(ui->loginButton, &QPushButton::clicked, this, &SocialNetworkWindow::logIn);
    connect(ui->listOfFriends, &QTableWidget::cellClicked, this, &SocialNetworkWindow::goToProfile);
    connect(ui->homeButton, &QPushButton::clicked, this, &SocialNetworkWindow::goHome);
    connect(ui->suggestedFriends, &QTableWidget::cellClicked, this, &SocialNetworkWindow::goToSuggested);
    connect(ui->addFriendButton, &QPushButton::clicked, this, &SocialNetworkWindow::addFriendToUser);
    connect(ui->postButton, &QPushButton::clicked, this, &SocialNetworkWindow::createAPost);
    connect(ui->savePrivacySetting, &QPushButton::clicked, this, &SocialNetworkWindow::changeFriendListPrivacy);

    updateDisplay(); // critically important in hiding widgets here
}

SocialNetworkWindow::~SocialNetworkWindow()
{
    delete ui;
}


// pre: none
// post: updates the UI to show/hide certain widgets
void SocialNetworkWindow::updateDisplay() {
    if (currentUser != nullptr) { // hides login widgets
        ui->namePrompt->setVisible(false);
        ui->loginButton->setVisible(false);
        ui->nameInput->setVisible(false);
    }

    if (displayedUser != nullptr) { // shows profile widgets
        ui->profileName->setVisible(true);
        ui->listOfFriends->setVisible(true);
        ui->recentPosts->setVisible(true);
        ui->postEditor->setVisible(true);
        ui->postButton->setVisible(true);
        ui->postLabel->setVisible(true);
        ui->postPrivacySelector->setVisible(true);

        bool isMyProfile = (displayedUser->getName() == currentUser->getName()); // ignore warning, will not be null when at this line

        ui->homeButton->setVisible(!isMyProfile);
        ui->suggestedFriends->setVisible(isMyProfile);

        if (!isMyProfile) {
            // figures out whether to give user the add friends button
            std::set<int> displayedFriends = displayedUser->getFriends();
            ui->addFriendButton->setVisible(true);

            for (int i : displayedFriends) {
                if (i == currentUser->getId()) { // if already friends, then button hidden
                    ui->addFriendButton->setVisible(false);
                }
            }

            ui->privacyTitle->setVisible(false);
            ui->savePrivacySetting->setVisible(false);
            ui->currentPrivacy->setVisible(false);
            ui->friendListPrivacySelector->setVisible(false);
        } else {
            ui->addFriendButton->setVisible(false); // only happens when on own profile

            ui->privacyTitle->setVisible(true);
            ui->savePrivacySetting->setVisible(true);
            ui->currentPrivacy->setVisible(true);
            ui->friendListPrivacySelector->setVisible(true);

            if (currentUser->getFriendListPrivacy() == 0) {
                ui->currentPrivacy->setText("Current Setting: Private");
            } else if (currentUser->getFriendListPrivacy() == 1) {
                ui->currentPrivacy->setText("Current Setting: Public");
            } else if (currentUser->getFriendListPrivacy() == 2) {
                ui->currentPrivacy->setText("Current Setting: Semi-private");
            }
        }
    } else { // hides profile widgets
        ui->profileName->setVisible(false);
        ui->listOfFriends->setVisible(false);
        ui->recentPosts->setVisible(false);
        ui->homeButton->setVisible(false);
        ui->postEditor->setVisible(false);
        ui->addFriendButton->setVisible(false);
        ui->suggestedFriends->setVisible(false);
        ui->postButton->setVisible(false);
        ui->postLabel->setVisible(false);
        ui->postPrivacySelector->setVisible(false);

        ui->privacyTitle->setVisible(false);
        ui->savePrivacySetting->setVisible(false);
        ui->currentPrivacy->setVisible(false);
        ui->friendListPrivacySelector->setVisible(false);
    }
}


// pre: none
// post: logs user into the network
void SocialNetworkWindow::logIn() {
    std::string name = ui->nameInput->toPlainText().toStdString();

    int result = socialNet.getId(name);

    // checks whether input was valid
    if (result == -1) {
        ui->namePrompt->setText("Invalid Name. Try again.");
    } else {
        currentUser = socialNet.getUser(result);
        displayedUser = currentUser;
        loadProfile();
    }
}

// pre: both currentUser and displayedUser are not null
// post: loads the correct profile
void SocialNetworkWindow::loadProfile() {
    // decides whether it is the user's profile page
    bool isMyProfile = (displayedUser->getName() == currentUser->getName());
    int accessLvl = socialNet.getAccessLevel(currentUser->getId(), displayedUser->getId());

    if (isMyProfile) {
        ui->profileName->setText("My Profile");

        // gets suggested friends
        int friendScore;
        std::vector<int> friendSuggestions = socialNet.suggestFriends(currentUser->getId(), friendScore);

        // sets up suggested table
        ui->suggestedFriends->clearContents();
        ui->suggestedFriends->setRowCount(friendSuggestions.size());

        // populates suggested table
        int tracker = 0;
        for (int friendId : friendSuggestions) {
            std::string friendName = socialNet.getUser(friendId)->getName();
            QTableWidgetItem* item = new QTableWidgetItem(QString(friendName.c_str()));
            ui->suggestedFriends->setItem(tracker, 0, item);
            tracker++;
        }
    } else {
        ui->profileName->setText(QString(displayedUser->getName().c_str()));
    }

    ui->listOfFriends->clearContents();

    // checks if friend list can be displayed
    if (displayedUser->getFriendListPrivacy() == 1 || displayedUser->getFriendListPrivacy() == accessLvl || accessLvl == 0) {
        // gets friends and sets up friends table
        std::set<int> userFriends = displayedUser->getFriends();
        ui->listOfFriends->setRowCount(userFriends.size());

        // populates friends table
        int tempCounter = 0;
        for (int friendId : userFriends) {
            std::string friendName = socialNet.getUser(friendId)->getName();
            QTableWidgetItem* item = new QTableWidgetItem(QString(friendName.c_str()));
            ui->listOfFriends->setItem(tempCounter, 0, item);
            tempCounter++;
        }
    }

    std::string postString = displayedUser->getPostsString(5, accessLvl);
    ui->recentPosts->setText(postString.c_str());

    updateDisplay();
}

// pre: cell at (column, row) in table of profile's friends contains the name of a valid user
// post: changes profile to said user
void SocialNetworkWindow::goToProfile(int row, int column) {
    // grabs the id of the user with the name in cell at row, column (x, y)
    int userId = socialNet.getId(ui->listOfFriends->item(row, column)->text().toStdString());

    displayedUser = socialNet.getUser(userId);
    loadProfile();
}

// pre: currentUser is not null
// post: loads the profile of the user logged in
void SocialNetworkWindow::goHome() {
    displayedUser = currentUser;
    loadProfile();
}

// pre: cell at (column, row) in table of suggested friends contains the name of a valid user
// post: changes profile to said user
void SocialNetworkWindow::goToSuggested(int row, int column) {
    int userId = socialNet.getId(ui->suggestedFriends->item(row, column)->text().toStdString());

    displayedUser = socialNet.getUser(userId);
    loadProfile();
}

// pre: both currentUser and displayedUser are not null AND users.txt exists at specified path below
// post: creates a new connection between the profile being displayed and the logged in user. also updates users.txt to include the new connection
void SocialNetworkWindow::addFriendToUser() {
    socialNet.addConnection(currentUser->getName(), displayedUser->getName());
    socialNet.writeUsers(const_cast<char*>("C:/cygwin64/home/heron/CS62Project/SocialNetwork/users.txt"));
    loadProfile();
}

// pre: both currentUser and displayedUser are not null AND posts.txt exists at the specified path below
// post: creates a new post if done on own profile or incoming post if on someone else's profile. also updates posts.txt to include the new post
void SocialNetworkWindow::createAPost() {
    std::string message = ui->postEditor->toPlainText().toStdString();
    int privacyLvl = ui->postPrivacySelector->currentIndex();


    if (displayedUser->getName() == currentUser->getName()) {
        socialNet.addPost(currentUser->getId(), message, 0, false, "", privacyLvl);
    } else {
        socialNet.addPost(displayedUser->getId(), message, 0, true, currentUser->getName(), privacyLvl);
    }

    socialNet.writePosts(const_cast<char*>("C:/cygwin64/home/heron/CS62Project/SocialNetwork/posts.txt"));
    loadProfile();
}

// pre: currentUser is valid and filepath below exists
// post: changes logged in user's friend list privacy to what is selected in the drop down
void SocialNetworkWindow::changeFriendListPrivacy() {
    int privacyLvl = ui->friendListPrivacySelector->currentIndex();
    currentUser->setFriendListPrivacy(privacyLvl);

    socialNet.writeUsers(const_cast<char*>("C:/cygwin64/home/heron/CS62Project/SocialNetwork/users.txt"));
    updateDisplay();
}
