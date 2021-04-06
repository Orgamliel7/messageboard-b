#include <array>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;
#include "Board.hpp"
#include "Direction.hpp"
using ariel::Direction;
  
 




// מודרניזציה ללוח לאחר כל שינוי בו
void ariel::Board::modernizeBoundery(unsigned int horizontal, unsigned int vertical, Direction dir, unsigned int length)  //  עדכון גבולות של הלוח
{ // מקבלת אופקי , אנכי, כיוון ואורך של המילה
const int plusOneToLength = 1; // אם מדובר בכיוון אנכי/אופקי נוסיף אחד לאורך הכולל שלהם
     int lengthOfHorizontal = 0;  int lengthOfVertical = 0; // אתחול של משתנים שיחזיקו אורכים של אופקי ואנכי
    if(dir == Direction::Horizontal) // אם הכיוון אופקי
    {
        
        lengthOfHorizontal=(int)horizontal+plusOneToLength; //  אורך האופקי שווה לאופקי שהכנסנו בפונקציה פלוס  1 של הנוכחי כי הוא מוסיף רק את האות הראשונה 
        lengthOfVertical=(int)(length+vertical); // אורך המילה יתווסף למאונך 
    }
    else if(dir == Direction::Vertical) // אחרת אם הכיוון הוא אנכי
    {
        lengthOfHorizontal =(int)(horizontal+length); // המרה לאינט של האורך 
        lengthOfVertical =plusOneToLength+(int)vertical; // המרה פלוס אחד לאורך של מאוזן כי הוספנו לו שורה שמוסיפה אחד בדיוק ואת האורך עצמו למאוזן
    }

       if(this->horizontalBegin==INT32_MAX&&this->horizontalFinal==-1&&this->verticalBegin==INT32_MAX&&this->verticalFinal==-1) 
       { // אם הלוח ריק לגמרי, נקבע גבולות על פי המילה הראשונה שהוכנסה
        this->horizontalBegin = horizontal; // ההתחלה תהיה המאוזן שהכנסנו
        this->horizontalFinal = lengthOfHorizontal; // הסוף יהיה אורך המילה
        this->verticalBegin=vertical;
        verticalFinal = lengthOfVertical;
        board.insert(board.begin(),(unsigned int)horizontalFinal-horizontalBegin,"_"); // נשבץ שם משבצות ריקות עד שנכניס את המודעה שתדרוס

     }
     else // הלוח לא ריק
     {
        if (lengthOfHorizontal > horizontalFinal)  // נבדוק האם גודל האופקי הנתון בפונ גדול מגודל האופקי האחרון של הלוח
        {
             board.insert(board.end(),  ((unsigned int)lengthOfHorizontal - (unsigned int)horizontalFinal), "_"); //  _ אם כן , נשבץ 
            horizontalFinal = lengthOfHorizontal; // נעדכן את הגודל של הלוח להיות הגודל של האופקי
        }
        if(horizontal<horizontalBegin) // אם המיקום האופקי שהכנסנו קטן מנקודת ההתחלה של הלוח
        {
            board.insert(board.begin(), horizontalBegin - horizontal, "_");
            this->horizontalBegin=horizontal;
        }

        if (vertical < verticalBegin) 
        {
            verticalBegin = vertical;
        }
        if (lengthOfVertical > verticalFinal)  // נעשה אותו דבר עם האנכי
        {
            this->verticalFinal = lengthOfVertical;
        }
    }
    //פונקציה שמעדכנת את הגודל ע"פ מה שקבענו לה, אם גדול תרחיב, אם קטן תקצץ עד אליו. פה זה תמיד יגדיל 
        for (auto pointer = board.begin(); pointer < board.end(); pointer++) // נעבור על כל הלוח עם מצביע כדי לעשות את זה גם לאנכי
        {
            (*pointer).resize((unsigned int)verticalFinal-verticalBegin,'_'); // נכניס לכל משבצת ריקה קו תחתון כנדרש
        }
}
  // פרסום מודעה מאוזנת
void ariel::Board::horizontalPosterize(unsigned int horizontal, unsigned int vertical, const std::string& message) 
{
    board.at(horizontal-horizontalBegin).replace(vertical-verticalBegin,message.length(),message);
}
  // פרסום מודעה אנכית
void ariel::Board::verticalPosterize(unsigned int horizontal, unsigned int vertical, std::string message) 
{
    for (unsigned int i = 0; i <message.length() ; ++i) 
    {
        board.at(horizontal-horizontalBegin+i).at(vertical-verticalBegin)=message[i];
    }
}

