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

for i in temp :
    print i
