// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Seraph developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

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
                (0, uint256("0x000007e8828bcf3f1c0c5be279eb9565a6b2813e066dab69515326cc38380fb8"))
	        (20, uint256("0x00000b79aa269e5f5bf0f9c12b885743570a0b2885b6ae6438aac000f0d0d378"))
	        (30, uint256("0x00000387754276c709a5a990b2f4e48c5ecb3acefcfd417c14a5f4937e754d17"));

static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1522403211,// * UNIX timestamp of last checkpoint block
        31,    // * total number of transactions between genesis and last checkpoint
        //   (the tx=... number in the SetBestChain debug.log lines)
        2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of(0, uint256("0x"));
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1518900000,
        0,
        250};
static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        1518900000,
        0,
        100};
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
        pchMessageStart[0] = 0xe9;
        pchMessageStart[1] = 0x2c;
        pchMessageStart[2] = 0x78;
        pchMessageStart[3] = 0xaf;
        vAlertPubKey = ParseHex("048ea26bc698946b3f4193aef683b6760bd132e309381425e651be31215bcfc2dad7f9146fb700c2d103e621fbc253169563af35c67b9258c4bd2f2a76cf1a1fa3");
        nDefaultPort = 25676;
        bnProofOfWorkLimit = ~uint256(0) >> 20; 
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nTargetTimespan = 2 * 60; 
        nTargetSpacingSlowLaunch = 3 * 60;  
        nTargetSpacing = 2* 60; 
        nLastPOWBlock = 26280000; 
        nRampToBlock = 500; 
        nMaturity = 10; 
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 32000000 * COIN; 

        const char* pszTimestamp = "Sea lo que sea sera Y quede lo que quede de mi Bendita la alegría a la que me has atado";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04dceb694838cc44a752a15056ace368cb15e49a2e9e808b8b387c657277ebfa2c6dadc9cb934200dd8ea4c04946928b1e705710b259ff3ac6b3cc26b741bbbdd7") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1519425170;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1362655;


        hashGenesisBlock = genesis.GetHash();

        //MineGenesis(genesis);
        vFixedSeeds.clear();
        vSeeds.clear();
        assert(hashGenesisBlock == uint256("0x000007e8828bcf3f1c0c5be279eb9565a6b2813e066dab69515326cc38380fb8"));
        assert(genesis.hashMerkleRoot == uint256("0x5721e13893e3b38b95fe2ad83a1cbc54c714f066ea6069ad5e220df783d6fbb9"));
		
	    vSeeds.push_back(CDNSSeedData("207.148.23.183", "207.148.23.183"));  // Seed node 1 : New York
        vSeeds.push_back(CDNSSeedData("140.82.32.18", "140.82.32.18"));  // Seed node 2 : Germany
		vSeeds.push_back(CDNSSeedData("207.148.94.219", "207.148.94.219"));  // Seed node 3 : Japan
		vSeeds.push_back(CDNSSeedData("140.82.18.79", "140.82.18.79"));  // Seed node 4 : Los Angeles


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 54); 
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 28);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 126);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x21)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x4C)(0x2B).convert_to_container<std::vector<unsigned char> >();
        //  BIP44 coin type is 'TBD'
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x89)(0x00).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04a72cdafbd514beba17787899e4f97346fcf96575cc74d545145f9056d09c39492d8ddf42971bd5a3ac03947d40d7470bc0b3000fab52ebb6ca2c509a404ce324";
        strObfuscationPoolDummyAddress = "P2MsmZwhprg6UUGnM5bLkFRXUh2Hkrma7D";
        nStartMasternodePayments = 1519260063;
    }


    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;
/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xb5;
        pchMessageStart[1] = 0xd9;
        pchMessageStart[2] = 0xf4;
        pchMessageStart[3] = 0xa0;

        vAlertPubKey = ParseHex("048ea26bc698946b3f4193aef683b6760bd132e309381425e651be31215bcfc2dad7f9146fb700c2d103e621fbc253169563af35c67b9258c4bd2f2a76cf1a1fa3");
        nDefaultPort = 43246;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 120; // 120 Seconds
        nTargetSpacing = 5 * 120;  // 600 Seconds
        nLastPOWBlock = 1000;
        nMaturity = 15;
        nMaxMoneyOut = 33284220 * COIN; // 2050 Maximum

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1518900000;
        genesis.nNonce = 746269;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();

        hashGenesisBlock == uint256("0x");
        genesis.hashMerkleRoot == uint256("0x");
        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("seraph.io", "test01.seraph.io"));
        vSeeds.push_back(CDNSSeedData("seraph.io", "test02.seraph.io"));
        vSeeds.push_back(CDNSSeedData("seraph.io", "test03.seraph.io"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65); // Testnet seraph addresses start with 'T'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 12);  // Testnet seraph script addresses start with '5' or '6'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet seraph BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet seraph BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet seraph BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
        nPoolMaxTransactions = 2;
        strSporkKey = "04a72cdafbd514beba17787899e4f97346fcf96575cc74d545145f9056d09c39492d8ddf42971bd5a3ac03947d40d7470bc0b3000fab52ebb6ca2c509a404ce324";
        strObfuscationPoolDummyAddress = "TUQ57Fbh1crybrDhV6X9SDH95H4oSq4v6p";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;
/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Seraph: 1 day
        nTargetSpacing = 1 * 60;        // Seraph: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1454124731;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12345;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 52589;
//        assert(hashGenesisBlock == uint256("0x4f023a2120d9127b21bbad01724fdb79b519f593f2a85b60d3d79160ec5f29df"));
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
        nDefaultPort = 52591;
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
