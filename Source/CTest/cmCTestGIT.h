/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc.

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmCTestGIT_h
#define cmCTestGIT_h

#include "cmCTestGlobalVC.h"

/** \class cmCTestGIT
 * \brief Interaction with git command-line tool
 *
 */
class cmCTestGIT: public cmCTestGlobalVC
{
public:
  /** Construct with a CTest instance and update log stream.  */
  cmCTestGIT(cmCTest* ctest, std::ostream& log);

  virtual ~cmCTestGIT();

private:
  std::string GetWorkingRevision();
  virtual void NoteOldRevision();
  virtual void NoteNewRevision();
  virtual bool UpdateImpl();

  void LoadRevisions();
  void LoadModifications();

  // Parsing helper classes.
  class OneLineParser;
  class DiffParser;
  class CommitParser;
  friend class OneLineParser;
  friend class DiffParser;
  friend class CommitParser;
};

#endif
