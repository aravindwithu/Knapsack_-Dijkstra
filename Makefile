run:
	gcc Q1-1_brute_force_knapsack.c -lm -o Q1-1_brute_force_knapsack.out
	gcc Q1-2_greedy_algorithm.c -lm -o Q1-2_greedy_algorithm.out
	gcc Q1-3_dynamic_programming_knapsack.c -lm -o Q1-3_dynamic_programming_knapsack.out
	gcc Q2_dijikstra.c -lm -o Q2_dijikstra.out

clean:
	rm Q1-1_brute_force_knapsack.out
	rm Q1-2_greedy_algorithm.out
	rm Q1-3_dynamic_programming_knapsack.out
	rm Q2_dijkstra.out