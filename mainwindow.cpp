#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QFrame>
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("CarBazaar");
    setFixedSize(920, 680);
    setStyleSheet("background-color: #F7F3EF;");

    pages = new QStackedWidget(this);
    pages->setGeometry(0, 0, 920, 680);

    pages->addWidget(buildWelcomePage());
    pages->addWidget(buildMainPage());
    pages->setCurrentIndex(0);
}

// ═══════════════════════════════════════════════════
// WELCOME PAGE
// ═══════════════════════════════════════════════════
QWidget* MainWindow::buildWelcomePage()
{
    QWidget *page = new QWidget();
    page->setStyleSheet("background-color: #F7F3EF;");

    QVBoxLayout *mainLayout = new QVBoxLayout(page);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setContentsMargins(40, 40, 40, 40);

    QWidget *card = new QWidget();
    card->setFixedWidth(400);
    card->setStyleSheet("background-color: #FFFFFF; border-radius: 24px;");

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(40);
    shadow->setOffset(0, 8);
    shadow->setColor(QColor(0, 0, 0, 25));
    card->setGraphicsEffect(shadow);

    QVBoxLayout *cl = new QVBoxLayout(card);
    cl->setContentsMargins(38, 42, 38, 42);
    cl->setSpacing(0);

    // Banner
    QWidget *banner = new QWidget();
    banner->setFixedHeight(100);
    banner->setStyleSheet("background-color: #FDF0EE; border-radius: 16px;");
    QVBoxLayout *bl = new QVBoxLayout(banner);
    QLabel *logo = new QLabel("🚗");
    logo->setAlignment(Qt::AlignCenter);
    logo->setStyleSheet("font-size: 44px; background: transparent;");
    bl->addWidget(logo);
    cl->addWidget(banner);
    cl->addSpacing(20);

    // Title
    QLabel *title = new QLabel("CarBazaar");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 26px; font-weight: bold; color: #1E1E1E; background: transparent;");
    QLabel *subtitle = new QLabel("Create your account to browse cars");
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("font-size: 13px; color: #AAAAAA; background: transparent;");
    cl->addWidget(title);
    cl->addSpacing(4);
    cl->addWidget(subtitle);
    cl->addSpacing(28);

    QString inputStyle =
        "QLineEdit {"
        "  border: 1.5px solid #E8E8E8;"
        "  border-radius: 12px;"
        "  padding: 0 16px;"
        "  font-size: 14px;"
        "  color: #2C2C2C;"
        "  background-color: #FAFAFA;"
        "}"
        "QLineEdit:focus {"
        "  border: 1.5px solid #C0281C;"
        "  background-color: #FFFFFF;"
        "}";

    QString labelStyle =
        "font-size: 12px; font-weight: 600;"
        "color: #555555; background: transparent; margin-bottom: 4px;";

    // Username
    QLabel *userLabel = new QLabel("CHOOSE USERNAME");
    userLabel->setStyleSheet(labelStyle);
    usernameInput = new QLineEdit();
    usernameInput->setPlaceholderText("Enter a username");
    usernameInput->setFixedHeight(50);
    usernameInput->setStyleSheet(inputStyle);
    cl->addWidget(userLabel);
    cl->addWidget(usernameInput);
    cl->addSpacing(14);

    // Password
    QLabel *passLabel = new QLabel("CHOOSE PASSWORD");
    passLabel->setStyleSheet(labelStyle);
    passwordInput = new QLineEdit();
    passwordInput->setPlaceholderText("Enter a password");
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setFixedHeight(50);
    passwordInput->setStyleSheet(inputStyle);
    cl->addWidget(passLabel);
    cl->addWidget(passwordInput);
    cl->addSpacing(8);

    // Error
    errorLabel = new QLabel("");
    errorLabel->setAlignment(Qt::AlignCenter);
    errorLabel->setFixedHeight(20);
    errorLabel->setStyleSheet("color: #C0281C; font-size: 12px; background: transparent;");
    cl->addWidget(errorLabel);
    cl->addSpacing(16);

    // Button
    signInButton = new QPushButton("Sign Up  →");
    signInButton->setFixedHeight(52);
    signInButton->setCursor(Qt::PointingHandCursor);
    signInButton->setStyleSheet(
        "QPushButton { background-color: #C0281C; color: white; border-radius: 12px;"
        "  font-size: 15px; font-weight: bold; border: none; }"
        "QPushButton:hover   { background-color: #A8221A; }"
        "QPushButton:pressed { background-color: #8E1C15; }"
        );
    cl->addWidget(signInButton);

    mainLayout->addWidget(card, 0, Qt::AlignCenter);

    connect(signInButton, &QPushButton::clicked, this, &MainWindow::onSignInClicked);

    return page;
}

