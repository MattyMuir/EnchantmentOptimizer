#include "Permutation.h"

#define HAS_DEST(pair) (pair.first == 0 || pair.second == 0)

decltype(Permutation::allSteps) Permutation::allSteps = decltype(Permutation::allSteps)();

bool Permutation::operator++()
{
start:
    for (int i = 0; i < steps.size(); i++)
    {
        if (steps[i] < allSteps[i].size() - 1)
        {
            steps[i]++;

            // Check if permutation is suitable
            bool prevHadTarget = false;
            for (int i = 0; i < steps.size(); i++)
            {
                if ((*this)[i].first == 0)
                {
                    prevHadTarget = true;
                }
                else
                {
                    if (prevHadTarget) goto start;
                }
            }
            return true;
        }
        else
        {
            steps[i] = 0;
        }
    }
    return false;
}

const std::pair<int, int>& Permutation::operator[](int n) const
{
    return allSteps[n][steps[n]];
}

void Permutation::Initialize(int size)
{
    steps.reserve(size);
    for (int i = 0; i < size; i++)
        steps.emplace_back(0);
}

void Permutation::LogSteps(const std::vector<Item>& itemSet_)
{
    // Make a copy of the itemSet
    auto itemSet = itemSet_;

    // Apply permutation and save each step & cost
    std::vector<std::string> lines;
    std::vector<int> costs;
    for (int stepIndex = 0; stepIndex < steps.size(); stepIndex++)
    {
        Item& target = itemSet[(*this)[stepIndex].first];
        Item& sacrifice = itemSet[(*this)[stepIndex].second];

        std::stringstream line;
        line << stepIndex + 1 << ": ";
        line << target.ToString() << " + " << sacrifice.ToString();

        lines.emplace_back(line.str());

        // Perform step of permutation
        costs.push_back(Item::CombineCost(target, sacrifice));
        target += sacrifice;
        itemSet.erase(itemSet.begin() + (*this)[stepIndex].second);
    }

    // Find longest line
    int longestLine = 0;
    for (const std::string& line : lines)
        if (line.size() > longestLine) longestLine = line.size();

    // Output lines and costs
    for (int i = 0; i < lines.size(); i++)
        std::cout << std::format("{:<{}}   {}\n", lines[i], longestLine + 3, costs[i]);
}

void Permutation::SetMaxLength(int maxLength)
{
    allSteps.clear();
    allSteps.reserve(maxLength + 1);

    // Start at n = 1, as when zero enchantments remain, there are no possible steps
    for (int n = maxLength; n > 0; n--)
    {
        allSteps.emplace_back();

        // Add all possible steps that include the target
        for (int i = 1; i <= n; i++)
            allSteps.back().emplace_back(0, i);

        // Add all permutations between two books
        for (int i1 = 1; i1 <= n; i1++)
        {
            for (int i2 = 1; i2 <= n; i2++)
            {
                if (i1 != i2)
                    allSteps.back().emplace_back(i1, i2);
            }
        }
    }
}