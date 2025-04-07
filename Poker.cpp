import random

suits = ['Hearts', 'Diamonds', 'Clubs', 'Spades']
ranks = ['2', '3', '4', '5', '6', '7', '8', '9', '10', 'Jack', 'Queen', 'King', 'Ace']

def create_deck():
    return [rank + ' of ' + suit for suit in suits for rank in ranks]

def deal_hand(deck, hand_size=5):
    return [deck.pop() for _ in range(hand_size)]

def show_hand(hand, name="Your hand"):
    print(f"{name}:")
    for i, card in enumerate(hand):
        print(f"{i + 1}: {card}")
    print()

def draw_cards(hand, deck, indices):
    for i in indices:
        hand[i] = deck.pop()
    return hand

def get_player_draw_choice():
    while True:
        choice = input("Enter card numbers to discard (e.g., 1 3 5), or press Enter to keep all: ")
        if not choice:
            return []
        try:
            indices = [int(x) - 1 for x in choice.split() if 1 <= int(x) <= 5]
            return list(set(indices))  # remove duplicates
        except ValueError:
            print("Invalid input. Please enter numbers between 1 and 5.")

def simple_ai_draw(hand):
    # Very basic AI: randomly replaces 0-3 cards
    count = random.randint(0, 3)
    return random.sample(range(5), count)

def main():
    print("Welcome to Five Card Draw Poker!")
    
    deck = create_deck()
    random.shuffle(deck)

    player_hand = deal_hand(deck)
    computer_hand = deal_hand(deck)

    show_hand(player_hand)

    # Player draw
    indices = get_player_draw_choice()
    draw_cards(player_hand, deck, indices)
    print("\nYour new hand:")
    show_hand(player_hand)

    # Computer draw
    comp_indices = simple_ai_draw(computer_hand)
    draw_cards(computer_hand, deck, comp_indices)

    # Reveal computer hand
    show_hand(computer_hand, "Computer's hand")

    # No hand ranking in this version
    print("Game over! (No hand ranking implemented — just for demo)")

if __name__ == "__main__":
    main()
