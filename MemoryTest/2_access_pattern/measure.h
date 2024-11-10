
/* Execute the call 'f(param1, param2)' and measure the minimum execution time
 * in useconds between 'k' samples where the error between them is less or
 * equal than 'epsilon'. The executions are limited to 'maxsamples'.
 *
 * For example, to measure the time of 'function_to_measure(p1, p2)' ensuring
 * that the error is less than 1% in 3 executions (and running it a maximum of
 * 100 times):
 *
 *		time = measure_full(function_to_measure, p1, p2, 3, .01, 100);
 */
double measure_full(int (*f)(int, int), int param1, int param2,
		int k, double epsilon, int maxsamples);
