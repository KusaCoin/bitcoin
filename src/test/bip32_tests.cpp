// Copyright (c) 2013-2017 The Bitcoin Core developers
// Copyright (c) 2018 The Kusacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/test/unit_test.hpp>

#include <base58.h>
#include <key.h>
#include <uint256.h>
#include <util.h>
#include <utilstrencodings.h>
#include <test/test_kusacoin.h>

#include <string>
#include <vector>

struct TestDerivation {
    std::string pub;
    std::string prv;
    unsigned int nChild;
};

struct TestVector {
    std::string strHexMaster;
    std::vector<TestDerivation> vDerive;

    explicit TestVector(std::string strHexMasterIn) : strHexMaster(strHexMasterIn) {}

    TestVector& operator()(std::string pub, std::string prv, unsigned int nChild) {
        vDerive.push_back(TestDerivation());
        TestDerivation &der = vDerive.back();
        der.pub = pub;
        der.prv = prv;
        der.nChild = nChild;
        return *this;
    }
};

TestVector test1 =
  TestVector("000102030405060708090a0b0c0d0e0f")
    ("myAZYAMHdHJQJ1BBkot8pfGuNtsARjHPLwTymST2a98bzd6xUPEeawibUrSGMDBnM59q5tZDJdA7Pfyw96DF19Y41crL3hGkKze6DeY7utix4bM5",
     "X6oWoFPAeU8uUMkCtQFPtoQ4if6na46nC8WzpGjLSEu3apMxE4C6QmSxwxrpxwcjkDTeo8vstCmwNqyn1vFr8TN8ZpiPsYDUx4ncdE4kijZKNcHL",
     0x80000000)
    ("myAZYAPZ3H1hm6SJjxVGXs2n1muGY46whKYTn84TU7Dz7bJ9kkWwmMx8ZyackzTM3pTjctmVsVPepQd1E4cD96ZnPgjnmtuYauwzSAUFUCHSyht2",
     "X6oWoFRS4TrCwT1KsYrXc19wMY8tgNvLYWbUpxLmLCzRhnZ9WRUPbBgW361BNit65dB2kqymaa5GFELcte1sr6xQkcnUPc6A6JkKWw5PaAhuDSFL",
     1)
    ("myAZYARjAUoFeV9BonwJybHftNeAC7UvoKaC54P8JhVkvXvwxz4Su5kYsw9WzQXodEQSxrV7vGp6vXDVheuwxZtxHNPciC7PSPazhoCnFVKH67XD",
     "X6oWoFTcBfdkpqiCwPJa3jQqE8snLSJKeWdD7tfSAoGCWjBwif1tiuUvM3a5c8wH9E6ooJ4XGNtrgK3aJmxQ5EJCjPwxq7s7pNW6NbshwhchpJfH",
     0x80000002)
    ("myAZYAULSXL5WC23Df774qt5FjeCLLdoKb7n4PvMywq45hoKQPue1tWPJqb4uxYzTgGtHD1DetC5XuA4g7F6FGzVpRqmYn1MaUY4PWthPaUCW78b",
     "X6oWoFWDTiAagYb4MFUN8z1EbVspUfTCAnAo7ECfr3bVfu4KA4s5qiEkmx1dXgyVmCLKHoXYeyMobjTQD1A8ppK7vX3QVUUgNXSLKD9TALHgBoNk",
     2)
    ("myAZYAWZqMmCTNViCjaanY9HLd9MeRT64Di6FqQFHCnaZ2Et1m1GNxH5g3AXqdsyr6531gKLq2CZUwtxnffSFNHw29SEognumJixDXacEj75rvyc",
     "X6oWoFYSrYbhdj4jLKwqrgGSgPNynkGUuQm7JfgZ9JZ29DVsmRxiCn1T99b6TNHuDeziisKgMbH3AeGrNUM3H1jfGiRzXsimU5XA2N7vKqjHpMuW",
     1000000000)
    ("myAZYAYHbqSohVd6QFvNEegr4vrMeDgfN3CuHdedqT4xhEKGWU8fmUhLLJGguGhtnwL7jA1dNXYVHV6fPG5qGU9RrzhPvZLKr7CXrLYE9yFGtAix",
     "X6oWoFaAd2HJsrC7XrHdJnp1Qh5ynYW4DEFvLTvwhYqQHRaGG967bJRhoQhFX19gRZuqoUj5cNe27VKPVUX3eYofzqPe5DDXhCRujeTUgau9R4MN",
     0);

