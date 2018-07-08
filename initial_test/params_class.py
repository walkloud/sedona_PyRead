
class particles():
    ''' HELP '''
    def __init__(self):
        self.n_emit = 1
        self.energy = 1.9


    def set_params(self,params):
        for k in params:
            print('you are changing the value of %s from %s to %s' %(k,self.k,params[k]))
            self.k = params[k]
