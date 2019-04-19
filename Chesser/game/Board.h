//#ifndef BOARDDEF_H
//#define BOARDDEF_H
//#pragma once
//
//#include <iostream>
//#include "move/MoveSet.h"
//#include "pieces/Pieces.h"
//#include "univ_includes.h"
//
// using namespace std;
//
// class Board {
//   public:
//    void Init();
//
//    void ApplyMove(Move move);
//
//    vector<vector<Piece*>>* GetBoard() { return &m_Board; }
//    MoveSet* GetMoveSet() { return &m_Moves; }
//    vector<string> GetMoveSetStr() {
//        vector<string> res;
//        int counter = 1;
//        for (Move* move : m_Moves)
//            res.push_back(to_string(counter) + move->mWhites.to_str() + " " +
//                          move->mBlacks.to_str());
//        return res;
//    }
//
//    Piece* operator[](const vector<int> x) {
//        if (x.size() > 2) return nullptr;
//
//        return m_Board[x[0]][x[2]];
//    }
//    Piece* operator[](const Cords* x) {
//        return m_Board[x->mOrig.rank][x->mOrig.file];
//    }
//
//    auto begin() { return m_Board.begin(); }
//    auto end() { return m_Board.end(); }
//
//    int size() { return m_Board.size(); };
//    auto get() { return m_Board; }
//
//    void print() {
//        for (int i = 0; i < m_Board.size(); i++) {
//            cout << i << ". ";
//            for (int j = 0; j < m_Board[i].size(); j++) {
//                char repr = ' ';
//                if (m_Board[i][j] == nullptr)
//                    repr == ' ';
//                else if (m_Board[i][j]->type == PieceTypes::_King)
//                    repr = 'K';
//                else if (m_Board[i][j]->type == PieceTypes::_Queen)
//                    repr = 'Q';
//                else if (m_Board[i][j]->type == PieceTypes::_Rook)
//                    repr = 'R';
//                else if (m_Board[i][j]->type == PieceTypes::_Bishop)
//                    repr = 'B';
//                else if (m_Board[i][j]->type == PieceTypes::_Knight)
//                    repr = 'N';
//                else if (m_Board[i][j]->type == PieceTypes::_Pawn)
//                    repr = 'P';
//
//                cout << "|" << repr << "|";
//            }
//            cout << endl;
//            if (i == m_Board.size() - 1) {
//                cout << "   ";
//                for (int j = 0; j < 8; j++) cout << "[" << j << "]";
//            }
//        }
//        cout << endl;
//        cout << endl;
//    }
//
//   private:
//    vector<vector<Piece*>> m_Board;
//    MoveSet m_Moves;
//    bool isWhite = true;
//};
//
//#endif