void MainWindow::onSignInClicked()
{
    QString user = usernameInput->text().trimmed();
    QString pass = passwordInput->text().trimmed();

    if (user.isEmpty() || pass.isEmpty())
    {
        errorLabel->setText("❌  Please fill in both fields");
        return;
    }

    // Save what the user typed and go to main page
    savedUsername = user;
    savedPassword = pass;
    pages->setCurrentIndex(1);
}

// ═══════════════════════════════════════════════════
// MAIN PAGE
// ═══════════════════════════════════════════════════
QWidget* MainWindow::buildMainPage()
{
    QWidget *page = new QWidget();
    page->setStyleSheet("background-color: #F7F3EF;");

    QVBoxLayout *rootLayout = new QVBoxLayout(page);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    // Nav
    QWidget *nav = new QWidget();
    nav->setFixedHeight(68);
    nav->setStyleSheet("background-color: #FFFFFF; border-bottom: 1px solid #F0EDED;");
    QHBoxLayout *navLayout = new QHBoxLayout(nav);
    navLayout->setContentsMargins(32, 0, 32, 0);
    QLabel *navLogo = new QLabel("🚗");
    navLogo->setStyleSheet("font-size: 22px; background: transparent;");
    QLabel *navTitle = new QLabel("CarBazaar");
    navTitle->setStyleSheet("font-size: 20px; font-weight: bold; color: #C0281C; background: transparent;");
    QLabel *navRight = new QLabel("Find your perfect ride ✨");
    navRight->setStyleSheet("font-size: 12px; color: #BBBBBB; background: transparent;");
    navLayout->addWidget(navLogo);
    navLayout->addSpacing(8);
    navLayout->addWidget(navTitle);
    navLayout->addStretch();
    navLayout->addWidget(navRight);
    rootLayout->addWidget(nav);

    // Heading
    QLabel *heading = new QLabel("Available Cars");
    heading->setAlignment(Qt::AlignCenter);
    heading->setStyleSheet("font-size: 24px; font-weight: bold; color: #1E1E1E; background: transparent; padding: 22px 0 4px 0;");
    QLabel *sub = new QLabel("Tap  \"See More\"  to view full details & contact info");
    sub->setAlignment(Qt::AlignCenter);
    sub->setStyleSheet("font-size: 12px; color: #AAAAAA; background: transparent; margin-bottom: 18px;");
    rootLayout->addWidget(heading);
    rootLayout->addWidget(sub);

    // Scroll
    QScrollArea *scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setStyleSheet("background: transparent;");
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QWidget *scrollWidget = new QWidget();
    scrollWidget->setStyleSheet("background: transparent;");

    QHBoxLayout *carsLayout = new QHBoxLayout(scrollWidget);
    carsLayout->setContentsMargins(50, 20, 50, 40);
    carsLayout->setSpacing(28);
    carsLayout->setAlignment(Qt::AlignCenter);

    CarData cars[3] = {
        { "Toyota Camry",   "2023", "7,400,000 EGP",
         "2.5L Engine, Automatic, Leather Seats, Sunroof, Apple carplay", "01007008551", "🚙" },
        { "BMW 3 Series",   "2022", "3,200,000 EGP",
         "2.0L Turbo, Sport Package, Heated Seats, Parking Sensors",  "01007008551", "🏎‍🟀" },
        { "Hyundai Tucson", "2023", "1,900,000 EGP",
         "1.6L Turbo, AWD, Panoramic Roof, Smart Key,Touchscreen Display",     "01007008551", "🚗" }
    };

    for (int i = 0; i < 3; i++)
        addCarCard(carsLayout, cars[i]);

    scroll->setWidget(scrollWidget);
    rootLayout->addWidget(scroll, 1);

    return page;
}

