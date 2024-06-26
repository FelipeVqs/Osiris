#pragma once

#include <optional>

#include <GameClasses/Implementation/ConVarImpl.h>
#include "ConVars.h"

struct ConVarAccessorState {
    std::optional<bool> mp_teammates_are_enemies;
};

struct ConVarAccessor {
    explicit ConVarAccessor(const ConVars& conVars, const ConVarImpl& conVarImpl, ConVarAccessorState& state) noexcept
        : conVars{conVars}
        , conVarImpl{conVarImpl}
        , state{state}
    {
    }

    template <typename ConVar>
    [[nodiscard]] bool checkConVarType() const noexcept {
        static_assert(std::is_same_v<ConVar, cs2::mp_teammates_are_enemies>, "Invalid ConVar type");
        return std::is_same_v<ConVar, cs2::mp_teammates_are_enemies>;
    }

    template <typename ConVar>
    [[nodiscard]] bool checkAndGetConVar() const noexcept {
        if (!checkConVarType<ConVar>()) {
            return false;
        }

        if constexpr (std::is_same_v<ConVar, cs2::mp_teammates_are_enemies>) {
            if (state.mp_teammates_are_enemies.has_value()) {
                return true;
            }

            const auto conVar = conVars.getConVar<ConVar>();
            if (!conVar || !conVarImpl.offsetToConVarValue || !conVarIsBool(conVar)) {
                return false;
            }

            state.mp_teammates_are_enemies = readConVarValue<bool>(conVar);
            return true;
        }

        // Add other ConVar types here if needed

        return false;
    }

    template <typename ConVar>
    [[nodiscard]] bool getConVarValue() const noexcept {
        if constexpr (std::is_same_v<ConVar, cs2::mp_teammates_are_enemies>) {
            assert(state.mp_teammates_are_enemies.has_value());
            return *state.mp_teammates_are_enemies;
        }

        // Add other ConVar types here if needed

        return false;
    }

private:
    template <typename T>
    [[nodiscard]] T readConVarValue(cs2::ConVar* conVar) const noexcept {
        T value;
        std::memcpy(&value, conVarImpl.offsetToConVarValue.of(conVar).get(), sizeof(value));
        return value;
    }

    [[nodiscard]] bool conVarIsBool(cs2::ConVar* conVar) const noexcept {
        if (!conVarImpl.offsetToConVarValueType) {
            return true;
        }

        return cs2::ConVarValueType{*conVarImpl.offsetToConVarValueType.of(conVar).get()} == cs2::ConVarValueType::boolean;
    }

    const ConVars& conVars;
    const ConVarImpl& conVarImpl;
    ConVarAccessorState& state;
};
