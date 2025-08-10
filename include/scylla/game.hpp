// include/scylla/game.hpp
#pragma once

#include <cstdint>
#include <optional>

#include "scylla/chessboard.hpp"
#include "scylla/core/square.hpp"
#include "scylla/core/types.hpp"
#include "scylla/game_state.hpp"
#include "scylla/move.hpp"

namespace scy {

class GameHistory {
   public:
    constexpr GameHistory() = default;

    // Push new state and corresponding move
    constexpr void push(const GameState& state, const Move& move) {
        m_states.push_back(state);
        m_moves.push_back(move);
    }

    // Pop last state and move (ensure you check empty before calling)
    constexpr void pop() {
        if (!m_states.empty()) {
            m_states.pop_back();
        }

        if (!m_moves.empty()) {
            m_moves.pop_back();
        }
    }

    constexpr bool empty() const noexcept {
        return m_states.empty();
    }

    const GameState& last_state() const {
        return m_states.back();
    }

    const Move& last_move() const {
        return m_moves.back();
    }

    constexpr std::size_t size() const noexcept {
        return m_states.size();
    }

    // No default parameter here — caller must specify how many repetitions
    // to check for
    constexpr bool has_repeated(const GameState& state,
                                std::size_t times) const {
        int count = 0;
        for (const auto& s : m_states) {
            if (s == state) {
                ++count;
                if (count >= times) {
                    return true;
                }
            }
        }
        return false;
    }

    constexpr void clear() noexcept {
        m_states.clear();
        m_moves.clear();
    }

   private:
    std::vector<GameState> m_states;
    std::vector<Move> m_moves;
};

class Game {};

}  // namespace scy
