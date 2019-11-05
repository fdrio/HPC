import numpy as np
import pandas as pd
import sys

#generates random numbers [-100, 100] of size argv[1]
l = np.random.randint(-100,100,int(sys.argv[1]))

#convert to df
df = pd.DataFrame(l)


#save df to csv
df.to_csv("list_"+str(sys.argv[1]),header=False,index=False)


