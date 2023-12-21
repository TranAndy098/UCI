max_pm = 524288
disk_dim = (1024, 512)

class Physical_Memory:
    def __init__(self, demand_paging, initfile, inputfile):
        self.dp = demand_paging
        self.pm = [0] * max_pm
        self.disk = [[0]*disk_dim[1] for i in range(disk_dim[0])]
        
        if demand_paging:
            self.free_frames = [i for i in range(512)]
            self.free_frames.remove(0)
            self.free_frames.remove(1)
        
        self.init(initfile)
        self.output = self.va_translate(inputfile)


    def init(self, initfile):
        [line_1, line_2] = open(initfile, "r").readlines()
        line_1 = line_1.rstrip().split()
        line_2 = line_2.rstrip().split()

        for i in range(len(line_1)//3):
            (s,z,f) = ([int(line_1[3*i]), int(line_1[3*i + 1]), int(line_1[3*i + 2])])
            
            self.pm[2*s] = z
            self.pm[2*s + 1] = f
            
            if self.dp and f > 0:
                self.free_frames.remove(f)

        for i in range(len(line_2)//3):
            (s,p,f) = ([int(line_2[3*i]), int(line_2[3*i + 1]), int(line_2[3*i + 2])])
            
            if self.pm[2*s+1] < 0:
                self.disk[-self.pm[2*s+1]][p] = f
            else:
                self.pm[self.pm[2*s+1]*512 + p] = f
            
            if self.dp and f > 0:
                self.free_frames.remove(f)

    """  
    def va_translate_no_dp(self, inputfile):
        line = open(inputfile, "r").readline().rstrip().split()
        pas = ""
        for i in line:
            i = int(i)
            (s,w,p,pw) = (i >> 18, i & 0x1FF, (i >> 9) & 0x1FF, i & 0x3FFF)
            if pw >= self.pm[2*s]:
                pas += "-1 "
            else:
                pas += str(self.pm[self.pm[2*s + 1]*512 + p]*512 + w) + " "
        return pas
    """ 
    def va_translate(self, inputfile):
        line = open(inputfile, "r").readline().rstrip().split()
        pas = ""

        for i in line:
            i = int(i)
            (s,w,p,pw) = (i >> 18, i & 0x1FF, (i >> 9) & 0x1FF, i & 0x3FFFF)
            if pw >= self.pm[2*s]:
                pas += "-1 "
            else:
                if self.pm[2*s + 1] < 0:

                    f1 = self.free_frames[0]
                    self.free_frames.remove(f1)
                    b = -self.pm[2*s + 1]

                    for i in range(disk_dim[1]):
                        self.pm[disk_dim[1] * f1 + i] = self.disk[b][i]
                    
                    self.pm[2*s + 1] = f1

                if self.pm[self.pm[2*s + 1]*512 + p] < 0:

                    f2 = self.free_frames[0]
                    self.free_frames.remove(f2)
                    b = -self.pm[self.pm[2*s + 1]*512 + p]

                    for i in range(disk_dim[1]):
                        self.pm[disk_dim[1] * f2 + i] = self.disk[b][i]

                    self.pm[self.pm[2*s + 1]*512 + p] = f2
                
                pas += str(self.pm[self.pm[2*s + 1]*512 + p]*512 + w) + " "
        return pas

    