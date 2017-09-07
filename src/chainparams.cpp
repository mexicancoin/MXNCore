// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2017 The Dash Core developers
// Copyright (c) 2014-2017 The MexicanCoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

#include "stdio.h"
#include "pow.h"

static CBlock
CreateGenesisBlock(const char *pszTimestamp, const CScript &genesisOutputScript, uint32_t nTime, uint32_t nNonce,
                   uint32_t nBits, int32_t nVersion, const CAmount &genesisReward) {
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4)
                             << std::vector<unsigned char>((const unsigned char *) pszTimestamp,
                                     (const unsigned char *) pszTimestamp +
                                     strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime = nTime;
    genesis.nBits = nBits;
    genesis.nNonce = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);

    return genesis;
}


static CBlock
CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount &genesisReward) {
    const char *pszTimestamp = "Bitcoin gana terreno: Citibanamex, BBVA y Banxico ya experimentan";
    const CScript genesisOutputScript = CScript() << ParseHex(
                                            "04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f")
                                        << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */


class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";

        consensus.nSubsidyHalvingInterval = 525600;
        consensus.nMasternodePaymentsStartBlock = 500;
        consensus.nMasternodePaymentsIncreaseBlock = -1;
        consensus.nMasternodePaymentsIncreasePeriod = -1;
        consensus.nInstantSendKeepLock = 94;
        consensus.nBudgetPaymentsStartBlock = 65123;
        consensus.nBudgetPaymentsCycleBlocks = 64800;
        consensus.nBudgetPaymentsWindowBlocks = 390;
        consensus.nBudgetProposalEstablishingTime = 86400;
        consensus.nSuperblockStartBlock = 69023;
        consensus.nSuperblockCycle = 64800;
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.nMasternodeMinimumConfirmations = 20;

        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;

        consensus.nMajorityWindow = 3900;
        consensus.BIP34Height = -1;
        consensus.BIP34Hash = uint256S("0x0");
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 60;
        consensus.nPowTargetSpacing = 40;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 2052;
        consensus.nMinerConfirmationWindow = 2160;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1486252800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517788800;

        pchMessageStart[0] = 0xb5;
        pchMessageStart[1] = 0xcc;
        pchMessageStart[2] = 0xcd;
        pchMessageStart[3] = 0xa7;

        vAlertPubKey = ParseHex(
                           "042736aa94dcc46a596d1f42a5402261b6d9d8a72de40ace5a8856f9e5f7bab96f837f926a8ab8d1e2f8d6d7ef59732d99b55352c4fdf775bdb9690c42851609bd");
        nDefaultPort = 19683;
        nMaxTipAge = 11520;
        nPruneAfterHeight = 100000;


genesis = CreateGenesisBlock(1504802012, 948015, 0x1e0ffff0, 1, 50 * COIN);
consensus.hashGenesisBlock = genesis.GetHash();
assert(consensus.hashGenesisBlock == uint256S("0x000007a402fa2831afe62294a55006339dcb23b6b43e4d0276f7db8b44951609"));
assert(genesis.hashMerkleRoot == uint256S("0x97e0b41502bf7e9be91920d8a6e3acca67000af08bcd63f5e4ea5a6ab2976dbf"));

        vSeeds.push_back(CDNSSeedData("199.43.199.118", "199.43.199.118"));
        vSeeds.push_back(CDNSSeedData("192.198.94.86", "192.198.94.86"));

        // MexicanCoin addresses start with 'X'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 76);
        // MexicanCoin script addresses start with 'X'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 78);
        // MexicanCoin private keys start with 's' or 't'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 126);

        // MexicanCoin BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(
                                             0x1E).convert_to_container<std::vector<unsigned char> >();
        // MexicanCoin BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(
                                             0xE4).convert_to_container<std::vector<unsigned char> >();

        // MexicanCoin BIP44 coin type is '5' <== Should be migrated to 31 SLIP-44 MexicanCoin
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(
                                            0x05).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 3600;
        strSporkPubKey = "04251df9125d968a5efeac89f08be613621ae19d3d9ca4818485d2405a994b6164d9f26c5ad3e7a19a99dc36fa7dd03f05e968b4bdd1dc39e5b25c0dc60a441506";
        strMasternodePaymentsPubKey = "0483bbc11d4c6a0cb4361da2a234912a7e174e2b9ecfb7685920c24a58fa32205d73f272540032ec7f4dd9d7d865bf171268dcacaa1184675cb2ed2361eb93218f";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (0, uint256S("0x000007a402fa2831afe62294a55006339dcb23b6b43e4d0276f7db8b44951609"))
             ,
            1504802012,
            1,
            1
        };
    }
};

static CMainParams mainParams;

