#pip install regex
#pip install tqdm
from pathlib import Path
import regex as re
from tqdm import tqdm
import csv

# open the file in the write mode
csv_file = open('../eredmeny.csv', 'w', encoding='UTF8', newline='')
writer = csv.writer(csv_file)
writer.writerow(['kuldo', 'cimzett'])
result = list(Path("../").rglob("../all_documents/"))



for file in tqdm(result):
    with open(file, "rt") as f:
        data = f.read()
        sender = re.search(r'([fFrRoOmM]+: )[\w.+-]+@[\w-]+\.[\w.-]+', data)
        to = re.search(r'([tToO]+: )[\w.+-]+@[\w-]+\.[\w.-]+', data)
        if sender and to:
            writer.writerow([sender.group(0).lower().replace('from: ', ''), to.group(0).lower().replace('to: ', '')])