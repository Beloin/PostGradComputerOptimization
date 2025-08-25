#include <stdio.h>
#include <omp.h>

int main() {
    const int NUM_TEAMS = 4;
    const int THREADS_PER_TEAM = 8;

    #pragma omp target teams num_teams(NUM_TEAMS) thread_limit(THREADS_PER_TEAM)
    #pragma omp parallel
    {
        #pragma omp single
        {
            int team_id = omp_get_team_num();
            int thread_id = omp_get_thread_num();
            int mt = omp_get_max_threads();
            printf("Single: Team %d, Thread %d - Max threads: %d\n", team_id, thread_id, mt);
        }
    }

    return 0;
}
