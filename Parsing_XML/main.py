#!/usr/bin/python
import xml.etree.ElementTree as ET
import os

file = open("outputProt.sql", "w+")
file2 = open("outputLoc.sql", "w+")
prot_seq = ["LOCATE_protein/protein/protein_sequence",
            "LOCATE_protein/transcript/transcript_sequence"]
loc_seq = ["LOCATE_protein/scl_prediction/source/location",
           "LOCATE_protein/scl_prediction/source/goid"]

prot_loc_seq = ["LOCATE_protein/protein/protein_sequence",
                "LOCATE_protein/transcript/transcript_sequence",
                "LOCATE_protein/scl_prediction/source/goid"]

loc_seq_tier = ["LOCATE_protein/literature/reference/locations/location"]

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

# peuplage table proteine
print "Peuplage table proteine"
for i in range(0, len(prot_seq)):
    j = 0
    for element in root.findall(prot_seq[i]):
        res[j][i] = element.text
        j += 1
id = 0
for row in res:
    output = "INSERT INTO protein(id,sprt,sadn) VALUES(" + str(id) + ",'" + row[0] + "','" + row[1] + "');" + '\n'
    id += 1
    print output
    file.write(output)

#--------
""" pas utilise car c'est les precidictions
#trouver tous les tiers 1/2
for i in range(0, len(loc_seq_tier)):
    for element in root.findall(loc_seq_tier[0]):
        print '\n', element.attrib['goid'].split(';')
        for child in element:
            print child.tag, child.text
"""

#---------
# peuplage table Localisation
print "Peuplage table loc"
# trouver toute les paire go id nom
for i in range(0, len(loc_seq)):
    j = 0
    for element in root.findall(loc_seq[i]):
        if element.text != "No prediction":
            res2[j][i] = element.text
            j += 1

id = 0
goName = {}
#construction de la hashtable afin d'entrer qu'une seule fois la goID
for row in res2:
    goID = row[1][3:10]
    if goID not in goName :
        if goID != "" :
            goName[goID] = row[0]


for key in goName:
    output = "INSERT INTO localisation(id,name,goid) VALUES(" + str(id) + ",'" + "GO:" + str(key) + "','"+ goName[key] + "');" + '\n'
    id += 1
    print output
    file2.write(output)
#-------------
# peuplage table PROTLOC

#incrementer de 1 par 1 notre counter par LOC


file.close()
file2.close()

