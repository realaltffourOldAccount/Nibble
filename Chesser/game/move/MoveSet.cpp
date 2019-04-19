//#include "MoveSet.h"
//
// void MoveSet::Insert(Move* move, int begin) {
//    auto it = mSet.begin();
//    std::advance(it, begin);
//    mSet.insert(it, move);
//}
// void MoveSet::InsertRange(vector<Move*> moves, int begin) {
//    for (int i = 0; i < moves.size(); i++) this->Insert(moves[i], begin + i);
//}
// void MoveSet::Delete(int begin) {
//    auto it = mSet.begin();
//    std::advance(it, begin);
//    mSet.erase(it);
//}
// void MoveSet::DeleteRange(int begin, int end) {
//    auto it1 = mSet.begin();
//    std::advance(it1, begin);
//    auto it2 = mSet.begin();
//    std::advance(it2, begin);
//    mSet.erase(it1, it2);
//}
// void MoveSet::push_back(Move* move) { mSet.push_back(move); }
// void MoveSet::push_front(Move* move) { mSet.push_front(move); }
// Move* MoveSet::pop_back() {
//    Move* res = *(mSet.end() - 1);
//    mSet.pop_back();
//}
// Move* MoveSet::pop_front() {
//    Move* res = *(mSet.begin());
//    mSet.pop_front();
//}
//
// void MoveSet::clear() { mSet.clear(); }