
#include <time.h>
#include <stdio.h>


#include "sampler.h"
#include "measure.h"

#ifdef _WIN32
#include<windows.h>
LARGE_INTEGER StartingTime;
LARGE_INTEGER Frequency = { 0 };

void start_counter()
{
	if (Frequency.QuadPart == 0) {
		QueryPerformanceFrequency(&Frequency);
	}
	QueryPerformanceCounter(&StartingTime);

}

double get_counter()
{
	LARGE_INTEGER EndingTime, ElapsedMicroseconds;
	
	
	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;


	//
	// We now have the elapsed number of ticks, along with the
	// number of ticks-per-second. We use these values
	// to convert to the number of elapsed microseconds.
	// To guard against loss-of-precision, we convert
	// to microseconds *before* dividing by ticks-per-second.
	//

	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
	return ElapsedMicroseconds.QuadPart*1.0;
}
#else /* _WIN32 */

#include <sys/time.h>
//#define USE_CLOCK
#define USE_GETTIME
//#define USE_GETTIMEOFDAY

static clock_t ini_clock;

void start_counter_clock()
{
	ini_clock = clock();
}

/* Return useconds */
double get_counter_clock()
{
	clock_t fini;
	fini = clock();
	return (((1.0)*(fini - ini_clock))/CLOCKS_PER_SEC)*1e6;
}

/**** gettime *******/
static struct timespec ini_timespec;

void start_counter_gettime()
{
	//clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ini_timespec);
	clock_gettime(CLOCK_MONOTONIC, &ini_timespec);
}
/* Return useconds */
double get_counter_gettime()
{
	struct timespec fini;
	//clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &fini);
	clock_gettime(CLOCK_MONOTONIC, &fini);

	long nsecs;
	if (fini.tv_nsec < ini_timespec.tv_nsec) {
	//printf(" INI  secs %ld nsecs %ld\n", ini_timespec.tv_sec, ini_timespec.tv_nsec);
	//printf(" FINI secs %ld nsecs %ld\n", fini.tv_sec, fini.tv_nsec);
		fini.tv_nsec += 1e9;
		fini.tv_sec --;
	}
	nsecs = fini.tv_nsec - ini_timespec.tv_nsec;
	long secs = fini.tv_sec - ini_timespec.tv_sec;
	//printf(" secs %ld nsecs %ld\n", secs, nsecs);
	//printf(" Total nsecs %ld\n", nsecs);
	return secs*1000000.0 + nsecs/1000.0;
}

/**** gettimeofday *******/
static struct timeval tstart;

/* Record current time */
void start_counter_tod()
{
  gettimeofday(&tstart, NULL);
}

/* Get number of useconds since last call to start_timer */
double get_counter_tod()
{
  struct timeval tfinish;
  long sec, usec;
  gettimeofday(&tfinish, NULL);
#if 0
  sec = tfinish.tv_sec - tstart.tv_sec;
  usec = tfinish.tv_usec - tstart.tv_usec;   
#else
  struct timeval tres;
  timersub(&tfinish, &tstart, &tres);
  sec = tres.tv_sec;
  usec = tres.tv_usec;
#endif
  //printf(" * Counter = %f usecs %lds %ldus\n", (1e6 * sec + usec), sec, usec) ;
  return (1e6 * sec + usec);
}

void start_counter()
{
#ifdef USE_CLOCK
	start_counter_clock();
#endif
#ifdef USE_GETTIME
	start_counter_gettime();
#endif
#ifdef USE_GETTIMEOFDAY
	start_counter_tod();
#endif
}
double get_counter()
{
#ifdef USE_CLOCK
	return get_counter_clock();
#endif
#ifdef USE_GETTIME
	return get_counter_gettime();
#endif
#ifdef USE_GETTIMEOFDAY
	return get_counter_tod();
#endif
}
#endif /*!WIN32*/

double measure_full(int (*f)(int, int), int param1, int param2,
		int k, double epsilon, int maxsamples)
{
	double result;
	sampler s;

	init_sampler(k, maxsamples, &s);

	do {
		double cyc;
		f(param1, param2); /* warm cache */

		start_counter();

		f(param1, param2);

		cyc = get_counter();

		add_sample(cyc, &s);

	} while (!has_converged(&s, epsilon));
	result = get_min(&s);
	free_sampler(&s);
	return result;
}

