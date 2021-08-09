#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <future>

#include "EnchantInfo.h"
#include "Item.h"
#include "Enchants Data.h"
#include "Timer.h"

#define OUTPUT 0

void Split(std::string str, std::string delim, std::vector<std::string>& split)
{
    split.clear();
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delim)) != std::string::npos)
    {
        token = str.substr(0, pos);
        split.push_back(token);
        str.erase(0, pos + delim.length());
    }
    split.push_back(str);
}

int Cost(Item& i1, Item& i2)
{
    int totalCost = 0;

    for (Enchant enchant : i2.enchants)
    {
        EnchantInfo info = enchants[static_cast<int>(enchant)];
        int multiplier = info.mul_item;
        if (i2.isBook)
        {
            multiplier = info.mul_book;
        }
        int cost = multiplier * info.max;
        totalCost += cost;
    }

    int targetPenalty = pow(2, i1.priorPenalty) - 1;
    int sacrificePenalty = pow(2, i2.priorPenalty) - 1;
    int penaltyCost = targetPenalty + sacrificePenalty;

    totalCost += penaltyCost;

    return totalCost;
}

bool Increment(std::vector<std::pair<int, int>>& p)
{
    int permSize = p.size();
    int pairIndex;
    for (pairIndex = 1; pairIndex < permSize; pairIndex++)
    {
        std::pair<int, int>& pair = p[permSize - 1 - pairIndex];
        if (pair.first == pairIndex + 1 && pair.second == pairIndex)
        {
            // Pair is max
            pair.first = 0;
            pair.second = 1;
        }
        else
        {
            // Increment current pair
            if (pair.second == pairIndex + 1)
            {
                pair.first++;
                if (pair.first == 1)
                {
                    pair.second = 2;
                }
                else
                {
                    pair.second = 1;
                }
            }
            else
            {
                if (pair.second == pair.first - 1)
                {
                    pair.second += 2;
                }
                else
                {
                    pair.second++;
                }
            }
            return true;
        }
    }

    return false;
}

void Branch(std::vector<Item>& originalItemSet, std::vector<std::pair<int, int>>& optPerm, std::vector<int>& costs, int& bestCost, int& bestOrderness, int threadNum, int threadIndex)
{
    int itemNum = originalItemSet.size();

    std::vector<std::pair<int, int>> perm;
    perm.reserve(itemNum - 1);
    for (int i = 0; i < itemNum - 1; i++)
    {
        perm.emplace_back(std::pair<int, int>(0, 1));
    }

    for (int inc = 0; inc < threadIndex; inc++)
    {
        if (!Increment(perm)) { return; }
    }

    int costSum, orderness;
    bestCost = 100000, bestOrderness = -1;
    std::vector<int> permCosts;
    std::vector<Item> itemSetSource;
    std::vector<Item*> itemSet;

    int totalIter = 1;
    for (int i = 2; i < originalItemSet.size(); i++)
    {
        totalIter *= i * i;
    }

    bool finished = false;
    int iter = threadIndex + 1;


    while (!finished)
    {
#if OUTPUT == 1
        if (threadIndex == 0)
        {
            if (iter % (threadNum * (10000 / threadNum) + 1) == 0)
            {
                //std::cout << std::setprecision(3) << "\r" << (float)100 * iter / totalIter << "%   ";

            }
        }
#endif

        itemSet.clear();
        permCosts.clear();
        itemSet.reserve(itemNum);
        permCosts.reserve(itemNum - 1);

        itemSetSource = originalItemSet;
        for (Item& i : itemSetSource) { itemSet.push_back(&i); }

        costSum = 0, orderness = 0;

        // Apply perm and calculate costs
        for (int n = 0; n < perm.size(); n++)
        {
            Item* target = itemSet[perm[n].first];
            Item* sacrifice = itemSet[perm[n].second];

            int levelCost = Cost(*target, *sacrifice);
            permCosts.push_back(levelCost);

            costSum += levelCost * (levelCost + 6);

            // Add all of sacrifice's enchants to target
            target->enchants.reserve(target->enchants.size() + sacrifice->enchants.size());
            for (Enchant sacrificeEnchant : sacrifice->enchants)
            {
                target->enchants.push_back(sacrificeEnchant);
            }
            target->priorPenalty = std::max(target->priorPenalty, sacrifice->priorPenalty) + 1;
            itemSet.erase(itemSet.begin() + perm[n].second);
        }

        // Calculate orderness
        for (int i = 0; i < itemSet[0]->enchants.size() - 1; i++)
        {
            if (enchants[static_cast<int>(itemSet[0]->enchants[i])].max >= enchants[static_cast<int>(itemSet[0]->enchants[i + 1])].max)
            {
                orderness++;
            }
        }
        if (itemSet[0]->enchants[itemSet[0]->enchants.size() - 1] == Enchant::Mending)
        {
            orderness++;
        }

        // Check if perm is the best yet
        if (costSum < bestCost || ((costSum == bestCost) && orderness > bestOrderness))
        {
            bestCost = costSum;
            bestOrderness = orderness;
            optPerm = perm;
            costs = permCosts;
        }

        // Increment perm (threadNum) times
        for (int inc = 0; inc < threadNum; inc++)
        {
            if (!Increment(perm))
            {
#if OUTPUT == 1
                std::cout << "Thread: " << threadIndex << " finished" << std::endl;
#endif
                return;
            }
            iter++;
        }
    }
}

