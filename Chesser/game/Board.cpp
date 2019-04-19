//#include "Board.h"
//
// void Board::Init() {
//    // Black's Pieces
//    // Back row
//    vector<Piece*> blacks_backrow;
//    blacks_backrow.push_back(new Rook(false));
//    blacks_backrow.push_back(new Knight(false));
//    blacks_backrow.push_back(new Bishop(false));
//    blacks_backrow.push_back(new Queen(false));
//    blacks_backrow.push_back(new King(false));
//    blacks_backrow.push_back(new Bishop(false));
//    blacks_backrow.push_back(new Knight(false));
//    blacks_backrow.push_back(new Rook(false));
//
//    // Front row
//    vector<Piece*> blacks_frontrow;
//    for (int i = 0; i < 8; i++) blacks_frontrow.push_back(new Pawn(false));
//
//    m_Board.push_back(blacks_backrow);
//    m_Board.push_back(blacks_frontrow);
//
//    // Spaces
//    vector<Piece*> empty_row;
//    for (int i = 0; i < 8; i++) empty_row.push_back(nullptr);
//    for (int i = 0; i < 4; i++) m_Board.push_back(empty_row);
//    // White's Pieces
//    // Front Row
//    vector<Piece*> whites_frontrow;
//    for (int i = 0; i < 8; i++) whites_frontrow.push_back(new Pawn(true));
//
//    // Back Row
//    vector<Piece*> whites_backrow;
//    whites_backrow.push_back(new Rook(true));
//    whites_backrow.push_back(new Knight(true));
//    whites_backrow.push_back(new Bishop(true));
//    whites_backrow.push_back(new Queen(true));
//    whites_backrow.push_back(new King(true));
//    whites_backrow.push_back(new Bishop(true));
//    whites_backrow.push_back(new Knight(true));
//    whites_backrow.push_back(new Rook(true));
//
//    m_Board.push_back(whites_frontrow);
//    m_Board.push_back(whites_backrow);
//}