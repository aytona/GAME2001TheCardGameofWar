#include <iostream>
#include <stdlib.h>
#include "Queue.h"
using namespace std;

class RankDeck
{
private:
	static const int numCards = 52;

protected:
	int deck[numCards];
	int currentCard = 0;
	
public:
	RankDeck()
	{
		for (int i = 0; i < numCards; i++)
			deck[i] = i / 4;
	}
	// Shuffle current player's deck
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
	// Pop front element
	int DealNextCard()
	{
		currentCard = currentCard + 1;
		return (deck[currentCard - 1]);
	}
	// Check to see if there are more elements to pop
	bool DealMoreCards()
	{
		return (currentCard != numCards);
	}
};

class WarGame
{
private:
	Queue<int> _player1;
	Queue<int> _player2;
	int maxNumBattles;
	int numBattles = 0;
	RankDeck deck;
	Queue<int> _prizePool;
	static const int numCards = 52;
protected:

public:
	WarGame(int _maxNumBattles)
	{
		maxNumBattles = _maxNumBattles;
		deck = new RankDeck();
	}

	int GetNumBattles()
	{
		return numBattles;
	}

	bool Play()
	{
		_player1 = new Queue<int>(numCards);
		_player2 = new Queue<int>(numCards);
		_prizePool = new Queue<int>(numCards);
		bool gameOver = false;
		bool gameOK = true;
		deck.Shuffle();
		while (deck.DealMoreCards())
		{
			_player1.push(deck.DealNextCard());
			if (deck.DealMoreCards())
				_player2.push(deck.DealNextCard());
		}
	}
};

int main()
{
	
	return 0;
}