/*-------------------------------------------------------------------------
 *
 * win32getrusage.c
 *	  get information about resource utilisation
 *
 * This is a modified copy of the win32 port from postgres for use with
 * picosat.
 *
 * IDENTIFICATION
 *	  win32getrusage.c
 *
 *-------------------------------------------------------------------------
 */

#include <stdio.h>
#include <string.h>
#include "win32getrusage.h"

void
_dosmaperr(unsigned long e)
{
	int			i;

	if (e == 0)
	{
		errno = 0;
		return;
	}

	for (i = 0; i < lengthof(doserrors); i++)
	{
		if (doserrors[i].winerr == e)
		{
			int			doserr = doserrors[i].doserr;
			fprintf(stderr, "mapped win32 error code %lu to %d", e, doserr);
			errno = doserr;
			return;
		}
	}

	fprintf(stderr, "unrecognized win32 error code: %lu", e);
	errno = EINVAL;
}

int
getrusage(int who, struct rusage *rusage)
{
	FILETIME	starttime;
	FILETIME	exittime;
	FILETIME	kerneltime;
	FILETIME	usertime;
	ULARGE_INTEGER li;

	if (who != RUSAGE_SELF)
	{
		/* Only RUSAGE_SELF is supported in this implementation for now */
		errno = EINVAL;
		return -1;
	}

	if (rusage == (struct rusage *) NULL)
	{
		errno = EFAULT;
		return -1;
	}
	memset(rusage, 0, sizeof(struct rusage));
	if (GetProcessTimes(GetCurrentProcess(),
						&starttime, &exittime, &kerneltime, &usertime) == 0)
	{
		_dosmaperr(GetLastError());
		return -1;
	}

	/* Convert FILETIMEs (0.1 us) to struct timeval */
	memcpy(&li, &kerneltime, sizeof(FILETIME));
	li.QuadPart /= 10L;			/* Convert to microseconds */
	rusage->ru_stime.tv_sec = (long) (li.QuadPart / 1000000L);
	rusage->ru_stime.tv_usec = li.QuadPart % 1000000L;

	memcpy(&li, &usertime, sizeof(FILETIME));
	li.QuadPart /= 10L;			/* Convert to microseconds */
	rusage->ru_utime.tv_sec = (long) (li.QuadPart / 1000000L);
	rusage->ru_utime.tv_usec = li.QuadPart % 1000000L;

	return 0;
}
