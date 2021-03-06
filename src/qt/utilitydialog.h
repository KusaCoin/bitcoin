// Copyright (c) 2011-2017 The Bitcoin Core developers
// Copyright (c) 2018 The Kusacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KUSACOIN_QT_UTILITYDIALOG_H
#define KUSACOIN_QT_UTILITYDIALOG_H

#include <QDialog>
#include <QObject>

class KusacoinGUI;

namespace Ui {
    class HelpMessageDialog;
}

/** "Help message" dialog box */
class HelpMessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpMessageDialog(QWidget *parent, bool about);
    ~HelpMessageDialog();

    void printToConsole();
    void showOrPrint();

private:
    Ui::HelpMessageDialog *ui;
    QString text;

private Q_SLOTS:
    void on_okButton_accepted();
};


/** "Shutdown" window */
class ShutdownWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ShutdownWindow(QWidget *parent=0, Qt::WindowFlags f=0);
    static QWidget *showShutdownWindow(KusacoinGUI *window);

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // KUSACOIN_QT_UTILITYDIALOG_H
