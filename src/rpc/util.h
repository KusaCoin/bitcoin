// Copyright (c) 2017 The Bitcoin Core developers
// Copyright (c) 2018 The Kusacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KUSACOIN_RPC_UTIL_H
#define KUSACOIN_RPC_UTIL_H

#include <string>
#include <vector>

class CKeyStore;
class CPubKey;
class CScript;

CPubKey HexToPubKey(const std::string& hex_in);
CPubKey AddrToPubKey(CKeyStore* const keystore, const std::string& addr_in);
CScript CreateMultisigRedeemscript(const int required, const std::vector<CPubKey>& pubkeys);

#endif // KUSACOIN_RPC_UTIL_H
