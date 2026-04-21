#include <cs50.h>
#include <stdio.h>
#include<string.h>

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
} pair;

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

bool creates_cycle(int winner, int loser);


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

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        int current_candidate = ranks[i];

        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[current_candidate][ranks[j]] += 1;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (i == j)
            {
                continue;
            }

            pair pair;

            int first_candidate = preferences[i][j];
            int second_candidate = preferences[j][i];

            if (first_candidate > second_candidate)
            {
                pair.winner = i;
                pair.loser = j;
            }
            else if (first_candidate < second_candidate)
            {
                pair.winner = j;
                pair.loser = i;
            }
            else
            {
                continue;
            }
            pairs[pair_count] = pair;
            pair_count += 1;
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        pair biggest_pair = pairs[i];
        int pair_to_trade_position = i;
        int biggest_diff = preferences[biggest_pair.winner][biggest_pair.loser] - preferences[biggest_pair.loser][biggest_pair.winner];
        for (int j = i + 1; j < pair_count; j++)
        {
            int current_diff = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            if (current_diff > biggest_diff)
            {
                biggest_diff = current_diff;
                biggest_pair = pairs[j];
                pair_to_trade_position = j;
            }
        }
        pair aux = biggest_pair;
        pairs[pair_to_trade_position] = pairs[i];
        pairs[i] = aux;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {

        pair current_pair = pairs[i];

        bool create_cycle = creates_cycle(current_pair.winner, current_pair.loser);

        if (create_cycle)
        {
            continue;
        }

        locked[current_pair.winner][current_pair.loser] = true;
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    int winner;
    for (int i = 0; i < pair_count; i++)
    {
        winner = i;
        for (int j = 0; j < pair_count; j++)
        {
            if (locked[j][i])
            {
                break;
            }
            winner = j;
        }

    }
    printf("%s\n", candidates[winner]);

    return;
}

bool creates_cycle(int winner, int loser)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (i == winner)
            {
                return true;
            }
            else
            {
                creates_cycle(winner, i);
            }
        }
    }
    return false;
}


