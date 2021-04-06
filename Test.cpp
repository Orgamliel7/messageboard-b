#include "doctest.h"
#include <string>
#include <experimental/random>
#include <unistd.h>
#include <algorithm>
using namespace std;
using namespace doctest;

#include "Board.hpp"
#include "Direction.hpp"
using namespace ariel;
/*
 יש לבדוק את הפונקציות post, read
 post - מקבלת מיקום (שורה וטור), כיוון (אופקי או אנכי), ומחרוזת המייצגת מודעה, ומדביקה את המחרוזת על הלוח במקום המתאים.
read-  מקבלת מיקום (שורה וטור), כיוון (אופקי או אנכי), ומספר תוים, קוראת את מה שכתוב על הלוח במיקום הנתון ובאורך הנתון, ומחזירה מחרוזת. האות הנמצאת בכל משבצת על הלוח היא האות האחרונה שהודבקה שם.
*/






TEST_CASE("Test board") // לוח ריק בלי מודעות אז נצפה לראות קו תחתון באורכים שונים
{
    Board board;
    CHECK(board.read(0, 0, Direction::Horizontal, 0) == string(""));
    CHECK(board.read(1, 1, Direction::Vertical, 0) == string(""));
    CHECK(board.read(2, 2, Direction::Horizontal, 1) == string("_"));
    CHECK(board.read(3, 3, Direction::Vertical, 5) == string("_____"));
}


TEST_CASE("Test Horizontal direction")
{
    Board board;
    board.post(1, 2, Direction::Horizontal, "Check");
    CHECK(board.read(1, 0, Direction::Horizontal, 2) == string("__"));
    CHECK(board.read(1, 0, Direction::Horizontal, 3) == string("__C"));
    CHECK(board.read(1, 2, Direction::Horizontal, 4) == string("Chec"));
    CHECK(board.read(1, 6, Direction::Horizontal, 1) == string("k"));

}

TEST_CASE("Test Vertical direction")
{
    Board board;
    board.post(1, 1, Direction::Vertical, " GTlosdlus");
    CHECK(board.read(1, 0, Direction::Horizontal, 2) == string("_G"));
    CHECK(board.read(2, 0, Direction::Horizontal, 3) == string("_T_"));
    CHECK(board.read(3, 1, Direction::Horizontal, 3) == string("l__"));
    CHECK(board.read(4, 0, Direction::Horizontal, 4) == string("_o__"));
    CHECK(board.read(4, 0, Direction::Vertical, 2) == string("__"));
   
}