TestVector test2 =
  TestVector("fffcf9f6f3f0edeae7e4e1dedbd8d5d2cfccc9c6c3c0bdbab7b4b1aeaba8a5a29f9c999693908d8a8784817e7b7875726f6c696663605d5a5754514e4b484542")
    ("myAZYAMHdHJQJ1BBkoVe9mRyfM4tByUXmd6Eb82pJS5LpbV5LgDfn7sNRHLRwZHsKnQC3o7T6XpmZ54SPozyEGiyAkmKzZCwnq8asxuo2Ab2x858",
     "X6oWoFPAeU8uUMkCtPruDuZ917JWLJHvcp9FdxK8AXqnQnk56MB7bwbjtPkzZHgWoPyCtNydJx4Pq85pD1naEVnXGS5idzdZCD8XMoKNx6XadS5z",
     0)
    ("myAZYAQZNZ26FVC1qKmESuDMYQsHiLSH2L4isgCZfbtNGftwJNC7kh8iVSB1C8kqDaVCV1RwGQ3mJU9HMyAPv9sfb6MzGqFgTjUjG6PugbqLt5Dq",
     "X6oWoFSSPjrbRqm2xv8VX3LWtB6urfFfsX7jvWUsXheors9w439ZaWs5xYbZosBnc333inds8r4oZZFELNJD4452KNJt2zoyFbch6vjHWToACwt6",
     0xFFFFFFFF)
    ("myAZYARiRod7ms6BwVdSdKfMBtCyGjBVvsYtZmMeCXHH3KdhgpVMDK28oeEnnk95LLDoanwrp3tcumMhxdqGFvn9hpWSuNLJX6CzGxnBHSb8A5Ce",
     "X6oWoFTbSzTcxDfD55zhhTnWXeSbR3ztn4bucbdx4d3idWthSVSo38kWGkfMQUYGamHnCgsC2d61CcFjSoXwpnSdSwcKbRYCbN8RMiWd3ED8G51E",
     1)
    ("myAZYAUXQDe6i2jV8bF7mPKVkr9uW4iNRyjoq5o94NLwNdX48VKDNcXfWY9BAawGU86VsP8KMtXi9QV1nidXGqgaf5quoxcWNJkRUtYrEh3sVwLE",
     "X6oWoFWQRQUbtPJWGBcNqXSf6cPXePXmHAnpsv5SvU7Nxpn3tAGfCSG2yeZjnKLUCnzytzpYjNP5b1oQf8EiyqL9px68tZJjQDEPkCK3mhw1q96B",
     0xFFFFFFFE)
    ("myAZYAVhS8c34e8SqtCMN7oKJDfbgySqo2iSL7Vrwu4dnUHKNwfYJiCbX4fYGDbPyKU2KLZxzh2mrT6LeNGgfXZhAoCcGEWprs3WtkmvpDzRqnfe",
     "X6oWoFXaTKSYEzhTyUZcSFvUdyuDqJGEeDmTNwnAozq5NfYK8ccz8XvxzB66sx3CbRRNBYPqRgCraQAzEwMpMMH4Kdvp4PFGiMSRNXu4Hmfxoaug",
     2)
    ("myAZYAX4U63FaAJm5dTYFqsSzCQyfNWNuH3MQmfUqJqzH75Ay1rsssqXHFEVGHzUFT3P1rdBDxxHGLoMdrhkAMfP57TTqsgewoQodS57ztdXMgYj",
     "X6oWoFYwVGskkWsnDDpoKyzcKxebohKmkU6NTbwnhQcRsJLAigpKhhZtkMf3t2SsbaSTFahh9xxVPrGpvyuhs5bRYguYnC6nDQrZ6EGPqrE5keJK",
     0);

