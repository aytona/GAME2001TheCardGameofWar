#include <iostream>
#include "Queue.h"
using namespace std;

class RankDeck
{
	// Need Container
public:
	RankDeck();
	void Shuffle()
	{

	}
	void DealNextCard()
	{

	}
	bool DealMoreCards()
	{
		return false;
	}
};

class WarGame
{
private:
	bool endType;
	int numBattles;
public:
	WarGame(int);
	void Play()
	{
		// Create 3 Queues (1 for each player(2), 1 for prize pile) - Enqueues (push)
		// Recursive Battle()
		endType = false;
		numBattles = 0;
	}
	void Battle()
	{
		// Must be recursive
		// Cycles until gameover or discontinued

		/* The algorithm for the battle is below:
		battle()		Get player1’s card from player1’s hand
		Put player1’s card in the prize pile
		Get player2’s card from player1’s hand
		Put player2’s card in the prize pile
		if (player1’s card > player2’s card)
		remove all the cards from the prize pile and put them in player2’s hand
		else //war!
		each player puts three cards in the prize pile
		battle() */
	}
};

int main()
{
	int numGames;
	cin >> numGames;
	int maxBattles;
	cin >> maxBattles;

	cout << "Number of games simulated: " << endl;
	cout << "Number of discontinued games: " << endl;
	cout << "Number of completed games: " << endl;
	cout << "- In the completed games -" << endl;
	cout << "Total number of battles: " << endl;
	cout << "Average number of battles: " << endl;
	cout << "Program completed" << endl;
	return 0;
}