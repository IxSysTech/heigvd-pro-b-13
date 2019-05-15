#!/usr/bin/python
import xml.etree.ElementTree as ET

path = "minimouse.xml"
#path = "../../LOCATE_mouse_v6_20081121.xml"

# map1 : prot : transcript
# map2 : goid loc
# map3 :
# struct final : [{(protSeq, organism) : [transcriptSeq, [{goid : loc}]}, ... ]

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
                                        #print element_ggChild.tag, element_ggChild.text

                                if  "source" in element_ggChild.tag: # pour goID
                                    tabGo = []
                                    for element_gggChild in element_ggChild:
                                        for k in searchedGChildren:  # on verifie qu'il y a bien une des sequences qu'on cherche
                                            if k in element_gggChild.tag and element_gggChild.text != "No prediction":
                                                if element_gggChild.tag == "goid" :
                                                    tabGo.append((element_gggChild.text, tempo))
                                                    newTab.append(tabGo)
                                                else : tempo = element_gggChild.text
                                                #print element_gggChild.tag, element_gggChild.text
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

for i in temp :
    if i[0] not in organism :   #table organisme
        organism[i[0]] = {idOrg, i[0]}
        idOrg += 1
    if i[2] not in prot :   #table prot
        prot[i[2]] = {idProt, i[1]}
        idProt += 1
    if i[3] !=  [] :    #table loc
        for j in i[3] :
            if list(j)[0][3:10] not in loc :
                loc[list(j)[0][3:10]] = (idLoc, list(j)[1])
                idLoc += 1
    if prot[i[2]][0] not in protType:  #si la prot n'a pas de organisme affilie - Table ProtType
        protType[prot[i[2][0]]] = organism[i[0]][0]
    else :
        temp = protType[prot[i[2][0]]].values()
        if organism[i[0]][0] not in temp :
            temp.append(organism[i[0]][0])
        protType[prot[i[2][0]]] = temp
    if prot[i[2]][0] not in protLoc:
        temp = []
        for j in i[3] :
            if j[0][3:10] not in temp :
                temp.append(j[0][3:10])
        protLoc[prot[i[2][0]]] = temp
    else :
        temp = protLoc[prot[i[2][0]]].values()
        for j in i[3] :
            if j[0][3:10] not in temp :
                temp.append(loc[j[0][3:10]][0])
        protLoc[prot[i[2][0]]] = temp



#temp 0 : mouse
#temp 1 : S prot
#temp 2 : S adn
#temp 3 : pair go name


