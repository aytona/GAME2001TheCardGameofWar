#include <iostream>
#include <stdlib.h>
#include <queue>
using namespace std;

// Model a deck of cards
class RankDeck
{
private:

	static const int numCards = 52;

protected:

	// Should contain a container for the cards
	int deck[numCards];
	int currentCard = 0;
	
public:

	// Constructor
	RankDeck()
	{
		for (int i = 0; i < numCards; i++)
			deck[i] = i / 4;
	}

	// shuffle method
	void Shuffle()
	{
		int randLoc, temp;
		for (int i = (numCards - 1); i > 0; i--)
		{
			randLoc = rand() % i;
			temp = deck[randLoc];
			deck[randLoc] = deck[i];
			deck[i] = temp;
		}
		currentCard = 0;
	}
	// dealNextCard method
	int DealNextCard()
	{
		currentCard = currentCard + 1;
		return (deck[currentCard - 1]);
	}
	
	// and a boolean method that indicates if there are more cards to be dealt
	bool DealMoreCards()
	{
		return (currentCard != numCards);
	}
};

// Simluates a game of War
class WarGame
{
private:
	queue<int> *_player1;
	queue<int> *_player2;
	queue<int> *_prizePool;
	RankDeck *deck;
	int maxNumBattles;
	int numBattles = 0;
	const int numCards = 52;

public:
	
	// Its constructor takes an argument indicating the maximum number of battles permitted before discontinuing a game
	WarGame(int _maxNumBattles)
	{
		maxNumBattles = _maxNumBattles;
		deck = new RankDeck();
	}

	/* play method that simulates a game until is finished or discontinued,
	returning a true if the game finishes normally or false if it is discontinued */
	bool Play()
	{
		// When invoked, must create three queues
		queue<int> *_player1 = new queue<int>;
		queue<int> *_player2 = new queue<int>;
		queue<int> *_prizePool = new queue<int>;

		// Shuffles the deck and deals the cards to the players
		deck->Shuffle();
		while (deck->DealMoreCards())
		{
			_player1->push(deck->DealNextCard());
			if (deck->DealMoreCards())
				_player2->push(deck->DealNextCard());
		}

		/* Once the cards are dealt, the play method calls the recursive battle method,
		which enacts the battle between the players->*/
		bool finished, discontinued = false;		// finished to check if the game finished, discontinued returns if the game was discontinued or not
		do
		{
			numBattles = numBattles + 1;
			Battle();

			// If every single battle did not discontinue
			if (numBattles == maxNumBattles)
			{
				finished = true;
				discontinued = false;
			}
		} while (!finished);
		return discontinued;
	}

	// Method that returns the number of battles waged in the most recent game
	int GetNumBattles()
	{
		return numBattles;
	}

	// This cycle continues until the game is over or discontinued
	void Battle()
	{
		int _p1Card, _p2Card;

		_p1Card = _player1->front();	// Get player1's card from hand/top card
		_prizePool->push(_p1Card);		// Put player1's card in the prize pile
		_p2Card = _player2->front();	// Get player2's card from hand/top
		_prizePool->push(_p2Card);		// Put player2's card in the prize pile

		// If player1 wins
		if (_p1Card > _p2Card)
		{
			while (!_prizePool->empty())
			{
				_player1->push(_prizePool->front());
			}
		}

		// If player2 wins
		if (_p2Card > _p2Card)
		{
			while (!_prizePool->empty())
			{
				_player2->push(_prizePool->front());
			}
		}
		
		// else if its a tie
		else
		{
			// Put player1's and player2's top 3 cards in the prize pile
			for (int i = 0; i < 3; i++)
			{
				_prizePool->push(_player1->front());
				_prizePool->push(_player2->front());
			}
			
			// Loop through battle to declare a winner
			Battle();
		}
	}
};

int main()
{
	int numGames;
	int maxNumBattles;

	cout << "How many games should be simluated? ";
	cin >> numGames;
	cout << "What is the maximum number of battles per game? ";
	cin >> maxNumBattles;

	// Construct wargame
	WarGame warGame(maxNumBattles);

	// Statistics declerations
	int totalDiscontinued = 0;
	int totalCompleted = 0;
	int totalBattles = 0;

	for (int i = 0; i < numGames; i++)
	{
		if (warGame.Play())
		{
			totalCompleted = totalCompleted + 1;
			totalBattles = totalBattles + warGame.GetNumBattles();
		}
		else
		{
			totalDiscontinued = totalDiscontinued + 1;
		}
	}

	// Statistics
	cout << "Number of Games Simulated: " << numGames << endl;
	cout << "Number of Discontinued Games: " << totalDiscontinued << endl;
	cout << "Number of Completed Games: " << totalCompleted << endl;
	// If at least 1 game has successfully completed
	if (totalCompleted > 0)
	{
		cout << "In the completed games" << endl;
		cout << "\tTotal Number of Battles " << totalBattles << endl;
		cout << "\tAverage Number of Battles " << totalBattles / totalCompleted << endl;
	}

	cout << "Program completed" << endl;
	return 0;
}