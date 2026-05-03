#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QStackedWidget>

struct CarData {
    QString name;
    QString model;
    QString price;
    QString specs;
    QString contact;
    QString emoji;
};

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onSignInClicked();
    void showDetail(CarData car);
    void showMain();

private:
    QStackedWidget *pages;
    QLineEdit   *usernameInput;
    QLineEdit   *passwordInput;
    QPushButton *signInButton;
    QLabel      *errorLabel;
    QString      savedUsername;
    QString      savedPassword;

    QWidget* buildWelcomePage();
    QWidget* buildMainPage();
    QWidget* buildDetailPage(const CarData &car);
    void addCarCard(QHBoxLayout *layout, const CarData &car);
};

#endif