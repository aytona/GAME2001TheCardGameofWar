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

private:
	void Battle()
	{
		int _p1Card, _p2Card;
		_p1Card = _player1.front();
		_prizePool.push(_p1Card);
		_p2Card = _player2.front();
		_prizePool.push(_p2Card);

		if (_p1Card > _p2Card)
		{
			while (!_prizePool.isEmpty())
			{
				_player1.push(_prizePool.front());
			}
		}
		else
		{
			if (_p2Card > _p2Card)
			{
				while (!_prizePool.isEmpty())
				{
					_player2.push(_prizePool.front());
				}
			}
			else
			{
				for (int i = 0; i < 3; i++)
				{
					_prizePool.pop(_player1.front());
					_prizePool.pop(_player2.front());
				}
				Battle();
			}
		}
	}

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
		numBattles = 0;
		while (!gameOver)
		{
			try
			{
				numBattles = numBattles + 1;
				Battle();
			}
			catch (Queue exception)
			{
				gameOver = true;
			}
			if (numBattles == maxNumBattles)
			{
				gameOver = true;
				gameOK = false;
			}
		}
		return gameOK;
	}
};

int main()
{
	WarGame game;
	int numGames;
	int maxNumBattles;
	int numDiscont = 0;
	int numCompleted = 0;
	int totBattles = 0;

	cout << "How many games should be simluated? ";
	cin >> numGames;
	cout << "What is the maximum number of battles per game? ";
	cin >> maxNumBattles;
	
	game = new WarGame(maxNumBattles);
	for (int i = 0; i < numGames; i++)
	{
		if (game.Play())
		{
			numCompleted = numCompleted + 1;
			totBattles = totBattles + game.GetNumBattles();
		}
		else
		{
			numDiscont = numDiscont + 1;
		}
	}

	cout << "Number of Games Simulated: " << numGames << endl;
	cout << "Number of Discontinued Games: " << numDiscont << endl;
	cout << "Number of Completed Games: " << numCompleted << endl;

	if (numCompleted > 0)
	{
		cout << "In the completed games" << endl;
		cout << "\tTotal Number of Battles " << totBattles << endl;
		cout << "\tAverage Number of Battles " << totBattles / numCompleted << endl;
	}

	cout << "Program completed." << endl;
	return 0;
}