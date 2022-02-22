// Create, Read, Update, Delete
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include "Grade.h"
#include "commonFunctions.h"
using namespace std;
namespace yh {
   // Sete assessement Weight
   double eachWeight;
   double allWeight;
   double quizEachWeight=1;
   double quizAllWeight;
   double assignEachWeight = 1;
   double assignAllWeight;
   double testEachWeight = 1;
   double testAllWeight;
   Grade* grades = nullptr;

   void Grade::resetInfo() {
      m_courseCode[0] = '\0';
      m_week = 0;
      m_title=nullptr;
      m_score=-1; // possibly 0
      m_fullMark=0;
      m_type = 'N'; // None
   }

   Grade::Grade() {
      resetInfo();
   }
 
   Grade::Grade(const char* courseCode, int week, const char* title, char type, double score, double fullMark) {
      resetInfo();
      if (title!= nullptr) {
         strcpy(m_courseCode, courseCode);
         m_week = week;
         setTitle(title);
         m_type = type;
         setScore(score);
         setFullMark(fullMark);
         m_type = type;
      }
   }

   void Grade::deallocate() {
      delete[] m_title;
      m_title = nullptr;
   }

   Grade::~Grade() {
      deallocate();
   }
   Grade::Grade(const Grade& toCopyFrom) {
      strcpy(m_courseCode, toCopyFrom.m_courseCode);
      m_week = toCopyFrom.m_week;
      deallocate();
      setTitle(toCopyFrom.m_title);
      setScore(toCopyFrom.m_score);
      setFullMark(toCopyFrom.m_fullMark);
      m_type = toCopyFrom.m_type;
    
   }
   Grade& Grade::operator=(const Grade& toCopyFrom) {
      if (this != &toCopyFrom) {
         strcpy(m_courseCode, toCopyFrom.m_courseCode);
         m_week = toCopyFrom.m_week;
         deallocate();
         setTitle(toCopyFrom.m_title);
         setScore(toCopyFrom.m_score);
         setFullMark(toCopyFrom.m_fullMark);
         m_type = toCopyFrom.m_type;
      }
      return *this;
   }
   Grade& Grade::setInfo(const char* courseCode, int week, const char* title, char type, double score, double fullMark) {
      resetInfo();
      if (title != nullptr) {
         strcpy(m_courseCode, courseCode);
         m_week = week;
         setTitle(title);
         setScore(score);
         setFullMark(fullMark);
         m_type = type;
      }
      return *this;
   }

   Grade& Grade::setTitle(const char* title) {
      if (title != nullptr) {
         m_title = new char[strlen(title) + 1];
         strcpy(m_title, title);
      }
      return *this;
   }

   Grade& Grade::setScore(double score) {
      if (score > 0) {
         m_score = score;
      }
      return *this;
   }

   Grade& Grade::setFullMark(double fullMark) {
      if (fullMark > 0 && fullMark<=100) {
         m_fullMark = fullMark;
      }
      return *this;
   }

   int Grade::getWeek() const {
      return m_week;
   }
   const char* Grade::getTitle() const {
      return m_title;
   }
   double Grade::getScore() const {
      return m_score;
   }
   double Grade::getFullMark() const {
      return m_fullMark;
   }

   double Grade::getWeightedScore() const {
      // if Q, A, T , assign eachweight differently
      if (m_type == 'Q') {
         eachWeight = quizEachWeight;
         allWeight = quizAllWeight;
      }
      else if (m_type == 'A') {
         eachWeight = assignEachWeight;
         allWeight = assignAllWeight;
      }
      else if (m_type == 'T') {
         eachWeight = testEachWeight;
         allWeight = testAllWeight;
      }
      return (m_score/ m_fullMark * eachWeight); 
   }

   ostream& Grade::display() const {
      cout << "Week   | #" << getWeek() << endl;
      cout << "Title  | " << getTitle() <<endl;
      cout << "Score  | " << getScore() << endl;
      cout << "Out of | " << getFullMark() << endl;
      cout.setf(ios::fixed);
      cout.precision(3);
      cout << "Weighted  | " << eachWeight <<endl;
      cout << "---------------------" << endl;
      cout.precision(3);
      cout << "Total     : " << getWeightedScore() <<  " % " << endl;
      cout.unsetf(ios::fixed);
      cout << endl;
      return cout;
   }

   bool Grade::isValid() const {
      return (m_type == 'T' || m_type == 'Q'|| m_type == 'A') && m_score>0;
   }

   void readGrades(int& numGrades, double& totalScore, const char* searchSubject) {
      bool finished = false;
      //int numGrades = 0;
      FILE* fptr = nullptr;
      fptr = fopen("grade.csv", "r");
      if (fptr != nullptr) {
         // Read comma deliminated file
         char title[20];
         char type;
         int week;
         double score = 0, fullMark = 0;
         int sizeGrades = 5;
         grades = new Grade[static_cast<__int64>(sizeGrades)];

         while (fscanf(fptr, "%[^,],%d,%c,%lf,%lf\n", title, &week, &type, &score, &fullMark) == 5) {
            if (numGrades == sizeGrades) {
               Grade* tempGrades = nullptr;
               tempGrades = new Grade[static_cast<__int64>(sizeGrades) + numGrades];
               for (int i = 0; i < sizeGrades; i++) {
                  tempGrades[i] = grades[i];
               }
               delete[] grades;
               grades = tempGrades; // copy assignment needed
               sizeGrades += numGrades;
            }
            grades[numGrades].setInfo(searchSubject, week, title, type, score, fullMark);
            numGrades++;
         }
         // Close file
         fclose(fptr);
         fptr = nullptr;
         for (int i = 0; i < numGrades; i++) {
            totalScore += grades[i].getWeightedScore();
         }
      }
      else {
         cout << "ERROR: GRADE FILE INACCESIBLE";
      }
     // return grades;
   }

