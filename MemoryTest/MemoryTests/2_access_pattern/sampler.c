#include <stdlib.h>
#include <stdio.h>
#include "sampler.h"


struct sampler_t {
	int MAX_VALUES;
	double *values; //Sorted array of values values[MAX_VALUES], minimum at first position
	int MAX_SAMPLES;
#if KEEP_SAMPLES
	double *samples; //Additional sampled values  samples[MAX_VALUES+MAX_SAMPLES]
#endif
	int samplecount;
};

/* Start new sampling process. Keep a maximum of 'k' values and 'maxsamples' (maxsamples >= k) */
void init_sampler(int k, int maxsamples, sampler *res)
{
  struct sampler_t *s = calloc(1, sizeof(struct sampler_t));
  s->MAX_VALUES = k;
  s->values = calloc(s->MAX_VALUES, sizeof(double));
  s->MAX_SAMPLES = maxsamples + k;
#if KEEP_SAMPLES
  /* Allocate extra for wraparound analysis */
  s->samples = calloc(s->MAX_SAMPLES, sizeof(double));
#endif
  s->samplecount = 0;
  *res = s;
}

/* Free resources used by sampling process */
void free_sampler(sampler *res)
{
  if (!res) return;
  struct sampler_t *s = *res;
  if (s->values)
    free(s->values);
  s->values = NULL;
#if KEEP_SAMPLES
  if (s->samples)
    free(s->samples);
  s->samples = NULL;
#endif
  free(s);
  *res = NULL;
}
/* Add new sample.  */
void add_sample(double val, sampler *res)
{
  int pos = 0;
  struct sampler_t *s = *res;
  if (s->samplecount < s->MAX_VALUES) {
    pos = s->samplecount;
    s->values[pos] = val;
  } else if (val < s->values[s->MAX_VALUES-1]) {
    pos = s->MAX_VALUES-1;
    s->values[pos] = val;
  }
#if KEEP_SAMPLES
  if (s->samplecount < s->MAX_SAMPLES)
	s->samples[s->samplecount] = val;
#endif
  s->samplecount++;
  /* Insertion sort */
  while (pos > 0 && s->values[pos-1] > s->values[pos]) {
    double temp = s->values[pos-1];
    s->values[pos-1] = s->values[pos];
    s->values[pos] = temp;
    pos--;
  }
}

/* Get current minimum */
double get_min(sampler *res)
{
  struct sampler_t *s = *res;
  return s->values[0];
}

/* What is relative error for kth smallest sample */
double err(sampler *res, int k)
{
  struct sampler_t *s = *res;
  if (s->samplecount < k)
    return 1000.0;
  return (s->values[k-1] - s->values[0])/s->values[0];
}

/* Have k minimum measurements converged within epsilon? */
int has_converged(sampler *res, double epsilon_arg)
{
  struct sampler_t *s = *res;
  if ((s->samplecount >= s->MAX_VALUES) &&
      ((1 + epsilon_arg)*s->values[0] >= s->values[s->MAX_VALUES-1]))
    return s->samplecount;
  if ((s->samplecount >= s->MAX_SAMPLES))
    return -1;
  return 0;
}

void show_values(sampler *res)
{
    int i;
    struct sampler_t *s = *res;
    printf(" %d smallest values: [", s->MAX_VALUES);
    for (i = 0; i < s->MAX_VALUES; i++)
      printf("%.0f%s", s->values[i], i==s->MAX_VALUES-1 ? "]\n" : ", ");
}
#if KEEP_SAMPLES
void show_samples(sampler *res)
{
    int i;
    struct sampler_t *s = *res;
    printf(" %d samples [", s->samplecount);
    for (i = 0; i < s->samplecount; i++)
      printf("%.0f%s", s->samples[i], i==s->samplecount-1 ? "]\n" : ", ");
}
#endif
