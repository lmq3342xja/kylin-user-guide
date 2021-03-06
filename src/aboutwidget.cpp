#include "aboutwidget.h"
#include "xatom-helper.h"

AboutWidget::AboutWidget(QWidget *parent):
    QDialog(parent)
{
    this->setFixedSize(420,560);

    if(QGSettings::isSchemaInstalled("org.ukui.style")){
        settings = new QGSettings("org.ukui.style");
        connect(settings,&QGSettings::changed,this,&AboutWidget::gsettingsChange);
    }

    // 添加窗管协议
    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(this->winId(), hints);

    initUI();
}

AboutWidget::~AboutWidget()
{

}

void AboutWidget::initUI()
{
    QPalette palette;
    if(settings->get("styleName").toString() == "ukui-default"){
        palette.setBrush(QPalette::Background, QBrush(QColor(Qt::white)));
        palette.setBrush(QPalette::Text, QBrush(QColor(29,29,31)));
    }else{
        palette.setBrush(QPalette::Background, QBrush(QColor(29,29,31)));
        palette.setBrush(QPalette::Text, QBrush(QColor(Qt::white)));
    }
    this->setPalette(palette);

    title_icon = new QLabel(this);
    title_icon->setGeometry(8,8,24,24);

    title_name = new QLabel(this);
    title_name->setGeometry(40,8,300,25);
    title_name->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    close_btn = new QPushButton(this);
    close_btn->setIcon(QIcon::fromTheme("window-close-symbolic"));
    close_btn->setProperty("isWindowButton", 0x2);
    close_btn->setProperty("useIconHighlightEffect", 0x8);
    close_btn->setFlat(true);
    close_btn->setFocusPolicy(Qt::NoFocus);
    close_btn->setToolTip(tr("Close"));
    close_btn->setCursor(QCursor(Qt::ArrowCursor));
    close_btn->setGeometry(386,4,30,30);
    connect(close_btn,&QPushButton::released,this,&AboutWidget::close);

    app_icon = new QLabel(this);
    app_icon->setGeometry(162,72,96,96);

    QFont font;
    font.setPixelSize(18);

    app_name = new QLabel(this);
    app_name->setGeometry(10,184,400,28);
    app_name->setAlignment(Qt::AlignCenter);
    app_name->setFont(font);

    font.setPixelSize(14);
    app_version = new QLabel(this);
    app_version->setGeometry(10,224,400,24);
    app_version->setAlignment(Qt::AlignCenter);
    app_version->setFont(font);

//    palette.setColor(QPalette::WindowText,QColor(89,89,89));
//    app_version->setPalette(palette);

    app_description = new QLabel(this);
    app_description->setGeometry(32,260,356,100);
    app_description->setAlignment(Qt::AlignTop);
    app_description->setWordWrap(true);

    app_support = new QLabel(this);
    app_support->setGeometry(32,360,356,30);
    app_support->setAlignment(Qt::AlignLeft);
    app_support->setOpenExternalLinks(true);
    app_support->setText(tr("Service & Support : <a style='color: black;' href='mailto://support@kylinos.cn'>support@kylinos.cn</a>"));
}

void AboutWidget::setAppIcon(const QString &text)
{
    if(text.isEmpty() || text == ""){
        qDebug() << Q_FUNC_INFO << "arg is empty!!!";
        return;
    }else{
        if(QIcon::hasThemeIcon(text)){
            title_icon->setPixmap(QIcon::fromTheme(text).pixmap(24,24));
            app_icon->setPixmap(QIcon::fromTheme(text).pixmap(96,96));
        }else{
            qDebug() << Q_FUNC_INFO << "No icon exists: " << text << " !!!";
        }
    }
}

void AboutWidget::setAppName(const QString &text)
{
    if(text.isEmpty() || text == ""){
        qDebug() << Q_FUNC_INFO << "APP name should not be empty!!!";
        return;
    }else{
        title_name->setText(text);
        title_name->update();
        app_name->setText(text);
    }
}

void AboutWidget::setAppVersion(const QString &text)
{
    if(text.isEmpty() || text == ""){
        qDebug() << Q_FUNC_INFO << "APP version should not be empty!!!";
        return;
    }else{
        app_version->setText(tr("VERSION")+":  "+text);
    }
}

void AboutWidget::setAppDescription(const QString &text)
{
    app_description->setText(text);
}

void AboutWidget::gsettingsChange(const QString &key)
{
    if(key == "styleName"){
        QPalette palette;
        if(settings->get("styleName").toString() == "ukui-black"|| settings->get("styleName").toString() == "ukui-dark"){
            palette.setBrush(QPalette::Background, QBrush(QColor(29,29,31)));
            palette.setBrush(QPalette::Text, QBrush(QColor(Qt::white)));
            this->setPalette(palette);
        }else{
            palette.setBrush(QPalette::Background, QBrush(QColor(Qt::white)));
            palette.setBrush(QPalette::Text, QBrush(QColor(29,29,31)));
            this->setPalette(palette);
        }
    }
}

void AboutWidget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << Q_FUNC_INFO;
}
