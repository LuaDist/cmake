/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmCTestMultiProcessHandler_h
#define cmCTestMultiProcessHandler_h

#include <cmStandardIncludes.h>
#include <cmCTestTestHandler.h>
#include <cmCTestRunTest.h>

/** \class cmCTestMultiProcessHandler
 * \brief run parallel ctest
 *
 * cmCTestMultiProcessHandler 
 */
class cmCTestMultiProcessHandler 
{
public:
  struct TestSet : public std::set<int> {};
  struct TestMap : public std::map<int, TestSet> {};
  struct TestCostMap : public std::map<float, TestSet> {};
  struct PropertiesMap : public 
     std::map<int, cmCTestTestHandler::cmCTestTestProperties*> {};

  cmCTestMultiProcessHandler();
  virtual ~cmCTestMultiProcessHandler();
  // Set the tests
  void SetTests(TestMap& tests, PropertiesMap& properties);
  // Set the max number of tests that can be run at the same time.
  void SetParallelLevel(size_t);
  virtual void RunTests();
  void PrintTestList();

  void SetPassFailVectors(std::vector<cmStdString>* passed,
                          std::vector<cmStdString>* failed)
    {
    this->Passed = passed;
    this->Failed = failed;
    }
  void SetTestResults(std::vector<cmCTestTestHandler::cmCTestTestResult>* r)
  { this->TestResults = r; }

  void SetCTest(cmCTest* ctest) { this->CTest = ctest;}

  void SetTestHandler(cmCTestTestHandler * handler)
  { this->TestHandler = handler; }

  cmCTestTestHandler * GetTestHandler()
  { return this->TestHandler; }
protected:  
  cmCTest* CTest;
  // Start the next test or tests as many as are allowed by
  // ParallelLevel
  void StartNextTests();
  void StartTestProcess(int test);
  bool StartTest(int test);
  // Mark the checkpoint for the given test
  void WriteCheckpoint(int index);
  void WriteCostData(int index, float cost);
  void ReadCostData();
  void CreateTestCostList();
  // Removes the checkpoint file
  void MarkFinished();
  void EraseTest(int index);
  // Return true if there are still tests running
  // check all running processes for output and exit case
  bool CheckOutput();
  void RemoveTest(int index);
  //Check if we need to resume an interrupted test set
  void CheckResume();
  //Check if there are any circular dependencies
  bool CheckCycles();
  int FindMaxIndex();
  inline size_t GetProcessorsUsed(int index);
  // map from test number to set of depend tests
  TestMap Tests;
  TestCostMap TestCosts;
  //Total number of tests we'll be running
  size_t Total;
  //Number of tests that are complete
  size_t Completed;
  size_t RunningCount;
  //list of test properties (indices concurrent to the test map)
  PropertiesMap Properties;
  std::map<int, bool> TestRunningMap;
  std::map<int, bool> TestFinishMap;
  std::map<int, cmStdString> TestOutput;
  std::vector<cmStdString>* Passed;
  std::vector<cmStdString>* Failed;
  std::vector<cmCTestTestHandler::cmCTestTestResult>* TestResults;
  size_t ParallelLevel; // max number of process that can be run at once
  std::set<cmCTestRunTest*> RunningTests;  // current running tests
  cmCTestTestHandler * TestHandler;
};

#endif
