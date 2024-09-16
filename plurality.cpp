#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
struct CANDIDATE
{
    std::string name;
    int votes = 0;
};

// Array of candidates
std::vector<CANDIDATE> candidates;

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(const std::string &name);
void print_winner();

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        std::cerr << "Usage: plurality [candidate ...]\n";
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        std::cerr << "Maximum number of candidates is " << MAX << "\n";
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates.push_back({argv[i + 1], 0});
    }

    int voter_count;
    std::cout << "Number of voters: ";
    std::cin >> voter_count;

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        std::string name;
        std::cout << "Vote: ";
        std::cin >> name;

        // Check for invalid vote
        if (!vote(name))
        {
            std::cout << "Invalid vote.\n";
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(const std::string &name)
{
    // Check if the vote is valid
    for (auto &c : candidates)
    {
        if (c.name == name)
        {
            c.votes++;
            return true;
        }
    }
    return false;
}

// Print the winner(s) of the election
void print_winner()
{
    // Find the largest amount of votes
    int most_votes = std::max_element(candidates.begin(), candidates.end(),
                                      [](const CANDIDATE &a, const CANDIDATE &b)
                                      {
                                          return a.votes < b.votes;
                                      })
                         ->votes;

    // Print the winners
    for (const auto &c : candidates)
    {
        if (c.votes == most_votes)
        {
            std::cout << c.name << "\n";
        }
    }
}