TestVector test3 =
  TestVector("4b381541583be4423346c643850da4b320e46a87ae3d2a4e6da11eba819cd4acba45d239319ac14f863b8d5ab5a0d0c64d2e8a1e7d1457df2e5a3c51c73235be")
    ("myAZYAMHdHJQJ1BBknZ6KHpUTZ49Dr7rsNxPrqNarqNNNsBA8eTu3n1cPEbfU3HQJbzmgyCCxMpeZTjGFFJc97S1cB6z8gSr1Zh2ikdJih7hWwC4",
     "X6oWoFPAeU8uUMkCtNvMPRwdoKHmNAwFia1Qufetiw8oy4S9tKRLsbjyrM2E5mgEyLzSDTgJ4Wz5w2WYvNSBYjDfhDZDtWv7qQZsL633JkTwrRaK",
      0x80000000)
    ("myAZYAPeq2GERgYZ6z6BiWxoxcJttYUUFXoomErpoec4DoV5VuV2WMWPFK4TBM1EpLMNSAZho8nQJJgTjsmYV3fwnkMG5MYnu7YXXEofdMWGDPZc",
     "X6oWoFRXrD6jc37aEaTSnf5yJNYX2sHs6irpp598fkNVozk5FaSULBEkiRV1o5SbKgwm8upwUXvsogFBP1yphJSFSyKRWx42t9j99D3zxhteqARL",
      0);

void RunTest(const TestVector &test) {
    std::vector<unsigned char> seed = ParseHex(test.strHexMaster);
    CExtKey key;
    CExtPubKey pubkey;
    key.SetMaster(seed.data(), seed.size());
    pubkey = key.Neuter();
    for (const TestDerivation &derive : test.vDerive) {
        unsigned char data[74];
        key.Encode(data);
        pubkey.Encode(data);

        // Test private key
        CKusacoinExtKey b58key; b58key.SetKey(key);
        BOOST_CHECK(b58key.ToString() == derive.prv);

        CKusacoinExtKey b58keyDecodeCheck(derive.prv);
        CExtKey checkKey = b58keyDecodeCheck.GetKey();
        assert(checkKey == key); //ensure a base58 decoded key also matches

        // Test public key
        CKusacoinExtPubKey b58pubkey; b58pubkey.SetKey(pubkey);
        BOOST_CHECK(b58pubkey.ToString() == derive.pub);

        CKusacoinExtPubKey b58PubkeyDecodeCheck(derive.pub);
        CExtPubKey checkPubKey = b58PubkeyDecodeCheck.GetKey();
        assert(checkPubKey == pubkey); //ensure a base58 decoded pubkey also matches

        // Derive new keys
        CExtKey keyNew;
        BOOST_CHECK(key.Derive(keyNew, derive.nChild));
        CExtPubKey pubkeyNew = keyNew.Neuter();
        if (!(derive.nChild & 0x80000000)) {
            // Compare with public derivation
            CExtPubKey pubkeyNew2;
            BOOST_CHECK(pubkey.Derive(pubkeyNew2, derive.nChild));
            BOOST_CHECK(pubkeyNew == pubkeyNew2);
        }
        key = keyNew;
        pubkey = pubkeyNew;

        CDataStream ssPub(SER_DISK, CLIENT_VERSION);
        ssPub << pubkeyNew;
        BOOST_CHECK(ssPub.size() == 75);

        CDataStream ssPriv(SER_DISK, CLIENT_VERSION);
        ssPriv << keyNew;
        BOOST_CHECK(ssPriv.size() == 75);

        CExtPubKey pubCheck;
        CExtKey privCheck;
        ssPub >> pubCheck;
        ssPriv >> privCheck;

        BOOST_CHECK(pubCheck == pubkeyNew);
        BOOST_CHECK(privCheck == keyNew);
    }
}

BOOST_FIXTURE_TEST_SUITE(bip32_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(bip32_test1) {
    RunTest(test1);
}

BOOST_AUTO_TEST_CASE(bip32_test2) {
    RunTest(test2);
}

BOOST_AUTO_TEST_CASE(bip32_test3) {
    RunTest(test3);
}

BOOST_AUTO_TEST_SUITE_END()
