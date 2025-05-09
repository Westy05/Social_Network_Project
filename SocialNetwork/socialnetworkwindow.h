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


    void updateDisplay();

    void logIn();
    void loadProfile();
    void goToProfile(int row, int column);
    void goHome();
    void goToSuggested(int row, int column);
    void addFriendToUser();
    void createAPost();
private:
    Ui::SocialNetworkWindow *ui;
    Network socialNet;
    User* currentUser;
    User* displayedUser;
};
#endif // SOCIALNETWORKWINDOW_H
