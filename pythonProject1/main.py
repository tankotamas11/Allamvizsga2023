with open('enronosok.txt', 'r') as file:
    lines = file.read()
persons=lines.strip().split()
with open('kapcsolatok.txt', 'r') as file:
    email = file.read()

emails = email.strip().split("\n")
print(emails[1].split(" "))

outfile=open('kivalasztott.txt','w')

for e in emails:

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
    if email1 >= 0 and email2 >= 0:
        outfile.write(e+ "\n")

