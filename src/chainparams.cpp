// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2014-2018 The MarteX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 *
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 *   CBlock(hash=cf0e34e039bde2f97264768907c204e2703339f5cfb38f65440cee7f9adfb794, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000,
 *    hashMerkleRoot=07fab1cd4f71e2e3a036f201590ddb4be37bb4573dfca63d3216405f3650dc18, nTime=1537366286, nBits=1e3fffff, nNonce=857701, vtx=1)
 *    CTransaction(hash=07fab1cd4f, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *      CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01040b53696e6365203230313421)
 *      CTxOut(nValue=1.00000000, scriptPubKey=046acdcdecdea7b6b17c217f27e73c)
 *    vMerkleTree:  07fab1cd4f71e2e3a036f201590ddb4be37bb4573dfca63d3216405f3650dc18
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (     0, uint256("0xcf0e34e039bde2f97264768907c204e2703339f5cfb38f65440cee7f9adfb794"));
    //boost::assign::map_list_of(0, uint256("0x001"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1537366286, // * UNIX timestamp of last checkpoint block
    1,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (     0, uint256("0x4c02cb69c798414bdb443382818f9f5619e52c198ad91586b6515ac40e888563"));
    //boost::assign::map_list_of(0, uint256("0x001"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1537366286,
    1,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (     0, uint256("0x7c3cbaa93b112a59d234b0553016e65604fa5c1763e3b429a038a36395720632"));
    //boost::assign::map_list_of(0, uint256("0x001"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1537366286,
    1,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x2d;
        pchMessageStart[1] = 0x3f;
        pchMessageStart[2] = 0xa2;
        pchMessageStart[3] = 0xf5;

        vAlertPubKey = ParseHex("046acdcdecdea7b6b17c217f27e73ca2acbddda8e70570ff355dbe1af30347d280f66067d136a797fce4d01227cc5be988676184d842930765fcce5dc011ad158e");
        nDefaultPort = 51315;
	bnProofOfWorkLimit = ~uint256(0) >> 18;
        nSubsidyHalvingInterval = 262800;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 1006;
        nRejectBlockOutdatedMajority = 1007;
        nToCheckBlockUpgradeMajority = 1008;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // MarteX: 1 day
        nTargetSpacing = 2 * 60;  // MarteX: 2 minute
        nMaturity = 150;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 11600000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 1001;
        nModifierUpdateBlock = 0;
        nZerocoinStartHeight = 1002;
        nBlockEnforceSerialRange = 1004; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 1005; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 1003; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 1005; //Last valid accumulator checkpoint
        nZerocoinStartTime = 1546214400; //Mon, 31 Dez 2018 00:00:00 GMT
        nBlockEnforceInvalidUTXO = 1001; //Start enforcing the invalid UTXO's

        const char* pszTimestamp = "Since 2014!";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("046acdcdecdea7b6b17c217f27e73ca2acbddda8e70570ff355dbe1af30347d280f66067d136a797fce4d01227cc5be988676184d842930765fcce5dc011ad158e") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1537366286;
        genesis.nBits = 0x1e3fffff;
        genesis.nNonce = 857701;
	//printf("MAIN = %s\n", genesis.ToString().c_str());

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xcf0e34e039bde2f97264768907c204e2703339f5cfb38f65440cee7f9adfb794"));
        assert(genesis.hashMerkleRoot == uint256("0x07fab1cd4f71e2e3a036f201590ddb4be37bb4573dfca63d3216405f3650dc18"));

        vSeeds.push_back(CDNSSeedData("seed0",  "seed.martexcoin.org"));
        vSeeds.push_back(CDNSSeedData("seed1",  "seed1.martexcoin.org"));
        vSeeds.push_back(CDNSSeedData("seed2",  "seed2.martexcoin.org"));
        vSeeds.push_back(CDNSSeedData("seed3",  "seed3.martexcoin.org"));
        vSeeds.push_back(CDNSSeedData("seed4",  "seed4.martexcoin.org"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 50); // first letter "M"
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 5);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 50 + 128);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        //BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xB4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = false; //default true
        fMiningRequiresPeers = false; //default true
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = true;  //default false
        fSkipProofOfWorkCheck = false;  //default false
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "029edc4fc53218495a1ec17ba3175653d18084deb46244ed0d5cf470e4f2f64ebc";
        strAnonSendPoolDummyAddress = "MLJoZZky8GtfYKiRY2Jzxfd4KTEK3drZv2";
        nStartMasternodePayments = 1546214400; //Mon, 31 Dez 2018 00:00:00 GMT

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 2;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * TestNet network
 *
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 *   CBlock(hash=4c02cb69c798414bdb443382818f9f5619e52c198ad91586b6515ac40e888563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000,
 *    hashMerkleRoot=d5033f45952ca385ef3a2a9ce938156bbf004c09982ed4814253cca72a9569c4, nTime=1537366286, nBits=1e3fffff, nNonce=857701, vtx=2)
 *    CTransaction(hash=07fab1cd4f, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *      CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01040b53696e6365203230313421)
 *      CTxOut(nValue=1.00000000, scriptPubKey=046acdcdecdea7b6b17c217f27e73c)
 *    vMerkleTree:  d5033f45952ca385ef3a2a9ce938156bbf004c09982ed4814253cca72a9569c4
 */

