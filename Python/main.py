import matplotlib.pyplot as plt
import networkx as nx

months=[ "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" ]

def monthToInt(month):
    t=1
    for m in months:
        if month == m:
            return t
        else:
             t += 1



persons=[]
emails = []
sendings= []
sizes = []
colors=[]
for _ in range(50):
    sendings.append(0)
    sizes.append(200)
    colors.append('lightblue')

with open('enronosok.txt', 'r') as file:
    lines = file.read()



persons=lines.strip().split()
print(len(persons))


with open('kapcsolatok.txt', 'r') as file:
    email = file.read()


emails = email.strip().split("\n")
print(emails[1].split(" "))


# Gráf létrehozása
G = nx.Graph()
# Csúcsok hozzáadása
edges = []
num=0

for e in emails:
    num+=1
    t = e.split(" ")

    try:
        index = persons.index(t[0])
        email1 = index
    except ValueError:
        email1 = -1

    try:
        index = persons.index(t[1])
        email2 = index
    except ValueError:
        email2 = -1

    if email1 >= 0 and email2 >= 0 and email1 != email2:
        sendings[email1]+=1
        edge = (email1, email2)
        edges.append(edge)
        if sendings[email1]<21:
            sizes[email1] = 200

        elif sendings[email1] >20 and sendings[email1] < 51: #lightblue
            sizes[email1]=400

        elif sendings[email1] >50 and sendings[email1]<101: #blue
            sizes[email1]=600

        elif sendings[email1] >100 and sendings[email1]<250: #red
            sizes[email1]=800

        else:
            sizes[email1]=900

    if num%1000 == 0 or num == len(emails):
        plt.clf()
        G.add_edges_from(edges)
        nx.draw(G, with_labels=True, node_color=colors, node_size=sizes, font_size=12, font_color='black')
        plt.pause(4)


plt.show()


        #green

