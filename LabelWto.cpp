#include "LabelWto.h"

const int DEFAULT_FIXED_MSEC = 1000;

LabelWto::LabelWto(QWidget *parent, int aFixedMsec )
    : QWidget(parent)
    , mTimer( new QTimer( this ) )
    , mFixedMsec( aFixedMsec )
{
    setupUi(this);
    setStyleSheet("background-color: black;");
    mTimer->setSingleShot( true );
    setupConnections();
}

LabelWto::~LabelWto()
{
}

void LabelWto::setupConnections()
{
    connect( mTimer, SIGNAL(timeout()), this, SLOT(hideLabel() ) );
}

void LabelWto::setFixedMsec( int aMsec )
{
    mFixedMsec = aMsec;
}

void LabelWto::setTextAndTimer( QString aText, int aMsec )
{
    mLabel->setText( aText );
    mLabel->show();
    mTimer->start( aMsec );
}

void LabelWto::setTextAndTimer( QString aText )
{
    mLabel->setText( aText );
    mLabel->show();
    mTimer->start( mFixedMsec > 0 ? mFixedMsec : DEFAULT_FIXED_MSEC );
}

void LabelWto::appendText( QString aText )
{
    mLabel->show();
    mLabel->setText( mLabel->text() + aText );
    mTimer->start( mTimer->interval() );
}

QString LabelWto::getText()
{
    return mLabel->text();
}

void LabelWto::hideLabel()
{
    mLabel->setText( QString() );
    mLabel->hide();
}
