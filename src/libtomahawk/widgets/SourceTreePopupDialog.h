/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2012 Leo Franchi <lfranchi@kde.org>
 *
 *   Tomahawk is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SOURCETREE_POPUP_DIALOG
#define SOURCETREE_POPUP_DIALOG

#include "DllMacro.h"

#include <QWidget>

class QShowEvent;
class QLabel;
class QDialogButtonBox;
class QPushButton;
class QFocusEvent;
class SourceTreeView;

/**
 * Place me at offset() to the left of the right edge of the sourcetree.
 */
class DLLEXPORT SourceTreePopupDialog : public QWidget
{
    Q_OBJECT
public:
    explicit SourceTreePopupDialog( SourceTreeView* parent );

    int offset() const { return 14; }

    void setMainText( const QString& text );
    void setOkButtonText( const QString& text );

    bool resultValue() const { return m_result; }

signals:
    void result( bool accepted );

protected:
    virtual void paintEvent( QPaintEvent* );
    virtual void focusOutEvent( QFocusEvent* );
    virtual void showEvent( QShowEvent* );

private slots:
    void onAccepted();
    void onRejected();

private:
    QString m_text;
    bool m_result;

    QLabel* m_label;
    QDialogButtonBox* m_buttons;
};

#endif
