#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

/*
*  Update ranks given a new vote
*  Exact name matches only
*/
bool vote(int rank, string name, int ranks[])
{
    // look for candidate by name in candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        // if found, add index of candidate name to ranks[rank]
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

/*
*  Update preferences given one voter's ranks
*  Update preferences array with values at ranks[i] and ranks[j]
*/
void record_preferences(int ranks[])
{
    int winner, loser;
    for (int i = 0; i < candidate_count; i++)
    {
        winner = ranks[i];
        int j = i + 1;
        while (j < candidate_count)
        {
            loser = ranks[j];
            preferences[winner][loser]++;
            j++;
        }
    }
    return;
}

/*
*  Record pairs of candidates where one is preferred over the other
*  Create a pair if there is a diff, and add to pairs array
*  also increment pair count
*/
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                // candidate i is the winner
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }

        }
    }

    return;
}

/*
*  Sort pairs in decreasing order by strength of victory
*/
void sort_pairs(void)
{
    // need strength of victory for each pair
    int strength[pair_count];

    for (int i = 0; i < pair_count; i++)
    {
        strength[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }

    // selection sort was much simpler to handle with these two arrays
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (strength[i] < strength[j])
            {
                //swap appropriate pairs
                pair tmp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = tmp;

                //swap strength too
                int tmp2 = strength[i];
                strength[i] = strength[j];
                strength[j] = tmp2;
            }
        }
    }

    return;
}

// recursive check for cycles in locked
// return true if a cycle exists back to candidate
bool check_cycle(int index, bool visited[])
{
    if (visited[index])
    {
        return true;
    }
    // keep track of where we've visted
    visited[index] = true;
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[index][i] && check_cycle(i, visited))
        {
            return true;
        }
    }
    return false;
}

bool has_cycle(int index)
{
    bool visited[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        visited[i] = false;
    }
    return check_cycle(index, visited);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // update locked
    for (int i = 0; i < pair_count; i++)
    {
        int win = pairs[i].winner;
        int lose = pairs[i].loser;
        // set value to true
        locked[win][lose] = true;
        // if it wont create a cycle...
        if (has_cycle(i))
        {
            locked[win][lose] = false;
        }
    }
    return;
}

bool is_source(int index)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // if a candidate is locked over this one
        if (locked[i][index])
        {
            return false;
        }
    }
    return true;
}

// Print the winner of the election
// find candidate that is a source - meaning no one points to them
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (is_source(i))
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
