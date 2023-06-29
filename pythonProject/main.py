months=[ "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" ]
def monthToInt(month):
    t=1
    for m in months:
        if month == m:
            return t
        else: t += 1
with open('kapcsolatok.txt', 'r') as file:
    email = file.read()
emails = email.strip().split("\n")
rendezett = []
for i in range(len(emails)):
    t=emails[i].split(" ")
    month=monthToInt(t[3])
    johelyen=0
    if i==0:
        rendezett.append(emails[i])
    else:
        rendezett.append(rendezett[i-1])
        s=i-1
        while s>0:
            rendezett[s]=rendezett[s-1]
            s-=1
        rendezett[0]=emails[i]
        j=0
        while johelyen == 0:
            if j >= i - 1:
                johelyen = 1
            seged1=rendezett[j].split(" ")
            seged2 = rendezett[j+1].split(" ")
            if seged1[4] < seged2[4]:
                johelyen=1
            elif seged1[4] == seged2[4]:
                if monthToInt(seged1[3]) < monthToInt(seged2[3]):
                    johelyen=1
                elif monthToInt(seged1[3]) == monthToInt(seged2[3]):
                    if seged1[2] <= seged2[2]:
                        johelyen=1
                    else:
                        rendezett[j]=rendezett[j+1]
                        rendezett[j+1]=emails[i]
                        j+=1
                else:
                    rendezett[j] = rendezett[j + 1]
                    rendezett[j + 1] = emails[i]
                    j += 1
            else:
                rendezett[j] = rendezett[j + 1]
                rendezett[j + 1] = emails[i]
                j += 1





outfile=open('rendezett.txt','w')

for i in range(len(rendezett)):
    outfile.write(rendezett[i] + "\n")


