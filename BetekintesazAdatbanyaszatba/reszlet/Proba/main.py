from pathlib import Path
import regex as re
from tqdm import tqdm
import csv

# open the file in the write mode
csv_file = open('eredmeny.csv', 'w', encoding='UTF8', newline='')
writer = csv.writer(csv_file)
for i in range (1, 840):
    result = list(Path("../").rglob("*/all_documents/%s" %i) )
    print (result)
    for file in tqdm(result):
         with open(file, "rt") as f:
            data = f.read()
            dateof = re.search(r'(?:, )([0-9]+) ([A-z]+) ([0-9]+)', data)
            sender = re.search(r'([fFrRoOmM]+: )[\w.+-]+@[\w-]+\.[\w.-]+', data)
            to = re.search(r'([tToO]+: )[\w.+-]+@[\w-]+\.[\w.-]+', data)

            print (dateof)
            if sender and to and dateof:
                writer.writerow([sender.group(0).lower().replace('from: ' ,''), to.group(0).lower().replace('to: ' , ''), dateof.group(0).lower().replace('dateof: ', '')])