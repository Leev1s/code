import numpy as np
import time

my_arr = np.arange(1000000)
my_list = list(range(1000000))

time_start=time.time()
my_arr2=my_arr*2
time_end=time.time()
print('totally cost',time_end-time_start)

time_start=time.time()
my_list2=my_list*2
time_end=time.time()
print('totally cost',time_end-time_start)