/**
 * Testnet (v1)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = -1;
        consensus.nMasternodePaymentsStartBlock = 121;
        consensus.nMasternodePaymentsIncreaseBlock = -1;
        consensus.nMasternodePaymentsIncreasePeriod = -1;
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 2282;
        consensus.nBudgetPaymentsCycleBlocks = 90;
        consensus.nBudgetPaymentsWindowBlocks = 39;
        consensus.nBudgetProposalEstablishingTime = 720;
        consensus.nSuperblockStartBlock = 2432;
        consensus.nSuperblockCycle = 90;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;

        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;

        consensus.nMajorityWindow = 390;
        consensus.BIP34Height = -1;
        consensus.BIP34Hash = uint256S("0x0");
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 60;
        consensus.nPowTargetSpacing = 40;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 8;
        consensus.nMinerConfirmationWindow = 11;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1456790400;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1493596800;

        pchMessageStart[0] = 0xbd;
        pchMessageStart[1] = 0xa3;
        pchMessageStart[2] = 0xc8;
        pchMessageStart[3] = 0xb1;

        vAlertPubKey = ParseHex(
                           "042736aa94dcc46a596d1f42a5402261b6d9d8a72de40ace5a8856f9e5f7bab96f837f926a8ab8d1e2f8d6d7ef59732d99b55352c4fdf775bdb9690c42851609bd");
        nDefaultPort = 18683;
        nMaxTipAge = 0x7fffffff;
        nPruneAfterHeight = 1000;

genesis = CreateGenesisBlock(1504802012, 948015, 0x1e0ffff0, 1, 50 * COIN);
consensus.hashGenesisBlock = genesis.GetHash();
assert(consensus.hashGenesisBlock == uint256S("0x000007a402fa2831afe62294a55006339dcb23b6b43e4d0276f7db8b44951609"));
assert(genesis.hashMerkleRoot == uint256S("0x97e0b41502bf7e9be91920d8a6e3acca67000af08bcd63f5e4ea5a6ab2976dbf"));
      
        vFixedSeeds.clear();
        vSeeds.clear();

        vSeeds.push_back(CDNSSeedData("tnodes.muex.io", "tnodes.muex.io"));
        //vSeeds.push_back(CDNSSeedData("nodes.monetaryunit.org", "nodes.monetaryunit.org"));
        //vSeeds.push_back(CDNSSeedData("nodes.mymue.com", "nodes.mymue.com"));
        //vSeeds.push_back(CDNSSeedData("nodes.cryptophi.com", "nodes.cryptophi.com"));



        // MexicanCoin addresses start with 'G'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 38);
        // MexicanCoin script addresses start with '8' or '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);
        // MexicanCoin private keys start with 'S' or 'T'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 64);

        // Testnet MexicanCoin BIP32 pubkeys
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(
                                             0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet MexicanCoin BIP32 prvkeys
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(
                                             0x94).convert_to_container<std::vector<unsigned char> >();

        // Testnet MexicanCoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(
                                            0x01).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5 * 60;
        strSporkPubKey = "04251df9125d968a5efeac89f08be613621ae19d3d9ca4818485d2405a994b6164d9f26c5ad3e7a19a99dc36fa7dd03f05e968b4bdd1dc39e5b25c0dc60a441506";
        strMasternodePaymentsPubKey = "0483bbc11d4c6a0cb4361da2a234912a7e174e2b9ecfb7685920c24a58fa32205d73f272540032ec7f4dd9d7d865bf171268dcacaa1184675cb2ed2361eb93218f";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (0, uint256S("0x0")),
            1483076495,
            168590,
            500
        };

    }
};

static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = -1;
        consensus.nMasternodePaymentsStartBlock = 121;
        consensus.nMasternodePaymentsIncreaseBlock = -1;
        consensus.nMasternodePaymentsIncreasePeriod = -1;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 212;
        consensus.nBudgetPaymentsCycleBlocks = 90;
        consensus.nBudgetPaymentsWindowBlocks = 39;
        consensus.nBudgetProposalEstablishingTime = 720;
        consensus.nSuperblockStartBlock = 318;
        consensus.nSuperblockCycle = 10;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 100;
        consensus.nMasternodeMinimumConfirmations = 1;

        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;

        consensus.BIP34Height = -1;
        consensus.BIP34Hash = uint256S("0x0");
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 24 * 60 * 60;
        consensus.nPowTargetSpacing = 40;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108;
        consensus.nMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;

        pchMessageStart[0] = 0xe6;
        pchMessageStart[1] = 0xce;
        pchMessageStart[2] = 0xa3;
        pchMessageStart[3] = 0xba;
        nMaxTipAge = 1 * 60 * 60;
        nDefaultPort = 17683;
        nPruneAfterHeight = 1000;


genesis = CreateGenesisBlock(1504802012, 948015, 0x1e0ffff0, 1, 50 * COIN);
consensus.hashGenesisBlock = genesis.GetHash();
assert(consensus.hashGenesisBlock == uint256S("0x000007a402fa2831afe62294a55006339dcb23b6b43e4d0276f7db8b44951609"));
assert(genesis.hashMerkleRoot == uint256S("0x97e0b41502bf7e9be91920d8a6e3acca67000af08bcd63f5e4ea5a6ab2976dbf"));
      
        vFixedSeeds.clear();
        vSeeds.clear();

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nFulfilledRequestExpireTime = 5 * 60;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (0, uint256S("0x0")),
            0,
            0,
            0
        };

        // MexicanCoin addresses start with 'R'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 61);
        // MexicanCoin script addresses start with 'U' or 'V'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 69);
        // MexicanCoin private keys start with 'Q' or 'R'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 59);

        // Regtest MexicanCoin BIP32 pubkeys start with
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(
                                             0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest MexicanCoin BIP32 prvkeys start with
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(
                                             0x94).convert_to_container<std::vector<unsigned char> >();

        // Regtest MexicanCoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(
                                            0x01).convert_to_container<std::vector<unsigned char> >();
    }
};

static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(const std::string &chain) {
    if (chain == CBaseChainParams::MAIN)
        return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
        return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
        return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string &network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
