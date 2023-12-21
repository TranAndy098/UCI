import sys
from pm import Physical_Memory

if __name__ == "__main__":
    
    dp = str(sys.argv[1]) == "dp"
    initfile = str(sys.argv[-2])
    inputfile = str(sys.argv[-1])
    pm = Physical_Memory(dp ,initfile, inputfile)
    output = pm.output
    
    f = open("output-dp.txt", "w") if dp else open("output.txt", "w")
    f.write(output.lstrip().rstrip())
    f.close()