void MainWindow::addCarCard(QHBoxLayout *layout, const CarData &car)
{
    QWidget *card = new QWidget();
    card->setFixedSize(248, 360);
    card->setStyleSheet("background-color: #FFFFFF; border-radius: 20px;");

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(28);
    shadow->setOffset(0, 6);
    shadow->setColor(QColor(0, 0, 0, 22));
    card->setGraphicsEffect(shadow);

    QVBoxLayout *cl = new QVBoxLayout(card);
    cl->setContentsMargins(18, 18, 18, 18);
    cl->setSpacing(0);

    QWidget *imgBox = new QWidget();
    imgBox->setFixedHeight(120);
    imgBox->setStyleSheet("background-color: #FDF0EE; border-radius: 14px;");
    QVBoxLayout *il = new QVBoxLayout(imgBox);
    il->setContentsMargins(0, 0, 0, 0);
    QLabel *emojiLbl = new QLabel(car.emoji);
    emojiLbl->setAlignment(Qt::AlignCenter);
    emojiLbl->setStyleSheet("font-size: 56px; background: transparent;");
    il->addWidget(emojiLbl);
    cl->addWidget(imgBox);
    cl->addSpacing(14);

    QLabel *nameLbl = new QLabel(car.name);
    nameLbl->setAlignment(Qt::AlignCenter);
    nameLbl->setStyleSheet("font-size: 16px; font-weight: bold; color: #1E1E1E; background: transparent;");
    cl->addWidget(nameLbl);
    cl->addSpacing(6);

    QLabel *modelLbl = new QLabel("📅  Model " + car.model);
    modelLbl->setAlignment(Qt::AlignCenter);
    modelLbl->setStyleSheet("font-size: 12px; color: #999999; background: transparent;");
    cl->addWidget(modelLbl);
    cl->addSpacing(10);

    QWidget *priceBadge = new QWidget();
    priceBadge->setFixedHeight(34);
    priceBadge->setStyleSheet("background-color: #FDF0EE; border-radius: 10px;");
    QHBoxLayout *pl = new QHBoxLayout(priceBadge);
    pl->setContentsMargins(0, 0, 0, 0);
    QLabel *priceLbl = new QLabel(car.price);
    priceLbl->setAlignment(Qt::AlignCenter);
    priceLbl->setStyleSheet("font-size: 15px; font-weight: bold; color: #C0281C; background: transparent;");
    pl->addWidget(priceLbl);
    cl->addWidget(priceBadge);
    cl->addSpacing(14);

    QFrame *sep = new QFrame();
    sep->setFrameShape(QFrame::HLine);
    sep->setStyleSheet("background-color: #F5F0EB; border: none; max-height: 1px;");
    cl->addWidget(sep);
    cl->addStretch();

    QPushButton *btn = new QPushButton("See More  →");
    btn->setFixedHeight(42);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet(
        "QPushButton { background-color: #C0281C; color: white; border-radius: 10px;"
        "  font-size: 13px; font-weight: bold; border: none; }"
        "QPushButton:hover   { background-color: #A8221A; }"
        "QPushButton:pressed { background-color: #8E1C15; }"
        );

    CarData copy = car;
    connect(btn, &QPushButton::clicked, [this, copy]() {
        showDetail(copy);
    });

    cl->addWidget(btn);
    layout->addWidget(card);
}

// ═══════════════════════════════════════════════════
// DETAIL PAGE
// ═══════════════════════════════════════════════════
void MainWindow::showDetail(CarData car)
{
    QWidget *detailPage = buildDetailPage(car);
    pages->addWidget(detailPage);
    pages->setCurrentWidget(detailPage);
}

void MainWindow::showMain()
{
    pages->setCurrentIndex(1);
}

