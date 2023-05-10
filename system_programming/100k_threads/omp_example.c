#include <stdio.h>   /* printf */
#include <stddef.h>  /* size_t */
#include <stdlib.h>  /* exit */
#include <omp.h>

int main()
{
    int num_of_threads = 0;
    int i = 0;
    
    printf("this is sequence\n");
    num_of_threads = omp_get_num_threads();
    printf("num of threads: %d\n", num_of_threads);
    omp_set_num_threads(2);
    
    #pragma omp parallel default(none), private(i), shared(num_of_threads)
    {
        printf("this is parallel\n");
        num_of_threads = omp_get_num_threads();
        printf("num of threads: %d\n", num_of_threads);
        printf("%d\n", ++i);
        
       	#pragma omp for
        for (i = 0; i < 10; i++)
        {
            puts("eat meet");
        }
    }
    
    return 0;
}