   void readWeightSetting(const char* searchSubject) {
      char subject[10] = { '\0' };
      double tempOneQuizWeight=0;
      double tempAllQuizWeight=0;
      double tempOneAssignWeight = 0;
      double tempAllAssignWeight = 0;
      double tempOneTestWeight = 0;
      double tempAllTestWeight = 0;

      FILE* fptr = nullptr;
      fptr = fopen("assessmentWeight.csv", "r");
      if (fptr != nullptr) {
         while (fscanf(fptr, "%[^,],%lf,%lf,%lf,%lf,%lf,%lf\n", subject, &tempOneQuizWeight, &tempAllQuizWeight, &tempOneAssignWeight, &tempAllAssignWeight, &tempOneTestWeight, &tempAllTestWeight) == 7) {
            if (strstr(subject, searchSubject) != nullptr) {
               quizEachWeight = tempOneQuizWeight;
               quizAllWeight = tempAllQuizWeight;
               assignEachWeight = tempOneAssignWeight;
               assignAllWeight = tempAllAssignWeight;
               testEachWeight = tempOneQuizWeight;
               testAllWeight = tempAllQuizWeight;
            }
         }
         fclose(fptr);
         fptr = nullptr;
      }
      else {
         cout << "ERROR: WEIGHT SETTING FILE INACCESIBLE";
      }
   }

   void modifyQuizWeightSetting(const char* searchSubject) {
      cout << "Quiz Weight for " << searchSubject << endl;
      cout << "=======================" << endl;
      cout.setf(ios::fixed);
      cout.precision(3);
      cout << "Each quiz weight : " << quizEachWeight << " %" <<endl;
      cout.unsetf(ios::fixed);
      cout << "Total quiz weight: " << quizAllWeight << " %" << endl << endl;

      cout << "Modify Quiz Weight for " << searchSubject<<"(0. exit)" << endl;
      cout << "=======================" << endl;
      cout << "Each quiz weight: ";
      cin >> eachWeight;
      if (eachWeight != 0) {
         cout << "Total quiz weight: ";
         cin >> quizAllWeight;
      }
      cout << endl;
   }  

   void displayData(const int numGrades) {
      double total = 0;
      if(numGrades > 0){
         cout << "Week     | ";
         for (int i = 0; i < numGrades; i++) {
            cout << setw(7);
            cout << "#" << grades[i].getWeek();
         }
         cout << endl;
         cout << "Title    | ";
         for (int i = 0; i < numGrades; i++) {
            cout << setw(8);
            cout << grades[i].getTitle();
         }
         cout << endl;

         cout << "Score    | ";
         for (int i = 0; i < numGrades; i++) {
            cout << setw(6);
            cout << grades[i].getScore()<<"/"<< grades[i].getFullMark();
         }
         cout << endl;
         //cout << "Max      | ";
         //for (int i = 0; i < numGrades; i++) {
         //   cout << setw(8);
         //   cout << grades[i].getFullMark();
         //}
         //cout << endl;
         cout << "Weighted | ";
         for (int i = 0; i < numGrades; i++) {
            cout.setf(ios::fixed);
            cout.precision(3);
            cout << setw(8);
            cout << quizEachWeight;
            cout.unsetf(ios::fixed);
         }
         cout << endl;
         cout << "---------------------" << endl;
         cout << "Grade    : ";
         for (int i = 0; i < numGrades; i++) {
            cout.setf(ios::fixed);
            cout.precision(3);
            cout << setw(8);
            cout << grades[i].getWeightedScore();
            cout.unsetf(ios::fixed);
         }
         cout << endl;
         for (int i = 0; i < numGrades; i++) {
            total += grades[i].getWeightedScore();
         }
         cout << "TOTAL: " << total << " / "<< allWeight<<" %" << endl << endl;
      }
      else {
         cout << "No data found. Return to menu." << endl;
      }
   }

   //void setQuiz() {
   //   int numQuiz;
   //   char quizName[20];
   //   double score, max; //, weighted
   //   double total = 0;
   //   Quiz* quiz = nullptr;
   //   cout << "How many Quiz to add? ";
   //   cin >> numQuiz;
   //   quiz = new Quiz[numQuiz];
   //   for (int i = 0; i < numQuiz; i++) {
   //      cout << "Quiz Name : ";
   //      cin >> quizName;
   //      cout << "Score     : ";
   //      cin >> score;
   //      cout << "Max       : ";
   //      cin >> max;
   //      //cout << "Weighted  : ";
   //      //cin >> weighted;
   //      cout << endl;
   //      quiz[i].setInfo(quizName, score, max);
   //   }
   //   for (int i = 0; i < numQuiz; i++) {
   //      quiz[i].display() << endl;
   //   }

   //   for (int i = 0; i < numQuiz; i++) {
   //      total += quiz[i].getTotal();
   //   }
   //   cout << "QUIZ TOTAL: " << total << " / "<< maxWeight<< " %" << endl << endl;
   //   FILE* fptr = nullptr;
   //   fptr = fopen("quiz.csv", "w");
   //   if (fptr != nullptr) {
   //      for (int i = 0; i < numQuiz; i++) {
   //         fprintf(fptr, "%s,%lf,%lf,%lf\n", quiz[i].getQuizName(), eachWeight, quiz[i].getCurrentMark(), quiz[i].getMaxMark());
   //      }
   //      fclose(fptr);
   //      fptr = nullptr;
   //   }
   //   else {
   //      cout << "ERROR: Can not write the data" << endl;
   //   }
   //}

}