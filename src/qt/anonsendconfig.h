#ifndef ANONSENDCONFIG_H
#define ANONSENDCONFIG_H

#include <QDialog>

namespace Ui
{
class AnonSendConfig;
}
class WalletModel;

/** Multifunctional dialog to ask for passphrases. Used for encryption, unlocking, and changing the passphrase.
 */
class AnonSendConfig : public QDialog
{
    Q_OBJECT

public:
    AnonSendConfig(QWidget* parent = 0);
    ~AnonSendConfig();

    void setModel(WalletModel* model);


private:
    Ui::AnonSendConfig* ui;
    WalletModel* model;
    void configure(bool enabled, int coins, int rounds);

private slots:

    void clickBasic();
    void clickHigh();
    void clickMax();
};

#endif // ANONSENDCONFIG_H
