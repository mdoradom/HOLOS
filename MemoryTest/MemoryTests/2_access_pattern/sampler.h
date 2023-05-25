#ifndef SAMPLER_H__
#define SAMPLER_H__

//#define KEEP_VALS 1
//#define KEEP_SAMPLES 1


typedef struct sampler_t * sampler;

/* Start new sampling process. Keep a maximum of 'k' values and 'maxsamples' (maxsamples >= k) */
void init_sampler(int k, int maxsamples, sampler *s);

/* Free resources used by sampling process */
void free_sampler(sampler *s);

/* Add new sample.  */
void add_sample(double val, sampler *s);

/* Get current minimum */
double get_min(sampler *s);

/* What is relative error for kth smallest sample */
double err(sampler *s, int k);

/* Have k minimum measurements converged within epsilon?
   Returns 0 if not converged, #samples if converged, and -1 if can't
   reach convergence */
int has_converged(sampler *s, double epsilon_arg);

/* Show values */
void show_values(sampler *s);

/* Show all samples */
void show_samples(sampler *s);

#endif /* SAMPLER_H__ */
