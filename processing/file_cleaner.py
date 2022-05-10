import sys
import getopt
import re
from urllib.request import urlopen
from collections import Counter
import matplotlib
import matplotlib.pyplot as plt
#starting with book 1
#book URLS
'''
Book1: https://raw.githubusercontent.com/formcept/whiteboard/master/nbviewer/notebooks/data/harrypotter/Book%201%20-%20The%20Philosopher's%20Stone.txt
Book2: https://raw.githubusercontent.com/formcept/whiteboard/master/nbviewer/notebooks/data/harrypotter/Book%202%20-%20The%20Chamber%20of%20Secrets.txt
Book3: https://raw.githubusercontent.com/formcept/whiteboard/master/nbviewer/notebooks/data/harrypotter/Book%203%20-%20The%20Prisoner%20of%20Azkaban.txt
Book4: https://raw.githubusercontent.com/formcept/whiteboard/master/nbviewer/notebooks/data/harrypotter/Book%204%20-%20The%20Goblet%20of%20Fire.txt
Book5: https://raw.githubusercontent.com/formcept/whiteboard/master/nbviewer/notebooks/data/harrypotter/Book%205%20-%20The%20Order%20of%20the%20Phoenix.txt
Book6: https://raw.githubusercontent.com/formcept/whiteboard/master/nbviewer/notebooks/data/harrypotter/Book%206%20-%20The%20Half%20Blood%20Prince.txt
Book7: https://raw.githubusercontent.com/formcept/whiteboard/master/nbviewer/notebooks/data/harrypotter/Book%207%20-%20The%20Deathly%20Hallows.txt

python3 file_cleaner.py -i <input_file> -o <ouput_file> -remove <number of common words to remove>
'''
class Optimize:
    def __init__(self):
        self.setup(sys.argv)
        self.run()
    def setup(self, argv):
        self.arg_input = ""
        self.arg_output = ""
        self.arg_remove = ""
        arg_help = "{0} -i <input> -o <output> -r <remove>".format(argv[0])
        try:
            opts, args = getopt.getopt(argv[1:], "u:o:r:", ["help", "input=", 
            "output=", "remove="])
        except:
            print(arg_help)
            sys.exit(2)
        
        for opt, arg in opts:
            if opt in ("-h", "--help"):
                print(arg_help)  # print the help message
                sys.exit(2)
            elif opt in ("-i", "--input"):
                self.arg_input = arg
            elif opt in ("-o", "--output"):
                self.arg_output = arg
            elif opt in ("-r", "--remove"):
                # if (int(arg) < 0):
                #     raise Exception("Words removed cannot be negative")
                self.arg_remove = arg
        
    def run(self):
        '''
        default_params:
        input: first harry_potter book
        output: parsed_book.txt
        remove: 0 words are removed
        '''
        print("Args passed")
        print(self.arg_input, self.arg_output, self.arg_remove)
        if(self.arg_input == ""):
            self.arg_input = "https://raw.githubusercontent.com/formcept/whiteboard/master/nbviewer/notebooks/data/harrypotter/Book%201%20-%20The%20Philosopher's%20Stone.txt"
        
        if(self.arg_output == ""):
            self.arg_output = "parsed_book.txt"

        if(self.arg_remove == ""):
            self.arg_remove = "0"

        response = urlopen(self.arg_input)

        f = open(self.arg_output, "w")
        for line in response:
            parse = str(line.decode("utf-8")).lower()
            parse = parse.replace("-", " ")
            if(parse.startswith("page |")):continue
            f.write(re.sub("[^a-z0–9_\- ]*","",parse))
        f.close()

        file = re.split("[ \-]+", open(self.arg_output, "r").read())
        self.most_common = Counter(file)
        #print(self.most_common.most_common(10))
        # data = urlopen(self.arg_output).read()
        # print(data[:10])

        with open(self.arg_output, 'r') as file :
            data = file.read()
        for key, value in self.most_common.most_common(int(self.arg_remove)):
            data = data.replace(" " + key + " ", " ")
        with open(self.arg_output, 'w') as file:
            file.write(data)


    def display_words(self):
        sorted_vals = list(zip(*self.most_common.most_common(100)))

        X = sorted_vals[0] 
        Y = sorted_vals[1]

        matplotlib.rcParams['figure.dpi'] = 300

        plt.bar(X, Y, width=0.8, color = (0.5,0.1,0.5,0.6))
        plt.title('100 Most Common Words vs. Frequencies')
        plt.xlabel('Words')
        plt.ylabel('Frequencies')
        plt.tick_params( axis='x', which='both', bottom=False, top=False, labelbottom=False)
        plt.savefig("test.png")

Optimize()

# print(sum([most_common[k] for k in most_common]))
# print(most_common.most_common(30))