// post מפרסמת מודעה חדשה ודורסת אחרת אם קיימת כבר כזו
void ariel::Board::post(unsigned int horizontal, unsigned int vertical, Direction dir, const string &message)
{ // לכן תקבל מיקום אופקי ומיקום אנכי, כיוון ואת ההודעה שנשלחת כרפנרס קבוע בכדי שלא תשתנה ונשלח רפרנס כדי שזו תהיה ההודעה ולא הכתובת
    switch (dir) // נבדוק את הכיוון קודם 
    {
        case Direction::Horizontal: //  אם זה אופקי
            modernizeBoundery(horizontal,vertical,dir,message.length()); // נעדכן את גבולות הלוח במקרה הצורך
            horizontalPosterize(horizontal,vertical,message); // נחליף את הכתוב בלוח במיקום המבוקש שהכנסנו ולכן נביא לו כמות תווים והמודעה עצמה 
            break;
        case Direction::Vertical:  //  אם זה אנכי
                       modernizeBoundery(horizontal,vertical,dir,message.length());
                       verticalPosterize(horizontal,vertical,message);
            break;
        default: // אם לא קיבלנו את אחד משני הכיוונים האפשריים כקלט
            throw out_of_range("please enter one of the two options: Horizontal or Vertical");
    }
}




 // פונקציה זו קוראת את ההודעה הכתובה בצורה אופקית ומחזירה אותה כפלט
string ariel::Board::HorizontalReader(unsigned int horizontal, unsigned int vertical, unsigned int lengthOfWord) 
{
vector<string> boardString(1,"_"); // נאתחל וקטור שיכיל מודעה , בסיסי בגודל אחד שייצג תו אחד ריק בלוח 
    boardString.at(0).resize(lengthOfWord,'_'); // נעדכן את גודלו להיות כאורך המודעה אותה נרצה לקרוא
    if(horizontal +1 > horizontalFinal || horizontal<horizontalBegin)// אם הפנו אותנו לאיטרטור שחורג מהמקסימום או לפני המינימום 
    {
        return boardString.at(0); // נחזיר תו ריק כי זה כלל לא בלוח
    }
    for (unsigned int i=0; i < lengthOfWord; ++i)  // אחרת, המיקום תקף ואפשר לעבור בלולאה כדי להדפיס
    {
        try // נעטוף בניסוי ותפיסה כי יכולה להיזרק שגיאת חריגה מגבולות
        {
            boardString.at(0).at(i)=board.at(horizontal-horizontalBegin).at(vertical-verticalBegin+i); // החזרת המודעה שנמצאת במיקום הנ"ל  
        } catch (const std::exception& e) 
        {
        }
    }
    return boardString.at(0);
}


  // פונקציה זו קוראת את ההודעה הכתובה בצורה אנכית ומחזירה אותה כפלט

string ariel::Board::VerticalReader(unsigned int horizontal, unsigned int vertical, unsigned int lengthOfWord) 
{
   vector<string> boardString(1,"_");
    boardString.at(0).resize(lengthOfWord,'_');
    if(vertical+1>(int)verticalFinal||vertical<verticalBegin){return boardString.at(0);
    }
    for (unsigned int i=0; i < lengthOfWord && horizontal+i<horizontalFinal; ++i) 
    {
        try 
        {
            boardString.at(0).at(i) = board.at(horizontal-horizontalBegin + i).at(vertical-verticalBegin);
        } catch (const std::exception& e) 
        {

        }
    }
    return boardString.at(0);
}

/**
 פונקציה זו תקרא לאחת מפונקציות העזר ותחזיר את הפלט שלהן, תלוי באיזה כיוון מדובר
 לכן נעביר להן את המיקום האנכי והאופקי, ואת אורך המודעה
 * return the text found in the coordination's, direction and length inputted by the user
 */
string ariel::Board::read(unsigned int horizontal, unsigned int vertical, Direction dir, unsigned int lengthOfWord) 
{
    switch (dir) // תלוי כיוון אופקי או אנכי שנדע באיזו צורה לקרוא 
    {
        case Direction::Horizontal:
            return HorizontalReader(horizontal,vertical,lengthOfWord);// נשלח לפונקציית העזר של קריאה מאוזנת
        case Direction::Vertical:
            return VerticalReader(horizontal,vertical,lengthOfWord); // נשלח לפונקציית העזר של קריאה אנכית
        default: 
            throw out_of_range("please enter one of the two options: Horizontal or Vertical");
    }
}

void ariel::Board::show()  // צפייה בלוח המודעות
{
      for (auto&item:board) // נעבור בלולאת פור מקוצרת  על כל השורות בלוח ובתוכן עם פוינטר אוטומטי
      {
           cout << string(item) << endl; // בכל אחד מהם נדפיס שורת מודעות בלוח לפי הסדר 
      }
}
        // מתוכן נדפיס מתוך כל וקטור אנכי את שורת המודעות הנוכחית ע"י שימוש  בפונקציית הסטרינג שתקבל מיקום איטרטור התחלתי ומיקום סופי 
      
        /*
            i= horizontal_start בהתחלה
           new apartment in Haifa! נראה את שורת המודעות הראשונה

           ואז באיטרציה השנייה של 
           new apartment in Haifa! 
           want to learn spanish in one month? call us +972524535
        */
    

