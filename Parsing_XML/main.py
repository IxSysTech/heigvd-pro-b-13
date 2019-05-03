#!/usr/bin/python
import xml.etree.ElementTree as ET
import os
import collections

file = open("outputProt.sql", "w+")
file2 = open("outputLoc.sql", "w+")
file3 = open("outputProtLoc.sql", "w+")
file4 = open("outputProtType.sql", "w+")
file5 = open("outputType.sql", "w+")
file6 = open("outputError.sql", "w+")

path = "../../LOCATE_mouse_v6_20081121.xml"
#path = "minimouse.xml"

prot_seq = ["LOCATE_protein/protein/protein_sequence",          #table prot
            "LOCATE_protein/transcript/transcript_sequence"]

loc_seq = ["LOCATE_protein/scl_prediction/source/location",     #table location
           "LOCATE_protein/scl_prediction/source/goid"]

prot_loc_seq = ["LOCATE_protein/scl_prediction"]                               #table ProtLoc et table ProtType
prot_type_seq = ["LOCATE_protein/protein"]                               #table ProtType

loc_seq_tier = ["LOCATE_protein/literature/reference/locations/location"]

nbProt = os.popen("grep -o '<LOCATE_protein*' " + path + " | wc -l").read()
nbLoc = os.popen("grep -o '<location*' " + path + " | wc -l").read()
nbLocNoPre = os.popen("grep -o '<location>No prediction*' " + path + " | wc -l").read()

nbProtLoc = nbProt

res = []
res2 = []

for i in range(int(nbProt)):
    res.append([""] * 2)

for i in range(int(nbLoc) - int(nbLocNoPre)):
    res2.append([""] * 2)

res3 = res #pour peupler la table ProtLoc on aura autant d'entrer que de prot

organism = "LOCATE_protein/protein/organism"

tree = ET.parse(path)
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
    output = "INSERT INTO \"PRO19\".\"protein\"(id,sprt,sadn) VALUES(" + str(id) + ",'" + row[0] + "','" + row[1] + "');" + '\n'
    id += 1
    #print output
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

#order de la hashmap afin de gagner en lisibilite
goNameOrdered = collections.OrderedDict(sorted(goName.items()))

for key in goNameOrdered:
    output = "INSERT INTO \"PRO19\".\"location\"(id,name,goid) VALUES(" + str(id) + ",'" + "GO:" + str(key) + "','"+ goNameOrdered[key] + "');" + '\n'
    id += 1
    #print output
    file2.write(output)



#-------------
# peuplage table PROTLOC


print "Peuplage table inter ProtLoc"
protID = 0 # sert de clef pour protID car on incremente de 1 a chaque fois dans la table de Prot
locID = 0

key_list = list(goNameOrdered.keys())

for element in root.findall(prot_loc_seq[0]):
    for source in element:
        if(source.find('location').text != "No prediction"):
            try:
                goid = source.find('goid').text     #va nous servir a retrouver l'id de loc
                keygo = goid[3:10]
                for i in range(len(key_list)):
                    if keygo == key_list[i] :
                        locID = i
                        output = "INSERT INTO \"PRO19\".\"prot_to_loc\"(fk_prot, fk_loc) VALUES('" + str(protID) + "','" + str(locID) + "');" + '\n'
                        #print output
                        file3.write(output)
            except:
                file6.write("error at ProtID = " + str(protID) + '\n')

    protID += 1

os.system('cat outputProtLoc.sql | sort | uniq > outputProtLoc2.sql') #erreur premiere ligne ?

#-------------
#peuplage table ProtType

protID = 0
typeID = 0 # 0 humain, 1 mouse
for element in root.findall(prot_type_seq[0]):
    for source in element:
        if source.tag == "organism":
            organism = source.text
            typeID = (0 , 1)[organism == 'Mouse']
            output = "INSERT INTO \"PRO19\".\"prot_to_type\"(fk_prot, fk_type) VALUES('" + str(protID) + "','" + str(typeID) + "');" + '\n'
            #print output
            file4.write(output)
    protID += 1

#-----------
#peuplage table type
file5.write("INSERT INTO \"PRO19\".\"typeOrganism\"(ID, Name) VALUES('0', 'Human');" + '\n' +
            "INSERT INTO \"PRO19\".\"typeOrganism\"(ID, Name) VALUES('1', 'Mouse');" + '\n')

#----------
file.close()
file2.close()
file3.close()
file4.close()
file5.close()
file6.close()