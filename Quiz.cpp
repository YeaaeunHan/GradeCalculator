// Create, Read, Update, Delete
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Quiz.h"
#include "commonFunctions.h"
using namespace std;
namespace yh {
   Quiz* quiz = nullptr;
   void Quiz::resetInfo() {
      m_courseCode=0;
      m_quizName=nullptr;
      m_unit[0]= 0;
      m_currentMark=-1; // possibly 0
      m_max=0;
   }

   //Quiz::Quiz(int num) {
   //   quiz = new Quiz[num];
   //}

   Quiz::Quiz() {
      resetInfo();
   }
 
   Quiz::Quiz(const char* quizName, double weighted, double currentMark, double max) {
      resetInfo();
      if (quizName!= nullptr) {
         setQuizName(quizName);
         setCurrentMark(currentMark);
         setMax(max);
         setWeighted(weighted);
      }
   }

   Quiz::~Quiz() {
      delete[] m_quizName;
      m_quizName = nullptr;
   }

   Quiz& Quiz::setQuizName(const char* quizName) {
      if (quizName != nullptr) {
         m_quizName = new char[strlen(quizName) + 1];
         strcpy(m_quizName, quizName);
      }
      return *this;
   }

   void Quiz::setUnit(const char unit) {
   }

   Quiz& Quiz::setCurrentMark(double mark) {
      if (mark > 0) {
         m_currentMark = mark;
      }
      return *this;
   }
   Quiz& Quiz::setWeighted(double weighted) {
      if (weighted > 0) {
         m_weighted = weighted;
      }
      return *this;
   }

   Quiz& Quiz::setMax(double maxMark) {
      if (maxMark > 0) {
         m_max = maxMark;
      }
      return *this;
   }

   const char* Quiz::getQuizName() const {
      return m_quizName;
   }
   double Quiz::getCurrentMark() const {
      return m_currentMark;
   }
   double Quiz::getMaxMark() const {
      return m_max;
   }
   double Quiz::getWeighted() const {
      return m_weighted;
   }
   double Quiz::getTotal() const {
      return (m_currentMark / m_max * m_weighted); 
   }


   void Quiz::remaingMarkToPass() {
   }


   void Quiz::display() const {
      cout << "Quiz Name : " << getQuizName() <<endl;
      cout << "Mark      : " << getCurrentMark() << endl;
      cout << "Max       : " << getMaxMark() << endl;
      cout << "Weighted  : " << getWeighted()<<endl;
      cout << "---------------------" << endl;
      cout.setf(ios::fixed);
      cout.precision(3);
      cout << "Total     : " << getTotal() <<  " % " << endl;
      cout.unsetf(ios::fixed);
      cout << endl;
   }

   void Quiz::isValid() const {
   }

}