import matplotlib.pyplot as plt
import networkx as nx


with open('../girvanmodszerrel.txt','r') as file:
    sorok=file.readlines()
    szamok= [int(sor.strip()) for sor in sorok]

for szam in szamok:
    print(szam)

with open('../sulyszerintitorles.txt','r') as file:
    sorok2=file.readlines()
    szamok2= [int(sor.strip()) for sor in sorok2]

for szam in szamok2:
    print(szam)
x=[]
y=[]
x2=[]
y2=[]
x3=[]
y3=[]
for i in range(1,szamok[0]+1):
    x.append(i)
    y.append(szamok[i])

for i in range(1,szamok2[0]+1):
    x2.append(i)
    y2.append(szamok2[i])



for i in range(1,szamok2[szamok2[0]+1]+1):
    x3.append(i)
    y3.append(szamok2[i+szamok2[0]+1])
    print('szamok', szamok2[i+szamok2[0]+1])

plt.plot(x,y,color='red',label='Girvan-Newman módszer')
plt.plot(x2,y2,color='green',label='Súlyok szerint növekvő')
plt.plot(x3,y3,color='blue',label='Súlyok szerint csökkenő')

plt.xlabel('Él törlési műveletek száma')
plt.ylabel('Komponensek száma')
plt.title('Gráf szétesése izolált csúcsokra')

plt.legend()

plt.show()

# Gráf létrehozása
G = nx.Graph()
edges=[]

with open('../girvanvizualizalas.txt','r')as f:
    elek= f.read()

adatok=elek.strip().split("\n")
print (adatok[len(adatok)-1])
elekszama =int( adatok[0])
print(len(adatok))

for i in range (0,17):
    G.add_node(i)

for i in range(1,elekszama+1):
    seged=adatok[i].split(" ")
    edge=(int(seged[0]),int(seged[1]))
    edges.append(edge)

# Él törlése
ismetles=-1;
for i in range(elekszama,len(adatok)):
    print(i,"ismetlesek szama:",ismetles)
    seged = adatok[i].split(" ")
    print('legujabb:',seged[0])
    if(i==elekszama):
        print('eleje')

        G.add_edges_from(edges)

        # Csúcsok és élek ábrázolása
        pos = nx.spring_layout(G)
        nx.draw_networkx_nodes(G, pos, node_color='lightblue', node_size=400)
        nx.draw_networkx_edges(G, pos)
        nx.draw_networkx_labels(G, pos, font_color='black', font_size=12)

        # Izolált csúcsok különleges formázása
        izolalt_csucsok = [csucs for csucs in G.nodes() if G.degree[csucs] == 0]
        nx.draw_networkx_nodes(G, pos, nodelist=izolalt_csucsok, node_color='red', node_size=500)
        plt.pause(4)
    else:
        if ismetles!=int(seged[0]) :
            print("itt vagyok")
            ismetles=seged[0]
            plt.clf()
            G.clear()
            for j in range(0, 17):
                G.add_node(j)
            G.add_edges_from(edges)

            # Csúcsok és élek ábrázolása
            pos = nx.spring_layout(G)
            nx.draw_networkx_nodes(G, pos, node_color='lightblue', node_size=400)
            nx.draw_networkx_edges(G, pos)
            nx.draw_networkx_labels(G, pos, font_color='black', font_size=12)

            # Izolált csúcsok különleges formázása
            izolalt_csucsok = [csucs for csucs in G.nodes() if G.degree[csucs] == 0]
            nx.draw_networkx_nodes(G, pos, nodelist=izolalt_csucsok, node_color='red', node_size=500)
            plt.pause(2)




        ismetles = int(seged[0])
        edge = (int(seged[1]), int(seged[2]))
        edges = [p for p in edges if p != edge]
        if i == len(adatok)-1:
            print('vege')
            plt.clf()
            G.clear()
            for j in range(0, 17):
                G.add_node(j)
            G.add_edges_from(edges)
            G.add_edges_from(edges)

            # Csúcsok és élek ábrázolása
            pos = nx.spring_layout(G)
            nx.draw_networkx_nodes(G, pos, node_color='lightblue', node_size=400)
            nx.draw_networkx_edges(G, pos)
            nx.draw_networkx_labels(G, pos, font_color='black', font_size=12)

            # Izolált csúcsok különleges formázása
            izolalt_csucsok = [csucs for csucs in G.nodes() if G.degree[csucs] == 0]
            nx.draw_networkx_nodes(G, pos, nodelist=izolalt_csucsok, node_color='red', node_size=500)
            plt.pause(2)
    # Ábra megjelenítése
plt.axis('off')
plt.show()