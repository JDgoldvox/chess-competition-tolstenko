#pragma once
#include <string>
#include <MonteCarlo.h>

namespace ChessSimulator {
/**
 * @brief Move a piece on the board
 *
 * @param fen The board as FEN
 * @return std::string The move as UCI
 */
std::string Move(std::string fen);
} // namespace ChessSimulator