#pragma once

namespace sdl_message_box_type {

constexpr int INFORMATION = 0x0;
constexpr int ERROR = 0x10;
constexpr int WARNING = 0x20;
constexpr int QUESTION = 0x30;

} // namespace sdl_message_box_type

namespace sdl3 {

using message_box_type = int;

inline const message_box_type ERROR = sdl_message_box_type::ERROR;
inline const message_box_type WARNING = sdl_message_box_type::WARNING;

} // namespace sdl3
