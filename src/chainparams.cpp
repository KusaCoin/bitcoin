// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>

#include <assert.h>
#include <memory>

#include <chainparamsseeds.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 2;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 0 << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Nogomet+ 06/Jul/2018 Najskuplja krila u povijesti stajala HNS 70 tisuca franaka";
    const CScript genesisOutputScript = CScript() << OP_HASH160 << ParseHex("84fec8aa5c732cb18d8bd750811641e7e1e6b472") << OP_EQUAL;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.powLimit = uint256S("000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nZawyLwmaAveragingWindow = 45;
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x93;
        pchMessageStart[1] = 0x9f;
        pchMessageStart[2] = 0xff;
        pchMessageStart[3] = 0xf5;
        nDefaultPort = 9393;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1531062000, 9987283, 0x1e00ffff, 2, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000003acb5e87c6ad4985175506885cc88a0acf2fe8e398e1bb681274ea6f8c"));
        assert(genesis.hashMerkleRoot == uint256S("0xd10a2acbf61e1dd85ff0abc9206938b73c3e16722980a137cefdee9262ac7b45"));

        // Note that of those which support the service bits prefix, most only support a subset of
        // possible options.
        // This is fine at runtime as we'll fall back to using them as a oneshot if they dont support the
        // service bits we want, but we should get them updated to support all service bits wanted by any
        // release ASAP to avoid it where possible.
        vSeeds.emplace_back("kusacoinseed.sweetduet.info");

        base58Prefixes[PUBKEY_ADDRESS] = {0xc8, 0x62, 0x0b, 0x94};
        base58Prefixes[SCRIPT_ADDRESS] = {0x30, 0x9b, 0x42, 0xa4};
        base58Prefixes[SECRET_KEY] =     {0x9e, 0xa1, 0xc1, 0x0a};
        base58Prefixes[EXT_PUBLIC_KEY] = {0xd3, 0xd3, 0x30, 0xc0};
        base58Prefixes[EXT_SECRET_KEY] = {0x8d, 0xc9, 0x87, 0x10};

        bech32_hrp = "kusa";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                { 10000, uint256S("0x000000293173a8c60938c7f3367b4f9d278ba2a004a9691cc2140c0e75ff7bb0")},
            }
        };

        chainTxData = ChainTxData{
            // Data from rpc: getchaintxstats 4096 000000293173a8c60938c7f3367b4f9d278ba2a004a9691cc2140c0e75ff7bb0
            /* nTime    */ 1537459078,
            /* nTxCount */ 10005,
            /* dTxRate  */ 0.001728578589825587
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.powLimit = uint256S("000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nZawyLwmaAveragingWindow = 45;
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0x93;
        pchMessageStart[1] = 0x89;
        pchMessageStart[2] = 0xb8;
        pchMessageStart[3] = 0xa9;
        nDefaultPort = 19393;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1531062001, 2739213, 0x1e00ffff, 2, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000009832a3bdaae54515587a8ffdf3cae8531d6067b28e1315829f0f242888"));
        assert(genesis.hashMerkleRoot == uint256S("0xd10a2acbf61e1dd85ff0abc9206938b73c3e16722980a137cefdee9262ac7b45"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        //vSeeds.emplace_back("example.com");

        base58Prefixes[PUBKEY_ADDRESS] = {0x31, 0xfb, 0x8d, 0xdb};
        base58Prefixes[SCRIPT_ADDRESS] = {0xce, 0x76, 0xfd, 0xf4};
        base58Prefixes[SECRET_KEY] =     {0xc8, 0xe3, 0xc1, 0x93};
        base58Prefixes[EXT_PUBLIC_KEY] = {0x37, 0x86, 0xa4, 0xcc};
        base58Prefixes[EXT_SECRET_KEY] = {0xfc, 0xb8, 0x01, 0xa0};

        bech32_hrp = "kusatest";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fMineBlocksOnDemand = false;


        checkpointData = {
            {
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nZawyLwmaAveragingWindow = 45;
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0x93;
        pchMessageStart[1] = 0xb0;
        pchMessageStart[2] = 0xad;
        pchMessageStart[3] = 0xd5;
        nDefaultPort = 19494;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1531062002, 3, 0x207fffff, 2, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x42175de5dcad9922758e9ee1213b77912a0396d7e5b5182c594c0471f40cf473"));
        assert(genesis.hashMerkleRoot == uint256S("0xd10a2acbf61e1dd85ff0abc9206938b73c3e16722980a137cefdee9262ac7b45"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fMineBlocksOnDemand = true;

        checkpointData = {
            {
                {0, uint256S("26d5b70ef04fcb4ae5c18e3e92562029af13956f8d9f8319ead74072dac00ca9")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = {0x31, 0xfb, 0x8d, 0xdb};
        base58Prefixes[SCRIPT_ADDRESS] = {0xce, 0x76, 0xfd, 0xf4};
        base58Prefixes[SECRET_KEY] =     {0xc8, 0xe3, 0xc1, 0x93};
        base58Prefixes[EXT_PUBLIC_KEY] = {0x37, 0x86, 0xa4, 0xcc};
        base58Prefixes[EXT_SECRET_KEY] = {0xfc, 0xb8, 0x01, 0xa0};

        bech32_hrp = "kusareg";
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
