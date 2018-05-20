// Copyright (c) 2011-2014 The Bitcoin Core developers
// Copyright (c) 2018 The Kusacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KUSACOIN_QT_KUSACOINADDRESSVALIDATOR_H
#define KUSACOIN_QT_KUSACOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class KusacoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit KusacoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Kusacoin address widget validator, checks for a valid kusacoin address.
 */
class KusacoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit KusacoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // KUSACOIN_QT_KUSACOINADDRESSVALIDATOR_H
