// Copyright (c) 2014-2016 The Dash Developers
// Copyright (c) 2016-2017 The MARTEX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ANONSENDCONFIG_H
#define ANONSENDCONFIG_H

#include <QDialog>

namespace Ui
{
class AnonsendConfig;
}
class WalletModel;

/** Multifunctional dialog to ask for passphrases. Used for encryption, unlocking, and changing the passphrase.
 */
class AnonsendConfig : public QDialog
{
    Q_OBJECT

public:
    AnonsendConfig(QWidget* parent = 0);
    ~AnonsendConfig();

    void setModel(WalletModel* model);


private:
    Ui::AnonsendConfig* ui;
    WalletModel* model;
    void configure(bool enabled, int coins, int rounds);

private slots:

    void clickBasic();
    void clickHigh();
    void clickMax();
};

#endif // ANONSENDCONFIG_H
