/*
 * File: condvar1_1.c
 *
 *
 * --------------------------------------------------------------------------
 *
 *      Pthreads4w - POSIX Threads Library for Win32
 *      Copyright(C) 1998 John E. Bossom
 *      Copyright(C) 1999-2018, Pthreads4w contributors
 *
 *      Homepage: https://sourceforge.net/projects/pthreads4w/
 *
 *      The current list of contributors is contained
 *      in the file CONTRIBUTORS included with the source
 *      code distribution. The list can also be seen at the
 *      following World Wide Web location:
 *      https://sourceforge.net/p/pthreads4w/wiki/Contributors/
 *
 * This file is part of Pthreads4w.
 *
 *    Pthreads4w is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    Pthreads4w is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Pthreads4w.  If not, see <http://www.gnu.org/licenses/>. *
 *
 * --------------------------------------------------------------------------
 *
 * Test Synopsis:
 * - Test CV linked list management.
 *
 * Test Method (Validation or Falsification):
 * - Validation:
 *   Initiate and destroy several CVs in random order.
 *
 * Requirements Tested:
 * - 
 *
 * Features Tested:
 * - 
 *
 * Cases Tested:
 * - 
 *
 * Description:
 * - Creates and then imediately destroys a CV. Does not
 *   test the CV.
 *
 * Environment:
 * - 
 *
 * Input:
 * - None.
 *
 * Output:
 * - File name, Line number, and failed expression on failure.
 * - No output on success.
 *
 * Assumptions:
 * -
 *
 * Pass Criteria:
 * - All initialised CVs destroyed without segfault.
 * - Successfully broadcasts all remaining CVs after
 *   each CV is removed.
 *
 * Fail Criteria:
 */

#include <stdlib.h>
#include "test.h"

enum {
  NUM_CV = 100
};

static pthread_cond_t cv[NUM_CV];

int
main()
{
  int i, j;

  for (i = 0; i < NUM_CV; i++)
    {
      /* Traverse the list before every init of a CV. */
      assert(pthread_timechange_handler_np(NULL) == (void *) 0);
      assert(pthread_cond_init(&cv[i], NULL) == 0);
    }

  j = NUM_CV;
  (void) srand((unsigned)time(NULL));

  do
    {
      i = (NUM_CV - 1) * rand() / RAND_MAX;
      if (cv[i] != NULL)
        {
          j--;
          assert(pthread_cond_destroy(&cv[i]) == 0);
          /* Traverse the list every time we remove a CV. */
          assert(pthread_timechange_handler_np(NULL) == (void *) 0);
        }
    }
  while (j > 0);

  return 0;
}