QWidget* MainWindow::buildDetailPage(const CarData &car)
{
    QWidget *page = new QWidget();
    page->setStyleSheet("background-color: #F7F3EF;");

    QVBoxLayout *mainLayout = new QVBoxLayout(page);
    mainLayout->setContentsMargins(230, 40, 230, 40);

    QWidget *card = new QWidget();
    card->setStyleSheet("background-color: #FFFFFF; border-radius: 24px;");

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(30);
    shadow->setOffset(0, 6);
    shadow->setColor(QColor(0, 0, 0, 30));
    card->setGraphicsEffect(shadow);

    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(32, 32, 32, 32);
    cardLayout->setSpacing(0);

    // Banner
    QWidget *banner = new QWidget();
    banner->setFixedHeight(130);
    banner->setStyleSheet("background-color: #FDF0EE; border-radius: 16px;");
    QVBoxLayout *bl = new QVBoxLayout(banner);
    bl->setContentsMargins(0, 0, 0, 0);
    QLabel *emojiLbl = new QLabel(car.emoji);
    emojiLbl->setAlignment(Qt::AlignCenter);
    emojiLbl->setStyleSheet("font-size: 68px; background: transparent;");
    bl->addWidget(emojiLbl);
    cardLayout->addWidget(banner);
    cardLayout->addSpacing(18);

    // Name
    QLabel *nameLbl = new QLabel(car.name);
    nameLbl->setAlignment(Qt::AlignCenter);
    nameLbl->setStyleSheet("font-size: 24px; font-weight: bold; color: #1E1E1E; background: transparent;");
    cardLayout->addWidget(nameLbl);
    cardLayout->addSpacing(8);

    // Price badge
    QLabel *priceBadge = new QLabel(car.price);
    priceBadge->setAlignment(Qt::AlignCenter);
    priceBadge->setFixedHeight(36);
    priceBadge->setStyleSheet(
        "background-color: #FDF0EE; color: #C0281C;"
        "font-size: 15px; font-weight: bold; border-radius: 10px; padding: 0 16px;"
        );
    QHBoxLayout *badgeRow = new QHBoxLayout();
    badgeRow->addStretch();
    badgeRow->addWidget(priceBadge);
    badgeRow->addStretch();
    cardLayout->addLayout(badgeRow);
    cardLayout->addSpacing(20);

    // Divider
    QFrame *div = new QFrame();
    div->setFrameShape(QFrame::HLine);
    div->setStyleSheet("background-color: #F0EDED; border: none; max-height: 1px;");
    cardLayout->addWidget(div);
    cardLayout->addSpacing(16);

    // Rows
    auto makeRow = [](const QString &icon, const QString &label,
                      const QString &value) -> QWidget*
    {
        QWidget *row = new QWidget();
        row->setFixedHeight(48);
        row->setStyleSheet("background-color: #FAFAFA; border-radius: 10px;");
        QHBoxLayout *hl = new QHBoxLayout(row);
        hl->setContentsMargins(14, 0, 14, 0);
        hl->setSpacing(10);
        QLabel *iconLbl = new QLabel(icon);
        iconLbl->setStyleSheet("font-size: 16px; background: transparent;");
        iconLbl->setFixedWidth(24);
        QLabel *labelLbl = new QLabel(label + ":");
        labelLbl->setFixedWidth(80);
        labelLbl->setStyleSheet("font-size: 12px; font-weight: 600; color: #999999; background: transparent;");
        QLabel *valueLbl = new QLabel(value);
        valueLbl->setWordWrap(true);
        valueLbl->setStyleSheet("font-size: 13px; font-weight: 500; color: #2C2C2C; background: transparent;");
        hl->addWidget(iconLbl);
        hl->addWidget(labelLbl);
        hl->addWidget(valueLbl, 1);
        return row;
    };

    cardLayout->addWidget(makeRow("📅", "Model",   car.model));
    cardLayout->addSpacing(8);
    cardLayout->addWidget(makeRow("⚙️",  "Specs",   car.specs));
    cardLayout->addSpacing(8);
    cardLayout->addWidget(makeRow("📞", "Contact", car.contact));
    cardLayout->addStretch();
    cardLayout->addSpacing(16);

    // Back button
    QPushButton *backBtn = new QPushButton("←   Back");
    backBtn->setFixedHeight(50);
    backBtn->setCursor(Qt::PointingHandCursor);
    backBtn->setStyleSheet(
        "QPushButton { background-color: #C0281C; color: white; border-radius: 12px;"
        "  font-size: 14px; font-weight: bold; border: none; }"
        "QPushButton:hover   { background-color: #A8221A; }"
        "QPushButton:pressed { background-color: #8E1C15; }"
        );
    connect(backBtn, &QPushButton::clicked, this, &MainWindow::showMain);
    cardLayout->addWidget(backBtn);

    mainLayout->addWidget(card);
    return page;
}