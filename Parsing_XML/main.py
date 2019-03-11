# -*- coding: utf-8 -*-

import xml.etree.ElementTree as ET

parameter = ["LOCATE_protein/protein/protein_sequence",
             "LOCATE_protein/transcript/transcript_sequence",
             "LOCATE_protein/scl_prediction/source/location",
             "LOCATE_protein/scl_prediction/source/goid"
            ]
result = [[]]
organism = "LOCATE_protein/protein/organism"

tree = ET.parse("mouse.xml")
root = tree.getroot();

for i in range(0, len(parameter)):
    j = 0
    for element in root.findall(parameter[i]):

        result[j].append(element)
        j += 1

print(result)