class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x70;
        pchMessageStart[1] = 0x35;
        pchMessageStart[2] = 0x22;
        pchMessageStart[3] = 0x05;
        vAlertPubKey = ParseHex("04da6ac103778f420a56c8d3b47133ad05872a6eeae68a29e765d4d98b8273361fd0bc7cab6fa28463611b852cfca06afd41e8dab8ce48736763c07d2015736469");
        nDefaultPort = 41315;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // MarteX: 1 day
        nTargetSpacing = 2 * 60;  // MarteX: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 5;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 11600000 * COIN;
        nZerocoinStartHeight = 201;
	nSubsidyHalvingInterval = 150;

        const char* pszTimestamp = "Since 2014!";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("046acdcdecdea7b6b17c217f27e73ca2acbddda8e70570ff355dbe1af30347d280f66067d136a797fce4d01227cc5be988676184d842930765fcce5dc011ad158e") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1537366286;
        genesis.nBits = 0x1e3fffff;
        genesis.nNonce = 857701;
        //printf("TESTNET = %s\n", genesis.ToString().c_str());

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x4c02cb69c798414bdb443382818f9f5619e52c198ad91586b6515ac40e888563"));
        assert(genesis.hashMerkleRoot == uint256("0xd5033f45952ca385ef3a2a9ce938156bbf004c09982ed4814253cca72a9569c4"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
	base58Prefixes[SECRET_KEY]     = list_of(324).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "029edc4fc53218495a1ec17ba3175653d18084deb46244ed0d5cf470e4f2f64ebc";
        strAnonSendPoolDummyAddress = "MLJoZZky8GtfYKiRY2Jzxfd4KTEK3drZv2";
        nStartMasternodePayments = 1546214400; //Mon, 31 Dez 2018 00:00:00 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * RegTest network
 *
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 *   CBlock(hash=7c3cbaa93b112a59d234b0553016e65604fa5c1763e3b429a038a36395720632, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000,
 *    hashMerkleRoot=2ec44783dd8d741855203e4ee2cfb86c7c8a1da087e70ed0dcfdccc1d40f3c89, nTime=1537366286, nBits=1e3fffff, nNonce=857701, vtx=3)
 *    CTransaction(hash=07fab1cd4f, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *      CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01040b53696e6365203230313421)
 *      CTxOut(nValue=1.00000000, scriptPubKey=046acdcdecdea7b6b17c217f27e73c)
 *    vMerkleTree:  2ec44783dd8d741855203e4ee2cfb86c7c8a1da087e70ed0dcfdccc1d40f3c89
 */

class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x2f;
        pchMessageStart[1] = 0xca;
        pchMessageStart[2] = 0x4d;
        pchMessageStart[3] = 0x3e;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // MarteX: 1 day
        nTargetSpacing = 1 * 60;        // MarteX: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 16;
        nDefaultPort = 31315;

        const char* pszTimestamp = "Since 2014!";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("046acdcdecdea7b6b17c217f27e73ca2acbddda8e70570ff355dbe1af30347d280f66067d136a797fce4d01227cc5be988676184d842930765fcce5dc011ad158e") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1537366286;
        genesis.nBits = 0x1e3fffff;
        genesis.nNonce = 857701;
        //printf("REGTEST = %s\n", genesis.ToString().c_str());

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x7c3cbaa93b112a59d234b0553016e65604fa5c1763e3b429a038a36395720632"));
        assert(genesis.hashMerkleRoot == uint256("0x2ec44783dd8d741855203e4ee2cfb86c7c8a1da087e70ed0dcfdccc1d40f3c89"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 21315;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
