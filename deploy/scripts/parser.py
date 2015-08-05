#!/usr/bin/python

#./parser --dir folder_name

import sys
import getopt
from os import listdir
from os.path import isfile, join

class Parser:

    def __init__(self, file_name):
        self.file_name = file_name
        self.text = []
        with open(self.file_name, 'rb') as f:
            for line in f:
                self.text.append(line)




    def create_csv_for_each_replication(self):
        new_text = []
        n_replications = 1
        new_file_name = self.file_name[:-4]+'_rep'+str(n_replications)+'.csv'
        new_csv = open(new_file_name, 'wb')
        for line in self.text:
            if line[0] == "=":
                n_replications = n_replications + 1
                new_csv.close()
            elif line[0] == 'g':
                new_file_name = self.file_name[:-4]+'_rep'+str(n_replications)+'.csv'
                new_csv = open(new_file_name, 'wb')
                new_csv.write(line)
            elif len(line) <= 1:
                pass;
            else:
                new_csv.write(line)



def main(argv):
    folder_name = ''

    try:
        opts, args = getopt.getopt(argv, '', ['dir='])
        if opts < 1:
            print('required option(s) missing')
            print "Uso: ./parser.py --dir <folder-name>"
            sys.exit(2)
    except getopt.error as err:
        print(err)
        print "Uso: ./parser.py --dir <folder-name>"
        sys.exit(2)


    for opt, arg in opts:
        if opt == '--dir':
            folder_name = arg
        else:
            assert False, "unhandled option"

    files = [ f for f in listdir(folder_name) if isfile(join(folder_name,f)) and f[len(f)-3:] == 'out'] 
    for f in files:
        parser = Parser(join(folder_name, f))
        parser.create_csv_for_each_replication()



if __name__ == "__main__":
    main(sys.argv[1:])




        
