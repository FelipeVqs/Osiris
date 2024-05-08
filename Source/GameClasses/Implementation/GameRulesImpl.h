#pragma once

#include <MemoryPatterns/GameRulesPatterns.h>

struct GameRulesImpl {
private:
    explicit GameRulesImpl(const GameRulesPatterns& gameRulesPatterns) noexcept
        : roundStartTimeOffset{gameRulesPatterns.roundStartTimeOffset()} {}

    RoundStartTimeOffset roundStartTimeOffset;

public:
    static const GameRulesImpl& instance() noexcept {
        static GameRulesImpl instance{GameRulesPatterns::getDefault()};
        return instance;
    }

    [[nodiscard]] RoundStartTimeOffset getRoundStartTimeOffset() const noexcept {
        return roundStartTimeOffset;
    }

    static const GameRulesPatterns& getDefaultGameRulesPatterns() noexcept {
        return GameRulesPatterns::getDefault();
    }

    friend class GameRulesFactory;
};

class GameRulesFactory {
public:
    static const GameRulesImpl& getInstance() noexcept {
        return GameRulesImpl::instance();
    }

    static const GameRulesPatterns& getDefaultGameRulesPatterns() noexcept {
        return GameRulesImpl::getDefaultGameRulesPatterns();
    }
};
