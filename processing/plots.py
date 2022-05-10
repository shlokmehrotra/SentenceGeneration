import sys
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
'''
import re
from urllib.request import urlopen
from collections import Counter
url = "https://raw.githubusercontent.com/formcept/whiteboard/master/nbviewer/notebooks/data/harrypotter/Book%201%20-%20The%20Philosopher's%20Stone.txt"
response = urlopen(url)
counter = 0

f = open("parsed_book1.txt", "w")
for line in response:
    parse = str(line.decode("utf-8")).lower()
    parse = parse.replace("-", " ")
    if(parse.startswith("page |")):continue
    f.write(re.sub("[^a-z0–9_\- ]*","",parse))
f.close()

file = re.split("[ \-]+", open("parsed_book1.txt", "r").read())
most_common = Counter(file)


# STARTING HERE
sorted_vals = list(zip(*most_common.most_common(100)))

X = sorted_vals[0] 
Y = sorted_vals[1]

matplotlib.rcParams['figure.dpi'] = 300

plt.bar(X, Y, width=0.8, color = (0.5,0.1,0.5,0.6))
plt.title('100 Most Common Words vs. Frequencies')
plt.xlabel('Words')
plt.ylabel('Frequencies')
plt.tick_params( axis='x', which='both', bottom=False, top=False, labelbottom=False)
plt.savefig("test.png")

# print(sum([most_common[k] for k in most_common]))
# print(most_common.most_common(30))