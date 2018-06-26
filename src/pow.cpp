// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2018 The Kusacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <pow.h>

#include <arith_uint256.h>
#include <chain.h>
#include <primitives/block.h>
#include <uint256.h>
#include <algorithm>

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params)
{
    assert(pindexLast != nullptr);

    if (params.fPowNoRetargeting)
        return pindexLast->nBits;

    arith_uint256 powLimit = UintToArith256(params.powLimit);

    // Special difficulty rule for testnet:
    // If the new block's timestamp is more than 2* 10 minutes
    // then allow mining of a min-difficulty block.
    if (params.fPowAllowMinDifficultyBlocks &&
        pblock->GetBlockTime() > pindexLast->GetBlockTime() + params.nPowTargetSpacing*2)
        return powLimit.GetCompact();

    //  Zawy's LWMA (Linearly Weighted Moving Average)
    //  https://github.com/zawy12/difficulty-algorithms/issues/3
    //  https://github.com/BTCGPU/BTCGPU/blob/426289533623d88c0881cab74c265790fb665043/src/pow.cpp
    const int height = pindexLast->nHeight + 1;
    const int N = params.nZawyLwmaAveragingWindow;
    const int64_t T = params.nPowTargetSpacing;

    int64_t solveTimeSum = 0;
    int64_t solveTimeDen = 0;
    arith_uint256 targetSum = 0;
    int targetNum = 0;

    int64_t solveTimeSum3 = 0;
    int solveTimeNum3 = 0;
    arith_uint256 targetPrev = 0;

    for (int i=1; i<=N; i++)
    {
        //  Different from the original implementation, calculate target for initial blocks too.
        if (height - N + i - 2 < 0)
            continue;
        const CBlockIndex *block = pindexLast->GetAncestor(height - N + i - 1);
        const CBlockIndex *blockPrev = pindexLast->GetAncestor(height - N + i - 2);

        int64_t solveTime = block->GetBlockTime() - blockPrev->GetBlockTime();
        solveTime = std::max(-3*T, std::min(solveTime, 6*T));
        solveTimeSum += i * solveTime;
        solveTimeDen += i;

        arith_uint256 target;
        target.SetCompact(block->nBits);
        //  Avoid overflow
        //  If target become too small, care will be needed
        target >>= 64;
        targetSum += target;
        targetNum++;

        if (i > N-3)
        {
            solveTimeSum3 += solveTime;
            solveTimeNum3++;
        }
        if (i == N)
            targetPrev = target;
    }
    solveTimeSum = std::max(solveTimeSum, T*N*N/40);

    arith_uint256 nextTarget = 0;
    if (targetNum > 0)
        //  next_target = (targetSum/targetNum) / (T / (solvetimeSum/solveTimeDen))
        nextTarget = targetSum * solveTimeSum / targetNum / solveTimeDen / T;
    else
        nextTarget = powLimit>>64;

    //  LWMA-2
    if (solveTimeNum3 == 3 &&
        solveTimeSum3 < T*8/10)
        nextTarget = targetPrev*100/110;

    nextTarget <<= 64;
    nextTarget = std::min(nextTarget, UintToArith256(params.powLimit));
    return nextTarget.GetCompact();
}

bool CheckProofOfWork(uint256 hash, unsigned int nBits, const Consensus::Params& params)
{
    bool fNegative;
    bool fOverflow;
    arith_uint256 bnTarget;

    bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

    // Check range
    if (fNegative || bnTarget == 0 || fOverflow || bnTarget > UintToArith256(params.powLimit))
        return false;

    // Check proof of work matches claimed amount
    if (UintToArith256(hash) > bnTarget)
        return false;

    return true;
}