void CombineOptimally(std::vector<Item>& originalItemSet, std::vector<std::pair<int, int>>& optPerm, std::vector<int>& costs)
{
    int totalIter = 1;
    for (int i = 2; i < originalItemSet.size(); i++)
    {
        totalIter *= i * i;
    }

    int hardThreads = std::thread::hardware_concurrency();
    int threadNum = std::min(hardThreads, totalIter);
    std::vector<std::thread> threads;
    threads.reserve(threadNum);

    std::vector<std::vector<std::pair<int, int>>> optPerms = std::vector<std::vector<std::pair<int, int>>>(threadNum);
    std::vector<int> totalCosts = std::vector<int>(threadNum);
    std::vector<int> ordernesses = std::vector<int>(threadNum);
    std::vector<std::vector<int>> optCostLists = std::vector<std::vector<int>>(threadNum);

    for (int t = 0; t < threadNum; t++)
    {
        threads.emplace_back(Branch, std::ref(originalItemSet), std::ref(optPerms[t]), std::ref(optCostLists[t]), std::ref(totalCosts[t]), std::ref(ordernesses[t]), threadNum, t);
    }

    for (int t = 0; t < threadNum; t++)
    {
        threads[t].join();
    }

    int bestCost = 100000;
    int bestOrderness = -1;
    for (int t = 0; t < threadNum; t++)
    {
        if (totalCosts[t] < bestCost || ((totalCosts[t] == bestCost) && ordernesses[t] > bestOrderness))
        {
            bestCost = totalCosts[t];
            bestOrderness = ordernesses[t];
            optPerm = optPerms[t];
            costs = optCostLists[t];
        }
    }
}

int main()
{
    std::vector<std::string> items = { "Sword", "Pickaxe", "Axe", "Shovel", "Helmet", "Chestplate", "Leggings", "Boots", "Bow", "Crossbow", "Trident", "Rod", "Shield", "Hoe" };

    std::cout << "Which item are you enchanting?" << std::endl << std::endl;
    for (int i = 0; i < items.size(); i++)
    {
        std::cout << i << ": " << items[i] << std::endl;
    }
    std::cout << "=========================" << std::endl;
    std::cout << "A: ";
    std::string itemIndexStr;
    
    getline(std::cin, itemIndexStr);
    //itemIndexStr = "0";


    std::cout << "=========================" << std::endl;

    std::string item = items[std::stoi(itemIndexStr)];

    std::cout << "Which enchantments would you like to apply?" << std::endl << std::endl;

    int index = 0;
    std::map<std::string, Enchant>::iterator it;
    for (it = enchantsStrMap.begin(); it != enchantsStrMap.end(); it++)
    {
        std::cout << index << ": " << it->first << std::endl;
        index++;
    }
    std::cout << "=========================" << std::endl;
    std::cout << "A: ";
    std::string enchantsListStr;


    getline(std::cin, enchantsListStr);
    //enchantsListStr = "Fire Aspect,Knockback,Looting,Mending,Sharpness,Sweeping Edge,Unbreaking";
    

    std::cout << "=========================" << std::endl;

    std::vector<std::string> enchantsSplitStr;
    Split(enchantsListStr, ",", enchantsSplitStr);

    std::vector<Item> itemSet;
    itemSet.emplace_back(Item(false, {}, 0));
    for (std::string enchant : enchantsSplitStr)
    {
        int currentIndex = 0;
        int enchIndex = std::stoi(enchant);
        std::map<std::string, Enchant>::iterator it;
        for (it = enchantsStrMap.begin(); it != enchantsStrMap.end(); it++)
        {
            if (currentIndex == enchIndex)
            {
                itemSet.emplace_back(Item(true, { it->second }, 0));
            }
            currentIndex++;
        }
    }

    std::vector<std::pair<int, int>> optPerm;
    std::vector<int> costs;

    Timer t;
    CombineOptimally(itemSet, optPerm, costs);
    t.Stop();

    std::cout << std::endl;
    std::cout << "Took: " << t.duration / 1000000.0 << "s" << std::endl;
    std::cout << std::endl;

    for (int n = 0; n < optPerm.size(); n++)
    {
        Item& target = itemSet[optPerm[n].first];
        Item& sacrifice = itemSet[optPerm[n].second];

        int lineLength = 0;
        std::string nStr = std::to_string(n + 1);
        std::cout << nStr << ": (";
        lineLength += nStr.size() + 3;

        if (target.isBook)
        {
            for (int e = 0; e < target.enchants.size(); e++)
            {
                std::cout << enchToStr[target.enchants[e]];
                lineLength += enchToStr[target.enchants[e]].size();
                if (e != target.enchants.size() - 1)
                {
                    std::cout << ",";
                    lineLength++;
                }
            }
        }
        else
        {
            std::cout << item;
            lineLength += item.size();
        }
        
        std::cout << ") + (";
        lineLength += 5;

        for (int e = 0; e < sacrifice.enchants.size(); e++)
        {
            lineLength += enchToStr[sacrifice.enchants[e]].size();
            std::cout << enchToStr[sacrifice.enchants[e]];
            if (e != sacrifice.enchants.size() - 1) 
            {
                std::cout << ",";
                lineLength += 1;
            }
        }
        std::cout << ")";
        lineLength++;
        for (int add = 0; add < 45 - lineLength; add++)
        {
            std::cout << " ";
        }
        std::cout << "|\t" << costs[n] << std::endl;

        // Add all of sacrifice's enchants to target
        for (Enchant sacrificeEnchant : sacrifice.enchants)
        {
            target.enchants.push_back(sacrificeEnchant);
        }
        itemSet.erase(itemSet.begin() + optPerm[n].second);
    }

    std::cin.get();
}