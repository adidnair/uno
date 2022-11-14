#include <bits/stdc++.h>
#include <vector>

const std::string values[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "+2", "", "", "", "+4"};
const std::string colors[] = {"124", "22", "19", "226;38;5;16", "16"};

class Card
{
    private:
        int value;        // {10 = +2, 11 = skip, 12 = reverse, 13 = wild, 14 = +4, 15 = NULL}
        int color;        // {0 = r, 1 = g, 2 = b, 3 = y, 4 = wild, 5 = NULL}
        Card *next;
        Card *prev;
        
    public:
        bool playable;
        Card(int value = 15, int color = 5, Card *prev = NULL)
        {
            this->value = value;
            this->color = color;
            this->prev = prev;
            playable = false;
        }

        void changeValues(int value, int color, Card *prev, Card *next)
        {
            this->value = value;
            this->color = color;
            this->prev = prev;
            this->next = next;
            playable = false;
        }

        void printCard()
        {
            std::cout << "\e[48;5;" << colors[color] << "m " << values[value] << " \e[0m";
        }

        void primPrintCard()
        {
            std::cout << colors[color] << "_" << values[value];
        }

        int getColor() {return color;}
        int getValue() {return value;}
        Card *getNext() {return next;}
        void setNext(Card* next) {this->next = next;} 
        Card *getPrev() {return prev;}
        void setPrev(Card* prev) {this->prev = prev;} 
};

Card *getNullCard(Card *prev)
{
    Card *nullCard = new Card(15, 5, prev);
    nullCard->setNext(NULL);
    return nullCard;
}

Card *constNullCard = getNullCard(NULL);

class Player
{
    private:
        std::string username;
        int score;
        Card *hand;

    public:
        Player(std::string username)
        {
            this->username = username;
            score = 0;
        }

        void setUsername(std::string username)
        {
            this->username = username;
        }

        std::string getUsername()
        {
            return username;
        }

        void setHand(Card *hand) {this->hand = hand;}
        Card *getHand() {return hand;}

        void addCard(Card *toAdd)
        {
            Card *check = hand;
            Card *prev = hand;
            while(check->getColor() < toAdd->getColor())
                check = check->getNext();
            while((check->getColor() == toAdd->getColor()) && check->getValue() < toAdd->getValue())
                check = check->getNext();
            return;
        }

        void showCards()
        {
            Card *point = hand->getNext();
            hand->printCard();
            while(point->getColor() != 5)
            {
                std::cout << ",  ";
                point->printCard();
                point = point->getNext();
            }
            std::cout << std::endl;
        }
};

class Deck
{
    private:
        int size;
        std::vector<Card*> deck;

    public:
        void shuffleDeck()
        {
            std::shuffle(deck.begin(), deck.begin() + size, std::default_random_engine(rand()));
        }

        Deck(Card* cards, int size)
        {
            this->size = size;
            deck.reserve(size);
            for (size_t i = 0; i < size; ++i)
            {
                deck[i] = cards;
                cards++;
            }                
        }

        void printDeck()
        {
            deck[0]->printCard();
            for (size_t i = 1; i < size; ++i)
            {
                std::cout << " ";
                deck[i]->printCard();
            }
            std::cout << std::endl;
        }

        void showDeck()
        {
            auto p = deck.begin();
            (*p)->printCard();
            ++p;
            for (size_t i = 1; i < size; ++i)
            {
                std::cout << " ";
                (*p)->printCard();
                ++p;
            }
            std::cout << std::endl;
        }
};




// Methods

Card *addDeck(Card *arr)
{
    for (size_t c = 0; c < 4; c++)
    {
        for (size_t v = 1; v < 26; v++)
        {
            arr->changeValues(v/2, c, NULL, NULL);
            arr++;
        }
        arr->changeValues(13, 4, NULL, NULL);
        arr++;
        arr->changeValues(14, 4, NULL, NULL);
        arr++;
    }
    return arr-1;
}















int main()
{
    // Set seed for random functions
    srand(time(0));


    int player_count;
    std::cout << "Enter the number of players: ";
    std::cin >> player_count;

    // Initialize
    int cardCount = 108 * (1 + (player_count / 4));
    Player *players[player_count];
    Card cards[cardCount];
    Card* pl = cards;
    
    for (size_t i = 0; i < cardCount/108; ++i)
        pl = addDeck(pl) + 1;


    Deck deck = Deck(cards, cardCount);

    std::string name;
    for (size_t i = 0; i < player_count; ++i)
    {
        std::cout << "Enter Player " << i+1 << " name: ";
        std::cin >> name;
        players[i] = new Player(name);
    }

    deck.shuffleDeck();
    deck.printDeck();
    deck.showDeck();
    
    std::cout << std::endl;
    return 0;
}
