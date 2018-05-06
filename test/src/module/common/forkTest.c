/***********************************************************************************************************************************
Test Fork Handler
***********************************************************************************************************************************/
#include "common/harnessFork.h"

/***********************************************************************************************************************************
Test Run
***********************************************************************************************************************************/
void
testRun()
{
    // *****************************************************************************************************************************
    if (testBegin("forkAndDetach()"))
    {
        int sessionId = getsid(0);

        HARNESS_FORK_BEGIN()
        {
            HARNESS_FORK_CHILD()
            {
                char buffer[1024];

                forkDetach();

                TEST_RESULT_BOOL(getsid(0) != sessionId, true, "new session id has been created");
                TEST_RESULT_STR(getcwd(buffer, sizeof(buffer)), "/", "current working directory is '/'");
                TEST_RESULT_INT(write(STDIN_FILENO, buffer, strlen(buffer)), -1, "write to stdin fails");
                TEST_RESULT_INT(write(STDOUT_FILENO, buffer, strlen(buffer)), -1, "write to stdout fails");
                TEST_RESULT_INT(write(STDERR_FILENO, buffer, strlen(buffer)), -1, "write to stderr fails");
            }
        }
        HARNESS_FORK_END();
    }
}
