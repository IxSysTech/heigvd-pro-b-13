#!/usr/bin/python
import xml.etree.ElementTree as ET
import pickle
import os

path = "minimouse.xml"
#path = "../../LOCATE_mouse_v6_20081121.xml"

root = ET.parse(path)
searchParents = ["protein", "transcript", "scl_prediction"]
searchedChildren = ["protein_sequence", "transcript_sequence", "organism"]
searchedGChildren = ["location", "goid"]
temp = [[]]

for element in root.iter():
    if element is not None:
        try:
            for element_child in element:
                newTab = []

                for element_grandchild in element_child: # on regarde si on trouve un parent

                    for element_ggChild in element_grandchild:  #pour organism, proteinSeq, transcript_S,
                        for i in searchParents:
                            if i in element_grandchild.tag:
                                for j in searchedChildren:
                                    if j in element_ggChild.tag :
                                        newTab.append(element_ggChild.text)

                                if  "source" in element_ggChild.tag: # pour goID
                                    tabGo = []
                                    for element_gggChild in element_ggChild:
                                        for k in searchedGChildren:  # on verifie qu'il y a bien une des sequences qu'on cherche
                                            if k in element_gggChild.tag and element_gggChild.text != "No prediction":
                                                if element_gggChild.tag == "goid" :
                                                    tabGo.append((element_gggChild.text, tempo))
                                                    newTab.append(tabGo)
                                                else : tempo = element_gggChild.text
                if temp == [[]] :
                    temp[0]=(newTab)
                elif newTab != [] : temp.append(newTab)

        except:
            continue

organism = {}
prot = {}
loc = {}
idOrg = idProt = idLoc = 0
protLoc = {}
protType = {}

if os.path.isfile("exportedValue") :
    with open("exportedValue", 'rb') as f:
        organism, prot, loc, protLoc, protType = pickle.load(f)


for i in temp :
    if i[0] not in organism :   #table organisme
        organism[i[0]] = (idOrg, i[0])
        idOrg += 1
    if i[2] not in prot :   #table prot
        prot[i[2]] = (idProt, i[1])
        idProt += 1
    for x in range(3, len(i)):         #table loc
        id = i[x][0][0][3:10]
        if id not in loc :
            loc[id] = (idLoc, i[x][0][1])
            idLoc += 1
    if prot[i[2]][0] not in protType:  #si la prot n'a pas de organisme affilie - Table ProtType
        protType[prot[i[2]][0]] = organism[i[0]][0]
    else :
        temp = [protType[prot[i[2]][0]]]
        if organism[i[0]][0] not in temp :
            temp.append(organism[i[0]][0])
        protType[prot[i[2]][0]] = temp

    if prot[i[2]][0] not in protLoc: #protloc
        temp = []
        for x in range(3, len(i)):  # table loc
            id = i[x][0][0][3:10]
            if loc[id][0] not in temp :
                temp.append(loc[id][0]) #on met l'id de la loc dans temp
        protLoc[prot[i[2]][0]] = temp
    else :
        temp = protLoc[prot[i[2]][0]]
        for x in range(3, len(i)):  # table loc
            id = i[x][0][0][3:10]
            if loc[id][0] not in temp:
                temp.append(loc[id][0])  # on met l'id de la loc dans temp
        protLoc[prot[i[2]][0]] = temp

with open("exportedValue", 'wb') as f:
    pickle.dump((organism, prot, loc, protLoc, protType), f)

