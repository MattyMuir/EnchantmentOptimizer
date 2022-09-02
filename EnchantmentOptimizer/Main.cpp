#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <future>
#include <locale>
#include <ranges>

#include "Permutation.h"
#include "Timer.h"
#include "stringutility.h"

#define OUTPUT 1
#define HAS_DEST(pair) (pair.first == 0 || pair.second == 0)

#define THREAD_COUT(stream) { std::stringstream ss; ss << stream; std::cout << ss.str(); }

void Branch(const std::vector<Item>& originalItemSet, Permutation& optPerm, int& bestCost, int& bestOrderness, int threadNum, int threadIndex)
{
    int itemNum = originalItemSet.size();
#if OUTPUT
    uint64_t totalIter = 1;
    for (uint64_t i = 2; i < originalItemSet.size(); i++)
        totalIter *= i * i;

    totalIter /= 3;

    if (threadIndex == 0)
        THREAD_COUT("Total: " << FormatWithCommas(totalIter) << '\n');
#endif

    Permutation perm;
    perm.Initialize(itemNum - 1);

    // Increment perm to initial state
    for (int inc = 0; inc < threadIndex; inc++)
        if (!++perm) { return; }

    int costSum, orderness;
    bestCost = 100000, bestOrderness = -1;
    std::vector<Item> itemSetSource(originalItemSet);
    std::vector<Item*> itemSet;

    bool finished = false;
    uint64_t iter = threadIndex + 1;

    uint64_t nextmilestone = 10000;
    while (!finished)
    {
#if OUTPUT
        if (threadIndex == 0)
        {
            if (iter > nextmilestone)
            {
                //std::cout << "\rPermutations tested: " << FormatWithCommas(iter) << "         ";
                THREAD_COUT("\rProgress: " << (float)iter / totalIter * 100 << "%        ");
                nextmilestone += 10000;
            }
        }
#endif

        itemSet.clear();
        itemSet.reserve(itemNum);

        itemSetSource = originalItemSet;
        for (Item& i : itemSetSource) { itemSet.push_back(&i); }

        costSum = 0, orderness = 0;

        bool definitelyWorse = false;
        // Apply perm and calculate costs
        for (int n = 0; n < perm.steps.size(); n++)
        {
            auto pair = perm[n];
            Item* target = itemSet[pair.first];
            Item* sacrifice = itemSet[pair.second];

            int levelCost = Item::CombineCost(*target, *sacrifice);

            costSum += levelCost * (levelCost + 6);

            if (costSum > bestCost)
            {
                definitelyWorse = true;
                break;
            }

            // Add all of sacrifice's enchants to target
            *target += *sacrifice;
            itemSet.erase(itemSet.begin() + perm[n].second);
        }

        if (!definitelyWorse)
        {
            // Check if perm is the best yet
            if (costSum < bestCost)
            {
                bestCost = costSum;
                bestOrderness = orderness;
                optPerm = perm;
            }
            else if (costSum == bestCost)
            {
                // Calculate orderness
                for (int i = 0; i < itemSet[0]->enchants.size() - 1; i++)
                {
                    if ((itemSet[0]->enchants[i].max >= itemSet[0]->enchants[i + 1].max))
                        orderness++;
                }

                if (orderness > bestOrderness)
                {
                    bestCost = costSum;
                    bestOrderness = orderness;
                    optPerm = perm;
                }
            }
        }

        // Increment perm (threadNum) times
        for (int inc = 0; inc < threadNum; inc++)
        {
            if (!++perm)
            {
#if OUTPUT
                THREAD_COUT("Thread: " << threadIndex << " finished" << std::endl);
#endif
                return;
            }
            iter++;
        }
    }
}

void CombineOptimally(std::vector<Item>& originalItemSet, Permutation& optPerm)
{
    // Calculate total number of iterations
    uint64_t totalIter = 1;
    for (uint64_t i = 2; i < originalItemSet.size(); i++)
        totalIter *= i * i;

    uint64_t hardThreads = std::thread::hardware_concurrency() - 1;
    uint64_t threadNum = std::min(hardThreads, totalIter);

    // Prepare output values for the threads
    std::vector<Permutation> optPerms = std::vector<Permutation>(threadNum);
    std::vector<int> totalCosts = std::vector<int>(threadNum);
    std::vector<int> ordernesses = std::vector<int>(threadNum);

    // Run threads
    std::vector<std::thread> threads;
    threads.reserve(threadNum);
    for (int t = 0; t < threadNum; t++)
        threads.emplace_back(Branch, std::ref(originalItemSet), std::ref(optPerms[t]), std::ref(totalCosts[t]), std::ref(ordernesses[t]), threadNum, t);

    // Wait for threads
    for (int t = 0; t < threadNum; t++)
        threads[t].join();

    // Select best overall result
    int bestCost = 100000;
    int bestOrderness = -1;
    for (int t = 0; t < threadNum; t++)
    {
        if (totalCosts[t] < bestCost || ((totalCosts[t] == bestCost) && ordernesses[t] > bestOrderness))
        {
            bestCost = totalCosts[t];
            bestOrderness = ordernesses[t];
            optPerm = optPerms[t];
        }
    }
}

std::vector<Item> GenerateItemSet(const std::string& enchantsListStr)
{
    std::vector<Item> itemSet;
    itemSet.push_back({ false, {}, 0 });

    auto enchantsSplitStr = Split(enchantsListStr, ",");

    for (const auto& idStr : enchantsSplitStr)
        itemSet.emplace_back(Enchantment(std::stoi(idStr)));

    return itemSet;
}

void ModifyItemSetlevels(std::vector<Item>& itemSet)
{
    std::cout << "Enter new levels: \n";
    for (Item& item : itemSet)
    {
        if (item.isBook)
        {
            std::cout << item.enchants[0].ToString() << ": ";

            std::string res;
            std::getline(std::cin, res);

            int newLevel = std::stoi(res);
            item.prior = newLevel - item.enchants[0].max;
        }
    }
}

int main()
{
    std::cout << "Which enchantments would you like to apply?" << std::endl << std::endl;
    Enchantment::LogAllEnchants();
    std::cout << "=========================" << std::endl;
    std::cout << "A: ";

    std::string enchantsListStr;
    getline(std::cin, enchantsListStr);
    //enchantsListStr = "10,17,21,31,33,35,37,38,39";
    //enchantsListStr = "7,9,21,26,34,36,37,40,42";

    std::cout << "=========================" << std::endl;

    // Generate item set
    std::vector<Item> itemSet = GenerateItemSet(enchantsListStr);
    Permutation::SetMaxLength(itemSet.size() - 1);

    std::cout << "Are all enchants the standard level? (y/n): ";

    std::string res;
    getline(std::cin, res);
    if (res == "n")
        ModifyItemSetlevels(itemSet);

    TIMER(calc);
    Permutation optPerm;
    CombineOptimally(itemSet, optPerm);
    STOP_LOG(calc);

    // Print final result
    freopen("log.log", "w", stdout);
    optPerm.LogSteps(itemSet);
    std::cout << std::flush;
}