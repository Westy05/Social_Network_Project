/********************************************************************************
** Form generated from reading UI file 'socialnetworkwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOCIALNETWORKWINDOW_H
#define UI_SOCIALNETWORKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SocialNetworkWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *loginLayout;
    QLabel *namePrompt;
    QTextEdit *nameInput;
    QPushButton *loginButton;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *profileLayout;
    QLabel *profileName;
    QPushButton *homeButton;
    QPushButton *addFriendButton;
    QTableWidget *listOfFriends;
    QTableWidget *suggestedFriends;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *postsLayout;
    QLabel *postLabel;
    QTextEdit *postEditor;
    QPushButton *postButton;
    QLabel *recentPosts;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SocialNetworkWindow)
    {
        if (SocialNetworkWindow->objectName().isEmpty())
            SocialNetworkWindow->setObjectName("SocialNetworkWindow");
        SocialNetworkWindow->resize(800, 765);
        centralwidget = new QWidget(SocialNetworkWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 10, 160, 99));
        loginLayout = new QVBoxLayout(verticalLayoutWidget);
        loginLayout->setObjectName("loginLayout");
        loginLayout->setContentsMargins(5, 5, 5, 5);
        namePrompt = new QLabel(verticalLayoutWidget);
        namePrompt->setObjectName("namePrompt");
        namePrompt->setAlignment(Qt::AlignmentFlag::AlignCenter);

        loginLayout->addWidget(namePrompt);

        nameInput = new QTextEdit(verticalLayoutWidget);
        nameInput->setObjectName("nameInput");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(nameInput->sizePolicy().hasHeightForWidth());
        nameInput->setSizePolicy(sizePolicy);
        nameInput->setLineWrapMode(QTextEdit::LineWrapMode::WidgetWidth);

        loginLayout->addWidget(nameInput);

        loginButton = new QPushButton(verticalLayoutWidget);
        loginButton->setObjectName("loginButton");

        loginLayout->addWidget(loginButton);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(280, 0, 221, 721));
        profileLayout = new QVBoxLayout(verticalLayoutWidget_2);
        profileLayout->setObjectName("profileLayout");
        profileLayout->setContentsMargins(5, 5, 5, 5);
        profileName = new QLabel(verticalLayoutWidget_2);
        profileName->setObjectName("profileName");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(profileName->sizePolicy().hasHeightForWidth());
        profileName->setSizePolicy(sizePolicy1);
        profileName->setAlignment(Qt::AlignmentFlag::AlignCenter);

        profileLayout->addWidget(profileName);

        homeButton = new QPushButton(verticalLayoutWidget_2);
        homeButton->setObjectName("homeButton");

        profileLayout->addWidget(homeButton);

        addFriendButton = new QPushButton(verticalLayoutWidget_2);
        addFriendButton->setObjectName("addFriendButton");

        profileLayout->addWidget(addFriendButton);

        listOfFriends = new QTableWidget(verticalLayoutWidget_2);
        if (listOfFriends->columnCount() < 1)
            listOfFriends->setColumnCount(1);
        listOfFriends->setObjectName("listOfFriends");
        sizePolicy.setHeightForWidth(listOfFriends->sizePolicy().hasHeightForWidth());
        listOfFriends->setSizePolicy(sizePolicy);
        listOfFriends->setColumnCount(1);
        listOfFriends->horizontalHeader()->setDefaultSectionSize(200);
        listOfFriends->verticalHeader()->setVisible(false);

        profileLayout->addWidget(listOfFriends);

        suggestedFriends = new QTableWidget(verticalLayoutWidget_2);
        if (suggestedFriends->columnCount() < 1)
            suggestedFriends->setColumnCount(1);
        suggestedFriends->setObjectName("suggestedFriends");
        suggestedFriends->setColumnCount(1);
        suggestedFriends->horizontalHeader()->setDefaultSectionSize(200);
        suggestedFriends->verticalHeader()->setVisible(false);

        profileLayout->addWidget(suggestedFriends);

        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(530, 0, 221, 631));
        postsLayout = new QVBoxLayout(verticalLayoutWidget_3);
        postsLayout->setObjectName("postsLayout");
        postsLayout->setContentsMargins(5, 5, 5, 5);
        postLabel = new QLabel(verticalLayoutWidget_3);
        postLabel->setObjectName("postLabel");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(postLabel->sizePolicy().hasHeightForWidth());
        postLabel->setSizePolicy(sizePolicy2);
        postLabel->setMinimumSize(QSize(0, 5));
        postLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        postsLayout->addWidget(postLabel);

        postEditor = new QTextEdit(verticalLayoutWidget_3);
        postEditor->setObjectName("postEditor");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(postEditor->sizePolicy().hasHeightForWidth());
        postEditor->setSizePolicy(sizePolicy3);
        postEditor->setMinimumSize(QSize(0, 5));

        postsLayout->addWidget(postEditor);

        postButton = new QPushButton(verticalLayoutWidget_3);
        postButton->setObjectName("postButton");

        postsLayout->addWidget(postButton);

        recentPosts = new QLabel(verticalLayoutWidget_3);
        recentPosts->setObjectName("recentPosts");
        recentPosts->setMinimumSize(QSize(0, 100));
        recentPosts->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        recentPosts->setWordWrap(true);

        postsLayout->addWidget(recentPosts);

        SocialNetworkWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SocialNetworkWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        SocialNetworkWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SocialNetworkWindow);
        statusbar->setObjectName("statusbar");
        SocialNetworkWindow->setStatusBar(statusbar);

        retranslateUi(SocialNetworkWindow);

        QMetaObject::connectSlotsByName(SocialNetworkWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SocialNetworkWindow)
    {
        SocialNetworkWindow->setWindowTitle(QCoreApplication::translate("SocialNetworkWindow", "SocialNetworkWindow", nullptr));
        namePrompt->setText(QCoreApplication::translate("SocialNetworkWindow", "Enter your name.", nullptr));
        nameInput->setPlaceholderText(QCoreApplication::translate("SocialNetworkWindow", "Full name here", nullptr));
        loginButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Login", nullptr));
        profileName->setText(QCoreApplication::translate("SocialNetworkWindow", "Profile", nullptr));
        homeButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Go Home", nullptr));
        addFriendButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Add as friend", nullptr));
        postLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "User's Posts", nullptr));
        postEditor->setPlaceholderText(QCoreApplication::translate("SocialNetworkWindow", "Create a message here...", nullptr));
        postButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Post your message", nullptr));
        recentPosts->setText(QCoreApplication::translate("SocialNetworkWindow", "Placeholder text", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SocialNetworkWindow: public Ui_SocialNetworkWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOCIALNETWORKWINDOW_H
