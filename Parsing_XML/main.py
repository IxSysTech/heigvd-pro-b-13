#!/usr/bin/python
import xml.etree.ElementTree as ET
import os

file = open("outputProt.sql", "w+")
file2 = open("outputLoc.sql", "w+")
prot_seq = ["LOCATE_protein/protein/protein_sequence",
            "LOCATE_protein/transcript/transcript_sequence"]
loc_seq = ["LOCATE_protein/scl_prediction/source/location",
           "LOCATE_protein/scl_prediction/source/goid"]

nbProt = os.popen("grep -o '<LOCATE_protein*' minimouse.xml | wc -l").read()
nbLoc = os.popen("grep -o '<location*' minimouse.xml | wc -l").read()
nbLocNoPre = os.popen("grep -o '<location>No prediction*' minimouse.xml | wc -l").read()

res = []
res2 = []

for i in range(int(nbProt)):
    res.append([""] * 2)

for i in range(int(nbLoc) - int(nbLocNoPre)):
    res2.append([""] * 2)

organism = "LOCATE_protein/protein/organism"

tree = ET.parse("minimouse.xml")
root = tree.getroot();

"""
for i in range(0, len(prot_seq)):
    j = 0
    for element in root.findall(prot_seq[i]):
        res[j][i] = element.text
        j += 1
id = 0
for row in res:
    output = "INSERT INTO protein(id,sprt,sadn) VALUES(" + str(id) + ",'" + row[0] + "','" + row[1] + "');"
    id += 1
    file.write(output)
"""

for i in range(0, len(loc_seq)):
    j = 0
    for element in root.findall(loc_seq[i]):
        if element.text != "No prediction":
            res2[j][i] = element.text
            j += 1
id = 0
for row in res2:
    output = "INSERT INTO localisation(id,name,goid) VALUES(" + str(id) + ",'" + row[0] + "','" + row[1] + "');"
    id += 1
    print(output)
    #file2.write(output)

file.close()
file2.close()
