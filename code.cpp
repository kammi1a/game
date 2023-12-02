#include <iostream>
#include <vector>
#include <algorithm>

class MemoryGame {
public:
    MemoryGame(const std::vector<int>& numbers) : cards_(numbers), moves_(0) {
        cards_.insert(cards_.end(), numbers.begin(), numbers.end());
        std::random_shuffle(cards_.begin(), cards_.end());
        revealed_.resize(cards_.size(), false);
    }

    void play() {
        while (!allPairsMatched()) {
            displayBoard();
            int index1, index2;
            std::cout << "Enter two indixes to flip a pair of cards: ";
            std::cin >> index1 >> index2;

            if (isValidInput(index1) && isValidInput(index2) && index1 != index2) {
                flipCard(index1);
                flipCard(index2);
                moves_++;
            } else {
                std::cout << "The cards do not match. Try again.\n";
            }
        }

        std::cout << "Great! The cards are matched" << moves_ << " moves.\n";
    }

private:
    std::vector<int> cards_;
    std::vector<bool> revealed_;
    int moves_;

    bool allPairsMatched() const {
        return std::all_of(revealed_.begin(), revealed_.end(), [](bool isRevealed) { return isRevealed; });
    }

    void displayBoard() const {
        for (size_t i = 0; i < cards_.size(); ++i)
            std::cout << (revealed_[i] ? std::to_string(cards_[i]) : "[" + std::to_string(i) + "]") << ' ';
        std::cout << '\n';
    }

    bool isValidInput(int index) const {
        return index >= 0 && index < cards_.size() && !revealed_[index];
    }

    void flipCard(int index) {
        std::cout << "Card at index " << index << " is " << cards_[index] << '\n';
        revealed_[index] = true;
    }
};

int main() {
    std::vector<int> numbers = {1, 2, 3, 4};  // Customize as needed
    MemoryGame game(numbers);
    game.play();

    return 0;
}
