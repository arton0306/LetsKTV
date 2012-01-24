#include "LabelWto.h"

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
    // mLabel->show();
    mTimer->start( aMsec );
}

void LabelWto::setText( QString aText )
{
    mLabel->setText( aText );
    // mLabel->show();
    mTimer->start( mFixedMsec );
}

void LabelWto::appendText( QString aText )
{
    // mLabel->show();
    mLabel->setText( mLabel->text() + aText );
    mTimer->start( mFixedMsec );
}

QString LabelWto::getText()
{
    return mLabel->text();
}

void LabelWto::hideLabel()
{
    mLabel->setText( QString() );
    // mLabel->hide();
}

void LabelWto::setAlignment( Qt::Alignment aAlignment )
{
    mLabel->setAlignment( aAlignment );
}
