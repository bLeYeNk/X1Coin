// Copyright (c) 2011-2020 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef X1COIN_QT_X1COINADDRESSVALIDATOR_H
#define X1COIN_QT_X1COINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class X1coinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit X1coinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** X1coin address widget validator, checks for a valid x1coin address.
 */
class X1coinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit X1coinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // X1COIN_QT_X1COINADDRESSVALIDATOR_H
